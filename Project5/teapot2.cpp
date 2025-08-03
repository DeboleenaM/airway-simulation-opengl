#include <GL/glut.h>

float Tx = 0;
float Ty = 0;
float Tz = -10;

float angle = 0.0f;         // Rotation angle
int rotateDirection = 0;    // 0 = stop, 1 = clockwise, -1 = counter-clockwise

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(Tx, Ty, Tz, 0, 0, 0, 0, 1, 0);

    glColor3f(0.6f, 0.3f, 0.0f); // Brown

    glPushMatrix();
    glRotatef(angle, 0, 1, 0);  // Rotate around Y-axis
    glutSolidTeapot(0.5);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, (float)width / height, 1, 1000);
}

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': Tx++; break;
    case 's': Tx--; break;
    case 'w': Ty++; break;
    case 'd': Ty--; break;
    case 'n': Tz++; break;
    case 't': Tz--; break;
    default: break;
    }
    glutPostRedisplay(); //scene updating
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            rotateDirection = 1;  // Clockwise
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            rotateDirection = -1; // Counter-clockwise
        }
    }
    else if (state == GLUT_UP) {
        rotateDirection = 0;  // Stop rotation on mouse release
    }
}

void rotateTeapot() {
    if (rotateDirection != 0) {
        angle += rotateDirection * 1.0f;
        if (angle >= 360.0f || angle <= -360.0f)
            angle = 0.0f;
        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutCreateWindow("Rotating Brown Teapot");

    glEnable(GL_DEPTH_TEST);
    initLighting();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPress);
    glutMouseFunc(mouseClick);
    glutIdleFunc(rotateTeapot); // Called repeatedly in background

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 1000);

    glutMainLoop();
    return 0;
}