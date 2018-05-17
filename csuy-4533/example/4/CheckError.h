//////////////////////////////////////////////////////////////////////////////
//
//  --- CheckError.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __CHECKERROR_H__
#define __CHECKERROR_H__

#include <stdio.h>

#ifdef __APPLE__
#  include <OpenGL/gl3.h>
#else
#  include <GL/gl.h>
#endif

//----------------------------------------------------------------------------

static const char*
ErrorString( GLenum error )
{
    const char*  msg;
    switch( error ) {
#define Case( Token )  case Token: msg = #Token; break;
	Case( GL_NO_ERROR );
	Case( GL_INVALID_VALUE );
	Case( GL_INVALID_ENUM );
	Case( GL_INVALID_OPERATION );
#ifndef __gl3_h_ // In OpenGL 3.2 core profile, GL_STACK_OVERFLOW and GL_STACK_UNDERFLOW are
                 // Not defined and thus the following 2 cases must be bypassed.
                 // So we check the two cases below only when it's NOT OpenGL 3.2 core profile,
	         // i.e., only when "__gl3_h_" is not defined.
	Case( GL_STACK_OVERFLOW );
	Case( GL_STACK_UNDERFLOW );
#endif
	Case( GL_OUT_OF_MEMORY );
#undef  Case	
    }

    return msg;
}

//----------------------------------------------------------------------------

static void
_CheckError( const char* file, int line )
{
    GLenum  error = glGetError();

    do {
	fprintf( stderr, "[%s:%d] %s\n", file, line, ErrorString(error) );
    } while ((error = glGetError()) != GL_NO_ERROR );
	
}

//----------------------------------------------------------------------------

#define CheckError()  _CheckError( __FILE__, __LINE__ )

//----------------------------------------------------------------------------

#endif // !__CHECKERROR_H__
