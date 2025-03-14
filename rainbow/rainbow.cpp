/**************************
 * Includes
 *
 **************************/
//#define NOMINMAX

#define QUICKSTEP 1
//#define STEPFAST 1

// some constants
#define MOVEFORCE 5000
#define MOUSESENSE 0.1
#define VK_W 87
#define VK_S 83
#define KEY_A 97
#define KEY_D 100
#define KEY_M 109
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_5 53
#define LENGTH 3.5		// chassis length
#define WIDTH 2.5		// chassis width
#define HEIGHT 1.0		// chassis height
#define RADIUS 0.5		// wheel radius
#define STARTZ 1.0		// starting height of chassis
#define CMASS 1			// chassis mass
#define WMASS 1			// wheel mass
#define COMOFFSET -5		// center of mass offset
#define WALLMASS 1		// wall box mass
#define MECHMASS 50
#define BALLMASS 5		// ball mass
#define FMAX 25			// car engine fmax
#define ROWS 1			// rows of cars
#define COLS 1			// columns of cars
#define ITERS 10		// number of iterations
#define WBOXSIZE 1.0		// size of wall boxes
#define WALLWIDTH 1		// width of wall
#define WALLHEIGHT 1		// height of wall
#define DISABLE_THRESHOLD 0.0005	// maximum velocity (squared) a body can have and be disabled
#define DISABLE_STEPS 10	// number of steps a box has to have been disable-able before it will be disabled
#define CANNON_X -10		// x position of cannon
#define CANNON_Y 5		// y position of cannon
#define CANNON_BALL_MASS 25	// mass of the cannon ball
#define CANNON_BALL_RADIUS 0.6
#define STEPMAX 200
#define VELMIN 0.5
#define WALKSPEED 2.5f

#include <windows.h>
#include <gl/glew.h>//
#include <gl/glext.h>
#include <gl/gl.h>
//#include <glut.h>
#include <ode/ode.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <process.h>
#include <stdarg.h>							// Header File For Variable Argument Routines
#include <vector.h>
#include "mesh.h"
#include "mech.h"

#include "SceneNode.h"
//#include "light.h"
#include "constant.h"
#include "interaction.h"
#include "playerglobal.h"
#include "unt3.h"




#include <olectl.h>														// Header File For The OLE Controls Library	(Used In BuildTexture)
#include <math.h>														// Header File For The Math Library			(Used In BuildTexture)


#include "math\all.h"
#include "math\matrix.h"
//#include "NxPhysics.h"
//#include "PhysXLoader.h"
//#include "NxCooking.h"
//#include "Extensions.h"
using namespace std;



#define GL_ARRAY_BUFFER_ARB 0x8892
#define GL_STATIC_DRAW_ARB 0x88E4
typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);

PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;					// VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;					// VBO Bind Procedure
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;					// VBO Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;				// VBO Deletion Procedure

 PFNGLGETATTRIBLOCATIONARBPROC  glGetAttribLocationARB;
 PFNGLVERTEXATTRIB3FARBPROC glVertexAttrib3fARB;

 PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;
 PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB ;
 PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;

//#include "Extensions.h"

#define GL_TEXTURE_WRAP_R	0x8072

// GL_ARB_edge_clamp definitions

#define GL_CLAMP_TO_EDGE                  0x812F

// GL_ARB_texture_cube_map definitions

#define GL_NORMAL_MAP    0x8511
#define GL_REFLECTION_MAP    0x8512

#define GL_TEXTURE_CUBE_MAP    0x8513

#define GL_TEXTURE_BINDING_CUBE_MAP    0x8514

#define GL_TEXTURE_CUBE_MAP_POSITIVE_X     0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X     0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y     0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y     0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z     0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z     0x851A

#define GL_PROXY_TEXTURE_CUBE_MAP    0x851B

#define GL_MAX_CUBE_MAP_TEXTURE_SIZE    0x851C

// GL_ARB_texture_env_combine definitions

#define GL_COMBINE                                     0x8570

#define GL_COMBINE_RGB                                 0x8571
#define GL_COMBINE_ALPHA                               0x8572
#define GL_SOURCE0_RGB                                 0x8580
#define GL_SOURCE1_RGB                                 0x8581
#define GL_SOURCE2_RGB                                 0x8582
#define GL_SOURCE0_ALPHA                               0x8588
#define GL_SOURCE1_ALPHA                               0x8589
#define GL_SOURCE2_ALPHA                               0x858A
#define GL_OPERAND0_RGB                                0x8590
#define GL_OPERAND1_RGB                                0x8591
#define GL_OPERAND2_RGB                                0x8592
#define GL_OPERAND0_ALPHA                              0x8598
#define GL_OPERAND1_ALPHA                              0x8599
#define GL_OPERAND2_ALPHA                              0x859A
#define GL_RGB_SCALE                                   0x8573

#define GL_ADD_SIGNED                                  0x8574
#define GL_INTERPOLATE                                 0x8575
#define GL_SUBTRACT                                    0x84E7

#define GL_CONSTANT                                    0x8576
#define GL_PRIMARY_COLOR                               0x8577
#define GL_PREVIOUS                                    0x8578

// GL_ARB_texture_env_dot3 definitons

#define GL_DOT3_RGB                                    0x86AE
#define GL_DOT3_RGBA                                   0x86AF

// GL_ARB_multitexture definitions

#define GL_TEXTURE0			0x84C0
#define GL_TEXTURE1			0x84C1
#define GL_TEXTURE2			0x84C2
#define GL_TEXTURE3			0x84C3
#define GL_TEXTURE4			0x84C4
#define GL_TEXTURE5			0x84C5
#define GL_TEXTURE6			0x84C6
#define GL_TEXTURE7			0x84C7
#define GL_TEXTURE8			0x84C8
#define GL_TEXTURE9			0x84C9
#define GL_TEXTURE10		0x84CA
#define GL_TEXTURE11		0x84CB
#define GL_TEXTURE12		0x84CC
#define GL_TEXTURE13		0x84CD
#define GL_TEXTURE14		0x84CE
#define GL_TEXTURE15		0x84CF
#define GL_TEXTURE16		0x84D0
#define GL_TEXTURE17		0x84D1
#define GL_TEXTURE18		0x84D2
#define GL_TEXTURE19		0x84D3
#define GL_TEXTURE20		0x84D4
#define GL_TEXTURE21		0x84D5
#define GL_TEXTURE22		0x84D6
#define GL_TEXTURE23		0x84D7
#define GL_TEXTURE24		0x84D8
#define GL_TEXTURE25		0x84D9
#define GL_TEXTURE26		0x84DA
#define GL_TEXTURE27		0x84DB
#define GL_TEXTURE28		0x84DC
#define GL_TEXTURE29		0x84DD
#define GL_TEXTURE30		0x84DE
#define GL_TEXTURE31		0x84DF

#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1
#define GL_MAX_TEXTURE_UNITS              0x84E2

//typedef void (APIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVPROC) (GLenum target, const GLshort *v);





void SetUp_GL_ARB_multitexture();

/*
PFNGLACTIVETEXTUREPROC				glActiveTexture		= NULL;
*/PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture	= NULL;
PFNGLMULTITEXCOORD1DPROC			glMultiTexCoord1d	= NULL;
PFNGLMULTITEXCOORD1DVPROC			glMultiTexCoord1dv	= NULL;
PFNGLMULTITEXCOORD1FPROC			glMultiTexCoord1f	= NULL;
PFNGLMULTITEXCOORD1FVPROC			glMultiTexCoord1fv		= NULL;
PFNGLMULTITEXCOORD1IPROC			glMultiTexCoord1i	= NULL;
PFNGLMULTITEXCOORD1IVPROC			glMultiTexCoord1iv	= NULL;
PFNGLMULTITEXCOORD1SPROC			glMultiTexCoord1s	= NULL;
PFNGLMULTITEXCOORD1SVPROC			glMultiTexCoord1sv		= NULL;
PFNGLMULTITEXCOORD2DPROC			glMultiTexCoord2d	= NULL;
PFNGLMULTITEXCOORD2DVPROC			glMultiTexCoord2dv	= NULL;
PFNGLMULTITEXCOORD2FPROC			glMultiTexCoord2f		= NULL;
PFNGLMULTITEXCOORD2FVPROC			glMultiTexCoord2fv		= NULL;
PFNGLMULTITEXCOORD2IPROC			glMultiTexCoord2i		= NULL;
PFNGLMULTITEXCOORD2IVPROC			glMultiTexCoord2iv	= NULL;
PFNGLMULTITEXCOORD2SPROC			glMultiTexCoord2s	= NULL;
PFNGLMULTITEXCOORD2SVPROC			glMultiTexCoord2sv	= NULL;
PFNGLMULTITEXCOORD3DPROC			glMultiTexCoord3d	= NULL;
PFNGLMULTITEXCOORD3DVPROC			glMultiTexCoord3dv	= NULL;
PFNGLMULTITEXCOORD3FPROC			glMultiTexCoord3f	= NULL;
PFNGLMULTITEXCOORD3FVPROC			glMultiTexCoord3fv	= NULL;
PFNGLMULTITEXCOORD3IPROC			glMultiTexCoord3i	= NULL;
PFNGLMULTITEXCOORD3IVPROC			glMultiTexCoord3iv		= NULL;
PFNGLMULTITEXCOORD3SPROC			glMultiTexCoord3s		= NULL;
PFNGLMULTITEXCOORD3SVPROC			glMultiTexCoord3sv		= NULL;
PFNGLMULTITEXCOORD4DPROC			glMultiTexCoord4d		= NULL;
PFNGLMULTITEXCOORD4DVPROC			glMultiTexCoord4dv	= NULL;
PFNGLMULTITEXCOORD4FPROC			glMultiTexCoord4f		= NULL;
PFNGLMULTITEXCOORD4FVPROC			glMultiTexCoord4fv		= NULL;
PFNGLMULTITEXCOORD4IPROC			glMultiTexCoord4i		= NULL;
PFNGLMULTITEXCOORD4IVPROC			glMultiTexCoord4iv	= NULL;
PFNGLMULTITEXCOORD4SPROC			glMultiTexCoord4s		= NULL;
PFNGLMULTITEXCOORD4SVPROC			glMultiTexCoord4sv		= NULL;

void SetUp_GL_ARB_multitexture()
{
	//glActiveTexture = (PFNGLACTIVETEXTUREPROC)
	//			wglGetProcAddress("glActiveTextureARB");
	glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)
				wglGetProcAddress("glClientActiveTextureARB");

	glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)
				wglGetProcAddress("glMultiTexCoord1dARB");
	glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)
				wglGetProcAddress("glMultiTexCoord1dvARB");
	glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)
				wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)
				wglGetProcAddress("glMultiTexCoord1fvARB");
	glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)
				wglGetProcAddress("glMultiTexCoord1iARB");
	glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)
				wglGetProcAddress("glMultiTexCoord1ivARB");
	glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)
				wglGetProcAddress("glMultiTexCoord1sARB");
	glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)
				wglGetProcAddress("glMultiTexCoord1svARB");

	glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)
				wglGetProcAddress("glMultiTexCoord2dARB");
	glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)
				wglGetProcAddress("glMultiTexCoord2dvARB");
	glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)
				wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)
				wglGetProcAddress("glMultiTexCoord2fvARB");
	glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)
				wglGetProcAddress("glMultiTexCoord2iARB");
	glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)
				wglGetProcAddress("glMultiTexCoord2ivARB");
	glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)
				wglGetProcAddress("glMultiTexCoord2sARB");
	glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)
				wglGetProcAddress("glMultiTexCoord2svARB");

	glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)
				wglGetProcAddress("glMultiTexCoord3dARB");
	glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)
				wglGetProcAddress("glMultiTexCoord3dvARB");
	glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)
				wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)
				wglGetProcAddress("glMultiTexCoord3fvARB");
	glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)
				wglGetProcAddress("glMultiTexCoord3iARB");
	glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)
				wglGetProcAddress("glMultiTexCoord3ivARB");
	glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)
				wglGetProcAddress("glMultiTexCoord3sARB");
	glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)
				wglGetProcAddress("glMultiTexCoord3svARB");

	glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)
				wglGetProcAddress("glMultiTexCoord4dARB");
	glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)
				wglGetProcAddress("glMultiTexCoord4dvARB");
	glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)
				wglGetProcAddress("glMultiTexCoord4fARB");
	glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)
				wglGetProcAddress("glMultiTexCoord4fvARB");
	glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)
				wglGetProcAddress("glMultiTexCoord4iARB");
	glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)
				wglGetProcAddress("glMultiTexCoord4ivARB");
	glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)
				wglGetProcAddress("glMultiTexCoord4sARB");
	glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)
				wglGetProcAddress("glMultiTexCoord4svARB");
}


GLvoid BuildFont(GLvoid);


template <class T>
bool from_string(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

void Thread( void* pParams )
  {
      int count = 0;


      while(1)
      {

      }
  }


//vector <Node*> nodeArray;
BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName);

dGeomID geomGlob;

dBodyID joined1;
dBodyID joined2;

int jointID1;
int jointID2;

int jointCreateType;

bool mouseToggle;
bool pseudoMutex;
bool leftDown;

int disableSteps[2000];
bool disable[2000];

static dGeomID ground;
static dGeomID ceiling;
float tVertexArray [kvertCount][3];

