#include <windows.h>
#include <GL/glut.h>
#include<math.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


GLfloat PI = 3.14159265358979323846f;
bool isSoundOn = false;
bool showInstructions = true;
int toggle = 0;
int trigger = 0;
GLfloat speed = 0.01f;
GLfloat speed1 = 0.01f;
GLfloat busX = -1.2f;
GLfloat busX1 = -1.5f;
GLfloat trainX = -2.0f;
GLfloat busSpeed = 0.005f;
GLfloat busSpeed1 = 0.008f;
GLfloat trainSpeed = 0.008f;
GLfloat position = 0.0f;
GLfloat position2 = 0.0f;
GLfloat position3 = 0.0f;
GLfloat cloudOffset = 0.0f;

GLfloat i = 0.0f;
GLfloat planeX = -2.0f;
GLfloat planeY = -0.5f;
GLfloat cloudX = 0.0f;
float humanOffsetX = 0.0f;


GLfloat hourAngle = 0.0f;
GLfloat minuteAngle = 0.0f;
GLfloat secondAngle = 0.0f;
GLfloat clockSpeed = 5.0f; //
bool bulbOn = false;


// Global variables for animation
float move_wave = 0.0f;
bool wave_direction = true;

float move_cloud = 0.0f;

float move_boat = 0.0f;
float boat_vertical_offset = -0.1f;

float move_cargo_ship = -1.2f; // Initial position for the new cargo ship (starts just off-screen left)
bool cargo_ship_visible = false; // Flag to control cargo ship visibility (starts hidden)

// Z-coordinates for depth ordering (closer to 1.0 means closer to viewer)
const float Z_SKY = -0.9f;
const float Z_SUN = -0.8f;
const float Z_CLOUD = -0.7f;
const float Z_WATER = -0.5f;
const float Z_WAVE = -0.4f;

// Adjusted Z-coordinates to put cargo ship and small boat in front of the beach/benches
const float Z_BEACH = 0.0f;
const float Z_UMBRELLA = 0.1f;
const float Z_BENCH = 0.1f; // Z-coordinate for the bench

const float Z_CARGO_SHIP = 0.2f;
const float Z_SHIP_TEXT = 0.21f;
const float Z_SMALL_BOAT = 0.3f;

bool person1_active = false;
float person1_x, person1_y, person1_animationAngle;
int person1_state;

// --- Person 2 Variables ---
bool person2_active = false;
float person2_x, person2_y, person2_animationAngle;
int person2_state;

// --- Person 3 Variables ---
bool person3_active = false;
float person3_x, person3_y, person3_animationAngle;
int person3_state;
bool b_person1_active = false;
float b_person1_x, b_person1_y, b_person1_animationAngle;
int b_person1_state;

bool b_person2_active = false;
float b_person2_x, b_person2_y, b_person2_animationAngle;
int b_person2_state;

bool b_person3_active = false;
float b_person3_x, b_person3_y, b_person3_animationAngle;
int b_person3_state;

// New person group spawn timer
int spawnTimer = 10;

// --- Global variables for the Traffic Signal Light ---
bool isLightRed = true;    // Start with the red light on
int lightTimer = 0;        // A timer to count frames
int lightInterval = 50;    // How many frames before the light changes (e.g., 50 frames)
bool hasGroupSpawned = false;
int screen_id = 0; // 0: Intro, 1: Instructions, 2-6: Group member scenes

 void drawCircle(GLfloat x, GLfloat y, GLfloat radius, int segments)//circle function
     {
    GLfloat angle;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center
        for (int i = 0; i <= segments; ++i) {
            angle = 2.0f * PI * i / segments;
            glVertex2f(
                x + (radius * cos(angle)),
                y + (radius * sin(angle))
            );
        }
    glEnd();
}

void drawmaleHuman(float humanX, float humanY, float animationAngle) {
    // This angle is used to create the swinging motion of arms and legs
    float legAngle = 25.0f * sin(animationAngle);
    float armAngle = 20.0f * sin(animationAngle);

    glPushMatrix(); // Save the current transformation state

    // Move the entire human to its current position
    glTranslatef(humanX, humanY, 0.0f);

    // Scale the human to 80% of its original size
    glScalef(0.95f, 0.95f, 1.0f);

    // ---- Draw Torso ----
    glColor3f(0.4f, 0.2f, 0.8f); // Shirt color
    glBegin(GL_QUADS);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.03f, 0.0f);
    glVertex2f(0.04f, 0.15f);
    glVertex2f(-0.04f, 0.15f);
    glEnd();

    // ---- Draw Head, Neck, and Hair ----
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);

    // Change 1: Draw the Neck
    glColor3f(0.9f, 0.7f, 0.5f); // Skin color
    glBegin(GL_QUADS);
        glVertex2f(-0.015f, 0.0f);
        glVertex2f(0.015f, 0.0f);
        glVertex2f(0.015f, 0.05f);
        glVertex2f(-0.015f, 0.05f);
    glEnd();

    // Position the head on top of the neck
    glTranslatef(0.0f, 0.05f, 0.0f);

    // Change 2: Make the head an oval shape
    glPushMatrix();
        glScalef(1.0f, 1.1f, 1.0f); // Stretched slightly along the Y-axis
        glColor3f(0.9f, 0.7f, 0.5f); // Skin color
        drawCircle(0.0f, 0.0f, 0.05f, 30);
    glPopMatrix();

    // Change 3: Draw the Hair
    glColor3f(0.1f, 0.1f, 0.1f); // Hair color (black)
    glBegin(GL_QUADS);
        glVertex2f(-0.052f, 0.01f);
        glVertex2f(0.052f, 0.01f);
        glVertex2f(0.052f, 0.06f);
        glVertex2f(-0.052f, 0.06f);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.06f); // Top-center point of the hair
        glVertex2f(-0.052f, 0.06f);
        glVertex2f(-0.04f, 0.075f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.04f, 0.075f);
        glVertex2f(0.052f, 0.06f);
    glEnd();

    glPopMatrix(); // End of head, neck, and hair matrix



    // Right Arm (back arm)
    glPushMatrix();
      glTranslatef(0.04f, 0.13f, 0.0f);      // Move to the shoulder joint
      glRotatef(-armAngle, 0.0f, 0.0f, 1.0f); // Rotate the arm
      glTranslatef(-0.04f, -0.13f, 0.0f);     // Move back to origin
      glColor3ub(153, 102, 51);               // Darker color for the back arm
      glBegin(GL_QUADS);
        glVertex2f(0.035f, 0.14f); glVertex2f(0.05f, 0.14f); glVertex2f(0.05f, 0.02f); glVertex2f(0.035f, 0.02f);
      glEnd();
    glPopMatrix();

    // Left Arm (front arm)
    glPushMatrix();
      glTranslatef(-0.04f, 0.13f, 0.0f);
      glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
      glTranslatef(0.04f, -0.13f, 0.0f);
      glColor3f(0.9f, 0.7f, 0.5f); // Skin color
      glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.14f); glVertex2f(-0.035f, 0.14f); glVertex2f(-0.035f, 0.02f); glVertex2f(-0.05f, 0.02f);
      glEnd();
    glPopMatrix();

    // Right Leg (back leg)
    glPushMatrix();
      glRotatef(-legAngle, 0.0f, 0.0f, 1.0f); // Rotate the leg
      glColor3ub(51, 51, 102);                // Dark blue color for the back leg
      glBegin(GL_QUADS);
        glVertex2f(0.01f, 0.0f); glVertex2f(0.035f, 0.0f); glVertex2f(0.035f, -0.15f); glVertex2f(0.01f, -0.15f);
      glEnd();
    glPopMatrix();

    // Left Leg (front leg)
    glPushMatrix();
      glRotatef(legAngle, 0.0f, 0.0f, 1.0f);
      glColor3f(0.2f, 0.2f, 0.6f); // Pants color
      glBegin(GL_QUADS);
        glVertex2f(-0.035f, 0.0f); glVertex2f(-0.01f, 0.0f); glVertex2f(-0.01f, -0.15f); glVertex2f(-0.035f, -0.15f);
      glEnd();
    glPopMatrix();

    glPopMatrix(); // Restore the saved transformation state for the entire human
}

void drawFemaleHuman(float humanX, float humanY, float animationAngle) {
    float legAngle = 25.0f * sin(animationAngle);
    float armAngle = 20.0f * sin(animationAngle);

    glPushMatrix();
    glTranslatef(humanX, humanY, 0.0f);
    glScalef(0.95f, 0.95f, 1.0f); // Using the larger scale

    // ---- Torso (Top part of the dress) ----
    glColor3f(0.0f, 0.5f, 0.5f); // New dress color (e.g., teal)
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, 0.05f);
        glVertex2f(0.03f, 0.05f);
        glVertex2f(0.04f, 0.15f);
        glVertex2f(-0.04f, 0.15f);
    glEnd();

    // ---- Head, Neck, and a new Hairstyle ----
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);
    // Neck
    glColor3f(0.9f, 0.7f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.015f, 0.0f);
        glVertex2f(0.015f, 0.0f);
        glVertex2f(0.015f, 0.05f);
        glVertex2f(-0.015f, 0.05f);
    glEnd();

    glTranslatef(0.0f, 0.05f, 0.0f);
    // Head (oval shape)
    glPushMatrix();
        glScalef(1.0f, 1.1f, 1.0f);
        glColor3f(0.9f, 0.7f, 0.5f);
        drawCircle(0.0f, 0.0f, 0.05f, 30);
    glPopMatrix();

    // New, cleaner hairstyle
    glColor3f(0.15f, 0.1f, 0.1f); // Dark brown hair
    glBegin(GL_POLYGON);
        glVertex2f(0.05f, -0.05f);
        glVertex2f(0.055f, 0.04f);
        glVertex2f(0.04f, 0.075f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(-0.04f, 0.075f);
        glVertex2f(-0.055f, 0.04f);
        glVertex2f(-0.05f, -0.05f);
    glEnd();
    glPopMatrix(); // End head matrix

    // ---- Arms ----
    // Arms are drawn before the dress body to appear behind it
    // Right Arm
    glPushMatrix();
      glTranslatef(0.04f, 0.13f, 0.0f);
      glRotatef(-armAngle, 0.0f, 0.0f, 1.0f);
      glTranslatef(-0.04f, -0.13f, 0.0f);
      glColor3f(0.9f, 0.7f, 0.5f);
      glBegin(GL_QUADS);
        glVertex2f(0.035f, 0.14f); glVertex2f(0.05f, 0.14f); glVertex2f(0.05f, 0.02f); glVertex2f(0.035f, 0.02f);
      glEnd();
    glPopMatrix();
    // Left Arm
    glPushMatrix();
      glTranslatef(-0.04f, 0.13f, 0.0f);
      glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
      glTranslatef(0.04f, -0.13f, 0.0f);
      glColor3f(0.9f, 0.7f, 0.5f);
      glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.14f); glVertex2f(-0.035f, 0.14f); glVertex2f(-0.035f, 0.02f); glVertex2f(-0.05f, 0.02f);
      glEnd();
    glPopMatrix();

    // Skirt part of the dress
    glColor3f(0.0f, 0.5f, 0.5f); // Dress color
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, 0.05f);
        glVertex2f(0.03f, 0.05f);
        glVertex2f(0.07f, -0.1f);
        glVertex2f(-0.07f, -0.1f);
    glEnd();



    // Back Leg
    glPushMatrix();
        glTranslatef(0.03f, -0.1f, 0.0f); // Position at bottom of dress
        glRotatef(-legAngle * 0.5f, 0.0f, 0.0f, 1.0f); // Smaller rotation
        glColor3ub(200, 160, 130); // Darker skin for back leg
        glBegin(GL_QUADS);
            glVertex2f(-0.01f, 0.0f);
            glVertex2f(0.01f, 0.0f);
            glVertex2f(0.01f, -0.05f);
            glVertex2f(-0.01f, -0.05f);
        glEnd();
    glPopMatrix();

    // Front Leg
    glPushMatrix();
        glTranslatef(-0.03f, -0.1f, 0.0f); // Position at bottom of dress
        glRotatef(legAngle * 0.5f, 0.0f, 0.0f, 1.0f); // Smaller rotation
        glColor3f(0.9f, 0.7f, 0.5f); // Skin color
        glBegin(GL_QUADS);
            glVertex2f(-0.01f, 0.0f);
            glVertex2f(0.01f, 0.0f);
            glVertex2f(0.01f, -0.05f);
            glVertex2f(-0.01f, -0.05f);
        glEnd();
    glPopMatrix();


    glPopMatrix(); // End entire human matrix
}


void initializePeople() {
    person1_active = false;
    person2_active = false;
    person3_active = false;
    hasGroupSpawned = false;

     b_person1_active = false;
    b_person2_active = false;
    b_person3_active = false;
}
void timer5(int value) {



    if (!hasGroupSpawned && spawnTimer <= 0) {
        // ...set the flag to true to prevent this block from ever running again.
        hasGroupSpawned = true;

        // Activate all 3 people of the first group (disembarking)
        person1_active = true;
        person1_x = -0.89f;
        person1_y = -0.72f;
        person1_state = 1; // State 1: Moving down from train
        person1_animationAngle = 0.0f;

        person2_active = true;
        person2_x = -0.89f;
        person2_y = -0.72f;
        person2_state = 1;
        person2_animationAngle = 0.0f;

        person3_active = true;
        person3_x = -0.89f;
        person3_y = -0.72f;
        person3_state = 1;
        person3_animationAngle = 0.0f;
    }


    if (person1_active) {
        person1_animationAngle += 0.1f;
        if (person1_state == 1) { // State 1: Moving Down
            person1_y -= 0.003f;
            if (person1_y <= -0.84f) { person1_state = 2; }
        } else if (person1_state == 2) { // State 2: Moving Right
            person1_x += 0.004f;
            if (person1_x > 1.2f) { person1_active = false; }
        }
    }
    // -- Animate Person 2 --
    if (person2_active) {
        person2_animationAngle += 0.11f;
        if (person2_state == 1) { // State 1: Moving Down
            person2_y -= 0.003f;
            if (person2_y <= -0.82f) { person2_state = 2; }
        } else if (person2_state == 2) { // State 2: Moving Right
            person2_x += 0.0042f;
            if (person2_x > 1.2f) { person2_active = false; }
        }
    }
    // -- Animate Person 3 --
    if (person3_active) {
        person3_animationAngle += 0.09f;
        if (person3_state == 1) { // State 1: Moving Down
            person3_y -= 0.003f;
            if (person3_y <= -0.86f) { person3_state = 2; }
        } else if (person3_state == 2) { // State 2: Moving Right
            person3_x += 0.0038f;
            if (person3_x > 1.2f) {
                person3_active = false;


                if (!b_person1_active) { // Check to prevent re-triggering
                    // Activate all 3 people of Group 2 (Boarding)
                    b_person1_active = true;
                    b_person1_x = 0.4f;
                    b_person1_y = -0.84f;
                    b_person1_state = 1;
                    b_person1_animationAngle = 0.0f;

                    b_person2_active = true;
                    b_person2_x = 0.45f;
                    b_person2_y = -0.82f;
                    b_person2_state = 1;
                    b_person2_animationAngle = 0.0f;

                    b_person3_active = true;
                    b_person3_x = 0.5f;
                    b_person3_y = -0.86f;
                    b_person3_state = 1;
                    b_person3_animationAngle = 0.0f;
                }
            }
        }
    }

    // -- Animate Boarding Person 1 --
    if (b_person1_active) {
        b_person1_animationAngle += 0.1f;
        if (b_person1_state == 1) { // State 1: Walking Left
            b_person1_x -= 0.004f;
            if (b_person1_x <= -0.89f) { b_person1_state = 2; }
        } else if (b_person1_state == 2) { // State 2: Climbing Up
            b_person1_y += 0.003f;
            if (b_person1_y >= -0.72f) { b_person1_active = false; }
        }
    }
    // -- Animate Boarding Person 2 --
    if (b_person2_active) {
        b_person2_animationAngle += 0.1f;
        if (b_person2_state == 1) { // State 1: Walking Left
            b_person2_x -= 0.0038f;
            if (b_person2_x <= -0.89f) { b_person2_state = 2; }
        } else if (b_person2_state == 2) { // State 2: Climbing Up
            b_person2_y += 0.003f;
            if (b_person2_y >= -0.72f) { b_person2_active = false; }
        }
    }
    // -- Animate Boarding Person 3 --
    if (b_person3_active) {
        b_person3_animationAngle += 0.1f;
        if (b_person3_state == 1) { // State 1: Walking Left
            b_person3_x -= 0.0041f;
            if (b_person3_x <= -0.89f) { b_person3_state = 2; }
        } else if (b_person3_state == 2) { // State 2: Climbing Up
            b_person3_y += 0.003f;
            if (b_person3_y >= -0.72f) {
    b_person3_active = false; // Person disappears into train

    // Only play sound if currently on Station View (window 4)
    if (screen_id == 4) {
        PlaySound(TEXT("horn1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}
        }
    }


    lightTimer++;
    if (lightTimer >= lightInterval) {
        isLightRed = !isLightRed;
        lightTimer = 0;
    }


    if (!hasGroupSpawned) {
        spawnTimer--;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer5, 0);
}


void renderBitmapString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}


void railine(){
      glColor4f(0.0f, 0.0f, 0.0f,1.0f);
      glBegin(GL_LINE_LOOP);
      glVertex2f(-0.0772f,-0.3734f);
      glVertex2f(-0.0627f,-0.3997f);

      glVertex2f(-0.0726f,-0.3713f);
      glVertex2f(-0.058f,-0.3975f);

      glVertex2f(-0.0636f,-0.3684f);
      glVertex2f(-0.05f,-0.3935f);

      glVertex2f(-0.0584f,-0.3665f);
      glVertex2f(-0.0456f,-0.391f);
       glEnd();
      }


void chair(){



 glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);//chair
      glVertex2f(0.155f,-0.578f);
      glVertex2f(0.15f,-0.45f);
      glVertex2f(0.26f,-0.448f);
      glVertex2f(0.389f,-0.577f);
 glEnd();

  glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);//chair
      glVertex2f(0.155f,-0.578f);
    glVertex2f(0.16f,-0.626f);
    glVertex2f(0.398f,-0.624f);
      glVertex2f(0.389f,-0.577f);
 glEnd();

 glColor3f(0.36f, 0.20f, 0.09f);
    glBegin(GL_QUADS);//chair
    glVertex2f(0.28322f,-0.47122f);
    glVertex2f(0.26774f,-0.45574f);
    glVertex2f(0.29788f,-0.30288f);
    glVertex2f(0.31278f,-0.30528f);

 glEnd();

 glColor3f(0.36f, 0.20f, 0.09f);
    glBegin(GL_QUADS);//chair
 glVertex2f(0.37739f,-0.56539f);
 glVertex2f(0.36707f,-0.55507f);
 glVertex2f(0.3992f,-0.3192f);
 glVertex2f(0.41559f,-0.32184f);
 glEnd();

 glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);//chair
     glVertex2f(0.26f,-0.42f);
     glVertex2f(0.269f,-0.368f);
     glVertex2f(0.419f,-0.4634f);
     glVertex2f(0.404f,-0.544f);
 glEnd();
 glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);//chair
     glVertex2f(0.271f,-0.3395f);
     glVertex2f(0.28f,-0.3f);
     glVertex2f(0.429f,-0.324f);
     glVertex2f(0.42f,-0.42f);
      glEnd();

      glColor3f(0.36f, 0.20f, 0.09f);
    glBegin(GL_QUADS);//chair
     glVertex2f(0.189512f,-0.625752f);
     glVertex2f(0.21831f,-0.62551f);
     glVertex2f(0.216f,-0.778f);
     glVertex2f(0.1868f,-0.7772f);
      glEnd();

      glColor3f(0.36f, 0.20f, 0.09f);
    glBegin(GL_QUADS);//chair
     glVertex2f(0.341832f,-0.624472f);
     glVertex2f(0.377532f,-0.624172f);
     glVertex2f(0.38f,-0.78f);
     glVertex2f(0.34f,-0.78f);
      glEnd();
 }

  void chairshadow(){

      glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//chair
     glVertex2f(0.167f,-0.493f);
     glVertex2f(0.22f,-0.5f);
     glVertex2f(0.32f,-0.8f);
     glVertex2f(0.249f,-0.798f);
     glEnd();
  }
  void platformroof()
  {
        glColor4f(0.35f, 0.37f, 0.39f,0.5f);
    glBegin(GL_POLYGON);//platform roof
    glVertex2f(-1.0f,1.0f);
    glVertex2f(-0.216f,0.64f);
    glVertex2f(0.56f,0.59f);
    glVertex2f(1.0f,0.7f);
    glVertex2f(1.0f,1.0f);
      glEnd();

      glColor4f(0.90f, 0.90f, 0.88f,1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.552f,0.58f);
    glVertex2f(1.0f,0.9f);
    glVertex2f(1.0f,1.0f);
    glVertex2f(0.825f,1.0f);
          glEnd();

        glColor4f(0.35f, 0.37f, 0.39f,0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f,1.0f);
    glVertex2f(-0.216f,0.64f);
    glVertex2f(0.552f,0.58f);
    glVertex2f(0.825f,1.0f);
          glEnd();

         glColor4f(0.41f, 0.41f, 0.41f,1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.608f,0.934f);
    glVertex2f(-0.551f,0.89f);
    glVertex2f(0.758934f,0.89836f);
    glVertex2f(0.7977f,0.958f);
          glEnd();

           glColor4f(0.41f, 0.41f, 0.41f,1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5035f,0.8538f);
    glVertex2f(-0.464f,0.825f);
    glVertex2f(0.694506f,0.79924f);
    glVertex2f(0.72126f,0.8404f);
          glEnd();

           glColor4f(0.41f, 0.41f, 0.41f,1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.396f,0.774f);
    glVertex2f(-0.346f,0.736f);
    glVertex2f(0.62571f,0.6934f);
    glVertex2f(0.646458f,0.72532f);
          glEnd();




      glColor4f(0.35f, 0.37f, 0.39f,0.8f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.71f,1.0f);
    glVertex2f(-0.216f,0.64f);
    glVertex2f(-0.9f,1.0f);

      glVertex2f(0.371f,1.0f);
    glVertex2f(0.45f,1.0f);
    glVertex2f(0.512f,0.581f);


      glVertex2f(0.552f,0.58f);
    glVertex2f(1.0f,0.7f);
    glVertex2f(1.0f,0.8f);
      glEnd();

      glColor4f(0.35f, 0.37f, 0.39f,1.0);
       glVertex2f(0.552f,0.58f);
    glVertex2f(1.0f,0.7f);
    glVertex2f(1.0f,0.9f);
      glEnd();



  }


  void drawText(const char *text, float x, float y) {
     glRasterPos2f(x, y);  // Set the position (x, y)
     while (*text) {
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text);  // Draw each character
         text++;}}
