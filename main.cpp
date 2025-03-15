#include <windows.h>
#include<mmsystem.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

// Function to draw a circle with optional transparency
void DrawCircle(double x, double y, double radius, int R, int G, int B, int A = 255)
{
    glBegin(GL_POLYGON);
    glColor4ub(R, G, B, A);
    for (int i = 0; i < 360; i++)
    {
        double theta = i * 3.1416 / 180;
        glVertex2d(x + radius * cos(theta), y + radius * sin(theta));
    }
    glEnd();
}

// Global variables for animation and colors
bool isRain = false;
float rainSpeed = 8;
float rainPosition = 0;
float _moveCloud = 0.0f;
float _cloudSpeed = 2.0f; // Speed of cloud movement
float _moveCar = 0.0f;
float _moveBus=0.0f;
float _carSpeed = 2.5f; // Default car speed
float _busSpeed=2.5f;
bool isNight_Display = true;
int sky1R = 135, sky1G = 206, sky1B = 250; // Light blue sky
int sky2R = 135, sky2G = 206, sky2B = 250;
int SunMoonR = 255, SunMoonG = 255, SunMoonB = 0; // Yellow sun

// Function to draw the sky
void Day_Sky()
{
    glBegin(GL_QUADS);
    glColor3ub(sky1R, sky1G, sky1B);
    glVertex2f(0.0, 71.0);
    glColor3ub(sky2R, sky2G, sky2B);
    glVertex2f(0.0, 800.0);
    glVertex2f(1366.0, 800.0);
    glColor3ub(sky1R, sky1G, sky1B);
    glVertex2f(1366.0, 71.0);
    glEnd();

    DrawCircle(535, 662, 30.25, SunMoonR, SunMoonG, SunMoonB); // Sun
}

void Night_Sky()
{
    glBegin(GL_QUADS);
    glColor3ub(50, 50, 80); // Softer dark grayish-blue
    glVertex2f(0.0, 71.0);
    glColor3ub(30, 30, 60); // Slightly darker grayish-blue
    glVertex2f(0.0, 800.0);
    glVertex2f(1366.0, 800.0);
    glColor3ub(50, 50, 80); // Softer dark grayish-blue
    glVertex2f(1366.0, 71.0);
    glEnd();

    DrawCircle(535, 662, 30.25, 255, 255, 224); // Moon (light yellowish white)
}


void stars()
{
    glPointSize(3); // Make stars smaller by setting the point size to 2
    glBegin(GL_POINTS);
    glColor3ub(255, 255, 255); // White color for stars

    // Manually defined star positions in the upper half of the sky
    glVertex2f(100, 650);
    glVertex2f(200, 700);
    glVertex2f(300, 630);
    glVertex2f(400, 710);
    glVertex2f(500, 690);
    glVertex2f(600, 720);
    glVertex2f(700, 640);
    glVertex2f(800, 680);
    glVertex2f(900, 660);
    glVertex2f(1000, 710);
    glVertex2f(1100, 680);
    glVertex2f(1200, 690);
    glVertex2f(1300, 640);

    // Additional stars for more density
    glVertex2f(150, 750);
    glVertex2f(250, 740);
    glVertex2f(350, 720);
    glVertex2f(450, 740);
    glVertex2f(550, 710);
    glVertex2f(650, 760);
    glVertex2f(750, 735);
    glVertex2f(850, 750);
    glVertex2f(950, 725);
    glVertex2f(1050, 740);
    glVertex2f(1150, 715);
    glVertex2f(1250, 755);
    glVertex2f(1350, 730);

    // More stars for denser sky
    glVertex2f(50, 680);
    glVertex2f(150, 680);
    glVertex2f(250, 670);
    glVertex2f(350, 670);
    glVertex2f(450, 660);
    glVertex2f(550, 675);
    glVertex2f(650, 665);
    glVertex2f(750, 680);
    glVertex2f(850, 670);
    glVertex2f(950, 680);
    glVertex2f(1050, 675);
    glVertex2f(1150, 660);
    glVertex2f(1250, 670);
    glVertex2f(1350, 650);

    glEnd();
}




void Day_cloud()
{
//    // First cloud group (Sticky)
    DrawCircle(300, 700, 40, 255, 255, 255); // Cloud 1
    DrawCircle(350, 720, 50, 255, 255, 255); // Cloud 2
    DrawCircle(400, 700, 40, 255, 255, 255); // Cloud 3

//    // Second cloud group (Sticky)
    DrawCircle(800, 680, 45, 255, 255, 255); // Cloud 4
    DrawCircle(850, 700, 55, 255, 255, 255); // Cloud 5
    DrawCircle(900, 680, 45, 255, 255, 255); // Cloud 6

//    // Draw animated clouds
    glPushMatrix();
    glTranslatef(_moveCloud, 0.0, 0.0);

//    // Cloud group 1
    DrawCircle(200, 700, 40, 255, 255, 255); // Cloud 1
    DrawCircle(250, 720, 50, 255, 255, 255); // Cloud 2
    DrawCircle(300, 700, 40, 255, 255, 255); // Cloud 3

//    // Cloud group 2
    DrawCircle(600, 750, 35, 255, 255, 255); // Cloud 4
    DrawCircle(650, 770, 45, 255, 255, 255); // Cloud 5
    DrawCircle(700, 750, 35, 255, 255, 255); // Cloud 6

//    // Cloud group 3
    DrawCircle(1000, 700, 50, 255, 255, 255); // Cloud 7
    DrawCircle(1050, 720, 60, 255, 255, 255); // Cloud 8
    DrawCircle(1100, 700, 50, 255, 255, 255); // Cloud 9

    glPopMatrix();
}


void Night_Cloud()
{
    // First cloud group (Sticky)
    DrawCircle(300, 700, 40, 180, 180, 180); // Cloud 1 (light gray)
    DrawCircle(350, 720, 50, 180, 180, 180); // Cloud 2
    DrawCircle(400, 700, 40, 180, 180, 180); // Cloud 3

    // Second cloud group (Sticky)
    DrawCircle(800, 680, 45, 180, 180, 180); // Cloud 4
    DrawCircle(850, 700, 55, 180, 180, 180); // Cloud 5
    DrawCircle(900, 680, 45, 180, 180, 180); // Cloud 6

    // Draw animated clouds
    glPushMatrix();
    glTranslatef(_moveCloud, 0.0, 0.0);

    // Cloud group 1
    DrawCircle(200, 700, 40, 180, 180, 180); // Cloud 1
    DrawCircle(250, 720, 50, 180, 180, 180); // Cloud 2
    DrawCircle(300, 700, 40, 180, 180, 180); // Cloud 3

    // Cloud group 2
    DrawCircle(600, 750, 35, 180, 180, 180); // Cloud 4
    DrawCircle(650, 770, 45, 180, 180, 180); // Cloud 5
    DrawCircle(700, 750, 35, 180, 180, 180); // Cloud 6

    // Cloud group 3
    DrawCircle(1000, 700, 50, 180, 180, 180); // Cloud 7
    DrawCircle(1050, 720, 60, 180, 180, 180); // Cloud 8
    DrawCircle(1100, 700, 50, 180, 180, 180); // Cloud 9

    glPopMatrix();
}