int GenNormalizationCubeMap(unsigned int size, GLuint &texid)
{
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texid);

	unsigned char* data = new unsigned char[size*size*3];

	float offset = 0.5f;
	float halfSize = size * 0.5f;
	vec3 temp;
	unsigned int bytePtr = 0;

	for(unsigned int j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp[0] = halfSize;
			temp[1] = (j+offset-halfSize);
			temp[2] = -(i+offset-halfSize);
			scale_to_01(temp);

			data[bytePtr] = (unsigned char)(temp[0] * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp[1] * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp[2] * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(int j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp[0] = -halfSize;
			temp[1] = (j+offset-halfSize);
			temp[2] = (i+offset-halfSize);
			scale_to_01(temp);

			data[bytePtr] = (unsigned char)(temp[0] * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp[1] * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp[2] * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(int j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp[0] = i+offset-halfSize;
			temp[1] = -halfSize;
			temp[2] = j+offset-halfSize;
			scale_to_01(temp);

			data[bytePtr] = (unsigned char)(temp[0] * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp[1] * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp[2] * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(int j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp[0] = i+offset-halfSize;
			temp[1] = halfSize;
			temp[2] = -(j+offset-halfSize);
			scale_to_01(temp);

			data[bytePtr] = (unsigned char)(temp[0] * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp[1] * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp[2] * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(int j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp[0] = i+offset-halfSize;
			temp[1] = (j+offset-halfSize);
			temp[2] = halfSize;
			scale_to_01(temp);

			data[bytePtr] = (unsigned char)(temp[0] * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp[1] * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp[2] * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	bytePtr = 0;
	for(int j=0; j<size; j++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			temp[0] = -(i+offset-halfSize);
			temp[1] = (j+offset-halfSize);
			temp[2] = -halfSize;
			scale_to_01(temp);

			data[bytePtr] = (unsigned char)(temp[0] * 255.0f);
			data[bytePtr+1] = (unsigned char)(temp[1] * 255.0f);
			data[bytePtr+2] = (unsigned char)(temp[2] * 255.0f);

			bytePtr+=3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			0, GL_RGB8, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete [] data;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return true;
}

int BuildTexture(char *szPathName, GLuint &texid)						// Load Image And Convert To A Texture
{
	HDC			hdcTemp;												// The DC To Hold Our Bitmap
	HBITMAP		hbmpTemp;												// Holds The Bitmap Temporarily
	IPicture	*pPicture;												// IPicture Interface
	OLECHAR		wszPath[MAX_PATH+1];									// Full Path To Picture (WCHAR)
	char		szPath[MAX_PATH+1];										// Full Path To Picture
	long		lWidth;													// Width In Logical Units
	long		lHeight;												// Height In Logical Units
	long		lWidthPixels;											// Width In Pixels
	long		lHeightPixels;											// Height In Pixels
	GLint		glMaxTexDim ;											// Holds Maximum Texture Size

	if (strstr(szPathName, "http://"))									// If PathName Contains http:// Then...
	{
		strcpy(szPath, szPathName);										// Append The PathName To szPath
	}
	else																// Otherwise... We Are Loading From A File
	{
		GetCurrentDirectory(MAX_PATH, szPath);							// Get Our Working Directory
		strcat(szPath, "\\");											// Append "\" After The Working Directory
		strcat(szPath, szPathName);										// Append The PathName
	}

	MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);		// Convert From ASCII To Unicode
	HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);

	if(FAILED(hr))														// If Loading Failed
		return FALSE;													// Return False

	hdcTemp = CreateCompatibleDC(GetDC(0));								// Create The Windows Compatible Device Context
	if(!hdcTemp)														// Did Creation Fail?
	{
		pPicture->Release();											// Decrements IPicture Reference Count
		return FALSE;													// Return False (Failure)
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);					// Get Maximum Texture Size Supported

	pPicture->get_Width(&lWidth);										// Get IPicture Width (Convert To Pixels)
	lWidthPixels	= MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
	pPicture->get_Height(&lHeight);										// Get IPicture Height (Convert To Pixels)
	lHeightPixels	= MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

	// Resize Image To Closest Power Of Two
	if (lWidthPixels <= glMaxTexDim) // Is Image Width Less Than Or Equal To Cards Limit
		lWidthPixels = 1 << (int)floor((log((double)lWidthPixels)/log(2.0f)) + 0.5f);
	else  // Otherwise  Set Width To "Max Power Of Two" That The Card Can Handle
		lWidthPixels = glMaxTexDim;

	if (lHeightPixels <= glMaxTexDim) // Is Image Height Greater Than Cards Limit
		lHeightPixels = 1 << (int)floor((log((double)lHeightPixels)/log(2.0f)) + 0.5f);
	else  // Otherwise  Set Height To "Max Power Of Two" That The Card Can Handle
		lHeightPixels = glMaxTexDim;

	//	Create A Temporary Bitmap
	BITMAPINFO	bi = {0};												// The Type Of Bitmap We Request
	DWORD		*pBits = 0;												// Pointer To The Bitmap Bits

	bi.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);				// Set Structure Size
	bi.bmiHeader.biBitCount		= 32;									// 32 Bit
	bi.bmiHeader.biWidth		= lWidthPixels;							// Power Of Two Width
	bi.bmiHeader.biHeight		= lHeightPixels;						// Make Image Top Up (Positive Y-Axis)
	bi.bmiHeader.biCompression	= BI_RGB;								// RGB Encoding
	bi.bmiHeader.biPlanes		= 1;									// 1 Bitplane

	//	Creating A Bitmap This Way Allows Us To Specify Color Depth And Gives Us Imediate Access To The Bits
	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);

	if(!hbmpTemp)														// Did Creation Fail?
	{
		DeleteDC(hdcTemp);												// Delete The Device Context
		pPicture->Release();											// Decrements IPicture Reference Count
		return FALSE;													// Return False (Failure)
	}

	SelectObject(hdcTemp, hbmpTemp);									// Select Handle To Our Temp DC And Our Temp Bitmap Object

	// Render The IPicture On To The Bitmap
	pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);

	// Convert From BGR To RGB Format And Add An Alpha Value Of 255
	for(long i = 0; i < lWidthPixels * lHeightPixels; i++)				// Loop Through All Of The Pixels
	{
		BYTE* pPixel	= (BYTE*)(&pBits[i]);							// Grab The Current Pixel
		BYTE  temp		= pPixel[0];									// Store 1st Color In Temp Variable (Blue)
		pPixel[0]		= pPixel[2];									// Move Red Value To Correct Position (1st)
		pPixel[2]		= temp;											// Move Temp Value To Correct Blue Position (3rd)

		// This Will Make Any Black Pixels, Completely Transparent		(You Can Hardcode The Value If You Wish)
		if ((pPixel[0]==0) && (pPixel[1]==0) && (pPixel[2]==0))			// Is Pixel Completely Black
			pPixel[3]	=   0;											// Set The Alpha Value To 0
		else															// Otherwise
			pPixel[3]	= 255;											// Set The Alpha Value To 255
	}

	glGenTextures(1, &texid);											// Create The Texture

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid);								// Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);		// (Modify This For The Type Of Filtering You Want)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     // (Modify This For The Type Of Filtering You Want)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidthPixels, lHeightPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);	// (Modify This If You Want Mipmaps)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, lWidthPixels, lHeightPixels, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

	DeleteObject(hbmpTemp);												// Delete The Object
	DeleteDC(hdcTemp);													// Delete The Device Context

	pPicture->Release();												// Decrements IPicture Reference Count

	return TRUE;														// Return True (All Good)
}

mesh model;
mesh modelArray [100];
int modelArrayIndex;
string aname;

dJointID meshJoint [40000];

    float VertexArray [40000][3];
    float NormalArray [40000][3];
    float TextureArray[40000][2];
    int triangles [10000][3];
    float tangent[40000][3];
    float binormal[40000][3];
    int quads [10000][4];
    int vertCount;
    int normCount;
    int triCount;
    int quadCount;
    unsigned int VBOVertices;
    unsigned int VBONormals;
    unsigned int VBOTexCoords;
    unsigned int EBOQuads;
    unsigned int EBOtris;

    GLuint	base;				// Base Display List For The Font Set
    bool	keys[256];			// Array Used For The Keyboard Routine

    HDC			nhDC=NULL;		// Private GDI Device Context
    HGLRC		nhRC=NULL;		// Permanent Rendering Context
    HWND		hWnd=NULL;		// Holds Our Window Handle
    HINSTANCE	hInstance;		// Holds The Instance Of The Application


Mech *player;
//unsigned long mm_timer_start;
void createMech (Mech *PlayerMech);
void addBlockMech (Mech *PlayerMech);
void writeScene(Mech *play);
void importScene(Mech *play);


float xColRot;
float yColRot;
float zColRot;

float colPoint [5000][3];
int pointNum;


GLuint v,f,f2,p,p_metal,v_metal,f_metal,v_shadow,f_shadow,p_shadow;

GLuint vertexPrograms[100];
GLuint fragmentPrograms[100];
GLuint shaderPrograms[100];

GLuint testVertexProgram;
GLuint testFragmentProgram;
GLuint testShaderProgram;

int shaderIndex;
char shaderNames[3][100];
char modelNames[3][100];
char textureNames[3][100];

GLint loc1,loc2,loc3,loc4,posloc,posloc2,texloc,texloc2,occl,texloc_metal,texloc2_metal,loc1_metal,posloc_metal;
GLint gunBurst;
GLuint BMapTangent;  //Allow passage of a tangent
GLuint BMapBinormal;  //Allow passage of a binormal

string diagnosticString;

float lpos[3];
float lOffset;
int mouseDelX;
int mouseDelY;
int mouseRotX;
int mouseRotY;
bool mouseMove;
float up;
float heading;
float xpos;
float zpos;
float ypos;
float burstValue;
bool persp;
int key;
const dReal * rotmat;
const dReal * g;
dBox *wall_boxes[5000];
dBody *wall_bodies[5000];
dQuaternion quat;
dGeomID selectRay;
int selectIndex;
float contactPos[3];

float XProd;
dFixedJoint *handJoint;
dBody *hand;
dBox *handbox;

dBody *playerbody;
dBox *playerbox;

mesh cryoRoom;
mesh panel;
mesh door;
mesh door2;
mesh grate;
mesh chamfloor;
mesh port;
mesh playerModel;
mesh shotModel;

struct projectile
{
    dBodyID body;
    dGeomID geom;
};

vector <projectile *> playerShots;

Transform * form1;
Transform * form2;
GLfloat LightP [4];

float rate;
float cyldiff;

DWORD  start,end;

int frmCnt;
int FPS;
float objXrot;
float objYrot;

float playerRot;

GLYPHMETRICSFLOAT gmf[256];	// Storage For Information About Our Outline Font Characters

char keyInputBuffer[20];
int inputBufferCursor;
bool inputDone;

float camPos[4] = {0.0,1.0,0.0};

const float piover180 = 0.0174532925f;

GLvoid BuildFont(char *fontName)								// Build Our Bitmap Font
{

	HFONT	font;										// Windows Font ID

	base = glGenLists(256);								// Storage For 256 Characters

	font = CreateFont(	0,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						xpos,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						fontName);				        // Font Name

	SelectObject(nhDC, font);							// Selects The Font We Created

	wglUseFontOutlines(	nhDC,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						base,							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.1f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						gmf);							// Address Of Buffer To Recieve Data
}

GLvoid KillFont(GLvoid)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	/*char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(10, GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits*/
	float		length=0;								// Used To Find The Length Of The Text
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	for (unsigned int loop=0;loop<(strlen(text));loop++)	// Loop To Find Text Length
	{
		length+=gmf[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
	}

	//glDisable(GL_LIGHTING);
	//glTranslatef(0,0.0f,0.0f);					// Center Our Text On The Screen

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();
	glEnable(GL_LIGHTING);								// Pops The Display List Bits
}

GLuint	texture[1000];											// Storage For 1 Texture
char textName [3][1000];
int textIndex;

char *textFileRead(char *fn) {


	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {

      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

int textFileWrite(char *fn, char *s) {

	FILE *fp;
	int status = 0;

	if (fn != NULL) {
		fp = fopen(fn,"w");

		if (fp != NULL) {

			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
}



void setShaders() {

	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	char *vs_metal = NULL,*fs_metal = NULL,*fs2_metal = NULL;

	char *vs_shadow = NULL,*fs_shadow = NULL,*fs2_shadow = NULL;

	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

const int shadertype = 5;

switch(shadertype)
{
case 0:
	vs = textFileRead("parallax_BM_GLOSSMAP.vert");
	fs = textFileRead("parallax_BM_GLOSSMAP.frag");
	break;
case 1:
    vs = textFileRead("toon.vert");
	fs = textFileRead("toon.frag");
	break;
case 2:
    vs = textFileRead("pho.vert");
	fs = textFileRead("pho.frag");
	break;
case 3:
    vs = textFileRead("polkadot3d.vert");
	fs = textFileRead("polkadot3d.frag");
	break;
case 4:
    vs = textFileRead("AMB.vert");
	fs = textFileRead("AMB.frag");
	break;
case 5:
    vs = textFileRead("metal.vert");
	fs = textFileRead("techwar.frag");
	break;
}
	const char * ff = fs;
	const char * ff2 = fs2;
	const char * vv = vs;

	glShaderSourceARB(v, 1, &vv,NULL);
	glShaderSourceARB(f, 1, &ff,NULL);
	//glShaderSourceARB(f2, 1, &ff2,NULL);

	free(vs);free(fs);

	glCompileShaderARB(v);
	glCompileShaderARB(f);
	//glCompileShaderARB(f2);

	p = glCreateProgramObjectARB();
	glAttachObjectARB(p,v);
	glAttachObjectARB(p,f);
	//glAttachObjectARB(p,f2);

	glLinkProgramARB(p);

//metal shader//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
v_metal = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f_metal = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

const int shadertype2 = 3;

switch(shadertype2)
{
case 0:
	vs_metal = textFileRead("parallax_BM_GLOSSMAP.vert");
	fs_metal = textFileRead("parallax_BM_GLOSSMAP.frag");
	break;
case 1:
    vs_metal = textFileRead("toon.vert");
	fs_metal = textFileRead("toon.frag");
	break;
case 2:
    vs_metal = textFileRead("pho.vert");
	fs_metal = textFileRead("pho.frag");
	break;
case 3:
    vs_metal = textFileRead("metal.vert");
	fs_metal = textFileRead("metal.frag");
	break;
case 4:
    vs_metal = textFileRead("AMB.vert");
	fs_metal = textFileRead("AMB.frag");
	break;
}
	const char * ff_metal = fs_metal;
	const char * ff2_metal = fs2_metal;
	const char * vv_metal = vs_metal;

	glShaderSourceARB(v_metal, 1, &vv_metal,NULL);
	glShaderSourceARB(f_metal, 1, &ff_metal,NULL);
	//glShaderSourceARB(f2, 1, &ff2,NULL);

	free(vs_metal);free(fs_metal);

	glCompileShaderARB(v_metal);
	glCompileShaderARB(f_metal);
	//glCompileShaderARB(f2);

	p_metal = glCreateProgramObjectARB();
	glAttachObjectARB(p_metal,v_metal);
	glAttachObjectARB(p_metal,f_metal);
	//glAttachObjectARB(p,f2);

	glLinkProgramARB(p_metal);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//shadow shader//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
v_shadow = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f_shadow = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

const int shadertype3 = 3;

switch(shadertype2)
{
case 0:
	vs_shadow = textFileRead("parallax_BM_GLOSSMAP.vert");
	fs_shadow = textFileRead("parallax_BM_GLOSSMAP.frag");
	break;
case 1:
    vs_shadow = textFileRead("toon.vert");
	fs_shadow = textFileRead("toon.frag");
	break;
case 2:
    vs_shadow = textFileRead("pho.vert");
	fs_shadow = textFileRead("pho.frag");
	break;
case 3:
    vs_shadow = textFileRead("metal.vert");
	fs_shadow = textFileRead("wallShadow.frag");
	break;
case 4:
    vs_shadow = textFileRead("AMB.vert");
	fs_shadow = textFileRead("AMB.frag");
	break;
}
	const char * ff_shadow = fs_shadow;
	const char * ff2_shadow = fs2_shadow;
	const char * vv_shadow = vs_shadow;

	glShaderSourceARB(v_shadow, 1, &vv_shadow,NULL);
	glShaderSourceARB(f_shadow, 1, &ff_shadow,NULL);
	//glShaderSourceARB(f2, 1, &ff2,NULL);

	free(vs_shadow);free(fs_shadow);

	glCompileShaderARB(v_shadow);
	glCompileShaderARB(f_shadow);
	//glCompileShaderARB(f2);

	p_shadow = glCreateProgramObjectARB();
	glAttachObjectARB(p_shadow,v_shadow);
	glAttachObjectARB(p_shadow,f_shadow);
	//glAttachObjectARB(p,f2);

	glLinkProgramARB(p_shadow);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glUseProgramObjectARB(p);

    /*BMapTangent=glGetAttribLocationARB(p,"Tangent");

    glBindAttribLocationARB(p,BMapTangent,"Tangent" );

    BMapBinormal=glGetAttribLocationARB(p,"Binormal");

    glBindAttribLocationARB(p,BMapBinormal, "Binormal" );*/

    //gunBurst = glGetUniformLocationARB(p,"Burst");
	loc1 = glGetUniformLocationARB(p,"LightPosition");
	posloc = glGetUniformLocationARB(p,"Position");


	loc1_metal = glGetUniformLocationARB(p_metal,"LightPosition");
	posloc_metal = glGetUniformLocationARB(p_metal,"Position");
	//gunBurst = glGetUniformLocationARB(p_metal,"Burst");



}

void newShaders(GLuint &v, GLuint &f, GLuint &p, char* vertexName, char* fragmentName)
{

	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	vs = textFileRead(vertexName);
	fs = textFileRead(fragmentName);

	const char * ff = fs;
	const char * ff2 = fs2;
	const char * vv = vs;

	glShaderSourceARB(v, 1, &vv,NULL);
	glShaderSourceARB(f, 1, &ff,NULL);
	//glShaderSourceARB(f2, 1, &ff2,NULL);

	free(vs);free(fs);

	glCompileShaderARB(v);
	glCompileShaderARB(f);
	//glCompileShaderARB(f2);

	p = glCreateProgramObjectARB();
	glAttachObjectARB(p,v);
	glAttachObjectARB(p,f);
	//glAttachObjectARB(p,f2);

	glLinkProgramARB(p);

	loc1 = glGetUniformLocationARB(p,"LightPosition");
	posloc2 = glGetUniformLocationARB(p,"Position");

}


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
static dWorldID world;
static dSpaceID space;
static dJointGroupID contactgroup;
void setposi(int &,int &);
void perspectiveGL( GLdouble , GLdouble , GLdouble , GLdouble  );
void sceneLoad();
void renderModelTris(mesh &, float );
void renderModelQuads(mesh &, float );
void meshLoad(mesh &, string );
bool IsExtensionSupported( char*  );
float InvSqrt(float );
//bool linkExists(int , int , mesh &);
void constructSpringMesh(mesh &);
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
int createBody(Mech * PlayerMech, mesh &model, float bmass, float xpos, float ypos, float zpos,dWorldID world, dSpaceID space);
float getMeshVolume(mesh &model);
float getAABBVolume(mesh &model);
void meshInitializeVBO(mesh &model);

inline float crossProduct2D(float x1,float x2, float y1,float y2)
{
   return x1*y2 - x2*y1;
}

static void nearCallback (void *data, dGeomID o1, dGeomID o2)
{
	 if(mouseToggle)
	SetCursorPos(640,480);
	int i,n;
	int p;
	dBodyID b1;
	dBodyID b2;

    //if(dGeomGetBody(o1))
	b1 = dGeomGetBody(o1);

    //if(dGeomGetBody(o2))

	b2 = dGeomGetBody(o2);

	//if (b1 && b2 && dAreConnected(b1, b2))
	//	return;
	//if (dGeomGetClass(o1) == dBoxClass && dGeomGetClass(o2) == dBoxClass)
     //   return;
     int index = 0;
   /* for (std::vector<projectile *>::iterator i = playerShots.begin(); i != playerShots.end(); ++i)
    {
        if(b1 == playerShots.at(index)->body || b2 == playerShots.at(index)->body)
        {

            //playerShots.erase(i);
            return;
        }
        else
        ++index;

    }*/
    //else ++i;

        for(int i = 0; i < playerShots.size(); i++)
        if(b1 == playerShots.at(i)->body || b2 == playerShots.at(i)->body)
        {
            //const dReal * f = dBodyGetPosition(playerbody->id());
            //dBodySetPosition(newShot->body,f[0],f[1],f[2]);


            return;
        }

 for (int i = 0; i < player->blockNum; i++)
{
        if(player->blockCarrying[i])
        {
                if(player->mechbody [i]->id() == b1 || player->mechbody [i]->id() == b2 )
                return;
        }
}
  if( dGeomGetClass(o1) == dRayClass || dGeomGetClass(o2) == dRayClass)
  {



    for (int i = 0; i < player->blockNum; i++)
    {
        if( player->mechbody [i]->id() == b2 && dGeomGetClass(o1) == dRayClass)
        {


          //  if(b2)
          //  dBodyAddForce(b2,0.0,0.0,1000.0);
            dContact contact;
            int r = dCollide (o1,o2,1,&contact.geom,sizeof(dContact));
            //selectIndex = r;

        if(r)
        {

            player->blockIntersect[i] = true;
            selectIndex = i;
        }
                dReal  *scratch = contact.geom.pos;
                contactPos[0] = scratch[0];
                contactPos[1] = scratch[1];
                contactPos[2] = scratch[2];

                //return;

            }

                if( player->mechbody [i]->id() == b1 && dGeomGetClass(o2) == dRayClass)
                {

                    player->blockIntersect[i] = true;
                selectIndex = i;

            //    if(b1)
           // dBodyAddForce(b1,0.0,0.0,1000.0);


                dContact contact;
               int r = dCollide (o1,o2,1,&contact.geom,sizeof(dContact));
                //selectIndex = r;
            if(r)
            {


                 player->blockIntersect[i] = true;
                 selectIndex = i;
            }

                    dReal  *scratch = contact.geom.pos;
                    contactPos[0] = scratch[0];
                    contactPos[1] = scratch[1];
                    contactPos[2] = scratch[2];

                    //return;

            }

              //
    }
    return;
  }
else
	{

    const int N = 4;
	dContact contact[N];
	n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
	if (n > 0) {
		for (i=0; i<n; i++) {
		     if(mouseToggle)
		    SetCursorPos(640,480);
			contact[i].surface.mode = dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;
			if (dGeomGetClass(o1) == dSphereClass || dGeomGetClass(o2) == dSphereClass)
				contact[i].surface.mu = 20;
			else
				contact[i].surface.mu = 0.5;
			contact[i].surface.slip1 = 0.0;
			contact[i].surface.slip2 = 0.0;
			contact[i].surface.soft_erp = 1.0;
			contact[i].surface.soft_cfm = 0.00;
			//colPoint[pointNum][0] = contact[i].contactPos.xpos;
			//colPoint[pointNum][1] = contact[i].contactPos.ypos;
			//colPoint[pointNum][2] = contact[i].contactPos.zpos;

			dJointID c = dJointCreateContact (world,contactgroup,contact+i);
			dJointAttach (c,dGeomGetBody(o1),dGeomGetBody(o2));
		}
	}
	}
}

/**************************
 * WinMain
 *
 **************************/

int WINAPI
WinMain (HINSTANCE hInstance,
         HINSTANCE hPrevInstance,
         LPSTR lpCmdLine,
         int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "Daedalus",
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0,800, 600,
      NULL, NULL, hInstance, NULL);
    /* enable OpenGL for the window */

/*
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;


    wincl.hInstance = hInstance;
    wincl.lpszClassName = "Message";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);


    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); // optional


    if (!RegisterClassEx (&wincl))
        return 0;


    hwnd = CreateWindowEx (
           0,
           "Message",
           "Diagnostic Window",
           WS_OVERLAPPEDWINDOW,
           800,
           0,
           544,
           375,
           NULL,//HWND_DESKTOP,
           NULL,
           hInstance,
           NULL
           );


    ShowWindow (hwnd, iCmdShow);
    UpdateWindow(hwnd);*/



GLfloat LightAmbient[]=		{ 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, -5.5f, 1.0f };
GLfloat hemiDirection[]=	{ 0.0f, 0.0f, -1.0f, 0.0f };

lOffset = 0;

LightP [0]= LightPosition[0];
LightP [1]= LightPosition[1];
LightP [2]= LightPosition[2];
LightP [3]= LightPosition[3];




    EnableOpenGL (hWnd, &hDC, &hRC);
    glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
	glClearDepth(1.0f);							// Depth Buffer Setup
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);						// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT0);								// Enable Light One
    glEnable(GL_LIGHTING);
    glEnable(GL_POLYGON_SMOOTH);
    //glEnable(GL_LIGHT1);
    //glEnable (GL_BLEND);

    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glDisable(GL_LIGHTING);

LoadTextFileToEdit(hWnd,"room.bzk");

static int bodies;
static int joints;
//static dJointGroupID contactgroup;

static int wb_stepsdis[1000];
static int wb;
static bool doFast;
static dBodyID b;
static dMass m;
static bool enableAll;
static float cfm = 0.0;//5e-4;
int mY;
int mX;
LPPOINT lpPoint;

pseudoMutex = false;
up = 0;
frmCnt = 0;
playerInteraction = new Interaction();

objXrot = 0.0;
objYrot = 0.0;
mouseToggle = true;
inputBufferCursor = 0;
inputDone = false;
modelArrayIndex = 0;
shaderIndex = 0;
cyldiff = 0.0;
//chamfloor

SceneNode * node1 = new SceneNode();
SceneNode * node2 = new SceneNode();

SceneNode * doorNode = new SceneNode();
SceneNode * doorNode2 = new SceneNode();
SceneNode * grateNode = new SceneNode();
SceneNode * chamNode = new SceneNode();
SceneNode * portNode = new SceneNode();

SceneCell * cell1 = new SceneCell(0);

form1 = new Transform();
form2 = new Transform();
Transform * form3 = new Transform();
Transform * form4 = new Transform();
Transform * form5 = new Transform();
Transform * form6 = new Transform();
Transform * form7 = new Transform();
Transform * form8 = new Transform();

form1->children.push_back(node1);
//form1->children.push_back(node2);
form1->children.push_back(grateNode);
form1->children.push_back(chamNode);
//form1->children.push_back(portNode);
/*
//form2->children.push_back(node1);
form2->children.push_back(node2);
//form2->children.push_back(grateNode);
//form2->children.push_back(chamNode);
form2->children.push_back(portNode);

form3->children.push_back(doorNode);
//form3->children.push_back(node2);

form4->children.push_back(doorNode2);
//form4->children.push_back(node1);
//form4->children.push_back(node2);
*/
//form5->children.push_back(grateNode);

form1->position[0] = 0.0;
form1->position[1] = 0.0;
form1->position[2] = 0.0;

form2->position[0] = 0.0;
form2->position[1] = 18.74060153964;
form2->position[2] = 0.0;

//form3->position[0] = 0.0;
//form3->position[1] = 2*18.74060153964;
//form3->position[2] = 0.0;

form3->position[0] = 0.0;
form3->position[1] = 0.0;
form3->position[2] = 0.0;

form4->position[0] = 0.0;
form4->position[1] = 18.74060153964;
form4->position[2] = 0.0;

//form5->position[0] = 0.0;
//form5->position[1] = 0.0;
//form5->position[2] = 0.0;






    int i;
	i = 0;


    doFast = 1;
	//for (i = 0; i < newMAX; i++)
		wb_stepsdis[i] = 0;

	// recreate world
	dVector3 origin = {0.0,0.0,0.0};
	dVector3 extents = {1000.0,1000.0,1000.0};

	world = dWorldCreate();
	space = dQuadTreeSpaceCreate (0,origin,extents,4);
	selectRay = dCreateRay(space,1000.0);
	contactgroup = dJointGroupCreate (0);
	dWorldSetGravity (world,0,0,-5.0);
	dWorldSetCFM (world, cfm);
	dWorldSetERP (world, 0.8);
	dWorldSetQuickStepNumIterations (world,20);
	ground = dCreatePlane (space,0,0,1,0);
	ceiling = dCreatePlane (space,0,0,-1,-8);

	bodies = 0;
	joints = 0;
//	boxes = 0;

    glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");

    glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC)wglGetProcAddress("glGetAttribLocationARB");
    glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC)wglGetProcAddress("glVertexAttrib3fARB");
    glVertexAttribPointerARB=(PFNGLVERTEXATTRIBPOINTERARBPROC)wglGetProcAddress("glVertexAttribPointerARB");
    glEnableVertexAttribArrayARB=(PFNGLENABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glEnableVertexAttribArrayARB");
    glDisableVertexAttribArrayARB=( PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)wglGetProcAddress("glDisableVertexAttribArrayARB");



    sceneLoad();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//newShaders(testVertexProgram,testFragmentProgram,testShaderProgram,"pho.vert","pho.frag");

#if 1
vertCount = 0;
for(int i = 0; i < 24; i++)
for(int p = 0; p < 3; p++)
{
    VertexArray [i][p] = MVertexArray [i][p];
    vertCount++;
}

for(int i = 0; i < 24; i++)
for(int p = 0; p < 3; p++)
{
    NormalArray [i][p] = MNormalArray [i][p];
}

quadCount = 0;
for(int i = 0; i < 6; i++)
for(int p = 0; p < 4; p++)
{
    quads [i][p] = Mquads [i][p];
    quadCount++;
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check = BuildTexture("1024C.jpg", texture[0]);
//int suck = BuildTexture("1024x1024G.jpg", texture[1]);
//int suck = BuildTexture("fpx033107-03.jpg", texture[1]);
//int suck = BuildTexture("corr_working.jpg", texture[1]);
int suck = BuildTexture("techceiling.jpg", texture[1]);
//int suck2 = BuildTexture("corr_floor_working.jpg", texture[2]);
int suck2 = BuildTexture("berzerk0.jpg", texture[2]);
int suck3 = BuildTexture("corr-working-door.jpg", texture[3]);
    //suck3 = BuildTexture("corr-working-grate.jpg", texture[4]);
     suck3 = BuildTexture("techfloor.jpg", texture[4]);

    suck3 = BuildTexture("AUT", texture[5]);
    suck3 = BuildTexture("BZT", texture[6]);


	glEnable(GL_TEXTURE_2D);

	node1->model = &cryoRoom;
    node2->model = &panel;
    doorNode->model = &door;
    doorNode2->model = &door2;
    grateNode->model = &grate;
    chamNode->model = &chamfloor;
    portNode->model = &port;

#if 0
    //meshLoad(model, "outcorr.osg");
    //meshLoad(cryoRoom, "ouf.osg");
    //meshLoad(model, "frame.osg");
    //meshLoad(cryoRoom, "frame.osg");
    //meshLoad(model, "floor.osg");
    //meshLoad(cryoRoom, "floor.osg");
#else
    //meshLoad(model, "total.osg");
    meshLoad(model, "collision.bzm");
    //meshLoad(cryoRoom, "floor.osg");
    meshLoad(cryoRoom, "techceiling.bzm");
    meshLoad(door, "door.osg");
    meshLoad(door2, "door2.osg");
    //meshLoad(grate, "grate.osg");
     meshLoad(grate, "techfloor.bzm");
    //meshLoad(port, "doores.osg");
    meshLoad(port, "techceiling.bzm");
    meshLoad(playerModel, "DUD");
    meshLoad(shotModel, "BBB");

#endif

meshLoad(modelArray[modelArrayIndex], "DUD");
modelArrayIndex++;
//newShaders(vertexPrograms[shaderIndex],fragmentPrograms[shaderIndex],shaderPrograms[shaderIndex],"BPP.vert","BPP.frag");
//shaderIndex++;
//addBlockMech (player);
    //mesh panel;

    meshLoad(panel, "frame.osg");
     meshLoad(chamfloor, "compile.bzm");//chamberfloor.osg");



for(int i = 0; i <  chamfloor.vertCount; i++)
{

    port.VertexArray [i][0] *= 6.0;
    port.VertexArray [i][1] *= 6.0;
    port.VertexArray [i][2] *= 6.0;
}

for(int i = 0; i <  chamfloor.vertCount; i++)
{

    chamfloor.VertexArray [i][0] *= 6.0;
    chamfloor.VertexArray [i][1] *= 6.0;
    chamfloor.VertexArray [i][2] *= 6.0;

    //panel.VertexArray [i][0] *= 6.0;
    //panel.VertexArray [i][1] *= 6.0;
    //panel.VertexArray [i][2] *= 6.0;


    //cryoRoom.NormalArray [i][0] = 0.0;
    //cryoRoom.NormalArray [i][1] = 0.0;
    //cryoRoom.NormalArray [i][2] = 1.0;
    //cryoRoom.TextureArray [i][0] *= -1.0;
    //cryoRoom.TextureArray [i][1] *= -1.0;
    //cryoRoom.TextureArray [i][2] *= -1.0;


}


for(int i = 0; i <  grate.vertCount; i++)
{

    grate.VertexArray [i][0] *= 6.0;
    grate.VertexArray [i][1] *= 6.0;
    grate.VertexArray [i][2] *= 6.0;

    //panel.VertexArray [i][0] *= 6.0;
    //panel.VertexArray [i][1] *= 6.0;
    //panel.VertexArray [i][2] *= 6.0;


    //cryoRoom.NormalArray [i][0] = 0.0;
    //cryoRoom.NormalArray [i][1] = 0.0;
    //cryoRoom.NormalArray [i][2] = 1.0;
    //cryoRoom.TextureArray [i][0] *= -1.0;
    //cryoRoom.TextureArray [i][1] *= -1.0;
    //cryoRoom.TextureArray [i][2] *= -1.0;


}

for(int i = 0; i <  door.vertCount; i++)
{

    door.VertexArray [i][0] *= 6.0;
    door.VertexArray [i][1] *= 6.0;
    door.VertexArray [i][2] *= 6.0;

    //panel.VertexArray [i][0] *= 6.0;
    //panel.VertexArray [i][1] *= 6.0;
    //panel.VertexArray [i][2] *= 6.0;

    //cryoRoom.NormalArray [i][0] = 0.0;
    //cryoRoom.NormalArray [i][1] = 0.0;
    //cryoRoom.NormalArray [i][2] = 1.0;
    //cryoRoom.TextureArray [i][0] *= -1.0;
    //cryoRoom.TextureArray [i][1] *= -1.0;
    //cryoRoom.TextureArray [i][2] *= -1.0
}

for(int i = 0; i <  door2.vertCount; i++)
{

    door2.VertexArray [i][0] *= 6.0;
    door2.VertexArray [i][1] *= 6.0;
    door2.VertexArray [i][2] *= 6.0;

    door2.NormalArray [i][0] *= 1.0;
    door2.NormalArray [i][1] *= 1.0;
    door2.NormalArray [i][2] *= 1.0;

    //panel.VertexArray [i][0] *= 6.0;
    //panel.VertexArray [i][1] *= 6.0;
    //panel.VertexArray [i][2] *= 6.0;


    //cryoRoom.NormalArray [i][0] = 0.0;
    //cryoRoom.NormalArray [i][1] = 0.0;
    //cryoRoom.NormalArray [i][2] = 1.0;
    //cryoRoom.TextureArray [i][0] *= -1.0;
    //cryoRoom.TextureArray [i][1] *= -1.0;
    //cryoRoom.TextureArray [i][2] *= -1.0;


}

for(int i = 0; i <  cryoRoom.vertCount; i++)
{

    cryoRoom.VertexArray [i][0] *= 6.0;
    cryoRoom.VertexArray [i][1] *= 6.0;
    cryoRoom.VertexArray [i][2] *= 6.0;

    //panel.VertexArray [i][0] *= 6.0;
    //panel.VertexArray [i][1] *= 6.0;
    //panel.VertexArray [i][2] *= 6.0;


    //cryoRoom.NormalArray [i][0] = 0.0;
    //cryoRoom.NormalArray [i][1] = 0.0;
    //cryoRoom.NormalArray [i][2] = 1.0;
    //cryoRoom.TextureArray [i][0] *= -1.0;
    //cryoRoom.TextureArray [i][1] *= -1.0;
    //cryoRoom.TextureArray [i][2] *= -1.0;


}

float pVertexArray [panel.vertCount][3];

ofstream ModOut("modout.txt", ios::out);

for(int i = 0; i <  panel.vertCount; i++)
{
    panel.VertexArray [i][0] *= 6.0;
    panel.VertexArray [i][1] *= 6.0;
    panel.VertexArray [i][2] *= 6.0;

    pVertexArray [i][0] = panel.VertexArray [i][0];
    pVertexArray [i][1] = panel.VertexArray [i][1];
    pVertexArray [i][2] = -panel.VertexArray [i][2];
}

   node1->texture [0] = texture[0];
   node1->texture [1] = texture[1];

   node2->texture [0] = texture[0];
   node2->texture [1] = texture[1];

   doorNode->texture [0] = texture[0];
   doorNode->texture [1] = texture[3];

   doorNode2->texture [0] = texture[0];
   doorNode2->texture [1] = texture[3];

   grateNode->texture [0] = texture[0];
   grateNode->texture [1] = texture[4];

   chamNode->texture [0] = texture[0];
   chamNode->texture [1] = texture[2];

      portNode->texture [0] = texture[0];
   portNode->texture [1] = texture[5];

    float tVertexArray [model.vertCount][3];


textIndex = 7;





for(int i = 0; i <  model.vertCount; i++)
{

    model.VertexArray [i][0] *= 6.0;
    model.VertexArray [i][1] *= 6.0;
    model.VertexArray [i][2] *= 6.0;
    //model.TextureArray [i][0] *= -6.0;
    //model.TextureArray [i][1] *= -6.0;
    //model.TextureArray [i][2] *= -6.0;

    model.NormalArray [i][0] = -1.0;
    model.NormalArray [i][1] = -1.0;
    model.NormalArray [i][2] = -1.0;

    //model.NormalArray [i][0] = 0.0;
    //model.NormalArray [i][1] = 0.0;
    //model.NormalArray [i][2] = -1.0;

    tVertexArray [i][0] = model.VertexArray [i][0];
    tVertexArray [i][1] = model.VertexArray [i][1];
    tVertexArray [i][2] = -model.VertexArray [i][2];

     ModOut <<  tVertexArray [i][0]/6 << " " << tVertexArray [i][1]/6 << " " << tVertexArray [i][2]/6 << "\n";

}

ModOut.close();

   //mesh solidwalls;
  // meshLoad(solidwalls, "unt.osg");

    int texValue = 0;
    for(int i = 0; i < model.vertCount; i++)
    {
       // texValue = i % 4;

        //binormal[i][0] = 0.0;
       // binormal[i][1] = 1.0;
       // binormal[i][2] = 0.0;

       // tangent[i][0] = 1.0;
       // tangent[i][1] = 0.0;
       // tangent[i][2] = 0.0;

       // model.TextureArray[i][0] = 0.05*model.VertexArray[i][0];
       // model.TextureArray[i][1] = 0.05*model.VertexArray[i][1];

    }

     for(int i = 0; i < model.triCount; i++)
    {
       // texValue = i % 4;

          //  model.TextureArray[model.triangles[i][0]][0] = 0.0;
          //  model.TextureArray[model.triangles[i][0]][1] = 0.0;

          //  model.TextureArray[model.triangles[i][1]][0] = 1.0;
          //  model.TextureArray[model.triangles[i][1]][1] = 0.0;

          //  model.TextureArray[model.triangles[i][2]][0] = 1.0;
          //  model.TextureArray[model.triangles[i][2]][1] = 1.0;

    }

     for(int i = 0; i < 16; i++)
     for(int p = 0; p < 2; p++)
    {
        TextureArray[i][p] = MTextureArray[i][p];
    }


        meshInitializeVBO(door);
        meshInitializeVBO(door2);
        meshInitializeVBO(grate);
        meshInitializeVBO(chamfloor);
        meshInitializeVBO(port);
        meshInitializeVBO(playerModel);
////////
	/*glGenBuffersARB( 1, &door.VBOVertices);					        // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, door.VBOVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, door.vertCount*3*sizeof(float), door.VertexArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &door.VBOTexCoords);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, door.VBOTexCoords );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, door.vertCount*2*sizeof(float), door.TextureArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &door.VBONormals);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, door.VBONormals );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, door.vertCount*3*sizeof(float), door.NormalArray, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &door.EBOTris);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, door.EBOTris );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, door.triCount*3*sizeof(int), door.triangles, GL_STATIC_DRAW_ARB );

    glGenBuffersARB( 1, &door.EBOQuads);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, door.EBOQuads );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, door.quadCount*4*sizeof(int),door.quads, GL_STATIC_DRAW_ARB );*/
//////////////////////

    glGenBuffersARB( 1, &cryoRoom.VBOVertices);					        // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, cryoRoom.VBOVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, cryoRoom.vertCount*3*sizeof(float), cryoRoom.VertexArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &cryoRoom.VBOTexCoords);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, cryoRoom.VBOTexCoords );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, cryoRoom.vertCount*2*sizeof(float), cryoRoom.TextureArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &cryoRoom.VBONormals);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, cryoRoom.VBONormals );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, cryoRoom.vertCount*3*sizeof(float), cryoRoom.NormalArray, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &cryoRoom.EBOTris);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, cryoRoom.EBOTris );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, cryoRoom.triCount*3*sizeof(int), cryoRoom.triangles, GL_STATIC_DRAW_ARB );

    glGenBuffersARB( 1, &cryoRoom.EBOQuads);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, cryoRoom.EBOQuads );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, cryoRoom.quadCount*4*sizeof(int),cryoRoom.quads, GL_STATIC_DRAW_ARB );


////////
	glGenBuffersARB( 1, &panel.VBOVertices);					        // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, panel.VBOVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, panel.vertCount*3*sizeof(float), panel.VertexArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &panel.VBOTexCoords);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, panel.VBOTexCoords );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, panel.vertCount*2*sizeof(float), panel.TextureArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &panel.VBONormals);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, panel.VBONormals );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, panel.vertCount*3*sizeof(float), panel.NormalArray, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &panel.EBOTris);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, panel.EBOTris );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, panel.triCount*3*sizeof(int), panel.triangles, GL_STATIC_DRAW_ARB );

    glGenBuffersARB( 1, &panel.EBOQuads);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, panel.EBOQuads );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, panel.quadCount*4*sizeof(int),panel.quads, GL_STATIC_DRAW_ARB );
//////////////////////


	glGenBuffersARB( 1, &VBOVertices);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, kvertCount*3*sizeof(float), kVertexArray, GL_STATIC_DRAW_ARB );

    glGenBuffersARB( 1, &VBOTexCoords);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOTexCoords );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, kvertCount*2*sizeof(float), TextureArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &VBONormals);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBONormals );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, kvertCount*3*sizeof(float), kNormalArray, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &EBOQuads);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, EBOQuads );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, quadCount*4*sizeof(int), quads, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &EBOtris);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, EBOtris );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, ktriCount*3*sizeof(int), ktriangles, GL_STATIC_DRAW_ARB );



    player = new Mech();
    createMech (player);


	wb = 0;


	bool offset = false;
	for (dReal z = WBOXSIZE/2.0; z <= WALLHEIGHT; z+=WBOXSIZE)
	{
		offset = !offset;
		for (dReal y = (-WALLWIDTH+z)/2; y <= (WALLWIDTH-z)/2; y+=WBOXSIZE)
		{


			wall_bodies[wb] = new dBody();
			wall_bodies[wb]->create(world);//dBodyCreate (world);
			wall_bodies[wb]->setPosition(-20,20*y,20*z);// dBodySetPosition (wall_bodies[wb],-20,y,z);
			dMassSetBox (&m,1,WBOXSIZE,WBOXSIZE,WBOXSIZE);
			dMassAdjust (&m, WALLMASS);
			wall_bodies[wb]->setMass(&m);//dBodySetMass (wall_bodies[wb],&m);
			wall_boxes[wb] = new dBox();
			wall_boxes[wb]->create(space,WBOXSIZE,WBOXSIZE,WBOXSIZE);// = dCreateBox (space,WBOXSIZE,WBOXSIZE,WBOXSIZE);
			wall_boxes[wb]->setBody(wall_bodies[wb]->id());// dGeomSetBody (wall_boxes[wb],wall_bodies[wb]);
			//if(wb % 2 == 0)
			//dBodyDisable(wall_bodies[wb]->id());
			wb++;
		}
	}


    enableAll = true;
    aname = "";

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		//exit(1);
	}

	if (!IsExtensionSupported("GL_ARB_vertex_buffer_object"))
	   exit(1);

    setShaders();
    node1->shader =  p_metal;//p_shadow;
    node2->shader = p;
    doorNode->shader = p;
    doorNode2->shader = p;
    grateNode->shader = p_shadow;//p_metal;
    chamNode->shader = p;
    portNode->shader =   p_metal;
    //SetCursorPos(640,480);
    //_beginthread( Thread, 0, NULL );
    ShowCursor(false);
    float scale = -1.0;
    lpos[0] = 0.0;
    lpos[1] = 1.0;
    lpos[2] = 0.5;
    float W,X,Y,Z;
    float axis [3];

    xColRot = 0.0;
    yColRot = 0.0;
    zColRot = 0.0;

    playerRot = 270.0;

    joined1 = NULL;
    joined2 = NULL;

    jointCreateType = 0;

    diagnosticString = "";

    pointNum = 0;

    rate = 0.017;
    long int rendstart;
    int skipframes = 0;
    //lpos);
    //mouseDelX = 640;
   // mouseDelY = 480;
    /* program main loop */
    //dMass m;

    dBody *wallbody1 = new dBody();
	dBox*	wallbox1 = new dBox();
		wallbody1->create(world);
		wallbody1->setPosition (0,-15,5);
		dMassSetBox (&m,1,30,10.0,10.0);
		dMassAdjust (&m, 10000000);
		wallbody1->setMass (&m);
		wallbox1->create(space,30.0,10.0,10.0);
		wallbox1->setBody (wallbody1->id());

    dBody *wallbody2 = new dBody();
	dBox*	wallbox2 = new dBox();
		wallbody2->create(world);
		wallbody2->setPosition (0,15,5);
		dMassSetBox (&m,1,30,10.0,10.0);
		dMassAdjust (&m, 10000000);
		wallbody2->setMass (&m);
		wallbox2->create(space,30.0,10.0,10.0);
		wallbox2->setBody (wallbody2->id());



      dTriMeshDataID new_tmdata = dGeomTriMeshDataCreate();
      //dGeomTriMeshDataBuildSingle(new_tmdata, &kVertexArray[0][0], 3 * sizeof(float), 16, (int*)&Mtris[0][0], 8, 3 * sizeof(int));
      dGeomTriMeshDataBuildSingle(new_tmdata,&tVertexArray[0][0],3 * sizeof(float), model.vertCount, (int*)&model.triangles[0][0], 3*model.triCount, 3 * sizeof(int));

      dGeomID geom = dCreateTriMesh(space, new_tmdata, 0, 0, 0);
      geomGlob = geom;

      //node1->sceneGeom = geom;

      // remember the mesh's dTriMeshDataID on its userdata for convenience.
      dGeomSetData(geom, new_tmdata);

         {dGeomSetPosition(geom, 0,0,0);
          dMatrix3 Rotation;// = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
          //dRFromAxisAndAngle(Rotation, 1,0 , 0, 90.0*piover180);
          //dRFromAxisAndAngle(Rotation, 0,0 , 1,0.0*piover180);


          //dRFromAxisAndAngle(Rotation,0,1 ,0,180.0*piover180);
          dRFromEulerAngles(Rotation,180.0*piover180,180.0*piover180,0.0);
          dGeomSetRotation(geom, Rotation);
      }
