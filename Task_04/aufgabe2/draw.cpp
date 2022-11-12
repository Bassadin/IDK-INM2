#include <stdio.h>	// printf, fprintf
#include <math.h>	// z.B. M_PI, cos(), sin()
#include <GL/glut.h>
#include "../lib/gles.h" // struct opengles, gles*-Funktionen
#include "../lib/tile.h" // struct tile, loadPngTile

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