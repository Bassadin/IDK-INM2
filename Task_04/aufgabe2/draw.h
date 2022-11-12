// Sicherstellen, dass die Header-Datei nur einmal eingebunden wird.
#ifndef DRAW_H
#define DRAW_H

#include <EGL/egl.h> // EGL Datentypen und Funktionen
#include <GL/glut.h>


GLfloat kmh2deg(GLfloat kmh);
GLfloat rpm2deg(GLfloat rpm);
int draw_main();

#endif
