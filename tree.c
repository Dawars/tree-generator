#include "define.h"

double tree_height, radiusMin, radiusMax;
int trunk_res;

Vector trunk_mesh;

void cylinder(Vector*, Vec3*, float, float, float, int);

void tree_init(){
    tree_update();
}

void tree_deconstruct(){

    isosurface_deconstruct();
    blob_deconstruct();

    vector_free_array(&trunk_mesh);
}

void tree_update(){

    tree_deconstruct();

    //generate parameters
    tree_height = randDouble(8, 15);
    radiusMin = randDouble(tree_height / 20, tree_height / 15);
    radiusMax = randDouble(radiusMin + 0.5, radiusMin + 1);

    trunk_res = 7;

    vector_new(&trunk_mesh);

    Vec3 origin;
    vec3_new_static(&origin, 0, -tree_height/2, 0);

    //generate mesh
    cylinder(&trunk_mesh, &origin, radiusMin, radiusMax, tree_height, trunk_res);

    //generate leaves
    blob_init();
    isosurface_init();
    isosurface_update(1, 10);//update vals in update
}

void tree_render(){
    int i;


    glColor3f(76.0/255, 79.0/255, 9.0/255);

    glBegin(GL_TRIANGLES);
        for(i = 0; i < trunk_mesh.size; i++){
            Triangle *tri = (Triangle*) vector_get(&trunk_mesh, i);

            glVertex3d(tri->p[0].x, tri->p[0].y, tri->p[0].z);
            glVertex3d(tri->p[1].x, tri->p[1].y, tri->p[1].z);
            glVertex3d(tri->p[2].x, tri->p[2].y, tri->p[2].z);


        }
    glEnd();

    isosurface_render();
}

void cylinder(Vector* mesh, Vec3* origin, float radMin, float radMax, float height, int res){
    int i;
    float theta;

    Vec3 prev[2], curr[2];

    for(i = 0; i <= res; i++){
        theta = 2.0 / res * i * M_PI;

        curr[0].x = radMax * cos(theta) + origin->x;
        curr[0].y = -height / 2         + origin->y;
        curr[0].z = radMax * sin(theta) + origin->z;

        curr[1].x = radMin * cos(theta) + origin->x;
        curr[1].y = height / 2          + origin->y;
        curr[1].z = radMin * sin(theta) + origin->z;

        if(i>0){
            Triangle tri;
            tri.p[0] = prev[0];
            tri.p[1] = prev[1];
            tri.p[2] = curr[0];

            vector_add(mesh, triangle_copy(&tri));

			tri.p[0] = curr[1];
			tri.p[1] = curr[0];
			tri.p[2] = prev[1];

            vector_add(mesh, triangle_copy(&tri));

        }
        prev[0] = curr[0];
        prev[1] = curr[1];
    }
}
