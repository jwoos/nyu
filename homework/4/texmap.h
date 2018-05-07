#ifndef INTERACTIVE_CG_TEXMAP_H
#define INTERACTIVE_CG_TEXMAP_H


#include "Angel-yjc.h"


#define IMAGE_WIDTH  32
#define IMAGE_HEIGHT 32
GLubyte TEXTURE_IMAGE[IMAGE_HEIGHT][IMAGE_WIDTH][4];

#define	STRIPE_IMAGE_WIDTH 32
GLubyte TEXTURE_STRIPE_IMAGE[4*STRIPE_IMAGE_WIDTH];


/* global definitions for constants and global image arrays */

/*************************************************************
  void image_set_up(void):
  generate checkerboard and stripe images.

 * Inside init(), call this function and set up texture objects
 for texture mapping.
 (init() is called from main() before calling glutMainLoop().)
 ***************************************************************/
void image_set_up(void) {
	int i, j, c;

	/* --- Generate checkerboard image to the image array ---*/
	for (i = 0; i < IMAGE_HEIGHT; i++) {
		for (j = 0; j < IMAGE_WIDTH; j++) {
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0));

			if (c == 1) {
				c = 255;
				TEXTURE_IMAGE[i][j][0] = (GLubyte) c;
				TEXTURE_IMAGE[i][j][1] = (GLubyte) c;
				TEXTURE_IMAGE[i][j][2] = (GLubyte) c;
			} else {
				TEXTURE_IMAGE[i][j][0] = (GLubyte) 0;
				TEXTURE_IMAGE[i][j][1] = (GLubyte) 150;
				TEXTURE_IMAGE[i][j][2] = (GLubyte) 0;
			}

			TEXTURE_IMAGE[i][j][3] = (GLubyte) 255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/*--- Generate 1D stripe image to array stripeImage[] ---*/
	for (j = 0; j < STRIPE_IMAGE_WIDTH; j++) {
		/* When j <= 4, the color is (255, 0, 0),   i.e., red stripe/line.
		   When j > 4,  the color is (255, 255, 0), i.e., yellow remaining texture
		   */
		TEXTURE_STRIPE_IMAGE[4*j] = (GLubyte)    255;
		TEXTURE_STRIPE_IMAGE[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
		TEXTURE_STRIPE_IMAGE[4*j+2] = (GLubyte) 0;
		TEXTURE_STRIPE_IMAGE[4*j+3] = (GLubyte) 255;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	/*----------- End 1D stripe image ----------------*/

	/*--- texture mapping set-up is to be done in
	  init() (set up texture objects),
	  display() (activate the texture object to be used, etc.)
	  and in shaders.
	  ---*/
}


#endif