/*

      dTriMeshDataID new_tmdata2 = dGeomTriMeshDataCreate();
      //dGeomTriMeshDataBuildSingle(new_tmdata, &kVertexArray[0][0], 3 * sizeof(float), 16, (int*)&Mtris[0][0], 8, 3 * sizeof(int));
      dGeomTriMeshDataBuildSingle(new_tmdata2,&pVertexArray[0][0],3 * sizeof(float), panel.vertCount, (int*)&panel.triangles[0][0], 3*panel.triCount, 3 * sizeof(int));

      dGeomID geom2 = dCreateTriMesh(space, new_tmdata2, 0, 0, 0);


      //node2->sceneGeom = geom2;

      dGeomSetData(geom2, new_tmdata2);

         {dGeomSetPosition(geom2, 0,0,0);
          dMatrix3 Rotation;// = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
          //dRFromAxisAndAngle(Rotation, 1,0 , 0, 90.0*piover180);
          //dRFromAxisAndAngle(Rotation, 0,0 , 1,0.0*piover180);


          //dRFromAxisAndAngle(Rotation,0,1 ,0,180.0*piover180);
          dRFromEulerAngles(Rotation,180.0*piover180,180.0*piover180,0.0);
          dGeomSetRotation(geom2, Rotation);
      }
*/
    //  dMassSetBox (&m,1.0,10.0,10.0,10.0);


    dBody *wallbody3 = new dBody();
	dBox*	wallbox3 = new dBox();
		wallbody3->create(world);
		wallbody3->setPosition (-10,10,5);
		dMassSetBox (&m,1,10,10.0,10.0);
		dMassAdjust (&m, 10000000);
		wallbody3->setMass (&m);
		wallbox3->create(space,10.0,10.0,10.0);
		dGeomSetBody(wallbox3->id(),wallbody3->id());

////////////////////Set up cells and nodes for rendering/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cell1->trans.push_back(form1);
    cell1->trans.push_back(form2);
    cell1->trans.push_back(form3);
    cell1->trans.push_back(form4);

    cellArray.push_back(cell1);

    //Set up scene visibility graph
    SceneVisibilityGraph[0] = 0x00000001;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    hand = new dBody();
	handbox = new dBox();
		hand->create(world);
		hand->setPosition (-10,0,5);
		dMassSetBox (&m,1,1,1.0,1.0);
		dMassAdjust (&m, 10);
		hand->setMass (&m);
		handbox->create(space,1.0,1.0,1.0);
		handbox->setBody (hand->id());

    dBodySetGravityMode(hand->id(),0);

     handJoint = new dFixedJoint();
     handJoint->create(world);


      playerbody = new dBody();
	   playerbox = new dBox();
		playerbody->create(world);
		playerbody->setPosition (-120.0,50.0,1.5);
		dMassSetBox (&m,1,3.0,3.0,3.0);
		dMassAdjust (&m, 10000);
		playerbody->setMass (&m);
		playerbox->create(space,3.0,3.0,3.0);
		playerbox->setBody (playerbody->id());

burstValue = 0.0;

	//playerbody = player->mechbody[5];