float birdPositions[3] = {1366.0f, 1366.0f + 50.0f, 1366.0f + 100.0f}; // Positions for 3 birds, starting with a small gap between them
float birdSpeed = 2.0f;  // Speed of the birds
float birdYPosition = 660.0f;  // Fixed y position for all birds (flying in a row)

void DrawSimpleBird(float x, float y)
{
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0); // Black color for the bird's wings

    // Left wing
    glVertex2f(x, y);              // Starting point
    glVertex2f(x - 15.0f, y + 10.0f); // Left wing tip

    // Right wing
    glVertex2f(x, y);              // Starting point
    glVertex2f(x + 15.0f, y + 10.0f); // Right wing tip

    glEnd();
}

// Update bird positions
void UpdateBirdPosition()
{
    for (int i = 0; i < 3; ++i)
    {
        birdPositions[i] -= birdSpeed; // Move each bird to the left

        // Reset bird position when it goes off-screen
        if (birdPositions[i] < -20.0f)
        {
            birdPositions[i] = 1366.0f + (i * 50.0f); // Reset each bird with a small gap
        }
    }
}

void rain(float x_axis, float y_axis)
{
    glLineWidth(1);
    glColor3f(1, 1, 1); // White raindrops
    glBegin(GL_LINES);
    glVertex2f(x_axis, y_axis);         // Start of the raindrop
    glVertex2f(x_axis, y_axis - 15.0); // End of the raindrop (15px downward)
    glEnd();
}

void rain_fall()
{
    if (!isRain)
        return; // Only render rain if isRain is true

    glPushMatrix();
    glTranslatef(0, rainPosition, 0);
    for (float x = 0; x <= 1520; x += 20)    // Horizontal spacing for raindrops
    {
        for (float y = 0; y <= 800; y += 40)   // Vertical spacing for raindrops
        {
            rain(x, y);
        }
    }
    glPopMatrix();
}

void rain_update(int value)
{
    if (isRain)
    {
        rainPosition -= rainSpeed; // Move rain downward
        if (rainPosition<-1.0)   // Reset rain when it goes out of view
        {
            rainPosition = 80.0;
        }
    }

    glutPostRedisplay();             // Request a redraw
    glutTimerFunc(60, rain_update, 0); // Call this function again after 60ms
}

void DrawBuildingA(bool isNight_Display)
{
    //..........................First Building.............//
    // Draw the building body (5 stories)
    glBegin(GL_QUADS);
    glColor3ub(255, 165, 0);  // Orange color for the building body
    glVertex2f(20.0, 90.0);   // Bottom left (shifted more left)
    glVertex2f(220.0, 90.0);  // Bottom right
    glVertex2f(220.0, 440.0); // Top right
    glVertex2f(20.0, 440.0);  // Top left
    glEnd();

    // Draw the windows manually (4 rows and 2 columns)

    // Bottom row windows
    if (isNight_Display)
    {
        glColor3ub(255, 255, 153);  // Soft yellow for night mode
    }
    else
    {
        glColor3ub(135, 206, 235);  // Soft sky blue for day mode

    }
    // First window (left) - moved to the right
    glBegin(GL_QUADS);
    glVertex2f(50.0, 110.0);    // Bottom left (shifted to the right)
    glVertex2f(100.0, 110.0);   // Bottom right
    glVertex2f(100.0, 160.0);   // Top right
    glVertex2f(50.0, 160.0);    // Top left
    glEnd();
    // Second window (right)
    glBegin(GL_QUADS);
    glVertex2f(130.0, 110.0);   // Bottom left
    glVertex2f(180.0, 110.0);   // Bottom right
    glVertex2f(180.0, 160.0);   // Top right
    glVertex2f(130.0, 160.0);   // Top left
    glEnd();

    // Second row of windows
    glBegin(GL_QUADS);
    glVertex2f(50.0, 180.0);    // Bottom left
    glVertex2f(100.0, 180.0);   // Bottom right
    glVertex2f(100.0, 230.0);   // Top right
    glVertex2f(50.0, 230.0);    // Top left
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(130.0, 180.0);   // Bottom left
    glVertex2f(180.0, 180.0);   // Bottom right
    glVertex2f(180.0, 230.0);   // Top right
    glVertex2f(130.0, 230.0);   // Top left
    glEnd();

    // Third row of windows
    glBegin(GL_QUADS);
    glVertex2f(50.0, 250.0);    // Bottom left
    glVertex2f(100.0, 250.0);   // Bottom right
    glVertex2f(100.0, 300.0);   // Top right
    glVertex2f(50.0, 300.0);    // Top left
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(130.0, 250.0);   // Bottom left
    glVertex2f(180.0, 250.0);   // Bottom right
    glVertex2f(180.0, 300.0);   // Top right
    glVertex2f(130.0, 300.0);   // Top left
    glEnd();

    // Fourth row of windows
    glBegin(GL_QUADS);
    glVertex2f(50.0, 330.0);    // Bottom left
    glVertex2f(100.0, 330.0);   // Bottom right
    glVertex2f(100.0, 380.0);   // Top right
    glVertex2f(50.0, 380.0);    // Top left
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(130.0, 330.0);   // Bottom left
    glVertex2f(180.0, 330.0);   // Bottom right
    glVertex2f(180.0, 380.0);   // Top right
    glVertex2f(130.0, 380.0);   // Top left
    glEnd();
}





void DrawBuildingB(bool isNight_Display)
{
    // Draw the second building body (5 stories) with soft pink color
    glBegin(GL_QUADS);
    glColor3ub(255, 182, 193);  // Soft pink color for the building body
    glVertex2f(240.0, 90.0);    // Bottom left (moved more to the left)
    glVertex2f(400.0, 90.0);    // Bottom right
    glVertex2f(400.0, 490.0);   // Top right
    glVertex2f(240.0, 490.0);   // Top left
    glEnd();

    // Draw windows for the second building (1 column, 5 rows)
    if (isNight_Display)
    {
        glColor3ub(255, 255, 153);  // Soft yellow for night mode
    }
    else
    {

        glColor3ub(245, 245, 245);  // Very soft white color for windows
    }

    // First window (bottom left corner) - slightly increased height
    glBegin(GL_QUADS);
    glVertex2f(270.0, 110.0);    // Bottom left
    glVertex2f(360.0, 110.0);    // Bottom right
    glVertex2f(360.0, 170.0);    // Top right (slightly increased height)
    glVertex2f(270.0, 170.0);    // Top left
    glEnd();

    // Second window (next row) - slightly increased height
    glBegin(GL_QUADS);
    glVertex2f(270.0, 180.0);    // Bottom left
    glVertex2f(360.0, 180.0);    // Bottom right
    glVertex2f(360.0, 240.0);    // Top right (slightly increased height)
    glVertex2f(270.0, 240.0);    // Top left
    glEnd();

    // Third window (middle row) - slightly increased height
    glBegin(GL_QUADS);
    glVertex2f(270.0, 250.0);    // Bottom left
    glVertex2f(360.0, 250.0);    // Bottom right
    glVertex2f(360.0, 310.0);    // Top right (slightly increased height)
    glVertex2f(270.0, 310.0);    // Top left
    glEnd();

    // Fourth window (next row) - slightly increased height
    glBegin(GL_QUADS);
    glVertex2f(270.0, 320.0);    // Bottom left
    glVertex2f(360.0, 320.0);    // Bottom right
    glVertex2f(360.0, 380.0);    // Top right (slightly increased height)
    glVertex2f(270.0, 380.0);    // Top left
    glEnd();

    // Fifth window (top row) - slightly increased height
    glBegin(GL_QUADS);
    glVertex2f(270.0, 390.0);    // Bottom left
    glVertex2f(360.0, 390.0);    // Bottom right
    glVertex2f(360.0, 450.0);    // Top right (slightly increased height)
    glVertex2f(270.0, 450.0);    // Top left
    glEnd();
}


