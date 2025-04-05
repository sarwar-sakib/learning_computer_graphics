
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

    //SV
    //LEFT BLUE
    glBegin(GL_POLYGON);
    glColor3ub(0, 38, 116);

    glVertex2f(-0.9f, 0.7f);
    glVertex2f(-0.7f, 0.7f);
    glVertex2f(-0.7f, 0.2f);
    glVertex2f(-0.9f, 0.2f);

    glEnd();

    //bottom black
    glBegin(GL_POLYGON);
    glColor3ub(252, 208, 34);

    glVertex2f(-0.7f, 0.7f);
    glVertex2f(-0.7f, 0.2f);
    glVertex2f(-0.3f, 0.2f);
    glVertex2f(-0.3f, 0.7f);


    glEnd();

    //RIGHT green
    glBegin(GL_POLYGON);
    glColor3ub(0, 124, 46);

    glVertex2f(-0.3f, 0.2f);
    glVertex2f(-0.3f, 0.7f);
    glVertex2f(-0.1f, 0.7f);
    glVertex2f(-0.1f, 0.2f);

    glEnd();

    //left green SQ
    glBegin(GL_POLYGON);
    glColor3ub(0, 124, 46);

    glVertex2f(-0.56f, 0.5f);
    glVertex2f(-0.52f, 0.425f);
    glVertex2f(-0.56f, 0.35f);
    glVertex2f(-0.6f, 0.425f);

    glEnd();

    //RIGHT green SQ
    glBegin(GL_POLYGON);
    glColor3ub(0, 124, 46);

    glVertex2f(-0.44f, 0.5f);
    glVertex2f(-0.4f, 0.425f);
    glVertex2f(-0.44f, 0.35f);
    glVertex2f(-0.48f, 0.425f);

    glEnd();

    //MIDDLE green SQ
    glBegin(GL_POLYGON);
    glColor3ub(0, 124, 46);

    glVertex2f(-0.5f, 0.4f);
    glVertex2f(-0.46f, 0.325f);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(-0.54f, 0.325f);

    glEnd();

    //SYRIA
    //TOP RED
    glBegin(GL_POLYGON);
    glColor3ub(207, 9, 33);

    glVertex2f(0.1f, 0.8f);
    glVertex2f(0.9f, 0.8f);
    glVertex2f(0.9f, 0.6f);
    glVertex2f(0.1f, 0.6f);

    glEnd();

    //BOTTOM BLACK
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);

    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.9f, 0.4f);
    glVertex2f(0.9f, 0.2f);
    glVertex2f(0.1f, 0.2f);

    glEnd();

    //STAR LEFT
    glBegin(GL_POLYGON);
    glColor3ub(0, 123, 58);

    glVertex2f(0.28f, 0.525f);
    glVertex2f(0.3f, 0.575f);
    glVertex2f(0.32f, 0.525f);
    glVertex2f(0.38f, 0.525f);
    glVertex2f(0.335f, 0.49f);
    glVertex2f(0.36f, 0.425f);
    glVertex2f(0.3f, 0.47f);
    glVertex2f(0.24f, 0.425f);
    glVertex2f(0.275f, 0.49f);
    glVertex2f(0.22f, 0.525f);

    glEnd();


    //STAR RIGHT
    glBegin(GL_POLYGON);
    glColor3ub(0, 123, 58);

    glVertex2f(0.68f, 0.525f);
    glVertex2f(0.7f, 0.575f);
    glVertex2f(0.72f, 0.525f);
    glVertex2f(0.78f, 0.525f);
    glVertex2f(0.735f, 0.49f);
    glVertex2f(0.76f, 0.425f);
    glVertex2f(0.7f, 0.47f);
    glVertex2f(0.64f, 0.425f);
    glVertex2f(0.675f, 0.49f);
    glVertex2f(0.62f, 0.525f);

    glEnd();




    //NORWAY
    //BODY
    glBegin(GL_POLYGON);
    glColor3ub(187, 4, 43);

    glVertex2f(-0.9f, -0.2f);
    glVertex2f(-0.1f, -0.2f);
    glVertex2f(-0.1f, -0.7f);
    glVertex2f(-0.9f, -0.7f);

    glEnd();

    //VERT
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);

    glVertex2f(-0.7f, -0.2f);
    glVertex2f(-0.6f, -0.2f);
    glVertex2f(-0.6f, -0.7f);
    glVertex2f(-0.7f, -0.7f);

    glEnd();

    //HORI
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);

    glVertex2f(-0.9f, -0.4f);
    glVertex2f(-0.1f, -0.4f);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(-0.9f, -0.5f);

    glEnd();

     //VERT
    glBegin(GL_POLYGON);
    glColor3ub(0, 26, 91);

     glVertex2f(-0.68f, -0.2f);
    glVertex2f(-0.62f, -0.2f);
    glVertex2f(-0.62f, -0.7f);
    glVertex2f(-0.68f, -0.7f);

    glEnd();

    //HORI
    glBegin(GL_POLYGON);
    glColor3ub(0, 26, 91);

    glVertex2f(-0.9f, -0.425f);
    glVertex2f(-0.1f, -0.425f);
    glVertex2f(-0.1f, -0.475f);
    glVertex2f(-0.9f, -0.475f);

    glEnd();

    //BAHRAIN
    //BODY
    glBegin(GL_POLYGON);
    glColor3ub(219, 32, 23);

    glVertex2f(0.3f, -0.15f);
    glVertex2f(0.9f, -0.15f);
    glVertex2f(0.9f, -0.65f);
    glVertex2f(0.3f, -0.65f);

    glEnd();

    //TRIANGLE
 glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 255);

    glVertex2f(0.3f, -0.15f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.3f, -0.25f);


    glVertex2f(0.3f, -0.25f);
    glVertex2f(0.4f, -0.3f);
    glVertex2f(0.3f, -0.35f);


    glVertex2f(0.3f, -0.35f);
    glVertex2f(0.4f, -0.4f);
    glVertex2f(0.3f, -0.45f);


    glVertex2f(0.3f, -0.45f);
    glVertex2f(0.4f, -0.5f);
    glVertex2f(0.3f, -0.55f);


    glVertex2f(0.3f, -0.55f);
    glVertex2f(0.4f, -0.6f);
    glVertex2f(0.3f, -0.65f);

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