//xpos = 120.0;
//zpos = -50.0;

   start = timeGetTime();
   rendstart = timeGetTime();

    int BlockNumber = player->blockNum;
    while (!bQuit)
    {

        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {

        if (0)
		{
			dSpaceCollide (space,0,&nearCallback);
#if defined(QUICKSTEP)
			dWorldQuickStep (world,0.1);
#elif defined(STEPFAST)
			dWorldStepFast1 (world,0.02,ITERS);
#endif
			dJointGroupEmpty (contactgroup);
		}
		else
		{

			 for (int i = 0; i < player->blockNum; i++)
            {
                player->blockIntersect[i] = false;
            }

			dSpaceCollide (space,0,&nearCallback);
			dWorldQuickStep (world,0.025);
			dJointGroupEmpty (contactgroup);
		}


float playerpos[3];
g = playerbody->getPosition();
playerpos[0] = 4.0*sin(piover180*mouseRotX) - 1.0*cos(-(piover180*mouseRotX - piover180*180.0));
playerpos[1] = 4.0*cos(piover180*mouseRotX) - 1.0*sin(-(piover180*mouseRotX - piover180*180.0));
playerpos[2] = -1.3 - 4.0*sin(piover180*mouseRotY);
xpos = -g[0] + playerpos[0];
zpos = -g[1] + playerpos[1];
ypos = -1.3 - g[2] + playerpos[2];;

if( burstValue > 0.0 && burstValue < 3.1456)
 {
    burstValue += 0.3;
}

if( burstValue > 3.1456)
{
    burstValue = -0.1;
}

 if(leftDown)
 {
        burstValue = 0.1;
 }
//glUniform3fARB(gunBurst,burstValue,burstValue,burstValue);

float moveMag = 0.0;
if(key == 1)
                  {
                      //xpos -= (float)sin(heading*piover180) * WALKSPEED;
                      //zpos -= (float)cos(heading*piover180) * WALKSPEED;
                      //playerbody->setLinearVel(-sin(piover180*mouseRotX),-cos(piover180*mouseRotX),0.0);
                       //playerbody->addForce(300.0*sin(piover180*mouseRotX),300.0*cos(piover180*mouseRotX),0.0);
                       moveMag = WALKSPEED;
                       playerbody->setLinearVel(moveMag*sin(piover180*mouseRotX),moveMag*cos(piover180*mouseRotX),0.0);
                  }
                  else if(key == 0)
                  {
                      //playerbody->addForce(-300.0*sin(piover180*mouseRotX),-300.0*cos(piover180*mouseRotX),0.0);
                    //playerbody->setLinearVel(sin(piover180*mouseRotX),cos(piover180*mouseRotX),0.0);
                     // xpos += (float)sin(heading*piover180) * WALKSPEED;
                      //zpos += (float)cos(heading*piover180) * WALKSPEED;
                      moveMag = -WALKSPEED;
                      playerbody->setLinearVel(moveMag*sin(piover180*mouseRotX),moveMag*cos(piover180*mouseRotX),0.0);

                  }
                  else if(key == 65)
                  {
                      //playerbody->addForce(-300.0*sin(piover180*mouseRotX),-300.0*cos(piover180*mouseRotX),0.0);
                    //playerbody->setLinearVel(sin(piover180*mouseRotX),cos(piover180*mouseRotX),0.0);
                     // xpos += (float)sin(heading*piover180) * WALKSPEED;
                      //zpos += (float)cos(heading*piover180) * WALKSPEED;
                      moveMag = -WALKSPEED;
                      playerbody->setLinearVel(moveMag*sin(piover180*(mouseRotX - 90.0)),moveMag*cos(piover180*(mouseRotX  - 90.0)),0.0);

                  }
                    else if(key == 68)
                  {
                      //playerbody->addForce(-300.0*sin(piover180*mouseRotX),-300.0*cos(piover180*mouseRotX),0.0);
                    //playerbody->setLinearVel(sin(piover180*mouseRotX),cos(piover180*mouseRotX),0.0);
                     // xpos += (float)sin(heading*piover180) * WALKSPEED;
                      //zpos += (float)cos(heading*piover180) * WALKSPEED;
                      moveMag = WALKSPEED;
                      playerbody->setLinearVel(moveMag*sin(piover180*(mouseRotX - 90.0)),moveMag*cos(piover180*(mouseRotX - 90.0)),0.0);

                  }
                  else
                  playerbody->setLinearVel(0.0,0.0,0.0);


pseudoMutex = true;
if(skipframes == 0)
{
            /*glUniform3fARB(loc1,lpos[0],lpos[1],lpos[2]);

            texloc   = glGetUniformLocationARB(p_metal, "NormalHeight");
            //texloc   = glGetUniformLocationARB(p_metal, "NormalHeight");

            glUniform1iARB(texloc, 0);
            //glUniform1iARB(texloc_metal, 0);

            texloc2   = glGetUniformLocationARB(p_metal, "Base");
            //texloc2   = glGetUniformLocationARB(p_metal, "Base");

            glUniform1iARB(texloc2, 1);*/
            //glUniform1iARB(texloc2_metal, 1);



            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

            GLfloat material_diffuse[] = { 0, 0, 0, 1 };
            GLfloat material_specular[] = { 0.7, 0.8, 0.7, 1 };
            GLfloat material_shininess[] = { 10 };
            GLfloat material_ambient[] = { 0.0, 0.0, 0.0, 1 };
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);

            glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
           // glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
            glLightfv(GL_LIGHT0, GL_AMBIENT, material_ambient);
            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.8f);
            glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0007f);
            glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0002f);
            glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);


                if(key == 3)
                {
                         LightPosition[0] =  xpos;
                         LightPosition[1] =  zpos;
                         LightPosition[2] = -5.5;
                         LightP [0]= LightPosition[0];
                         LightP [1]= LightPosition[1];
                         LightP [2]= LightPosition[2];
                         LightP [3]= LightPosition[3];
                }

                //glUniform3fARB(posloc,xpos, zpos,-ypos);
                 //glUniform3fARB(posloc2,xpos, zpos,-ypos);
                 glUniform3fARB(posloc,xpos, zpos,-ypos);
                 glUniform3fARB(posloc2,xpos, zpos,-ypos);

    //for (int i = 0; i < wb - 1; i++)
    for (int i = 0; i < player->blockNum; i++)
    {

            //SetCursorPos(640,480);

            glPushMatrix ();

            //glUseProgramObjectARB(player->shader[i]);

            glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
           // glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

            perspectiveGL( 45, 1.33333333, 0.1f, 1000.0f );
           //
            glRotatef (90.0, 1.0f, 0.0f, 0.0f);
           // if(mouseMove)
           // {

                glRotatef (mouseRotY*0.5, 180.0f, 0.0f, 0.0f);
                glRotatef (mouseRotY*0.5, 1.0f, 0.0f, 0.0f);
                glRotatef (mouseRotX, 0.0f, 0.0f, 1.0f);


         dGeomRaySet(selectRay,-xpos,-zpos,-ypos,sin(piover180*mouseRotX),cos(piover180*mouseRotX),sin(piover180*(-mouseRotY)));

                //hand->setPosition(-xpos + 3.0*sin(piover180*(mouseRotX+10)),-zpos + 3.0*cos(piover180*(mouseRotX+10)),3.5);

//glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

                 glTranslatef (-xpos,-zpos,-ypos);
                // lpos[0] -= xpos;lpos[1] -= zpos;
           // }
        //glPushMatrix ();

         //   glMatrixMode(GL_PROJECTION);
                   // glLoadIdentity();

              //glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);	// Position The Light

               glActiveTexture(GL_TEXTURE0);
               glBindTexture(GL_TEXTURE_2D, player->texture [i]);
               //glDisable(GL_TEXTURE_2D);
              glEnableClientState(GL_NORMAL_ARRAY);
              glEnableClientState(GL_VERTEX_ARRAY);
              glEnableClientState(GL_TEXTURE_COORD_ARRAY);


            // glEnableClientState(GL_VERTEX_ARRAY);



        //wall_bodies[200]->addTorque(0,0,0.05);

        if( player->blockIntersect[i] == true)
        {
             GLfloat diffuse[] = { 1, 0, 0, 0 };
             glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

             if(leftDown)
                {

                    dBodyEnable(player->mechbody [i]->id());
                    dBodyAddForce(player->mechbody [i]->id(),10000000.0,20000000.0,0.0);
                }

             if(key == 69)
             {
                    player->blockCarrying [i] = true;
                    player->mechbody [i] ->disable();
                    playerInteraction->setHand(LEFT);
                    //dBodySetGravityMode(player->mechbody [i]->id(),0);
                   // player->mechbody [i]->setPosition(-xpos + 3.0*sin(piover180*(mouseRotX+10)),-zpos + 3.0*cos(piover180*(mouseRotX+10)),3.5);
                   // handJoint->attach(hand->id(),player->mechbody [i]->id());
                   // handJoint->set();

             }

             if(key == 70)
             {
                    if(!player->blockSelected [i])
                    player->blockSelected [i] = true;
                    else
                    player->blockSelected [i] = false;
                    //dBodySetGravityMode(player->mechbody [i]->id(),0);
                   // player->mechbody [i]->setPosition(-xpos + 3.0*sin(piover180*(mouseRotX+10)),-zpos + 3.0*cos(piover180*(mouseRotX+10)),3.5);
                   // handJoint->attach(hand->id(),player->mechbody [i]->id());
                   // handJoint->set();

             }

             //player->mechbody [i]->addForce(0.0,0.0,100000.0);
        }
        else
             glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);

        if( player->blockCarrying[i] == true)
        {
              player->mechbody [i]->setPosition(-xpos + 3.3*sin(piover180*(mouseRotX+19)),-zpos + 3.3*cos(piover180*(mouseRotX+19)),3.0 + 3.3*sin(piover180*(-mouseRotY)));
               if(key == 2 )
               {
                    player->modelIndex [i] = &modelArray[modelArrayIndex - 1 ];
                    player->modelID[i] = modelArrayIndex - 1 ;
               }

                 if(key == 77)
                {
                    player->texture [i] = texture[textIndex - 1];
                    player->textID[i] = textIndex - 1 ;
                }

                 if(key == 78)
                {
                    player->shader [i] = shaderPrograms[shaderIndex - 1 ];
                    player->shaderID[i] = shaderIndex - 1 ;
                }

        }

        if( player->blockSelected[i] == true)
        {
             GLfloat diffuse[] = { 0, 1, 0, 0 };
             glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        }

        if(key == 2 )
        {
                   //player->mechbody [i]->addRelForce(50.0,-50.0*sin(mouseRotX),-50.0*cos(mouseRotX));
                   if( player->blockIntersect[i] == true)
                   dBodyAddForce(player->mechbody [i]->id(),1000000.0*sin(piover180*mouseRotX),1000000.0*cos(piover180*mouseRotX),10.0*sin(piover180*(-mouseRotY)));


                   //ssplayer->mechbody [i]->addTorque(0,800.2,0);
        }

                   const dReal * vel;
                   const dReal * angvel;

                   //if(player->mechboxes [i]->id())
                   //dGeomGetQuaternion(player->mechboxes [i]->id(),quat);

                   if(player->mechGeoms [i])
                   dGeomGetQuaternion(player->mechGeoms [i],quat);
                   //rotmat =  player->mechboxes [i]->getRotation();
                   g = player->mechbody [i]->getPosition();

                   //if(i == 10)
                   glUniform3fARB(occl,-g[0],-g[1],-g[2]);
                   //else
                  // glUniform3fARB(occl,0.0,0.6,0.0);

                   vel = dBodyGetLinearVel(player->mechbody [i]->id());
                   angvel = dBodyGetAngularVel(player->mechbody [i]->id());

                   float vmag = vel[0]*vel[0] + vel[1]*vel[1] + vel[2]*vel[2];
                   float amag = angvel[0]*angvel[0] + angvel[1]*angvel[1] + angvel[2]*angvel[2];

                   if(vmag < 2.0*VELMIN )//&& amag < 0.0*VELMIN)
                        disable[i] = true;
                   else
                        {
                            disable[i] = false;
                            dBodyEnable(player->mechbody [i]->id());
                            disableSteps[i] = 0;
                        }

                   if(disable[i])
                        disableSteps[i]++;

                    if(disableSteps[i] >= STEPMAX)
                        dBodyDisable(player->mechbody [i]->id());


                   W = quat[0];
                   X = quat[1];
                   Y = quat[2];
                   Z = quat[3];

                   float sc = sqrt(X*X + Y*Y + Z*Z);

                   axis[0] = X/sc;
                   axis[2] = Y/sc;
                   axis[1] = Z/sc;
                   theta = acos(W)*2.0f;
                   //const GLfloat *transMat = (mat[0],mat[4],mat[8],-0.05*g[0],
                   //                  mat[1],mat[5],mat[9],-0.05*g[1],
                   //                  mat[2],mat[6],mat[10],-0.05*g[2]);
                    theta /= piover180;


                    if(i == 5)
                    XProd = crossProduct2D(g[0],g[1], xpos,zpos);

                   // glLoadMatrixf(transMat);
                   glTranslatef(-1.0*g[0],-1.0*g[1],-1.0*g[2]);
                   glRotatef(theta,axis[0],axis[2],axis[1]);


             glPushMatrix();
             glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();


                glRotatef(-theta,axis[0],axis[2],axis[1]);
                glTranslatef(1.0*g[0],1.0*g[1],1.0*g[2]) ;


                 glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
                 glLightfv(GL_LIGHT1, GL_POSITION, hemiDirection);
               	// Position The Light



              glPopMatrix();

                   //glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);	// Position The Light
                   //theta+= 0.01;
                   //glRotatef(theta,0.0,1.0,1.0);

                 /*  glBindBufferARB( GL_ARRAY_BUFFER_ARB,modelArray[modelArrayIndex -1].VBOVertices );
		           glVertexPointer( 3, GL_FLOAT, 0, 0);//(char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer

                   glBindBufferARB( GL_ARRAY_BUFFER_ARB, modelArray[modelArrayIndex].VBOTexCoords );
		           glTexCoordPointer(2, GL_FLOAT, 0, 0 );

		           glBindBufferARB( GL_ARRAY_BUFFER_ARB, modelArray[modelArrayIndex].VBONormals );
		           glNormalPointer( GL_FLOAT, 0, 0 );		// Set The TexCoord Pointer To The TexCoord Buffe

                   glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, modelArray[modelArrayIndex].EBOTris );
                */



#if 1
        //glBegin (GL_TRIANGLES);


                 //SetCursorPos(640,480);

                 float delx,dely,delz;

                 delx = player->blockDimension[i][0]*0.5;
                 dely = player->blockDimension[i][1]*0.5;
                 delz = player->blockDimension[i][2]*0.5;

bool render = i % 2;

#if 1

//if(persp)
//glUseProgramObjectARB(p);
//else
//glUseProgramObjectARB(0);
  glUseProgramObjectARB(player->shader[i]);

 if(player->modelIndex [i] == NULL)
 {



                 //glUseProgramObjectARB(p);

                 glBegin(GL_QUADS);
                 glColor3f(0.0,0.0,1.5);
                 glNormal3f(0.0,0.0,1.5);
                // glVertex3f();
                //-0.05*g[0],-0.05*g[1],-0.05*g[2]

                 /*glVertex3f(-0.05*(delx + g[0]),-0.05*(dely + g[1]),-0.05*(delz + g[2]));
                 glVertex3f(-0.05*(delx + g[0]),-0.05*(dely - g[1]),-0.05*(delz + g[2]));
                 glVertex3f(-0.05*(delx - g[0]),-0.05*(dely - g[1]),-0.05*(delz + g[2]));
                 glVertex3f(-0.05*(delx - g[0]),-0.05*(dely + g[1]),-0.05*(delz + g[2]));*/

                 //glVertex3f(delx,dely,-delz);
                 //glVertex3f(delx,-dely,-delz);
                 //glVertex3f(-delx,-dely,-delz);
                 //glVertex3f(-delx,dely,-delz);

        glNormal3f(0.0f,0.75f,0.0f);
        glColor3f(0.0f,1.5f,0.0f);
        glTexCoord2f(0.0f,0.0f);		// Set The Color To Green
		glVertex3f( 0.75f, 0.75f,-0.75f);			// Top Right Of The Quad (Top)
        glTexCoord2f(0.0f,1.0f);
		glVertex3f(-0.75f, 0.75f,-0.75f);			// Top Left Of The Quad (Top)
        glTexCoord2f(1.0f,1.0f);
		glVertex3f(-0.75f, 0.75f, 0.75f);			// Bottom Left Of The Quad (Top)
        glTexCoord2f(1.0f,0.0f);
		glVertex3f( 0.75f, 0.75f, 0.75f);			// Bottom Right Of The Quad (Top)

 //SetCursorPos(640,480);
	//The bottom is drawn the exact same way as the top, but because it's the bottom, it's drawn down one unit from the center of the cube. Notice the Y axis is always minus one. If we were under the cube, looking at the quad that makes the bottom, you would notice the top right corner is the corner closest to the viewer, so instead of drawing in the distance first, we draw closest to the viewer first, then on the left side closest to the viewer, and then we go into the screen to draw the bottom two points.

//If you didn't really care about the order the polygons were drawn in (clockwise or not), you could just copy the same code for the top quad, move it down on the Y axis to -1, and it would work, but ignoring the order the quad is drawn in can cause weird results once you get into fancy things such as texture mapping.

        glNormal3f(0.0f,-0.75f,0.0f);
		glColor3f(0.75f,0.5f,0.0f);			// Set The Color To Orange
        glTexCoord2f(0.0f,0.0f);
		glVertex3f( 0.75f,-0.75f, 0.75f);			// Top Right Of The Quad (Bottom)
        glTexCoord2f(1.0f,0.0f);
		glVertex3f(-0.75f,-0.75f, 0.75f);			// Top Left Of The Quad (Bottom)
        glTexCoord2f(1.0f,1.0f);
		glVertex3f(-0.75f,-0.75f,-0.75f);			// Bottom Left Of The Quad (Bottom)
        glTexCoord2f(1.0f,0.0f);
		glVertex3f( 0.75f,-0.75f,-0.75f);			// Bottom Right Of The Quad (Bottom)

 //SetCursorPos(640,480);
	//Now we draw the front of the Quad. We move one unit towards the screen, and away from the center to draw the front face. Notice the Z axis is always one. In the pyramid the Z axis was not always one. At the top, the Z axis was zero. If you tried changing the Z axis to zero in the following code, you'd notice that the corner you changed it on would slope into the screen. That's not something we want to do right now :)

        glNormal3f(0.0f,0.0f,0.75f);
		glColor3f(0.75f,0.0f,0.0f);			// Set The Color To Red
		 glTexCoord2f(0.0f,0.0f);
		glVertex3f( 0.75f, 0.75f, 0.75f);			// Top Right Of The Quad (Front)
		 glTexCoord2f(0.0f,1.0f);
		glVertex3f(-0.75f, 0.75f, 0.75f);			// Top Left Of The Quad (Front)
		 glTexCoord2f(1.0f,1.0f);
		glVertex3f(-0.75f,-0.75f, 0.75f);			// Bottom Left Of The Quad (Front)
		 glTexCoord2f(1.0f,0.0f);
		glVertex3f( 0.75f,-0.75f, 0.75f);			// Bottom Right Of The Quad (Front)

// SetCursorPos(640,480);
	//The back face is a quad the same as the front face, but it's set deeper into the screen. Notice the Z axis is now minus one for all of the points.

        glNormal3f(0.0f,0.0f,-0.75f);
		glColor3f(0.75f,0.75f,0.0f);			// Set The Color To Yellow
		 glTexCoord2f(0.0f,0.0f);
		glVertex3f( 0.75f,-0.75f,-0.75f);			// Bottom Left Of The Quad (Back)
		 glTexCoord2f(0.0f,1.0f);
		glVertex3f(-0.75f,-0.75f,-0.75f);			// Bottom Right Of The Quad (Back)
		 glTexCoord2f(1.0f,2.0f);
		glVertex3f(-0.75f, 0.75f,-0.75f);			// Top Right Of The Quad (Back)
		 glTexCoord2f(1.0f,0.0f);
		glVertex3f( 0.75f, 0.75f,-0.75f);			// Top Left Of The Quad (Back)

// SetCursorPos(640,480);
	//Now we only have two more quads to draw and we're done. As usual, you'll notice one axis is always the same for all the points. In this case the X axis is always minus one. That's because we're always drawing to the left of center because this is the left face.

        glNormal3f(-0.75f,0.0f,0.0f);
		glColor3f(0.0f,0.0f,0.75f);			// Set The Color To Blue
		 glTexCoord2f(0.0f,0.0f);
		glVertex3f(-0.75f, 0.75f, 0.75f);			// Top Right Of The Quad (Left)
		 glTexCoord2f(0.0f,1.0f);
		glVertex3f(-0.75f, 0.75f,-0.75f);			// Top Left Of The Quad (Left)
		 glTexCoord2f(1.0f,2.0f);
		glVertex3f(-0.75f,-0.75f,-0.75f);			// Bottom Left Of The Quad (Left)
		 glTexCoord2f(1.0f,0.0f);
		glVertex3f(-0.75f,-0.75f, 0.75f);			// Bottom Right Of The Quad (Left)

 //SetCursorPos(640,480);
	//This is the last face to complete the cube. The X axis is always one. Drawing is counter clockwise. If you wanted to, you could leave this face out, and make a box :)

//Or if you felt like experimenting, you could always try changing the color of each point on the cube to make it blend the same way the pyramid blends. You can see an example of a blended cube by downloading Evil's first GL demo from my web page. Run it and press TAB. You'll see a beautifully colored cube, with colors flowing across all the faces.

        glNormal3f(0.75f,0.0f,0.0f);
		glColor3f(0.75f,0.0f,0.75f);			// Set The Color To Violet
		 glTexCoord2f(0.0f,0.0f);
		glVertex3f( 0.75f, 0.75f,-0.75f);			// Top Right Of The Quad (Right)
		 glTexCoord2f(0.0f,1.0f);
		glVertex3f( 0.75f, 0.75f, 0.75f);			// Top Left Of The Quad (Right)
		 glTexCoord2f(1.0f,1.0f);
		glVertex3f( 0.75f,-0.75f, 0.75f);			// Bottom Left Of The Quad (Right)
		 glTexCoord2f(1.0f,0.0f);
		glVertex3f( 0.75f,-0.75f,-0.75f);			// Bottom Right Of The Quad (Right)

 //SetCursorPos(640,480);


                 glEnd();

 }
else
 {
                   glBindBufferARB( GL_ARRAY_BUFFER_ARB,player->modelIndex [i]->VBOVertices );
		           glVertexPointer( 3, GL_FLOAT, 0, 0);//(char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer

                   glBindBufferARB( GL_ARRAY_BUFFER_ARB, player->modelIndex [i]->VBOTexCoords );
		           glTexCoordPointer(2, GL_FLOAT, 0, 0 );

		           glBindBufferARB( GL_ARRAY_BUFFER_ARB, player->modelIndex [i]->VBONormals );
		           glNormalPointer( GL_FLOAT, 0, 0 );		// Set The TexCoord Pointer To The TexCoord Buffe

                   glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, player->modelIndex [i]->EBOTris );
                  //glDrawArrays( GL_TRIANGLES, 0, player->modelIndex [i]->vertCount);
                  //glDrawElements(GL_TRIANGLES,player->modelIndex [i]->triCount*3,GL_UNSIGNED_INT,NULL);
                  // glDrawArrays( GL_TRIANGLES, 0, modelArray[modelArrayIndex].vertCount);
                  //glDrawElements(GL_TRIANGLES,modelArray[modelArrayIndex].triCount*3,GL_UNSIGNED_INT,NULL);
                  glDrawElements(GL_TRIANGLES,player->modelIndex [i]->triCount*3,GL_UNSIGNED_INT,NULL);


            }

#else

#endif


                glDisableClientState( GL_VERTEX_ARRAY );
                glDisableClientState( GL_NORMAL_ARRAY );


                   //renderModelTris(model, -1.0);//-0.05);


           // glEnd ();

           // glPopMatrix();

            glPopMatrix();
          }
#endif

glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

////////////////////Beginning of static scene rendering/////////////////////////////////////////////////////////////////////////////////
/* Will use basic scenegraph with frustum culling. TODO: portal rendering or simplification.

   Convention of graph
*/


/*
        Algorithm:
                    -   Use bounds checking to find active cell;
                    -   Use SceneVisibilityGraph[activeCellID] to reference cells to be rendered
                    -   For each bit of SceneVisibilityGraph[activeCell], call cellArray.at(i)->render() if bit is 1
*/

int activeCell;

