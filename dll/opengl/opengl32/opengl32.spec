@ stub GlmfBeginGlsBlock
@ stub GlmfCloseMetaFile
@ stub GlmfEndGlsBlock
@ stub GlmfEndPlayback
@ stub GlmfInitPlayback
@ stub GlmfPlayGlsRecord
@ stdcall glAccum( long long )
@ stdcall glAlphaFunc( long long )
@ stdcall glAreTexturesResident( long ptr ptr )
@ stdcall glArrayElement( long )
@ stdcall glBegin( long )
@ stdcall glBindTexture( long long )
@ stdcall glBitmap( long long long long long long ptr )
@ stdcall glBlendFunc( long long )
@ stdcall glCallList( long )
@ stdcall glCallLists( long long ptr )
@ stdcall glClear( long )
@ stdcall glClearAccum( long long long long )
@ stdcall glClearColor( long long long long )
@ stdcall glClearDepth( double )
@ stdcall glClearIndex( long )
@ stdcall glClearStencil( long )
@ stdcall glClipPlane( long ptr )
@ stdcall glColor3b( long long long )
@ stdcall glColor3bv( ptr )
@ stdcall glColor3d( double double double )
@ stdcall glColor3dv( ptr )
@ stdcall glColor3f( long long long )
@ stdcall glColor3fv( ptr )
@ stdcall glColor3i( long long long )
@ stdcall glColor3iv( ptr )
@ stdcall glColor3s( long long long )
@ stdcall glColor3sv( ptr )
@ stdcall glColor3ub( long long long )
@ stdcall glColor3ubv( ptr )
@ stdcall glColor3ui( long long long )
@ stdcall glColor3uiv( ptr )
@ stdcall glColor3us( long long long )
@ stdcall glColor3usv( ptr )
@ stdcall glColor4b( long long long long )
@ stdcall glColor4bv( ptr )
@ stdcall glColor4d( double double double double )
@ stdcall glColor4dv( ptr )
@ stdcall glColor4f( long long long long )
@ stdcall glColor4fv( ptr )
@ stdcall glColor4i( long long long long )
@ stdcall glColor4iv( ptr )
@ stdcall glColor4s( long long long long )
@ stdcall glColor4sv( ptr )
@ stdcall glColor4ub( long long long long )
@ stdcall glColor4ubv( ptr )
@ stdcall glColor4ui( long long long long )
@ stdcall glColor4uiv( ptr )
@ stdcall glColor4us( long long long long )
@ stdcall glColor4usv( ptr )
@ stdcall glColorMask( long long long long )
@ stdcall glColorMaterial( long long )
@ stdcall glColorPointer( long long long ptr )
@ stdcall glCopyPixels( long long long long long )
@ stdcall glCopyTexImage1D( long long long long long long long )
@ stdcall glCopyTexImage2D( long long long long long long long long )
@ stdcall glCopyTexSubImage1D( long long long long long long )
@ stdcall glCopyTexSubImage2D( long long long long long long long long )
@ stdcall glCullFace( long )
@ stdcall glDebugEntry(long long)
@ stdcall glDeleteLists( long long )
@ stdcall glDeleteTextures( long ptr )
@ stdcall glDepthFunc( long )
@ stdcall glDepthMask( long )
@ stdcall glDepthRange( double double )
@ stdcall glDisable( long )
@ stdcall glDisableClientState( long )
@ stdcall glDrawArrays( long long long )
@ stdcall glDrawBuffer( long )
@ stdcall glDrawElements( long long long ptr )
@ stdcall glDrawPixels( long long long long ptr )
@ stdcall glEdgeFlag( long )
@ stdcall glEdgeFlagPointer( long ptr )
@ stdcall glEdgeFlagv( ptr )
@ stdcall glEnable( long )
@ stdcall glEnableClientState( long )
@ stdcall glEnd( )
@ stdcall glEndList( )
@ stdcall glEvalCoord1d( double )
@ stdcall glEvalCoord1dv( ptr )
@ stdcall glEvalCoord1f( long )
@ stdcall glEvalCoord1fv( ptr )
@ stdcall glEvalCoord2d( double double )
@ stdcall glEvalCoord2dv( ptr )
@ stdcall glEvalCoord2f( long long )
@ stdcall glEvalCoord2fv( ptr )
@ stdcall glEvalMesh1( long long long )
@ stdcall glEvalMesh2( long long long long long )
@ stdcall glEvalPoint1( long )
@ stdcall glEvalPoint2( long long )
@ stdcall glFeedbackBuffer( long long ptr )
@ stdcall glFinish( )
@ stdcall glFlush( )
@ stdcall glFogf( long long )
@ stdcall glFogfv( long ptr )
@ stdcall glFogi( long long )
@ stdcall glFogiv( long ptr )
@ stdcall glFrontFace( long )
@ stdcall glFrustum( double double double double double double )
@ stdcall glGenLists( long )
@ stdcall glGenTextures( long ptr )
@ stdcall glGetBooleanv( long ptr )
@ stdcall glGetClipPlane( long ptr )
@ stdcall glGetDoublev( long ptr )
@ stdcall glGetError( )
@ stdcall glGetFloatv( long ptr )
@ stdcall glGetIntegerv( long ptr )
@ stdcall glGetLightfv( long long ptr )
@ stdcall glGetLightiv( long long ptr )
@ stdcall glGetMapdv( long long ptr )
@ stdcall glGetMapfv( long long ptr )
@ stdcall glGetMapiv( long long ptr )
@ stdcall glGetMaterialfv( long long ptr )
@ stdcall glGetMaterialiv( long long ptr )
@ stdcall glGetPixelMapfv( long ptr )
@ stdcall glGetPixelMapuiv( long ptr )
@ stdcall glGetPixelMapusv( long ptr )
@ stdcall glGetPointerv( long ptr )
@ stdcall glGetPolygonStipple( ptr )
@ stdcall glGetString( long )
@ stdcall glGetTexEnvfv( long long ptr )
@ stdcall glGetTexEnviv( long long ptr )
@ stdcall glGetTexGendv( long long ptr )
@ stdcall glGetTexGenfv( long long ptr )
@ stdcall glGetTexGeniv( long long ptr )
@ stdcall glGetTexImage( long long long long ptr )
@ stdcall glGetTexLevelParameterfv( long long long ptr )
@ stdcall glGetTexLevelParameteriv( long long long ptr )
@ stdcall glGetTexParameterfv( long long ptr )
@ stdcall glGetTexParameteriv( long long ptr )
@ stdcall glHint( long long )
@ stdcall glIndexMask( long )
@ stdcall glIndexPointer( long long ptr )
@ stdcall glIndexd( double )
@ stdcall glIndexdv( ptr )
@ stdcall glIndexf( long )
@ stdcall glIndexfv( ptr )
@ stdcall glIndexi( long )
@ stdcall glIndexiv( ptr )
@ stdcall glIndexs( long )
@ stdcall glIndexsv( ptr )
@ stdcall glIndexub( long )
@ stdcall glIndexubv( ptr )
@ stdcall glInitNames( )
@ stdcall glInterleavedArrays( long long ptr )
@ stdcall glIsEnabled( long )
@ stdcall glIsList( long )
@ stdcall glIsTexture( long )
@ stdcall glLightModelf( long long )
@ stdcall glLightModelfv( long ptr )
@ stdcall glLightModeli( long long )
@ stdcall glLightModeliv( long ptr )
@ stdcall glLightf( long long long )
@ stdcall glLightfv( long long ptr )
@ stdcall glLighti( long long long )
@ stdcall glLightiv( long long ptr )
@ stdcall glLineStipple( long long )
@ stdcall glLineWidth( long )
@ stdcall glListBase( long )
@ stdcall glLoadIdentity( )
@ stdcall glLoadMatrixd( ptr )
@ stdcall glLoadMatrixf( ptr )
@ stdcall glLoadName( long )
@ stdcall glLogicOp( long )
@ stdcall glMap1d( long double double long long ptr )
@ stdcall glMap1f( long long long long long ptr )
@ stdcall glMap2d( long double double long long double double long long ptr )
@ stdcall glMap2f( long long long long long long long long long ptr )
@ stdcall glMapGrid1d( long double double )
@ stdcall glMapGrid1f( long long long )
@ stdcall glMapGrid2d( long double double long double double )
@ stdcall glMapGrid2f( long long long long long long )
@ stdcall glMaterialf( long long long )
@ stdcall glMaterialfv( long long ptr )
@ stdcall glMateriali( long long long )
@ stdcall glMaterialiv( long long ptr )
@ stdcall glMatrixMode( long )
@ stdcall glMultMatrixd( ptr )
@ stdcall glMultMatrixf( ptr )
@ stdcall glNewList( long long )
@ stdcall glNormal3b( long long long )
@ stdcall glNormal3bv( ptr )
@ stdcall glNormal3d( double double double )
@ stdcall glNormal3dv( ptr )
@ stdcall glNormal3f( long long long )
@ stdcall glNormal3fv( ptr )
@ stdcall glNormal3i( long long long )
@ stdcall glNormal3iv( ptr )
@ stdcall glNormal3s( long long long )
@ stdcall glNormal3sv( ptr )
@ stdcall glNormalPointer( long long ptr )
@ stdcall glOrtho( double double double double double double )
@ stdcall glPassThrough( long )
@ stdcall glPixelMapfv( long long ptr )
@ stdcall glPixelMapuiv( long long ptr )
@ stdcall glPixelMapusv( long long ptr )
@ stdcall glPixelStoref( long long )
@ stdcall glPixelStorei( long long )
@ stdcall glPixelTransferf( long long )
@ stdcall glPixelTransferi( long long )
@ stdcall glPixelZoom( long long )
@ stdcall glPointSize( long )
@ stdcall glPolygonMode( long long )
@ stdcall glPolygonOffset( long long )
@ stdcall glPolygonStipple( ptr )
@ stdcall glPopAttrib( )
@ stdcall glPopClientAttrib( )
@ stdcall glPopMatrix( )
@ stdcall glPopName( )
@ stdcall glPrioritizeTextures( long ptr ptr )
@ stdcall glPushAttrib( long )
@ stdcall glPushClientAttrib( long )
@ stdcall glPushMatrix( )
@ stdcall glPushName( long )
@ stdcall glRasterPos2d( double double )
@ stdcall glRasterPos2dv( ptr )
@ stdcall glRasterPos2f( long long )
@ stdcall glRasterPos2fv( ptr )
@ stdcall glRasterPos2i( long long )
@ stdcall glRasterPos2iv( ptr )
@ stdcall glRasterPos2s( long long )
@ stdcall glRasterPos2sv( ptr )
@ stdcall glRasterPos3d( double double double )
@ stdcall glRasterPos3dv( ptr )
@ stdcall glRasterPos3f( long long long )
@ stdcall glRasterPos3fv( ptr )
@ stdcall glRasterPos3i( long long long )
@ stdcall glRasterPos3iv( ptr )
@ stdcall glRasterPos3s( long long long )
@ stdcall glRasterPos3sv( ptr )
@ stdcall glRasterPos4d( double double double double )
@ stdcall glRasterPos4dv( ptr )
@ stdcall glRasterPos4f( long long long long )
@ stdcall glRasterPos4fv( ptr )
@ stdcall glRasterPos4i( long long long long )
@ stdcall glRasterPos4iv( ptr )
@ stdcall glRasterPos4s( long long long long )
@ stdcall glRasterPos4sv( ptr )
@ stdcall glReadBuffer( long )
@ stdcall glReadPixels( long long long long long long ptr )
@ stdcall glRectd( double double double double )
@ stdcall glRectdv( ptr ptr )
@ stdcall glRectf( long long long long )
@ stdcall glRectfv( ptr ptr )
@ stdcall glRecti( long long long long )
@ stdcall glRectiv( ptr ptr )
@ stdcall glRects( long long long long )
@ stdcall glRectsv( ptr ptr )
@ stdcall glRenderMode( long )
@ stdcall glRotated( double double double double )
@ stdcall glRotatef( long long long long )
@ stdcall glScaled( double double double )
@ stdcall glScalef( long long long )
@ stdcall glScissor( long long long long )
@ stdcall glSelectBuffer( long ptr )
@ stdcall glShadeModel( long )
@ stdcall glStencilFunc( long long long )
@ stdcall glStencilMask( long )
@ stdcall glStencilOp( long long long )
@ stdcall glTexCoord1d( double )
@ stdcall glTexCoord1dv( ptr )
@ stdcall glTexCoord1f( long )
@ stdcall glTexCoord1fv( ptr )
@ stdcall glTexCoord1i( long )
@ stdcall glTexCoord1iv( ptr )
@ stdcall glTexCoord1s( long )
@ stdcall glTexCoord1sv( ptr )
@ stdcall glTexCoord2d( double double )
@ stdcall glTexCoord2dv( ptr )
@ stdcall glTexCoord2f( long long )
@ stdcall glTexCoord2fv( ptr )
@ stdcall glTexCoord2i( long long )
@ stdcall glTexCoord2iv( ptr )
@ stdcall glTexCoord2s( long long )
@ stdcall glTexCoord2sv( ptr )
@ stdcall glTexCoord3d( double double double )
@ stdcall glTexCoord3dv( ptr )
@ stdcall glTexCoord3f( long long long )
@ stdcall glTexCoord3fv( ptr )
@ stdcall glTexCoord3i( long long long )
@ stdcall glTexCoord3iv( ptr )
@ stdcall glTexCoord3s( long long long )
@ stdcall glTexCoord3sv( ptr )
@ stdcall glTexCoord4d( double double double double )
@ stdcall glTexCoord4dv( ptr )
@ stdcall glTexCoord4f( long long long long )
@ stdcall glTexCoord4fv( ptr )
@ stdcall glTexCoord4i( long long long long )
@ stdcall glTexCoord4iv( ptr )
@ stdcall glTexCoord4s( long long long long )
@ stdcall glTexCoord4sv( ptr )
@ stdcall glTexCoordPointer( long long long ptr )
@ stdcall glTexEnvf( long long long )
@ stdcall glTexEnvfv( long long ptr )
@ stdcall glTexEnvi( long long long )
@ stdcall glTexEnviv( long long ptr )
@ stdcall glTexGend( long long double )
@ stdcall glTexGendv( long long ptr )
@ stdcall glTexGenf( long long long )
@ stdcall glTexGenfv( long long ptr )
@ stdcall glTexGeni( long long long )
@ stdcall glTexGeniv( long long ptr )
@ stdcall glTexImage1D( long long long long long long long ptr )
@ stdcall glTexImage2D( long long long long long long long long ptr )
@ stdcall glTexParameterf( long long long )
@ stdcall glTexParameterfv( long long ptr )
@ stdcall glTexParameteri( long long long )
@ stdcall glTexParameteriv( long long ptr )
@ stdcall glTexSubImage1D( long long long long long long ptr )
@ stdcall glTexSubImage2D( long long long long long long long long ptr )
@ stdcall glTranslated( double double double )
@ stdcall glTranslatef( long long long )
@ stdcall glVertex2d( double double )
@ stdcall glVertex2dv( ptr )
@ stdcall glVertex2f( long long )
@ stdcall glVertex2fv( ptr )
@ stdcall glVertex2i( long long )
@ stdcall glVertex2iv( ptr )
@ stdcall glVertex2s( long long )
@ stdcall glVertex2sv( ptr )
@ stdcall glVertex3d( double double double )
@ stdcall glVertex3dv( ptr )
@ stdcall glVertex3f( long long long )
@ stdcall glVertex3fv( ptr )
@ stdcall glVertex3i( long long long )
@ stdcall glVertex3iv( ptr )
@ stdcall glVertex3s( long long long )
@ stdcall glVertex3sv( ptr )
@ stdcall glVertex4d( double double double double )
@ stdcall glVertex4dv( ptr )
@ stdcall glVertex4f( long long long long )
@ stdcall glVertex4fv( ptr )
@ stdcall glVertex4i( long long long long )
@ stdcall glVertex4iv( ptr )
@ stdcall glVertex4s( long long long long )
@ stdcall glVertex4sv( ptr )
@ stdcall glVertexPointer( long long long ptr )
@ stdcall glViewport( long long long long )