void DrawTrafficLight()
{
    // Draw the pole
    glBegin(GL_QUADS);
    glColor3ub(100, 100, 100);  // Grey color for the pole
    glVertex2f(600, 75);               // Bottom-left of the pole
    glVertex2f(610, 75);               // Bottom-right of the pole
    glVertex2f(610, 125);              // Top-right of the pole
    glVertex2f(600, 125);              // Top-left of the pole
    glEnd();

    // Draw the traffic light box (with even bigger bottom)
    glBegin(GL_QUADS);
    glColor3ub(50, 50, 50);  // Dark grey for the box
    glVertex2f(595, 125);   // Bottom-left of the box
    glVertex2f(615, 125);   // Bottom-right of the box
    glVertex2f(615, 170);   // Top-right of the box (moved down more)
    glVertex2f(595, 170);   // Top-left of the box (moved down more)
    glEnd();

    // Set point size to make dots larger for the traffic light
    glPointSize(9.0);  // Increase size of dots

    // Draw the Red light (as a dot)
    glColor3ub(255, 0, 0);  // Red light
    glBegin(GL_POINTS);
    glVertex2f(605, 160);  // Red light position (adjusted for bigger box)
    glEnd();

    // Draw the Yellow light (as a dot)
    glColor3ub(255, 255, 0);  // Yellow light
    glBegin(GL_POINTS);
    glVertex2f(605, 150);  // Yellow light position (adjusted for bigger box)
    glEnd();

    // Draw the Green light (as a dot)
    glColor3ub(0, 255, 0);  // Green light
    glBegin(GL_POINTS);
    glVertex2f(605, 140);  // Green light position (adjusted for bigger box)
    glEnd();
}



void DrawBuildingC(bool isNight_Display)
{
    // Base of Building C
    glBegin(GL_QUADS);
    glColor3ub(44, 62, 80); // Dark blue base color
    glVertex2d(440, 90);  // Base bottom-left (moved left)
    glVertex2d(440, 440); // Increased height for building (top-left)
    glVertex2d(600, 440); // Increased height for building (top-right)
    glVertex2d(600, 90);  // Base bottom-right
    glEnd();

    // Roof of Building C
    glBegin(GL_QUADS);
    glColor3ub(30, 42, 54); // Roof color
    glVertex2d(440, 440); // Roof bottom-left
    glVertex2d(600, 440); // Roof bottom-right
    glVertex2d(600, 445); // Roof top-right
    glVertex2d(440, 445); // Roof top-left
    glEnd();

    // Draw eight floors with windows
    int floorHeight = 40;  // Height of each floor
    int windowWidth = 18;  // Width of each window
    int windowHeight = 25; // Height of each window
    int windowSpacingX = 12; // Horizontal spacing between windows
    int windowSpacingY = 8;  // Vertical spacing from floor

    // Floor 1 (Bottom floor)
    glBegin(GL_QUADS);
    if (isNight_Display)
    {
        glColor3ub(255, 255, 153);  // Soft yellow for night mode
    }
    else
    {
        glColor3ub(190, 230, 255); // Light blue window color

    }
    glVertex2d(450, 130); // Bottom left (moved left)
    glVertex2d(468, 130); // Bottom right
    glVertex2d(468, 155); // Top right
    glVertex2d(450, 155); // Top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 130);
    glVertex2d(498, 130);
    glVertex2d(498, 155);
    glVertex2d(480, 155);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 130);
    glVertex2d(528, 130);
    glVertex2d(528, 155);
    glVertex2d(510, 155);
    glEnd();

    // 4th column window added to Floor 1
    glBegin(GL_QUADS);
    glVertex2d(540, 130);
    glVertex2d(558, 130);
    glVertex2d(558, 155);
    glVertex2d(540, 155);
    glEnd();

    // Floor 2
    glBegin(GL_QUADS);
    glVertex2d(450, 170);
    glVertex2d(468, 170);
    glVertex2d(468, 195);
    glVertex2d(450, 195);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 170);
    glVertex2d(498, 170);
    glVertex2d(498, 195);
    glVertex2d(480, 195);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 170);
    glVertex2d(528, 170);
    glVertex2d(528, 195);
    glVertex2d(510, 195);
    glEnd();

    // 4th column window added to Floor 2
    glBegin(GL_QUADS);
    glVertex2d(540, 170);
    glVertex2d(558, 170);
    glVertex2d(558, 195);
    glVertex2d(540, 195);
    glEnd();

    // Floor 3
    glBegin(GL_QUADS);
    glVertex2d(450, 210);
    glVertex2d(468, 210);
    glVertex2d(468, 235);
    glVertex2d(450, 235);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 210);
    glVertex2d(498, 210);
    glVertex2d(498, 235);
    glVertex2d(480, 235);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 210);
    glVertex2d(528, 210);
    glVertex2d(528, 235);
    glVertex2d(510, 235);
    glEnd();

    // 4th column window added to Floor 3
    glBegin(GL_QUADS);
    glVertex2d(540, 210);
    glVertex2d(558, 210);
    glVertex2d(558, 235);
    glVertex2d(540, 235);
    glEnd();

    // Floor 4
    glBegin(GL_QUADS);
    glVertex2d(450, 250);
    glVertex2d(468, 250);
    glVertex2d(468, 275);
    glVertex2d(450, 275);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 250);
    glVertex2d(498, 250);
    glVertex2d(498, 275);
    glVertex2d(480, 275);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 250);
    glVertex2d(528, 250);
    glVertex2d(528, 275);
    glVertex2d(510, 275);
    glEnd();

    // 4th column window added to Floor 4
    glBegin(GL_QUADS);
    glVertex2d(540, 250);
    glVertex2d(558, 250);
    glVertex2d(558, 275);
    glVertex2d(540, 275);
    glEnd();

    // Floor 5
    glBegin(GL_QUADS);
    glVertex2d(450, 290);
    glVertex2d(468, 290);
    glVertex2d(468, 315);
    glVertex2d(450, 315);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 290);
    glVertex2d(498, 290);
    glVertex2d(498, 315);
    glVertex2d(480, 315);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 290);
    glVertex2d(528, 290);
    glVertex2d(528, 315);
    glVertex2d(510, 315);
    glEnd();

    // 4th column window added to Floor 5
    glBegin(GL_QUADS);
    glVertex2d(540, 290);
    glVertex2d(558, 290);
    glVertex2d(558, 315);
    glVertex2d(540, 315);
    glEnd();

    // Floor 6
    glBegin(GL_QUADS);
    glVertex2d(450, 330);
    glVertex2d(468, 330);
    glVertex2d(468, 355);
    glVertex2d(450, 355);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 330);
    glVertex2d(498, 330);
    glVertex2d(498, 355);
    glVertex2d(480, 355);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 330);
    glVertex2d(528, 330);
    glVertex2d(528, 355);
    glVertex2d(510, 355);
    glEnd();

    // 4th column window added to Floor 6
    glBegin(GL_QUADS);
    glVertex2d(540, 330);
    glVertex2d(558, 330);
    glVertex2d(558, 355);
    glVertex2d(540, 355);
    glEnd();

    // Floor 7
    glBegin(GL_QUADS);
    glVertex2d(450, 370);
    glVertex2d(468, 370);
    glVertex2d(468, 395);
    glVertex2d(450, 395);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 370);
    glVertex2d(498, 370);
    glVertex2d(498, 395);
    glVertex2d(480, 395);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 370);
    glVertex2d(528, 370);
    glVertex2d(528, 395);
    glVertex2d(510, 395);
    glEnd();

    // 4th column window added to Floor 7
    glBegin(GL_QUADS);
    glVertex2d(540, 370);
    glVertex2d(558, 370);
    glVertex2d(558, 395);
    glVertex2d(540, 395);
    glEnd();

    // Floor 8 (Top floor)
    glBegin(GL_QUADS);
    glVertex2d(450, 410);
    glVertex2d(468, 410);
    glVertex2d(468, 435);
    glVertex2d(450, 435);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(480, 410);
    glVertex2d(498, 410);
    glVertex2d(498, 435);
    glVertex2d(480, 435);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(510, 410);
    glVertex2d(528, 410);
    glVertex2d(528, 435);
    glVertex2d(510, 435);
    glEnd();

    // 4th column window added to Floor 8
    glBegin(GL_QUADS);
    glVertex2d(540, 410);
    glVertex2d(558, 410);
    glVertex2d(558, 435);
    glVertex2d(540, 435);
    glEnd();

    glFlush();
}


