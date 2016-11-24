/*
 * my_math.h
 *
 *  Created on: Nov 3, 2015
 *      Author: dawars
 */

#ifndef _MY_MATH
#define _MY_MATH

#include <math.h>

typedef struct {
	double x, y;
} Vec2;

typedef struct {
	double x, y, z;
} Vec3;

Vec2* vec2_new(double, double);
Vec3* vec3_new(double, double, double);
void vec3_new_static(Vec3*, double, double, double);

typedef struct {
   Vec3 p[3];
} Triangle;

Triangle* triangle_copy(Triangle*);

#endif
