/*
 * HelloGL.cpp
 * 
 * Copyright 2015  <pi@Daniel-RPi-2>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifdef _MSC_VER                         // Check if MS Visual C compiler
#  pragma comment(lib, "opengl32.lib")  // Compiler-specific directive to avoid manually configuration
#  pragma comment(lib, "glu32.lib")     // Link libraries
#  ifndef _MBCS
#    define _MBCS    // Uses Multi-byte character set
#  endif
#  ifdef _UNICODE     // Not using Unicode character set
#    undef _UNICODE 
#  endif
#  ifdef UNICODE
#    undef UNICODE 
#  endif
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* Handler for window-repaint event.
 * Call back when the window first appears
 * and whenever the window needs to be re-painted.
 */

void display() {
	glClearColor(0.0F, 0.0F, 0.0F, 1.0F); // Set background to opaque black
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Draw a red 1x1 square centered at origin
	glBegin(GL_QUADS); // Each set of 4 vertices form a quad
		glColor3f(1.0F, 0.0F, 0.0F); // Red (HSB)
		glVertex2f(-0.5F, -0.5F);
		glVertex2f(0.5F, -0.5F);
		glVertex2f(0.5F, 0.5F);
		glVertex2f(-0.5F, 0.5F);
	glEnd();
	
	glFlush(); // Render
}

/*
 * Main
 * GLUT (freeglut) is a console application at main
 */
int main(int argc, char **argv) {
	glutInit(&argc, argv); // Initialize GLUT
	glutCreateWindow("Hello openGL"); // Create a window
	glutInitWindowSize(320, 320); // Set width, height
	glutInitWindowPosition(50, 50); // Top left corner
	glutDisplayFunc(display); // Everybody love's function pointers!
	                          // Handles window-repaint
	glutMainLoop(); // Loop until window is closed
	return 0;
}

