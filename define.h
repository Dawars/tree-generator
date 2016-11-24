#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vector.h"
#include "random.h"
#include "my_math.h"
#include "isosurface.h"
#include "blob.h"
#include "render.h"
#include "tree.h"
#include "save_obj.h"

#define VIEW_SIZE 20

void initialize();
void deconstruct();

void input();
void update();
void render();
void loop();