for(int i = 0; i < cellArray.size(); i++)
    if(cellArray.at(i) && cellArray.at(i)->boundsCheck())
        activeCell = i;

for(int i = 0; i < 32; i++)
{
    unsigned long mask = 1 << i;
    //mask = mask << i;

    if(mask & SceneVisibilityGraph[activeCell])
    int rendered = cellArray.at(i)->render();

}

//int ch = cell1->render();

            long int diff;
            long int rendtime;

           // int endCnt;
             end = timeGetTime();
             diff = end - start;
             rendtime = end - rendstart;
             rendstart = timeGetTime();

             if(rendtime > 10)
                skipframes += rendtime/10;
             //else
                //rendtime = 0;

            // itoa((int) diff,FPS,10);
             if (diff > 1000.0)
             {
                 //endCnt = frmCnt;
                 start = timeGetTime();
                 FPS = frmCnt;
                 //itoa(frmCnt,FPS,10);
                 frmCnt = 0;
             }
            //if(mouseDelX < 650 && mouseDelX > 630 && mouseDelY < 490 && mouseDelY > 470 )
            glUseProgramObjectARB(0);
            glPushMatrix();
            glLoadIdentity();
            glDisable(GL_LIGHTING);
           // glOrtho(0,800,0,600,-1, 1);
            glMatrixMode(GL_MODELVIEW);
            glColor3f(1.0f,1.0f,1.0f);
            glScalef(.05,.05,.05);
            glTranslatef(-15.0,17.8,0);
 if(player && player->mechbody [player->blockNum])
      {

            g = dBodyGetPosition(player->mechbody [player->blockNum - 1]->id());
            X = g[0]; Y = g[1]; Z = g[2];
            glPrint("FPS %d Body Count %d %s",FPS,player->blockNum,keyInputBuffer,0);
            //glPrint("FPS %d Body Count %d %s",rendtime,skipframes,keyInputBuffer,0);
            //glPrint("FPS %f Body Count %f %f",burstValue, 1.0*mouseRotX,1.0*mouseRotY,0);
            //glPrint("FPS %f Body Count %f %s",xpos, zpos, keyInputBuffer,0);
            //glPrint("FPS %f Body Count %f %f",model.TextureArray[, 1.0*mouseRotX,1.0*mouseRotY,0);
      }
//XProd
        glEnable(GL_LIGHTING);
            //glPrint(keyInputBuffer,0);
            glPopMatrix();

             glPushMatrix();
            glLoadIdentity();
            //glDisable(GL_LIGHTING);
           // glOrtho(0,800,0,600,-1, 1);
            glMatrixMode(GL_MODELVIEW);
            glColor3f(1.0f,1.0f,1.0f);
            glScalef(.05,.05,.05);
            glTranslatef(-15.0,17.-36,0);
//jointCreateType
            string jtype;
            switch(jointCreateType)
            {
                case 0: jtype = "Fixed";
                        break;
                case 1: jtype = "Ball";
                        break;
                case 2: jtype = "Hinge1";
                        break;
                case 3: jtype = "Hinge2";
                        break;
                case 4: jtype = "Universal";
                        break;
                case 5: jtype = "Slider";
                        break;
            };

            glPrint("Joint Type %s Message: %d %s",jtype.c_str(),player->jointNum,diagnosticString.c_str(),0);



            //glPrint(keyInputBuffer,0);
            glPopMatrix();


            glPushMatrix ();

                glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();

            glBegin(GL_POINTS);
            glVertex2f(0.0,0.0);

            glEnd();

        glPopMatrix();


////////////////////Beginning of player scene rendering/////////////////////////////////////////////////////////////////////////////////
 glPushMatrix();
                    glLoadIdentity();
                    perspectiveGL( 45, 1.33333333, 0.1f, 1000.0f );

                    glRotatef (90.0, 1.0f, 0.0f, 0.0f);
               // if(mouseMove)
               // {

                glRotatef (mouseRotY*0.5, 180.0f, 0.0f, 0.0f);
                glRotatef (mouseRotY*0.5, 1.0f, 0.0f, 0.0f);
                glRotatef (mouseRotX, 0.0f, 0.0f, 1.0f);
               //

                    glTranslatef(-playerpos[0],-playerpos[1],-playerpos[2]);

                glRotatef (-(mouseRotX + playerRot), 0.0f, 0.0f, 1.0f);

                  glPushMatrix();
                glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();


                glRotatef((mouseRotX + playerRot), 0.0f, 0.0f, 1.0f);
                glTranslatef(-xpos + playerpos[0],-zpos +  playerpos[1],-ypos + playerpos[2]) ;


                 glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

               	// Position The Light



              glPopMatrix();

                   // glTranslatef(playerpos[0],playerpos[1],playerpos[2]);
                    //glRotatef(90.0f,1.0f,0.0f,0.0f);
                    //glRotatef(92.5f,0.0f,0.0f,1.0f);
                    //glRotatef(180.0f,0.0f,0.0f,.0f);

                    glUseProgramObjectARB(p_metal);
                    glActiveTexture(GL_TEXTURE1);

                    glBindTexture(GL_TEXTURE_2D, texture[6]);
                    //glDisable(GL_TEXTURE_2D);
                    glEnableClientState(GL_NORMAL_ARRAY);
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

                    glBindBufferARB( GL_ARRAY_BUFFER_ARB,playerModel.VBOVertices );
		            glVertexPointer( 3, GL_FLOAT, 0, 0);//(char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer

                    glBindBufferARB( GL_ARRAY_BUFFER_ARB, playerModel.VBOTexCoords );
		            glTexCoordPointer(2, GL_FLOAT, 0, 0 );

		            glBindBufferARB( GL_ARRAY_BUFFER_ARB, playerModel.VBONormals );
		            glNormalPointer( GL_FLOAT, 0, 0 );		// Set The TexCoord Pointer To The TexCoord Buffe

                    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB,playerModel.EBOTris );

                    glDrawElements(GL_TRIANGLES,playerModel.triCount*3,GL_UNSIGNED_INT,NULL);

                    glDisableClientState( GL_VERTEX_ARRAY );
                    glDisableClientState( GL_NORMAL_ARRAY );

 glPopMatrix();

////////////////////Beginning of projectile rendering/////////////////////////////////////////////////////////////////////////////////
for(int i = 0; i < playerShots.size(); i++)
{
    if(playerShots.at(i))
    {
        glPushMatrix ();

            glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();

            if(1)
            perspectiveGL( 45, 1.33333333, 0.1f, 1000.0f );

            glRotatef (90.0, 1.0f, 0.0f, 0.0f);


                glRotatef (mouseRotY*0.5, 180.0f, 0.0f, 0.0f);
                glRotatef (mouseRotY*0.5, 1.0f, 0.0f, 0.0f);
                glRotatef (mouseRotX, 0.0f, 0.0f, 1.0f);



                 glTranslatef (-xpos,-zpos,-ypos);


               glActiveTexture(GL_TEXTURE0);
               //glBindTexture(GL_TEXTURE_2D, player->texture [i]);
               //glDisable(GL_TEXTURE_2D);
              glEnableClientState(GL_NORMAL_ARRAY);
              glEnableClientState(GL_VERTEX_ARRAY);
              glEnableClientState(GL_TEXTURE_COORD_ARRAY);

                   const dReal * vel;
                   const dReal * angvel;


                   if(playerShots.at(i)->geom)
                   dGeomGetQuaternion(playerShots.at(i)->geom,quat);

                   //g = playerShots.at[i].bd.getPosition();
                   if(playerShots.at(i)->body)
                   g = dBodyGetPosition(playerShots.at(i)->body);

                  // vel = dBodyGetLinearVel(playerShots.at(i)->body);
                  // angvel = dBodyGetAngularVel(playerShots.at(i)->body);

                  // float vmag = vel[0]*vel[0] + vel[1]*vel[1] + vel[2]*vel[2];
                   //float amag = angvel[0]*angvel[0] + angvel[1]*angvel[1] + angvel[2]*angvel[2];

                   W = quat[0];
                   X = quat[1];
                   Y = quat[2];
                   Z = quat[3];

                   float sc = sqrt(X*X + Y*Y + Z*Z);

                   axis[0] = X/sc;
                   axis[2] = Y/sc;
                   axis[1] = Z/sc;
                   theta = acos(W)*2.0f;
                   //const GLfloat *transMat = (mat[0],mat[4],mat[8],-0.05*g[0],
                   //                  mat[1],mat[5],mat[9],-0.05*g[1],
                   //                  mat[2],mat[6],mat[10],-0.05*g[2]);
                    theta /= piover180;


                    if(i == 5)
                    XProd = crossProduct2D(g[0],g[1], xpos,zpos);

                   glTranslatef(-1.0*g[0],-1.0*g[1],-1.0*g[2]);
                   glRotatef(theta,axis[0],axis[2],axis[1]);


             glPushMatrix();
             glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();


                glRotatef(-theta,axis[0],axis[2],axis[1]);
                glTranslatef(1.0*g[0],1.0*g[1],1.0*g[2]) ;


                 glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
               	// Position The Light



              glPopMatrix();



                   glBindBufferARB( GL_ARRAY_BUFFER_ARB,shotModel.VBOVertices );
		           glVertexPointer( 3, GL_FLOAT, 0, 0);//(char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer

                   glBindBufferARB( GL_ARRAY_BUFFER_ARB, shotModel.VBOTexCoords );
		           glTexCoordPointer(2, GL_FLOAT, 0, 0 );

		           glBindBufferARB( GL_ARRAY_BUFFER_ARB, shotModel.VBONormals );
		           glNormalPointer( GL_FLOAT, 0, 0 );		// Set The TexCoord Pointer To The TexCoord Buffe

                   glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, shotModel.EBOTris );
                  //glDrawArrays( GL_TRIANGLES, 0, player->modelIndex [i]->vertCount);
                  //glDrawElements(GL_TRIANGLES,player->modelIndex [i]->triCount*3,GL_UNSIGNED_INT,NULL);
                  // glDrawArrays( GL_TRIANGLES, 0, modelArray[modelArrayIndex].vertCount);
                  //glDrawElements(GL_TRIANGLES,modelArray[modelArrayIndex].triCount*3,GL_UNSIGNED_INT,NULL);
                  glDrawElements(GL_TRIANGLES,shotModel.triCount*3,GL_UNSIGNED_INT,NULL);

                glDisableClientState( GL_VERTEX_ARRAY );
                glDisableClientState( GL_NORMAL_ARRAY );

            glPopMatrix();
    }
}

             frmCnt++;
           SwapBuffers (hDC);

           }
else skipframes--;
            mouseMove = false;
            pseudoMutex = false;
           // key = -1;
            //if(theta < 1.0f)
            //theta += 0.1f;
            //else
            //theta = 0.0f;

           // Sleep (1);
        }
    }


    KillFont();
    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK
WndProc (HWND hWnd, UINT message,
         WPARAM wParam, LPARAM lParam)
{
char three [3];
char vert  [9] = "   .vert";
char frag [9] = "   .frag";
string jnum;
    //SetCursorPos(640,480);
    switch (message)
    {

    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;


    case WM_KEYDOWN:

        if(!inputDone && inputBufferCursor < 20 && wParam != VK_BACK )
        {
            if(wParam == 0x6E)
            keyInputBuffer[inputBufferCursor] = '.';
            else
            keyInputBuffer[inputBufferCursor] =(TCHAR) wParam;
            inputBufferCursor++;
        }

        //if(inputBufferCursor >= 20)
      //  {
      //      inputBufferCursor = 0;
      //  }

        switch (wParam)
        {
        case VK_ESCAPE:
             key = -1;
            PostQuitMessage(0);
            return 0;
        case VK_W:
                //up+=0.1;
                if(inputDone)
                {
                    key = 1;
              //  xpos -= (float)sin(heading*piover180) * 0.05f;
              //  zpos -= (float)cos(heading*piover180) * 0.05f;
                //playerbody->addForce(-100.0*sin(piover180*mouseRotX),-100.0*cos(piover180*mouseRotX),0.0);

                }
              //playerbody->addRelForce(0.0,100.0,0.0);

                return 0;
        case VK_S:

                if(inputDone)
                {
                    key = 0;
                //up-=0.1;
               // xpos += (float)sin(heading*piover180) * 0.05f;
               // zpos += (float)cos(heading*piover180) * 0.05f;
               //playerbody->addForce(100.0*sin(piover180*mouseRotX),100.0*cos(piover180*mouseRotX),0.0);
                }
               //playerbody->addRelForce(0.0,-100.0,0.0);

                return 0;
        case 65://VK_A:

                if(inputDone)
                {
                    key = 65;
                //up-=0.1;
               // xpos += (float)sin(heading*piover180) * 0.05f;
               // zpos += (float)cos(heading*piover180) * 0.05f;
               //playerbody->addForce(100.0*sin(piover180*mouseRotX),100.0*cos(piover180*mouseRotX),0.0);
                }
               //playerbody->addRelForce(0.0,-100.0,0.0);

                return 0;
        case 68://VK_D:

                if(inputDone)
                {
                    key = 68;
                //up-=0.1;
               // xpos += (float)sin(heading*piover180) * 0.05f;
               // zpos += (float)cos(heading*piover180) * 0.05f;
               //playerbody->addForce(100.0*sin(piover180*mouseRotX),100.0*cos(piover180*mouseRotX),0.0);
                }
               //playerbody->addRelForce(0.0,-100.0,0.0);

                return 0;
        case VK_SHIFT:
                 key = -1;
             //  if (persp)
              //    persp = false;
             //   else if(!persp)
              //    persp = true;

                //rate += 0.0000000001;

               addBlockMech (player);


                return 0;
        case VK_UP:

                  key = 2;

                   return 0;

        case VK_DOWN:

                  key = 77;

                return 0;

        case VK_RIGHT:

                  key = 78;

                return 0;


        case 89: //shift

                key = 3;
                return 0;

        case 88:

                if(!persp)
                persp = true;
                else
                persp = false;

                return 0;

        case 86:


               if(playerInteraction->inHand != LEFT)
               key = 69;
               else
                for(int i = 0; i < player->blockNum; i++)
                {
                    if( player->blockCarrying [i])
                    {
                        player->blockCarrying [i] = false;
                        player->mechbody[i]->enable();
                    }

                    playerInteraction->setHand(EMPTY);
                }


                return 0;
        case 74:



        for(int i = 0; i < player->blockNum; i++)
        {
            if( player->blockIntersect[i] == true)
            {

                    if(!player->blockSelected [i])
                    {
                        player->blockSelected [i] = true;

                        if(!joined1)
                        {
                            player->blockJoint1[i] = true;
                            joined1 = player->mechbody[i]->id();
                            jointID1 = i;
                        }
                        else if(!joined2)
                        {
                            player->blockJoint1[i] = true;
                            joined2 = player->mechbody[i]->id();
                            jointID2 = i;
                        }
                        else
                        {
                            joined1 = NULL;
                            joined2 = NULL;
                            jointID1 = -1;
                            jointID2 = -1;
                        }
                    }
                    else
                    {
                        player->blockSelected [i] = false;
                    //dBodySetGravityMode(player->mechbody [i]->id(),0);
                   // player->mechbody [i]->setPosition(-xpos + 3.0*sin(piover180*(mouseRotX+10)),-zpos + 3.0*cos(piover180*(mouseRotX+10)),3.5);
                   // handJoint->attach(hand->id(),player->mechbody [i]->id());
                   // handJoint->set();



             //player->mechbody [i]->addForce(0.0,0.0,100000.0);
            }
            }
        }


                return 0;

            case 73:

                const dReal * start;
                const dReal * end;


                if(player->jointNum < 50)
                {

                    switch(jointCreateType)
                    {

                    case JFIXED:
                                player->mechJoints[player->jointNum] = dJointCreateFixed(world,0);
                                dJointAttach(player->mechJoints[player->jointNum],joined1,joined2);
                                dJointSetFixed(player->mechJoints[player->jointNum]);
                                joined1 = NULL;
                                joined2 = NULL;

                                player->jointID[player->jointNum][0] = jointID1;
                                player->jointID[player->jointNum][1] = jointID2;

                                player->jointType[player->jointNum] = JFIXED;

                                player->jointNum++;
                                //if(from_string<int>(num, std::string(jnum), std::dec))
                                diagnosticString = "joint " + jnum + " created as fixed joint";

                                break;
                     case JBALL:
                                player->mechJoints[player->jointNum] = dJointCreateBall(world,0);
                                dJointAttach(player->mechJoints[player->jointNum],joined1,joined2);

                                start = dBodyGetPosition(joined1);
                                end = dBodyGetPosition(joined2);
                                float midPointX = (start[0] + end[0])*0.5;
                                float midPointY = (start[1] + end[1])*0.5;
                                float midPointZ = (start[2] + end[2])*0.5;
                                dJointSetBallAnchor(player->mechJoints[player->jointNum],midPointX,midPointY,midPointZ);
                                joined1 = NULL;
                                joined2 = NULL;

                                player->jointID[player->jointNum][0] = jointID1;
                                player->jointID[player->jointNum][1] = jointID2;

                                player->jointType[player->jointNum] = JBALL;

                                player->jointNum++;
                                //if(from_string<int>(player->jointNum, std::string(jnum), std::dec))
                                diagnosticString = "joint " + jnum + " created as ball joint";
                                break;
                     case JHINGE1:
                                player->mechJoints[player->jointNum] = dJointCreateBall(world,0);
                                dJointAttach(player->mechJoints[player->jointNum],joined1,joined2);

                                start = dBodyGetPosition(joined1);
                                end = dBodyGetPosition(joined2);
                                float midPointXH = (start[0] + end[0])*0.5;
                                float midPointYH = (start[1] + end[1])*0.5;
                                float midPointZH = (start[2] + end[2])*0.5;
                                dJointSetHingeAnchor(player->mechJoints[player->jointNum],midPointXH,midPointYH,midPointZH);
                                dJointSetHingeAxis(player->mechJoints[player->jointNum],
                                                sin(piover180*mouseRotX),cos(piover180*mouseRotX),sin(piover180*(-mouseRotY)));
                                joined1 = NULL;
                                joined2 = NULL;

                                player->jointID[player->jointNum][0] = jointID1;
                                player->jointID[player->jointNum][1] = jointID2;

                                player->jointType[player->jointNum] = JHINGE1;

                                player->jointNum++;
                                //if(from_string<int>(player->jointNum, std::string(jnum), std::dec))
                                diagnosticString = "joint " + jnum + " created as hinge1 joint";
                                break;
                     case JHINGE2:
                                break;
                     case JUNIVERSAL:
                                break;
                     case JSLIDER:
                                player->mechJoints[player->jointNum] = dJointCreateSlider(world,0);
                                dJointAttach(player->mechJoints[player->jointNum],joined1,joined2);

                                start = dBodyGetPosition(joined1);
                                end = dBodyGetPosition(joined2);
                                float rX = start[0] - end[0];
                                float rY = start[1] - end[1];
                                float rZ = start[2] - end[2];
                                dJointSetSliderAxis(player->mechJoints[player->jointNum],rX,rY,rZ);
                                joined1 = NULL;
                                joined2 = NULL;

                                player->jointID[player->jointNum][0] = jointID1;
                                player->jointID[player->jointNum][1] = jointID2;

                                player->jointType[player->jointNum] = JSLIDER;

                                player->jointNum++;
                                //if(from_string<int>(player->jointNum, std::string(jnum), std::dec))
                                diagnosticString = "joint " + jnum + " created as slider joint";
                                break;
                    };
                }

                return 0;

        case 75://K

            if(inputDone)
            {
               for(int p = 0; p < inputBufferCursor; p++)
                aname.push_back(keyInputBuffer[p]);

                three[0] = keyInputBuffer[0];
                three[1] = keyInputBuffer[1];
                three[2] = keyInputBuffer[2];


                //meshLoad(modelArray[modelArrayIndex], "dog.osg");
                 for(int i = 0; i < modelArrayIndex; i++)
                    {
                        if(modelNames[0][i] == keyInputBuffer[0] &&
                           modelNames[1][i] == keyInputBuffer[1] &&
                           modelNames[2][i] == keyInputBuffer[2])
                            return 0;
                    }

                     modelNames[0][modelArrayIndex] = keyInputBuffer[0];
                     modelNames[1][modelArrayIndex] = keyInputBuffer[1];
                     modelNames[2][modelArrayIndex] = keyInputBuffer[2];



                meshLoad(modelArray[modelArrayIndex], three);
                modelArrayIndex++;

            }
                return 0;

        case 76://L

            if(inputDone)
            {
                three[0] = keyInputBuffer[0];
                three[1] = keyInputBuffer[1];
                three[2] = keyInputBuffer[2];

                /*t1 = AllocateTextureBuffer( 512,512, 4 );					// Get An Image Structure
                if (ReadTextureData(three,t1)==0)				// Fill The Image Structure With Data
                {															// Nothing Read?
                    MessageBox(NULL,"Could Not Read Image Data","TEXTURE ERROR",MB_OK | MB_ICONINFORMATION);
                    return FALSE;
                }*/

                for(int i = 0; i < textIndex; i++)
                    {
                        if(textureNames[0][i] == keyInputBuffer[0] &&
                           textureNames[1][i] == keyInputBuffer[1] &&
                           textureNames[2][i] == keyInputBuffer[2])
                            return 0;
                    }

                 textureNames[0][textIndex] = keyInputBuffer[0];
                 textureNames[1][textIndex] = keyInputBuffer[1];
                 textureNames[2][textIndex] = keyInputBuffer[2];
                 BuildTexture (three, texture[textIndex]);											// Load The Texture Map Into Texture Memory
                 textIndex++;
                //DeallocateTexture( t1 );									// Clean Up Image Memory Because Texture Is
            }
                return 0;

        case 77://M

                 if(inputDone)
                {
                    vert[0] = keyInputBuffer[0];
                    vert[1] = keyInputBuffer[1];
                    vert[2] = keyInputBuffer[2];

                    frag[0] = keyInputBuffer[0];
                    frag[1] = keyInputBuffer[1];
                    frag[2] = keyInputBuffer[2];

                    for(int i = 0; i < shaderIndex; i++)
                    {
                        if(shaderNames[0][i] == keyInputBuffer[0] &&
                           shaderNames[1][i] == keyInputBuffer[1] &&
                           shaderNames[2][i] == keyInputBuffer[2])
                            return 0;
                    }

                     shaderNames[0][shaderIndex] = keyInputBuffer[0];
                     shaderNames[1][shaderIndex] = keyInputBuffer[1];
                     shaderNames[2][shaderIndex] = keyInputBuffer[2];
                     newShaders(vertexPrograms[shaderIndex],fragmentPrograms[shaderIndex],shaderPrograms[shaderIndex],vert,frag);
                     shaderIndex++;
              // exit(0);
                }
                return 0;

        case 78://n

                //exit(0);
                if(inputDone)
                writeScene(player);

                return 0;

        case 79://o

                //exit(0);
                if(inputDone)
                importScene(player);

                return 0;

        case 80://p

                //exit(0);
                //zColRot;
                if(inputDone)
                playerRot += 1.0;

                return 0;

        case 81://q

                //exit(0);
                if(jointCreateType < 5)
                    jointCreateType++;
                else
                    jointCreateType = 0;

                return 0;
        case 82://r

                if(mouseToggle)
                {
                       mouseToggle = false;
                       ShowCursor(true);
                }
                else
                 {
                       mouseToggle = true;
                       ShowCursor(false);
                 }
                return 0;

        case VK_RETURN: //space bar
                key = 4;
                  if (inputDone)
                  inputDone = false;
                else if(!inputDone)
                  inputDone = true;
                return 0;

         case VK_BACK: //space bar
                key = 5;
               if(inputBufferCursor > 0)
               {
                keyInputBuffer[inputBufferCursor-1] = 0;
                inputBufferCursor--;
               }

                return 0;

        default:
             key = -1;
             //playerbody->setLinearVel(0.0,0.0,0.0);

             return 0;

        }

        case WM_KEYUP:
               key = -1;
        return 0;

        case WM_MOUSEMOVE:
            //SetCursorPos(640,480);
        mouseMove = true;

  	// Check to see if the left button is held down:
  bool leftButtonDown=wParam & MK_LBUTTON;

  // Check if right button down:
  bool rightButtonDown=wParam & MK_RBUTTON;

  	 //mouse handling funtions to determine the change by the user each frame and
				 //warp the cursor back to the center.
            //SetCursorPos(640,480);
   if(leftButtonDown)
   {
       leftDown = true;
        if(!pseudoMutex)
        {
           /*const dReal * f;
           f = dBodyGetPosition(playerbody->id());

           projectile * newShot = (projectile *) malloc(sizeof(projectile));

            dMass m;
            newShot->body = dBodyCreate(world);
            newShot->geom = dCreateSphere(space,0.3);
            dMassSetSphere(&m,1.0,0.3);
		    dMassAdjust (&m, 100.0);
            dBodySetMass( newShot->body,&m);
            dGeomSetBody(newShot->geom,newShot->body);
            dBodySetPosition(newShot->body,f[0],f[1],f[2]);
            dBodySetGravityMode(newShot->body,0);
            const float mg = 200.0;
            //dBodySetLinearVel(newShot->body,mg*sin(piover180*mouseRotX),mg*cos(piover180*mouseRotX),mg*sin(piover180*(-mouseRotY)));

            playerShots.push_back(newShot);*/
        }



        for(int i = 0; i < player->blockNum; i++)
        {
             if(player->blockCarrying[i])
             {
                 player->blockCarrying[i] = false;
                 player->mechbody[i]->enable();
                 dBodyAddForce(player->mechbody [i]->id(),20000000.0*sin(piover180*mouseRotX),20000000.0*cos(piover180*mouseRotX),20000000.0*sin(piover180*(-mouseRotY)));
                 dBodyAddTorque(player->mechbody [i]->id(),2000000.0,2000000.0,2000000.0);

             }

        }

   }
   else leftDown = false;

                 int mY;

				 int delY;

				 int mX;

				 int delX;

                    mY = (short)HIWORD(lParam);

				    delY = (mY - 457);

                    mX = (short)LOWORD(lParam);

                    delX = (mX - 637);


                mouseDelX = delX;//640;
                mouseDelY = delY;//480;

if(rightButtonDown)
   {
        for(int i = 0; i < player->blockNum; i++)
        {
             if(player->blockCarrying[i])
             {

                 //player->blockCarrying[i] = false;

                 player->mechbody[i]->enable();
                 //dBodyAddForce(player->mechbody [i]->id(),20000000.0*sin(piover180*mouseRotX),20000000.0*cos(piover180*mouseRotX),20000000.0*sin(piover180*(-mouseRotY)));
                 dBodyAddTorque(player->mechbody [i]->id(),20000.0*mouseDelX,0.0,20000.0*(mouseDelY - 1));
                 //dBodySetRotation(mat[0],
             }
        }
   }
else
{
 for(int i = 0; i < player->blockNum; i++)
             if(player->blockCarrying[i])
              {
                   player->mechbody[i]->disable();
                   //dBodySetAngularVel(player->mechbody[i]->id(),0,0,0);
              }



                float oldMag = (delX - mouseDelX)*(delX - mouseDelX) +
                            (delY - mouseDelY)*(delY - mouseDelY);

                float newMag = delX*delX + delY*delY;
  //if(mouseDelX == 640 && mouseDelY == 480 )
            if(newMag > oldMag)
            {
              //   if (delX > 0.0 )// && delX < -0.1)

                      mouseRotY += 0.5f*delY;
              //   else
              //   if (delX < 0.0)
                 //   mouseRotX += -0.5*delX;


			   // if (delY > 0.0 )//&& delY < -0.1)
                     heading -= 0.5*delX;
                     mouseRotX = heading;//-= 0.5*delX;
               // else
              //  if (delY < 0.0)
                  //  mouseRotY += 0.5*delY;
            }

            //if(mX > 650 && mX < 630 && mY > 490 && mY < 470 )
               // SetCursorPos(640 ,480);
}
    return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

/*******************
 * Enable OpenGL
 *
 *******************/

void
EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);
    nhDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    // create and enable the render context (RC)
    *hRC = wglCreateContext( *hDC );
    nhRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
    BuildFont("Lucida Console");
/*
   DEVMODE dmScreenSettings;											// Device Mode
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));					// Make Sure Memory Is Cleared
	dmScreenSettings.dmSize				= sizeof (DEVMODE);				// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth		= 800;						// Select Screen Width
	dmScreenSettings.dmPelsHeight		= 600;						// Select Screen Height
	dmScreenSettings.dmBitsPerPel		= 32;					// Select Bits Per Pixel
	dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN);
*/
	WORD GammaArray[3][256];

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * (162 + 128);

			if (iArrayValue > 65535)
				iArrayValue = 65535;

			GammaArray[0][iIndex] = (WORD)iArrayValue;
			GammaArray[1][iIndex] = (WORD)iArrayValue;
			GammaArray[2][iIndex] = (WORD)iArrayValue;

		}

		//Set the GammaArray values into the display device context.
		SetDeviceGammaRamp(nhDC, GammaArray);

	// Establish the high contrast structure
