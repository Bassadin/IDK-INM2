// --------------------------------------------------------------------------
//  Copyright © 2014  CS  -  All rights reserved
// --------------------------------------------------------------------------

#ifndef _GNU_SOURCE
#define _GNU_SOURCE    // Nötig für asprintf()
#endif

#include <stdio.h>     // asprintf()
#include <stdlib.h>    // abort()
#include <unistd.h>    // usleep
#include <math.h>      // tanh
#include <GL/glut.h> 

#include "dashboard.h"
#include "./gles.h"
#include "./tile.h"
#include "draw.h"

#include <iostream>

// --------------------------------------------------------------------------
//  Hilfsfunktionen
// --------------------------------------------------------------------------
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

GLfloat temp2deg(GLfloat temp)
{

	// Wertebereich einschränken
	     if (temp > 120.0f) { temp = 120.0f; }
	else if (temp <  40.0f) { temp =  40.0f; }

	temp -= 40.0f;

	// Der Tacho besitzt 9 Markierungen im Abstand von 13.33 Grad.
	temp *= (9.0f * 13.33f) / 80.0f;

	// Offset für Nullstellung hinzufügen.
	temp = 150.0f - temp;

	return temp;
}

GLfloat fuel2deg(GLfloat val)
{

	// Wertebereich einschränken
	     if (val > 1.0f) { val = 1.0f; }
	else if (val < 0.0f) { val = 0.0f; }

	// Der Tacho besitzt 9 Markierungen im Abstand von 13.33 Grad.
	val *= (9.0f * 13.33f);

	// Offset für Nullstellung hinzufügen.
	val += -150.0f;

	return val;
}

GLfloat filter(GLfloat value, GLfloat *buffer)
{
	//EC *buffer = *buffer + tanh((value - *buffer) / 16.0f);
	*buffer= value;
	return *buffer;
}


// --------------------------------------------------------------------------
//  Oberfläche in Endlosschleife zeichnen
// --------------------------------------------------------------------------
void* draw_main(void *data)
{
	int ret;
	struct dashboard *db = (struct dashboard *)data;

	// OpenGL ES initialisieren
	struct opengles opengles;
	glesInitialize(&opengles);

	char *title = 0;
	ret = asprintf(&title, "dashboard-demo - %s - %s ", \
	                        db->dev, db->type);
	if (!ret) { abort(); }

	// Fenster Umbenennen
	XStoreName(opengles.xlib_display, opengles.xlib_window, title);

	// Textur für Dashboard laden
	struct tile dashboard = TILE_ZEROINIT;
	tileLoadPng(&opengles, &dashboard, "../bilder/own/dashboard.png");

	// Textur für Tachonadel laden
	struct tile needle = TILE_ZEROINIT;
	tileLoadPng(&opengles, &needle, "../bilder/own/pointer.png");

	GLuint flags = 0;
	GLuint counter = 0;
	GLfloat rpmdeg = 0.0;
	GLfloat kmhdeg = 0.0;
	GLfloat tempdeg = 0.0;
	GLfloat fueldeg = 0.0;
	do{
		kmhdeg = filter(kmh2deg(db->kmh), &kmhdeg);
		rpmdeg = filter(rpm2deg(db->rpm), &rpmdeg);


		// Framebuffer löschen.
		glClear(GL_COLOR_BUFFER_BIT);

		// Dashboard zeichnen
		tileDraw(&dashboard);

		GLfloat needleHeightOffset = 256.0 / 512.0;

		// ---- Linke Tachonadel zeichnen ---------------------------

		// Aktuelle Transformationsmatrix sichern.
		glPushMatrix();

			// Tachonadel an ihre richtige Position schieben.
			glTranslatef(-0.8, 0.155, 0);

			// Tachonadel rotieren
			glRotatef(kmhdeg, 0, 0, 1);

			// Rotationszentrum der Tachonadel korrigieren.
			glTranslatef(0, needleHeightOffset, 0);


			// Tachonadel zeichnen.
			tileDraw(&needle);

		// Transformationsmatrix wiederherstellen.
		glPopMatrix();


		// ---- Rechte Tachonadel zeichnen --------------------------
		glPushMatrix();

			// Tachonadel an ihre richtige Position schieben.
			glTranslatef(0.8, 0.155, 0);

			// Tachonadel rotieren
			glRotatef(rpmdeg, 0, 0, 1);

			// Rotationszentrum der Tachonadel korrigieren.
			glTranslatef(0, needleHeightOffset, 0);

			// Tachonadel zeichnen.
			tileDraw(&needle);

		glPopMatrix();
		
		// Das gezeichnete Bild sichtbar machen.
		glesDraw(&opengles);

		// 12ms warten um CPU-Last zu verringern.
		usleep(20 * 1000);

		// Counter inkrementieren.
		counter++;
	}
	while(glesRun(&opengles));

	// OpenGL ES Ressourcen freigeben.
	glesDestroy(&opengles);

	return 0;
}