void DrawBuildingD(bool isNight_Display)
{
    // Building Body
    glBegin(GL_QUADS);
    glColor3ub(33, 0, 67); // Dark purple base color
    glVertex2d(620, 400); // Bottom left
    glVertex2d(620, 85);  // Bottom right
    glVertex2d(790, 85);  // Top right
    glVertex2d(790, 400); // Top left
    glEnd();

    // Roof of the building
    glBegin(GL_QUADS);
    glColor3ub(27, 54, 68); // Roof color
    glVertex2d(620, 405); // Roof bottom left
    glVertex2d(790, 405); // Roof bottom right
    glVertex2d(790, 400); // Roof top right
    glVertex2d(620, 400); // Roof top left
    glEnd();

    // Draw six floors with windows
    int floorHeight = 50; // Height of each floor
    int windowWidth = 20; // Width of each window
    int windowHeight = 30; // Height of each window
    int windowSpacingX = 15; // Horizontal spacing between windows
    int windowSpacingY = 10; // Vertical spacing from floor

    // First floor
    glBegin(GL_QUADS);
    if (isNight_Display)
    {
        glColor3ub(255, 255, 153);  // Soft yellow for night mode
    }
    else
    {

        glColor3ub(170, 216, 230); // Window color

    }
    glVertex2d(630, 380); // First window bottom left
    glVertex2d(650, 380); // First window bottom right
    glVertex2d(650, 350); // First window top right
    glVertex2d(630, 350); // First window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(665, 380); // Second window bottom left
    glVertex2d(685, 380); // Second window bottom right
    glVertex2d(685, 350); // Second window top right
    glVertex2d(665, 350); // Second window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(700, 380); // Third window bottom left
    glVertex2d(720, 380); // Third window bottom right
    glVertex2d(720, 350); // Third window top right
    glVertex2d(700, 350); // Third window top left
    glEnd();

    // Second floor
    glBegin(GL_QUADS);
    glVertex2d(630, 330); // First window bottom left
    glVertex2d(650, 330); // First window bottom right
    glVertex2d(650, 300); // First window top right
    glVertex2d(630, 300); // First window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(665, 330); // Second window bottom left
    glVertex2d(685, 330); // Second window bottom right
    glVertex2d(685, 300); // Second window top right
    glVertex2d(665, 300); // Second window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(700, 330); // Third window bottom left
    glVertex2d(720, 330); // Third window bottom right
    glVertex2d(720, 300); // Third window top right
    glVertex2d(700, 300); // Third window top left
    glEnd();

    // Third floor
    glBegin(GL_QUADS);
    glVertex2d(630, 280); // First window bottom left
    glVertex2d(650, 280); // First window bottom right
    glVertex2d(650, 250); // First window top right
    glVertex2d(630, 250); // First window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(665, 280); // Second window bottom left
    glVertex2d(685, 280); // Second window bottom right
    glVertex2d(685, 250); // Second window top right
    glVertex2d(665, 250); // Second window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(700, 280); // Third window bottom left
    glVertex2d(720, 280); // Third window bottom right
    glVertex2d(720, 250); // Third window top right
    glVertex2d(700, 250); // Third window top left
    glEnd();

    // Fourth floor
    glBegin(GL_QUADS);
    glVertex2d(630, 230); // First window bottom left
    glVertex2d(650, 230); // First window bottom right
    glVertex2d(650, 200); // First window top right
    glVertex2d(630, 200); // First window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(665, 230); // Second window bottom left
    glVertex2d(685, 230); // Second window bottom right
    glVertex2d(685, 200); // Second window top right
    glVertex2d(665, 200); // Second window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(700, 230); // Third window bottom left
    glVertex2d(720, 230); // Third window bottom right
    glVertex2d(720, 200); // Third window top right
    glVertex2d(700, 200); // Third window top left
    glEnd();

    // Fifth floor
    glBegin(GL_QUADS);
    glVertex2d(630, 180); // First window bottom left
    glVertex2d(650, 180); // First window bottom right
    glVertex2d(650, 150); // First window top right
    glVertex2d(630, 150); // First window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(665, 180); // Second window bottom left
    glVertex2d(685, 180); // Second window bottom right
    glVertex2d(685, 150); // Second window top right
    glVertex2d(665, 150); // Second window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(700, 180); // Third window bottom left
    glVertex2d(720, 180); // Third window bottom right
    glVertex2d(720, 150); // Third window top right
    glVertex2d(700, 150); // Third window top left
    glEnd();

    // Sixth floor
    glBegin(GL_QUADS);
    glVertex2d(630, 130); // First window bottom left
    glVertex2d(650, 130); // First window bottom right
    glVertex2d(650, 100); // First window top right
    glVertex2d(630, 100); // First window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(665, 130); // Second window bottom left
    glVertex2d(685, 130); // Second window bottom right
    glVertex2d(685, 100); // Second window top right
    glVertex2d(665, 100); // Second window top left
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(700, 130); // Third window bottom left
    glVertex2d(720, 130); // Third window bottom right
    glVertex2d(720, 100); // Third window top right
    glVertex2d(700, 100); // Third window top left
    glEnd();

    glFlush();
}

