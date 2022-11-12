#include <GL/glut.h>

#include <stdio.h>	// printf, fprintf
#include <stdlib.h> // exit
#include <unistd.h> // sleep

static GLfloat kmh2deg(GLfloat kmh)
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

static GLfloat rpm2deg(GLfloat rpm)
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