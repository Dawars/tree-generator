#include "define.h"

extern Vector tris;
extern Vector trunk_mesh;
extern double tree_height;

void save_obj() {
	FILE * file;
	int i, j;
	file = fopen("tree_save.obj", "w");
	Triangle * tri;

	for (i = 0; i < vector_size(&tris); i++) {
		tri = (Triangle *)vector_get(&tris, i);
		fprintf(file, "v %f %f %f\n", tri->p[0].x, tri->p[0].y + tree_height, tri->p[0].z);
		fprintf(file, "v %f %f %f\n", tri->p[1].x, tri->p[1].y + tree_height, tri->p[1].z);
		fprintf(file, "v %f %f %f\n", tri->p[2].x, tri->p[2].y + tree_height, tri->p[2].z);
	}


	for (i = 0; i < vector_size(&trunk_mesh); i++) {

		tri = (Triangle *)vector_get(&trunk_mesh, i);
		fprintf(file, "v %f %f %f\n", tri->p[0].x, tri->p[0].y + tree_height, tri->p[0].z);
		fprintf(file, "v %f %f %f\n", tri->p[1].x, tri->p[1].y + tree_height, tri->p[1].z);
		fprintf(file, "v %f %f %f\n", tri->p[2].x, tri->p[2].y + tree_height, tri->p[2].z);
	}


	for (i = 1; i < vector_size(&tris)*3; i += 3) {
		fprintf(file, "f %d %d %d\n", i, i + 1, i + 2);
	}
	
	for (j=i; j < i+vector_size(&trunk_mesh)*3; j += 3) {
		fprintf(file, "f %d %d %d\n", j, j + 1, j + 2);
	}

	fclose(file);
	printf("file written");
}