void DrawBuildingE(bool isNight_Display)
 {
    // Base colors for the building and roof
    glColor3ub(60, 20, 80); // Dark violet base color

    // Main building structure
    glBegin(GL_QUADS);
    glVertex2d(800, 500);   // Top-left corner
    glVertex2d(800, 85);    // Bottom-left corner
    glVertex2d(1050, 85);   // Bottom-right corner
    glVertex2d(1050, 500);  // Top-right corner
    glEnd();

    // Roof of the building
    glColor3ub(45, 15, 60); // Darker roof color
    glBegin(GL_QUADS);
    glVertex2d(800, 505);   // Top-left corner
    glVertex2d(1050, 505);  // Top-right corner
    glVertex2d(1050, 500);  // Bottom-right corner
    glVertex2d(800, 500);   // Bottom-left corner
    glEnd();

        glBegin(GL_QUADS);
    if (isNight_Display)
    {
        glColor3ub(255, 255, 153);  // Soft yellow for night mode
    }
    else
    {

    glColor3ub(170, 216, 230); // Light blue window color

    }

    // Draw windows (explicitly specify each coordinate for all windows)

    // Floor 1
    glBegin(GL_QUADS);
    glVertex2d(810, 480); glVertex2d(830, 480); glVertex2d(830, 440); glVertex2d(810, 440);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(850, 480); glVertex2d(870, 480); glVertex2d(870, 440); glVertex2d(850, 440);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(890, 480); glVertex2d(910, 480); glVertex2d(910, 440); glVertex2d(890, 440);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(930, 480); glVertex2d(950, 480); glVertex2d(950, 440); glVertex2d(930, 440);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(970, 480); glVertex2d(990, 480); glVertex2d(990, 440); glVertex2d(970, 440);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(1010, 480); glVertex2d(1030, 480); glVertex2d(1030, 440); glVertex2d(1010, 440);
    glEnd();

    // Floor 2
    glBegin(GL_QUADS);
    glVertex2d(810, 410); glVertex2d(830, 410); glVertex2d(830, 370); glVertex2d(810, 370);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(850, 410); glVertex2d(870, 410); glVertex2d(870, 370); glVertex2d(850, 370);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(890, 410); glVertex2d(910, 410); glVertex2d(910, 370); glVertex2d(890, 370);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(930, 410); glVertex2d(950, 410); glVertex2d(950, 370); glVertex2d(930, 370);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(970, 410); glVertex2d(990, 410); glVertex2d(990, 370); glVertex2d(970, 370);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(1010, 410); glVertex2d(1030, 410); glVertex2d(1030, 370); glVertex2d(1010, 370);
    glEnd();

    // Floor 3
    glBegin(GL_QUADS);
    glVertex2d(810, 340); glVertex2d(830, 340); glVertex2d(830, 300); glVertex2d(810, 300);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(850, 340); glVertex2d(870, 340); glVertex2d(870, 300); glVertex2d(850, 300);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(890, 340); glVertex2d(910, 340); glVertex2d(910, 300); glVertex2d(890, 300);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(930, 340); glVertex2d(950, 340); glVertex2d(950, 300); glVertex2d(930, 300);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(970, 340); glVertex2d(990, 340); glVertex2d(990, 300); glVertex2d(970, 300);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(1010, 340); glVertex2d(1030, 340); glVertex2d(1030, 300); glVertex2d(1010, 300);
    glEnd();

    // Floor 4
    glBegin(GL_QUADS);
    glVertex2d(810, 270); glVertex2d(830, 270); glVertex2d(830, 230); glVertex2d(810, 230);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(850, 270); glVertex2d(870, 270); glVertex2d(870, 230); glVertex2d(850, 230);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(890, 270); glVertex2d(910, 270); glVertex2d(910, 230); glVertex2d(890, 230);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(930, 270); glVertex2d(950, 270); glVertex2d(950, 230); glVertex2d(930, 230);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(970, 270); glVertex2d(990, 270); glVertex2d(990, 230); glVertex2d(970, 230);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(1010, 270); glVertex2d(1030, 270); glVertex2d(1030, 230); glVertex2d(1010, 230);
    glEnd();

    // Floor 5
    glBegin(GL_QUADS);
    glVertex2d(810, 200); glVertex2d(830, 200); glVertex2d(830, 160); glVertex2d(810, 160);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(850, 200); glVertex2d(870, 200); glVertex2d(870, 160); glVertex2d(850, 160);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(890, 200); glVertex2d(910, 200); glVertex2d(910, 160); glVertex2d(890, 160);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(930, 200); glVertex2d(950, 200); glVertex2d(950, 160); glVertex2d(930, 160);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(970, 200); glVertex2d(990, 200); glVertex2d(990, 160); glVertex2d(970, 160);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(1010, 200); glVertex2d(1030, 200); glVertex2d(1030, 160); glVertex2d(1010, 160);
    glEnd();

    glFlush();
}

void DrawBuildingF(bool isNight_Display)
{
    // Main building structure (10 stories with reduced width and shifted left)
    glBegin(GL_QUADS);
    glColor3ub(90, 20,60); // Medium purple color for the building
    glVertex2d(1070, 600);   // Left-top corner (shifted left)
    glVertex2d(1070, 85);    // Left-bottom corner
    glVertex2d(1230, 85);    // Right-bottom corner (reduced width)
    glVertex2d(1230, 600);   // Right-top corner (reduced width)
    glEnd();

    // Roof of the building
    glBegin(GL_QUADS);
    glColor3ub(70, 30, 100); // Darker roof color
    glVertex2d(1070, 605);   // Top-left corner
    glVertex2d(1230, 605);   // Top-right corner (reduced width)
    glVertex2d(1230, 600);   // Bottom-right corner
    glVertex2d(1070, 600);   // Bottom-left corner
    glEnd();

        glBegin(GL_QUADS);
    if (isNight_Display)
    {
        glColor3ub(255, 255, 153);  // Soft yellow for night mode
    }
    else
    {

    glColor3ub(170, 216, 230); // Light blue window color

    }

    // Draw floors with windows
    for (int floor = 0; floor < 10; ++floor) // 10 floors
    {
        int baseY = 590 - (floor * 50); // Each floor is 50 pixels high

        // Draw windows for this floor
        for (int x = 1080; x <= 1220; x += 30) // Windows start from new position
        {
            glBegin(GL_QUADS);
            glVertex2d(x, baseY - 10);       // Top-left of the window
            glVertex2d(x + 20, baseY - 10); // Top-right of the window
            glVertex2d(x + 20, baseY - 40); // Bottom-right of the window
            glVertex2d(x, baseY - 40);      // Bottom-left of the window
            glEnd();
        }
    }

    glFlush();
}