void display5(){ glClearColor(0.97f, 0.97f, 0.95f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
    glColor3f(0.50f, 0.50f, 0.50f);
    glBegin(GL_QUADS);//main platform
        glVertex2f(-0.957f,-0.99f);
        glVertex2f(-0.08f,-0.4344f);
        glVertex2f(1.003f,-0.436f);
        glVertex2f(1.0f,-1.0f);

    glEnd();
       glColor3f(0.0f, 0.0f, 0.3f);
     glBegin(GL_QUADS);//blue line between line and platform
     glVertex2f(-0.957f,-0.99f);
         glVertex2f(-0.08f,-0.4344f);
         glVertex2f(-0.066f,-0.435f);
       glVertex2f(-0.908f,-1.0f);
     glEnd();



    glColor3f(0.3f, 0.3f, 0.3f); // Dark grey color for the post
    glBegin(GL_QUADS);
        glVertex2f(-0.081f, -0.4344f);
        glVertex2f(-0.066f, -0.435f);
        glVertex2f(-0.0654f,-0.2737f);
        glVertex2f(-0.079f, -0.2737f);
    glEnd();


    glColor3f(0.2f, 0.2f, 0.2f); // Slightly darker housing
    glBegin(GL_QUADS);
        glVertex2f(-0.0426f, -0.284f);
        glVertex2f(-0.065439f, -0.2841845f);
        glVertex2f(-0.0655944f, -0.325961f);
        glVertex2f(-0.042f,-0.326f);
    glEnd();




    float lightCenterX = -0.054f;

    // --- Draw the Red Light (Top) ---
    if (isLightRed) {
        glColor3f(1.0f, 0.0f, 0.0f); // Bright Red
    } else {
        glColor3f(0.4f, 0.0f, 0.0f); // Dim Red
    }

    drawCircle(lightCenterX, -0.298f, 0.008f, 20);

    // --- Draw the Green Light (Bottom) ---
    if (!isLightRed) {
        glColor3f(0.0f, 1.0f, 0.0f); // Bright Green
    } else {
        glColor3f(0.0f, 0.4f, 0.0f); // Dim Green
    }

    drawCircle(lightCenterX, -0.315f, 0.008f, 20);

     glColor4f(0.0f, 0.0f, 0.0f,1.0f);
    glBegin(GL_POLYGON);//pillar
    glVertex2f(-1.0f,-0.916f);
    glVertex2f(-1.0f,-1.0f);
    glVertex2f(-0.972f,-1.0f);
    glVertex2f(-0.094999f,-0.445041f);
    glVertex2f(-0.1077f,-0.4456f);
    glVertex2f(-0.1075651f,-0.430152f);
      glEnd();

      glColor3f(0.65f, 0.16f, 0.16f);
    glBegin(GL_QUADS);//orange area in platform
       glVertex2f(-0.908f,-0.998f);
       glVertex2f(-0.066f,-0.435f);
       glVertex2f(0.030456f,-0.435072f);
       glVertex2f(-0.367f,-1.004f);
     glEnd();

     glColor3f(0.82f, 0.71f, 0.55f);
    glBegin(GL_QUADS);//sitting area in platform
      glVertex2f(-0.367,-1.004);
          glVertex2f(0.030456,-0.435072);
         glVertex2f(1.003,-0.436);
         glVertex2f(1.0,-1);
 glEnd();

 platformroof();

 glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//shadow up line
     glVertex2f(1.0f,-0.02f);
     glVertex2f(1.0f,-0.05f);
     glVertex2f(-0.420247f,-0.023106f);
     glVertex2f(0.463413f,-0.023106f);
      glEnd();

      glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//shadow up line
     glVertex2f(1.0f,-0.116f);
     glVertex2f(1.0f,-0.133f);
     glVertex2f(-0.320424f,-0.1015566f);
     glVertex2f(-0.33931f,-0.0911952f);
      glEnd();

      glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//upline from left to right
     glVertex2f(-1.0f,0.54f);
     glVertex2f(-1.0f,0.48f);
     glVertex2f(1.0f,0.464f);
     glVertex2f(1.0f,0.513f);
      glEnd();


      glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//upline from left to right low one
     glVertex2f(-1.0f,0.375f);
     glVertex2f(-1.0f,0.328f);
     glVertex2f(1.0f,0.32f);
     glVertex2f(1.0f,0.365f);
 glEnd();

 glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//
     glVertex2f(0.043733f,-0.098289f);
     glVertex2f(0.06918f,-0.098761f);
     glVertex2f(0.068184f,-0.435108f);
     glVertex2f(0.04408f,-0.435085f);
      glEnd();

       glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//chairpillarshadow
     glVertex2f(0.206f,-0.734f);
     glVertex2f(0.19f,-0.756f);
     glVertex2f(0.57623f,-1.00124f);
     glVertex2f(0.688324f,-1.000912);
     glEnd();
     glColor4f(0.36f, 0.20f, 0.09f,0.1f);
 glBegin(GL_QUADS);//chairpillarshadow
     glVertex2f(0.365f,-0.76f);
     glVertex2f(0.37f,-0.745f);
     glVertex2f(0.82220f,-1.00052f);
     glVertex2f(0.90978f,-1.000264f);
      glEnd();

       for (int i = 0; i < 3; ++i) {
        glPushMatrix();
        glTranslatef(0.0f + i * 0.08f, 0.0f, 0.0f); // Move each chair in X
        chairshadow();
        glPopMatrix();
 glEnd();
       }


 chair();

 glColor4f(0.67f,0.67f,0.67f,1.0f);
    glBegin(GL_POLYGON);//pillar back
    glVertex2f(0.512,0.5847f);
    glVertex2f(0.552f,0.58f);
    glVertex2f(0.55f,-0.55f);
    glVertex2f(0.51f,-0.545f);

      glEnd();

      glColor4f(0.21f, 0.57f, 0.58f,0.6f);
    glBegin(GL_QUADS);//back pillar lowerside color
    glVertex2f(0.511032f,0.037925f);
    glVertex2f(0.551038f,0.03647f);
    glVertex2f(0.55f,-0.55f);
    glVertex2f(0.51f,-0.545f);
      glEnd();

      glColor4f(0.0f, 0.0f, 0.2f, 1.0f);
    glBegin(GL_QUADS);//back pillar out square
    glVertex2f(0.489f,-0.032f);
    glVertex2f(0.591f,-0.034f);
    glVertex2f(0.59f,-0.33455f);
    glVertex2f(0.4885f,-0.346f);
      glEnd();

      glColor4f(0.8f, 0.8f, 0.5f, 1.0f);
    glBegin(GL_QUADS);//back pillar in square
    glVertex2f(0.5f,-0.04);
    glVertex2f(0.591f,-0.041165f);
    glVertex2f(0.59f,-0.330859f);
    glVertex2f(0.502f,-0.3327f);
      glEnd();


      glColor4f(0.36f, 0.20f, 0.09f,0.1f);
       glBegin(GL_POLYGON);//pillar back shadow
        glVertex2f(0.55f,-0.55f);
        glVertex2f(1.002049f,-0.614788f);
         glVertex2f(1.00165f,-0.6898f);

      glEnd();

      glColor4f(0.67f,0.57f,0.67f,1.0f);
    glBegin(GL_QUADS);//clock pillar
    glVertex2f(0.6527f,0.461f);
    glVertex2f(0.713f,0.460634f);
    glVertex2f(0.713f,-0.702f);
    glVertex2f(0.6527f,-0.721f);
      glEnd();

      glColor4f(0.36f, 0.20f, 0.09f,0.1f);
    glBegin(GL_QUADS);//clock pillar shadow
    glVertex2f(0.655f,-0.721f);
    glVertex2f(1.0f,-0.82234f);
    glVertex2f(1.0f,-0.769888f);
    glVertex2f(0.713f,-0.702f);
      glEnd();

      glColor4f(0.67f,0.57f,0.67f,1.0f);
    glBegin(GL_QUADS);//clock pillar up
    glVertex2f(0.713f,0.527f);
    glVertex2f(0.713f,0.460634f);
    glVertex2f(-0.224f,0.478f);
    glVertex2f(-0.224f,0.535f);
      glEnd();

      glColor4f(0.67f,0.57f,0.67f,1.0f);
    glBegin(GL_POLYGON);//clock pillar diagonal
    glVertex2f(0.522072f,0.463533f);
    glVertex2f(0.6527f,0.341618f);
    glVertex2f(0.6527f,0.276608f);
    glVertex2f(0.459826f,0.46474f);
      glEnd();

      glColor4f(0.6f, 0.2f, 0.8f, 1.0f);
    glBegin(GL_QUADS);//clock connecting pillar1
    glVertex2f(0.337965f,0.467103f);
    glVertex2f(0.366896f,0.466542f);
    glVertex2f(0.3642f,0.36845f);
    glVertex2f(0.338954f,0.368665f);
      glEnd();

       glColor4f(0.6f, 0.2f, 0.8f, 1.0f);
    glBegin(GL_QUADS);//clock connecting pillar2
   glVertex2f(-0.1196182f,0.476065f);
   glVertex2f(-0.0848555f,0.475421f);
   glVertex2f(-0.086f,0.372f);
       glVertex2f(-0.119f,0.3725f);
      glEnd();

      glColor4f(0.302f, 0.098f, 0.902f, 1.0f);
    glBegin(GL_QUADS);//clock area
    glVertex2f(-0.235f,0.373f);
    glVertex2f(-0.235f,0.075f);
    glVertex2f(0.427f,0.075f);
    glVertex2f(0.427f,0.368f);
      glEnd();

      glColor4f(0.705f, 0.745f, 0.862f, 1.0f);
    glBegin(GL_QUADS);//clock area square
    glVertex2f(0.0f,0.336f);
    glVertex2f(0.0f,0.089f);
    glVertex2f(0.382f,0.087f);
    glVertex2f(0.382f,0.335f);
      glEnd();

      glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);//clock square insde square
    glVertex2f(0.015f,0.3245f);
    glVertex2f(0.365f,0.322f);
    glVertex2f(0.365f,0.271f);
    glVertex2f(0.015f,0.272f);
      glEnd();
glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
drawText("Arrival | Next station |   Departure", 0.015f, 0.28f);


      glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);//clock square insde square
    glVertex2f(0.015f,0.247f);
    glVertex2f(0.015f,0.1984f);
    glVertex2f(0.365f,0.1985f);
    glVertex2f(0.365f,0.2445f);
      glEnd();

      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
drawText("8:40    | COX'S BAZAR |   8:49", 0.015f, 0.2f);

       glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);//clock square insde square
    glVertex2f(0.015f,0.173f);
    glVertex2f(0.015f,0.119f);
    glVertex2f(0.365f,0.119f);
    glVertex2f(0.365f,0.171f);
      glEnd();
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
drawText("8:56    | RAJSHAHI    |      9:03", 0.015f, 0.13f);


      glColor4f(0.0f, 0.294f, 0.229f, 1.0f);
     drawCircle(-0.128f, 0.243f, 0.09f, 100);
     glColor3f(1.0f, 1.0f, 1.0f); // clock
     drawCircle(-0.126f, 0.243f, 0.08f, 100);

     glColor3f(0.0f,0.0f,0.0f);
     glBegin(GL_LINE_LOOP);//
     glVertex2f(-0.153f,0.264f);
     glVertex2f(-0.124f,0.243f);
       glEnd();
     glBegin(GL_LINE_LOOP);
     glVertex2f(-0.124f,0.243f);
     glVertex2f(-0.099f,0.291f);
       glEnd();





glColor4f(0.78f,0.78f,0.78f,1.0f);
    glBegin(GL_POLYGON);//pillar front
    glVertex2f(0.813f,0.834f);
    glVertex2f(0.864,0.868f);
    glVertex2f(0.894f,0.825f);
    glVertex2f(0.885f,-0.853f);
    glVertex2f(0.8f,-0.85f);
      glEnd();



       glColor4f(0.21f, 0.57f, 0.58f,0.6f);
    glBegin(GL_POLYGON);//front pillar lowerside color
    glVertex2f(0.807462f,0.116616f);
    glVertex2f(0.890202f,0.116884f);
    glVertex2f(0.885f,-0.853f);
    glVertex2f(0.8f,-0.85f);
    glEnd();

     glColor4f(0.0f, 0.0f, 0.2f, 1.0f);
    glBegin(GL_QUADS);//front pillar out square
    glVertex2f(0.7585f,0.0826f);
    glVertex2f(0.92685f,0.08f);
    glVertex2f(0.924f,-0.387f);
    glVertex2f(0.753f,-0.3845f);
      glEnd();

      glColor4f(0.8f, 0.8f, 0.5f, 1.0f);
    glBegin(GL_QUADS);//front pillar inside square
    glVertex2f(0.773f,-0.3655f);
    glVertex2f(0.924135f,-0.365985f);
    glVertex2f(0.92685f,0.05665f);
    glVertex2f(0.777f,0.057f);
    glEnd();


      glColor4f(0.36f, 0.20f, 0.09f,0.1f);
       glBegin(GL_QUADS);//pillar front shadow
        glVertex2f(0.8f,-0.85f);
        glVertex2f(0.885f,-0.853f);
         glVertex2f(1.0f,-0.863512f);
       glVertex2f(1.0f,-0.914272f);
       glEnd();

      glColor4f(0.0f, 0.0f, 0.0f,1.0f);
       glBegin(GL_QUADS);//1st rail line
     glVertex2f(-0.028f,-0.382f);
     glVertex2f(-0.021f,-0.385f);
     glVertex2f(-1.044f,-0.916f);
     glVertex2f(-1.004202f,-0.893504f);
       glEnd();

      glColor4f(0.0f, 0.0f, 0.0f,1.0f);
       glBegin(GL_QUADS);//2nd rail line
     glVertex2f(-1.0f,-0.709984f);
     glVertex2f(-1.0f,-0.73248f);
     glVertex2f(-0.0336f,-0.3564f);
     glVertex2f(-0.0336f,-0.3523f);
       glEnd();


         railine();

       glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//train outsquare
    glVertex2f(-1.0f,-0.916f);
    glVertex2f(-1.0f,0.268f);
    glVertex2f(-0.0947f,-0.2254f);
    glVertex2f(-0.0947f,-0.4244f);
      glEnd();

      glColor4f(0.275f, 0.510f, 0.706f, 1.0f);
    glBegin(GL_QUADS);//train innersquare
    glVertex2f(-0.0947f,-0.24729f);
    glVertex2f(-0.0947f,-0.4045f);
    glVertex2f(-1.0f,-0.790496f);
    glVertex2f(-1.0f,0.211168f);
      glEnd();

      glColor4f(1.0f, 0.980f, 0.804f, 1.0f);
    glBegin(GL_QUADS);//train yellow square
    glVertex2f(-1.0f,-0.226912f);
    glVertex2f(-1.0f,-0.15232f);
    glVertex2f(-0.09556f,-0.299826f);
    glVertex2f(-0.095765f,-0.317537f);
      glEnd();

      glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//1st door
    glVertex2f(-0.943f,0.036f);
    glVertex2f(-0.84f,0.002f);
    glVertex2f(-0.836f,-0.72f);
    glVertex2f(0-0.941f,-0.762f);
      glEnd();

      glColor4f(0.95f, 0.95f, 0.92f, 0.7f);
    glBegin(GL_POLYGON);//1st door inside polygon
    glVertex2f(-0.942932f,0.008868f);
    glVertex2f(-0.868f,-0.0215f);
    glVertex2f(-0.855f,-0.0495f);
    glVertex2f(-0.853f,-0.7025);
    glVertex2f(-0.94106f,-0.73806f);
      glEnd();

      glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//1st window
    glVertex2f(-0.77f,-0.064f);
    glVertex2f(-0.636f,-0.117f);
    glVertex2f(-0.636f,-0.35f);
    glVertex2f(-0.77f,-0.355f);
      glEnd();
      glColor4f(0.95f, 0.95f, 0.92f, 0.5f);
    glBegin(GL_QUADS);//1st window
    glVertex2f(-0.765f,-0.064f);
    glVertex2f(-0.63f,-0.117f);
    glVertex2f(-0.63f,-0.35f);
    glVertex2f(-0.765f,-0.355f);
      glEnd();

      glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//1st window
    glVertex2f(-0.77f,-0.13675f);
    glVertex2f(-0.636f,-0.18224f);
       glEnd();
 glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//1st window
    glVertex2f(-0.70032f,-0.09156f);
    glVertex2f(-0.7f,-0.16f);
      glEnd();

      glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//2ndwindow
    glVertex2f(-0.58f,-0.14f);
    glVertex2f(-0.472f,-0.179f);
    glVertex2f(-0.471f,-0.355f);
    glVertex2f(-0.58f,-0.36f);
      glEnd();

      glColor4f(0.95f, 0.95f, 0.92f, 0.5f);
    glBegin(GL_QUADS);//2ndwindow
    glVertex2f(-0.57f,-0.14f);
    glVertex2f(-0.467f,-0.179f);
    glVertex2f(-0.467f,-0.355f);
    glVertex2f(-0.57f,-0.36f);
      glEnd();


       glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//1st window
    glVertex2f(-0.52438f,-0.160085f);
    glVertex2f(-0.52438f,-0.2148973f);
       glEnd();
 glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//1st window
    glVertex2f(-0.58f,-0.20094f);
    glVertex2f(-0.471724f,-0.227567f);
      glEnd();


      glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//2nd door
    glVertex2f(-0.43f,-0.532f);
    glVertex2f(-0.388f,-0.518f);
    glVertex2f(-0.39f,-0.208f);
    glVertex2f(-0.433f,-0.192f);
      glEnd();

      glColor4f(0.95f, 0.95f, 0.92f, 0.7f);
    glBegin(GL_POLYGON);//2nd door
    glVertex2f(-0.430096f,-0.52112f);
    glVertex2f(-0.3957f,-0.5114f);
    glVertex2f(-0.3965f,-0.232f);
    glVertex2f(-0.41f,-0.22f);
    glVertex2f(-0.432832f,-0.21104f);
      glEnd();


      glColor4f(0.05f, 0.1f, 0.25f, 1.0f);
    glBegin(GL_QUADS);//train divider
    glVertex2f(-0.384528f,-0.066945f);
    glVertex2f(-0.359915f,-0.112683f);
    glVertex2f(-0.330977f,-0.127384f);
    glVertex2f(-0.355138f,-0.0830128f);
    glEnd();
     glColor4f(0.05f, 0.1f, 0.25f, 1.0f);
    glBegin(GL_QUADS);//train divider
    glVertex2f(-0.355281f,-0.514479f);
    glVertex2f(-0.36922f,-0.57188f);
    glVertex2f(-0.343813f,-0.558115f);
      glVertex2f(-0.329884f,-0.503674f);

      glEnd();
 glColor4f(0.05f, 0.1f, 0.25f, 1.0f);
       glBegin(GL_QUADS);//train divider
     glVertex2f(-0.359915f,-0.112683f);
     glVertex2f(-0.330977f,-0.127384f);
     glVertex2f(-0.329884f,-0.503674f);
     glVertex2f(-0.355281f,-0.514479f);

       glEnd();

       glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//3rd door
    glVertex2f(-0.3085f,-0.495f);
    glVertex2f(-0.292f,-0.488f);
    glVertex2f(-0.292f,-0.239f);
    glVertex2f(-0.31f,-0.234f);
      glEnd();

      glColor4f(0.95f, 0.95f, 0.92f, 0.7f);
    glBegin(GL_POLYGON);//3rd door inside polygon
    glVertex2f(-0.3085f,-0.495f);
    glVertex2f(-0.2955063f,-0.489048f);
    glVertex2f(-0.2956f,-0.2486f);
    glVertex2f(-0.3003f,-0.2455f);
    glVertex2f(-0.309943f,-0.243918f);
      glEnd();


 glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//3rd window
    glVertex2f(-0.282f,-0.36f);
    glVertex2f(-0.2536f,-0.3618f);
    glVertex2f(-0.253f,-0.2657f);
    glVertex2f(-0.282f,-0.26f);
      glEnd();

      glColor4f(0.95f, 0.95f, 0.92f, 0.5f);
    glBegin(GL_QUADS);//3rd window
    glVertex2f(-0.28f,-0.36f);
    glVertex2f(-0.2536f,-0.3618f);
    glVertex2f(-0.253f,-0.2657f);
    glVertex2f(-0.28f,-0.26f);
      glEnd();

      glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//3rd window
    glVertex2f(-0.28f,-0.2864f);
    glVertex2f(-0.2531554f,-0.2905899f);
      glEnd();
     glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//3rd window
    glVertex2f(-0.26515f,-0.263135f);
    glVertex2f(-0.2652355f,-0.2887044f);
      glEnd();


 glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//4th window
    glVertex2f(-0.24f,-0.272f);
    glVertex2f(-0.215f,-0.2765f);
    glVertex2f(-0.2155f,-0.3585f);
    glVertex2f(-0.24f,-0.3575f);
      glEnd();

      glColor4f(0.95f, 0.95f, 0.92f, 0.5f);
    glBegin(GL_QUADS);//4th window
    glVertex2f(-0.238f,-0.272f);
    glVertex2f(-0.215f,-0.2765f);
    glVertex2f(-0.2155f,-0.3585f);
    glVertex2f(-0.238f,-0.3575f);
      glEnd();


      glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//4th window
    glVertex2f(-0.22625f,-0.274475f);
    glVertex2f(-0.2260734f,-0.2961441f);
      glEnd();
     glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//4th window
    glVertex2f(-0.24f,-0.2938025f);
    glVertex2f(-0.215131f,-0.297984f);
      glEnd();

 glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//4th door
    glVertex2f(-0.2040749f,-0.2654f);
    glVertex2f(-0.1989047f,-0.267f);
    glVertex2f(-0.1989047f,-0.448144f);
    glVertex2f(-0.2040749f,-0.450035f);
      glEnd();

      glColor4f(0.95f, 0.95f, 0.92f, 0.7f);
    glBegin(GL_QUADS);//4th door
    glVertex2f(-0.2042f,-0.2654f);
    glVertex2f(-0.1993f,-0.267f);
    glVertex2f(-0.1993582f,-0.448144f);
    glVertex2f(-0.2038038f,-0.450035f);
      glEnd();


       glColor4f(0.05f, 0.1f, 0.25f, 1.0f);
    glBegin(GL_QUADS);//2nd train divider
    glVertex2f(-0.2068332f,-0.1640944f);
    glVertex2f(-0.1896515f,-0.173488f);
    glVertex2f(-0.1808621f,-0.2036461f);
    glVertex2f(-0.1935224f,-0.1972143f );
    glEnd();

     glColor4f(0.05f, 0.1f, 0.25f, 1.0f);
    glBegin(GL_QUADS);//2nd train divider
    glVertex2f(-0.1824869f,-0.4409967f);
    glVertex2f(-0.1938252f,-0.44579f);
    glVertex2f(-0.1935224f,-0.1972143f );
    glVertex2f(-0.1808621f,-0.2036461f);
    glEnd();


     glColor4f(0.05f, 0.1f, 0.25f, 1.0f);
    glBegin(GL_QUADS);//2nd train divider
    glVertex2f(-0.1824869f,-0.4409967f);
    glVertex2f(-0.1938252f,-0.44579f);
    glVertex2f(-0.1995362f,-0.479951f);
    glVertex2f(-0.1868326f,-0.473068f);

    glEnd();


     glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//5th door
    glVertex2f(-0.1672f,-0.4343f);
    glVertex2f(-0.1697881f,-0.435564f);
    glVertex2f(-0.1697f,-0.2826f);
    glVertex2f(-0.1668f,-0.2826f);
      glEnd();


      glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//5th window
    glVertex2f(-0.16f,-0.288f);
    glVertex2f(-0.1521f,-0.2913f);
    glVertex2f(-0.1522f,-0.355f);
    glVertex2f(-0.1595f,-0.3526f);
      glEnd();


      glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//5th window
    glVertex2f(-0.16f,-0.288f);
    glVertex2f(-0.1521f,-0.2913f);
    glVertex2f(-0.1521268f,-0.3083716f);
    glVertex2f(-0.1598585f,-0.3062818f);
      glEnd();


      glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//5th window
   glVertex2f(-0.1598585f,-0.3062818f);
   glVertex2f(-0.1521268f,-0.3083716f);
      glEnd();
     glColor4f(0.0f,0.0f,0.0f,1.0f);
    glBegin(GL_LINE_LOOP);//5th window
    glVertex2f(-0.1556834f,-0.3074103f);
    glVertex2f(-0.155734f,-0.289782f);
      glEnd();



      glColor4f(0.0f, 0.294f, 0.529f, 1.0f);
    glBegin(GL_QUADS);//6th window
    glVertex2f(-0.14f,-0.35f);
    glVertex2f(-0.131f,-0.3546f);
    glVertex2f(-0.131f,-0.3f);
    glVertex2f(-0.1405f,-0.295f);
      glEnd();


      glColor4f(0.95f, 0.95f, 0.92f, 0.5f);
    glBegin(GL_QUADS);//6th door
    glVertex2f(-0.1149f,-0.292f);
    glVertex2f(-0.1153647f,-0.412411f);
    glVertex2f(-0.11219f,-0.41106f);
    glVertex2f(-0.1116f,-0.293f);
      glEnd();

      glColor4f(0.36f, 0.20f, 0.09f,0.2f);
    glBegin(GL_TRIANGLES);//upper line above train
    glVertex2f(-1.0f,0.633f);
    glVertex2f(-1.0f,0.6f);
    glVertex2f(-0.0947f,-0.2254f);
    glEnd();


// --- Draw the Animated People ---
    if (person1_active) {
        // Call the function for drawing a male
        drawmaleHuman(person1_x, person1_y, person1_animationAngle);
    }
    if (person2_active) {
        // Call the new function for drawing a female
        drawFemaleHuman(person2_x, person2_y, person2_animationAngle);
    }
    if (person3_active) {
        // Call the function for drawing a male
        drawmaleHuman(person3_x, person3_y, person3_animationAngle);
    }

    if (b_person1_active) {
        drawmaleHuman(b_person1_x, b_person1_y, b_person1_animationAngle);
    }
    if (b_person2_active) {
        drawFemaleHuman(b_person2_x, b_person2_y, b_person2_animationAngle);
    }
    if (b_person3_active) {
        drawFemaleHuman(b_person3_x, b_person3_y, b_person3_animationAngle);
    }

    glutSwapBuffers();

}



void renderBitmapString(float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawText(GLfloat x, GLfloat y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *text);
        text++;
    }
}

void showInstructionScreen() {
    glColor3f(0.0f, 0.0f, 0.0f); // Black text

    // Title block (centered and larger)
    drawText(-0.25f, 0.8f, "TRAIN JOURNEY - FROM HOME TO HORIZON");
    drawText(-0.25f, 0.72f, "--------------------------------");
    drawText(-0.25f, 0.66f, "WINDOW: 2 CITY VIEW");
    drawText(-0.25f, 0.60f, "NAME: AHSANUL HAQUE JOAR");
    drawText(-0.25f, 0.54f, "ID: 22-47183-1 | SL:7");
    drawText(-0.25f, 0.48f, "--------------------------------");

    // Section header
    drawText(-0.25f, 0.40f, "CONTROLS INSTRUCTIONS");

    // Instruction blocks with better alignment
    // Train controls
    drawText(-0.25f, 0.32f, "1. TRAIN SPEED CONTROL:");
    drawText(-0.23f, 0.27f, "W Key      Increase");
    drawText(-0.23f, 0.22f, "Q Key      Decrease");

    // Bus controls
    drawText(-0.25f, 0.14f, "2. BUS SPEED CONTROL:");
    drawText(-0.23f, 0.09f, "'<' Left Arrow      Decrease");
    drawText(-0.23f, 0.04f, "'>'Right Arrow     Increase");

    // Background toggle
    drawText(-0.25f, -0.04f, "3. BACKGROUND TOGGLE:");
    drawText(-0.23f, -0.09f, "Left Mouse Click    Day/Afternoon");

    // Menu toggle
    drawText(-0.25f, -0.17f, "4. INSTRUCTION MENU:");
    drawText(-0.23f, -0.22f, "Enter Key       Show/Hide");

    // Sound control
    drawText(-0.25f, -0.30f, "5. SOUND CONTROL:");
    drawText(-0.23f, -0.35f, "S Key           Sound On/Off");

    // Footer
    drawText(-0.25f, -0.45f, "--------------------------------");
    drawText(-0.25f, -0.55f, "PRESS ENTER TO BEGIN");
}

