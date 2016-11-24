#ifndef _ISOSURFACE
#define _ISOSURFACE

void isosurface_init();

void isosurface_update(double, double);

void isosurface_render();

void isosurface_deconstruct();

int isosurface_polygonise(double, double, double, double, Triangle*);
#endif
