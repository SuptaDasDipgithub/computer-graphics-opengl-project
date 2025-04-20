#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include<stdio.h>

float cloud=0;

float carX=0;
float carY=100;
int mode;

void init(void)
{

    scanf("%d",&mode);

    if(mode==1){
        glClearColor(0.662, 0.933, 0.992, 0.0);
    }
    else{
        glColor3f(0.1f, 0.3f, 0.1f);

    }


    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000.0, 0.0, 800.0);
}


void updateCloud(int value) {
    cloud += 1;

    if (cloud > 1100)
        cloud = -100;

    glutPostRedisplay();
    glutTimerFunc(16, updateCloud, 0); //16ms e update hobe
}
void drawStars() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
        glVertex2f(rand() % 1000, rand() % 808); // Random position
    }
    glEnd();
}

void drawMoon() {
    float x = 800, y = 700, r = 40;
    int triangleAmount = 40;

    glColor3f(1.0f, 1.0f, 0.8f); // Pale yellow
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (r * cos(i * 2.0f * M_PI / triangleAmount)),
            y + (r * sin(i * 2.0f * M_PI / triangleAmount))
        );
    }
    glEnd();
}


void update(int value) {
    carX += 1.0f; // Speed
    if (carX > 1000) carX = -100;
    glutPostRedisplay(); // Redraw
    glutTimerFunc(16, update, 0); // ~60 FPS
}


void drawCar(float x, float y) {
    // Car Body
    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 80, y);
        glVertex2f(x + 80, y + 20);
        glVertex2f(x + 60, y + 35);
        glVertex2f(x + 20, y + 35);
        glVertex2f(x, y + 20);
    glEnd();

    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    float radius = 10;
    for (int i = 0; i <= 360; i += 10) {
        float theta = i * M_PI / 180.0f;
        float cx = cos(theta) * radius;
        float cy = sin(theta) * radius;

        // Front Wheel
        glBegin(GL_POLYGON);
        for (int j = 0; j <= 360; j += 10) {
            theta = j * M_PI / 180.0f;
            glVertex2f(x + 20 + cos(theta) * radius, y - 5 + sin(theta) * radius);
        }
        glEnd();

        // Rear Wheel
        glBegin(GL_POLYGON);
        for (int j = 0; j <= 360; j += 10) {
            theta = j * M_PI / 180.0f;
            glVertex2f(x + 60 + cos(theta) * radius, y - 5 + sin(theta) * radius);
        }
        glEnd();
    }
}


void drawTree(float x, float y, float radius) {

    glColor3f(0.2f, 0.6f, 0.4f); // Green
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0f * M_PI * i / 100;
            glVertex2f((x) + cos(angle) * radius, (y) + sin(angle) * radius);
        }

    glEnd();

    glColor3f(0.407f, 0.619f, 0.145f); // Green
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center
        for (int i = 0; i <= 100; i++) {
            float angle = 1.0f * M_PI * i / 100;
            glVertex2f((x) + cos(angle) * radius, (y) + sin(angle) * radius);
        }

    glEnd();



    glColor3f(0.1f, 0.1f, 0.1f); // Dark gray
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x, y - radius);       // Bottom of canopy
        glVertex2f(x, y - radius - 50);  // Trunk height
    glEnd();


    float branchY = y - radius + 10;
    for (int i = 0; i < 3; i++) {
        float yOffset = i * 10.0f;
        float width = 20.0f - i * 4.0f;
        glBegin(GL_LINE_STRIP);
            glVertex2f(x - width / 2, branchY - yOffset+10);
            glVertex2f(x, branchY - yOffset - 5 +10);
            glVertex2f(x + width / 2, branchY - yOffset +10);
        glEnd();
    }
}




