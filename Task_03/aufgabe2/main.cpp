// --------------------------------------------------------------------------
// DashBoard - Aufgabe 1
//
// Bearbeitet von:
//     Name, Matrikelnummer
//     Name, Matrikelnummer
//
// --------------------------------------------------------------------------

// Header
#include <stdio.h>	// printf, fprintf
#include <stdlib.h> // exit
#include <unistd.h> // sleep
#include <math.h>	// z.B. M_PI, cos(), sin()
#include <GL/glut.h>
#include "../lib/gles.h" // struct opengles, gles*-Funktionen
#include "../lib/tile.h" // struct tile, loadPngTile

#include <chrono>
#include <thread>

GLfloat kmh2deg(GLfloat kmh)
{
	GLfloat minKmh = 0;
	GLfloat maxKmh = 150;

	if (kmh < minKmh || kmh > maxKmh)
	{
		throw std::invalid_argument("kmh value out of bounds");
	}

	GLfloat percentageValue = kmh / maxKmh;

	GLfloat zeroAngle = 180;
	GLfloat maxAngle = -155;

	GLfloat difference = abs(zeroAngle - maxAngle);

	return zeroAngle - (percentageValue * difference);
}

GLfloat rpm2deg(GLfloat rpm)
{
	GLfloat minRpm = 0;
	GLfloat maxRpm = 7000;

	if (rpm < minRpm || rpm > maxRpm)
	{
		throw std::invalid_argument("rpm value out of bounds");
	}

	GLfloat percentageValue = rpm / maxRpm;

	GLfloat zeroAngle = 180;
	GLfloat maxAngle = 25;

	GLfloat difference = abs(zeroAngle - maxAngle);

	return zeroAngle - (percentageValue * difference);
}

int main(void)
{
	// OpenGL ES initialisieren
	struct opengles opengles;
	glesInitialize(&opengles);

	// Textur für Dashboard laden
	struct tile dashboard = TILE_ZEROINIT;
	tileLoadPng(&opengles, &dashboard, "../bilder/own/dashboard.png");

	// Textur für Tachonadel laden
	struct tile needle = TILE_ZEROINIT;
	tileLoadPng(&opengles, &needle, "../bilder/own/pointer.png");

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		tileDraw(&dashboard);

		// ---- Rechte Tachonadel zeichnen ---------------------------

		glPushMatrix();

		GLfloat needleHeightOffset = 256.0 / 512.0;
		GLfloat speedKmh = 120;

		glTranslatef(0.8, 0.155, 0);
		glRotatef(kmh2deg(speedKmh),0, 0, 1);
		glTranslatef(0, needleHeightOffset, 0);

		tileDraw(&needle);

		glPopMatrix();

		// ---- Linke Tachonadel zeichnen ---------------------------

		glPushMatrix();

		GLfloat speedRpm = 5000;

		glTranslatef(-0.8, 0.155, 0);
		glRotatef(rpm2deg(speedRpm), 0, 0, 1);
		glTranslatef(0, needleHeightOffset, 0);
		tileDraw(&needle);

		glPopMatrix();

		// ---- Das gezeichnete Bild sichtbar machen ----------------
		glesDraw(&opengles);

		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	} while (glesRun(&opengles));

	// OpenGL ES Ressourcen freigeben.
	glesDestroy(&opengles);

	return 0;
}