void showInstructionScreen3() {
    glColor3f(0.0f, 0.0f, 0.0f); // Black text

    // Title block
    drawText(-0.2f, 0.65f, "TRAIN JOURNEY - FROM HOME TO HORIZON");
    drawText(-0.2f, 0.58f, "WINDOW: 3 STATION VIEW");
    drawText(-0.2f, 0.52f, "NAME: MD. SAKIB SARWAR");
    drawText(-0.2f, 0.46f, "ID: 22-46625-1 | SL:4");

    // Section header
    drawText(-0.2f, 0.36f, "INSTRUCTION");

    // Instruction lines
    drawText(-0.2f, 0.26f, "1. TRAIN SPEED");
    drawText(-0.18f, 0.21f, "KEY UP       > INCREASE");
    drawText(-0.18f, 0.16f, "KEY DOWN     > DECREASE");

    drawText(-0.2f, 0.06f, "2. CLOCK SPEED");
    drawText(-0.18f, 0.01f, "T            > INCREASE");
    drawText(-0.18f, -0.04f, "t            > DECREASE");

    drawText(-0.2f, -0.14f, "3. LAMP POST LAMP");
    drawText(-0.18f, -0.19f, "MOUSE LEFT   > ON/OFF");

    drawText(-0.2f, -0.29f, "4. INSTRUCTION MENU");
    drawText(-0.18f, -0.34f, "MOUSE RIGHT  > SHOW");

    drawText(-0.2f, -0.44f, "5. SOUND CONTROL");
    drawText(-0.18f, -0.49f, "M or m       > PLAY/PAUSE");

    drawText(-0.2f, -0.59f, "PRESS ENTER TO GO NEXT");
}


void afterNoonView(){
    glColor3f(141.0f / 255.0f, 102.0f / 255.0f, 156.0f / 255.0f);
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glColor3f(240.0f / 255.0f, 146.0f / 255.0f, 121.0f / 255.0f);

    glVertex2f(-1.0f, -0.6f);
    glVertex2f(1.0f, -0.6f);
    glEnd();
    glFlush();
}


void handleMouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        toggle = 1 - toggle;   // Flip between 0 and 1
        trigger = 1;         // Set flag to trigger tr() in display
        glutPostRedisplay(); // Request display update
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bulbOn = !bulbOn;
        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        showInstructions = true;
        glutPostRedisplay();
    }

}

void update(int value) {
    busX += busSpeed;
    if (busX > 1.5f) {
        busX = -1.5f; // Reset when off-screen
    }

    busX1 += speed1;
    if (busX1 > 1.5f) {
        busX1 = -1.5f; // Reset when off-screen
    }

    trainX += speed;
    if (trainX > 2.5f) {
        trainX = -1.8f; // Reset when off-screen
    }

    glutPostRedisplay();           // Refresh display
    glutTimerFunc(16, update, 0);  // ~60 FPS
}

void drawWheels(float cx, float cy, float radius, int segments){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);                // centre
    for (int i = 0; i <= segments; ++i)
    {
        float ang = 2.0f * 3.1415926f * i / segments;
        glVertex2f(cx + radius * cosf(ang),
                   cy + radius * sinf(ang));
    }
    glEnd();
}


void drawSeaWithFullWaves() {
    float startX = -1.2f;
    float endX = 1.3f;
    float baseYTop = -0.64f;
    float baseYBottom = -1.3f;
    float amplitudeTop = 0.025f;
    float amplitudeBottom = 0.015f;
    float frequency = 25.0f;
    float step = 0.01f;

    glBegin(GL_QUAD_STRIP);
    for (float x = startX; x <= endX; x += step) {
        // Top wave
        float yTop = baseYTop + amplitudeTop * sinf(frequency * x);

        // Bottom wave (inverse or random phase)
        float yBottom = baseYBottom + amplitudeBottom * sinf(frequency * x + 1.5f);

        glColor3f(16.0f / 255.0f, 118.0f / 255.0f, 171.0f / 255.0f); // Top color
        glVertex2f(x, yTop);

        glColor3f(28.0f / 255.0f, 46.0f / 255.0f, 72.0f / 255.0f);   // Bottom darker
        glVertex2f(x, yBottom);
    }
    glEnd();
}

void drawCircle(float cx, float cy, float radius, float r, float g, float b) {
    const int segments = 64; // Higher quality circle
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = 2 * M_PI * i / segments;
        glVertex2f(cx + radius * cosf(angle), cy + radius * sinf(angle));
    }
    glEnd();
}

void drawCircle(float x, float y, float radius) {
    int segments = 50;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void train(){
            glColor3f(0.0f, 0.0f, 0.0f); // Black wheels
    drawCircle(-0.1f, -0.21f, 0.02f);
    drawCircle(-0.07f, -0.21f, 0.02f);
    drawCircle(-0.30f, -0.21f, 0.02f);
    drawCircle(-0.33f, -0.21f, 0.02f);
    drawCircle(-0.53f, -0.21f, 0.02f);
    drawCircle(-0.56f, -0.21f, 0.02f);
    drawCircle(-0.78f, -0.21f, 0.02f);
    drawCircle(-0.81f, -0.21f, 0.02f);
    glColor3f(33.0f / 255.0f, 101.0f / 255.0f, 205.0f / 255.0f);

glBegin(GL_POLYGON);
    glVertex2f(0.1350034997893, -0.1709128737848);
    glVertex2f(-0.663653875868, -0.1731650270102);
    glVertex2f(-0.672419821652, -0.1675586091967);
    glVertex2f(-0.6711778158601, -0.0235470772408);
    glVertex2f(-0.662217568289, -0.0125504097672);
    glVertex2f(0.0730395501287, -0.0130359164763);
    glVertex2f(0.0836048363264, -0.0181229061271);
    glVertex2f(0.0934285114714, -0.0359617555258);
glEnd();
glFlush();

glColor3f(70.0f / 255.0f, 99.0f / 255.0f, 188.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.672419821652, -0.1675586091967);
    glVertex2f(-0.663653875868, -0.1731650270102);
    glVertex2f(-0.6726222946205, -0.1894950480424);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.663653875868, -0.1731650270102);
    glVertex2f(-0.6726222946205, -0.1894950480424);
    glVertex2f(-0.6716678995321, -0.1980846038385);
    glVertex2f(-0.6676033761315, -0.2041433437953);
    glVertex2f(-0.6004647520734, -0.2031462355172);
    glVertex2f(-0.6001323826474, -0.189851458476);
    glVertex2f(-0.6021265992036, -0.1725682483225);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.6001323826474, -0.189851458476);
    glVertex2f(-0.6021265992036, -0.1725682483225);
    glVertex2f(-0.4990056470299, -0.1726708401538);
    glVertex2f(-0.501254235113, -0.1895352507768);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.501254235113, -0.1895352507768);
    glVertex2f(-0.4992378490169, -0.1925765696545);
    glVertex2f(-0.4988023699251, -0.202429284107);
    glVertex2f(-0.4844698513919, -0.202461688988);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.4844698513919, -0.202461688988);
    glVertex2f(-0.501254235113, -0.1895352507768);
    glVertex2f(-0.4990056470299, -0.1726708401538);
    glVertex2f(-0.1442751214515, -0.1720305881822);
    glVertex2f(-0.1440068534334, -0.1936054646578);
    glVertex2f(-0.1434715090311, -0.2033000430044);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.1442751214515, -0.1720305881822);
    glVertex2f(-0.1440068534334, -0.1936054646578);
    glVertex2f(-0.1403105826612, -0.1893811661562);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.1403105826612, -0.1893811661562);
    glVertex2f(-0.1442751214515, -0.1720305881822);
    glVertex2f(-0.045527692726, -0.1723204409061);
    glVertex2f(-0.0451715611998, -0.1890821802631);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.045527692726, -0.1723204409061);
    glVertex2f(-0.0451715611998, -0.1890821802631);
    glVertex2f(-0.0428608301554, -0.1913546019395);
    glVertex2f(0.0340683190012, -0.204012298053);
    glVertex2f(0.0333980683167, -0.1728155627993);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.0428608301554, -0.1913546019395);
    glVertex2f(-0.0422816957353, -0.2026422879883);
    glVertex2f(0.0340683190012, -0.204012298053);
glEnd();
glFlush();

glColor3f(220.0f / 255.0f, 85.0f / 255.0f, 69.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.0333980683167, -0.1728155627993);
    glVertex2f(0.0340683190012, -0.204012298053);
    glVertex2f(0.1323104330942, -0.2038317008656);
    glVertex2f(0.1323104330942, -0.2038317008656);
    glVertex2f(0.1386981987919, -0.1793712322184);
    glVertex2f(0.1341708234848, -0.1731653805914);
glEnd();
glFlush();

glColor3f(18.0f / 255.0f, 70.0f / 255.0f, 111.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.6001323826474, -0.189851458476);
    glVertex2f(-0.6004647520734, -0.2031462355172);
    glVertex2f(-0.5972034339553, -0.2070345057055);
    glVertex2f(-0.5034226752894, -0.2070345057055);
    glVertex2f(-0.4988023699251, -0.202429284107);
    glVertex2f(-0.4992378490169, -0.1925765696545);
    glVertex2f(-0.501254235113, -0.1895352507768);
glEnd();
glFlush();

glColor3f(165.0f / 255.0f, 162.0f / 255.0f, 82.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.5749430701066, -0.1920985196393);
    glVertex2f(-0.5752303006079, -0.2027260481864);
    glVertex2f(-0.5258266543888, -0.2033005091889);
    glVertex2f(-0.5269755763939, -0.1920985196393);
glEnd();
glFlush();

glColor3f(18.0f / 255.0f, 70.0f / 255.0f, 111.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.1395375408537, -0.1888419250419);
    glVertex2f(-0.1440068534334, -0.1936054646578);
    glVertex2f(-0.1434715090311, -0.2033000430044);
    glVertex2f(-0.1387415801581, -0.2075845665863);
    glVertex2f(-0.0440137546271, -0.2076108443375);
    glVertex2f(-0.0422816957353, -0.2026422879883);
    glVertex2f(-0.0428608301554, -0.1913546019395);
    glVertex2f(-0.0451715611998, -0.1890821802631);
glEnd();
glFlush();

glColor3f(165.0f / 255.0f, 162.0f / 255.0f, 82.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.1140948203055, -0.1927348616661);
    glVertex2f(-0.1151217800618, -0.2033467791476);
    glVertex2f(-0.0685662711106, -0.2024909793507);
    glVertex2f(-0.0689085910293, -0.191365581991);
glEnd();
glFlush();

glColor3f(31.0f / 255.0f, 104.0f / 255.0f, 201.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-1.0121005403361, -0.1720982056166);
    glVertex2f(-1.0106908978733, -0.0249820990945);
    glVertex2f(-0.9991920807769, -0.0124379349893);
    glVertex2f(-0.6918600602003, -0.0145286290068);
    glVertex2f(-0.6824519371214, -0.0244594255901);
    glVertex2f(-0.6798722801047, -0.1676363933231);
    glVertex2f(-0.685105057256, -0.1731918359948);
glEnd();
glFlush();

glColor3f(70.0f / 255.0f, 99.0f / 255.0f, 188.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.6798722801047, -0.1676363933231);
    glVertex2f(-0.6796867217499, -0.1984390802314);
    glVertex2f(-0.685105057256, -0.1731918359948);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.685105057256, -0.1731918359948);
    glVertex2f(-0.6796867217499, -0.1984390802314);
    glVertex2f(-0.6848630436646, -0.2031084492211);
    glVertex2f(-1.0086205828803, -0.2037006328129);
    glVertex2f(-1.0122949732048, -0.1992913644235);
    glVertex2f(-1.0121005403361, -0.1720982056166);
glEnd();
glFlush();

glColor3f(18.0f / 255.0f, 70.0f / 255.0f, 111.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.850338750978, -0.1942606338307);
    glVertex2f(-0.8465905715115, -0.1913323686225);
    glVertex2f(-0.7562017296144, -0.1905661346563);
    glVertex2f(-0.7531138152649, -0.1941234282388);
    glVertex2f(-0.7529797052253, -0.2047851763872);
    glVertex2f(-0.7547901907599, -0.2069309370208);
    glVertex2f(-0.8489524297825, -0.2067818731997);
    glVertex2f(-0.8508293186658, -0.2043488690917);
glEnd();
glFlush();

glColor3f(165.0f / 255.0f, 162.0f / 255.0f, 82.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.8228646369994, -0.1934403398042);
    glVertex2f(-0.8229659519909, -0.2026600040351);
    glVertex2f(-0.7767663158448, -0.202457374052);
    glVertex2f(-0.7765594988811, -0.1937188343348);
glEnd();
glFlush();

glColor3f(198.0f / 255.0f, 148.0f / 255.0f, 70.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-1.0106908978733, -0.0249820990945);
    glVertex2f(-1.0096390068771, -0.040585803666);
    glVertex2f(-0.6830255570267, -0.0396912369075);
    glVertex2f(-0.6824519371214, -0.0244594255901);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.6718699591986, -0.0426932616589);
    glVertex2f(-0.6650962528336, -0.0361800824618);
    glVertex2f(-0.6711778158601, -0.0235470772408);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.6711778158601, -0.0235470772408);
    glVertex2f(-0.6650962528336, -0.0361800824618);
    glVertex2f(-0.0459449592458, -0.0383722208556);
    glVertex2f(-0.0380196739386, -0.0250781938887);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.0380196739386, -0.0250781938887);
    glVertex2f(-0.0294935594728, -0.0271300038974);
    glVertex2f(-0.021993684383, -0.0346298789871);
    glVertex2f(-0.0459449592458, -0.0383722208556);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.0459449592458, -0.0383722208556);
    glVertex2f(-0.021993684383, -0.0346298789871);
    glVertex2f(0.0239786612549, -0.1653821107518);
    glVertex2f(0.0032804980851, -0.1631444714902);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.0032804980851, -0.1631444714902);
    glVertex2f(0.0239786612549, -0.1653821107518);
    glVertex2f(0.0239786612549, -0.1732138481674);
    glVertex2f(0.0028454907605, -0.167365053722);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.0028454907605, -0.167365053722);
    glVertex2f(0.0239786612549, -0.1732138481674);
    glVertex2f(-0.0039918295151, -0.1729341432597);
glEnd();
glFlush();

glColor3f(29.0f / 255.0f, 183.0f / 255.0f, 217.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.6334531746583, -0.1558067742943);
    glVertex2f(-0.6000130568089, -0.1553837829931);
    glVertex2f(-0.6, -0.06);
    glVertex2f(-0.6337879668993, -0.0590924311956);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.4361172271898, -0.0587155193332);
    glVertex2f(-0.4021137670264, -0.0585189675403);
    glVertex2f(-0.4011310080622, -0.1538465870735);
    glVertex2f(-0.435920675397, -0.1544362424521);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.3350963355938, -0.0584489684123);
    glVertex2f(-0.33410616375, -0.155005519191);
    glVertex2f(-0.2971636535257, -0.154768708228);
    glVertex2f(-0.2982834793716, -0.0585553140597);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.1329993268228, -0.0606022147701);
    glVertex2f(-0.1, -0.06);
    glVertex2f(-0.0991400061348, -0.1544742624704);
    glVertex2f(-0.1335597935594, -0.1547694799733);
glEnd();
glFlush();

glColor3f(88.0f / 255.0f, 147.0f / 255.0f, 201.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.5933614895912, -0.0594866088112);
    glVertex2f(-0.5937799653455, -0.1538860044743);
    glVertex2f(-0.5581255354512, -0.1536923662689);
    glVertex2f(-0.557370190754, -0.0596854557661);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.5387676390502, -0.0725024470014);
    glVertex2f(-0.5387676390502, -0.0725024470014);
    glVertex2f(-0.4705528154455, -0.0635268123166);
    glVertex2f(-0.4644942620332, -0.0700341474631);
    glVertex2f(-0.4633723076976, -0.1131171939502);
    glVertex2f(-0.4714503789139, -0.1223172195022);
    glVertex2f(-0.5286700500297, -0.1220928286351);
    glVertex2f(-0.5380944664488, -0.1158098843557);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.3951536170536, -0.0584153610789);
    glVertex2f(-0.3933977517984, -0.1538173732783);
    glVertex2f(-0.3588657351127, -0.1536222771389);
    glVertex2f(-0.3594510235311, -0.0578300726605);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.2933319976219, -0.0583934412736);
    glVertex2f(-0.2915595680492, -0.1540640486527);
    glVertex2f(-0.2579499213085, -0.1543019419287);
    glVertex2f(-0.2580019250821, -0.0586297628291);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.2362681800976, -0.072020350739);
    glVertex2f(-0.2301561382272, -0.0640481222124);
    glVertex2f(-0.1697382139825, -0.062809534794);
    glVertex2f(-0.1623136060578, -0.0689967080646);
    glVertex2f(-0.1598387367495, -0.1137211319923);
    glVertex2f(-0.164788475366, -0.1209689635378);
    glVertex2f(-0.2261298789348, -0.1229135037086);
    glVertex2f(-0.2349686978929, -0.1165495540588);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.0930313656421, -0.0605460760963);
    glVertex2f(-0.0930475522475, -0.1546194022291);
    glVertex2f(-0.0591722837204, -0.1543573608052);
    glVertex2f(-0.06, -0.06);
glEnd();
glFlush();

glColor3f(79.0f / 255.0f, 65.0f / 255.0f, 120.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.6716678995321, -0.1980846038385);
    glVertex2f(-0.6804230206078, -0.1980954326706);
    glVertex2f(-0.6821187221498, -0.0341970484246);
    glVertex2f(-0.6726316166764, -0.0340186297379);
glEnd();
glFlush();

glColor3f(79.0f / 255.0f, 65.0f / 255.0f, 120.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.6284026671463, -0.0709896301233);
    glVertex2f(-0.6222941649366, -0.0644644211843);
    glVertex2f(-0.6101113707379, -0.0646294833505);
    glVertex2f(-0.6049816575298, -0.0702721678794);
    glVertex2f(-0.6044707060345, -0.1122083047273);
    glVertex2f(-0.6077325642788, -0.1181405211242);
    glVertex2f(-0.6232531465324, -0.1190625359115);
    glVertex2f(-0.6287852352565, -0.1124547632689);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.5886700577868, -0.0692485945782);
    glVertex2f(-0.5836442252518, -0.064595801563);
    glVertex2f(-0.5702653124446, -0.0641063291432);
    glVertex2f(-0.5647179583537, -0.068348423448);
    glVertex2f(-0.5634126985677, -0.1153377757467);
    glVertex2f(-0.568633737712, -0.1203956574177);
    glVertex2f(-0.5834810677786, -0.120558814891);
    glVertex2f(-0.5888652643961, -0.1159904056397);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.4314965585816, -0.0719342494135);
    glVertex2f(-0.423568119673, -0.0654216031671);
    glVertex2f(-0.4119586198426, -0.0651384446347);
    glVertex2f(-0.406578607726, -0.0713679323486);
    glVertex2f(-0.4060122906611, -0.1141248707485);
    glVertex2f(-0.4136575710373, -0.1212038340598);
    glVertex2f(-0.4244175952704, -0.1209206755273);
    glVertex2f(-0.4309302415167, -0.1138417122161);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.3288130439348, -0.0705733457147);
    glVertex2f(-0.322214678663, -0.0646135319207);
    glVertex2f(-0.3081665461487, -0.0641878309354);
    glVertex2f(-0.3036966858032, -0.0714247476852);
    glVertex2f(-0.3024195828474, -0.1127177432576);
    glVertex2f(-0.3081665461487, -0.1201675105);
    glVertex2f(-0.32, -0.12);
    glVertex2f(-0.3281744924569, -0.114207696706);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.0892836732076, -0.0718699773967);
    glVertex2f(-0.0842944268722, -0.0658828817943);
    glVertex2f(-0.0685284084525, -0.0648850325272);
    glVertex2f(-0.0635391621172, -0.0712712678364);
    glVertex2f(-0.0625413128501, -0.1111852385193);
    glVertex2f(-0.0661335702116, -0.1179706135353);
    glVertex2f(-0.0818995886313, -0.1183697532422);
    glVertex2f(-0.0880862540871, -0.1119835179329);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.2368273742128, -0.1422376156921);
    glVertex2f(-0.2368273742128, -0.1447957929406);
    glVertex2f(-0.1608000049094, -0.1443836179112);
    glVertex2f(-0.1609490641881, -0.1420810240986);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.1609261492239, -0.1499339677486);
    glVertex2f(-0.1608000049094, -0.1528352869818);
    glVertex2f(-0.2373273815841, -0.1529121916653);
    glVertex2f(-0.2372111008001, -0.1504702952008);
glEnd();
glFlush();

glColor3f(88.0f / 255.0f, 147.0f / 255.0f, 201.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.9430868518139, -0.1552868113166);
    glVertex2f(-0.9083709543237, -0.154717698243);
    glVertex2f(-0.9088896146924, -0.0616857402958);
    glVertex2f(-0.9426742358103, -0.0608657252201);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.8861037632391, -0.0702623670788);
    glVertex2f(-0.8806447934814, -0.065299667299);
    glVertex2f(-0.8229120527106, -0.0641417040171);
    glVertex2f(-0.8136483464551, -0.0709240603827);
    glVertex2f(-0.8133174998032, -0.1142649717923);
    glVertex2f(-0.8196035861908, -0.1220398681139);
    glVertex2f(-0.8786597135695, -0.1220398681139);
    glVertex2f(-0.8870963031951, -0.1152575117482);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.7427563799708, -0.0610159477725);
    glVertex2f(-0.7090650701458, -0.0614243272856);
    glVertex2f(-0.7087383665354, -0.152329606886);
    glVertex2f(-0.7413066326995, -0.1532280418147);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.8893404085619, -0.1430334745668);
    glVertex2f(-0.8893404085619, -0.1452364453233);
    glVertex2f(-0.8118287483798, -0.1462581503938);
    glVertex2f(-0.8120045404289, -0.1439610412011);
glEnd();
glFlush();

glColor3f(24.0f / 255.0f, 182.0f / 255.0f, 218.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.7844110902998, -0.0601991887465);
    glVertex2f(-0.7507197804749, -0.0610159477725);
    glVertex2f(-0.7496988316923, -0.1549432357694);
    glVertex2f(-0.7842069005433, -0.1539222869868);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.9830564271331, -0.0596608765778);
    glVertex2f(-0.9477101589978, -0.0601353231299);
    glVertex2f(-0.948535508957, -0.154335396395);
    glVertex2f(-0.9844740230543, -0.1540035331632);
glEnd();
glFlush();

glColor3f(76.0f / 255.0f, 66.0f / 255.0f, 123.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.9383739377764, -0.0710206155469);
    glVertex2f(-0.9145307451309, -0.0708579966006);
    glVertex2f(-0.9145492049903, -0.1156735630729);
    glVertex2f(-0.9388177488355, -0.115188192196);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.7792512789475, -0.0697082583524);
    glVertex2f(-0.7544532071357, -0.0699639085773);
    glVertex2f(-0.7541094527302, -0.1164442472969);
    glVertex2f(-0.7792330617327, -0.1167663448482);
glEnd();
glFlush();

glColor3f(241.0f / 255.0f, 233.0f / 255.0f, 183.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.0259594423073, -0.140775583802);
    glVertex2f(0.028771952653, -0.1374943217321);
    glVertex2f(0.0333255408316, -0.1395702222253);
    glVertex2f(0.0354684058569, -0.1435211296156);
    glVertex2f(0.0375443063501, -0.1482086468584);
    glVertex2f(0.0362050157093, -0.1529631286332);
    glVertex2f(0.0331916117676, -0.1576506458759);
    glVertex2f(0.027164803884, -0.1565792133633);
    glVertex2f(0.0244862226024, -0.1488782921788);
glEnd();
glFlush();

glColor3f(241.0f / 255.0f, 233.0f / 255.0f, 183.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.1118812654008, -0.1429171236519);
    glVertex2f(0.115, -0.14);
    glVertex2f(0.12, -0.14);
    glVertex2f(0.1222895558501, -0.1424134966946);
    glVertex2f(0.1236325610693, -0.1470020978604);
    glVertex2f(0.1233527683153, -0.1541088338124);
    glVertex2f(0.1213942190372, -0.159312979037);
    glVertex2f(0.1167496593206, -0.1597606474435);
    glVertex2f(0.1130004364168, -0.1571865541065);
    glVertex2f(0.1112097627912, -0.1501917352562);
glEnd();
glFlush();

glColor3f(146.0f / 255.0f, 129.0f / 255.0f, 158.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.0412719368907, -0.1375187653607);
    glVertex2f(0.0418671414714, -0.1418835989524);
    glVertex2f(0.1011891980129, -0.1422804020061);
    glVertex2f(0.1020998635417, -0.137050527676);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.0439162295579, -0.1449793809557);
    glVertex2f(0.0441232908693, -0.1487064845602);
    glVertex2f(0.1046887244439, -0.1490170765273);
    glVertex2f(0.1049993164109, -0.1444617276772);
glEnd();
glFlush();


glBegin(GL_POLYGON);
    glVertex2f(0.0471231448798, -0.1533381424659);
    glVertex2f(0.0472905231405, -0.1570204642008);
    glVertex2f(0.1067121439077, -0.1570781008503);
    glVertex2f(0.1070221277403, -0.1525316713051);
glEnd();
glFlush();


glBegin(GL_POLYGON);
    glVertex2f(0.05, -0.16);
    glVertex2f(0.05, -0.165);
    glVertex2f(0.1107098140348, -0.1648777802536);
    glVertex2f(0.1110677463276, -0.1597933951853);
glEnd();
glFlush();