void drawClockFace(int centerX, int centerY) {

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int angle = 0; angle < 360; angle += 10) {
        float x = 0.025f * cos(angle * M_PI / 180);
        float y = 0.045f * sin(angle * M_PI / 180);
        glVertex2i(x * 400 + centerX, y * 300 + centerY);
    }
    glEnd();

    // --- Inner light gray background ---
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_LINES);
    for (int angle = 0; angle < 360; angle += 10) {
        float x = 0.02f * cos(angle * M_PI / 180);
        float y = 0.02f * sin(angle * M_PI / 180);
        glVertex2i(x * 300 + centerX, y * 300 + centerY);
    }
    glEnd();


    glLineWidth(3.0);
    glColor3f(0.3, 0.0, 0.3);

    glBegin(GL_LINES);
    // ghontar kata
    glVertex2i(centerX, centerY);
    glVertex2i(centerX + 0, centerY + 10);

    //miniute kata
    glVertex2i(centerX, centerY);
    glVertex2i(centerX + 5, centerY - 7);
    glEnd();
}


void drawWindowFrame(int centerX, int centerY) {

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int angle = 0; angle <= 180; angle += 10) {
        float x = 0.03f * cos(angle * M_PI / 180);
        float y = 0.05f * sin(angle * M_PI / 180);
        glVertex2i(x * 400 + centerX, y * 300 + centerY);
    }
    glVertex2i(centerX - 12, centerY - 40);
    glVertex2i(centerX + 12, centerY - 40);
    glEnd();

    glColor3f(0.0, 0.5, 1.0); //glass
    glBegin(GL_POLYGON);
    for (int angle = 0; angle <= 180; angle += 10) {
        float x = 0.02f * cos(angle * M_PI / 180);
        float y = 0.033f * sin(angle * M_PI / 180);
        glVertex2i(x * 400 + centerX, y * 300 + centerY);
    }
    glVertex2i(centerX - 8, centerY - 35);
    glVertex2i(centerX + 8, centerY - 35);
    glEnd();


    glColor3f(0.2, 0.2, 0.4);
    glBegin(GL_POLYGON);
    for (int angle = 180; angle >= 90; angle -= 10) {
        float x = 0.02f * cos(angle * M_PI / 180);
        float y = 0.033f * sin(angle * M_PI / 180);
        glVertex2i(x * 400 + centerX, y * 300 + centerY);
    }
    glVertex2i(centerX, centerY);
    glEnd();


    glColor3f(0.7, 0.7, 0.7);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    // Vertical rod
    glVertex2i(centerX, centerY + 10);
    glVertex2i(centerX, centerY - 35);


    glVertex2i(centerX - 8, centerY - 10);
    glVertex2i(centerX + 8, centerY - 10);

    // Horizontal rod
    glVertex2i(centerX - 8, centerY - 25);
    glVertex2i(centerX + 8, centerY - 25);
    glEnd();
}

void drawDoorFrame(int centerX, int centerY) {
    // white frame
    glColor3f(0.945, 0.698, 0.760);
    glBegin(GL_POLYGON);
    for (int angle = 0; angle <= 180; angle += 10) {
        float x = 0.03f * cos(angle * M_PI / 180);
        float y = 0.05f * sin(angle * M_PI / 180);
        glVertex2i(x * 400 + centerX, y * 300 + centerY);
    }
    glVertex2i(centerX - 12, centerY - 40);
    glVertex2i(centerX + 12, centerY - 40);
    glEnd();

    // glass area
    glColor3f(0.584, 0.835, 0.894);
    glBegin(GL_POLYGON);
    for (int angle = 0; angle <= 180; angle += 10) {
        float x = 0.02f * cos(angle * M_PI / 180);
        float y = 0.033f * sin(angle * M_PI / 180);
        glVertex2i(x * 400 + centerX, y * 300 + centerY);
    }
    glVertex2i(centerX - 8, centerY - 25);
    glVertex2i(centerX + 8, centerY - 25);
    glEnd();

    // steel rods
    glColor3f(0.7, 0.7, 0.7);
    glLineWidth(2.0);

    glBegin(GL_LINES);
    // lombo rod
    glVertex2i(centerX, centerY + 10);
    glVertex2i(centerX, centerY - 25);

    // prostho rod - upper
    glVertex2i(centerX - 8, centerY - 5);
    glVertex2i(centerX + 8, centerY - 5);

    // prostho rod
    glVertex2i(centerX - 8, centerY - 15);
    glVertex2i(centerX + 8, centerY - 15);
    glEnd();
}

