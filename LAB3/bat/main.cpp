#include <windows.h> // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void renderBitmapString(float x, float y, float z, void *font, char *string) {
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.65f, 0.1f);
    glVertex2f(0.7f, 0.1f);
    glVertex2f(0.7f, -0.15f);
    glVertex2f(-0.65f, -0.15f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.1f, 0.35f);
    glVertex2f(0.15f, 0.35f);
    glVertex2f(0.15f, -0.3f);
    glVertex2f(-0.1f, -0.3f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.45f, 0.3f);
    glVertex2f(-0.3f, 0.3f);
    glVertex2f(-0.3f, -0.35f);
    glVertex2f(-0.45f, -0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(0.35f, 0.3f);
    glVertex2f(0.5f, 0.3f);
    glVertex2f(0.5f, -0.35f);
    glVertex2f(0.35f, -0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.1f, 0.4f);
    glVertex2f(-0.05f, 0.4f);
    glVertex2f(-0.05f, 0.35f);
    glVertex2f(-0.1f, 0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.15f, 0.4f);
    glVertex2f(0.15f, 0.35f);
    glVertex2f(0.1f, 0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.05f, -0.3f);
    glVertex2f(0.1f, -0.3f);
    glVertex2f(0.1f, -0.4f);
    glVertex2f(-0.05f, -0.4f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(0.75f, 0.15f);
    glVertex2f(0.8f, 0.15f);
    glVertex2f(0.8f, -0.2f);
    glVertex2f(0.75f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);//yellow color

    glVertex2f(0.7f, 0.15f);
    glVertex2f(0.75f, 0.15f);
    glVertex2f(0.75f, -0.2f);
    glVertex2f(0.7f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.75f, 0.15f);
    glVertex2f(-0.7f, 0.15f);
    glVertex2f(-0.7f, -0.2f);
    glVertex2f(-0.75f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);//yellow color

    glVertex2f(-0.7f, 0.15f);
    glVertex2f(-0.65f, 0.15f);
    glVertex2f(-0.65f, -0.2f);
    glVertex2f(-0.7f, -0.2f);



    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.4f, 0.5f);
    glVertex2f(0.45f, 0.5f);
    glVertex2f(0.45f, 0.45f);
    glVertex2f(-0.4f, 0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);//yellow color


    glVertex2f(0.45f, 0.45f);
    glVertex2f(0.45f, 0.4f);
    glVertex2f(-0.4f, 0.4f);
    glVertex2f(-0.4f, 0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);//yellow color

    glVertex2f(-0.4f, -0.5f);
    glVertex2f(0.45f, -0.5f);
    glVertex2f(0.45f, -0.55f);
    glVertex2f(-0.4f, -0.55f);
    glEnd();


     glFlush(); // Render now
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640); // Set the window's initial width & height
    glutInitWindowPosition(0, 50);  // Set the window's initial position according to the monitor
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop(); // Enter the event-processing loop
    return 0;
}
