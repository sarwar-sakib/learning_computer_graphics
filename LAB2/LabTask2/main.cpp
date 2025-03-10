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
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //background color
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    //Horizontal Line
    glLineWidth(2.0f); //line thickness

    glBegin(GL_LINES);
    glColor3ub(0, 255, 0);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    //vertical line
    glBegin(GL_LINES);
    glColor3ub(0, 255, 0);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    //Hexagon
    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);//yellow color

    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.6f, 0.3f);
    glVertex2f(0.7f, 0.5f);
    glVertex2f(0.6f, 0.7f);
    glVertex2f(0.4f, 0.7f);
    glVertex2f(0.3f, 0.5f);
    glEnd();

    //Top-left Triangle
    glBegin(GL_POLYGON);
    glColor3ub(255,0,0);//red color

    glVertex2f(-0.7f, 0.4f);
    glVertex2f(-0.3f, 0.4f);
    glVertex2f(-0.5f, 0.7f);
    glEnd();

    //Square
    glBegin(GL_POLYGON);
    glColor3ub(0,255,0);// green color

    glVertex2f(-0.7f, -0.7f);
    glVertex2f(-0.3f, -0.7f);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(-0.7f, -0.3f);
    glEnd();

    //bottom-right Triangle
    glBegin(GL_POLYGON);
    glColor3ub(232, 133, 20);// orange color

    glVertex2f(0.4f, -0.7f);
    glVertex2f(0.6f, -0.7f);
    glVertex2f(0.5f, -0.2f);
    glEnd();

     glFlush(); // Render now
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(480, 480); // Set the window's initial width & height
    glutInitWindowPosition(0, 50);  // Set the window's initial position according to the monitor
    glutCreateWindow("LAB TASK 2"); // Create a window with the given title
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop(); // Enter the event-processing loop
    return 0;
}