void drawCircle(int centerX, int centerY, float radiusX, float radiusY,float r, float g, float b) {

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int angle = 0; angle < 360; angle += 5) {
        float rad = angle * M_PI / 180.0;
        float x = radiusX * cos(rad);
        float y = radiusY * sin(rad);
        glVertex2i(centerX + (int)(x), centerY + (int)(y));
    }
    glEnd();
}


void drawCircleGlass(int centerX, int centerY, float radiusX, float radiusY,float r1, float g1, float b1,float r2, float g2, float b2) {
    glColor3f(r1, g1, b1);
    glBegin(GL_POLYGON);
    for (int angle = 0; angle < 360; angle += 5) {
        float rad = angle * M_PI / 180.0;
        float x = (radiusX+1) * cos(rad);
        float y = radiusY * sin(rad);
        glVertex2i(centerX + (int)(x), centerY + (int)(y));
    }
    glEnd();

    glColor3f(r2, g2, b2);
     glBegin(GL_POLYGON);
    for (int angle = 0; angle < 360; angle += 5) {
        float rad = angle * M_PI / 180.0;
        float x = (radiusX) * cos(rad)-0.11;
        float y = (radiusY) * sin(rad);
        glVertex2i(centerX  + (int)(x+2.2), centerY  + (int)(y));
    }
    glEnd();
}

void drawCloud(int x, int y) {
    // White color for cloud
    float r = 1.0f, g = 1.0f, b = 1.0f;

    // Cloud puff circles
    drawCircle(x, y, 20, 20, r, g, b);           // Center
    drawCircle(x - 25, y - 5, 15, 15, r, g, b);   // Left
    drawCircle(x + 25, y - 5, 15, 15, r, g, b);   // Right
    drawCircle(x - 12, y + 10, 15, 15, r, g, b);  // Top-left
    drawCircle(x + 12, y + 10, 15, 15, r, g, b);  // Top-right

    // Flat bottom rectangle
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
        glVertex2i(x - 35, y - 10);
        glVertex2i(x + 35, y - 10);
        glVertex2i(x + 35, y);
        glVertex2i(x - 35, y);
    glEnd();
}






void drawShapes(void)
{
    glClear(GL_COLOR_BUFFER_BIT);	// Clear display window

    //Set color to black

    glColor3f(0.0, 0.0, 0.0);
    //Adjust the point size
    glPointSize(10.0);
if(mode==1){
  drawCloud(cloud,700);
drawCloud(cloud+200,650);
drawCloud(cloud-50,600);
drawCloud(cloud+300,774);
drawCloud(cloud-300,687);
  drawCircle(500,720,31,42,1.0,1.0,1.0);
  drawCircle(500,720,18,27,0.988,0.690,0.250);
}
else{
    drawMoon();
    drawStars();
}





//rasta
glColor3f(0.365, 0.365, 0.365);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1000, 0);
    glVertex2i(1000, 150);
    glVertex2i(0, 150);
    glEnd();
//prothom barir main block
glColor3f(0.851, 0.698, 0.463);
    glBegin(GL_QUADS);
    glVertex2i(50,150);
    glVertex2i(150, 150);
    glVertex2i(150, 300);
    glVertex2i(50, 300);
    glEnd();

//prothom barir dokan er block
glColor3f(0.949, 0.800, 0.553);
    glBegin(GL_QUADS);
    glVertex2i(150,150);
    glVertex2i(250, 150);
    glVertex2i(250, 300);
    glVertex2i(150, 300);
    glEnd();
//cile kotha
glColor3f(0.772, 0.623, 0.376);
    glBegin(GL_TRIANGLES);
    glVertex2i(50,300);
    glVertex2i(152, 300);
    glVertex2i(100, 380);
    glEnd();

