#include "define.h"

double camera[3] = {1, 0.1, 1};
int orbitDegrees = 0;
int zoom = 32;

int threshold = 10;
int res = 1;

int frame = 0, zeit, timebase = 0;
char s[50];
int w, h;

void changeSize(int ww, int hh) {
    w = ww; h = hh;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27) {
		  exit(0);
	}

	if (key == 's') {
		save_obj();
		tree_update();
		//new_tree();
	}
        
}

void pressKey(int key, int x, int y){

    if(key == GLUT_KEY_UP && zoom > 1)
        zoom--;
    if(key == GLUT_KEY_DOWN)
        zoom++;
    if(key == GLUT_KEY_RIGHT)
        threshold++;
    if(key == GLUT_KEY_LEFT && threshold > 1)
        threshold--;
    if(key == GLUT_KEY_PAGE_UP)
        res++;
    if(key == GLUT_KEY_PAGE_DOWN && res > 1)
        res--;
}

int prevX = 0;
void mouseMove(int x, int y) {
    // update deltaAngle
    int dX = x - prevX;
    prevX = x;
    orbitDegrees += -(dX)/4.0;
}

void mouseButton(){

}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, w, h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Tree Generator");

	// register callbacks
	glutDisplayFunc(loop);
	glutReshapeFunc(changeSize);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
//	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	//glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouseMove);

	initialize();

	// enter GLUT event processing cycle
	glutMainLoop();

    deconstruct();

	return 1;
}

void initialize(){
    srand(time(NULL));

    blob_init();
    isosurface_init();

    tree_init();

    glEnable(GL_DEPTH_TEST);
}

void deconstruct(){
    blob_deconstruct();
    isosurface_deconstruct();
    tree_deconstruct();
}


void input(){
    camera[0] = zoom * cos(M_PI * orbitDegrees/180);
    camera[2] = zoom * -sin(M_PI * orbitDegrees/180);
}

void update(){
    //move blobs
    //blob_update();
    //compute field
    //isosurface_update(res, threshold);

    //tree_update();
}
void render(){

    blob_render();
    //isosurface_render();
    tree_render();

    glutPostRedisplay();
}

void loop(){
    input();
    update();

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(camera[0], camera[1], camera[2], /* look from camera XYZ */
               0, 0, 0, /* look at the origin */
               0, 1, 0); /* positive Y up vector */
    //glRotatef(orbitDegrees, 0.f, 1.f, 0.f);/* orbit the Y axis */

	glPushMatrix();
	glLoadIdentity();
        render();

// Code to compute frames per second
	frame++;

	zeit=glutGet(GLUT_ELAPSED_TIME);
	if (zeit - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",
			frame*1000.0/(zeit-timebase));
		timebase = zeit;
		frame = 0;
	}

        // Code to display a string (fps) with bitmap fonts
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_18,s);
	glPopMatrix();

	restorePerspectiveProjection();

    glutSwapBuffers();
}