glColor3f(140.0f / 255.0f, 187.0f / 255.0f, 220.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.0040678005632, -0.0472931798261);
    glVertex2f(0.0247170630047, -0.131880278907);
    glVertex2f(0.120919107034, -0.1311227824973);
    glVertex2f(0.0961742243178, -0.0475456786293);
glEnd();
glFlush();

glColor3f(239.0f / 255.0f, 226.0f / 255.0f, 102.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.0081175216889, -0.0378078712846);
    glVertex2f(0.0873921889508, -0.0368877053971);
    glVertex2f(0.0771348413815, -0.0196121726489);
    glVertex2f(-0.0173407283354, -0.0200170679477);
glEnd();
glFlush();
}

void bus(){
        glPushMatrix();
        glColor3f(255.0f / 255.0f, 114.0f / 255.0f, 92.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5672019377311, -0.5822555467175);
    glVertex2f(-0.5251137002698, -0.588444993403);
    glVertex2f(-0.1797933074284, -0.5815239397477);
    glVertex2f(-0.1745696693527, -0.5739941724924);
    glVertex2f(-0.1765830047504, -0.4635495585046);
    glVertex2f(-0.18, -0.46);
    glVertex2f(-0.562220221393, -0.4659586496848);
    glVertex2f(-0.5659829212825, -0.469930388457);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.529257504861, -0.4665575025648);
    glVertex2f(-0.4849803470441, -0.465626440835);
    glVertex2f(-0.4920150356692, -0.4603504243662);
    glVertex2f(-0.5242918423021, -0.4608676808827);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.3392412125968, -0.4647896721905);
    glVertex2f(-0.2147579218922, -0.4635412605554);
    glVertex2f(-0.2225779578785, -0.4542993998443);
    glVertex2f(-0.3351322883081, -0.4565718236131);
    glEnd();
    glFlush();

    glColor3f(26.0f / 255.0f, 46.0f / 255.0f, 53.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.35739341705, -0.463776346119);
    glVertex2f(-0.3572405526888, -0.4789950348653);
    glVertex2f(-0.4247820007165, -0.4791896788078);
    glVertex2f(-0.4255432051833, -0.4644494304463);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.4234325779156, -0.48482820249);
    glVertex2f(-0.3588497839184, -0.4836161929511);
    glVertex2f(-0.3573395088637, -0.5846412015479);
    glVertex2f(-0.421475234986, -0.5856998380176);
    glEnd();
    glFlush();

            glBegin(GL_POLYGON);
    glVertex2f(-0.353583018299, -0.4767967656245);
    glVertex2f(-0.2334144721161, -0.4739379362303);
    glVertex2f(-0.2326544087812, -0.5339829396843);
    glVertex2f(-0.3523401379787, -0.5356990878917);
    glEnd();
    glFlush();

                glBegin(GL_POLYGON);
    glVertex2f(-0.2268520765469, -0.4811560144437);
    glVertex2f(-0.1886528139787, -0.4813581269441);
    glVertex2f(-0.1871359739196, -0.5809603804793);
    glVertex2f(-0.2251410269592, -0.5818783769295);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.4270209319746, -0.5378503610917);
    glVertex2f(-0.4286547365182, -0.4792984370988);
    glVertex2f(-0.56, -0.48);
    glVertex2f(-0.5587523914621, -0.532679593523);
    glVertex2f(-0.552104261731, -0.5398201773083);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.1836713104816, -0.4716596946395);
    glVertex2f(-0.1766736091856, -0.4711634547147);
    glVertex2f(-0.1757880552097, -0.5456236801604);
    glVertex2f(-0.1822670044269, -0.5459836217835);
    glEnd();
    glFlush();

    glColor3f(56.0f / 255.0f, 90.0f / 255.0f, 100.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.554207260697, -0.4842957370729);
    glVertex2f(-0.5540117815281, -0.5124447373827);
    glVertex2f(-0.545606177269, -0.5173317166031);
    glVertex2f(-0.4939996767011, -0.516354320759);
    glVertex2f(-0.4947815933763, -0.4833183412288);
    glEnd();
    glFlush();

    glColor3f(56.0f / 255.0f, 90.0f / 255.0f, 100.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4899810134883, -0.4834067669212);
    glVertex2f(-0.4383631827804, -0.5200267446741);
    glVertex2f(-0.49, -0.52);
    glEnd();
    glFlush();

    glColor3f(56.0f / 255.0f, 90.0f / 255.0f, 100.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4899810134883, -0.4834067669212);
    glVertex2f(-0.4298528069679, -0.5335432239057);
    glVertex2f(-0.431004031605, -0.4816856487728);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.4197837044982, -0.4917490397194);
    glVertex2f(-0.3956326429126, -0.4912398367645);
    glVertex2f(-0.3936941362549, -0.5712196143027);
    glVertex2f(-0.417760416417, -0.5718065967456);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.3874329901965, -0.4917813236866);
    glVertex2f(-0.3639536924775, -0.4911943412436);
    glVertex2f(-0.3618014235199, -0.570241310231);
    glVertex2f(-0.3854763820533, -0.5710239534883);
    glEnd();
    glFlush();

            glBegin(GL_POLYGON);
    glVertex2f(-0.3516680491718, -0.4794425448131);
    glVertex2f(-0.3493875195922, -0.5323508310596);
    glVertex2f(-0.2952249420769, -0.5323508310596);
    glVertex2f(-0.2959091009508, -0.4783022800233);
    glEnd();
    glFlush();

                glBegin(GL_POLYGON);
    glVertex2f(-0.2920142811532, -0.4782260088239);
    glVertex2f(-0.2910421137774, -0.5327237759755);
    glVertex2f(-0.2353757415213, -0.5310865297327);
    glVertex2f(-0.2369740910169, -0.4785786995592);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.2233786664441, -0.4886450888687);
    glVertex2f(-0.2215051715542, -0.5682862964527);
    glVertex2f(-0.1911064463055, -0.5675493576588);
    glVertex2f(-0.1922311246392, -0.4879034807305);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.1766736091856, -0.4711634547147);
    glVertex2f(-0.1812956409956, -0.4742551171992);
    glVertex2f(-0.18, -0.54);
    glVertex2f(-0.1757880552097, -0.5456236801604);
    glEnd();
    glFlush();

   // ---------- WHEELS ----------
float rearX  = -0.48f;
float frontX = -0.23f;
float wheelY = -0.59f;   // just below the bus base
float R      = 0.030f;   // outer radius (black tyre)
float r      = 0.015f;   // inner radius (white hub)

// — outer tyre —
glColor3f(0.0f, 0.0f, 0.0f);      // black
drawWheels(rearX,  wheelY, R, 100);
drawWheels(frontX, wheelY, R, 100);

// — hubcap —
glColor3f(1.0f, 1.0f, 1.0f);      // white
drawWheels(rearX,  wheelY, r, 60);
drawWheels(frontX, wheelY, r, 60);
    glPopMatrix();
}

void blackBus(){

     glPushMatrix();
        glColor3f(255.0f / 255.0f, 245.0f / 255.0f, 92.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5672019377311, -0.5822555467175);
    glVertex2f(-0.5251137002698, -0.588444993403);
    glVertex2f(-0.1797933074284, -0.5815239397477);
    glVertex2f(-0.1745696693527, -0.5739941724924);
    glVertex2f(-0.1765830047504, -0.4635495585046);
    glVertex2f(-0.18, -0.46);
    glVertex2f(-0.562220221393, -0.4659586496848);
    glVertex2f(-0.5659829212825, -0.469930388457);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.529257504861, -0.4665575025648);
    glVertex2f(-0.4849803470441, -0.465626440835);
    glVertex2f(-0.4920150356692, -0.4603504243662);
    glVertex2f(-0.5242918423021, -0.4608676808827);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.3392412125968, -0.4647896721905);
    glVertex2f(-0.2147579218922, -0.4635412605554);
    glVertex2f(-0.2225779578785, -0.4542993998443);
    glVertex2f(-0.3351322883081, -0.4565718236131);
    glEnd();
    glFlush();

    glColor3f(26.0f / 255.0f, 46.0f / 255.0f, 53.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.35739341705, -0.463776346119);
    glVertex2f(-0.3572405526888, -0.4789950348653);
    glVertex2f(-0.4247820007165, -0.4791896788078);
    glVertex2f(-0.4255432051833, -0.4644494304463);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.4234325779156, -0.48482820249);
    glVertex2f(-0.3588497839184, -0.4836161929511);
    glVertex2f(-0.3573395088637, -0.5846412015479);
    glVertex2f(-0.421475234986, -0.5856998380176);
    glEnd();
    glFlush();

            glBegin(GL_POLYGON);
    glVertex2f(-0.353583018299, -0.4767967656245);
    glVertex2f(-0.2334144721161, -0.4739379362303);
    glVertex2f(-0.2326544087812, -0.5339829396843);
    glVertex2f(-0.3523401379787, -0.5356990878917);
    glEnd();
    glFlush();

                glBegin(GL_POLYGON);
    glVertex2f(-0.2268520765469, -0.4811560144437);
    glVertex2f(-0.1886528139787, -0.4813581269441);
    glVertex2f(-0.1871359739196, -0.5809603804793);
    glVertex2f(-0.2251410269592, -0.5818783769295);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.4270209319746, -0.5378503610917);
    glVertex2f(-0.4286547365182, -0.4792984370988);
    glVertex2f(-0.56, -0.48);
    glVertex2f(-0.5587523914621, -0.532679593523);
    glVertex2f(-0.552104261731, -0.5398201773083);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.1836713104816, -0.4716596946395);
    glVertex2f(-0.1766736091856, -0.4711634547147);
    glVertex2f(-0.1757880552097, -0.5456236801604);
    glVertex2f(-0.1822670044269, -0.5459836217835);
    glEnd();
    glFlush();

    glColor3f(56.0f / 255.0f, 90.0f / 255.0f, 100.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.554207260697, -0.4842957370729);
    glVertex2f(-0.5540117815281, -0.5124447373827);
    glVertex2f(-0.545606177269, -0.5173317166031);
    glVertex2f(-0.4939996767011, -0.516354320759);
    glVertex2f(-0.4947815933763, -0.4833183412288);
    glEnd();
    glFlush();

    glColor3f(56.0f / 255.0f, 90.0f / 255.0f, 100.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4899810134883, -0.4834067669212);
    glVertex2f(-0.4383631827804, -0.5200267446741);
    glVertex2f(-0.49, -0.52);
    glEnd();
    glFlush();

    glColor3f(56.0f / 255.0f, 90.0f / 255.0f, 100.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4899810134883, -0.4834067669212);
    glVertex2f(-0.4298528069679, -0.5335432239057);
    glVertex2f(-0.431004031605, -0.4816856487728);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.4197837044982, -0.4917490397194);
    glVertex2f(-0.3956326429126, -0.4912398367645);
    glVertex2f(-0.3936941362549, -0.5712196143027);
    glVertex2f(-0.417760416417, -0.5718065967456);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(-0.3874329901965, -0.4917813236866);
    glVertex2f(-0.3639536924775, -0.4911943412436);
    glVertex2f(-0.3618014235199, -0.570241310231);
    glVertex2f(-0.3854763820533, -0.5710239534883);
    glEnd();
    glFlush();

            glBegin(GL_POLYGON);
    glVertex2f(-0.3516680491718, -0.4794425448131);
    glVertex2f(-0.3493875195922, -0.5323508310596);
    glVertex2f(-0.2952249420769, -0.5323508310596);
    glVertex2f(-0.2959091009508, -0.4783022800233);
    glEnd();
    glFlush();

                glBegin(GL_POLYGON);
    glVertex2f(-0.2920142811532, -0.4782260088239);
    glVertex2f(-0.2910421137774, -0.5327237759755);
    glVertex2f(-0.2353757415213, -0.5310865297327);
    glVertex2f(-0.2369740910169, -0.4785786995592);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.2233786664441, -0.4886450888687);
    glVertex2f(-0.2215051715542, -0.5682862964527);
    glVertex2f(-0.1911064463055, -0.5675493576588);
    glVertex2f(-0.1922311246392, -0.4879034807305);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.1766736091856, -0.4711634547147);
    glVertex2f(-0.1812956409956, -0.4742551171992);
    glVertex2f(-0.18, -0.54);
    glVertex2f(-0.1757880552097, -0.5456236801604);
    glEnd();
    glFlush();

   // ---------- WHEELS ----------
float rearX  = -0.48f;
float frontX = -0.23f;
float wheelY = -0.59f;   // just below the bus base
float R      = 0.030f;   // outer radius (black tyre)
float r      = 0.015f;   // inner radius (white hub)

// — outer tyre —
glColor3f(0.0f, 0.0f, 0.0f);      // black
drawWheels(rearX,  wheelY, R, 100);
drawWheels(frontX, wheelY, R, 100);

// — hubcap —
glColor3f(1.0f, 1.0f, 1.0f);      // white
drawWheels(rearX,  wheelY, r, 60);
drawWheels(frontX, wheelY, r, 60);
    glPopMatrix();
}
void drawTree(float x, float y) {
    // Elegant tapered trunk with subtle gradient
    glBegin(GL_POLYGON);
        glColor3f(0.4f, 0.2f, 0.07f); // Base color
        glVertex2f(x - 0.018f, y);
        glVertex2f(x + 0.018f, y);
        glColor3f(0.3f, 0.15f, 0.05f); // Darker at top
        glVertex2f(x + 0.012f, y + 0.18f);
        glVertex2f(x - 0.012f, y + 0.18f);
    glEnd();

    // Main foliage composition - 3 tiers of circles

    // Bottom tier (largest circles)
    drawCircle(x - 0.07f, y + 0.22f, 0.11f, 0.15f, 0.35f, 0.12f);
    drawCircle(x + 0.07f, y + 0.22f, 0.11f, 0.15f, 0.35f, 0.12f);
    drawCircle(x, y + 0.2f, 0.13f, 0.12f, 0.32f, 0.1f);

    // Middle tier (medium circles)
    drawCircle(x - 0.05f, y + 0.28f, 0.09f, 0.25f, 0.45f, 0.15f);
    drawCircle(x + 0.05f, y + 0.28f, 0.09f, 0.25f, 0.45f, 0.15f);
    drawCircle(x, y + 0.3f, 0.1f, 0.22f, 0.42f, 0.14f);

    // Top tier (smaller circles)
    drawCircle(x - 0.03f, y + 0.36f, 0.07f, 0.35f, 0.55f, 0.2f);
    drawCircle(x + 0.03f, y + 0.36f, 0.07f, 0.35f, 0.55f, 0.2f);
    drawCircle(x, y + 0.38f, 0.08f, 0.4f, 0.6f, 0.25f);

    // Accent circles for depth and richness
    drawCircle(x - 0.09f, y + 0.25f, 0.06f, 0.18f, 0.38f, 0.13f);
    drawCircle(x + 0.09f, y + 0.25f, 0.06f, 0.18f, 0.38f, 0.13f);
    drawCircle(x - 0.11f, y + 0.3f, 0.05f, 0.28f, 0.48f, 0.18f);
    drawCircle(x + 0.11f, y + 0.3f, 0.05f, 0.28f, 0.48f, 0.18f);

    // Highlight circles (brightest)
    drawCircle(x - 0.02f, y + 0.32f, 0.04f, 0.45f, 0.65f, 0.3f);
    drawCircle(x + 0.02f, y + 0.32f, 0.04f, 0.45f, 0.65f, 0.3f);
    drawCircle(x, y + 0.34f, 0.05f, 0.5f, 0.7f, 0.35f);
}



void drawCloud(float x, float y, float size) {
    glColor3f(1.0f, 1.0f, 1.0f); // White color for clouds

    // Cloud is made of several overlapping circles
    drawCircle(x, y, size * 0.5f, 20);
    drawCircle(x + size * 0.4f, y + size * 0.1f, size * 0.4f, 20);
    drawCircle(x + size * 0.7f, y, size * 0.35f, 20);
    drawCircle(x + size * 0.3f, y - size * 0.1f, size * 0.35f, 20);
    drawCircle(x - size * 0.2f, y, size * 0.4f, 20);
}

void drawClouds() {
    // Draw several clouds at different positions
    drawCloud(-0.8f + cloudOffset, 0.7f, 0.15f);
    drawCloud(-0.4f + cloudOffset * 0.8f, 0.8f, 0.12f);
    drawCloud(0.0f + cloudOffset * 0.6f, 0.65f, 0.18f);
    drawCloud(0.5f + cloudOffset * 0.4f, 0.75f, 0.14f);
    drawCloud(0.8f + cloudOffset * 0.3f, 0.7f, 0.16f);

    // Some smaller distant clouds
    drawCloud(-0.9f + cloudOffset * 0.5f, 0.5f, 0.1f);
    drawCloud(-0.2f + cloudOffset * 0.7f, 0.55f, 0.08f);
    drawCloud(0.3f + cloudOffset * 0.6f, 0.45f, 0.09f);
    drawCloud(0.9f + cloudOffset * 0.4f, 0.5f, 0.11f);
}

void airplane() {
    glPushMatrix();
    glColor3f(0.99f, 0.99f, 0.99f);
    glBegin(GL_POLYGON);
    glVertex2f(0.5869253384256, 0.5766049439836);
    glVertex2f(0.5972289115965, 0.5718494486739);
    glVertex2f(0.7389030426973, 0.5718494486739);
    glVertex2f(0.7549528393675, 0.5754160701562);
    glVertex2f(0.7624823736078, 0.5805678567417);
    glVertex2f(0.7624878070089, 0.5885372631524);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(0.5869253384256, 0.5766049439836);
    glVertex2f(0.586132755874, 0.6130637413578);
    glVertex2f(0.7175033138038, 0.6134600326336);
    glVertex2f(0.737516023232, 0.6104878480651);
    glVertex2f(0.7468288682135, 0.6057323527554);
    glVertex2f(0.7565380044707, 0.596221362136);
    glVertex2f(0.7624878070089, 0.5885372631524);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.582233477999, 0.61285264165);
    glVertex2f(0.586132755874, 0.6130637413578);
    glVertex2f(0.5869253384256, 0.5766049439836);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5869253384256, 0.5766049439836);
    glVertex2f(0.582233477999, 0.61285264165);
    glVertex2f(0.565, 0.61);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5869253384256, 0.5766049439836);
    glVertex2f(0.565, 0.61);
    glVertex2f(0.5403306618568, 0.591436691243);
    glVertex2f(0.555, 0.585);
    glVertex2f(0.565, 0.58);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(0.555, 0.585);
    glVertex2f(0.5403306618568, 0.591436691243);
    glVertex2f(0.5359163496311, 0.5881871921557);
    glEnd();
    glFlush();

         glBegin(GL_POLYGON);
    glVertex2f(0.53, 0.59);
    glVertex2f(0.5359163496311, 0.5881871921557);
    glVertex2f(0.5403306618568, 0.591436691243);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5281915363389, 0.6039949358511);
    glVertex2f(0.53, 0.59);
    glVertex2f(0.5403306618568, 0.591436691243);
    glVertex2f(0.565, 0.61);
    glVertex2f(0.5557854110871, 0.6283623105181);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5557854110871, 0.6283623105181);
    glVertex2f(0.565, 0.61);
    glVertex2f(0.582233477999, 0.61285264165);
    glVertex2f(0.5823967376713, 0.6277092718289);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5281915363389, 0.6039949358511);
    glVertex2f(0.53, 0.59);
    glVertex2f(0.5207166963469, 0.5922472322887);
    glVertex2f(0.5184969811476, 0.5934012566051);
    glVertex2f(0.5184223294943, 0.5956034803773);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5281915363389, 0.6039949358511);
    glVertex2f(0.5557854110871, 0.6283623105181);
    glVertex2f(0.5319194687666, 0.660163855108);
    glVertex2f(0.5059320665605, 0.659909076655);
    glVertex2f(0.5036390604835, 0.646915375552);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(0.5059320665605, 0.659909076655);
    glVertex2f(0.497003105114, 0.6585141215284);
    glVertex2f(0.4871932241909, 0.6556044110852);
    glVertex2f(0.4868606858545, 0.6521958931373);
    glVertex2f(0.5036390604835, 0.646915375552);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.6237308610562, 0.57448718661);
    glVertex2f(0.62944477399, 0.5749267183742);
    glVertex2f(0.6258186369359, 0.5607518189807);
    glVertex2f(0.6216430851765, 0.5611913507448);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.7341199099207, 0.5756626063538);
    glVertex2f(0.738969178611, 0.5771070693679);
    glVertex2f(0.7347389654982, 0.5619402077196);
    glVertex2f(0.7311278079629, 0.5619402077196);
    glEnd();
    glFlush();

     glColor3f(113.0f / 255.0f, 158.0f / 255.0f, 240.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.6216430851765, 0.5611913507448);
    glVertex2f(0.6258186369359, 0.5607518189807);
    glVertex2f(0.6273474362004, 0.5594825670554);
    glVertex2f(0.6272527864069, 0.557352946703);
    glVertex2f(0.6270161619233, 0.555128676557);
    glVertex2f(0.6243186428102, 0.5536616047587);
    glVertex2f(0.6211478747298, 0.5535196300685);
    glVertex2f(0.6191602290675, 0.5548920520734);
    glVertex2f(0.61840303072, 0.557352946703);
    glVertex2f(0.6194441784478, 0.5600504658161);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.7311278079629, 0.5619402077196);
    glVertex2f(0.7347389654982, 0.5619402077196);
    glVertex2f(0.7371926807899, 0.5596290769408);
    glVertex2f(0.737104864416, 0.557127129937);
    glVertex2f(0.7352176646726, 0.5545902384786);
    glVertex2f(0.7314432651857, 0.55421898607);
    glVertex2f(0.7286588721216, 0.5559514973099);
    glVertex2f(0.7284423082166, 0.5587977657754);
    glVertex2f(0.7293395015372, 0.560777778621);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.742955950911, 0.6020158207991);
    glVertex2f(0.7505501933654, 0.6021692398386);
    glVertex2f(0.756917083504, 0.5954188021013);
    glVertex2f(0.7433394985097, 0.5946517069039);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.7118160637357, 0.6020614044489);
    glVertex2f(0.7149848972521, 0.6019733812956);
    glVertex2f(0.715336989865, 0.5938752511983);
    glVertex2f(0.7121681563487, 0.593787228045);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.7061825819289, 0.6017093118359);
    glVertex2f(0.7099675775179, 0.6017093118359);
    glVertex2f(0.710407693284, 0.5934351354321);
    glVertex2f(0.7066226976951, 0.5931710659724);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.7001089843559, 0.6015332655295);
    glVertex2f(0.704334095711, 0.6017973349892);
    glVertex2f(0.7045981651707, 0.5931710659724);
    glVertex2f(0.7003730538156, 0.5930830428192);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.6973802666057, 0.6014452423762);
    glVertex2f(0.6977323592186, 0.5930830428192);
    glVertex2f(0.6937713173232, 0.5928189733595);
    glVertex2f(0.6937713173232, 0.6016212886827);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.6871695808308, 0.6015332655295);
    glVertex2f(0.691042599573, 0.6014452423762);
    glVertex2f(0.6913946921859, 0.592995019666);
    glVertex2f(0.6871695808308, 0.592995019666);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.681576220584, 0.6015878786962);
    glVertex2f(0.6851185096466, 0.6016601703098);
    glVertex2f(0.6854076761007, 0.5929851766871);
    glVertex2f(0.6820099702651, 0.5929851766871);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.6764314572518, 0.6012837973317);
    glVertex2f(0.6796549205658, 0.6015035789213);
    glVertex2f(0.6799479626853, 0.5930053574571);
    glVertex2f(0.6766512388414, 0.5928588363974);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.6691786647953, 0.6012105368019);
    glVertex2f(0.6733545149976, 0.6015035789213);
    glVertex2f(0.673647557117, 0.5924192732182);
    glVertex2f(0.6694717069148, 0.5923460126884);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.6635376039958, 0.6015768394512);
    glVertex2f(0.6670541094293, 0.6014303183915);
    glVertex2f(0.6673471515487, 0.5927123153377);
    glVertex2f(0.6633910829361, 0.5923460126884);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.6359730703573, 0.6032923188647);
    glVertex2f(0.641825870506, 0.6030582068588);
    glVertex2f(0.6422940945179, 0.5925231665911);
    glVertex2f(0.6365583503722, 0.5919378865762);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.6276620941462, 0.6037605428766);
    glVertex2f(0.6332807822889, 0.6035264308706);
    glVertex2f(0.6332807822889, 0.5924061105881);
    glVertex2f(0.6275450381432, 0.5915867185673);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.6191170059291, 0.6031752628617);
    glVertex2f(0.623799246048, 0.6031752628617);
    glVertex2f(0.623916302051, 0.5919378865762);
    glVertex2f(0.6188828939231, 0.5921719985822);
    glEnd();
    glFlush();


    glPopMatrix();
}