//nicher block
glColor3f(0.866, 0.811, 0.682);
    glBegin(GL_QUADS);
    glVertex2i(50,150);
    glVertex2i(50, 170);
    glVertex2i(150, 170);
    glVertex2i(150, 150);
    glEnd();

glColor3f(0.937, 0.894, 0.760);
    glBegin(GL_QUADS);
    glVertex2i(150,150);
    glVertex2i(150, 170);
    glVertex2i(250, 170);
    glVertex2i(250, 150);
    glEnd();

    //left cow chal
glColor3f(0.459, 0.216, 0.235);
    glBegin(GL_QUADS);
    glVertex2i(50,300);
    glVertex2i(102, 380);
    glVertex2i(100, 390);
    glVertex2i(42, 300);
    glEnd();

    //right cowcal
glColor3f(0.459, 0.216, 0.235);
    glBegin(GL_QUADS);
    glVertex2i(152,300);
    glVertex2i(158,300);
    glVertex2i(100, 390);
    glVertex2i(100, 380);
    glEnd();

glColor3f(0.894, 0.392, 0.467);
    glBegin(GL_QUADS);
    glVertex2i(158,300);
    glVertex2i(250,300);
    glVertex2i(190, 390);
    glVertex2i(100, 390);
    glEnd();
 glColor3f(0.459, 0.216, 0.235);
    glBegin(GL_QUADS);
    glVertex2i(75,340);
    glVertex2i(126,340);
    glVertex2i(122, 350);
    glVertex2i(81, 350);
    glEnd();








//barir chal
glColor3f(0.871, 0.647, 0.714);
    glBegin(GL_POLYGON);
    glVertex2i(280,400);
    glVertex2i(370,400);
    glVertex2i(370,500);
    glVertex2i(325,580);
    glVertex2i(280,500);
glEnd();

glColor3f(0.772, 0.623, 0.376);
    glBegin(GL_TRIANGLES);
    glVertex2i(50,300);
    glVertex2i(150,220);
    glVertex2i(150,300);
glEnd();
glColor3f(0.878, 0.717, 0.470);
    glBegin(GL_TRIANGLES);
    glVertex2i(150,300);
    glVertex2i(150,220);
    glVertex2i(250,300);
glEnd();

//2nd house side chow chala 4th floor
glColor3f(0.922, 0.776, 0.812);
    glBegin(GL_QUADS);
    glVertex2i(370,500);
    glVertex2i(380,500);
    glVertex2i(332, 579);
    glVertex2i(322, 579);
    glEnd();

//2nd house side bar 4th floor
glColor3f(0.922, 0.776, 0.812);

    glBegin(GL_QUADS);
    glVertex2i(370, 400);
    glVertex2i(380,400);
    glVertex2i(380, 500);
    glVertex2i(370, 500);
    glEnd();

//2nd house side 4th floor
glColor3f(0.922, 0.776, 0.812);
    glBegin(GL_QUADS);
    glVertex2i(380, 400);
    glVertex2i(450,400);
    glVertex2i(450, 480);
    glVertex2i(380, 480);
    glEnd();

//3rd floor front side
glColor3f(0.901, 0.847, 0.866);
    glBegin(GL_QUADS);
    glVertex2i(280, 300);
    glVertex2i(370, 300);
    glVertex2i(370, 400);
    glVertex2i(280, 400);
    glEnd();

//3rd floor back side
glColor3f(1.0, 0.941, 0.960);
    glBegin(GL_QUADS);
    glVertex2i(370, 300);
    glVertex2i(450, 300);
    glVertex2i(450, 400);
    glVertex2i(370, 400);
    glEnd();
//2nd floor front side
glColor3f(0.870, 0.647, 0.713);
    glBegin(GL_QUADS);
    glVertex2i(280, 200);
    glVertex2i(280, 300);
    glVertex2i(370, 300);
    glVertex2i(370, 200);
    glEnd();
