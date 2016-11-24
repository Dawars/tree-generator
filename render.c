#include "define.h"

void renderBitmapString(float x, float y, float z, void *font, char *string) {

	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

