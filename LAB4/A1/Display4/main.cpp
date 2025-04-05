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
    //1
    glBegin(GL_POLYGON);
    glColor3ub(211, 15, 51);
    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.1f, 0.75f);
    glVertex2f(-0.1f, 0.7f);
    glVertex2f(-0.9f, 0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(211, 15, 51);
    glVertex2f(-0.9f, 0.65f);
    glVertex2f(-0.1f, 0.65f);
    glVertex2f(-0.1f, 0.6f);
    glVertex2f(-0.9f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(211, 15, 51);
    glVertex2f(-0.9f, 0.55f);
    glVertex2f(-0.1f, 0.55f);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(-0.9f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(211, 15, 51);
    glVertex2f(-0.9f, 0.45f);
    glVertex2f(-0.1f, 0.45f);
    glVertex2f(-0.1f, 0.4f);
    glVertex2f(-0.9f, 0.4f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(211, 15, 51);
    glVertex2f(-0.9f, 0.35f);
    glVertex2f(-0.1f, 0.35f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.9f, 0.3f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(211, 15, 51);
    glVertex2f(-0.9f, 0.25f);
    glVertex2f(-0.1f, 0.25f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.9f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 39, 104);
    glVertex2f(-0.9f, 0.75f);
    glVertex2f(-0.7f, 0.75f);
    glVertex2f(-0.7f, 0.5f);
    glVertex2f(-0.9f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.82f, 0.65f);
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.78f, 0.65f);
    glVertex2f(-0.74f, 0.65f);
    glVertex2f(-0.78f, 0.62f);
    glVertex2f(-0.76f, 0.55f);
    glVertex2f(-0.8f, 0.6f);
    glVertex2f(-0.84f, 0.55f);
    glVertex2f(-0.82f, 0.62f);
    glVertex2f(-0.86f, 0.65f);
    glEnd();

    //2
    glBegin(GL_POLYGON);
    glColor3ub(1, 34, 105);
    glVertex2f(0.1f, 0.6f);
    glVertex2f(0.9f, 0.6f);
    glVertex2f(0.9f, 0.2f);
    glVertex2f(0.1f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.1f, 0.425f);
    glVertex2f(0.46f, 0.6f);
    glVertex2f(0.5f, 0.6f);
    glVertex2f(0.5f, 0.575f);
    glVertex2f(0.14f, 0.4f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(200, 15, 46);
    glVertex2f(0.12f, 0.4f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.48f, 0.6f);
    glVertex2f(0.5f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(0.1f, 0.575f);
    glVertex2f(0.1f, 0.6f);
    glVertex2f(0.14f, 0.6f);
    glVertex2f(0.5f, 0.425f);
    glVertex2f(0.5f, 0.4f);
    glVertex2f(0.46f, 0.4f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(200, 15, 46);
    glVertex2f(0.1f, 0.59f);
    glVertex2f(0.1f, 0.6f);
    glVertex2f(0.5f, 0.4f);
    glVertex2f(0.48f, 0.4f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(0.26f, 0.6f);
    glVertex2f(0.34f, 0.6f);
    glVertex2f(0.34f, 0.4f);
    glVertex2f(0.26f, 0.4f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(0.1f, 0.475f);
    glVertex2f(0.1f, 0.525f);
    glVertex2f(0.5f, 0.525f);
    glVertex2f(0.5f, 0.475f);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(200, 15, 46);
    glVertex2f(0.1f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.3f, 0.6f);
    glVertex2f(0.3f, 0.4f);
    glEnd();

    glLineWidth(0.1f);
    glBegin(GL_POLYGON);
    glColor3ub(200, 15, 46);
    glVertex2f(0.69f, 0.53f);
    glVertex2f(0.7f, 0.55f);
    glVertex2f(0.71f, 0.53f);
    glVertex2f(0.73f, 0.53f);
    glVertex2f(0.71f, 0.52f);
    glVertex2f(0.72f, 0.5f);
    glVertex2f(0.7f, 0.51f);
    glVertex2f(0.68f, 0.49f);
    glVertex2f(0.69f, 0.52f);
    glVertex2f(0.67f, 0.53f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(255,255,255);
    glVertex2f(0.69f, 0.53f);
    glVertex2f(0.7f, 0.55f);
    glVertex2f(0.71f, 0.53f);
    glVertex2f(0.73f, 0.53f);
    glVertex2f(0.71f, 0.52f);
    glVertex2f(0.72f, 0.5f);
    glVertex2f(0.7f, 0.51f);
    glVertex2f(0.68f, 0.49f);
    glVertex2f(0.69f, 0.52f);
    glVertex2f(0.67f, 0.53f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(200, 15, 46);
    glVertex2f(0.69f, 0.29f);
    glVertex2f(0.7f, 0.31f);
    glVertex2f(0.71f, 0.29f);
    glVertex2f(0.73f, 0.29f);
    glVertex2f(0.71f, 0.28f);
    glVertex2f(0.72f, 0.26f);
    glVertex2f(0.7f, 0.27f);
    glVertex2f(0.68f, 0.25f);
    glVertex2f(0.69f, 0.28f);
    glVertex2f(0.67f, 0.29f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(255,255,255);
    glVertex2f(0.69f, 0.29f);
    glVertex2f(0.7f, 0.31f);
    glVertex2f(0.71f, 0.29f);
    glVertex2f(0.73f, 0.29f);
    glVertex2f(0.71f, 0.28f);
    glVertex2f(0.72f, 0.26f);
    glVertex2f(0.7f, 0.27f);
    glVertex2f(0.68f, 0.25f);
    glVertex2f(0.69f, 0.28f);
    glVertex2f(0.67f, 0.29f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(200, 15, 46);
    glVertex2f(0.60f, 0.43f);
    glVertex2f(0.61f, 0.45f);
    glVertex2f(0.62f, 0.43f);
    glVertex2f(0.64f, 0.43f);
    glVertex2f(0.62f, 0.42f);
    glVertex2f(0.63f, 0.40f);
    glVertex2f(0.61f, 0.41f);
    glVertex2f(0.59f, 0.39f);
    glVertex2f(0.60f, 0.42f);
    glVertex2f(0.58f, 0.43f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(255,255,255);
    glVertex2f(0.60f, 0.43f);
    glVertex2f(0.61f, 0.45f);
    glVertex2f(0.62f, 0.43f);
    glVertex2f(0.64f, 0.43f);
    glVertex2f(0.62f, 0.42f);
    glVertex2f(0.63f, 0.40f);
    glVertex2f(0.61f, 0.41f);
    glVertex2f(0.59f, 0.39f);
    glVertex2f(0.60f, 0.42f);
    glVertex2f(0.58f, 0.43f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(200, 15, 46);
    glVertex2f(0.77f, 0.46f);
    glVertex2f(0.78f, 0.48f);
    glVertex2f(0.79f, 0.46f);
    glVertex2f(0.81f, 0.46f);
    glVertex2f(0.79f, 0.45f);
    glVertex2f(0.80f, 0.43f);
    glVertex2f(0.78f, 0.44f);
    glVertex2f(0.76f, 0.42f);
    glVertex2f(0.77f, 0.45f);
    glVertex2f(0.75f, 0.46f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(255,255,255);
    glVertex2f(0.77f, 0.46f);
    glVertex2f(0.78f, 0.48f);
    glVertex2f(0.79f, 0.46f);
    glVertex2f(0.81f, 0.46f);
    glVertex2f(0.79f, 0.45f);
    glVertex2f(0.80f, 0.43f);
    glVertex2f(0.78f, 0.44f);
    glVertex2f(0.76f, 0.42f);
    glVertex2f(0.77f, 0.45f);
    glVertex2f(0.75f, 0.46f);
    glEnd();

    //3
    glBegin(GL_POLYGON);
    glColor3ub(254, 0, 0);
    glVertex2f(0.1f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.3f, -0.7f);
    glVertex2f(0.1f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(254, 0, 0);
    glVertex2f(0.7f, -0.3f);
    glVertex2f(0.9f, -0.3f);
    glVertex2f(0.9f, -0.7f);
    glVertex2f(0.7f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(254, 0, 0);
    glVertex2f(0.5f, -0.56f);
    glVertex2f(0.42f, -0.575f);
    glVertex2f(0.5f, -0.35f);
    glVertex2f(0.58f, -0.575f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(254, 0, 0);
    glVertex2f(0.5f, -0.45f);
    glVertex2f(0.5f, -0.65f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(254, 0, 0);
    glVertex2f(0.44f, -0.56f);
    glVertex2f(0.36f, -0.5f);
    glVertex2f(0.39f, -0.5f);
    glVertex2f(0.38f, -0.45f);
    glVertex2f(0.42f, -0.46f);
    glVertex2f(0.42f, -0.44f);
    glVertex2f(0.46f, -0.48f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(254, 0, 0);
    glVertex2f(0.46f, -0.48f);
    glVertex2f(0.45f, -0.4f);
    glVertex2f(0.47f, -0.41f);
    glVertex2f(0.5f, -0.36f);
    glVertex2f(0.53f, -0.41f);
    glVertex2f(0.55f, -0.4f);
    glVertex2f(0.54f, -0.48f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(254, 0, 0);
    glVertex2f(0.56f, -0.56f);
    glVertex2f(0.63f, -0.5f);
    glVertex2f(0.62f, -0.5f);
    glVertex2f(0.62f, -0.45f);
    glVertex2f(0.58f, -0.46f);
    glVertex2f(0.58f, -0.44f);
    glVertex2f(0.54f, -0.48f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(207, 9, 33);
    glVertex2f(-0.9f, -0.2f);
    glVertex2f(-0.1f, -0.2f);
    glVertex2f(-0.1f, -0.7f);
    glVertex2f(-0.9f, -0.7f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 39, 128);
    glVertex2f(-0.9f, -0.2f);
    glVertex2f(-0.5f, -0.2f);
    glVertex2f(-0.5f, -0.45f);
    glVertex2f(-0.9f, -0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.71f, -0.24f);
    glVertex2f(-0.7f, -0.22f);
    glVertex2f(-0.69f, -0.24f);
    glVertex2f(-0.67f, -0.24f);
    glVertex2f(-0.69f, -0.25f);
    glVertex2f(-0.68f, -0.27f);
    glVertex2f(-0.7f, -0.26f);
    glVertex2f(-0.72f, -0.27f);
    glVertex2f(-0.71f, -0.25f);
    glVertex2f(-0.73f, -0.24f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.61f, -0.31f);
    glVertex2f(-0.6f, -0.29f);
    glVertex2f(-0.59f, -0.31f);
    glVertex2f(-0.57f, -0.31f);
    glVertex2f(-0.59f, -0.32f);
    glVertex2f(-0.58f, -0.34f);
    glVertex2f(-0.6f, -0.33f);
    glVertex2f(-0.62f, -0.34f);
    glVertex2f(-0.61f, -0.32f);
    glVertex2f(-0.63f, -0.31f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.65f, -0.35f);
    glVertex2f(-0.64f, -0.33f);
    glVertex2f(-0.63f, -0.35f);
    glVertex2f(-0.61f, -0.35f);
    glVertex2f(-0.63f, -0.36f);
    glVertex2f(-0.62f, -0.38f);
    glVertex2f(-0.64f, -0.37f);
    glVertex2f(-0.66f, -0.38f);
    glVertex2f(-0.65f, -0.36f);
    glVertex2f(-0.67f, -0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.71f, -0.41f);
    glVertex2f(-0.7f, -0.39f);
    glVertex2f(-0.69f, -0.41f);
    glVertex2f(-0.67f, -0.41f);
    glVertex2f(-0.69f, -0.42f);
    glVertex2f(-0.68f, -0.44f);
    glVertex2f(-0.7f, -0.43f);
    glVertex2f(-0.72f, -0.44f);
    glVertex2f(-0.71f, -0.42f);
    glVertex2f(-0.73f, -0.41f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-0.81f, -0.31f);
    glVertex2f(-0.8f, -0.29f);
    glVertex2f(-0.79f, -0.31f);
    glVertex2f(-0.77f, -0.31f);
    glVertex2f(-0.79f, -0.32f);
    glVertex2f(-0.78f, -0.34f);
    glVertex2f(-0.8f, -0.33f);
    glVertex2f(-0.82f, -0.34f);
    glVertex2f(-0.81f, -0.32f);
    glVertex2f(-0.83f, -0.31f);
    glEnd();

     glFlush(); // Render now
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(0, 50);
    glutCreateWindow("OpenGL Setup Test");
    glutDisplayFunc(display);
    glutMainLoop();
}