@ stdcall wglChoosePixelFormat(long ptr)
@ stdcall wglCopyContext(long long long)
@ stdcall wglCreateContext(long)
@ stdcall wglCreateLayerContext(long long)
@ stdcall wglDeleteContext(long)
@ stdcall wglDescribeLayerPlane(long long long long ptr)
@ stdcall wglDescribePixelFormat(long long long ptr)
@ stdcall wglGetCurrentContext()
@ stdcall wglGetCurrentDC()
@ stdcall wglGetDefaultProcAddress(str)
@ stdcall wglGetLayerPaletteEntries(long long long long ptr)
@ stdcall wglGetPixelFormat(long)
@ stdcall wglGetProcAddress(str)
@ stdcall wglMakeCurrent(long long)
@ stdcall wglRealizeLayerPalette(long long long)
@ stdcall wglSetLayerPaletteEntries(long long long long ptr)
@ stdcall wglSetPixelFormat(long long ptr)
@ stdcall wglShareLists(long long)
@ stdcall wglSwapBuffers(long)
@ stdcall wglSwapLayerBuffers(long long)
@ stdcall wglSwapMultipleBuffers(long ptr)
@ stdcall wglUseFontBitmapsA(long long long long)
@ stdcall wglUseFontBitmapsW(long long long long)
@ stdcall wglUseFontOutlinesA(long long long long long long long ptr)
@ stdcall wglUseFontOutlinesW(long long long long long long long ptr)