//2nd floor back side
glColor3f(0.913, 0.752, 0.8);
    glBegin(GL_QUADS);
    glVertex2i(370, 200);
    glVertex2i(370, 300);
    glVertex2i(450, 300);
    glVertex2i(450, 200);
    glEnd();

 //1st floor front side
glColor3f(0.901, 0.847, 0.866);
    glBegin(GL_QUADS);
    glVertex2i(280, 150);
    glVertex2i(280, 200);
    glVertex2i(370, 200);
    glVertex2i(370, 150);
    glEnd();

//1st floor back side
glColor3f(1.0, 0.941, 0.960);
    glBegin(GL_QUADS);
    glVertex2i(370, 150);
    glVertex2i(370, 200);
    glVertex2i(450, 200);
    glVertex2i(450, 150);
    glEnd();

//2nd house chal
glColor3f(0.949, 0.509, 0.556);
    glBegin(GL_QUADS);
    glVertex2i(380, 500);
    glVertex2i(337, 570);
    glVertex2i(430, 570);
    glVertex2i(470, 500);
    glEnd();

glColor3f(0.749, 0.356, 0.44);
    glBegin(GL_QUADS);
    glVertex2i(380, 490);
    glVertex2i(380, 500);
    glVertex2i(470, 500);
    glVertex2i(457, 490);
    glEnd();

glColor3f(0.713, 0.592, 0.627);
    glBegin(GL_QUADS);
    glVertex2i(380, 480);
    glVertex2i(380, 490);
    glVertex2i(458, 490);
    glVertex2i(448, 480);
    glEnd();

glColor3f(0.713, 0.592, 0.627);
    glBegin(GL_QUADS);
    glVertex2i(380, 480);
    glVertex2i(380, 490);
    glVertex2i(458, 490);
    glVertex2i(448, 480);
    glEnd();

glColor3f(0.713, 0.592, 0.627);
    glBegin(GL_QUADS);
    glVertex2i(380, 480);
    glVertex2i(380, 490);
    glVertex2i(458, 490);
    glVertex2i(448, 480);
    glEnd();

glColor3f(0.698, 0.552, 0.584); // Light blue color

glBegin(GL_TRIANGLES);
  glVertex2i(420,570);
  glVertex2i(430,585);
  glVertex2i(440,570);
glEnd();

glColor3f(0.701, 0.552, 0.6); // Light blue color

//2nd building side shadow
glBegin(GL_QUADS);
  glVertex2i(430,570);
  glVertex2i(440,570);
  glVertex2i(481,500);
  glVertex2i(470,500);
glEnd();

//2nd bulding main side
glColor3f(0.850,0.823, 0.894); // Light blue color
glBegin(GL_QUADS);
  glVertex2i(430,585);
  glVertex2i(440,585);
  glVertex2i(490,500);
  glVertex2i(480,500);
glEnd();

//fiuncion janla
drawWindowFrame(445,265);


glColor3f(0.474, 0.356, 0.415);
    glBegin(GL_QUADS);
    glVertex2i(280,150);
    glVertex2i(280, 170);
    glVertex2i(450, 170);
    glVertex2i(450, 150);
    glEnd();

//space for 2nd building side part
glColor3f(0.952, 0.788, 0.839);
glBegin(GL_POLYGON);
    glVertex2i(448, 152); // Bottom-left
    glVertex2i(448, 482); // Bottom-right

    glVertex2i(468, 500); // Inner corner (top of lower bar)
    glVertex2i(490, 500); // Outer top-right
     // Bottom-left
glEnd();
drawWindowFrame(445,465);
 // Light blue color

//3rd bulding main structure
glColor3f(0.992,0.815, 0.733);
glBegin(GL_POLYGON);
    glVertex2i(450, 150); // Bottom-left
    glVertex2i(450, 450); // Bottom-right
    glVertex2i(520, 530); // Inner corner (top of lower bar)
    glVertex2i(600, 450); // Outer top-right
    glVertex2i(600, 150); // Bottom-left