void DrawBuildingG(bool isNight_Display)
{
    // Main building structure (10 stories with increased height)
    glBegin(GL_QUADS);
    glColor3ub(80, 30, 120); // Dark purple base color
    glVertex2d(1250, 500);   // Left-top corner (shifted right and higher)
    glVertex2d(1250, 85);    // Left-bottom corner
    glVertex2d(1450, 85);    // Right-bottom corner (extended for 10 stories)
    glVertex2d(1450, 500);   // Right-top corner (extended for 10 stories)
    glEnd();

    // Roof of the building (extended)
    glBegin(GL_QUADS);
    glColor3ub(50, 20, 90);  // Darker roof color
    glVertex2d(1250, 505);
    glVertex2d(1450, 505);
    glVertex2d(1450, 500);
    glVertex2d(1250, 500);
    glEnd();

    // Floor 1 (y = 490)
    glBegin(GL_QUADS);
    if (isNight_Display)
    {
        glColor3ub(255, 255, 153);  // Soft yellow for night mode
    }
    else
    {

        glColor3ub(170, 216, 230); // Light blue window color

    }
    glVertex2d(1260, 490); // Top-left of the window
    glVertex2d(1280, 490); // Top-right of the window
    glVertex2d(1280, 450); // Bottom-right of the window
    glVertex2d(1260, 450); // Bottom-left of the window
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 490);
    glVertex2d(1320, 490);
    glVertex2d(1320, 450);
    glVertex2d(1300, 450);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 490);
    glVertex2d(1360, 490);
    glVertex2d(1360, 450);
    glVertex2d(1340, 450);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 490);
    glVertex2d(1400, 490);
    glVertex2d(1400, 450);
    glVertex2d(1380, 450);
    glEnd();

    // Floor 2 (y = 440)
    glBegin(GL_QUADS);
    glVertex2d(1260, 440);
    glVertex2d(1280, 440);
    glVertex2d(1280, 400);
    glVertex2d(1260, 400);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 440);
    glVertex2d(1320, 440);
    glVertex2d(1320, 400);
    glVertex2d(1300, 400);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 440);
    glVertex2d(1360, 440);
    glVertex2d(1360, 400);
    glVertex2d(1340, 400);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 440);
    glVertex2d(1400, 440);
    glVertex2d(1400, 400);
    glVertex2d(1380, 400);
    glEnd();

    // Floor 3 (y = 390)
    glBegin(GL_QUADS);
    glVertex2d(1260, 390);
    glVertex2d(1280, 390);
    glVertex2d(1280, 350);
    glVertex2d(1260, 350);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 390);
    glVertex2d(1320, 390);
    glVertex2d(1320, 350);
    glVertex2d(1300, 350);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 390);
    glVertex2d(1360, 390);
    glVertex2d(1360, 350);
    glVertex2d(1340, 350);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 390);
    glVertex2d(1400, 390);
    glVertex2d(1400, 350);
    glVertex2d(1380, 350);
    glEnd();

    // Floor 4 (y = 340)
    glBegin(GL_QUADS);
    glVertex2d(1260, 340);
    glVertex2d(1280, 340);
    glVertex2d(1280, 300);
    glVertex2d(1260, 300);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 340);
    glVertex2d(1320, 340);
    glVertex2d(1320, 300);
    glVertex2d(1300, 300);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 340);
    glVertex2d(1360, 340);
    glVertex2d(1360, 300);
    glVertex2d(1340, 300);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 340);
    glVertex2d(1400, 340);
    glVertex2d(1400, 300);
    glVertex2d(1380, 300);
    glEnd();

    // Floor 5 (y = 290)
    glBegin(GL_QUADS);
    glVertex2d(1260, 290);
    glVertex2d(1280, 290);
    glVertex2d(1280, 250);
    glVertex2d(1260, 250);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 290);
    glVertex2d(1320, 290);
    glVertex2d(1320, 250);
    glVertex2d(1300, 250);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 290);
    glVertex2d(1360, 290);
    glVertex2d(1360, 250);
    glVertex2d(1340, 250);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 290);
    glVertex2d(1400, 290);
    glVertex2d(1400, 250);
    glVertex2d(1380, 250);
    glEnd();

    // Floor 6 (y = 240)
    glBegin(GL_QUADS);
    glVertex2d(1260, 240);
    glVertex2d(1280, 240);
    glVertex2d(1280, 200);
    glVertex2d(1260, 200);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 240);
    glVertex2d(1320, 240);
    glVertex2d(1320, 200);
    glVertex2d(1300, 200);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 240);
    glVertex2d(1360, 240);
    glVertex2d(1360, 200);
    glVertex2d(1340, 200);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 240);
    glVertex2d(1400, 240);
    glVertex2d(1400, 200);
    glVertex2d(1380, 200);
    glEnd();

    // Floor 7 (y = 190)
    glBegin(GL_QUADS);
    glVertex2d(1260, 190);
    glVertex2d(1280, 190);
    glVertex2d(1280, 150);
    glVertex2d(1260, 150);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 190);
    glVertex2d(1320, 190);
    glVertex2d(1320, 150);
    glVertex2d(1300, 150);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 190);
    glVertex2d(1360, 190);
    glVertex2d(1360, 150);
    glVertex2d(1340, 150);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 190);
    glVertex2d(1400, 190);
    glVertex2d(1400, 150);
    glVertex2d(1380, 150);
    glEnd();

    // Floor 8 (y = 140)
    glBegin(GL_QUADS);
    glVertex2d(1260, 140);
    glVertex2d(1280, 140);
    glVertex2d(1280, 100);
    glVertex2d(1260, 100);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 140);
    glVertex2d(1320, 140);
    glVertex2d(1320, 100);
    glVertex2d(1300, 100);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 140);
    glVertex2d(1360, 140);
    glVertex2d(1360, 100);
    glVertex2d(1340, 100);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 140);
    glVertex2d(1400, 140);
    glVertex2d(1400, 100);
    glVertex2d(1380, 100);
    glEnd();

    // Floor 9 (y = 90)
    glBegin(GL_QUADS);
    glVertex2d(1260, 90);
    glVertex2d(1280, 90);
    glVertex2d(1280, 85); // Bottom of building
    glVertex2d(1260, 85);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1300, 90);
    glVertex2d(1320, 90);
    glVertex2d(1320, 85);
    glVertex2d(1300, 85);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1340, 90);
    glVertex2d(1360, 90);
    glVertex2d(1360, 85);
    glVertex2d(1340, 85);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d(1380, 90);
    glVertex2d(1400, 90);
    glVertex2d(1400, 85);
    glVertex2d(1380, 85);
    glEnd();

    glFlush();
}




void DrawRoad()
{
    // Road base
    glBegin(GL_QUADS);
    glColor3ub(31, 30, 31);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 70.0);
    glVertex2f(1366.0, 70.0);
    glVertex2f(1366.0, 0.0);
    glEnd();

    // Grass border
    glBegin(GL_QUADS);
    glColor3ub(70, 116, 37);
    glVertex2f(0.0, 71.0);
    glVertex2f(0.0, 90.0);
    glVertex2f(1366.0, 90.0);
    glVertex2f(1366.0, 71.0);
    glEnd();

    // Road lines
    for (float xOffset = 0; xOffset <= 1200; xOffset += 200)
    {
        glPushMatrix();
        glTranslatef(xOffset, 0.0, 0.0);
        glBegin(GL_QUADS);
        glColor3ub(255, 255, 255);
        glVertex2d(35, 35);
        glVertex2d(145, 35);
        glVertex2d(140, 42);
        glVertex2d(30, 42);
        glEnd();
        glPopMatrix();
    }
    DrawTrafficLight();  // Second traffic light

}

