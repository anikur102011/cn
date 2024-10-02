#include <GL/glut.h>
#include <iostream>

using namespace std;

// Clipping window boundaries
double clipLeft = 20, clipBottom = 20, clipRight = 80, clipTop = 80;

// Region codes for the clipping window
const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

// Coordinates for the line input by the user
double lineX1, lineY1, lineX2, lineY2;

// Function to compute the region code for a point (x, y)
int computeRegionCode(double x, double y) {
    int code = INSIDE; // Start with the inside region code (0000)

    // Check each boundary and set the region code based on position
    if (x < clipLeft) {
        code = code + LEFT;  // Add the LEFT region code
    }

    if (x > clipRight) {
        code = code + RIGHT;  // Add the RIGHT region code
    }

    if (y < clipBottom) {
        code = code + BOTTOM;  // Add the BOTTOM region code
    }

    if (y > clipTop) {
        code = code + TOP;  // Add the TOP region code
    }

    return code;  // Return the final region code
}

// Cohen-Sutherland line clipping algorithm
void clipLine(double &x1, double &y1, double &x2, double &y2) {
    int code1 = computeRegionCode(x1, y1);
    int code2 = computeRegionCode(x2, y2);
    bool lineAccepted = false;

    while (true) {
        if (code1 == 0 && code2 == 0) {  // Both points are inside the clipping window
            lineAccepted = true;
            break;
        } else if ((code1 & code2) != 0) {  // Both points are outside in the same region
            break;
        } else {
            // One of the points is outside, calculate intersection
            double intersectX, intersectY;
            int outsideCode = (code1 != 0) ? code1 : code2;

            if (outsideCode & TOP) {  // Point is above the clip window
                intersectX = x1 + (x2 - x1) * (clipTop - y1) / (y2 - y1);
                intersectY = clipTop;
            } else if (outsideCode & BOTTOM) {  // Point is below the clip window
                intersectX = x1 + (x2 - x1) * (clipBottom - y1) / (y2 - y1);
                intersectY = clipBottom;
            } else if (outsideCode & RIGHT) {  // Point is to the right of the clip window
                intersectY = y1 + (y2 - y1) * (clipRight - x1) / (x2 - x1);
                intersectX = clipRight;
            } else if (outsideCode & LEFT) {  // Point is to the left of the clip window
                intersectY = y1 + (y2 - y1) * (clipLeft - x1) / (x2 - x1);
                intersectX = clipLeft;
            }

            // Replace the outside point with the intersection point
            if (outsideCode == code1) {
                x1 = intersectX;
                y1 = intersectY;
                code1 = computeRegionCode(x1, y1);
            } else {
                x2 = intersectX;
                y2 = intersectY;
                code2 = computeRegionCode(x2, y2);
            }
        }
    }

    if (lineAccepted) {
        glColor3f(0.0, 1.0, 0.0);  // Green for the clipped line
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
}

// OpenGL display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);

    // Draw the clipping window
    glColor3f(1.0, 1.0, 0.0);  // Yellow
    glBegin(GL_LINE_LOOP);
    glVertex2d(clipLeft, clipBottom);
    glVertex2d(clipRight, clipBottom);
    glVertex2d(clipRight, clipTop);
    glVertex2d(clipLeft, clipTop);
    glEnd();

    // Draw the original line
    glColor3f(1.0, 0.0, 0.0);  // Red
    glBegin(GL_LINES);
    glVertex2d(lineX1, lineY1);
    glVertex2d(lineX2, lineY2);
    glEnd();

    // Clip the line and draw the clipped part
    clipLine(lineX1, lineY1, lineX2, lineY2);

    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter the coordinates of the line (x1, y1, x2, y2): ";
    cin >> lineX1 >> lineY1 >> lineX2 >> lineY2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Line Clipping Algorithm");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