glEnd();

//3rd bulding side structure
glColor3f(1.0,0.886, 0.831);
glBegin(GL_QUADS);
  glVertex2i(600,150);
  glVertex2i(600,420);
  glVertex2i(750,420);
  glVertex2i(750,150);
glEnd();

glBegin(GL_QUADS);
  glVertex2i(600,450);
  glVertex2i(515,525);
  glVertex2i(520,530);
  glVertex2i(610,450);
glEnd();

glColor3f(1.0,0.922, 0.861);
glBegin(GL_LINES);
  glVertex2i(450,250);
  glVertex2i(750,250);
glEnd();


glBegin(GL_QUADS);
  glVertex2i(600,450);
  glVertex2i(610,450);
  glVertex2i(610,410);
  glVertex2i(600,410);
glEnd();

glColor3f(0.584,0.309, 0.341);
glBegin(GL_QUADS);
 glVertex2i(610,450);
 glVertex2i(531,520);
 glVertex2i(700,520);
 glVertex2i(770,450);
glEnd();





glColor3f(0.992,0.807, 0.733);
glBegin(GL_QUADS);
 glVertex2i(570,520);
 glVertex2i(570,580);
 glVertex2i(610,580);
 glVertex2i(610,520);
glEnd();



glColor3f(0.992,0.815, 0.733);
glBegin(GL_QUADS);
 glVertex2i(600,500);
 glVertex2i(590,530);
 glVertex2i(610,530);
 glVertex2i(610,500);
glEnd();

glColor3f(0.3,0.3, 0.3);
glBegin(GL_LINES);
 glVertex2i(570,530);
 glVertex2i(610,530);
glEnd();


glColor3f(0.996,0.886, 0.831);
glBegin(GL_QUADS);
 glVertex2i(610,500);
 glVertex2i(610,580);
 glVertex2i(650,580);
 glVertex2i(650,500);
glEnd();

glColor3f(1.0,0.99, 0.78);
glBegin(GL_LINES);
 glVertex2i(610,530);
 glVertex2i(650,530);
glEnd();

glColor3f(0.800,0.700, 0.611);
glBegin(GL_QUADS);
 glVertex2i(610,570);
 glVertex2i(610,580);
 glVertex2i(650,580);
 glVertex2i(650,575);
glEnd();

glColor3f(0.847,0.717, 0.639);
glBegin(GL_QUADS);
 glVertex2i(570,570);
 glVertex2i(570,580);
 glVertex2i(610,580);
 glVertex2i(610,570);
glEnd();


glColor3f(0.940,0.780, 0.710);
glBegin(GL_QUADS);
 glVertex2i(560,580);
 glVertex2i(560,590);
 glVertex2i(610,590);
 glVertex2i(610,580);
glEnd();

glColor3f(0.925,0.760, 0.686);
glBegin(GL_QUADS);
 glVertex2i(610,580);
 glVertex2i(610,590);
 glVertex2i(660,590);
 glVertex2i(660,580);
glEnd();

glColor3f(0.466,0.243, 0.270);
glBegin(GL_QUADS);
 glVertex2i(570,590);
 glVertex2i(590,620);
 glVertex2i(610,620);
 glVertex2i(610,590);
glEnd();

glColor3f(0.584,0.309, 0.341);
glBegin(GL_QUADS);
 glVertex2i(610,590);
 glVertex2i(610,620);
 glVertex2i(630,620);
 glVertex2i(650,590);
glEnd();

glColor3f(0.941,0.756, 0.686);
glBegin(GL_QUADS);
 glVertex2i(590,620);
 glVertex2i(590,640);
 glVertex2i(630,640);
 glVertex2i(630,620);
glEnd();

glColor3f(0.596,0.305, 0.341);
glBegin(GL_QUADS);
 glVertex2i(450,150);
 glVertex2i(450,170);
 glVertex2i(770,170);
 glVertex2i(770,150);
glEnd();