HIGHCONTRAST strHighContrast;
// Clear the structure
ZeroMemory(&strHighContrast, sizeof(HIGHCONTRAST));
// request that the confirm hotkey dialog appears after high contrast is set by hotkey
strHighContrast.dwFlags = HCF_CONFIRMHOTKEY;
// set the size of the structure
strHighContrast.cbSize = sizeof(HIGHCONTRAST);
// specify the name of the high contrast scheme
strHighContrast.lpszDefaultScheme = "basic scheme";
// set the system high contrast value
SystemParametersInfo(SPI_SETHIGHCONTRAST,
sizeof(HIGHCONTRAST), &strHighContrast,  0);
//
}


/******************
 * Disable OpenGL
 *
 ******************/

void
DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    	const GLdouble pi = 3.1415926535897932384626433832795;

        GLdouble fW, fH;

        fH = tan( (fovY / 2) / 180 * pi ) * zNear;

        fH = tan( fovY / 360 * pi ) * zNear;

        fW = fH * aspect;

        glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void sceneLoad()
{
	persp = true;
    key = -1;
	vertCount = 0;
	triCount = 0;
	quadCount = 0;
	const int START = 0;
	const int VERTEX = 1;
	const int NORMAL = 2;
	const int TRIS = 3;
	const int QUADS = 4;
	int state = START;
	bool read = false;
	float vert;
	int link;
	string text;
	int n = 0;
	vertCount = 0;
}

void writeScene(Mech *play)
{
   ofstream VertexROut("shadeout", ios::out);
    if (VertexROut.is_open())
   {

    // VertexOut << "-shaders\n";
     for(int i = 0; i < shaderIndex; i++)
    {
        VertexROut << shaderNames[0][i] << shaderNames[1][i] << shaderNames[2][i] << "\n";
    }
}

VertexROut.close();

     ofstream VertexMOut("modelout", ios::out);
    if (VertexMOut.is_open())
   {
     for(int i = 0; i < modelArrayIndex; i++)
    {
       VertexMOut << modelNames[0][i] << modelNames[1][i] << modelNames[2][i]  << "\n";
    }
   }
   VertexMOut.close();

    ofstream VertexTOut("textureout", ios::out);
    if (VertexTOut.is_open())
   {
     for(int i = 4; i < textIndex; i++)
    {
       VertexTOut << textureNames[0][i] << textureNames[1][i] << textureNames[2][i]  << "\n";
    }
   }
   VertexTOut.close();

   ofstream VertexOut("sceneout", ios::out);
   const dReal *f;
   float X,Y,Z,W;


   // VertexOut << "-bodydata\n";
    for(int i = 5; i < play->blockNum; i++)
    {
        f = play->mechbody[i]->getPosition();
        X = f[0]; Y = f[1]; Z = f[2];
       // VertexOut << "body #" << i << "\n";
       // VertexOut << "position\n";
        VertexOut << X <<"\n";
        VertexOut << Y <<"\n";
        VertexOut << Z <<"\n";

        f = play->mechbody[i]->getQuaternion();
        X = f[0]; Y = f[1]; Z = f[2]; W =f [3];
     //   VertexOut << "rotation\n";
        VertexOut << X <<"\n";
        VertexOut << Y <<"\n";
        VertexOut << Z <<"\n";
        VertexOut << W <<"\n";
        VertexOut << play->modelID[i] <<"\n";
        VertexOut << play->shaderID[i] <<"\n";
        VertexOut << play->textID[i];

        if(i != play->blockNum - 1)
        VertexOut << "\n";

    }
    VertexOut.close();

    ofstream VertexJOut("jointout", ios::out);

    for(int i = 3; i < play->jointNum; i++)
    {
        VertexJOut << play->jointType[i] <<"\n";
        VertexJOut << play->jointID[i][0] <<"\n";
        VertexJOut << play->jointID[i][1];
        if(i != play->blockNum - 1)
        VertexJOut << "\n";

    }
    VertexJOut.close();
}


void importScene(Mech *play)
{
   ifstream VertexIn("sceneout");
   ifstream VertexRIn("shadeout");
   ifstream VertexMIn("modelout");
   ifstream VertexTIn("textureout");
   ifstream VertexJIn("jointout");
   ofstream VertexOut("diagnostic", ios::out);
   float pos[3];
   float quatern[4];
   string text;
   int mod;
   int shd;
   int txt;
   int typ;
   int jt1;
   int jt2;
   int state = 0;
   const dReal *start;
   const dReal *end;


   if(VertexRIn.is_open())
   while(!VertexRIn.eof())
    {
          getline (VertexRIn,text);
          if(text.compare(""))
          {
            char vert [9] = "   .vert";
            char frag [9] = "   .frag";

            vert[0] = text[0];
            vert[1] = text[1];
            vert[2] = text[2];

            frag[0] = text[0];
            frag[1] = text[1];
            frag[2] = text[2];

            newShaders(vertexPrograms[shaderIndex],fragmentPrograms[shaderIndex],shaderPrograms[shaderIndex],vert,frag);
            shaderIndex++;
          }
    }

    VertexRIn.close();

   if (VertexMIn.is_open())
    while(! VertexMIn.eof())
    {
        getline (VertexMIn,text);
        if(text.compare(""))
        {
            meshLoad(modelArray[modelArrayIndex],text.substr(0,3));
            modelArrayIndex++;
        }
    }

    VertexMIn.close();

    if (VertexTIn.is_open())
    while(! VertexTIn.eof())
    {
        getline (VertexTIn,text);
        if(text.compare(""))
        {
             char  * txtnm;

            txtnm[0] = text[0];
            txtnm[1] = text[1];
            txtnm[2] = text[2];

             VertexOut <<
             BuildTexture (txtnm, texture[textIndex]);	// Load The Texture Map Into Texture Memory

           textIndex++;
        }

    }

    VertexTIn.close();

   if (VertexIn.is_open())
   while(! VertexIn.eof() )
    {

            for(int n = 0; n  < 3; n++)
            {

                getline (VertexIn,text);
                if(from_string<float>(pos[n], std::string(text), std::dec))
                {

                }

            }

            for(int n = 0; n  < 4; n++)
            {

                getline (VertexIn,text);
                if(from_string<float>(quatern[n], std::string(text), std::dec))
                {

                }

            }

            getline (VertexIn,text);
            if(from_string<int>(mod, std::string(text), std::dec))
                {

                }

            getline (VertexIn,text);
            if(from_string<int>(shd, std::string(text), std::dec))
                {

                }

            getline (VertexIn,text);
            if(from_string<int>(txt, std::string(text), std::dec))
                {

                }

            dMass m;

            int blockNum = play->blockNum;

            //addBlockMech (play);

             //int btype = createBody(play, modelArray[mod], 1000*MECHMASS,pos[0],pos[1],pos[2], world, space);
           /* if(play->blockNum < 2000)
            {
                play->blockIntersect[blockNum] = false;
                play->mechbody[blockNum] = new dBody();
                play->mechID[blockNum] = play->mechbody[blockNum]->id();
                //play->mechboxes[blockNum] = new dBox();
                /play->mechGeoms[blockNum] = dCreateBox(space,1.5,1.5,1.5);
                play->mechbody[blockNum]->create(world);
                play->mechbody[blockNum]->setPosition (pos[0],pos[1],pos[2]);
                dMassSetBox (&m,1,1.5,1.5,1.5);
                dMassAdjust (&m, 1000*MECHMASS);
                play->mechbody[blockNum]->setMass (&m);
                play->modelIndex[blockNum] = &modelArray[mod];
                play->modelID[blockNum] = mod;
                play->shader[blockNum] = shaderPrograms[shd];
                play->shaderID[blockNum] = shd;
                play->texture[blockNum] = texture[txt];
                play->textID[blockNum] = txt;
                play->mechbody[blockNum]->setMass (&m);
                //play->mechboxes[blockNum]->create(space,1.5,1.5,1.5);
                dGeomSetBody(play->mechGeoms[blockNum],play->mechbody[blockNum]->id());
                //////play->mechboxes[blockNum]->setBody (play->mechbody[blockNum]->id());
                play->mechbody[blockNum]->setQuaternion (quatern);
                play->blockNum++;
            }*/


		//player->blockCarrying[blockNum] = true;


      //  play->mechbody[play->blockNum]->setPosition(pos[0],pos[1],pos[2]);
      //  play->mechbody[play->blockNum]->setQuaternion(quatern);

        }

        int jointNum = play->jointNum;

    if (VertexJIn.is_open())
   while(! VertexJIn.eof() )
    {
         getline (VertexJIn,text);
            if(from_string<int>(typ, std::string(text), std::dec))
                {

                }

            getline (VertexJIn,text);
            if(from_string<int>(jt1, std::string(text), std::dec))
                {

                }

            getline (VertexJIn,text);
            if(from_string<int>(jt2, std::string(text), std::dec))
                {

                }

        if(player->jointNum < 50)
                {

                    switch(typ)
                    {

                    case JFIXED:
                                play->mechJoints[jointNum] = dJointCreateFixed(world,0);
                                dJointAttach(play->mechJoints[jointNum],play->mechbody[jt1]->id(),play->mechbody[jt2]->id());
                                dJointSetFixed(play->mechJoints[jointNum]);

                                play->jointID[jointNum][0] = jt1;
                                play->jointID[jointNum][1] = jt2;

                                play->jointType[jointNum] = JFIXED;

                                play->jointNum++;



                                break;
                     case JBALL:
                                play->mechJoints[jointNum] = dJointCreateBall(world,0);
                                dJointAttach(play->mechJoints[jointNum],play->mechbody[jt1]->id(),play->mechbody[jt2]->id());


                                start = dBodyGetPosition(play->mechbody[jt1]->id());
                                end = dBodyGetPosition(play->mechbody[jt2]->id());
                                float midPointX = (start[0] + end[0])*0.5;
                                float midPointY = (start[1] + end[1])*0.5;
                                float midPointZ = (start[2] + end[2])*0.5;
                                dJointSetBallAnchor(play->mechJoints[jointNum],midPointX,midPointY,midPointZ);

                                play->jointID[jointNum][0] = jt1;
                                play->jointID[jointNum][1] = jt2;

                                play->jointType[jointNum] = JBALL;

                                play->jointNum++;
                                //if(from_string<int>(player->jointNum, std::string(jnum), std::dec))

                                break;
                     case JHINGE1:
                                play->mechJoints[jointNum] = dJointCreateBall(world,0);
                                dJointAttach(play->mechJoints[jointNum],joined1,joined2);

                                start = dBodyGetPosition(joined1);
                                end = dBodyGetPosition(joined2);
                                float midPointXH = (start[0] + end[0])*0.5;
                                float midPointYH = (start[1] + end[1])*0.5;
                                float midPointZH = (start[2] + end[2])*0.5;
                                dJointSetHingeAnchor(play->mechJoints[jointNum],midPointXH,midPointYH,midPointZH);
                                dJointSetHingeAxis(play->mechJoints[jointNum],
                                                sin(piover180*mouseRotX),cos(piover180*mouseRotX),sin(piover180*(-mouseRotY)));

                                play->jointID[jointNum][0] = jt1;
                                play->jointID[jointNum][1] = jt2;

                                play->jointType[jointNum] = JHINGE1;

                                play->jointNum++;
                                //if(from_string<int>(player->jointNum, std::string(jnum), std::dec))

                                break;
                     case JHINGE2:
                                break;
                     case JUNIVERSAL:
                                break;
                     case JSLIDER:
                                play->mechJoints[jointNum] = dJointCreateSlider(world,0);
                                dJointAttach(play->mechJoints[jointNum],play->mechbody[jt1]->id(),play->mechbody[jt2]->id());

                                start = dBodyGetPosition(play->mechbody[jt1]->id());
                                end = dBodyGetPosition(play->mechbody[jt2]->id());
                                float rX = start[0] - end[0];
                                float rY = start[1] - end[1];
                                float rZ = start[2] - end[2];
                                dJointSetSliderAxis(play->mechJoints[jointNum],rX,rY,rZ);

                                play->jointID[jointNum][0] = jt1;
                                play->jointID[jointNum][1] = jt2;

                                play->jointType[jointNum] = JSLIDER;

                                play->jointNum++;
                                //if(from_string<int>(player->jointNum, std::string(jnum), std::dec))

                                break;
                    };
                }
    }
    VertexJIn.close();
}

void meshLoad(mesh &model, string fileName)
{
    model.normCount = 0;
	model.vertCount = 0;
	model.triCount = 0;
	model.quadCount = 0;
	const int START = 0;
	const int VERTEX = 1;
	const int NORMAL = 2;
	const int TRIS = 3;
	const int QUADS = 4;
	const int TEXCOORDS = 5;
	int state = START;
	bool read = false;
	float vert;
	int link;
	string text;
	int n = 0;
	int texCount = 0;



    ifstream VertexIn (fileName.c_str());//"outsphere.osg");
    ofstream VertexOut("gl", ios::out);


	if (VertexIn.is_open())
   {
    while (! VertexIn.eof() )
    {
      getline (VertexIn,text,' ');


      if(!text.compare("VertexArray"))
      {
          state = VERTEX;
          VertexOut << "VERTLIST" << std::endl;
      }else if(!text.compare("NormalArray"))
      {
          state = NORMAL;
          VertexOut << "NORMLIST" << std::endl;
      }
      else if(!text.compare("QUADS"))
      {
           state = QUADS;
           read = false;
           VertexOut << "QUADLIST" << std::endl;
      }
       else if(!text.compare("TRIANGLES"))
      {
           state = TRIS;
           read = false;
           VertexOut << "TRILIST" << std::endl;
      }
       else if(!text.compare("TexCoordArray"))
      {
           state = TEXCOORDS;
           read = false;
           VertexOut << "TEXLIST" << std::endl;
      }


      if(state == VERTEX && !text.compare("{\n"))
      read = true;
      else if(state == VERTEX && !text.compare("}\n"))
      {
          read = false;
          n=0;
         // state = NORMAL;
      }

      if(state == NORMAL && !text.compare("{\n"))
      read = true;
      else if(state == NORMAL && !text.compare("}\n"))
      {
          read = false;
          n=0;
          //state = QUADS;
      }

      if(state == TRIS && !text.compare("{\n"))
      read = true;
      else if(state == TRIS && !text.compare("}\n"))
      {
          read = false;
          n=0;
          //state = TRIS;
      }

      if(state == QUADS && !text.compare("{\n"))
      read = true;
      else if(state == QUADS && !text.compare("}\n"))
      {
          read = false;
          n=0;
          //state = TRIS;
      }

      if(state == TEXCOORDS && !text.compare("{\n"))
      read = true;
      else if(state == TEXCOORDS && !text.compare("}\n"))
      {
          read = false;
          n=0;
          //state = TRIS;
      }

      if(state == VERTEX && read && text.compare("\n"))//*/
         if(from_string<float>(vert, std::string(text), std::dec))
         {

                 if (n == 3)
                 {
                   n = 0;
                   model.vertCount++;
                 }

                model.VertexArray[model.vertCount][n] = -1.0*vert;

                 //VertexOut << vert << "\n";
                 VertexOut << text << std::endl;
                 n++;

         }
        // n=0;
         if(state == NORMAL && read && text.compare("\n"))//*/
         if(from_string<float>(vert, std::string(text), std::dec))
         {

                 if (n == 3)
                 {
                   n = 0;
                   model.normCount++;
                 }

                if(0)//fileName.compare("compile.bzm"))
                {
                    model.NormalArray[model.normCount][n] = vert;
                    VertexOut << -vert << std::endl;
                }

                else
               {
                    model.NormalArray[model.normCount][n] = -vert;
                    VertexOut << text << std::endl;
               }
                 //VertexOut << vert << "\n";

                 n++;

         }

         if(state == TRIS && read && text.compare("\n"))//*/
         if(from_string<int>(link, std::string(text), std::dec))
         {




                 if (n == 3)
                 {
                   n = 0;
                   model.triCount++;
                 }

                 model.triangles[model.triCount][n] = link;

VertexOut << text << std::endl;


                 n++;

                // VertexOut << link << "\n";

         }

        // n=0;
         if(state == QUADS && read && text.compare("\n"))//*/
         if(from_string<int>(link, std::string(text), std::dec))
         {


                 if (n == 4)
                 {
                   n = 0;
                   model.quadCount++;
                 }

                 model.quads[model.quadCount][n] = link;

VertexOut << text << std::endl;
                 n++;


                // VertexOut << link << "\n";
                 //n++;
         }

         if(state == TEXCOORDS && read && text.compare("\n"))//*/
         if(from_string<float>(vert, std::string(text), std::dec))
         {
                model.TextureArray[texCount][n] = vert;

                 if (n == 2)
                 {
                   n = 0;
                  texCount++;
                 }



               VertexOut << text << std::endl;
                 n++;


                // VertexOut << link << "\n";
                 //n++;
         }
    }
    VertexIn.close();

  }
  else
    MessageBox(NULL,"Could Not Find Mesh",fileName.c_str(),MB_OK | MB_ICONINFORMATION);

    glGenBuffersARB( 1, &model.VBOVertices);					        // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, model.VBOVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model.vertCount*3*sizeof(float), model.VertexArray, GL_STATIC_DRAW_ARB );


	 glGenBuffersARB( 1, &model.VBOTexCoords);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, model.VBOTexCoords );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model.vertCount*2*sizeof(float), model.TextureArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &model.VBONormals);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, model.VBONormals );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model.vertCount*3*sizeof(float), model.NormalArray, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &model.EBOTris);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.EBOTris );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.triCount*3*sizeof(int), model.triangles, GL_STATIC_DRAW_ARB );

    glGenBuffersARB( 1, &model.EBOQuads);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.EBOQuads );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.quadCount*4*sizeof(int), model.quads, GL_STATIC_DRAW_ARB );