void cityBuilding(){
        glPushMatrix();
     glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.9165551075862f, 0.3299784835584f);
    glVertex2f(-0.9240548496061f, -0.5525364414272f);
    glVertex2f(-0.7183019878658f, -0.5566188394776f);
    glVertex2f(-0.7020075890435f, 0.3291304696511f);
    glEnd();
    glFlush();
        glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8891644156834f, 0.3271369786236f);
    glVertex2f(-0.7597081554481f, 0.3276129207568f);
    glVertex2f(-0.7592322133149f, 0.3699717706133f);
    glVertex2f(-0.888212531417f, 0.36949582848f);
    glEnd();
    glFlush();

        glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6866933736163f, 0.2020009413475f);
    glVertex2f(-0.4732417088864f, 0.2718578498046f);
    glVertex2f(-0.4868249966419f, -0.5586631729629f);
    glVertex2f(-0.6944552523338f, -0.5567227032836f);
    glEnd();
    glFlush();

            glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4452670604313f, 0.3315723061369f);
    glVertex2f(-0.2269652712555f, 0.3315723061369f);
    glVertex2f(-0.2348729285514f, -0.5472967100592f);
    glVertex2f(-0.4458434790875f, -0.5503542542699f);
    glEnd();
    glFlush();

                glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4120574315271f, 0.3684974205607f);
    glVertex2f(-0.2827431560154f, 0.3694038767643f);
    glVertex2f(-0.2827431560154f, 0.3080879251785f);
    glVertex2f(-0.4120574315271f, 0.3096428818473f);
    glEnd();
    glFlush();


                    glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2107971942833f, 0.268941344189f);
    glVertex2f(0.003270783055f, 0.2213706825582f);
    glVertex2f(0.0052528939563f, -0.5437241253362f);
    glVertex2f(-0.2180564353927f, -0.5595268869019f);
    glEnd();
    glFlush();

                        glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0284404814737f, 0.3387420996324f);
    glVertex2f(0.2418031220802f, 0.1667969127908f);
    glVertex2f(0.2331893190512f, -0.5529918150577f);
    glVertex2f(0.0316650802774f, -0.5561103804765f);
    glEnd();
    glFlush();

                            glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.2647210540119f, 0.2702908745339f);
    glVertex2f(0.4718011715158f, 0.2204867956405f);
    glVertex2f(0.4693239829293f, -0.5551359797074f);
    glVertex2f(0.2565709254164f, -0.5572376006196f);
    glEnd();
    glFlush();

                            glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.4972220346737f, 0.3336691273783f);
    glVertex2f(0.7150641291566f, 0.3336691273783f);
    glVertex2f(0.6910838447224f, -0.575443243912f);
    glVertex2f(0.4935659498468f, -0.5845594544448f);
    glEnd();
    glFlush();

    glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.5295844832327f, 0.3304091127252f);
    glVertex2f(0.6523735496478f, 0.3283961772102f);
    glVertex2f(0.6537155066578f, 0.3713388015302f);
    glVertex2f(0.5269005692127f, 0.3726807585402f);
    glEnd();
    glFlush();

    glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.7380007466471f, 0.2672377290805f);
    glVertex2f(0.9261938773781f, 0.2266470538248f);
    glVertex2f(0.9209675282814f, -0.5891948655964f);
    glVertex2f(0.7190061904525f, -0.5923019631014f);
    glEnd();
    glFlush();

    glColor3f(173.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.92, 0.2);
    glVertex2f(0.9466197653753, 0.2014711670211);
    glVertex2f(0.9522201793967, -0.5913621304238);
    glVertex2f(0.9209675282814, -0.5891948655964);
    glEnd();
    glFlush();

// Building code
glColor3f(140.0f / 255.0f, 211.0f / 255.0f, 226.0f / 255.0f);
glBegin(GL_POLYGON);
glVertex2f(-0.7778522242043f, 0.1430806256088f);
glVertex2f(-0.4086364593232f, 0.1430806256088f);
glVertex2f(-0.409961164317f, -0.5530465694392f);
glVertex2f(-0.7802353187657f, -0.5548689365131f);
glEnd();

// Window pattern - now with 4 columns
glColor3f(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);

// First row of windows (aligned left)
for (float y = 0.03f; y > -0.05f; y -= 0.02f) {
    // Column 1
    glBegin(GL_POLYGON);
    glVertex2f(-0.71f, y);
    glVertex2f(-0.693f, y);
    glVertex2f(-0.693f, y - 0.0085f);
    glVertex2f(-0.71f, y - 0.0085f);
    glEnd();

    // Column 2
    glBegin(GL_POLYGON);
    glVertex2f(-0.65f, y);
    glVertex2f(-0.633f, y);
    glVertex2f(-0.633f, y - 0.0085f);
    glVertex2f(-0.65f, y - 0.0085f);
    glEnd();

    // Column 3
    glBegin(GL_POLYGON);
    glVertex2f(-0.59f, y);
    glVertex2f(-0.573f, y);
    glVertex2f(-0.573f, y - 0.0085f);
    glVertex2f(-0.59f, y - 0.0085f);
    glEnd();

    // NEW Column 4 (extra column)
    glBegin(GL_POLYGON);
    glVertex2f(-0.53f, y);
    glVertex2f(-0.513f, y);
    glVertex2f(-0.513f, y - 0.0085f);
    glVertex2f(-0.53f, y - 0.0085f);
    glEnd();
}

// Second row of windows (offset right)
for (float y = -0.03f; y > -0.45f; y -= 0.02f) {
    // Column 1
    glBegin(GL_POLYGON);
    glVertex2f(-0.68f, y);
    glVertex2f(-0.663f, y);
    glVertex2f(-0.663f, y - 0.0085f);
    glVertex2f(-0.68f, y - 0.0085f);
    glEnd();

    // Column 2
    glBegin(GL_POLYGON);
    glVertex2f(-0.62f, y);
    glVertex2f(-0.603f, y);
    glVertex2f(-0.603f, y - 0.0085f);
    glVertex2f(-0.62f, y - 0.0085f);
    glEnd();

    // Column 3
    glBegin(GL_POLYGON);
    glVertex2f(-0.56f, y);
    glVertex2f(-0.543f, y);
    glVertex2f(-0.543f, y - 0.0085f);
    glVertex2f(-0.56f, y - 0.0085f);
    glEnd();

    // NEW Column 4 (extra column)
    glBegin(GL_POLYGON);
    glVertex2f(-0.50f, y);
    glVertex2f(-0.483f, y);
    glVertex2f(-0.483f, y - 0.0085f);
    glVertex2f(-0.50f, y - 0.0085f);
    glEnd();
}

// Third row of windows (aligned with first row)
for (float y = -0.09f; y > -0.45f; y -= 0.02f) {
    // Column 1
    glBegin(GL_POLYGON);
    glVertex2f(-0.71f, y);
    glVertex2f(-0.693f, y);
    glVertex2f(-0.693f, y - 0.0085f);
    glVertex2f(-0.71f, y - 0.0085f);
    glEnd();

    // Column 2
    glBegin(GL_POLYGON);
    glVertex2f(-0.65f, y);
    glVertex2f(-0.633f, y);
    glVertex2f(-0.633f, y - 0.0085f);
    glVertex2f(-0.65f, y - 0.0085f);
    glEnd();

    // Column 3
    glBegin(GL_POLYGON);
    glVertex2f(-0.59f, y);
    glVertex2f(-0.573f, y);
    glVertex2f(-0.573f, y - 0.0085f);
    glVertex2f(-0.59f, y - 0.0085f);
    glEnd();

    // NEW Column 4 (extra column)
    glBegin(GL_POLYGON);
    glVertex2f(-0.53f, y);
    glVertex2f(-0.513f, y);
    glVertex2f(-0.513f, y - 0.0085f);
    glVertex2f(-0.53f, y - 0.0085f);
    glEnd();
}

glFlush();
                    glColor3f(85.0f / 255.0f,149.0f / 255.0f, 196.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8080875742622f, 0.1199156816554f);
    glVertex2f(-0.3878418160996f, 0.1180938069813f);
    glVertex2f(-0.3878418160996f, 0.1041261011464f);
    glVertex2f(-0.8086948658202f, 0.1041261011464f);
    glEnd();
    glFlush();

                        glColor3f(85.0f / 255.0f,149.0f / 255.0f, 196.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3987730641443f, 0.0725469401284f);
    glVertex2f(-0.3975584810282f, 0.0597938174096f);
    glVertex2f(-0.7983709093336f, 0.0597938174096f);
    glVertex2f(-0.7989782008916f, 0.0737615232445f);
    glEnd();
    glFlush();

        glColor3f(24.0f / 255.0f,181.0f / 255.0f, 223.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6678515941379f, 0.156946214237f);
    glVertex2f(-0.6295413937075f, 0.1556469540328f);
    glVertex2f(-0.6340523999875f, -0.5292807146483f);
    glVertex2f(-0.6748604582112f, -0.5312239555161f);
    glEnd();
    glFlush();




    glColor3f(24.0f / 255.0f,181.0f / 255.0f, 223.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5626548606533f, 0.1521820208384f);
    glVertex2f(-0.5271398523085f, 0.1537722450927f);
    glVertex2f(-0.5213444296554f, -0.5370536781195f);
    glVertex2f(-0.5647885586098f, -0.5353965598743f);
    glEnd();
    glFlush();

        glColor3f(85.0f / 255.0f,149.0f / 255.0f, 196.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8355058681035, -0.3924291069909);
    glVertex2f(-0.3687862759945, -0.3892826827744);
    glVertex2f(-0.3677374679223, -0.5392622370926);
    glVertex2f(-0.8376034842478, -0.5413598532369);
    glEnd();
    glFlush();

            glColor3f(85.0f / 255.0f,149.0f / 255.0f, 196.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8355058681035, -0.3924291069909);
    glVertex2f(-0.3687862759945, -0.3892826827744);
    glVertex2f(-0.3677374679223, -0.5392622370926);
    glVertex2f(-0.8376034842478, -0.5413598532369);
    glEnd();
    glFlush();

                glColor3f(85.0f / 255.0f,149.0f / 255.0f, 196.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8094087372461f, 0.1562490116758f);
    glVertex2f(-0.3866809748474f, 0.1550531764215f);
    glVertex2f(-0.3872788924746f, 0.1407031533697f);
    glVertex2f(-0.8093058958036f, 0.1436927226196f);
    glEnd();
    glFlush();

    glColor3f(255.0f / 255.0f,255.0f / 255.0f, 255.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.64891756272f, 0.1082218083678f);
    glVertex2f(-0.548203643539f, 0.107880405252f);
    glVertex2f(-0.548203643539f, 0.0614495814939f);
    glVertex2f(-0.6482347564883f, 0.0617909846098f);
    glEnd();
    glFlush();

    glColor3f(255.0f / 255.0f,255.0f / 255.0f, 255.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6312842235338f, 0.1010164327646f);
    glVertex2f(-0.56f, 0.1f);
    glVertex2f(-0.598638614476f, 0.1294647492293f);
    glEnd();
    glFlush();

glColor3f(140.0f / 255.0f, 211.0f / 255.0f, 226.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.3780287774307, -0.4033439879658);
    glVertex2f(-0.3771235975905, -0.5382157841555);
    glVertex2f(-0.5135040268472, -0.5388192373823);
    glVertex2f(-0.5150126599142, -0.404249167806);
    glEnd();
    glFlush();

glColor3f(140.0f / 255.0f, 211.0f / 255.0f, 226.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.5243661849296, -0.4036457145792);
    glVertex2f(-0.5255730913832, -0.5373106043153);
    glVertex2f(-0.64, -0.54);
    glVertex2f(-0.6411343843153, -0.404249167806);
    glEnd();
    glFlush();

glColor3f(140.0f / 255.0f, 211.0f / 255.0f, 226.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.7068001098475, -0.4036061856398);
    glVertex2f(-0.7045822578628, -0.5391674820657);
    glVertex2f(-0.8162834839316, -0.5370650633226);
    glVertex2f(-0.8151505653011, -0.4032101679198);
    glEnd();
    glFlush();

    glColor3f(88.0f / 255.0f, 147.0f / 255.0f, 203.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.1116502554775, 0.1514911689587);
    glVertex2f(0.1917517233389, 0.1519744749426);
    glVertex2f(0.1917517233389, -0.5412693053477);
    glVertex2f(-0.1226020629189, -0.5391874921936);
    glEnd();
    glFlush();

        glColor3f(21.0f / 255.0f, 184.0f / 255.0f, 224.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.110201492607, 0.0938146251114);
    glVertex2f(0.1917687167781, 0.0961197412136);
    glVertex2f(0.1917517233389, -0.5412693053477);
    glVertex2f(-0.1226020629189, -0.5391874921936);
    glEnd();
    glFlush();

    glColor3f(139.0f / 255.0f, 208.0f / 255.0f, 228.0f / 255.0f);
        glBegin(GL_POLYGON);
    glVertex2f(-0.0652816964257, 0.0914838823547);
    glVertex2f(0.1525623270498, 0.0966706448184);
    glVertex2f(0.1542912478711, -0.5274697716471);
    glVertex2f(-0.0670106172469, -0.5309276132896);
    glEnd();
    glFlush();
            glColor3f(21.0f / 255.0f, 184.0f / 255.0f, 224.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.1378628858331, -0.0421872249169);
    glVertex2f(0.2217352261064, -0.0421872249169);
    glVertex2f(0.2217352261064, -0.5423974190891);
    glVertex2f(-0.1332526536287, -0.5377871868848);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.1470833502418, -0.3349369698933);
    glVertex2f(0.2355659227194, -0.3395472020976);
    glVertex2f(0.2309556905151, -0.5377871868848);
    glVertex2f(-0.1447782341396, -0.5377871868848);
    glEnd();
    glFlush();

        glColor3f(139.0f / 255.0f, 208.0f / 255.0f, 228.0f / 255.0f);
        glBegin(GL_POLYGON);
    glVertex2f(0.0086703138847, -0.3279266425065);
    glVertex2f(0.071340751966, -0.3263980952363);
    glVertex2f(0.0721050256011, -0.447917603223);
    glVertex2f(0.0109631347902, -0.4494461504933);
    glEnd();
    glFlush();

            glColor3f(139.0f / 255.0f, 208.0f / 255.0f, 228.0f / 255.0f);
        glBegin(GL_POLYGON);
    glVertex2f(0.0312484638443, -0.3372863786906);
    glVertex2f(0.0490530984104, -0.3339352549189);
    glVertex2f(0.0460846815239, -0.0118620227291);
    glVertex2f(0.0312425970912, -0.0088936058425);
    glEnd();
    glFlush();

// Draw white windows
glColor3f(1.0f, 1.0f, 1.0f);

// Window dimensions (calculated from your window code)
const float window_w = 0.1324224569582f - 0.1088140982991f; // Width = ~0.0236
const float window_h = 0.0655572045027f - 0.0544937263143f; // Height = ~0.011

// Building boundaries (using your vertex coordinates)
const float left = -0.112f;  // Slightly beyond leftmost point for margin
const float right = 0.191f;  // Slightly before rightmost point
const float top = 0.093f;    // Slightly below top point
const float bottom = -0.49f;// Slightly above bottom point

// Calculate optimal window grid (more windows vertically)
const int cols = 5;  // Horizontal windows
const int rows = 15; // Vertical windows (fills full height)

// Calculate dynamic spacing with edge margins
const float margin_x = 0.008f;
const float margin_y = 0.005f;
const float spacing_x = (right - left - cols*window_w - 2*margin_x)/(cols - 1);
const float spacing_y = (top - bottom - rows*window_h - 2*margin_y)/(rows - 1);

// Draw complete window grid
for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
        float x = left + margin_x + col*(window_w + spacing_x);
        float y = bottom + margin_y + row*(window_h + spacing_y);

        // Skip windows that would extend beyond building edges
        if (x + window_w > right || y + window_h > top) continue;

        glBegin(GL_POLYGON);
            glVertex2f(x, y + window_h);         // Top-left
            glVertex2f(x + window_w, y + window_h); // Top-right
            glVertex2f(x + window_w, y);           // Bottom-right
            glVertex2f(x, y);                      // Bottom-left
        glEnd();
    }
}

glFlush();


    glColor3f(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.0130954629344, 0.1963377300308);
    glVertex2f(0.0925502526955, 0.1970055863402);
    glVertex2f(0.0928720790162, 0.0936993373993);
    glVertex2f(-0.0117214752075, 0.0927338584372);
    glEnd();
    glFlush();

    glColor3f(81.0f / 255.0f, 148.0f / 255.0f, 213.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.6, -0.1);
    glVertex2f(0.8451011343818, -0.1027089536387);
    glVertex2f(0.8471816585857, -0.6024386461898);
    glVertex2f(0.6, -0.6);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.8451011343818, -0.1027089536387);
    glVertex2f(0.6, -0.1);
    glVertex2f(0.6012068597155, 0.025865745506);
    glVertex2f(0.6886906756284, 0.0232147207814);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.6012068597155, 0.025865745506);
    glVertex2f(0.6886906756284, 0.0232147207814);
    glVertex2f(0.6043762338948, 0.1144522047601);
    glEnd();
    glFlush();

    glColor3f(169.0f / 255.0f, 217.0f / 255.0f, 252.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.6147660467305, 0.0815092203969);
    glVertex2f(0.6144891350063, 0.0558948859148);
    glVertex2f(0.6406572929367, 0.0568640769493);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(0.6189697017817, 0.0514730784566);
    glVertex2f(0.643486520284, 0.0524537511967);
    glVertex2f(0.6425058475439, 0.027119705411);
    glEnd();
    glFlush();

            glBegin(GL_POLYGON);
    glVertex2f(0.6493705567245, 0.0462428238427);
    glVertex2f(0.6487167748978, 0.020418441687);
    glVertex2f(0.6755218297936, 0.020418441687);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.6145566744512, 0.0454255965593);
    glVertex2f(0.6137394471678, 0.020418441687);
    glVertex2f(0.64, 0.02);
    glEnd();
    glFlush();

    glColor3f(215.0f / 255.0f, 225.0f / 255.0f, 240.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.5960260679108, -0.107807302137);
    glVertex2f(0.5961857285313, -0.1162881019158);
    glVertex2f(0.8525545401926, -0.1181409343944);
    glVertex2f(0.852671513456, -0.1087576200765);
    glEnd();
    glFlush();

        glBegin(GL_POLYGON);
    glVertex2f(0.8523718108624, -0.1616997585895);
    glVertex2f(0.8523718108624, -0.1737369388436);
    glVertex2f(0.594374914083, -0.1761443748944);
    glVertex2f(0.5951773927667, -0.1653109126657);
    glEnd();
    glFlush();

            glBegin(GL_POLYGON);
    glVertex2f(0.5953319520218, -0.2826147770475);
    glVertex2f(0.5953319520218, -0.2954653951543);
    glVertex2f(0.8504405188819, -0.2892780605103);
    glVertex2f(0.8504405188819, -0.2773793400411);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5951754999167, -0.3438123009907);
    glVertex2f(0.8522472554248, -0.3396157812482);
    glVertex2f(0.8523599748165, -0.351476496908);
    glVertex2f(0.5951754999167, -0.3567668719196);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.5969124229061, -0.40389372117);
    glVertex2f(0.8487531164369, -0.3982639052691);
    glVertex2f(0.8501673774746, -0.413820776683);
    glVertex2f(0.5972189610092, -0.4176397237161);
    glEnd();
    glFlush();

        glColor3f(136.0f / 255.0f, 212.0f / 255.0f, 232.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.6354722973325, -0.1315621827636);
    glVertex2f(0.897015656109, -0.1304655649071);
    glVertex2f(0.8989173560959, -0.5633880707456);
    glVertex2f(0.6326200837438, -0.56791996416);
    glEnd();
    glFlush();

    // Draw windows
// Window parameters
float buildingLeft = 0.635f;
float buildingRight = 0.897f;
float buildingTop = -0.13f;
float buildingBottom = -0.567f;

// ====== MAIN WINDOWS ====== (smaller, more numerous)
float windowWidth = 0.02f;  // Smaller width for more windows
float windowHeight = 0.03f; // Smaller height
float spacingX = 0.015f;    // Reduced spacing between windows
float spacingY = 0.02f;

int windowColumns = (int)((buildingRight - buildingLeft - spacingX) / (windowWidth + spacingX));
int windowRows = (int)((buildingTop - buildingBottom - spacingY*2) / (windowHeight + spacingY));

float startX = buildingLeft + spacingX;
float startY = buildingTop - spacingY - windowHeight;

// Draw grid of small windows (some lit, some dark)
for (int i = 0; i < windowRows; i++) {
    for (int j = 0; j < windowColumns; j++) {
        float x = startX + j * (windowWidth + spacingX);
        float y = startY - i * (windowHeight + spacingY);

        // Randomly make some windows lit (yellow)
        if (rand() % 4 == 0) {  // 25% chance of being lit
            glColor3f(0.9f, 0.8f, 0.3f); // Yellow (light on)
        } else {
            glColor3f(0.9f, 0.8f, 0.3f);  // Dark blue (light off)
        }

        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + windowWidth, y);
        glVertex2f(x + windowWidth, y + windowHeight);
        glVertex2f(x, y + windowHeight);
        glEnd();
    }
}
glFlush();

glColor3f(88.0f / 255.0f, 149.0f / 255.0f, 205.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0206957957274, -0.5396522035708);
    glVertex2f(1.0570892329888, -0.5374156211933);
    glVertex2f(1.0570892329888, -0.6559544872019);
    glVertex2f(-1.0497713666352, -0.6492447400693);
    glEnd();
    glFlush();

// Draw the filled polygon (original box)
glColor3f(146.0f / 255.0f, 209.0f / 255.0f, 219.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(1.0423257724835, -0.5624623909192);
    glVertex2f(1.0430201147764, -0.5996354880988);
    glVertex2f(-1.0511492195355, -0.6025103133419);
    glVertex2f(-1.0040618180714, -0.5674476939879);
glEnd();

// Draw the dotted line (diagonal from bottom-left to top-right)
glEnable(GL_LINE_STIPPLE);
glLineStipple(1, 0x00FF);
glColor3f(1.0f, 1.0f, 1.0f); // Black color
glBegin(GL_LINE_STRIP);
    glVertex2f(-1.0055189369873, -0.5838123976263); // Top-left
    glVertex2f(1.0050540172682, -0.5842274341996);  // Bottom-right
glEnd();
glDisable(GL_LINE_STIPPLE);
glFlush();




glColor3f(88.0f / 255.0f, 147.0f / 255.0f, 203.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.7048834688229, -0.2904908334376);
    glVertex2f(-0.639995281781, -0.2912633118548);
    glVertex2f(-0.64, -0.54);
    glVertex2f(-0.70565594724, -0.5407738405992);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.7048834688229, -0.2904908334376);
    glVertex2f(-0.6245457134376, -0.2912633118548);
    glVertex2f(-0.6114135803458, -0.2348723874017);
    glVertex2f(-0.6855715083937, -0.2379623010703);
glEnd();
glFlush();

glColor3f(54.0f / 255.0f, 112.0f / 255.0f, 158.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.7365550839267, -0.5392288837649);
    glVertex2f(-0.70565594724, -0.5407738405992);
    glVertex2f(-0.7048834688229, -0.2904908334376);
    glVertex2f(-0.738100040761, -0.2889458766033);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(-0.7048834688229, -0.2904908334376);
    glVertex2f(-0.738100040761, -0.2889458766033);
    glVertex2f(-0.7543220875215, -0.2827660492659);
    glVertex2f(-0.7635918285275, -0.2395072579047);
    glVertex2f(-0.6855715083937, -0.2379623010703);
glEnd();
glFlush();



glColor3f(88.0f / 255.0f, 147.0f / 255.0f, 203.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.5192014641649, -0.5388091470784);
    glVertex2f(0.5840447371727, -0.5412023397535);
    glVertex2f(0.5805273602567, -0.2902650926403);
    glVertex2f(0.5197685464273, -0.2902650926403);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.5197685464273, -0.2902650926403);
    glVertex2f(0.5805273602567, -0.2902650926403);
    glVertex2f(0.5967297106112, -0.2870246225694);
    glVertex2f(0.6129320609657, -0.2319366313641);
    glVertex2f(0.5367810142996, -0.235177101435);
glEnd();
glFlush();

glColor3f(54.0f / 255.0f, 112.0f / 255.0f, 158.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.4834656657879, -0.2897071487693);
    glVertex2f(0.5197685464273, -0.2902650926403);
    glVertex2f(0.5192014641649, -0.5388091470784);
    glVertex2f(0.4891897196425, -0.5387978531615);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.4671109077752, -0.2813537999453);
    glVertex2f(0.4834656657879, -0.2897071487693);
    glVertex2f(0.5197685464273, -0.2902650926403);
    glVertex2f(0.5367810142996, -0.235177101435);
    glVertex2f(0.4565793800448, -0.2359872189527);
glEnd();
glFlush();

glColor3f(69.0f / 255.0f, 128.0f / 255.0f, 184.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-1.0047646657432, -0.2110509817792);
    glVertex2f(-1.1177426813574, -0.2467472100113);
    glVertex2f(1.1523840967451, -0.2496365264842);
    glVertex2f(1.1499310283231, -0.2106589078957);
glEnd();
glFlush();
    glPopMatrix();
}

