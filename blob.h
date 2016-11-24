#ifndef _BLOB
#define _BLOB

#include "vector.h"
void blob_init();

void blob_deconstruct();

void blob_update();

void blob_render();

typedef struct{
    Vec3 *pos;
    Vec3 *vel;
    double size;
}Blob;

Blob* blob_new(Vec3*, Vec3*, double);

Vector* getBlobs();

#endif // _BLOB
