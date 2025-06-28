#include <windows.h>
#include <GL/glut.h>
#include<math.h>
#define PI 3.14159265358979323846

GLfloat i = 0.0f;
GLfloat trainX = -2.0f;
GLfloat planeX = -2.0f;
GLfloat planeY = -0.5f;
GLfloat cloudX = 0.0f;
GLfloat trainSpeed = 0.008f;  // Default speed
float humanOffsetX = 0.0f;


GLfloat hourAngle = 0.0f;
GLfloat minuteAngle = 0.0f;
GLfloat secondAngle = 0.0f;
GLfloat clockSpeed = 5.0f; //
bool bulbOn = false;
bool showInstructions = true;
bool isSoundOn = false;


void drawText(GLfloat x, GLfloat y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void showInstructionScreen() {
    glColor3f(0.0f, 0.0f, 0.0f); // Black text

    // Title block
    drawText(-0.2f, 0.65f, "JOURNEY TO COX BAZAR");
    drawText(-0.2f, 0.58f, "WINDOW: 3");
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

void handleKeyboard(unsigned char key, int x, int y) {
    if (key == 'T') {
        clockSpeed += 5.0f;
        if (clockSpeed > 100.0f) clockSpeed = 100.0f; // optional max
    }
    else if (key == 't') {
        clockSpeed -= 5.0f;
        if (clockSpeed < 5.0f) clockSpeed = 5.0f; // optional min
    }
        if (key == 13) { // ENTER key
        showInstructions = false;
        glutPostRedisplay();
    }
     if (key == 'M' || key == 'm') {
        if (!isSoundOn) {
            isSoundOn = true;
            PlaySound("train.wav", NULL, SND_ASYNC | SND_LOOP);
        } else {
            isSoundOn = false;
            PlaySound(NULL, 0, 0); // Stop sound
        }
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            trainSpeed += 0.002f; // Increase speed
            break;
        case GLUT_KEY_DOWN:
            if (trainSpeed > 0.002f)
                trainSpeed -= 0.002f; // Decrease speed but prevent negative
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bulbOn = !bulbOn;
        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        showInstructions = true;
        glutPostRedisplay();
    }
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

void drawCircle(float x, float y, float radius) {
    int segments = 50;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void sun() {
    ///sun
     glColor3f(1.0f, 0.843f, 0.0f);
    drawCircle(-0.7f, 0.8f, 0.07f);
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

void sky(){

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

void cityBuilding(){

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

void train() {
    glPushMatrix();
        // --- Wheels ---
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


    glPopMatrix();
}

void update(int value) {
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
    glutTimerFunc(16, update, 0); // Call again after 16ms (~60 FPS)


}

void trainStation(){

    /**........................................ Train Section ...........................................**/

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

        /**........................................ Station Building ...........................................**/



        /**........................................ Station Building ...........................................**/


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

void display(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (showInstructions) {
        showInstructionScreen();
    } else {
    sky();

    cityBuilding();

    trainStation();

    stationBuilding();
    }
        glutSwapBuffers();

}


int main(int argc, char** argv){
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // <-- Fix: enable double buffering
    glutInitWindowSize(1080, 720);              // Set window size
    glutInitWindowPosition(300, 50);            // Set window position
    glutCreateWindow("Train Station");               // Create window

    glutDisplayFunc(display);                   // Register display callback
    glutTimerFunc(16, update, 0);                // Start animation timer
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);

   // sound();
    glutMainLoop();
    return 0;
}