void lampTower(){
    glColor3f(245.0f / 255.0f, 212.0f / 255.0f, 26.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7677558789309, 0.2529325779234);
    glVertex2f(0.7722729543287, 0.24164482977);
    glVertex2f(0.7755373148739, 0.3066253109327);
    glVertex2f(0.7683615314725, 0.291492456408);
    glVertex2f(0.7671502263893, 0.2700927332699);
glEnd();
glFlush();

glColor3f(245.0f / 255.0f, 212.0f / 255.0f, 26.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7755373148739, 0.3066253109327);
    glVertex2f(0.7792856071414, 0.3178208441699);
    glVertex2f(0.781659241027, 0.3075767400321);
    glVertex2f(0.7853975040185, 0.2919049788188);
    glVertex2f(0.7722729543287, 0.24164482977);
glEnd();
glFlush();



glColor3f(245.0f / 255.0f, 212.0f / 255.0f, 26.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7671502263893, 0.2700927332699);
    glVertex2f(0.7683615314725, 0.291492456408);
    glVertex2f(0.7638398347467, 0.261555968426);
glEnd();
glFlush();

glColor3f(124.0f / 255.0f, 118.0f / 255.0f, 60.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7638398347467, 0.261555968426);
    glVertex2f(0.7671502263893, 0.2700927332699);
    glVertex2f(0.7677558789309, 0.2529325779234);
    glVertex2f(0.7664108430674, 0.2424763803619);
    glVertex2f(0.7614041426534, 0.2496481404144);
glEnd();
glFlush();

glColor3f(245.0f / 255.0f, 212.0f / 255.0f, 26.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7677558789309, 0.2529325779234);
    glVertex2f(0.7722729543287, 0.24164482977);
    glVertex2f(0.7664108430674, 0.2424763803619);
glEnd();
glFlush();


glColor3f(233.0f / 255.0f, 195.0f / 255.0f, 10.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7853975040185, 0.2919049788188);
    glVertex2f(0.7856731867369, 0.2704017267857);
    glVertex2f(0.7815146434835, 0.2549957527972);
    glVertex2f(0.7722729543287, 0.24164482977);
glEnd();
glFlush();

glColor3f(245.0f / 255.0f, 212.0f / 255.0f, 26.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7853975040185, 0.2919049788188);
    glVertex2f(0.7856731867369, 0.2704017267857);
    glVertex2f(0.791292585766, 0.2703364956979);
glEnd();
glFlush();

glColor3f(245.0f / 255.0f, 212.0f / 255.0f, 26.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7856731867369, 0.2704017267857);
    glVertex2f(0.791292585766, 0.2703364956979);
    glVertex2f(0.7932034560937, 0.2587143276505);
    glVertex2f(0.789955866636, 0.2533016785543);
    glVertex2f(0.7815146434835, 0.2549957527972);
glEnd();
glFlush();

glColor3f(230.0f / 255.0f, 195.0f / 255.0f, 62.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7815146434835, 0.2549957527972);
    glVertex2f(0.789955866636, 0.2533016785543);
    glVertex2f(0.7940153534581, 0.2468064996389);
    glVertex2f(0.7917149775922, 0.240176004496);
    glVertex2f(0.7787246197613, 0.2370637312657);
    glVertex2f(0.7722729543287, 0.24164482977);
glEnd();
glFlush();

glColor3f(230.0f / 255.0f, 195.0f / 255.0f, 62.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7932034560937, 0.2587143276505);
    glVertex2f(0.7959097806418, 0.2527604136447);
    glVertex2f(0.7940153534581, 0.2468064996389);
    glVertex2f(0.789955866636, 0.2533016785543);
glEnd();
glFlush();


glColor3f(100.0f / 255.0f, 99.0f / 255.0f, 119.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7275547803562, 0.2312075272035);
    glVertex2f(0.7330332179781, 0.2110774540813);
    glVertex2f(0.8140631325711, 0.2089115601378);
    glVertex2f(0.8232363304496, 0.2257290895816);
    glVertex2f(0.7815146434835, 0.2549957527972);
glEnd();
glFlush();


glColor3f(213.0f / 255.0f, 211.0f / 255.0f, 192.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7224150441626, 0.2141577768867);
    glVertex2f(0.7205433529315, 0.2073020197756);
    glVertex2f(0.7820149637371, 0.2336469958351);
    glVertex2f(0.7826653199234, 0.2398974600664);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.7826653199234, 0.2398974600664);
    glVertex2f(0.7820149637371, 0.2336469958351);
    glVertex2f(0.8262065364821, 0.2039026680259);
    glVertex2f(0.8262432749202, 0.2093278498447);
glEnd();
glFlush();

glColor3f(150.0f / 255.0f, 150.0f / 255.0f, 150.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7205433529315, 0.2073020197756);
    glVertex2f(0.7307414081804, 0.1962541265893);
    glVertex2f(0.78, 0.22);
    glVertex2f(0.7820149637371, 0.2336469958351);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.7820149637371, 0.2336469958351);
    glVertex2f(0.78, 0.22);
    glVertex2f(0.8219573467951, 0.1908718196524);
    glVertex2f(0.8262065364821, 0.2039026680259);
glEnd();
glFlush();

glColor3f(105.0f / 255.0f, 105.0f / 255.0f, 105.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.7307414081804, 0.1962541265893);
    glVertex2f(0.75049678806, 0.1838298034692);
    glVertex2f(0.7772727694389, 0.2007285619801);
    glVertex2f(0.78, 0.22);
glEnd();
glFlush();

glBegin(GL_POLYGON);
    glVertex2f(0.78, 0.22);
    glVertex2f(0.7772727694389, 0.2007285619801);
    glVertex2f(0.8025750245143, 0.1837245862605);
    glVertex2f(0.8219573467951, 0.1908718196524);
glEnd();
glFlush();

glColor3f(178.0f / 255.0f, 179.0f / 255.0f, 175.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.75049678806, 0.1838298034692);
    glVertex2f(0.7772727694389, 0.2007285619801);
    glVertex2f(0.7691349045583, -0.5834534971062);
    glVertex2f(0.7196961559906, -0.5812062812623);
glEnd();
glFlush();
glColor3f(241.0f / 255.0f, 241.0f / 255.0f, 240.0f / 255.0f);

glBegin(GL_POLYGON);
    glVertex2f(0.7691349045583, -0.5834534971062);
    glVertex2f(0.818573653126, -0.5857007129502);
    glVertex2f(0.8025750245143, 0.1837245862605);
    glVertex2f(0.7772727694389, 0.2007285619801);
glEnd();
glFlush();

glColor3f(179.0f / 255.0f, 178.0f / 255.0f, 179.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.5718808531534, -0.585900848447);
    glVertex2f(0.5713617910833, -0.6142131595303);
    glVertex2f(0.9445955008777, -0.6131961739451);
    glVertex2f(0.9445955008777, -0.5882800271059);
    glVertex2f(0.7616871397828, -0.5726110007296);
glEnd();
}

void sun() {
    ///sun
     glColor3f(1.0f, 0.843f, 0.0f);
    drawCircle(-0.7f, 0.8f, 0.07f);
}

void sky(){
    glColor3f(9.0f / 255.0f, 221.0f / 255.0f, 245.0f / 255.0f);
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glColor3f(172.0f / 255.0f, 235.0f / 255.0f, 228.0f / 255.0f);

    glVertex2f(-1.0f, -0.6f);
    glVertex2f(1.0f, -0.6f);
    glEnd();
    glFlush();

        glPushMatrix();
        sun();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(planeX, 0.0F, 0.0f); // move diagonally
    airplane(); // draw the airplane
    glPopMatrix();

    glPushMatrix();
        sun();
    glPopMatrix();

}

void clouds() {
    glColor3f(1.0f, 1.0f, 1.0f); // White clouds
    drawCircle(0.60f, 0.85f, 0.03f);
    drawCircle(0.57f, 0.85f, 0.025f);
    drawCircle(0.63f, 0.85f, 0.025f);
    drawCircle(0.60f, 0.83f, 0.022f);
}

void tree() {
    glPushMatrix();

    /// Trunk
    glColor3f(0.55f, 0.27f, 0.07f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(0.15f, 0.20f);
        glVertex2f(0.17f, 0.20f);
        glVertex2f(0.17f, 0.30f);
        glVertex2f(0.15f, 0.30f);
    glEnd();

    glColor3f(0.0f, 0.60f, 0.0f); // Green
    drawCircle(0.16f, 0.36f, 0.045f);
    drawCircle(0.13f, 0.36f, 0.04f);
    drawCircle(0.14f, 0.39f, 0.035f);
    drawCircle(0.18f, 0.36f, 0.04f);
    drawCircle(0.17f, 0.39f, 0.035f);
    drawCircle(0.15f, 0.33f, 0.035f);
    drawCircle(0.17f, 0.33f, 0.035f);
    drawCircle(0.16f, 0.42f, 0.03f);

    glPopMatrix();
}

void tree2() {
    glPushMatrix();

    /// trunk
    glColor3f(0.55f, 0.27f, 0.07f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(0.15f, 0.20f);
        glVertex2f(0.17f, 0.20f);
        glVertex2f(0.17f, 0.30f);
        glVertex2f(0.15f, 0.30f);
    glEnd();

    /// leaves (using drawCircle)
    glColor3f(0.00f, 0.60f, 0.00f); // Green
    drawCircle(0.16f, 0.32f, 0.04f);  // bottom
    drawCircle(0.16f, 0.36f, 0.035f); // middle
    drawCircle(0.16f, 0.40f, 0.03f);  // top

    glPopMatrix();
}

void human3(GLfloat bodyR, GLfloat bodyG, GLfloat bodyB) {
    ///head
    glPushMatrix();
    glTranslatef(-0.02f, 0.02f, 0.00f);
    glScalef(0.90f, 0.90f, 0.00f);

    GLfloat x = 0.30f, y = 0.28f, radius = 0.01f;
    int triangleAmount = 100;
    GLfloat twicePi = 1.00f * PI;

    glColor3f(0.00f, 0.00f, 0.00f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();

    x = 0.30f; y = 0.28f; radius = 0.01f;
    triangleAmount = 100;
    twicePi = -1.00f * PI;

    glColor3f(0.70f, 0.45f, 0.24f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();

    ///body
    glBegin(GL_QUADS);
    glColor3f(bodyR, bodyG, bodyB);
        glVertex2f(0.31f, 0.273f);
        glVertex2f(0.29f, 0.273f);
        glVertex2f(0.29f, 0.25f);
        glVertex2f(0.31f, 0.25f);
    glEnd();


    ///legs
    glBegin(GL_QUADS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.29f, 0.25f);
        glVertex2f(0.29f, 0.23f);
        glVertex2f(0.296f, 0.23f);
        glVertex2f(0.30f, 0.25f);

        glVertex2f(0.30f, 0.25f);
        glVertex2f(0.304f, 0.23f);
        glVertex2f(0.31f, 0.23f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.29f, 0.248f);
        glVertex2f(0.29f, 0.232f);
        glVertex2f(0.296f, 0.232f);
        glVertex2f(0.30f, 0.25f);

        glVertex2f(0.30f, 0.25f);
        glVertex2f(0.304f, 0.232f);
        glVertex2f(0.31f, 0.232f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    glPopMatrix();
}

void human2(GLfloat bodyR, GLfloat bodyG, GLfloat bodyB) {
    ///head
    glPushMatrix();
    glTranslatef(-0.02f, 0.02f, 0.00f);
    glScalef(0.90f, 0.90f, 0.00f);

    GLfloat x = 0.30f, y = 0.28f, radius = 0.01f;
    int triangleAmount = 100;
    GLfloat twicePi = 1.00f * PI;

    glColor3f(0.00f, 0.00f, 0.00f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();

    x = 0.30f; y = 0.28f; radius = 0.01f;
    triangleAmount = 100;
    twicePi = -1.00f * PI;

    glColor3f(0.70f, 0.45f, 0.24f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();

    ///body
    glBegin(GL_QUADS);
    glColor3f(bodyR, bodyG, bodyB);
        glVertex2f(0.31f, 0.273f);
        glVertex2f(0.29f, 0.273f);
        glVertex2f(0.29f, 0.25f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    ///hand right
    glBegin(GL_QUADS);
        glColor3f(0.70f, 0.45f, 0.24f);
        glVertex2f(0.31f, 0.273f);
        glVertex2f(0.32f, 0.254f);
        glVertex2f(0.318f, 0.25f);
        glVertex2f(0.31f, 0.265f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.24f, 0.54f, 0.51f);
        glVertex2f(0.31f, 0.273f);
        glVertex2f(0.32f, 0.252f);
        glVertex2f(0.318f, 0.254f);
        glVertex2f(0.31f, 0.265f);
    glEnd();

    ///hand left
    glBegin(GL_QUADS);
        glColor3f(0.70f, 0.45f, 0.24f);
        glVertex2f(0.29f, 0.273f);
        glVertex2f(0.28f, 0.254f);
        glVertex2f(0.282f, 0.25f);
        glVertex2f(0.29f, 0.265f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.24f, 0.54f, 0.51f);
        glVertex2f(0.29f, 0.273f);
        glVertex2f(0.28f, 0.252f);
        glVertex2f(0.282f, 0.254f);
        glVertex2f(0.29f, 0.265f);
    glEnd();

    ///legs
    glBegin(GL_QUADS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.29f, 0.25f);
        glVertex2f(0.29f, 0.23f);
        glVertex2f(0.296f, 0.23f);
        glVertex2f(0.30f, 0.25f);

        glVertex2f(0.30f, 0.25f);
        glVertex2f(0.304f, 0.23f);
        glVertex2f(0.31f, 0.23f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.29f, 0.248f);
        glVertex2f(0.29f, 0.232f);
        glVertex2f(0.296f, 0.232f);
        glVertex2f(0.30f, 0.25f);

        glVertex2f(0.30f, 0.25f);
        glVertex2f(0.304f, 0.232f);
        glVertex2f(0.31f, 0.232f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    glPopMatrix();
}

void human(GLfloat bodyR, GLfloat bodyG, GLfloat bodyB) {
    ///head
    glPushMatrix();
    glTranslatef(-0.02f, 0.02f, 0.00f);
    glScalef(0.90f, 0.90f, 0.00f);

    GLfloat x = 0.30f, y = 0.28f, radius = 0.01f;
    int triangleAmount = 100;
    GLfloat twicePi = 1.00f * PI;

    glColor3f(0.00f, 0.00f, 0.00f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();

    x = 0.30f; y = 0.28f; radius = 0.01f;
    triangleAmount = 100;
    twicePi = -1.00f * PI;

    glColor3f(0.70f, 0.45f, 0.24f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();

    glPointSize(1.00f);
    glBegin(GL_POINTS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.30f - 0.004f, 0.278f);
    glEnd();

    glPointSize(1.00f);
    glBegin(GL_POINTS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.30f + 0.006f, 0.278f);
    glEnd();

    glPointSize(0.10f);
    glBegin(GL_LINES);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.298f, 0.275f);
        glVertex2f(0.304f, 0.275f);
    glEnd();

    ///body
    glBegin(GL_QUADS);
        glColor3f(bodyR, bodyG, bodyB); // Use passed-in color
        glVertex2f(0.31f, 0.273f);
        glVertex2f(0.29f, 0.273f);
        glVertex2f(0.29f, 0.25f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    glLineWidth(0.10f);
    glBegin(GL_LINES);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.30f, 0.273f);
        glVertex2f(0.30f, 0.25f);
    glEnd();

    ///hand right
    glBegin(GL_QUADS);
        glColor3f(0.70f, 0.45f, 0.24f);
        glVertex2f(0.31f, 0.273f);
        glVertex2f(0.32f, 0.254f);
        glVertex2f(0.318f, 0.25f);
        glVertex2f(0.31f, 0.265f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.24f, 0.54f, 0.51f);
        glVertex2f(0.31f, 0.273f);
        glVertex2f(0.32f, 0.252f);
        glVertex2f(0.318f, 0.254f);
        glVertex2f(0.31f, 0.265f);
    glEnd();

    ///hand left
    glBegin(GL_QUADS);
        glColor3f(0.70f, 0.45f, 0.24f);
        glVertex2f(0.29f, 0.273f);
        glVertex2f(0.28f, 0.254f);
        glVertex2f(0.282f, 0.25f);
        glVertex2f(0.29f, 0.265f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.24f, 0.54f, 0.51f);
        glVertex2f(0.29f, 0.273f);
        glVertex2f(0.28f, 0.252f);
        glVertex2f(0.282f, 0.254f);
        glVertex2f(0.29f, 0.265f);
    glEnd();

    ///legs
    glBegin(GL_QUADS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.29f, 0.25f);
        glVertex2f(0.29f, 0.23f);
        glVertex2f(0.296f, 0.23f);
        glVertex2f(0.30f, 0.25f);

        glVertex2f(0.30f, 0.25f);
        glVertex2f(0.304f, 0.23f);
        glVertex2f(0.31f, 0.23f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.00f, 0.00f, 0.00f);
        glVertex2f(0.29f, 0.248f);
        glVertex2f(0.29f, 0.232f);
        glVertex2f(0.296f, 0.232f);
        glVertex2f(0.30f, 0.25f);

        glVertex2f(0.30f, 0.25f);
        glVertex2f(0.304f, 0.232f);
        glVertex2f(0.31f, 0.232f);
        glVertex2f(0.31f, 0.25f);
    glEnd();

    glPopMatrix();
}

void sky3(){

    /**........................................ Sky Section ...........................................**/
    glColor3f(0.65f,0.84f,0.99f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.07f);
    glVertex2f(1.0f, -0.07f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    glFlush();

///Plane
    glPushMatrix();
    glTranslatef(planeX, planeY, 0.0f); // move diagonally
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f); // rotate 15 degrees around Z-axis
    airplane(); // draw the airplane
    glPopMatrix();

    glPushMatrix();
        sun();
    glPopMatrix();

///-------------------------------------
    glPushMatrix();
    glTranslatef(cloudX, 0.0f, 0.0f);
        clouds();
    glPopMatrix();

        glPushMatrix();
        clouds();
    glPopMatrix();

            glPushMatrix();
    glScalef(2.0f, 2.0f, 0.0f);
    glTranslatef(cloudX, -0.48f, 0.0f);
        clouds();
    glPopMatrix();

            glPushMatrix();
    glScalef(1.5f, 1.5f, 0.0f);
    glTranslatef(cloudX, -0.2f, 0.0f);
        clouds();
    glPopMatrix();
///----------------------------------------
        glPushMatrix();
    glTranslatef(-1.4f-cloudX, 0.0f, 0.0f);
        clouds();
    glPopMatrix();

    glPushMatrix();
    glScalef(2.0f, 2.0f, 0.0f);
    glTranslatef(-1.4f-cloudX, -0.4f, 0.0f);
        clouds();
    glPopMatrix();

    glPushMatrix();
    glScalef(2.0f, 2.0f, 0.0f);
    glTranslatef(-1.0f, -0.4f, 0.0f);
        clouds();
    glPopMatrix();


    glPushMatrix();
    glScalef(2.0f, 2.0f, 0.0f);
    glTranslatef(-0.9f-cloudX, -0.5f, 0.0f);
        clouds();
    glPopMatrix();

        glPushMatrix();
    glScalef(2.0f, 2.0f, 0.0f);
    glTranslatef(-0.7f, -0.35f, 0.0f);
        clouds();
    glPopMatrix();
    glPushMatrix();
    glScalef(2.0f, 2.0f, 0.0f);
    glTranslatef(-0.5f-cloudX, -0.35f, 0.0f);
        clouds();
    glPopMatrix();

}

void cityBuilding3(){

            /**........................................ city Building ...........................................**/
    glColor3f(140.0f / 255.0f, 180.0f / 255.0f, 255.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.9165551075862f, 0.3299784835584f);
    glVertex2f(-0.9240548496061f, -0.5525364414272f);
    glVertex2f(-0.7183019878658f, -0.5566188394776f);
    glVertex2f(-0.7020075890435f, 0.3291304696511f);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.8891644156834f, 0.3271369786236f);
    glVertex2f(-0.7597081554481f, 0.3276129207568f);
    glVertex2f(-0.7592322133149f, 0.3699717706133f);
    glVertex2f(-0.888212531417f, 0.36949582848f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(-0.6866933736163f, 0.2020009413475f);
    glVertex2f(-0.4732417088864f, 0.2718578498046f);
    glVertex2f(-0.4868249966419f, -0.5586631729629f);
    glVertex2f(-0.6944552523338f, -0.5567227032836f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(-0.4452670604313f, 0.3315723061369f);
    glVertex2f(-0.2269652712555f, 0.3315723061369f);
    glVertex2f(-0.2348729285514f, -0.5472967100592f);
    glVertex2f(-0.4458434790875f, -0.5503542542699f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(-0.4120574315271f, 0.3684974205607f);
    glVertex2f(-0.2827431560154f, 0.3694038767643f);
    glVertex2f(-0.2827431560154f, 0.3080879251785f);
    glVertex2f(-0.4120574315271f, 0.3096428818473f);
    glEnd();
    glFlush();



    glBegin(GL_POLYGON);
    glVertex2f(-0.2107971942833f, 0.268941344189f);
    glVertex2f(0.003270783055f, 0.2213706825582f);
    glVertex2f(0.0052528939563f, -0.5437241253362f);
    glVertex2f(-0.2180564353927f, -0.5595268869019f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.0284404814737f, 0.3387420996324f);
    glVertex2f(0.2418031220802f, 0.1667969127908f);
    glVertex2f(0.2331893190512f, -0.5529918150577f);
    glVertex2f(0.0316650802774f, -0.5561103804765f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.2647210540119f, 0.2702908745339f);
    glVertex2f(0.4718011715158f, 0.2204867956405f);
    glVertex2f(0.4693239829293f, -0.5551359797074f);
    glVertex2f(0.2565709254164f, -0.5572376006196f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.4972220346737f, 0.3336691273783f);
    glVertex2f(0.7150641291566f, 0.3336691273783f);
    glVertex2f(0.6910838447224f, -0.575443243912f);
    glVertex2f(0.4935659498468f, -0.5845594544448f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.5295844832327f, 0.3304091127252f);
    glVertex2f(0.6523735496478f, 0.3283961772102f);
    glVertex2f(0.6537155066578f, 0.3713388015302f);
    glVertex2f(0.5269005692127f, 0.3726807585402f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.7380007466471f, 0.2672377290805f);
    glVertex2f(0.9261938773781f, 0.2266470538248f);
    glVertex2f(0.9209675282814f, -0.5891948655964f);
    glVertex2f(0.7190061904525f, -0.5923019631014f);
    glEnd();
    glFlush();


    glBegin(GL_POLYGON);
    glVertex2f(0.92, 0.2);
    glVertex2f(0.9466197653753, 0.2014711670211);
    glVertex2f(0.9522201793967, -0.5913621304238);
    glVertex2f(0.9209675282814, -0.5891948655964);
    glEnd();
    glFlush();

    /**........................................ city Building  end ...........................................**/

    }

void seat() {
    glColor3f(0.4f, 0.26f, 0.13f); // Wood-like brown color

    // Seat base
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.6f);
    glVertex2f(0.15f, -0.6f);
    glVertex2f(0.15f, -0.625f);
    glVertex2f(-0.15f, -0.625f);
    glEnd();

    // Left leg
    glBegin(GL_QUADS);
    glVertex2f(-0.14f, -0.6f);
    glVertex2f(-0.11f, -0.6f);
    glVertex2f(-0.13f, -0.67f);
    glVertex2f(-0.14f, -0.67f);
    glEnd();

    // Right leg
    glBegin(GL_QUADS);
    glVertex2f(0.11f, -0.6f);
    glVertex2f(0.14f, -0.6f);
    glVertex2f(0.14f, -0.67f);
    glVertex2f(0.13f, -0.67f);
    glEnd();

    glFlush();
}

void lampPost() {
    // Post: tall and slim
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glBegin(GL_QUADS);
        glVertex2f(0.004f, -0.67f);
        glVertex2f(-0.004f, -0.67f);
        glVertex2f(-0.002f, -0.15f);
        glVertex2f(0.002f, -0.15f);
    glEnd();

    // Arm: single diagonal line from top of post
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(0.002f, -0.15f);   // Start of arm (near side)
        glVertex2f(-0.07f, -0.20f);   // End of arm (far left)
    glEnd();

    // Vertical line to hold the bulb
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-0.07f, -0.20f);   // Arm end
        glVertex2f(-0.07f, -0.24f);   // Drop to bulb center
    glEnd();

    // Bulb: large glowing circle
if (bulbOn) {
    glColor3f(1.0f, 1.0f, 0.6f); // Light yellow (on)
} else {
    glColor3f(0.3f, 0.3f, 0.3f); // Dim gray (off)
}
drawCircle(-0.07f, -0.25f, 0.02f); // Centered below arm

    glFlush();
}

void drawAnalogClock() {
    glPushMatrix();
    // Position at bulb location
    glTranslatef(0.1f, -0.17f, 0.0f);

    // Clock face
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.0f, 0.0f, 0.01f);

    // Clock border
    glColor3f(0.0f, 0.0f, 0.0f);

    // Hour markers (12 lines)
    for(int i = 0; i < 12; i++) {
        float angle = i * 30.0f * PI / 180.0f;
        glBegin(GL_LINES);
        glVertex2f(0.008f * cos(angle), 0.008f * sin(angle));
        glVertex2f(0.01f * cos(angle), 0.01f * sin(angle));
        glEnd();
    }

    // Hour hand (rotated clockwise)
    glPushMatrix();
    glRotatef(-hourAngle, 0.0f, 0.0f, 1.0f); // Negative for clockwise
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.005f); // Points upward before rotation
    glEnd();
    glPopMatrix();

    // Minute hand
    glPushMatrix();
    glRotatef(-minuteAngle, 0.0f, 0.0f, 1.0f); // Negative for clockwise
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.008f);
    glEnd();
    glPopMatrix();

    // Second hand (red)
    glPushMatrix();
    glRotatef(-secondAngle, 0.0f, 0.0f, 1.0f); // Negative for clockwise
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(0.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.008f);
    glEnd();
    glPopMatrix();

    // Center dot
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.001f);

    glPopMatrix();
}

void stationBuilding(){
     /// station building-----------------------------------------------------------------------------

    glColor3f(119.0f / 255.0f, 47.0f / 255.0f, 30.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1199196642857, 0.5019331343413);
    glVertex2f(0.0450066266714, 0.5888444992855);
    glVertex2f(0.2099329176284, 0.5039861587101);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.4150019141232, 0.4668382131942);
    glVertex2f(-0.4157586406903, 0.4312314298535);
    glVertex2f(0.512787416017, 0.429396654358);
    glVertex2f(0.5119743111179, 0.4659997937033);
    glEnd();
    glFlush();

    glColor3f(219.0f / 255.0f, 74.0f / 255.0f, 6.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.512787416017, 0.429396654358);
    glVertex2f(0.5121084116156, -0.0794472023838);
    glVertex2f(-0.4167520642858, -0.0840752236843);
    glVertex2f(-0.4157586406903, 0.4312314298535);
    glEnd();
    glFlush();

    glColor3f(250.0f / 255.0f, 144.0f / 255.0f, 109.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.425426289424, 0.4454566899247);
    glVertex2f(-0.4259953447947, 0.4315745820673);
    glVertex2f(0.5216945252277, 0.4292915699357);
    glVertex2f(0.5210752723615, 0.4471334857048);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(-0.4261993239678, 0.3856091003413);
    glVertex2f(-0.4263386543405, 0.3748806616431);
    glVertex2f(0.5168126598502, 0.3757702492114);
    glVertex2f(0.5170389661691, 0.3882170967534);
    glEnd();
    glFlush();

    glColor3f(197.0f / 255.0f, 64.0f / 255.0f, 5.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4147844850386, 0.37363396148);
    glVertex2f(-0.4, 0.3);
    glVertex2f(0.5, 0.3);
    glVertex2f(0.5099190709017, 0.3718071544096);
    glEnd();
    glFlush();

    glColor3f(231.0f / 255.0f, 115.0f / 255.0f, 67.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4278462903316, 0.1100893671021);
    glVertex2f(-0.4280629068604, 0.0996917737191);
    glVertex2f(0.52, 0.1);
    glVertex2f(0.5198671870009, 0.1106441089601);
    glEnd();
    glFlush();

    glColor3f(248.0f / 255.0f, 131.0f / 255.0f, 98.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.52, 0.1);
    glVertex2f(0.5323795141194, 0.0965254935459);
    glVertex2f(0.5323795141194, 0.0881332062814);
    glVertex2f(-0.4381268302261, 0.0863684502326);
    glVertex2f(-0.4376119399152, 0.0958939209846);
    glVertex2f(-0.4280629068604, 0.0996917737191);
    glEnd();
    glFlush();

    glColor3f(197.0f / 255.0f, 64.0f / 255.0f, 5.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4148522979738, 0.0842343908909);
    glVertex2f(-0.3993037976394, 0.0309663804859);
    glVertex2f(0.5074560422833, 0.0378102464295);
    glVertex2f(0.5096833274928, 0.0862536997364);
    glEnd();
    glFlush();

    glColor3f(158.0f / 255.0f, 56.0f / 255.0f, 10.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4259508648472, -0.0824915884667);
    glVertex2f(-0.426746938632, -0.1303040034738);
    glVertex2f(0.5205136127483, -0.1318347428133);
    glVertex2f(0.5121084116156, -0.0794472023838);
    glEnd();
    glFlush();

    glColor3f(227.0f / 255.0f, 105.0f / 255.0f, 57.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3409906557584, 0.084553749543);
    glVertex2f(-0.3063603069075, 0.0841414834852);
    glVertex2f(-0.3053490856378, -0.1420138865254);
    glVertex2f(-0.3418478505538, -0.1420138865254);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.400056727124, 0.0830658860983);
    glVertex2f(0.4306381767171, 0.0830658860983);
    glVertex2f(0.4324310744706, -0.1439310862507);
    glVertex2f(0.4014375331957, -0.1433112154252);
    glEnd();
    glFlush();

    glColor3f(232.0f / 255.0f, 92.0f / 255.0f, 34.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1181660055038, 0.5038429688031);
    glVertex2f(0.2125405408518, 0.502820959319);
    glVertex2f(0.2134462592793, 0.3651517583279);
    glVertex2f(-0.1169566352278, 0.3663778807702);
    glEnd();
    glFlush();



    glColor3f(224.0f / 255.0f, 94.0f / 255.0f, 36.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1169566352278, 0.3663778807702);
    glVertex2f(0.2134462592793, 0.3651517583279);
    glVertex2f(0.2152583096336, -0.1387842824691);
    glVertex2f(-0.1218296896619, -0.1381636261385);
    glEnd();
    glFlush();

    glColor3f(250.0f / 255.0f, 136.0f / 255.0f, 98.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1379777103009, 0.4813703012431);
    glVertex2f(-0.1373598112467, 0.5042325662485);
    glVertex2f(0.2255843960254, 0.502997082301);
    glVertex2f(0.2253469335681, 0.4807524021889);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glVertex2f(0.2206172238753, 0.3653001825344);
    glVertex2f(0.2207970924921, 0.3545080655236);
    glVertex2f(-0.1309041324834, 0.353740684282);
    glVertex2f(-0.1312384062372, 0.3665711609995);
    glEnd();
    glFlush();

    glColor3f(208.0f / 255.0f, 78.0f / 255.0f, 26.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1174241732871, 0.3537116192675);
    glVertex2f(-0.1122325883177, 0.3156399961582);
    glVertex2f(0.2118074746261, 0.3143859297732);
    glVertex2f(0.2123863818494, 0.3531727137297);
    glEnd();
    glFlush();


    // First draw the blue rectangle background
    glColor3f(1.0f / 255.0f, 94.0f / 255.0f, 156.0f / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.15f);
    glVertex2f(-0.15f, 0.085f);
    glVertex2f(0.24f, 0.085f);
    glVertex2f(0.24f, 0.15f);
    glEnd();

    /// Set text
glColor3f(1.0f, 1.0f, 1.0f);
drawText(-0.09f, 0.10f, "TRAIN STATION");
glFlush();

glColor3f(1.0f, 1.0f, 1.0f); // White text
drawText(0.38f, -0.98f, "i: Right Click to See Instruction Page");

glColor3f(33.0f / 255.0f, 180.0f / 255.0f, 188.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.2991569133131, 0.0800630027019);
    glVertex2f(-0.1377092825053, 0.0795553057497);
    glVertex2f(-0.1372015855531, -0.1209849903794);
    glVertex2f(-0.2971261255042, -0.1214926873317);
glEnd();


glColor3f(1.0f, 1.0f, 1.0f);

glLineWidth(1.0f);


glColor3f(33.0f / 255.0f, 180.0f / 255.0f, 188.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.069526025571, 0.0670903004951);
    glVertex2f(-0.069526025571, -0.1377330742495);
    glVertex2f(0.166161145368, -0.1363301744225);
    glVertex2f(0.1656935120923, 0.0675579337707);
glEnd();


glColor3f(33.0f / 255.0f, 180.0f / 255.0f, 188.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.2324140262409, 0.0803583438355);
    glVertex2f(0.2328846014465, -0.1201066937317);
    glVertex2f(0.3938213217469, -0.1205772689372);
    glVertex2f(0.3942918969525, 0.0789466182188);
glEnd();

glFlush();


glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3, 0.08);
    glVertex2f(-0.14, 0.08);
    glVertex2f(-0.14, -0.12);
    glVertex2f(-0.3, -0.12);
glEnd();

glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.07, 0.067);
    glVertex2f(-0.07, -0.13);
    glVertex2f(0.16, -0.13);
    glVertex2f(0.16, 0.067);
glEnd();
glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.23, 0.08);
    glVertex2f(0.23, -0.12);
    glVertex2f(0.39, -0.12);
    glVertex2f(0.39, 0.08);
glEnd();

glColor3f(228.0f / 255.0f, 106.0f / 255.0f, 60.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(0.18, 0.08);
    glVertex2f(0.21, 0.08);
    glVertex2f(0.21, -0.16);
    glVertex2f(0.18, -0.16);
glEnd();

glColor3f(228.0f / 255.0f, 106.0f / 255.0f, 60.0f / 255.0f);
glBegin(GL_POLYGON);
    glVertex2f(-0.0877609783376, -0.1609792698844);
    glVertex2f(-0.1225580099688, -0.1609792698844);
    glVertex2f(-0.1230413020748, 0.0879161646993);
    glVertex2f(-0.0906607309736, 0.0893660410173);
glEnd();


///windows1
glPushMatrix();
    glTranslatef(-0.34f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();

            glPushMatrix();
    glTranslatef(-0.28f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();

            glPushMatrix();
    glTranslatef(-0.22f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();
///2
glPushMatrix();
    glTranslatef(0.32f, 0.05f, 0.0f);

       glPushMatrix();
    glTranslatef(-0.34f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();

            glPushMatrix();
    glTranslatef(-0.28f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();

            glPushMatrix();
    glTranslatef(-0.22f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();
glPopMatrix();

///3
glPushMatrix();
    glTranslatef(0.65f, 0.0f, 0.0f);

       glPushMatrix();
    glTranslatef(-0.34f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();

            glPushMatrix();
    glTranslatef(-0.28f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();

            glPushMatrix();
    glTranslatef(-0.22f, 0.23f, 0.0f);
   glBegin(GL_QUADS);               // Each set of 4 vertices form a quad
      glColor3f(0.13f, 0.38f, 0.4f);  // Red
      glVertex2f(-0.02f, -0.06f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f( 0.02f, -0.06f);     //  so that the normal (front-face) is facing you
      glVertex2f( 0.02f, 0.06f);
      glVertex2f(-0.02f, 0.06f);
       glEnd();
    glFlush();
     glPopMatrix();
glPopMatrix();



 ///end station building



///lines
 glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);

    for (float x = -1.0f; x <= -0.4f; x += 0.1f) {
    glVertex2f(x, -0.15f);
    glVertex2f(x, -0.0f);
    }

    for (float x = 0.5f; x <= 1.0f; x += 0.1f) {
    glVertex2f(x, -0.15f);
    glVertex2f(x, -0.0f);
    }


    for (float x = -1.0f; x <= -0.4f; x += 0.1f) {
    glVertex2f(x, -0.9f);
    glVertex2f(x, -0.7f);
    }

    for (float x = 0.5f; x <= 1.0f; x += 0.1f) {
    glVertex2f(x, -0.9f);
    glVertex2f(x, -0.7f);
    }

    glEnd();


///Seats
    glPushMatrix();
    glTranslatef(-0.8f, 0.5f, 0.0f); // No actual movement, keeps seat at origin
    seat(); // Call your seat drawing function
glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8f, 0.5f, 0.0f); // No actual movement, keeps seat at origin
    seat(); // Call your seat drawing function
glPopMatrix();



///human
    glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(0.18f, -0.3f, 0.0f);
        human(1.0f, 0.0f, 0.0f); // Red body
    glPopMatrix();;

        glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(0.12f, -0.3f, 0.0f);
       human(0.0f, 0.0f, 1.0f); // Blue body
    glPopMatrix();

            glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.1f, -0.34f, 0.0f);
       human(0.0f, 1.0f, 1.0f); // Blue body
    glPopMatrix();

            glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.15f, -0.34f, 0.0f);
        human(1.0f, 1.0f, 0.0f); // Blue body
    glPopMatrix();

            glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.4f, -0.34f, 0.0f);
        human(1.0f, 0.0f, 1.0f); // Blue body
    glPopMatrix();

            glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.68f, -0.3f, 0.0f);
       human(1.0f, 1.0f, 1.0f); // Blue body
    glPopMatrix();
///human2
            glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.68f, -0.68f, 0.0f);
        human2(1.1f, 0.0f, 0.51f);
    glPopMatrix();

                glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.62f, -0.68f, 0.0f);
        human2(0.00f, 0.00f, 0.51f);
    glPopMatrix();

                    glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.3f, -0.68f, 0.0f);
        human2(0.00f, 0.70f, 0.51f);
    glPopMatrix();

            glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.25f, -0.70f, 0.0f);
        human2(0.00f, 0.70f, 0.51f);
    glPopMatrix();

                glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(0.15f, -0.68f, 0.0f);
        human2(0.60f, 0.0f, 0.5f);
    glPopMatrix();
    ///human 3
glPushMatrix();
    glTranslatef(-humanOffsetX, 0.0f, 0.0f); // Move along X
    glScalef(2.0f, 2.0f, 2.0f);
    glTranslatef(-0.1f, -0.60f, 0.0f);
    human3(0.60f, 0.0f, 0.5f);
glPopMatrix();

glPushMatrix();
    glTranslatef(humanOffsetX, 0.0f, 0.0f); // Move along X
    glScalef(2.0f, 2.0f, 2.0f);
    glTranslatef(-0.3f, -0.62f, 0.0f);
    human3(0.00f, 0.70f, 0.51f);
glPopMatrix();

glPushMatrix();
    glTranslatef(humanOffsetX, 0.0f, 0.0f); // Move along X
    glScalef(2.0f, 2.0f, 2.0f);
    glTranslatef(-0.25f, -0.63f, 0.0f);
    human3(0.00f, 0.70f, 0.51f);
glPopMatrix();




///seats 2
        glPushMatrix();
    glTranslatef(-0.8f, -0.25f, 0.0f); // No actual movement, keeps seat at origin
    seat(); // Call your seat drawing function
glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8f, -0.25, 0.0f); // No actual movement, keeps seat at origin
    seat(); // Call your seat drawing function
glPopMatrix();


    glFlush();


     ///Shade
    glColor3f(0.24f,0.36f,0.44f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.0f);
    glVertex2f(-0.45f, -0.0f);
    glVertex2f(-0.5f, 0.15f);
    glVertex2f(-1.0f, 0.15f);

    glVertex2f(1.0f, -0.0f);
    glVertex2f(0.45f, -0.0f);
    glVertex2f(0.5f, 0.15f);
    glVertex2f(1.0f, 0.15f);

    glVertex2f(-1.0f, -0.65f);
    glVertex2f(-0.45f, -0.65f);
    glVertex2f(-0.5f, -0.80f);
    glVertex2f(-1.0f, -0.80f);

    glVertex2f(1.0f, -0.65f);
    glVertex2f(0.45f, -0.65f);
    glVertex2f(0.5f, -0.80f);
    glVertex2f(1.0f, -0.80f);




    glEnd();
    glFlush();

            ///lamppost
    glPushMatrix();
        glTranslatef(0.8f, 0.46f, 0.0f); // Move lamp post 0.5 units right
        lampPost();                    // Draw the lamp post at translated position
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.4f, 0.46f, 0.0f); // Move lamp post 0.5 units right
        lampPost();                    // Draw the lamp post at translated position
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.4f, 0.46f, 0.0f); // Move lamp post 0.5 units right
        lampPost();                    // Draw the lamp post at translated position
    glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.8f, 0.46f, 0.0f); // Move lamp post 0.5 units right
        lampPost();                    // Draw the lamp post at translated position
    glPopMatrix();



        glPushMatrix();
        glTranslatef(-0.36f, 1.1f, 0.0f);  // Position at right bulb
        glScalef(4.0f, 4.0f, 1.0f);       // Slightly enlarge to fit bulb
        drawAnalogClock();
    glPopMatrix();

    glFlush();
   }