void DrawTrees()
{
    // Triangular big tree (further left of the RIGHT tree)
    //-------TRUNK-----//
    glBegin(GL_QUADS);
    glColor3ub(58, 24, 10);
    glVertex2d(180, 85);  // Move the trunk further left
    glVertex2d(180, 105);
    glVertex2d(190, 105);
    glVertex2d(190, 85);
    glEnd();

    //---Leaves by triangle----//
    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(160, 105); // Left side of the tree
    glVertex2d(185, 140); // Top of the triangle
    glVertex2d(210, 105); // Right side of the tree
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(160, 115); // Left side of the second triangle
    glVertex2d(185, 150); // Top of the second triangle
    glVertex2d(210, 115); // Right side of the second triangle
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(160, 125); // Left side of the third triangle
    glVertex2d(185, 160); // Top of the third triangle
    glVertex2d(210, 125); // Right side of the third triangle
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(160, 135); // Left side of the fourth triangle
    glVertex2d(185, 170); // Top of the fourth triangle
    glVertex2d(210, 135); // Right side of the fourth triangle
    glEnd();

//-------------------------------Drawing Trees---------------------------------

    //Leaves(RIGHT)
    DrawCircle(462,100,20.5,105, 112, 16);
    DrawCircle(475,105,13,105, 112, 16);
    DrawCircle(470,120,11.5,105, 112, 16);
    DrawCircle(453,118,11.5,105, 112, 16);
    DrawCircle(445,114,11.5,105, 112, 16);
    DrawCircle(442,95,11.5,105, 112, 16);


    glBegin(GL_POLYGON);
    glColor3ub(58, 24, 10);
    glVertex2d(457.46505956786, 79.4529305369738);
    glVertex2d(465.7419618073546, 79.8235380999363);
    glVertex2d(470.3127884172247, 115.7724717072936);
    glVertex2d(461.418206906126, 92.5477310949803);
    glVertex2d(453.5119122295939, 107.9897128850822);
    glVertex2d(457.3415237135392, 87.6062969221476);
    glVertex2d(448.076334639478, 92.6712669493011);
    glVertex2d(457.46505956786, 79.4529305369738);
    glEnd();

    //Leaves( Left)
    glPushMatrix();
    glTranslatef(290,0,0);
    DrawCircle(462,100,20.5,105, 112, 16);
    DrawCircle(475,105,13,105, 112, 16);
    DrawCircle(470,120,11.5,105, 112, 16);
    DrawCircle(453,118,11.5,105, 112, 16);
    DrawCircle(445,114,11.5,105, 112, 16);
    DrawCircle(442,95,11.5,105, 112, 16);


    glBegin(GL_POLYGON);
    glColor3ub(58, 24, 10);
    glVertex2d(457.46505956786, 79.4529305369738);
    glVertex2d(465.7419618073546, 79.8235380999363);
    glVertex2d(470.3127884172247, 115.7724717072936);
    glVertex2d(461.418206906126, 92.5477310949803);
    glVertex2d(453.5119122295939, 107.9897128850822);
    glVertex2d(457.3415237135392, 87.6062969221476);
    glVertex2d(448.076334639478, 92.6712669493011);
    glVertex2d(457.46505956786, 79.4529305369738);
    glEnd();

    ///////////////////////////////////////------Triangular big tree---------------\\\\\\\\\\\\\\\\\\\\\\\\\\\

    //-------TRUNK-----//
    glBegin(GL_QUADS);
    glColor3ub(58, 24, 10);
    glVertex2d(1010,85);
    glVertex2d(1010,105);
    glVertex2d(1020,105);
    glVertex2d(1020,85);
    glEnd();
    //---Leaves by triangle----//
    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(990,105);
    glVertex2d(1015,140);
    glVertex2d(1040,105);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(990,115);
    glVertex2d(1015,150);
    glVertex2d(1040,115);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(990,125);
    glVertex2d(1015,160);
    glVertex2d(1040,125);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(990,135);
    glVertex2d(1015,170);
    glVertex2d(1040,135);
    glEnd();

    ///////////////////////////////////////------Triangular big tree on LEFT---------------\\\\\\\\\\\\\\\\\\\\\\\\\\\

    //-------TRUNK-----//
    glBegin(GL_QUADS);
    glColor3ub(58, 24, 10);
    glVertex2d(710, 85);  // Shifted to the left
    glVertex2d(710, 105);
    glVertex2d(720, 105);
    glVertex2d(720, 85);
    glEnd();

    //---Leaves by triangle----//
    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(690, 105); // Left side of the tree
    glVertex2d(715, 140); // Top of the triangle
    glVertex2d(740, 105); // Right side of the tree
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(690, 115); // Left side of the second triangle
    glVertex2d(715, 150); // Top of the second triangle
    glVertex2d(740, 115); // Right side of the second triangle
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(690, 125); // Left side of the third triangle
    glVertex2d(715, 160); // Top of the third triangle
    glVertex2d(740, 125); // Right side of the third triangle
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(105, 112, 16);
    glVertex2d(690, 135); // Left side of the fourth triangle
    glVertex2d(715, 170); // Top of the fourth triangle
    glVertex2d(740, 135); // Right side of the fourth triangle
    glEnd();

    glPopMatrix();
}

void DrawBus()
{

     glPushMatrix();
     glTranslatef(_moveBus,0.0,0.0);
    //-----------BUS--------------//
    glBegin(GL_POLYGON);
    glColor3ub(33, 43, 107);
    glVertex2d(80.25,58.0);
    glVertex2d(80.25,112.5);
    glVertex2d(201.5,112.5);
    glVertex2d(201.5,85.5);
    glVertex2d(210.0,85.5);
    glVertex2d(210.0,58.0);
    glVertex2d(80.25,58.0);
    glEnd();

    //----------Bus Windows----------//

    glBegin(GL_QUADS);
    glColor3ub(22, 52, 26);
    glVertex2d(80.25,85.5);
    glVertex2d(80.25,112.5);
    glVertex2d(201.5,112.5);
    glVertex2d(201.5,85.5);
    glEnd();

    //---------Window-1----------------//
    glBegin(GL_QUADS);
    glColor3ub(176, 196, 196);
    glVertex2d(84.25, 89.0);
    glVertex2d(84.25,110.0);
    glVertex2d(103.0,110);
    glVertex2d(103.0,89);
    glEnd();

    //----------Window-2--------------
    glBegin(GL_QUADS);
    glColor3ub(176, 196, 196);
    glVertex2d(106.0,89.0);
    glVertex2d(106.0,110);
    glVertex2d(125.0,110);
    glVertex2d(125.0,89.0);
    glEnd();

    //----------Window-3--------------
    glBegin(GL_QUADS);
    glColor3ub(176, 196, 196);
    glVertex2d(128.0,89.0);
    glVertex2d(128.0,110);
    glVertex2d(147.0,110);
    glVertex2d(147.0,89);
    glEnd();

    //---------------Bus Door----------
    glBegin(GL_QUADS);
    glColor3ub(176, 196, 196);
    glVertex2d(152.5,65);
    glVertex2d(152.5,110);
    glVertex2d(171.5,110);
    glVertex2d(171.5,65);
    glEnd();

    ///----------Bus Front Window------------
    glBegin(GL_QUADS);
    glColor3ub(176, 196, 196);
    glVertex2d(177.0,89.0);
    glVertex2d(177.0,110);
    glVertex2d(196.0,110);
    glVertex2d(196.0,89);
    glEnd();

    ///-----------Bus Wheels-------------------//

    glBegin(GL_POLYGON);///Wheel-1
    glColor3f(0.0, 0.0, 0.0);
    for (int i =0;i < 360;i++)
    {
        double theta;
        theta = i * 3.1416 / 180;
        glVertex2d(108+ 9.65* cos(theta), 57.5+ 9.65* sin(theta));
    }
    glEnd();

    glBegin(GL_POLYGON);///Wheel-1
    glColor3f(1.0, 1.0, 1.0);
    for (int i =0;i < 360;i++)
    {
        double theta;
        theta = i * 3.1416 / 180;
        glVertex2d(108+ 4.65* cos(theta), 57.5+ 4.65* sin(theta));
    }
    glEnd();


    glBegin(GL_POLYGON);///Wheel-2
    glColor3f(0.0, 0.0, 0.0);
    for (int i =0;i < 360;i++)
    {
        double theta;
        theta = i * 3.1416 / 180;
        glVertex2d(188.25+ 9.65* cos(theta), 57.5+ 9.65* sin(theta));
    }
    glEnd();
    glBegin(GL_POLYGON);///Wheel-2
    glColor3f(1.0, 1.0, 1.0);
    for (int i =0;i < 360;i++)
    {
        double theta;
        theta = i * 3.1416 / 180;
        glVertex2d(188.25+ 4.65* cos(theta), 57.5+ 4.65* sin(theta));
    }
    glEnd();
     glPopMatrix();
}