for(int i=0; i < model.vertCount + 1; i++)
{   for(int n=0; n < 3; n++)
    //VertexOut << model.VertexArray[i][n] << " ";
    VertexOut << "\n";
}

for(int i=0; i < model.vertCount + 1; i++)
{   for(int n=0; n < 3; n++)
    //VertexOut << model.NormalArray[i][n] << " ";
    VertexOut << "\n";
}
for(int i=0; i < model.vertCount + 1; i++)
 {  for(int n=0; n < 2; n++)
    VertexOut << model.TextureArray[i][n] << " ";
    VertexOut << "\n";
 }

for(int i=0; i < model.triCount; i++)
 {  for(int n=0; n < 3; n++)
    //VertexOut << model.triangles[i][n] << " ";
    VertexOut << "\n";
 }

model.vertCount+= 1;
model.quadCount += 1;
model.triCount += 1;

for(int i=0; i < model.quadCount; i++)
{   for(int n=0; n < 4; n++)
    //VertexOut << model.quads[i][n] << " ";
    VertexOut << "\n";
}


VertexOut << model.vertCount << " " << model.quadCount;



}


void meshInitializeVBO(mesh &model)
{
    glGenBuffersARB( 1, &model.VBOVertices);					        // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, model.VBOVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model.vertCount*3*sizeof(float), model.VertexArray, GL_STATIC_DRAW_ARB );


	 glGenBuffersARB( 1, &model.VBOTexCoords);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, model.VBOTexCoords );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model.vertCount*2*sizeof(float), model.TextureArray, GL_STATIC_DRAW_ARB );

	 glGenBuffersARB( 1, &model.VBONormals);					             // Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, model.VBONormals );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, model.vertCount*3*sizeof(float), model.NormalArray, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &model.EBOTris);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.EBOTris );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.triCount*3*sizeof(int), model.triangles, GL_STATIC_DRAW_ARB );

    glGenBuffersARB( 1, &model.EBOQuads);					             // Get A Valid Name
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.EBOQuads );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, model.quadCount*4*sizeof(int), model.quads, GL_STATIC_DRAW_ARB );

}

bool linkExists(int x, int y, mesh &model)
{
    for (int i = 0; i < model.linkCount; i++)
    {
         if  ( (model.linkIndex[i][0] == x && model.linkIndex[i][1] == y) ||
               (model.linkIndex[i][0] == y && model.linkIndex[i][1] == x))
               return true;

    }

    return false;
}


void constructSpringMesh(mesh &model)
{
    int visited = 0;
    model.linkCount = 0;
	float d[3];
	float displacement;

    for(int i = 0; i < model.triCount; i++)
            {
                   for (int n = 0; n < 3; n++)
                   {
                     for (int p = 0; p < 3; p ++)

                       if (n < p)
                       {
                         if (!linkExists(model.triangles[i][n],model.triangles[i][p],model))
                         {
                           model.linkIndex[model.linkCount][0] = model.triangles[i][n];
                           model.linkIndex[model.linkCount][1] = model.triangles[i][p];

                           d[0] = model.VertexArray[model.triangles[i][n]][0] - model.VertexArray[model.triangles[i][p]][0];
                           d[1] = model.VertexArray[model.triangles[i][n]][1] - model.VertexArray[model.triangles[i][p]][1];
                           d[2] = model.VertexArray[model.triangles[i][n]][2] - model.VertexArray[model.triangles[i][p]][2];

                           model.linkEquilLength[ model.linkCount] = sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);



                           model.linkCount++;
                         }
                       }


                   }
            }

         for(int i = 0; i < model.quadCount; i++)
            {
                   for (int n = 0; n < 4; n++)
                   {
                     for (int p = 0; p < 4; p ++)

                       if (n < p)
                       {
                         if (!linkExists(model.quads[i][n],model.quads[i][p],model))
                         {
                           model.linkIndex[model.linkCount][0] = model.quads[i][n];
                           model.linkIndex[model.linkCount][1] = model.quads[i][p];

                           d[0] = model.VertexArray[model.quads[i][n]][0] - model.VertexArray[model.quads[i][p]][0];
                           d[1] = model.VertexArray[model.quads[i][n]][1] - model.VertexArray[model.quads[i][p]][1];
                           d[2] = model.VertexArray[model.quads[i][n]][2] - model.VertexArray[model.quads[i][p]][2];

                           model.linkEquilLength[ model.linkCount] = sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);



                           model.linkCount++;
                         }
                       }


                   }
            }
}

void renderModelTris(mesh &model, float scale)
{
          float X,Y,Z;
          for(int i = 0; i < model.triCount; i++)
            {
                  SetCursorPos(640,480);

                  if(key == 1)
                  {
                      xpos -= (float)sin(heading*piover180) * 0.0000005f;
                      zpos -= (float)cos(heading*piover180) * 0.0000005f;
                  }
                  else if(key == 0)
                  {
                //up-=0.1;
                      xpos += (float)sin(heading*piover180) * 0.0000005f;
                      zpos += (float)cos(heading*piover180) * 0.0000005f;
                  }
                  //key = -1;

                   for (int n = 0; n < 3; n++)
                   {
                        SetCursorPos(640,480);
                      // if(scale*VertexArray[quads[i][n]][2] < 0)
                       switch (n)
                       {
                           case 0:
                                  glTexCoord2f(1.0f,1.0f);
                                  break;
                           case 1:
                                  glTexCoord2f(1.0f,0.0f);
                                  break;
                           case 2:
                                  glTexCoord2f(0.0f,1.0f);
                                  break;
                         // case 3:
                          //        glTexCoord2f(0.0f,0.0f);
                          //        break;
                       }

                       X = model.NormalArray[model.triangles[i][n]][0];
                       Y = model.NormalArray[model.triangles[i][n]][1];
                       Z = model.NormalArray[model.triangles[i][n]][2];


                       glColor3f (0.001*i,0.001*i,0.001*i);
                     //  glNormal3f(mat[0]*X + mat[4]*Y + mat[8]*Z,
                        //          mat[1]*X + mat[5]*Y + mat[9]*Z,
                         //         mat[2]*X + mat[6]*Y + mat[10]*Z);

                         glNormal3f(X,Y,Z);

                       X = scale*model.VertexArray[model.triangles[i][n]][0];
                       Y = scale*model.VertexArray[model.triangles[i][n]][1];
                       Z = scale*model.VertexArray[model.triangles[i][n]][2];

                       //glVertex3f(mat[0]*X + mat[4]*Y + mat[8]*Z + scale*g[0],
                       //           mat[1]*X + mat[5]*Y + mat[9]*Z + scale*g[1],
                       //           mat[2]*X + mat[6]*Y + mat[10]*Z + scale*g[2]);


                           glVertex3f(X,Y,Z);
                   }
            }
}



void renderModelQuads(mesh &model, float scale)
{
          for(int i = 0; i < model.quadCount; i++)
            {
                  SetCursorPos(640,480);

                   if(key == 1)
                  {
                      xpos -= (float)sin(heading*piover180) * 0.0000005f;
                      zpos -= (float)cos(heading*piover180) * 0.0000005f;
                  }
                  else if(key == 0)
                  {
                //up-=0.1;
                      xpos += (float)sin(heading*piover180) * 0.0000005f;
                      zpos += (float)cos(heading*piover180) * 0.0000005f;
                  }
                  //key = -1;


                   for (int n = 0; n < 4; n++)
                   {

                       if(mouseToggle)
                       SetCursorPos(640,480);

                     // if(scale*VertexArray[quads[i][n]][0] > 0)
                       switch (n)
                       {
                           case 0:
                                  glTexCoord2f(0.0f,0.0f);
                                  break;
                          case 1:
                                  glTexCoord2f(1.0f,1.0f);
                                  break;
                          case 2:
                                  glTexCoord2f(0.0f,1.0f);
                                  break;
                          case 3:
                                  glTexCoord2f(1.0f,0.0f);
                                  break;
                       }

                       glColor3f (0.001*i,0.001*i,0.001*i);
                       glNormal3f(model.NormalArray[model.quads[i][n]][0],
                                  model.NormalArray[model.quads[i][n]][1],
                                  model.NormalArray[model.quads[i][n]][2]);

                       glVertex3f(scale*model.VertexArray[model.quads[i][n]][0],
                                  scale*model.VertexArray[model.quads[i][n]][1],
                                  scale*model.VertexArray[model.quads[i][n]][2]);
                   }
            }
}

bool IsExtensionSupported( char* szTargetExtension )
{
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	unsigned char *pszWhere, *pszTerminator;

	// Extension names should not have spaces
	pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' );
	if( pszWhere || *szTargetExtension == '\0' )
		return false;

	// Get Extensions String
	pszExtensions = glGetString( GL_EXTENSIONS );

	// Search The Extensions String For An Exact Copy
	pszStart = pszExtensions;
	for(;;)
	{
		pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension );
		if( !pszWhere )
			break;
		pszTerminator = pszWhere + strlen( szTargetExtension );
		if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' )
			if( *pszTerminator == ' ' || *pszTerminator == '\0' )
				return true;
		pszStart = pszTerminator;
	}
	return false;
}

float InvSqrt(float x)
{
float xhalf = 0.5f*x;
int i = *(int*)&x;
// get bits for floating value
i = 0x5f3759df - (i>>1); // gives initial guess y
x = *(float*)&i;
// convert bits back to float
x = x*(0.75f-xhalf*x*x); // Newton step, repeating increases accuracy
return x;
}

void addBlockMech (Mech *PlayerMech)
{
      dMass m;

      int btype = createBody(PlayerMech, modelArray[modelArrayIndex - 1 ], 1000*MECHMASS, -xpos, -zpos, 5, world, space);
      if(PlayerMech->blockNum < 2000 && !btype)
      {
        int blockNum = PlayerMech->blockNum;
        PlayerMech->blockIntersect[blockNum] = false;
        PlayerMech->mechbody[blockNum] = new dBody();
        PlayerMech->mechID[blockNum] = PlayerMech->mechbody[blockNum]->id();
		//PlayerMech->mechboxes[blockNum] = new dBox();
		PlayerMech->mechbody[blockNum]->create(world);
		PlayerMech->mechGeoms[blockNum] = dCreateBox(space,1.5,1.5,1.5);
		PlayerMech->mechbody[blockNum]->setPosition (-xpos,-zpos,5);
		dMassSetBox (&m,1,1.5,1.5,1.5);
		dMassAdjust (&m, 1000*MECHMASS);
		PlayerMech->mechbody[blockNum]->setMass (&m);
		//PlayerMech->mechboxes[blockNum]->create(space,1.5,1.5,1.5);
		//dGeomSetBody(geom,PlayerMech->mechbody[blockNum]->id());
		dGeomSetBody(PlayerMech->mechGeoms[blockNum],PlayerMech->mechbody[blockNum]->id());
		//PlayerMech->mechboxes[blockNum]->setBody (PlayerMech->mechbody[blockNum]->id());
		//PlayerMech->setBlockDimension(PlayerMech->blockNum,1.5,1.5,1.5);
		PlayerMech->blockNum++;
		//player->blockCarrying[blockNum] = true;
		PlayerMech->modelIndex [blockNum] = &modelArray[modelArrayIndex - 1 ];
        PlayerMech->modelID[blockNum] = modelArrayIndex - 1 ;

        PlayerMech->texture [blockNum] = texture[textIndex - 1];
        PlayerMech->textID[blockNum] = textIndex - 1 ;

        PlayerMech->shader [blockNum] = shaderPrograms[shaderIndex - 1 ];
        PlayerMech->shaderID[blockNum] = shaderIndex - 1 ;

      }

}
void createMech (Mech *PlayerMech)
{

        for(int i = 0; i< 2000; i++)
        {
            PlayerMech->blockIntersect [i] = false;
            PlayerMech->blockCarrying [i] = false;
            PlayerMech->modelIndex [i] = NULL;
        }
		dMass m;
		float baseHeight = 6.0;

		PlayerMech->blockNum = 0;
		PlayerMech->jointNum = 0;

	    PlayerMech->mechbody[0] = new dBody();
	    PlayerMech->mechID[0] = PlayerMech->mechbody[0]->id();
		//PlayerMech->mechboxes[0] = new dBox();
		PlayerMech->mechGeoms[0] = dCreateBox(space,6.0,6.0,6.0);
		PlayerMech->mechbody[0]->create(world);
		PlayerMech->mechbody[0]->setPosition (0,0,10);
		dMassSetBox (&m,1,6.0,6.0,6.0);
		dMassAdjust (&m, 1000*MECHMASS);
		PlayerMech->mechbody[0]->setMass (&m);
		//PlayerMech->mechboxes[0]->create(space,6.0,6.0,6.0);
		//PlayerMech->mechboxes[0]->setBody (PlayerMech->mechbody[0]->id());
		dGeomSetBody(PlayerMech->mechGeoms[0],PlayerMech->mechbody[0]->id());
		PlayerMech->setBlockDimension(PlayerMech->blockNum,6.0,6.0,6.0);
		//PlayerMech->mechHead[0] = new osg::MatrixTransform;
		//PlayerMech->mechHead[0]->addChild(baseBlueGeode);
		//PlayerMech->mechHead[0]->setMatrix(osg::Matrix::translate(20,20,3));
		//loadedGroup->addChild(PlayerMech->mechHead[0]);

		PlayerMech->blockNum++;

		PlayerMech->mechbody[1] = new dBody();
		PlayerMech->mechID[1] = PlayerMech->mechbody[1]->id();
		//PlayerMech->mechboxes[1] = new dBox();
		PlayerMech->mechGeoms[1] = dCreateBox(space,2.0,2.0,1.5);
		PlayerMech->mechbody[1]->create(world);
		PlayerMech->mechbody[1]->setPosition (0,-1, 13 + .75);
		dMassSetBox (&m,1,2.0,2.0,1.5);
		dMassAdjust (&m, MECHMASS);
		PlayerMech->mechbody[1]->setMass (&m);
		//PlayerMech->mechboxes[1]->create(space,2.0,2.0,1.5);
		//PlayerMech->mechboxes[1]->setBody (PlayerMech->mechbody[1]->id());
		dGeomSetBody(PlayerMech->mechGeoms[1],PlayerMech->mechbody[1]->id());
		PlayerMech->setBlockDimension(PlayerMech->blockNum,2.0,2.0,1.5);
		//PlayerMech->mechHead[1] = new osg::MatrixTransform;
		//PlayerMech->mechHead[1]->addChild(d2X2YellowGeode);
		//PlayerMech->mechHead[1]->setMatrix(osg::Matrix::translate(20,19,baseHeight + .75));
		//loadedGroup->addChild(PlayerMech->mechHead[1]);
        PlayerMech->blockNum++;

		PlayerMech->mechbody[2] = new dBody();
		PlayerMech->mechID[2] = PlayerMech->mechbody[2]->id();
		//PlayerMech->mechboxes[2] = new dBox();
		PlayerMech->mechGeoms[2] = dCreateBox(space,2.0,2.0,1.5);
		PlayerMech->mechbody[2]->create(world);
		PlayerMech->mechbody[2]->setPosition (0,1,13 + .75);
		dMassSetBox (&m,1,2.0,2.0,1.5);
		dMassAdjust (&m, MECHMASS);
		PlayerMech->mechbody[2]->setMass (&m);
		//PlayerMech->mechboxes[2]->create(space,2.0,2.0,1.5);
		//PlayerMech->mechboxes[2]->setBody (PlayerMech->mechbody[2]->id());
		dGeomSetBody(PlayerMech->mechGeoms[2],PlayerMech->mechbody[2]->id());
		PlayerMech->setBlockDimension(PlayerMech->blockNum,2.0,2.0,1.5);
		//PlayerMech->mechHead[2] = new osg::MatrixTransform;
		//PlayerMech->mechHead[2]->addChild(d2X2YellowGeode);
		//PlayerMech->mechHead[2]->setMatrix(osg::Matrix::translate(20,21,baseHeight + .75));
		//loadedGroup->addChild(PlayerMech->mechHead[2]);
		PlayerMech->blockNum++;

		PlayerMech->mechjoint[0] = new dFixedJoint();
        PlayerMech->mechjoint[0]->create(world);
		PlayerMech->mechjoint[0]->attach(PlayerMech->mechbody[0]->id(),PlayerMech->mechbody[1]->id());
		dJointSetFixed(PlayerMech->mechjoint[0]->id());
		PlayerMech->jointNum++;

		PlayerMech->mechjoint[1] = new dFixedJoint();
        PlayerMech->mechjoint[1]->create(world);
		PlayerMech->mechjoint[1]->attach(PlayerMech->mechbody[0]->id(),PlayerMech->mechbody[2]->id());
        dJointSetFixed(PlayerMech->mechjoint[1]->id());
        PlayerMech->jointNum++;


		PlayerMech->mechbody[3] = new dBody();
		PlayerMech->mechID[3] = PlayerMech->mechbody[3]->id();
		//PlayerMech->mechboxes[3] = new dBox();
		PlayerMech->mechGeoms[3] = dCreateBox(space,2.0,2.0,1.5);
		PlayerMech->mechbody[3]->create(world);
		PlayerMech->mechbody[3]->setPosition (0,0,13 + 2.25);
		dMassSetBox (&m,1,2.0,3.0,1.5);
		dMassAdjust (&m, MECHMASS);
		PlayerMech->mechbody[3]->setMass (&m);
		//PlayerMech->mechboxes[3]->create(space,2.0,3.0,1.5);
		//PlayerMech->mechboxes[3]->setBody (PlayerMech->mechbody[3]->id());
		dGeomSetBody(PlayerMech->mechGeoms[3],PlayerMech->mechbody[3]->id());
		PlayerMech->setBlockDimension(PlayerMech->blockNum,2.0,3.0,1.5);
		//PlayerMech->mechHead[3] = new osg::MatrixTransform;
		//PlayerMech->mechHead[3]->addChild(d2X3BlueGeode);
		//PlayerMech->mechHead[3]->setMatrix(osg::Matrix::translate(20,20,baseHeight + 2.25));
		//loadedGroup->addChild(PlayerMech->mechHead[3]);
		PlayerMech->blockNum++;

		PlayerMech->mechjoint[2] = new dFixedJoint();
        PlayerMech->mechjoint[2]->create(world);
		PlayerMech->mechjoint[2]->attach(PlayerMech->mechbody[2]->id(),PlayerMech->mechbody[3]->id());
        dJointSetFixed(PlayerMech->mechjoint[2]->id());
        PlayerMech->jointNum++;

		PlayerMech->mechbody[4] = new dBody();
		//dBodySetData(PlayerMech->mechID[4],PlayerMech->mechbody[4]->id());
		PlayerMech->mechID[4] = PlayerMech->mechbody[4]->id();
		//PlayerMech->mechboxes[4] = new dBox();
		PlayerMech->mechGeoms[4] = dCreateBox(space,2.0,2.0,1.5);
		PlayerMech->mechbody[4]->create(world);
		PlayerMech->mechbody[4]->setPosition (0,-1,13 + 3.75);
		dMassSetBox (&m,1,2.0,2.0,1.5);
		dMassAdjust (&m, MECHMASS);
		PlayerMech->mechbody[4]->setMass (&m);
		//PlayerMech->mechboxes[4]->create(space,2.0,2.0,1.5);
		//PlayerMech->mechboxes[4]->setBody (PlayerMech->mechbody[4]->id());
		//dGeomSetBody(geom,PlayerMech->mechbody[4]->id());
		dGeomSetBody(PlayerMech->mechGeoms[4],PlayerMech->mechbody[4]->id());
		PlayerMech->setBlockDimension(PlayerMech->blockNum,2.0,2.0,1.5);
		//PlayerMech->mechHead[4] = new osg::MatrixTransform;
		//PlayerMech->mechHead[4]->addChild(d2X2BlueGeode);
		//PlayerMech->mechHead[4]->setMatrix(osg::Matrix::translate(20,19,baseHeight + 3.75));
		//loadedGroup->addChild(PlayerMech->mechHead[4]);
		PlayerMech->blockNum++;


		/*for (int i = 5; i < 5; i++)
		{


		    PlayerMech->mechbody[i] = new dBody();
		//dBodySetData(PlayerMech->mechID[4],PlayerMech->mechbody[4]->id());
		PlayerMech->mechID[i] = PlayerMech->mechbody[i]->id();
		PlayerMech->mechboxes[i] = new dBox();
		PlayerMech->mechbody[i]->create(world);
		PlayerMech->mechbody[i]->setPosition (0.7*(i/10),0.7*(i/10),50.0);
		dMassSetBox (&m,1,2.0,2.0,1.5);
		dMassAdjust (&m, 1000000000000.0*MECHMASS);
		PlayerMech->mechbody[i]->setMass (&m);
		PlayerMech->mechboxes[i]->create(space,2.0,2.0,1.5);
		PlayerMech->mechboxes[i]->setBody (PlayerMech->mechbody[i]->id());
		//dGeomSetBody(geom,PlayerMech->mechbody[4]->id());
		PlayerMech->setBlockDimension(PlayerMech->blockNum,2.0,2.0,1.5);
		//PlayerMech->mechHead[4] = new osg::MatrixTransform;
		//PlayerMech->mechHead[4]->addChild(d2X2BlueGeode);
		//PlayerMech->mechHead[4]->setMatrix(osg::Matrix::translate(20,19,baseHeight + 3.75));
		//loadedGroup->addChild(PlayerMech->mechHead[4]);
		PlayerMech->blockNum++;

		}*/

}