glColor3f(0.584,0.309, 0.341);
glBegin(GL_TRIANGLES);
 glVertex2i(595,640);
 glVertex2i(610,690);
 glVertex2i(625,640);
glEnd();


glColor3f(0.584,0.309, 0.341);
glBegin(GL_LINES);
glVertex2i(610,688);
glVertex2i(610,750);
glEnd();

glColor3f(0.996,0.933, 0.878);
glBegin(GL_LINES);
glVertex2i(450,350);
glVertex2i(750,350);
glEnd();

glColor3f(0.941,0.756, 0.686);
glBegin(GL_TRIANGLES);
  glVertex2i(690,520);
  glVertex2i(698,535);
  glVertex2i(710,520);
glEnd();

glBegin(GL_QUADS);
  glVertex2i(710,520);
  glVertex2i(700,520);
  glVertex2i(760,450);
  glVertex2i(770,450);
glEnd();

glColor3f(0.984,0.882, 0.835);
glBegin(GL_QUADS);
  glVertex2i(698,535);
  glVertex2i(710,535);
  glVertex2i(780,450);
  glVertex2i(770,450);
glEnd();
glColor3f(0.494,0.258, 0.286);
glBegin(GL_QUADS);
  glVertex2i(770,450);
  glVertex2i(765,445);
  glVertex2i(610,445);
  glVertex2i(610,450);
glEnd();

glColor3f(0.803,0.709, 0.654);
glBegin(GL_QUADS);
  glVertex2i(610,445);
  glVertex2i(765,445);
  glVertex2i(750,410);
  glVertex2i(610,410);
glEnd();

glColor3f(0.992,0.890, 0.815);
glBegin(GL_QUADS);
  glVertex2i(750,445);
  glVertex2i(750,150);
  glVertex2i(775,150);
  glVertex2i(775,450);
glEnd();

glColor3f(0.596,0.305, 0.341);
glBegin(GL_QUADS);
 glVertex2i(450,150);
 glVertex2i(450,170);
 glVertex2i(775,170);
 glVertex2i(775,150);
glEnd();

//4th bulding
//front side
glColor3f(0.541,0.658, 0.619);
glBegin(GL_POLYGON);
 glVertex2i(790,150);
 glVertex2i(790,510);
 glVertex2i(835,600);
 glVertex2i(890,510);
 glVertex2i(890,150);

glEnd();
glColor3f(0.607,0.713, 0.666);
glBegin(GL_TRIANGLES);
 glVertex2i(790,510);
 glVertex2i(835,600);
 glVertex2i(890,510);

glEnd();

glColor3f(0.607,0.713, 0.666);
glBegin(GL_TRIANGLES);
 glVertex2i(790,510);
 glVertex2i(890,480);
 glVertex2i(990,510);

glEnd();

glColor3f(0.345,0.301, 0.254);
glBegin(GL_QUADS);
 glVertex2i(790,510);
 glVertex2i(780,510);
 glVertex2i(825,600);
 glVertex2i(835,600);
glEnd();

glColor3f(0.360,0.325, 0.270);
glBegin(GL_QUADS);
 glVertex2i(880,510);
 glVertex2i(920,510);
 glVertex2i(840,600);
 glVertex2i(825,598);
glEnd();



//back side
glColor3f(0.780,0.858, 0.850);
glBegin(GL_QUADS);
 glVertex2i(890,150);
 glVertex2i(890,510);
 glVertex2i(990,510);
 glVertex2i(990,150);

glEnd();

//bottom
glColor3f(0.376,0.325, 0.274);
glBegin(GL_QUADS);
 glVertex2i(790,150);
 glVertex2i(790,170);
 glVertex2i(990,170);
 glVertex2i(990,150);

glEnd();

//4th building chal
glColor3f(0.505,0.447, 0.364);
glBegin(GL_QUADS);
 glVertex2i(890,510);
 glVertex2i(835,600);
 glVertex2i(945,600);
 glVertex2i(998,510);

glEnd();