// Function to draw the car
void DrawCar()
{
    glPushMatrix();
    glTranslatef(_moveCar,0.0,0.0);
    glBegin(GL_POLYGON);
    glColor3ub(230, 150, 11);
    glVertex2d(1145,58);
    glVertex2d(1120,58);
    glVertex2d(1102,58);
    glVertex2d(1090,44);
    glVertex2d(1060,35);
    glVertex2d(1060,17);
    glVertex2d(1174,17);
    glVertex2d(1174,30);
    glVertex2d(1163,38);
    glVertex2d(1145,58);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 56, 64);
    glVertex2d(1091,40);
    glVertex2d(1104,40);
    glVertex2d(1104,55);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(49, 144, 151);
    glVertex2d(1095,40);
    glVertex2d(1104,40);
    glVertex2d(1104,50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0, 56, 64);
    glVertex2d(1106,40);
    glVertex2d(1143,40);
    glVertex2d(1143,55);
    glVertex2d(1106,55);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(49, 144, 151);
    glVertex2d(1106,40);
    glVertex2d(1139,40);
    glVertex2d(1139,50);
    glVertex2d(1106,50);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 56, 64);
    glVertex2d(1146,40);
    glVertex2d(1160,40);
    glVertex2d(1146,55);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(49, 144, 151);
    glVertex2d(1146,40);
    glVertex2d(1155,40);
    glVertex2d(1146,50);
    glEnd();

    //Wheel-1
    DrawCircle(1078,11,8,0,0,0);
    DrawCircle(1078,11,4,255,255,255);

    //wheel-2
    DrawCircle(1078+80,11,8,0,0,0);
    DrawCircle(1078+80,11,4,255,255,255);

    //Black and White lines
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2d(1060,28);
    glVertex2d(1175,28);
    glVertex2d(1175,30);
    glVertex2d(1060,30);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(1060,25);
    glVertex2d(1175,25);
    glVertex2d(1175,28);
    glVertex2d(1060,28);
    glEnd();


    glPopMatrix();
}

// Function to animate clouds
void Cloud_Move(int value)
{
    _moveCloud += _cloudSpeed;
    if (_moveCloud > 1366.0)
    {
        _moveCloud = -1000.0;
    }
    glutPostRedisplay();
    glutTimerFunc(20, Cloud_Move, 0);
}

// Function to animate the car
void Car_Move(int value)
{
    _moveCar -= _carSpeed;
    if (_moveCar < -1300.0f)
    {
        _moveCar = 250.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(20, Car_Move, 0);
}

void Bus_Move(int value)
{
    _moveBus += _busSpeed; // Move the bus to the right

    if (_moveBus > 1300.0f) // Bus moves off the right edge
    {
        _moveBus = -250.0f; // Reset to the left
    }

    glutPostRedisplay();
    glutTimerFunc(20, Bus_Move, 0); // Keep the loop running
}



// Function to initialize OpenGL settings
void myInit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1366.0, 0.0, 800.0);
}

void night_Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Night_Sky();
    stars();
    Night_Cloud();
    for (int i = 0; i < 3; ++i)
    {
        DrawSimpleBird(birdPositions[i], birdYPosition); // Draw birds in a row
    }

    // Update positions for animation
    UpdateBirdPosition();
    DrawBuildingA(true);
    DrawBuildingB(true);
    DrawBuildingC(true);
    DrawTrafficLight();
    DrawBuildingD(true);
    DrawBuildingE(true);
    DrawBuildingF(true);
    DrawBuildingG(true);
    DrawRoad();
    DrawTrees();
    DrawBus();
    DrawCar();
    rain_fall();


    glutSwapBuffers();
}


// Main display function
void day_Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Day_Sky();
    Day_cloud();
    for (int i = 0; i < 3; ++i)
    {
        DrawSimpleBird(birdPositions[i], birdYPosition); // Draw birds in a row
    }

    // Update positions for animation
    UpdateBirdPosition();
    DrawBuildingA(false);
    DrawBuildingB(false);
    DrawBuildingC(false);
    DrawTrafficLight();
    DrawBuildingD(false);
    DrawBuildingE(false);
    DrawBuildingF(false);
    DrawBuildingG(false);
    DrawRoad();
    DrawTrees();
    DrawBus();
    DrawCar();
    rain_fall();

    glutSwapBuffers();
}

void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        _cloudSpeed += 0.5f; // Increase speed
        _carSpeed += 0.5f; // Increase car speed
        _busSpeed+=0.5f;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        _cloudSpeed -= 0.5f; // Decrease speed
        _carSpeed -= 0.5f; // Decrease car speed
        _busSpeed -=0.5f;
        //if (_cloudSpeed < 0.0f) _cloudSpeed = 0.0f; // Prevent reverse movement
    }
    glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        _cloudSpeed = 0.0f; // Stop clouds
        _carSpeed = 0.0f; // Stop the car
        _busSpeed=0.0f;
        birdSpeed = 0.0f;
        break;
    case 'w':
        _cloudSpeed = 2.0f; // Resume with default speed
        _carSpeed = 2.5f; // Resume movement with default speed
        _busSpeed=2.5f;
        birdSpeed = 2.0f;

        break;

        static int pressCount = 0; // Static variable to keep track of the number of presses

    case 'r':
        pressCount++;
        isRain = !isRain;
        if (pressCount % 2 != 0)
        {
            sndPlaySound("rain.wav", SND_ASYNC);
        }
        else
        {
            sndPlaySound(NULL, SND_ASYNC);
        }
        break;

    case 'd':
        glutDisplayFunc(day_Display);
        break;
    case 'n':
        glutDisplayFunc(night_Display);
        break;
    }
    glutPostRedisplay(); // Request a redraw after key press
}


// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1520, 800);
    glutCreateWindow("Urban City Life");
    glutDisplayFunc(day_Display); /// default display
//    glutDisplayFunc(display);
    glutTimerFunc(20, Cloud_Move, 0);
    glutTimerFunc(20, Car_Move, 0);
    glutTimerFunc(20, Bus_Move, 0);
    myInit();
    glutMouseFunc(handleMouse);
    glutKeyboardFunc(handleKeypress); // Register keyboard handler
    glutTimerFunc(60, rain_update, 0); // Start the timer for rain updates
    glutMainLoop();
    return 0;
}