// Function to draw the water and beach
void water(){
    glColor3ub(0, 191, 255); // Water color
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, -1.0f, Z_WATER);
    glVertex3f(1.0f, -1.0f, Z_WATER);
    glVertex3f(1.0f, -0.166667f, Z_WATER);
    glVertex3f(-1.0f, -0.166667f, Z_WATER);
    glEnd();

    glColor3ub(245, 222, 179); // Beach color
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, -0.166667f, Z_BEACH);
    glVertex3f(1.0f, -0.166667f, Z_BEACH);
    glVertex3f(1.0f, 0.166667f, Z_BEACH);
    glVertex3f(-1.0f, 0.166667f, Z_BEACH);
    glEnd();
}

// Function to draw a single beach bench with hardcoded vertices (relative to origin)
void draw_single_bench() {
    glColor3ub(255, 69, 0); // Orange-red for the bench

    // Values are pre-calculated assuming x_center = 0.0f and y_base = 0.0f
    // and original dimensions:
    // half_width = 0.0375f; backrest_height = 0.066667f; seat_depth = 0.05f;
    // leg_length = 0.05f; leg_thickness = 0.0075f; tilt_factor_x = 0.0125f;

    // Backrest
    glBegin(GL_POLYGON);
    glVertex3f(-0.0375f, 0.05f, Z_BENCH);
    glVertex3f(0.0375f, 0.05f, Z_BENCH);
    glVertex3f(0.0375f, 0.116667f, Z_BENCH);
    glVertex3f(-0.0375f, 0.116667f, Z_BENCH);
    glEnd();

    // Seat
    glBegin(GL_POLYGON);
    glVertex3f(-0.0375f, 0.05f, Z_BENCH);
    glVertex3f(0.0375f, 0.05f, Z_BENCH);
    glVertex3f(0.05f, 0.0f, Z_BENCH);
    glVertex3f(-0.05f, 0.0f, Z_BENCH);
    glEnd();

    // Front Left Leg
    glBegin(GL_POLYGON);
    glVertex3f(-0.0425f, 0.0f, Z_BENCH);
    glVertex3f(-0.05f, 0.0f, Z_BENCH);
    glVertex3f(-0.05f, -0.05f, Z_BENCH);
    glVertex3f(-0.0425f, -0.05f, Z_BENCH);
    glEnd();

    // Front Right Leg
    glBegin(GL_POLYGON);
    glVertex3f(0.0425f, 0.0f, Z_BENCH);
    glVertex3f(0.05f, 0.0f, Z_BENCH);
    glVertex3f(0.05f, -0.05f, Z_BENCH);
    glVertex3f(0.0425f, -0.05f, Z_BENCH);
    glEnd();

    // Back Left Leg
    glBegin(GL_POLYGON);
    glVertex3f(-0.03f, 0.05f, Z_BENCH);
    glVertex3f(-0.0375f, 0.05f, Z_BENCH);
    glVertex3f(-0.0375f, 0.0f, Z_BENCH);
    glVertex3f(-0.03f, 0.0f, Z_BENCH);
    glEnd();

    // Back Right Leg
    glBegin(GL_POLYGON);
    glVertex3f(0.03f, 0.05f, Z_BENCH);
    glVertex3f(0.0375f, 0.05f, Z_BENCH);
    glVertex3f(0.0375f, 0.0f, Z_BENCH);
    glVertex3f(0.03f, 0.0f, Z_BENCH);
    glEnd();
}

// Function to draw the beach benches
void beach_bench(){
    float bench_y_base_position = 0.0f; // Global Y-position for the row of benches

    glMatrixMode(GL_MODELVIEW); // Ensure we are on the ModelView matrix for transformations

    // Draw first bench
    glPushMatrix(); // Save current ModelView matrix
    glTranslatef(-0.75f, bench_y_base_position, 0.0f); // Translate to position this bench
    draw_single_bench(); // Draw the bench (it's drawn relative to its local origin)
    glPopMatrix(); // Restore previous ModelView matrix

    // Draw second bench
    glPushMatrix();
    glTranslatef(-0.25f, bench_y_base_position, 0.0f);
    draw_single_bench();
    glPopMatrix();

    // Draw third bench
    glPushMatrix();
    glTranslatef(0.25f, bench_y_base_position, 0.0f);
    draw_single_bench();
    glPopMatrix();

    // Draw fourth bench
    glPushMatrix();
    glTranslatef(0.75f, bench_y_base_position, 0.0f);
    draw_single_bench();
    glPopMatrix();
}

// Function to draw a single umbrella
void draw_single_umbrella(float x_center, float y_pole_base){
    glColor3ub(0, 0, 0); // Black pole
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex3f(x_center, y_pole_base, Z_UMBRELLA);
    glVertex3f(x_center, y_pole_base + 0.2f, Z_UMBRELLA);
    glEnd();
    glLineWidth(1.0f);

    glColor3ub(0, 0, 255); // Blue canopy
    glBegin(GL_TRIANGLES);
    glVertex3f(x_center - 0.075f, y_pole_base + 0.166667f, Z_UMBRELLA);
    glVertex3f(x_center + 0.075f, y_pole_base + 0.166667f, Z_UMBRELLA);
    glVertex3f(x_center, y_pole_base + 0.266667f, Z_UMBRELLA);
    glEnd();
}

// Function to draw the umbrellas
void umbrella(){
    float umbrella_y_pole_base = 0.016667f;
    draw_single_umbrella(-0.70f, umbrella_y_pole_base);
    draw_single_umbrella(-0.20f, umbrella_y_pole_base);
    draw_single_umbrella(0.30f, umbrella_y_pole_base);
    draw_single_umbrella(0.80f, umbrella_y_pole_base);
}

// Function to draw the waves with animation
void wave(){
    glColor3ub(190, 230, 250); // Light blue for waves
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, move_wave, 0.0f);

    // Wave 1
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, -0.183333f, Z_WAVE);
    glVertex3f(-0.5f, -0.183333f, Z_WAVE);
    glVertex3f(-0.55f, -0.15f, Z_WAVE);
    glVertex3f(-0.95f, -0.15f, Z_WAVE);
    glEnd();

    // Wave 2
    glBegin(GL_POLYGON);
    glVertex3f(-0.625f, -0.2f, Z_WAVE);
    glVertex3f(-0.125f, -0.2f, Z_WAVE);
    glVertex3f(-0.175f, -0.166667f, Z_WAVE);
    glVertex3f(-0.575f, -0.166667f, Z_WAVE);
    glEnd();

    // Wave 3
    glBegin(GL_POLYGON);
    glVertex3f(-0.25f, -0.183333f, Z_WAVE);
    glVertex3f(0.25f, -0.183333f, Z_WAVE);
    glVertex3f(0.2f, -0.15f, Z_WAVE);
    glVertex3f(-0.2f, -0.15f, Z_WAVE);
    glEnd();

    // Wave 4
    glBegin(GL_POLYGON);
    glVertex3f(0.125f, -0.2f, Z_WAVE);
    glVertex3f(0.625f, -0.2f, Z_WAVE);
    glVertex3f(0.575f, -0.166667f, Z_WAVE);
    glVertex3f(0.175f, -0.166667f, Z_WAVE);
    glEnd();

    // Wave 5
    glBegin(GL_POLYGON);
    glVertex3f(0.5f, -0.183333f, Z_WAVE);
    glVertex3f(1.0f, -0.183333f, Z_WAVE);
    glVertex3f(0.95f, -0.15f, Z_WAVE);
    glVertex3f(0.55f, -0.15f, Z_WAVE);
    glEnd();

    glPopMatrix();
}

// Function to draw the sky
void sky4(){
    glColor3ub(135, 240, 250); // Light blue sky
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, 0.166667f, Z_SKY);
    glVertex3f(1.0f, 0.166667f, Z_SKY);
    glVertex3f(1.0f, 1.0f, Z_SKY);
    glVertex3f(-1.0f, 1.0f, Z_SKY);
    glEnd();
}

// Function to draw clouds with animation
void cloud(){
    float base_y_cloud1_group = 0.666667f;
    float r_x_small_scaled = 0.05f;
    float r_y_small_scaled = 0.066667f;
    float r_x_medium_scaled = 0.0625f;
    float r_y_medium_scaled = 0.083333f;
    float r_x_large_scaled = 0.055f;
    float r_y_large_scaled = 0.073333f;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(move_cloud, 0.0f, Z_CLOUD);

    glColor3ub(255, 255, 255); // White clouds

    const float PI_CONST = 3.14159265358979323846f;
    const int NUM_CIRCLE_SEGMENTS = 200;

    glBegin(GL_POLYGON);
    for(int i=0;i<NUM_CIRCLE_SEGMENTS;i++) {
        float A=(i*2*PI_CONST)/NUM_CIRCLE_SEGMENTS;
        float x = r_x_small_scaled * cos(A);
        float y = r_y_small_scaled * sin(A);
        glVertex3f(x + -0.75f, y + base_y_cloud1_group, 0.0f);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0;i<NUM_CIRCLE_SEGMENTS;i++) {
        float A=(i*2*PI_CONST)/NUM_CIRCLE_SEGMENTS;
        float x = r_x_medium_scaled * cos(A);
        float y = r_y_medium_scaled * sin(A);
        glVertex3f(x + -0.6875f, y + base_y_cloud1_group - 0.033333f, 0.0f);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0;i<NUM_CIRCLE_SEGMENTS;i++) {
        float A=(i*2*PI_CONST)/NUM_CIRCLE_SEGMENTS;
        float x = r_x_small_scaled * cos(A);
        float y = r_y_small_scaled * sin(A);
        glVertex3f(x + -0.625f, y + base_y_cloud1_group, 0.0f);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for(int i=0;i<NUM_CIRCLE_SEGMENTS;i++) {
        float A=(i*2*PI_CONST)/NUM_CIRCLE_SEGMENTS;
        float x = r_x_large_scaled * cos(A);
        float y = r_y_large_scaled * sin(A);
        glVertex3f(x + -0.6625f, y + base_y_cloud1_group + 0.05f, 0.0f);
    }
    glEnd();

    glPopMatrix();
}

// Function to draw the sun
void sun4(){
    glBegin(GL_POLYGON);
    float r_x_scaled = 0.1f;
    float r_y_scaled = 0.133333f;
    float center_x = 0.75f;
    float center_y = 0.833333f;

    const float PI_CONST = 3.14159265358979323846f;
    const int NUM_CIRCLE_SEGMENTS = 200;

    for(int i=0;i<NUM_CIRCLE_SEGMENTS;i++)
    {
        glColor3ub(255,245,0); // Yellow sun
        float A=(i*2*PI_CONST)/NUM_CIRCLE_SEGMENTS;
        float x = r_x_scaled * cos(A);
        float y = r_y_scaled * sin(A);
        glVertex3f(x + center_x, y + center_y, Z_SUN);
    }
    glEnd();
}

// Function to draw the small boat
void boat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(move_boat, boat_vertical_offset, Z_SMALL_BOAT);

    glColor3ub(139, 69, 19); // Brown boat body
    glBegin(GL_POLYGON);
    glVertex3f(-0.575f, -0.516667f, 0.0f);
    glVertex3f(-0.5f, -0.516667f, 0.0f);
    glVertex3f(-0.4625f, -0.316667f, 0.0f);
    glVertex3f(-0.6125f, -0.316667f, 0.0f);
    glEnd();

    glColor3ub(0, 0, 0); // Black mast
    glLineWidth(4.5f);
    glBegin(GL_LINES);
    glVertex3f(-0.575f, -0.316667f, 0.0f);
    glVertex3f(-0.575f, 0.083333f, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    glColor3ub(138, 43, 226); // Purple sail
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.575f, -0.291667f, 0.0f);
    glVertex3f(-0.5f, -0.291667f, 0.0f);
    glVertex3f(-0.575f, 0.058333f, 0.0f);
    glEnd();
    glPopMatrix();
}

