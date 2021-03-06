/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS user32.dll
 * FILE:            win32ss/user/user32/misc/imm.c
 * PURPOSE:         User32.dll Imm functions
 * PROGRAMMERS:     Dmitry Chapyshev (dmitry@reactos.org)
 *                  Katayama Hirofumi MZ (katayama.hirofumi.mz@gmail.com)
 * UPDATE HISTORY:
 *      01/27/2009  Created
 */

#include <user32.h>
#include <strsafe.h>
#include <ddk/imm.h>

WINE_DEFAULT_DEBUG_CHANNEL(user32);

#define IMM_INIT_MAGIC 0x19650412

/* Is != NULL when we have loaded the IMM ourselves */
HINSTANCE ghImm32 = NULL;

BOOL bImmInitializing = FALSE;

/* define stub functions */
#undef DEFINE_IMM_ENTRY
#define DEFINE_IMM_ENTRY(type, name, params, retval, retkind) \
    static type WINAPI IMMSTUB_##name params { IMM_RETURN_##retkind((type)retval); }
#include "immtable.h"

Imm32ApiTable gImmApiEntries = {
/* initialize by stubs */
#undef DEFINE_IMM_ENTRY
#define DEFINE_IMM_ENTRY(type, name, params, retval, retkind) \
    IMMSTUB_##name,
#include "immtable.h"
};

HRESULT
GetImmFileName(_Out_ LPWSTR lpBuffer,
               _In_ size_t cchBuffer)
{
    UINT length = GetSystemDirectoryW(lpBuffer, cchBuffer);
    if (length && length < cchBuffer)
    {
        StringCchCatW(lpBuffer, cchBuffer, L"\\");
        return StringCchCatW(lpBuffer, cchBuffer, L"imm32.dll");
    }
    return StringCchCopyW(lpBuffer, cchBuffer, L"imm32.dll");
}

/*
 * @unimplemented
 */