int createBody(Mech * PlayerMech, mesh &model, float bmass, float xpos, float ypos, float zpos,dWorldID world, dSpaceID space)
{

            int blockNum =  PlayerMech->blockNum;
            ofstream damn("DamM", ios::out);

            dMass m;

            float dist[model.vertCount];
            float maxdist = 0.0;
            float cyldist[model.vertCount];
            float cylmaxdist = 0.0;

            damn << "VertexArray\n";
            for(int i = 0; i < model.vertCount; i++)
            {
                damn << model.VertexArray[i][0] << " " << model.VertexArray[i][1] << " " << model.VertexArray[i][2] << "\n";
                dist[i] =  sqrt(model.VertexArray[i][0]*model.VertexArray[i][0] + model.VertexArray[i][1]*model.VertexArray[i][1] + model.VertexArray[i][2]*model.VertexArray[i][2]);
                if(i == 0)
                maxdist = dist[i];

                if(dist[i] > maxdist)
                maxdist = dist[i];
            }

            int compNum = 0;
            float sum = 0.0;

            for(int i = 0; i < model.vertCount - 1; i++)
            {
                for(int p = i + 1; p < model.vertCount; p++)
                {
                    sum += abs(dist[p] - dist[i]);
                    compNum++;
                }

            }

            sum /= compNum;
            damn << "\nsum: " << sum << "\n";

            if(sum < 0.0001)
            {
                damn << "\nsum: " << sum << "\n";

                //create sphere
                PlayerMech->blockIntersect[blockNum] = false;
                PlayerMech->mechbody[blockNum] = new dBody();
                PlayerMech->mechID[blockNum] = PlayerMech->mechbody[blockNum]->id();
                //PlayerMech->mechboxes[blockNum] = new dBox();
                PlayerMech->mechGeoms[blockNum] = dCreateSphere(space,maxdist);
                PlayerMech->mechbody[blockNum]->create(world);
                PlayerMech->mechbody[blockNum]->setPosition (xpos,ypos,zpos);
                dMassSetSphere (&m,1,2.0);
                dMassAdjust (&m, bmass);
                PlayerMech->mechbody[blockNum]->setMass (&m);
                //PlayerMech->mechboxes[blockNum]->create(space,2000.0,200.0,100.5);
                dGeomSetBody(PlayerMech->mechGeoms[blockNum],PlayerMech->mechbody[blockNum]->id());
                PlayerMech->blockNum++;
                //player->blockCarrying[blockNum] = true;
                PlayerMech->modelIndex [blockNum] = &modelArray[modelArrayIndex - 1 ];
                PlayerMech->modelID[blockNum] = modelArrayIndex - 1 ;

                PlayerMech->texture [blockNum] = texture[textIndex - 1];
                PlayerMech->textID[blockNum] = textIndex - 1 ;

                PlayerMech->shader [blockNum] = shaderPrograms[shaderIndex - 1 ];
                PlayerMech->shaderID[blockNum] = shaderIndex - 1 ;

                //PlayerMech->mechboxes[blockNum]->setBody (PlayerMech->mechbody[blockNum]->id());
                cyldiff = getMeshVolume(model);
                cyldiff = getAABBVolume(model);
                return BSPHERE;
            }
            else
            {

                    for(int n = 0; n < model.vertCount; n++)
                    {

                        cyldist[n] =  sqrt(model.VertexArray[n][0]*model.VertexArray[n][0] + model.VertexArray[n][1]*model.VertexArray[n][1]);
                        if(n == 0)
                        cylmaxdist = cyldist[n];

                        if(cyldist[n] > cylmaxdist)
                        cylmaxdist = cyldist[n];
                    }

                    int cylcompNum = 0;
                    float cylsum = 0.0;

                    for(int i = 0; i < model.vertCount - 1; i++)
                    {
                        for(int p = i + 1; p < model.vertCount; p++)
                        {
                            cylsum += abs(cyldist[p] - cyldist[i]);
                            cylcompNum++;
                        }

                    }

                    cylsum /= (float) cylcompNum;

                    cyldiff = cylsum;
                    damn << "\ncylsum: " << cylsum << "\n";

                    if(cylsum < 0.1)
                    {

                        //create sphere
                        PlayerMech->blockIntersect[blockNum] = false;
                        PlayerMech->mechbody[blockNum] = new dBody();
                        PlayerMech->mechID[blockNum] = PlayerMech->mechbody[blockNum]->id();
                        //PlayerMech->mechboxes[blockNum] = new dBox();
                        PlayerMech->mechGeoms[blockNum] = dCreateCCylinder(space,cylmaxdist,maxdist);
                        PlayerMech->mechbody[blockNum]->create(world);
                        PlayerMech->mechbody[blockNum]->setPosition (xpos,ypos,zpos);
                        dMassSetCylinder (&m,1,2,cylmaxdist,maxdist);
                        dMassAdjust (&m, bmass);
                        PlayerMech->mechbody[blockNum]->setMass (&m);
                        //PlayerMech->mechboxes[blockNum]->create(space,2000.0,200.0,100.5);
                        dGeomSetBody(PlayerMech->mechGeoms[blockNum],PlayerMech->mechbody[blockNum]->id());
                        PlayerMech->blockNum++;
                        //player->blockCarrying[blockNum] = true;
                        PlayerMech->modelIndex [blockNum] = &modelArray[modelArrayIndex - 1 ];
                        PlayerMech->modelID[blockNum] = modelArrayIndex - 1 ;

                        PlayerMech->texture [blockNum] = texture[textIndex - 1];
                        PlayerMech->textID[blockNum] = textIndex - 1 ;

                        PlayerMech->shader [blockNum] = shaderPrograms[shaderIndex - 1 ];
                        PlayerMech->shaderID[blockNum] = shaderIndex - 1 ;

                        //PlayerMech->mechboxes[blockNum]->setBody (PlayerMech->mechbody[blockNum]->id());
                        cyldiff = getMeshVolume(model);
                        cyldiff = getAABBVolume(model);
                        return BCYLINDER;
                    }
                    else
                    {
                        float volume = getMeshVolume(model);
                        float bbvolume = getAABBVolume(model);
                        cyldiff = volume;
                        cyldiff = bbvolume;


                            float bbmin[3];
                            float bbmax[3];

                            bbmin[0] = model.VertexArray[0][0];
                            bbmin[1] = model.VertexArray[0][1];
                            bbmin[2] = model.VertexArray[0][2];

                            bbmax[0] = model.VertexArray[0][0];
                            bbmax[1] = model.VertexArray[0][1];
                            bbmax[2] = model.VertexArray[0][2];

                            for(int i = 0; i < model.vertCount; i++)
                            {
                                if(bbmin[0] > model.VertexArray[i][0])
                                bbmin[0] = model.VertexArray[i][0];

                                if(bbmin[1] > model.VertexArray[i][1])
                                bbmin[1] = model.VertexArray[i][1];

                                if(bbmin[2] > model.VertexArray[i][2])
                                bbmin[2] = model.VertexArray[i][2];

                                if(bbmax[0] < model.VertexArray[i][0])
                                bbmax[0] = model.VertexArray[i][0];

                                if(bbmax[1] < model.VertexArray[i][1])
                                bbmax[1] = model.VertexArray[i][1];

                                if(bbmax[2] < model.VertexArray[i][2])
                                bbmax[2] = model.VertexArray[i][2];
                            }

                            float lx = bbmax[0] - bbmin[0];
                            float ly = bbmax[1] - bbmin[1];
                            float lz = bbmax[2] - bbmin[2];

                        if(1||bbvolume - volume < bbvolume*0.65)
                        {
                            PlayerMech->blockIntersect[blockNum] = false;
                            PlayerMech->mechbody[blockNum] = new dBody();
                            PlayerMech->mechID[blockNum] = PlayerMech->mechbody[blockNum]->id();
                            //PlayerMech->mechboxes[blockNum] = new dBox();
                            PlayerMech->mechbody[blockNum]->create(world);
                            PlayerMech->mechGeoms[blockNum] = dCreateBox(space,lx,ly,lz);
                            PlayerMech->mechbody[blockNum]->setPosition (xpos,ypos,zpos);
                            dMassSetBox (&m,1,lx,ly,lz);
                            dMassAdjust (&m, bmass);
                            PlayerMech->mechbody[blockNum]->setMass (&m);
                            //PlayerMech->mechboxes[blockNum]->create(space,1.5,1.5,1.5);
                            //dGeomSetBody(geom,PlayerMech->mechbody[blockNum]->id());
                            dGeomSetBody(PlayerMech->mechGeoms[blockNum],PlayerMech->mechbody[blockNum]->id());
                            //PlayerMech->mechboxes[blockNum]->setBody (PlayerMech->mechbody[blockNum]->id());
                            //PlayerMech->setBlockDimension(PlayerMech->blockNum,1.5,1.5,1.5);
                            PlayerMech->blockNum++;
                            //player->blockCarrying[blockNum] = true;
                            PlayerMech->modelIndex [blockNum] = &modelArray[modelArrayIndex - 1 ];
                            PlayerMech->modelID[blockNum] = modelArrayIndex - 1 ;

                            PlayerMech->texture [blockNum] = texture[textIndex - 1];
                            PlayerMech->textID[blockNum] = textIndex - 1 ;

                            PlayerMech->shader [blockNum] = shaderPrograms[shaderIndex - 1 ];
                            PlayerMech->shaderID[blockNum] = shaderIndex - 1 ;



                            }
                            else
                            {
                                dTriMeshDataID tmdata = dGeomTriMeshDataCreate();
                                dGeomTriMeshDataBuildSingle(tmdata,&model.VertexArray[0][0],3 * sizeof(float), model.vertCount, (int*)&model.triangles[0][0], 3*model.triCount, 3 * sizeof(int));
                                PlayerMech->blockIntersect[blockNum] = false;
                                PlayerMech->mechbody[blockNum] = new dBody();
                                PlayerMech->mechID[blockNum] = PlayerMech->mechbody[blockNum]->id();
                                //PlayerMech->mechboxes[blockNum] = new dBox();
                                PlayerMech->mechbody[blockNum]->create(world);
                                PlayerMech->mechGeoms[blockNum] = dCreateTriMesh(space, tmdata, 0, 0, 0);//dCreateBox(space,lx,ly,lz);
                                dGeomSetData(PlayerMech->mechGeoms[blockNum], tmdata);


                                #if 1
                               {


                                   dGeomSetPosition(PlayerMech->mechGeoms[blockNum],0,0,0);
                                    dMatrix3 Rotation;// = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                                    //dRFromAxisAndAngle(Rotation, 1,0 , 0, 90.0*piover180);
                                    //dRFromAxisAndAngle(Rotation, 0,0 , 1,0.0*piover180);


                                    //dRFromAxisAndAngle(Rotation,0,1 ,0,180.0*piover180);
                                    dRFromEulerAngles(Rotation,0*30.0*piover180,0*180.0*piover180,0.0);
                                    dGeomSetRotation(PlayerMech->mechGeoms[blockNum], Rotation);
                                }
                                #endif
                                PlayerMech->mechbody[blockNum]->setPosition (xpos,ypos,zpos);
                                dMassSetBox (&m,1,lx,ly,lz);
                                dMassAdjust (&m, bmass);
                                PlayerMech->mechbody[blockNum]->setMass (&m);
                                //PlayerMech->mechboxes[blockNum]->create(space,1.5,1.5,1.5);
                                //dGeomSetBody(geom,PlayerMech->mechbody[blockNum]->id());
                                dGeomSetBody(PlayerMech->mechGeoms[blockNum],PlayerMech->mechbody[blockNum]->id());
                                //PlayerMech->mechboxes[blockNum]->setBody (PlayerMech->mechbody[blockNum]->id());
                                //PlayerMech->setBlockDimension(PlayerMech->blockNum,1.5,1.5,1.5);
                                PlayerMech->blockNum++;
                                //player->blockCarrying[blockNum] = true;
                                PlayerMech->modelIndex [blockNum] = &modelArray[modelArrayIndex - 1 ];
                                PlayerMech->modelID[blockNum] = modelArrayIndex - 1 ;

                                PlayerMech->texture [blockNum] = texture[textIndex - 1];
                                PlayerMech->textID[blockNum] = textIndex - 1 ;

                                PlayerMech->shader [blockNum] = shaderPrograms[shaderIndex - 1 ];
                                PlayerMech->shaderID[blockNum] = shaderIndex - 1 ;






                            }






                            return -1;
                    }
            }

damn.close();
return 0;
}

float getMeshVolume(mesh &model)
{
      float volume = 0.0;
      for(int i = 0; i < model.triCount; i++)
      {
            float v0 [3];
            float v1 [3];
            float v2 [3];

                            v0[0] = model.VertexArray[model.triangles[i][1]][0];
                            v0[1] = model.VertexArray[model.triangles[i][1]][1];
                            v0[2] = model.VertexArray[model.triangles[i][1]][2];

                            v1[0] = model.VertexArray[model.triangles[i][0]][0];
                            v1[1] = model.VertexArray[model.triangles[i][0]][1];
                            v1[2] = model.VertexArray[model.triangles[i][0]][2];

                            v2[0] = model.VertexArray[model.triangles[i][2]][0];
                            v2[1] = model.VertexArray[model.triangles[i][2]][1];
                            v2[2] = model.VertexArray[model.triangles[i][2]][2];

                            //aXb=(a2b3-a3b2, a3b1-a1b3, a1b2-a2b1)

                            float crossP[3];
                            crossP[0] = v1[1]*v2[2] - v1[2]*v2[1];
                            crossP[1] = v1[2]*v2[0] - v1[0]*v2[2];
                            crossP[2] = v1[0]*v2[1] - v1[1]*v2[0];

                            volume += crossP[0]*v0[0] + crossP[1]*v0[1] + crossP[2]*v0[2];

        }

        volume /= 6.0;

        return volume;
}

float getAABBVolume(mesh &model)
{
     float bbmin[3];
                        float bbmax[3];

                        bbmin[0] = model.VertexArray[0][0];
                        bbmin[1] = model.VertexArray[0][1];
                        bbmin[2] = model.VertexArray[0][2];

                        bbmax[0] = model.VertexArray[0][0];
                        bbmax[1] = model.VertexArray[0][1];
                        bbmax[2] = model.VertexArray[0][2];

                        for(int i = 0; i < model.vertCount; i++)
                        {
                            if(bbmin[0] > model.VertexArray[i][0])
                             bbmin[0] = model.VertexArray[i][0];

                            if(bbmin[1] > model.VertexArray[i][1])
                             bbmin[1] = model.VertexArray[i][1];

                            if(bbmin[2] > model.VertexArray[i][2])
                             bbmin[2] = model.VertexArray[i][2];

                            if(bbmax[0] < model.VertexArray[i][0])
                             bbmax[0] = model.VertexArray[i][0];

                            if(bbmax[1] < model.VertexArray[i][1])
                             bbmax[1] = model.VertexArray[i][1];

                            if(bbmax[2] < model.VertexArray[i][2])
                             bbmax[2] = model.VertexArray[i][2];
                        }


            return (bbmax[0] - bbmin[0])*(bbmax[1] - bbmin[1])*(bbmax[2] - bbmin[2]);
}

int SceneCell :: render()
{



    SceneNode * node;
    for(int n = 0; n < trans.size();n++)
    {
        float x,y,z;
        x = trans.at(n)->position[0];
        y = trans.at(n)->position[1];
        z = trans.at(n)->position[2];

        for(int i = 0; i < trans.at(n)->children.size(); i++)
        //if(children.at(i))
        {

            node = trans.at(n)->children.at(i);
           glUseProgramObjectARB(node->shader);


             //glUniform3fARB(posloc,xpos -x, zpos -y,ypos -z);
             //glUniform3fARB(posloc_metal,xpos -x, zpos -y,ypos -z);
             glUniform3fARB(posloc,xpos -x, zpos -y,ypos -z);
             glUniform3fARB(posloc_metal,xpos -x, zpos -y,ypos -z);
            //glUniform1fARB(gunBurst,burstValue);

            if(i == 2)
            {


            //texloc   = glGetUniformLocationARB(p_metal, "NormalHeight");
            texloc_metal   = glGetUniformLocationARB(p_metal, "NormalHeight");

            //glUniform1iARB(texloc, 0);
            glUniform1iARB(texloc_metal, 0);

            //texloc2   = glGetUniformLocationARB(p_metal, "Base");
            texloc2_metal   = glGetUniformLocationARB(p_metal, "Base");

            //glUniform1iARB(texloc2, 1);
            glUniform1iARB(texloc2_metal, 1);

            }
            else
            {


                 texloc   = glGetUniformLocationARB(p, "NormalHeight");
            //texloc   = glGetUniformLocationARB(p_metal, "NormalHeight");

            glUniform1iARB(texloc, 0);
            //glUniform1iARB(texloc_metal, 0);

            texloc2   = glGetUniformLocationARB(p, "Base");
            //texloc2   = glGetUniformLocationARB(p_metal, "Base");

            glUniform1iARB(texloc2, 1);
            //glUniform1iARB(texloc2_metal, 1);

            }

        glPushMatrix ();

           glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();

              // glMatrixMode(GL_MODELVIEW);
               //     glLoadIdentity();


            perspectiveGL( 45, 1.33333333, 0.1f, 1000.0f );
           //
            glRotatef (90.0, 1.0f, 0.0f, 0.0f);
           // if(mouseMove)
           // {

                glRotatef (mouseRotY*0.5, 180.0f, 0.0f, 0.0f);
                glRotatef (mouseRotY*0.5, 1.0f, 0.0f, 0.0f);
                glRotatef (mouseRotX, 0.0f, 0.0f, 1.0f);
                glTranslatef (-xpos + x,-zpos + y,-ypos + z);

                GLfloat xLightP [] = {LightP[0] -x,LightP[1]-y,LightP[2]-z,LightP[3]};

                glLightfv(GL_LIGHT0, GL_POSITION, xLightP);


               glActiveTexture(GL_TEXTURE0);
               glBindTexture(GL_TEXTURE_2D, node->texture[0]);

               glActiveTexture(GL_TEXTURE1);
               glBindTexture(GL_TEXTURE_2D, node->texture[1]);
               //glDisable(GL_TEXTURE_2D);
                glEnableClientState(GL_NORMAL_ARRAY);
                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glEnableVertexAttribArrayARB(BMapTangent);
                glEnableVertexAttribArrayARB(BMapBinormal);


                    glBindBufferARB( GL_ARRAY_BUFFER_ARB, node->model->VBOVertices );
		           glVertexPointer( 3, GL_FLOAT, 0, 0);//(char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer

                   glBindBufferARB( GL_ARRAY_BUFFER_ARB, node->model->VBOTexCoords );
		           glTexCoordPointer(2, GL_FLOAT, 0, 0 );

		           glBindBufferARB( GL_ARRAY_BUFFER_ARB, node->model->VBONormals );
		           glNormalPointer( GL_FLOAT, 0, 0 );		// Set The TexCoord Pointer To The TexCoord Buffe



                   glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, node->model->EBOTris );


                     glDrawElements(GL_TRIANGLES,node->model->triCount*3,GL_UNSIGNED_INT,NULL);

                    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, node->model->EBOQuads );

                    glDrawElements(GL_QUADS,node->model->quadCount*4,GL_UNSIGNED_INT,NULL);

                   glDisableClientState( GL_VERTEX_ARRAY );
                   glDisableClientState( GL_NORMAL_ARRAY );
/*
                   glUseProgramObjectARB(p_shadow);

                   glDisable(GL_DEPTH_TEST);
                    glBlendFunc(GL_DST_COLOR, GL_ZERO);
                    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                   glEnable(GL_BLEND);

                     glDrawElements(GL_TRIANGLES,node->model->triCount*3,GL_UNSIGNED_INT,NULL);

                    glDrawElements(GL_QUADS,node->model->quadCount*4,GL_UNSIGNED_INT,NULL);

                   glDisableClientState( GL_VERTEX_ARRAY );
                   glDisableClientState( GL_NORMAL_ARRAY );

                    glDisable(GL_BLEND);
                   glEnable(GL_DEPTH_TEST);
*/

            glPopMatrix ();

        }
    }
}

int SceneCell :: boundsCheck()
{
    //for now return 1
    return 1;
}

SceneNode::SceneNode(
                                    mesh *model,
                                    int modelID,
                                    GLuint texture [12],
                                    int textID [12],
                                    GLuint shader,
                                    int shaderID
                                    )
{
        this->model = model;
        this->shader = shader;
}

BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName)
{
	//nodeArray.clear();
	std::ifstream infile;
	std::string line;
	float position[3];
    infile.open (pszFileName, ios::binary);
    if (infile.is_open())
  {
    while (! infile.eof() )
    {
        for(int i = 0; i < 3; i++)
        {
            getline (infile,line);

            bool taco = from_string<float>(position[i], std::string(line), std::dec);
        }

        //Node * newNode = new Node(position[0],position[1],position[2]);
        //nodeArray.push_back(newNode);

    }
    infile.close();
  }

	return true;
}
