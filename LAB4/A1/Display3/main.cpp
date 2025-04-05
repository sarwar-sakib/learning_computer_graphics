
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
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    //SL
    //BODY
    glBegin(GL_POLYGON);
    glColor3ub(102, 203, 255);

    glVertex2f(-0.9f, 0.6f);
    glVertex2f(-0.1f, 0.6f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.9f, 0.2f);

    glEnd();

    //TRI  WHITE
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);

    glVertex2f(-0.5f, 0.55f);
    glVertex2f(-0.34f, 0.25f);
    glVertex2f(-0.66f, 0.25f);


    glEnd();

    //TRI  BLACK
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);

    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-0.38f, 0.25f);
    glVertex2f(-0.62f, 0.25f);


    glEnd();

     //TRI  BLACK
    glBegin(GL_POLYGON);
    glColor3ub(253, 209, 22);

    glVertex2f(-0.5f, 0.4f);
    glVertex2f(-0.34f, 0.25f);
    glVertex2f(-0.66f, 0.25f);



    glEnd();

    //CONGO
    //BODY
    glBegin(GL_POLYGON);
    glColor3ub(0, 128, 255);

    glVertex2f(0.1f, 0.8f);
    glVertex2f(0.9f, 0.8f);
    glVertex2f(0.9f, 0.2f);
    glVertex2f(0.1f, 0.2f);

    glEnd();

    //SIDE YELLOW
    glBegin(GL_POLYGON);
    glColor3ub(247, 215, 17);

    glVertex2f(0.1f, 0.35f);
    glVertex2f(0.84f, 0.8f);
    glVertex2f(0.9f, 0.8f);
    glVertex2f(0.9f, 0.65f);
    glVertex2f(0.16f, 0.2f);
    glVertex2f(0.1f, 0.2f);

    glEnd();

    //SIDE RED
    glBegin(GL_POLYGON);
    glColor3ub(207, 7, 27);

    glVertex2f(0.1f, 0.325f);

    glVertex2f(0.9f, 0.8f);
    glVertex2f(0.9f, 0.675f);

    glVertex2f(0.1f, 0.2f);

    glEnd();

    //STAR LEFT
    glBegin(GL_POLYGON);
    glColor3ub(247, 215, 17);

    glVertex2f(0.22f, 0.675f);
    glVertex2f(0.24f, 0.75f);
    glVertex2f(0.265f, 0.675f);
    glVertex2f(0.36f, 0.675f);
    glVertex2f(0.285f, 0.625f);
    glVertex2f(0.32f, 0.55f);
    glVertex2f(0.245f, 0.6f);
    glVertex2f(0.18f, 0.55f);
    glVertex2f(0.2f, 0.625f);
    glVertex2f(0.14f, 0.675f);

    glEnd();



    //

    //
    //BODY


    glBegin(GL_POLYGON);
    glColor3ub(118, 179, 222);

    glVertex2f(0.1f, -0.2f);
    glVertex2f(0.9f, -0.2f);
    glVertex2f(0.9f, -0.7f);
    glVertex2f(0.1f, -0.7f);

    glEnd();

     glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);

    glVertex2f(0.49f, -0.3f);
    glVertex2f(0.5f, -0.275f);
    glVertex2f(0.51f, -0.3f);
    glVertex2f(0.54f, -0.3f);
    glVertex2f(0.52f, -0.325f);
    glVertex2f(0.53f, -0.35f);
    glVertex2f(0.5f, -0.33f);
    glVertex2f(0.47f, -0.35f);
    glVertex2f(0.48f, -0.325f);
    glVertex2f(0.46f, -0.3f);

    glEnd();

glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255); // Dark blue-ish color

    glVertex2f(0.665f, -0.415f);
    glVertex2f(0.69f,  -0.41f);
    glVertex2f(0.675f, -0.445f);
    glVertex2f(0.7f,   -0.47f);
    glVertex2f(0.67f,  -0.465f);
    glVertex2f(0.66f,  -0.495f);
    glVertex2f(0.645f, -0.455f);
    glVertex2f(0.62f,  -0.45f);
    glVertex2f(0.64f,  -0.425f);
    glVertex2f(0.635f, -0.4f);

glEnd();

glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);

    glVertex2f(0.49f, -0.6f);
    glVertex2f(0.5f, -0.625f);
    glVertex2f(0.51f, -0.6f);
    glVertex2f(0.54f, -0.6f);
    glVertex2f(0.52f, -0.575f);
    glVertex2f(0.53f, -0.55f);
    glVertex2f(0.5f, -0.57f);
    glVertex2f(0.47f, -0.55f);
    glVertex2f(0.48f, -0.575f);
    glVertex2f(0.46f, -0.6f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);

    glVertex2f(0.335f, -0.415f);
    glVertex2f(0.31f,  -0.41f);
    glVertex2f(0.325f, -0.445f);
    glVertex2f(0.3f,   -0.47f);
    glVertex2f(0.33f,  -0.465f);
    glVertex2f(0.34f,  -0.495f);
    glVertex2f(0.355f, -0.455f);
    glVertex2f(0.38f,  -0.45f);
    glVertex2f(0.36f,  -0.425f);
    glVertex2f(0.365f, -0.4f);

    glEnd();

    //IS
    glBegin(GL_POLYGON);
    glColor3ub(0, 104, 71);

    glVertex2f(-0.9f, -0.2f);
    glVertex2f(-0.1f, -0.2f);
    glVertex2f(-0.1f, -0.3f);
    glVertex2f(-0.9f, -0.3f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 104, 71); // Blue

    glVertex2f(-0.9f, -0.6f);
    glVertex2f(-0.1f, -0.6f);
    glVertex2f(-0.1f, -0.7f);
    glVertex2f(-0.9f, -0.7f);
    glEnd();

    glLineWidth(4.0f);
     glBegin(GL_LINE_LOOP);
    glColor3ub(218, 40, 28); // Blue

    glVertex2f(-0.5f, -0.35f);
    glVertex2f(-0.4f, -0.45f);
    glVertex2f(-0.5f, -0.575f);
    glVertex2f(-0.6f, -0.45f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(218, 40, 28); // Blue

    glVertex2f(-0.58f, -0.375f);
    glVertex2f(-0.42f, -0.375f);
    glVertex2f(-0.42f, -0.55f);
    glVertex2f(-0.58f, -0.55f);
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