static BOOL IntInitializeImmEntryTable(VOID)
{
    WCHAR ImmFile[MAX_PATH];
    HMODULE imm32 = ghImm32;

    /* Check whether the IMM table has already been initialized */
    if (IMM_FN(ImmWINNLSEnableIME) != IMMSTUB_ImmWINNLSEnableIME)
        return TRUE;

    GetImmFileName(ImmFile, _countof(ImmFile));
    TRACE("File %S\n", ImmFile);

    /* If IMM32 is already loaded, use it without increasing reference count. */
    if (imm32 == NULL)
        imm32 = GetModuleHandleW(ImmFile);

    /*
     * Loading imm32.dll will call imm32!DllMain function.
     * imm32!DllMain calls User32InitializeImmEntryTable.
     * Thus, if imm32.dll was loaded, the table has been loaded.
     */
    if (imm32 == NULL)
    {
        imm32 = ghImm32 = LoadLibraryW(ImmFile);
        if (imm32 == NULL)
        {
            ERR("Did not load imm32.dll!\n");
            return FALSE;
        }
        return TRUE;
    }

/* load imm procedures */
#undef DEFINE_IMM_ENTRY
#define DEFINE_IMM_ENTRY(type, name, params, retval, retkind) \
    do { \
        FN_##name proc = (FN_##name)GetProcAddress(imm32, #name); \
        if (!proc) { \
            ERR("Could not load %s\n", #name); \
            return FALSE; \
        } \
        IMM_FN(name) = proc; \
    } while (0);
#include "immtable.h"

    return TRUE;
}

BOOL WINAPI InitializeImmEntryTable(VOID)
{
    bImmInitializing = TRUE;
    return IntInitializeImmEntryTable();
}

BOOL WINAPI User32InitializeImmEntryTable(DWORD magic)
{
    TRACE("Imm (%x)\n", magic);

    if (magic != IMM_INIT_MAGIC)
        return FALSE;

    /* Check whether the IMM table has already been initialized */
    if (IMM_FN(ImmWINNLSEnableIME) != IMMSTUB_ImmWINNLSEnableIME)
        return TRUE;

    IntInitializeImmEntryTable();

    if (ghImm32 == NULL && !bImmInitializing)
    {
        WCHAR ImmFile[MAX_PATH];
        GetImmFileName(ImmFile, _countof(ImmFile));
        ghImm32 = LoadLibraryW(ImmFile);
        if (ghImm32 == NULL)
        {
            ERR("Did not load imm32.dll!\n");
            return FALSE;
        }
    }

    return IMM_FN(ImmRegisterClient)(&gSharedInfo, ghImm32);
}

static BOOL User32CanSetImeWindowToImc(HIMC hIMC, HWND hImeWnd)
{
    PIMC pIMC = ValidateHandle(hIMC, TYPE_INPUTCONTEXT);
    return pIMC && (!pIMC->hImeWnd || pIMC->hImeWnd == hImeWnd || !ValidateHwnd(pIMC->hImeWnd));
}

static BOOL User32GetImeShowStatus(VOID)
{
    return (BOOL)NtUserCallNoParam(NOPARAM_ROUTINE_GETIMESHOWSTATUS);
}

static LRESULT
User32SendImeUIMessage(PIMEUI pimeui, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL unicode)
{
    LRESULT ret = 0;
    HWND hwndUI = pimeui->hwndUI;
    PWND pwnd, pwndUI;

    pwnd = pimeui->spwnd;
    pwndUI = ValidateHwnd(hwndUI);
    if (!pwnd || (pwnd->state & WNDS_DESTROYED) || (pwnd->state2 & WNDS2_INDESTROY) ||
        !pwndUI || (pwndUI->state & WNDS_DESTROYED) || (pwndUI->state2 & WNDS2_INDESTROY))
    {
        return 0;
    }

    InterlockedIncrement(&pimeui->nCntInIMEProc);

    if (unicode)
        ret = SendMessageW(hwndUI, uMsg, wParam, lParam);
    else
        ret = SendMessageA(hwndUI, uMsg, wParam, lParam);

    InterlockedDecrement(&pimeui->nCntInIMEProc);

    return ret;
}

static VOID User32NotifyOpenStatus(PIMEUI pimeui, HWND hwndIMC, BOOL bOpen)
{
    WPARAM wParam = (bOpen ? IMN_OPENSTATUSWINDOW : IMN_CLOSESTATUSWINDOW);

    pimeui->fShowStatus = bOpen;

    if (LOWORD(GetWin32ClientInfo()->dwExpWinVer) >= 0x400)
        SendMessageW(hwndIMC, WM_IME_NOTIFY, wParam, 0);
    else
        User32SendImeUIMessage(pimeui, WM_IME_NOTIFY, wParam, 0, TRUE);
}

static VOID User32SetImeWindowOfImc(HIMC hIMC, HWND hImeWnd)
{
    PIMC pIMC = ValidateHandle(hIMC, TYPE_INPUTCONTEXT);
    if (!pIMC || pIMC->hImeWnd == hImeWnd)
        return;

    NtUserUpdateInputContext(hIMC, UIC_IMEWINDOW, (ULONG_PTR)hImeWnd);
}

static VOID User32UpdateImcOfImeUI(PIMEUI pimeui, HIMC hNewIMC)
{
    HWND hImeWnd = UserHMGetHandle(pimeui->spwnd);
    HIMC hOldIMC = pimeui->hIMC;

    if (hNewIMC == hOldIMC)
        return;

    if (hOldIMC)
        User32SetImeWindowOfImc(hOldIMC, NULL);

    pimeui->hIMC = hNewIMC;

    if (hNewIMC)
        User32SetImeWindowOfImc(hNewIMC, hImeWnd);
}

static LRESULT ImeWnd_OnImeNotify(PIMEUI pimeui, WPARAM wParam, LPARAM lParam)
{
    LRESULT ret = 0;
    HIMC hIMC;
    LPINPUTCONTEXT pIC;
    HWND hwndUI, hwndIMC;

    switch (wParam)
    {
        case IMN_SETCONVERSIONMODE:
        case IMN_SETOPENSTATUS:
            hIMC = pimeui->hIMC;
            pIC = IMM_FN(ImmLockIMC)(hIMC);
            if (pIC)
            {
                hwndIMC = pimeui->hwndIMC;
                if (IsWindow(hwndIMC))
                {
                    NtUserNotifyIMEStatus(hwndIMC, pIC->fOpen, pIC->fdwConversion);
                }
                else
                {
                    // TODO:
                }

                IMM_FN(ImmUnlockIMC)(hIMC);
            }
            /* FALL THROUGH */
        default:
            ret = User32SendImeUIMessage(pimeui, WM_IME_NOTIFY, wParam, lParam, TRUE);
            break;

        case IMN_PRIVATE:
            hwndUI = pimeui->hwndUI;
            if (IsWindow(hwndUI))
                ret = SendMessageW(hwndUI, WM_IME_NOTIFY, wParam, lParam);
            break;
    }

    return ret;
}

static HWND User32CreateImeUIWindow(PIMEUI pimeui, HKL hKL)
{
    IMEINFOEX ImeInfoEx;
    PIMEDPI pImeDpi;
    WNDCLASSW wc;
    HWND hwndUI = NULL;
    CHAR szUIClass[32];
    PWND pwnd = pimeui->spwnd;

    if (!pwnd || !IMM_FN(ImmGetImeInfoEx)(&ImeInfoEx, ImeInfoExKeyboardLayout, &hKL))
        return NULL;

    pImeDpi = IMM_FN(ImmLockImeDpi)(hKL);
    if (!pImeDpi)
        return NULL;

    if (!GetClassInfoW(pImeDpi->hInst, ImeInfoEx.wszUIClass, &wc))
        goto Quit;

    if (ImeInfoEx.ImeInfo.fdwProperty & IME_PROP_UNICODE)
    {
        hwndUI = CreateWindowW(ImeInfoEx.wszUIClass, ImeInfoEx.wszUIClass, WS_POPUP | WS_DISABLED,
                               0, 0, 0, 0, UserHMGetHandle(pwnd), 0, wc.hInstance, NULL);
    }
    else
    {
        WideCharToMultiByte(CP_ACP, 0, ImeInfoEx.wszUIClass, -1,
                            szUIClass, _countof(szUIClass), NULL, NULL);
        szUIClass[_countof(szUIClass) - 1] = 0;

        hwndUI = CreateWindowA(szUIClass, szUIClass, WS_POPUP | WS_DISABLED,
                               0, 0, 0, 0, UserHMGetHandle(pwnd), 0, wc.hInstance, NULL);
    }

    if (hwndUI)
        NtUserSetWindowLong(hwndUI, IMMGWL_IMC, (LONG_PTR)pimeui->hIMC, FALSE);

Quit:
    IMM_FN(ImmUnlockImeDpi)(pImeDpi);
    return hwndUI;
}

static BOOL ImeWnd_OnCreate(PIMEUI pimeui, LPCREATESTRUCT lpCS)
{
    PWND pParentWnd, pWnd = pimeui->spwnd;
    HIMC hIMC = NULL;

    if (!pWnd || (pWnd->style & (WS_DISABLED | WS_POPUP)) != (WS_DISABLED | WS_POPUP))
        return FALSE;

    pParentWnd = ValidateHwnd(lpCS->hwndParent);
    if (pParentWnd)
    {
        hIMC = pParentWnd->hImc;
        if (hIMC && !User32CanSetImeWindowToImc(hIMC, UserHMGetHandle(pWnd)))
            hIMC = NULL;
    }

    User32UpdateImcOfImeUI(pimeui, hIMC);

    pimeui->fShowStatus = FALSE;
    pimeui->nCntInIMEProc = 0;
    pimeui->fActivate = FALSE;
    pimeui->fDestroy = FALSE;
    pimeui->hwndIMC = NULL;
    pimeui->hKL = GetWin32ClientInfo()->hKL;
    pimeui->fCtrlShowStatus = TRUE;

    IMM_FN(ImmLoadIME)(pimeui->hKL);

    pimeui->hwndUI = NULL;

    return TRUE;
}

static VOID User32DestroyImeUIWindow(PIMEUI pimeui)
{
    HWND hwndUI = pimeui->hwndUI;

    if (IsWindow(hwndUI))
    {
        pimeui->fDestroy = TRUE;
        NtUserDestroyWindow(hwndUI);
    }

    pimeui->fShowStatus = pimeui->fDestroy = FALSE;
    pimeui->hwndUI = NULL;
}

VOID ImeWnd_OnImeSelect(PIMEUI pimeui, WPARAM wParam, LPARAM lParam)
{
    HKL hKL;
    HWND hwndUI, hwndIMC = pimeui->hwndIMC;

    if (wParam)
    {
        pimeui->hKL = hKL = (HKL)lParam;
        pimeui->hwndUI = hwndUI = User32CreateImeUIWindow(pimeui, hKL);
        if (hwndUI)
            User32SendImeUIMessage(pimeui, WM_IME_SELECT, wParam, lParam, TRUE);

        if (User32GetImeShowStatus() && pimeui->fCtrlShowStatus)
        {
            if (!pimeui->fShowStatus && pimeui->fActivate && IsWindow(hwndIMC))
                User32NotifyOpenStatus(pimeui, hwndIMC, TRUE);
        }
    }
    else
    {
        if (pimeui->fShowStatus && pimeui->fActivate && IsWindow(hwndIMC))
            User32NotifyOpenStatus(pimeui, hwndIMC, FALSE);

        User32SendImeUIMessage(pimeui, WM_IME_SELECT, wParam, lParam, TRUE);
        User32DestroyImeUIWindow(pimeui);
        pimeui->hKL = NULL;
    }
}

LRESULT WINAPI ImeWndProc_common( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL unicode ) // ReactOS
{
    PWND pWnd;
    PIMEUI pimeui;

    pWnd = ValidateHwnd(hwnd);
    if (pWnd)
    {
       if (!pWnd->fnid)
       {
          if (msg != WM_NCCREATE)
          {
             if (unicode)
                return DefWindowProcW(hwnd, msg, wParam, lParam);
             return DefWindowProcA(hwnd, msg, wParam, lParam);
          }
          NtUserSetWindowFNID(hwnd, FNID_IME);
          pimeui = HeapAlloc( GetProcessHeap(), 0, sizeof(IMEUI) );
          pimeui->spwnd = pWnd;
          SetWindowLongPtrW(hwnd, 0, (LONG_PTR)pimeui);
       }
       else
       {
          if (pWnd->fnid != FNID_IME)
          {
             ERR("Wrong window class for Ime! fnId 0x%x\n",pWnd->fnid);
             return 0;
          }
          pimeui = ((PIMEWND)pWnd)->pimeui;
          if (pimeui == NULL)
          {
             ERR("Window is not set to IME!\n");
             return 0;
          }
       }
    }

    if (pimeui->nCntInIMEProc > 0)
    {
        switch (msg)
        {
            case WM_IME_CHAR:
            case WM_IME_COMPOSITIONFULL:
            case WM_IME_CONTROL:
            case WM_IME_NOTIFY:
            case WM_IME_REQUEST:
            case WM_IME_SELECT:
            case WM_IME_SETCONTEXT:
            case WM_IME_STARTCOMPOSITION:
            case WM_IME_COMPOSITION:
            case WM_IME_ENDCOMPOSITION:
                return 0;

            case WM_IME_SYSTEM:
                // TODO:
                return 0;

            default:
            {
                if (unicode)
                    return DefWindowProcW(hwnd, msg, wParam, lParam);
                return DefWindowProcA(hwnd, msg, wParam, lParam);
            }
        }
    }

    switch (msg)
    {
        case WM_CREATE:
            return (ImeWnd_OnCreate(pimeui, (LPCREATESTRUCT)lParam) ? 0 : -1);

        case WM_DESTROY:
            User32DestroyImeUIWindow(pimeui);
            break;

        case WM_NCDESTROY:
            HeapFree(GetProcessHeap(), 0, pimeui);
            SetWindowLongPtrW(hwnd, 0, 0);
            NtUserSetWindowFNID(hwnd, FNID_DESTROY);
            break;

        case WM_ERASEBKGND:
            return TRUE;

        case WM_PAINT:
            break;

        case WM_COPYDATA:
            // TODO:
            break;

        case WM_IME_STARTCOMPOSITION:
        case WM_IME_COMPOSITION:
        case WM_IME_ENDCOMPOSITION:
            return User32SendImeUIMessage(pimeui, msg, wParam, lParam, unicode);

        case WM_IME_CONTROL:
            // TODO:
            break;

        case WM_IME_NOTIFY:
            return ImeWnd_OnImeNotify(pimeui, wParam, lParam);

        case WM_IME_REQUEST:
            break;

        case WM_IME_SELECT:
            ImeWnd_OnImeSelect(pimeui, wParam, lParam);
            break;

        case WM_IME_SETCONTEXT:
            // TODO:
            break;

        case WM_IME_SYSTEM:
            // TODO:
            break;

        default:
        {
            if (unicode)
                return DefWindowProcW(hwnd, msg, wParam, lParam);
            return DefWindowProcA(hwnd, msg, wParam, lParam);
        }
    }

    return 0;
}

LRESULT WINAPI ImeWndProcA( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return ImeWndProc_common(hwnd, msg, wParam, lParam, FALSE);
}

LRESULT WINAPI ImeWndProcW( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return ImeWndProc_common(hwnd, msg, wParam, lParam, TRUE);
}

BOOL
WINAPI
UpdatePerUserImmEnabling(VOID)
{
  BOOL Ret = NtUserCallNoParam(NOPARAM_ROUTINE_UPDATEPERUSERIMMENABLING);
  if ( Ret )
  {
    if ( gpsi->dwSRVIFlags & SRVINFO_IMM32 )
    {
      HMODULE imm32 = GetModuleHandleW(L"imm32.dll");
      if ( !imm32 )
      {
        imm32 = LoadLibraryW(L"imm32.dll");
        if (!imm32)
        {
           ERR("UPUIE: Imm32 not installed!\n");
           Ret = FALSE;
        }
      }
    }
  }
  return Ret;
}

static const WCHAR imeW[] = {'I','M','E',0};

BOOL
WINAPI
RegisterIMEClass(VOID)
{
    WNDCLASSEXW WndClass;
    ATOM atom;

    ZeroMemory(&WndClass, sizeof(WndClass));

    WndClass.cbSize = sizeof(WndClass);
    WndClass.lpszClassName = imeW;
    WndClass.style = CS_GLOBALCLASS;
    WndClass.lpfnWndProc = ImeWndProcW;
    WndClass.cbWndExtra = sizeof(LONG_PTR);
    WndClass.hCursor = LoadCursorW(NULL, IDC_ARROW);

    atom = RegisterClassExWOWW( &WndClass,
                                 0,
                                 FNID_IME,
                                 0,
                                 FALSE);
    if (atom)
    {
       RegisterDefaultClasses |= ICLASS_TO_MASK(ICLS_IME);
       TRACE("Register IME Class!\n");
       return TRUE;
    }
    ERR("Failed to register IME Class!\n");
    return FALSE;
}

/*
 * @unimplemented
 */
BOOL WINAPI CliImmSetHotKey(DWORD dwID, UINT uModifiers, UINT uVirtualKey, HKL hKl)
{
  UNIMPLEMENTED;
  return FALSE;
}

/*
 * @implemented
 */
BOOL
WINAPI
IMPSetIMEW(HWND hwnd, LPIMEPROW ime)
{
    return IMM_FN(ImmIMPSetIMEW)(hwnd, ime);
}

/*
 * @implemented
 */
BOOL
WINAPI
IMPQueryIMEW(LPIMEPROW ime)
{
    return IMM_FN(ImmIMPQueryIMEW)(ime);
}

/*
 * @implemented
 */
BOOL
WINAPI
IMPGetIMEW(HWND hwnd, LPIMEPROW ime)
{
    return IMM_FN(ImmIMPGetIMEW)(hwnd, ime);
}

/*
 * @implemented
 */
BOOL
WINAPI
IMPSetIMEA(HWND hwnd, LPIMEPROA ime)
{
    return IMM_FN(ImmIMPSetIMEA)(hwnd, ime);
}

/*
 * @implemented
 */
BOOL
WINAPI
IMPQueryIMEA(LPIMEPROA ime)
{
    return IMM_FN(ImmIMPQueryIMEA)(ime);
}

/*
 * @implemented
 */
BOOL
WINAPI
IMPGetIMEA(HWND hwnd, LPIMEPROA ime)
{
    return IMM_FN(ImmIMPGetIMEA)(hwnd, ime);
}

/*
 * @implemented
 */
LRESULT
WINAPI
SendIMEMessageExW(HWND hwnd, LPARAM lParam)
{
    return IMM_FN(ImmSendIMEMessageExW)(hwnd, lParam);
}

/*
 * @implemented
 */
LRESULT
WINAPI
SendIMEMessageExA(HWND hwnd, LPARAM lParam)
{
    return IMM_FN(ImmSendIMEMessageExA)(hwnd, lParam);
}

/*
 * @implemented
 */
BOOL
WINAPI
WINNLSEnableIME(HWND hwnd, BOOL enable)
{
    return IMM_FN(ImmWINNLSEnableIME)(hwnd, enable);
}

/*
 * @implemented
 */
BOOL
WINAPI
WINNLSGetEnableStatus(HWND hwnd)
{
    return IMM_FN(ImmWINNLSGetEnableStatus)(hwnd);
}

/*
 * @implemented
 */
UINT
WINAPI
WINNLSGetIMEHotkey(HWND hwnd)
{
    return FALSE;
}