glColor3f(0.607,0.713, 0.666);
glBegin(GL_TRIANGLES);
 glVertex2i(790,510);
 glVertex2i(890,460);
 glVertex2i(890,510);

glEnd();

glColor3f(0.698,0.8, 0.768);
glBegin(GL_TRIANGLES);
 glVertex2i(890,460);
 glVertex2i(990,510);
 glVertex2i(890,510);

glEnd();

glColor3f(1.0,1.0, 1.0);
glBegin(GL_QUADS);
 glVertex2i(0,75);
 glVertex2i(1000,75);
 glVertex2i(1000,65);
 glVertex2i(0,65);

glEnd();


drawWindowFrame(75,240);
drawCircle(100,280,15,22,1.0,1.0,1.0);
drawCircleGlass(100,280,10,15,0.490,0.435,0.301,0.513,0.745,0.729);
drawWindowFrame(125,240);
drawWindowFrame(175,240);
drawWindowFrame(225,240);

drawWindowFrame(395,265);
drawWindowFrame(395,465);
drawWindowFrame(420,365);
drawWindowFrame(345,265);

drawCircle(325,500,15,22,0.690,0.874,0.921);
drawCircleGlass(325,500,10,15,0.7,0.8,0.900,0.800,0.900,0.999);
drawCircle(525,460,15,22,0.690,0.874,0.921);
drawCircleGlass(525,460,10,15,0.7,0.8,0.900,0.800,0.900,0.999);



drawWindowFrame(345,365);
drawWindowFrame(300,265);
drawWindowFrame(300,365);
drawWindowFrame(300,465);
drawWindowFrame(345,465);

//3rd building window
drawWindowFrame(485,300);
drawWindowFrame(630,300);
drawWindowFrame(660,300);
drawWindowFrame(690,300);
drawWindowFrame(720,300);
drawWindowFrame(520,400);



drawWindowFrame(550,300);
drawDoorFrame(520,190);

drawDoorFrame(200,190);
drawDoorFrame(100,190);
drawDoorFrame(420,190);
drawDoorFrame(680,190);

drawClockFace(630,550);
drawClockFace(590,550);

//4th building

drawDoorFrame(840,190);
drawWindowFrame(810,260);
drawWindowFrame(810,330);
drawWindowFrame(810,400);
drawWindowFrame(810,470);
drawWindowFrame(860,260);
drawWindowFrame(860,330);
drawWindowFrame(860,400);
drawWindowFrame(860,470);

drawWindowFrame(920,260);
drawWindowFrame(920,330);
drawWindowFrame(920,400);
drawWindowFrame(920,470);
drawWindowFrame(970,260);
drawWindowFrame(970,330);
drawWindowFrame(970,400);
drawWindowFrame(970,470);
drawCircle(835,540,15,22,0.690,0.874,0.921);
drawCircleGlass(835,540,10,15,0.7,0.8,0.900,0.800,0.900,0.999);


drawTree(50, 215, 14); // x, y, radius
drawCircle(40, 140,25,10,0.250,0.250,0.250);
drawTree(250, 220, 20); // x, y, radius
drawCircle(250, 140,25,10,0.250,0.250,0.250);
drawCar(carX,carY);
drawCar(carX-300,carY-50);
drawCar(carX-600,carY);
drawTree(450, 220, 20); // x, y, radius
drawCircle(440, 140,25,10,0.250,0.250,0.250);

drawTree(790, 220, 30); // x, y, radius
drawCircle(790, 140,35,10,0.250,0.250,0.250);

drawTree(30, 80, 30); // x, y, radius






 // Draw at current X position




    glFlush();	// Process a
}
void display() {
    drawShapes();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Enable double buffering
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("City View Scene");

    init(); // Initialize background and projection
    glutDisplayFunc(display); // Register display function
    glutTimerFunc(60, updateCloud, 0); // Start cloud animation
    glutTimerFunc(20, update, 0);

    glutMainLoop(); // Enter main event loop
    return 0;
}
