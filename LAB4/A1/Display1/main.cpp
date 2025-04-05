#include <windows.h>
#include <GL/glut.h>
void renderBitmapString(float x, float y, float z, void *font, char *string) {
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //SUDAN
    //TOP RED
    glBegin(GL_POLYGON);
    glColor3ub(211, 15, 51);

    glVertex2f(-0.9f, 0.6f);
    glVertex2f(-0.1f, 0.6f);
    glVertex2f(-0.1f, 0.475f);
    glVertex2f(-0.9f, 0.475f);

    glEnd();

    //bottom black
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);

    glVertex2f(-0.9f, 0.325f);
    glVertex2f(-0.1f, 0.325f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.9f, 0.2f);

    glEnd();

    //left green
    glBegin(GL_POLYGON);
    glColor3ub(0, 115, 36);

    glVertex2f(-0.9f, 0.6f);
    glVertex2f(-0.6f, 0.4f);
    glVertex2f(-0.9f, 0.2f);

    glEnd();

    //SWEDEN
    //BLUE BG
    glBegin(GL_POLYGON);
    glColor3ub(0, 106, 168);

    glVertex2f(0.1f, 0.7f);
    glVertex2f(0.9f, 0.7f);
    glVertex2f(0.9f, 0.2f);
    glVertex2f(0.1f, 0.2f);

    glEnd();

    //YELLOW VERTICAL
    glBegin(GL_POLYGON);
    glColor3ub(254, 205, 0);

    glVertex2f(0.35f, 0.7f);
    glVertex2f(0.45f, 0.7f);
    glVertex2f(0.45f, 0.2f);
    glVertex2f(0.35f, 0.2f);

    glEnd();


    //YELLOW HORIZON
    glBegin(GL_POLYGON);
    glColor3ub(254, 205, 0);

    glVertex2f(0.1f, 0.5f);
    glVertex2f(0.9f, 0.5f);
    glVertex2f(0.9f, 0.4f);
    glVertex2f(0.1f, 0.4f);

    glEnd();

    //TONGA
    //BODY
    glBegin(GL_POLYGON);
    glColor3ub(195, 0, 0);

    glVertex2f(-0.6f, -0.5f);
    glVertex2f(-0.6f, -0.3f);
    glVertex2f(-0.1f, -0.3f);
    glVertex2f(-0.1f, -0.7f);
    glVertex2f(-0.9f, -0.7f);
    glVertex2f(-0.9f, -0.5f);

    glEnd();

    //VERT
    glBegin(GL_POLYGON);
    glColor3ub(195, 0, 0);

    glVertex2f(-0.78f, -0.325f);
    glVertex2f(-0.74f, -0.325f);
    glVertex2f(-0.74f, -0.475f);
    glVertex2f(-0.78f, -0.475f);

    glEnd();

    //HORI
    glBegin(GL_POLYGON);
    glColor3ub(195, 0, 0);

    glVertex2f(-0.82f, -0.375f);
    glVertex2f(-0.7f, -0.375f);
    glVertex2f(-0.7f, -0.425f);
    glVertex2f(-0.82f, -0.425f);

    glEnd();


    //VIETNAM
    //BODY
    glBegin(GL_POLYGON);
    glColor3ub(219, 32, 23);

    glVertex2f(0.1f, -0.2f);
    glVertex2f(0.9f, -0.2f);
    glVertex2f(0.9f, -0.7f);
    glVertex2f(0.1f, -0.7f);

    glEnd();

    //STAR
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);

    glVertex2f(0.46f, -0.4f);
    glVertex2f(0.5f, -0.3f);
    glVertex2f(0.54f, -0.4f);
    glVertex2f(0.65f, -0.4f);
    glVertex2f(0.56f, -0.45f);
    glVertex2f(0.6f, -0.55f);
    glVertex2f(0.5f, -0.48f);
    glVertex2f(0.4f, -0.55f);
    glVertex2f(0.44f, -0.45f);
    glVertex2f(0.35f, -0.4f);

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
