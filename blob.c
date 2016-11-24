#include "define.h"

Vector blobs;

void blob_init(){
    int i;

    vector_new(&blobs);

    for(i = 0; i < 30; i++){
        Blob* blob = blob_new(
        vec3_new(randDouble(-5, 5), randDouble(-5, 5), randDouble(-5, 5)),
        vec3_new(randDouble(-1, 1), randDouble(-1, 1), randDouble(-1, 1)),
        randDouble(3, 6));
        vector_add(&blobs, blob);
    }
}

void blob_deconstruct(){
    int i;
    Blob* temp;
    for(i = 0; i < vector_size(&blobs); i++){
        temp = (Blob*) vector_get(&blobs, i);
        free(temp->pos);
        free(temp->vel);
    }
    vector_free_array(&blobs);
}

void blob_update(){
    //move VIEW_SIZE
    int i;
    for(i = 0; i < vector_size(&blobs); i++){
        Blob* b = (Blob*)vector_get(&blobs, i);
        b->pos->x += b->vel->x * 0.5;
        b->pos->y += b->vel->y * 0.5;
        b->pos->z += b->vel->z * 0.5;

        if(b->pos->x < -VIEW_SIZE/2 || b->pos->x > VIEW_SIZE/2)
            b->vel->x *= -1;

        if(b->pos->y < -VIEW_SIZE/2 || b->pos->y > VIEW_SIZE/2)
            b->vel->y *= -1;

        if(b->pos->z < -VIEW_SIZE/2 || b->pos->z > VIEW_SIZE/2)
            b->vel->z *= -1;
    }
}

void blob_render(){
    int i;

    glColor3f(1, 0, 0);
    for(i = 0; i < vector_size(&blobs); i++){
        Blob* b = (Blob*)vector_get(&blobs, i);
        glPushMatrix();
        glTranslatef(b->pos->x, b->pos->y, b->pos->z);
        glutSolidSphere(0.2f, 5, 5);

        glPopMatrix();
    }
}

Vector* getBlobs(){
    return &blobs;
}

Blob* blob_new(Vec3 *pos, Vec3 *vel, double size){
    Blob* b = (Blob*)malloc(sizeof(Blob));
	b->pos = pos;
	b->vel = vel;
	b->size = size;
	return b;
}
