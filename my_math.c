/*
 * my_math.c
 *
 *  Created on: Nov 3, 2015
 *      Author: dawars
 */

#include "my_math.h"
#include "define.h"

Vec2* vec2_new(double x, double y){
	Vec2* vec = (Vec2*)malloc(sizeof(Vec2));
	vec->x = x;
	vec->y = y;
	return vec;
}

Vec3* vec3_new(double x, double y, double z){
	Vec3* vec = (Vec3*)malloc(sizeof(Vec3));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return vec;
}

void vec3_new_static(Vec3 *vec, double x, double y, double z){
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

Triangle* triangle_copy(Triangle *tri){
    Triangle* out = (Triangle*)malloc(sizeof(Triangle));
    memcpy(out, tri, sizeof(Triangle));
    return out;
}