// Function to draw the cargo ship with hardcoded NDC values
void draw_cargo_ship_with_containers(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(move_cargo_ship, 0.0f, Z_CARGO_SHIP);

    const float PI = 3.14159265358979323846f;
    const int NUM_SEGMENTS = 200;

    const float scaled_r_x_window = 0.015272726f;
    const float scaled_r_y_window = 0.011454464f;

    const float ndc_center_x1 = -0.43454546f;
    const float ndc_center_y = -0.0666702f;
    const float ndc_center_x2 = -0.39636365f;
    const float ndc_center_x3 = -0.35818183f;


    // Bottom red hull
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5f, -0.516667f, 0.0f);
    glVertex3f(0.0454545f, -0.516667f, 0.0f);
    glVertex3f(0.0454545f, -0.3939406f, 0.0f);
    glVertex3f(-0.5f, -0.3939406f, 0.0f);
    glEnd();

    // Middle white band
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5f, -0.3939406f, 0.0f);
    glVertex3f(0.0454545f, -0.3939406f, 0.0f);
    glVertex3f(0.0454545f, -0.312123f, 0.0f);
    glVertex3f(-0.5f, -0.312123f, 0.0f);
    glEnd();

    // Deck room
    glColor3ub(70,130,180);
    glBegin(GL_POLYGON);
    glVertex3f(-0.45636364f, -0.312123f, 0.0f);
    glVertex3f(-0.33636365f, -0.312123f, 0.0f);
    glVertex3f(-0.33636365f, -0.0257614f, 0.0f);
    glVertex3f(-0.45636364f, -0.0257614f, 0.0f);
    glEnd();

    // Deck room 2D
    glColor3ub(72,61,139);
    glBegin(GL_POLYGON);
    glVertex3f(-0.33636365f, -0.312123f, 0.0f);
    glVertex3f(-0.3309091f, -0.312123f, 0.0f);
    glVertex3f(-0.3309091f, -0.0257614f, 0.0f);
    glVertex3f(-0.33636365f, -0.0257614f, 0.0f);
    glEnd();

    // Deck room windows
    glColor3ub(255,228,181);
    glBegin(GL_POLYGON);
    for(int i=0;i<NUM_SEGMENTS;i++) {
        float A=(i*2*PI)/NUM_SEGMENTS;
        glVertex3f(scaled_r_x_window * cos(A) + ndc_center_x1, scaled_r_y_window * sin(A) + ndc_center_y, 0.0f);
    }
    glEnd();

    glColor3ub(255,228,181);
    glBegin(GL_POLYGON);
    for(int i=0;i<NUM_SEGMENTS;i++) {
        float A=(i*2*PI)/NUM_SEGMENTS;
        glVertex3f(scaled_r_x_window * cos(A) + ndc_center_x2, scaled_r_y_window * sin(A) + ndc_center_y, 0.0f);
    }
    glEnd();

    glColor3ub(255,228,181);
    glBegin(GL_POLYGON);
    for(int i=0;i<NUM_SEGMENTS;i++) {
        float A=(i*2*PI)/NUM_SEGMENTS;
        glVertex3f(scaled_r_x_window * cos(A) + ndc_center_x3, scaled_r_y_window * sin(A) + ndc_center_y, 0.0f);
    }
    glEnd();

    // Control room
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glVertex3f(-0.4290909f, -0.0257614f, 0.0f);
    glVertex3f(-0.33636365f, -0.0257614f, 0.0f);
    glVertex3f(-0.33636365f, 0.2196914f, 0.0f);
    glVertex3f(-0.4290909f, 0.2196914f, 0.0f);
    glEnd();

    // Control room 2D
    glColor3ub(128,128,128);
    glBegin(GL_POLYGON);
    glVertex3f(-0.33636365f, -0.0257614f, 0.0f);
    glVertex3f(-0.3309091f, -0.312123f, 0.0f); // Incorrect: should be -0.0257614f, not -0.312123f
    glVertex3f(-0.3309091f, -0.0257614f, 0.0f); // Incorrect: this line is redundant or wrong
    glVertex3f(-0.32545455f, 0.2196914f, 0.0f);
    glVertex3f(-0.3309091f, 0.2196914f, 0.0f);
    glEnd();


    // Control room left windows
    glColor3ub(0,206,209);
    glBegin(GL_POLYGON);
    glVertex3f(-0.42363637f, 0.1378738f, 0.0f);
    glVertex3f(-0.40727274f, 0.1378738f, 0.0f);
    glVertex3f(-0.40727274f, 0.21150964f, 0.0f);
    glVertex3f(-0.42363637f, 0.21150964f, 0.0f);
    glEnd();

    glColor3ub(0,206,209);
    glBegin(GL_POLYGON);
    glVertex3f(-0.40181819f, 0.1378738f, 0.0f);
    glVertex3f(-0.38545447f, 0.1378738f, 0.0f);
    glVertex3f(-0.38545447f, 0.21150964f, 0.0f);
    glVertex3f(-0.40181819f, 0.21150964f, 0.0f);
    glEnd();

    glColor3ub(0,206,209);
    glBegin(GL_POLYGON);
    glVertex3f(-0.37999998f, 0.1378738f, 0.0f);
    glVertex3f(-0.36363638f, 0.1378738f, 0.0f);
    glVertex3f(-0.36363638f, 0.21150964f, 0.0f);
    glVertex3f(-0.37999998f, 0.21150964f, 0.0f);
    glEnd();

    glColor3ub(0,206,209);
    glBegin(GL_POLYGON);
    glVertex3f(-0.35818183f, 0.1378738f, 0.0f);
    glVertex3f(-0.33875002f, 0.1378738f, 0.0f);
    glVertex3f(-0.33636365f, 0.21150964f, 0.0f);
    glVertex3f(-0.35818183f, 0.21150964f, 0.0f);
    glEnd();

    // Control room roof top
    glColor3ub(70,130,180);
    glLineWidth(12.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.439999995f, 0.2196914f, 0.0f);
    glVertex3f(-0.319999965f, 0.2196914f, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // Control room top light holder
    glColor3ub(192,192,192);
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.37454547f, 0.23196404f, 0.0f);
    glVertex3f(-0.37454547f, 0.403781f, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // Exhaustor white part
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
    glVertex3f(-0.418181825f, 0.2401458f, 0.0f);
    glVertex3f(-0.3909091f, 0.2401458f, 0.0f);
    glVertex3f(-0.3909091f, 0.3424178f, 0.0f);
    glVertex3f(-0.418181825f, 0.3424178f, 0.0f);
    glEnd();

    // Exhaustor black part
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
    glVertex3f(-0.418181825f, 0.3424178f, 0.0f);
    glVertex3f(-0.3909091f, 0.3424178f, 0.0f);
    glVertex3f(-0.3909091f, 0.3628722f, 0.0f);
    glVertex3f(-0.418181825f, 0.3833266f, 0.0f);
    glEnd();

    // Control room front glass
    glColor3ub(0,206,209);
    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.3309091f, 0.11332852f, 0.0f);
    glVertex3f(-0.32818183f, 0.18696436f, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // Deck roof top
    glColor3ub(255,255,255);
    glLineWidth(12.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.483636365f, -0.02586484f, 0.0f);
    glVertex3f(-0.319999965f, -0.02586484f, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // Deck roof top 2D
    glColor3ub(128,128,128);
    glLineWidth(12.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.320000f, -0.025758f, 0.0f);
    glVertex3f(-0.314545f, -0.025758f, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // Body to deck line1
    glColor3ub(255,255,255);
    glLineWidth(15.0f);
    glBegin(GL_LINES); // Changed to GL_LINES, was missing
    glVertex3f(-0.47818182f, -0.2303054f, 0.0f);
    glVertex3f(-0.47818182f, -0.0257614f, 0.0f);
    glEnd();
    glLineWidth(1.0f);
    // Body to deck line2
    glColor3ub(255,255,255);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.45636364f, -0.2303054f, 0.0f);
    glVertex3f(-0.45636364f, -0.0257614f, 0.0f);
    glEnd();
    glLineWidth(1.0f);

    // Upper white tail part
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5f, -0.312123f, 0.0f);
    glVertex3f(-0.33636365f, -0.312123f, 0.0f);
    glVertex3f(-0.36363638f, -0.2303054f, 0.0f);
    glVertex3f(-0.5f, -0.2303054f, 0.0f);
    glEnd();

    // Upper white front part
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glVertex3f(-0.090909125f, -0.312123f, 0.0f);
    glVertex3f(0.0454545f, -0.312123f, 0.0f);
    glVertex3f(0.09999995f, -0.1893966f, 0.0f);
    glVertex3f(-0.0636364f, -0.1893966f, 0.0f);
    glEnd();

    glPopMatrix();
}

// Function to draw the text "Cox's to Saint Martin" on the cargo ship
void draw_text_on_ship() {
    if (!cargo_ship_visible) return;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(move_cargo_ship, -0.25f, Z_SHIP_TEXT);
    glColor3ub(0, 0, 0);

    drawText(-0.49f, -0.1025f, "Cox's to Saint Martin");

    glPopMatrix();
}


// Timer function for animation
void timer(int value){
    float wave_speed = 0.00016667f * 2.0f;
    float max_wave_offset = 0.016667f;

    if (wave_direction) {
        move_wave += wave_speed;
        if (move_wave > max_wave_offset) {
            wave_direction = false;
        }
    } else {
        move_wave -= wave_speed;
        if (move_wave < -max_wave_offset) {
            wave_direction = true;
        }
    }

    float cloud_speed = 0.00125f * 2.0f;
    const float CLOUD_VISUAL_WIDTH = 0.25f;
    const float CLOUD_HALF_WIDTH = CLOUD_VISUAL_WIDTH / 2.0f;
    float cloud_reset_right = 1.0f + CLOUD_HALF_WIDTH;
    float cloud_reset_left = -1.0f - CLOUD_HALF_WIDTH;

    move_cloud += cloud_speed;
    if (move_cloud > cloud_reset_right) {
        move_cloud = cloud_reset_left;
    }

    float boat_speed = 0.00075f * 2.0f;
    const float SMALL_BOAT_VISUAL_WIDTH = 0.15f;
    const float SMALL_BOAT_HALF_WIDTH = SMALL_BOAT_VISUAL_WIDTH / 2.0f;
    float boat_reset_right = 1.0f + SMALL_BOAT_HALF_WIDTH;
    float boat_reset_left = -1.0f - SMALL_BOAT_HALF_WIDTH;

    move_boat += boat_speed;
    if (move_boat > boat_reset_right) {
        move_boat = boat_reset_left;
    }

    if (cargo_ship_visible) {
        float cargo_ship_speed = 0.005f;
        const float CARGO_SHIP_VISUAL_WIDTH = 0.6f;
        const float CARGO_SHIP_HALF_WIDTH = CARGO_SHIP_VISUAL_WIDTH / 2.0f;
        float cargo_ship_reset_right = 1.0f + CARGO_SHIP_HALF_WIDTH;
        float cargo_ship_reset_left = -1.0f - CARGO_SHIP_HALF_WIDTH;

        move_cargo_ship += cargo_ship_speed;
        if (move_cargo_ship > cargo_ship_reset_right) {
            move_cargo_ship = cargo_ship_reset_left;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

// Keyboard callback function
void keyboard4(unsigned char key, int x, int y) {

    glutPostRedisplay();
}


void update3(int value) {
    trainX += trainSpeed;

    if (trainX > 2.0f) {
        trainX = -2.0f;
    }
///plane
    planeX += 0.007f;  // move right
    planeY += 0.001f; // move up

    if (planeX > 3.0f) { // reset after going off-screen
        planeX = -1.5f;
        planeY = -0.4f;  // reset height
    }
///cloud
cloudX -= 0.0005f; // move left

if (cloudX < -1.5f) {
    cloudX = 1.2f; // reset to right side after going off-screen
}

///Clock
    secondAngle += 0.1f * clockSpeed;
    minuteAngle += 0.0017f * clockSpeed;
    hourAngle += 0.00014f * clockSpeed;

    // Normalize angles
    if (secondAngle >= 360.0f) secondAngle -= 360.0f;
    if (minuteAngle >= 360.0f) minuteAngle -= 360.0f;
    if (hourAngle >= 360.0f) hourAngle -= 360.0f;

     humanOffsetX += 0.001f; // Adjust speed as needed

    if (humanOffsetX > 1.5f) { // Reset or limit
        humanOffsetX = -1.0f;
    }


    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, update3, 0); // Call again after 16ms (~60 FPS)


}

void trainStation(){

    glColor3f(0.5f,0.24f,0.16f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.07f);
    glVertex2f(1.0f, -0.07f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    glFlush();

    glColor3f(0.94f,0.8f,0.65f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.07f);
    glVertex2f(1.0f, -0.07f);
    glVertex2f(1.0f, -0.25f);
    glVertex2f(-1.0f, -0.25f);
    glEnd();
    glFlush();

    glColor3f(0.94f,0.8f,0.65f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.7f);
    glVertex2f(1.0f, -0.7f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    glFlush();


    /**........................................ Train Lines ...........................................**/
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.65f);
    glVertex2f(1.0f, -0.65f);
    glVertex2f(-1.0f, -0.6f);
    glVertex2f(1.0f, -0.6f);

    glVertex2f(-1.0f, -0.45f);
    glVertex2f(1.0f, -0.45f);
    glVertex2f(-1.0f, -0.4f);
    glVertex2f(1.0f, -0.4f);


    for (float x = -1.0f; x <= 1.0f; x += 0.05f) {
    glVertex2f(x, -0.46f);
    glVertex2f(x+0.05f, -0.39f);
    }
    for (float x = -1.0f; x <= 1.0f; x += 0.05f) {
    glVertex2f(x, -0.66f);
    glVertex2f(x+0.05f, -0.59f);
    }

    glEnd();
    glFlush();

    glPushMatrix();
    glTranslatef(trainX, -0.22f, 0.0f);
    train();
    glPopMatrix();

    glPushMatrix();
  // Move to correct position
    glTranslatef(-trainX, -0.42f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);       // Mirror over X-axis (Y coordinate flipped)
    train();                          // Draw train
    glPopMatrix();


    glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(0.2f, -0.25f, 0.0f);
        tree();
    glPopMatrix();

    glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-0.66f, -0.25f, 0.0f);
        tree();
    glPopMatrix();

        glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(0.33f, -0.25f, 0.0f);
        tree2();
    glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.6f, -0.3f, 0.0f);
        tree2();
    glPopMatrix();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:  // Increase speed
            speed1 += 0.002f;
            break;
        case GLUT_KEY_LEFT:   // Decrease speed
            speed1 -= 0.002f;
            if (speed1 < 0.0f) speed1 = 0.0f;  // Prevent going backward
            break;

            case GLUT_KEY_UP:
            trainSpeed += 0.002f; // Increase speed
            break;
        case GLUT_KEY_DOWN:
            if (trainSpeed > 0.002f)
                trainSpeed -= 0.002f; // Decrease speed but prevent negative
            break;
    }
}


void drawIntroScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f); // Black text

    // University and Course Info
    renderBitmapString(-0.55f, 0.9f, GLUT_BITMAP_HELVETICA_18, "AMERICAN INTERNATIONAL UNIVERSITY- BANGLADESH (AIUB)");
    renderBitmapString(-0.35f, 0.83f, GLUT_BITMAP_HELVETICA_18, "COMPUTER GRAPHICS PROJECT");
    renderBitmapString(-0.3f, 0.76f, GLUT_BITMAP_HELVETICA_18, "SEC: C  |  GROUP: 6");

    // Project Title and Teacher
    renderBitmapString(-0.45f, 0.66f, GLUT_BITMAP_HELVETICA_18, "TITLE: TRAIN JOURNEY: FROM HOME TO HORIZON");
    renderBitmapString(-0.42f, 0.59f, GLUT_BITMAP_HELVETICA_18, "SUBMITTED TO: MAHFUJUR RAHMAN");

    // Submitted By Heading
    renderBitmapString(-0.35f, 0.48f, GLUT_BITMAP_HELVETICA_18, "SUBMITTED BY:");

    // Table headers
    renderBitmapString(-0.7f, 0.42f, GLUT_BITMAP_HELVETICA_18, "SL          NAME                               ID                             WINDOW");

    // Student list
    renderBitmapString(-0.7f, 0.36f, GLUT_BITMAP_HELVETICA_18, "1.      MD. ABIDUL ISLAM             22-47875-2              BRIDGE CROSSING VIEW");
    renderBitmapString(-0.7f, 0.30f, GLUT_BITMAP_HELVETICA_18, "2.      AHSANUL HAQUE JOAR     22-47183-1              CITY VIEW");
    renderBitmapString(-0.7f, 0.24f, GLUT_BITMAP_HELVETICA_18, "3.      MD. SAKIB SARWAR          22-46625-1              STATION VIEW");
    renderBitmapString(-0.7f, 0.18f, GLUT_BITMAP_HELVETICA_18, "4.      TAUSHIF SHARIAR             22-46405-1              PASSENGER ON STATION VIEW");
    renderBitmapString(-0.7f, 0.12f, GLUT_BITMAP_HELVETICA_18, "5.      MD. AFIQUL ISLAM            22-47874-2              SEA BEACH VIEW");

    // Submission date
    renderBitmapString(-0.35f, -0.05f, GLUT_BITMAP_HELVETICA_18, "DATE OF SUBMISSION: 25 JUNE, 2025");

    // Prompt
    renderBitmapString(-0.25f, -0.25f, GLUT_BITMAP_HELVETICA_18, "PRESS 9 FOR INSTRUCTION WINDOW");

    glutSwapBuffers();
}

void drawInstructionScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f); // Black color

    // Title
    renderBitmapString(-0.2f, 0.8f, GLUT_BITMAP_HELVETICA_18, "INSTRUCTIONS");

    // Member Screens
    renderBitmapString(-0.7f, 0.6f, GLUT_BITMAP_HELVETICA_18, "PRESS KEY 1: BRIDGE CROSSING VIEW - MD. ABIDUL ISLAM");
    renderBitmapString(-0.7f, 0.5f, GLUT_BITMAP_HELVETICA_18, "PRESS KEY 2: CITY VIEW - AHSANUL HAQUE JOAR");
    renderBitmapString(-0.7f, 0.4f, GLUT_BITMAP_HELVETICA_18, "PRESS KEY 3: STATION VIEW - MD. SAKIB SARWAR");
    renderBitmapString(-0.7f, 0.3f, GLUT_BITMAP_HELVETICA_18, "PRESS KEY 4: PASSENGER ON STATION VIEW - TAUSHIF SHARIAR");
    renderBitmapString(-0.7f, 0.2f, GLUT_BITMAP_HELVETICA_18, "PRESS KEY 5: SEA BEACH VIEW - MD. AFIQUL ISLAM");

    // Navigation
    renderBitmapString(-0.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "PRESS KEY 9: INSTRUCTION WINDOW");
    renderBitmapString(-0.7f, -0.2f, GLUT_BITMAP_HELVETICA_18, "PRESS '0' TO GO BACK TO INTRO SCREEN");

    glutSwapBuffers();
}

void drawVillageView() {
    glClear(GL_COLOR_BUFFER_BIT);
    // TODO: Draw member 1's Village View animation
    renderBitmapString(-0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Village View (Member 1)");
    glutSwapBuffers();
}

void drawCityView() {
 glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    showInstructionScreen();
    if (showInstructions) {
        showInstructionScreen();  // Show instructions
    } else {


sky();

    if (trigger == 1) {
        if (toggle == 0) {
            afterNoonView();        // Call tr()
        } else {
            sky();       // Call tr2()
        }
    }

cityBuilding();

glPushMatrix();
    glTranslatef(trainX, 0.005f, 0.0f);  // Move bus based on busX
train();
glPopMatrix();

drawClouds();


glPushMatrix();
    glTranslatef(busX, 0.05f, 0.0f);  // Move bus based on busX
    bus();
glPopMatrix();


glPushMatrix();
glTranslatef(-busX, 0.0f, 0.0f);     // Move bus along X-axis
glScalef(-1.0f, 1.0f, 1.0f);        // Mirror on X-axis (flip vertically)
bus();                              // Draw the bus
glPopMatrix();

glPushMatrix();
glTranslatef(-busX1, 0.0f, 0.0f);
glScalef(-1.0f, 1.0f, 1.0f);      // Move bus along X-axis
blackBus();
glPopMatrix();

drawTree(0.3704561865567f, -0.635);
drawTree(-0.7261164791055, -0.635);



glPushMatrix();
glTranslatef(0.0f, -0.01f,0.0f);     // Move bus along X-axis
lampTower();                              // Draw the bus
glPopMatrix();



//water
glColor3f(16.0f / 255.0f, 118.0f / 255.0f, 171.0f / 255.0f);
glBegin(GL_POLYGON);
glVertex2f(-1.0775004767049, -0.6469033496693);
glVertex2f(-1.1959550986862, -1.1282827709127);
glColor3f(28.0f / 255.0f, 46.0f / 255.0f, 72.0f / 255.0f);
glVertex2f(0.8631390749045, -1.2895826816958);
glVertex2f(1.2789904073922, -0.6368221052454);
glEnd();
drawSeaWithFullWaves();
    }
glFlush();
glutSwapBuffers();

}

void drawStationView() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (showInstructions) {
        showInstructionScreen3();
    } else {
    sky3();

    cityBuilding3();

    trainStation();

    stationBuilding();
    }
    glutSwapBuffers();
}

void drawPassengerView() {
    display5();
}

void drawSeaBeachView() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sky4();
    sun4();
    cloud();
    water();
    wave();

    if (cargo_ship_visible) {
        draw_cargo_ship_with_containers();
        draw_text_on_ship();
    }
    boat();

    beach_bench();
    umbrella();

    glutSwapBuffers();
}



void display() {
    switch (screen_id) {
        case 0: drawIntroScreen(); break;
        case 9: drawInstructionScreen(); break;
        case 1: drawVillageView(); break;
        case 2: drawCityView(); break;
        case 3: drawStationView(); break;
        case 4: drawPassengerView(); break;
        case 5: drawSeaBeachView(); break;
    }
}

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        // Screen switching
        case '0':
            screen_id = 0;
            break;
        case '9':
            screen_id = 9;
            break;
        case '1':
            screen_id = 1;
            break;
        case '2':
            screen_id = 2;
            break;
        case '3':
            screen_id = 3;
            break;
        case '4':
            screen_id = 4;
            break;
        case '5':
            screen_id = 5;
            break;

        // Speed control
        case 'w': case 'W':
            speed += 0.002f;
            break;
        case 'q': case 'Q':
            speed -= 0.002f;
            if (speed < 0.0f) speed = 0.0f;
            break;

        // Sound control
case 's': case 'S':
    if (screen_id == 2) { // Only allow sound toggle on City View
        if (!isSoundOn) {
            PlaySound("train_V3.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            isSoundOn = true;
        } else {
            PlaySound(NULL, 0, 0); // Stop the sound
            isSoundOn = false;
        }
    }
    break;


        // Sound: alternate toggle with 'm'
        case 'm': case 'M':
            if (screen_id == 3) {
            if (!isSoundOn) {
                isSoundOn = true;
                PlaySound("train.wav", NULL, SND_ASYNC | SND_LOOP);
            } else {
                isSoundOn = false;
                PlaySound(NULL, 0, 0);
            }
            }
            break;

        // Train horn
        case 'h': case 'H':
            PlaySound(TEXT("horn.wav"), NULL, SND_FILENAME | SND_ASYNC);
            break;

        // Toggle instruction window using ENTER key
        case 13:
            if (screen_id == 0) {
                screen_id = 9;  // From Intro screen, ENTER brings to Instruction
            } else {
                showInstructions = !showInstructions;
            }
            glutPostRedisplay();
            return;

        // Cargo ship
        case 'c': case 'C':
            if (!cargo_ship_visible) {
                cargo_ship_visible = true;
                move_cargo_ship = -1.2f;
                std::cout << "Cargo ship made visible and started from left." << std::endl;
            } else {
                std::cout << "Cargo ship is already visible." << std::endl;
            }
            break;

        // Clock speed adjustments
        case 'T':
            clockSpeed += 5.0f;
            if (clockSpeed > 100.0f) clockSpeed = 100.0f;
            break;
        case 't':
            clockSpeed -= 5.0f;
            if (clockSpeed < 5.0f) clockSpeed = 5.0f;
            break;

        // Escape key
        case 27:
            std::cout << "Escape key pressed: Exiting application." << std::endl;
            exit(0);
            break;

        default:
            if (screen_id == 0) {
                screen_id = 9;  // Any other key from intro goes to instruction screen
            }
            break;
    }

    glutPostRedisplay();
}



void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 2D view
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(250, 40);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("TRAIN JOURNEY: FROM HOME TO HORIZON");
               // Set window position

    init();
        glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);

    glutMouseFunc(handleMouse);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, update, 0);  // Start animation
    glutTimerFunc(16, update3, 0);  // Start animation
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, timer5, 0);
    initializePeople();
    glutMainLoop();
    return 0;
}






