#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

int numVertices;
float originalX[100], originalY[100];  // Arrays to store original vertices
float transformedX[100], transformedY[100];  // Arrays to store transformed vertices

void drawPolygon(float x[], float y[]) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i) {
        glVertex2f(x[i], y[i]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // Red for original polygon
    drawPolygon(originalX, originalY);

    glColor3f(0.0, 1.0, 0.0); // Green for transformed polygon
    drawPolygon(transformedX, transformedY);

    glFlush();
}

void initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-100, 100, -100, 100);
}

void applyTranslation(float tx, float ty) {
    for (int i = 0; i < numVertices; ++i) {
        transformedX[i] = originalX[i] + tx;
        transformedY[i] = originalY[i] + ty;
    }
}

void applyScaling(float sx, float sy, float fx, float fy) {
    for (int i = 0; i < numVertices; ++i) {
        transformedX[i] = (originalX[i] - fx) * sx + fx;
        transformedY[i] = (originalY[i] - fy) * sy + fy;
    }
}

void applyRotation(float angle, int pivotX, int pivotY) {
    float radianAngle = (angle * 3.1416) / 180.0;
    for (int i = 0; i < numVertices; ++i) {
        float translateX = originalX[i] - pivotX;
        float translateY = originalY[i] - pivotY;

        transformedX[i] = translateX * cos(radianAngle) - translateY * sin(radianAngle) + pivotX;
        transformedY[i] = translateX * sin(radianAngle) + translateY * cos(radianAngle) + pivotY;
    }
}

void applyReflection(char option) {
    for (int i = 0; i < numVertices; ++i) {
        if (option == 'a') {
            transformedX[i] = originalX[i];
            transformedY[i] = -originalY[i];
        } else if (option == 'b') {
            transformedX[i] = -originalX[i];
            transformedY[i] = originalY[i];
        } else if (option == 'c') {
            transformedX[i] = -originalX[i];
            transformedY[i] = -originalY[i];
        } else {
            transformedX[i] = originalY[i];
            transformedY[i] = originalX[i];
        }
    }
}

void applyShearing(float sh, char option) {
    for (int i = 0; i < numVertices; ++i) {
        if (option == 'X') {
            transformedX[i] = originalX[i] + sh * originalY[i];
            transformedY[i] = originalY[i];
        } else {
            transformedX[i] = originalX[i];
            transformedY[i] = originalY[i] + sh * originalX[i];
        }
    }
}

int main(int argc, char** argv) {
    cout << "2D Geometric Transformation" << endl;
    cout << "........................................" << endl;
    cout << "1. Translation " << endl;
    cout << "2. Scaling (Fixed Point)" << endl;
    cout << "3. Rotation (Rotation / Pivot Point)" << endl;
    cout << "4. Reflection " << endl;
    cout << "5. Shearing" << endl;
    cout << "6. Quit" << endl;
    cout << "Enter your option: ";
    int option;
    cin >> option;

    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    for (int i = 0; i < numVertices; ++i) {
        cout << "Enter the coordinates of vertex " << i + 1 << " (x y): ";
        cin >> originalX[i] >> originalY[i];
    }

    switch (option) {
        case 1: {
            float tx, ty;
            cout << "Enter translation factors (tx ty): ";
            cin >> tx >> ty;
            applyTranslation(tx, ty);
            break;
        }
        case 2: {
            float sx, sy, fx, fy;
            cout << "Enter scaling factors (sx sy): ";
            cin >> sx >> sy;
            cout << "Enter fixed point (fx fy): ";
            cin >> fx >> fy;
            applyScaling(sx, sy, fx, fy);
            break;
        }
        case 3: {
            float angle, xr, yr;
            cout << "Enter the angle of rotation: ";
            cin >> angle;
            cout << "Enter the pivot point (xr yr): ";
            cin >> xr >> yr;
            applyRotation(angle, xr, yr);
            break;
        }
        case 4: {
            char axis;
            cout << "Enter the axis of reflection (a: x-axis, b: y-axis, c: origin, d: x=y): ";
            cin >> axis;
            applyReflection(axis);
            break;
        }
        case 5: {
            float sh;
            char axis;
            cout << "Enter the shearing factor (X: x-axis, Y: y-axis): ";
            cin >> axis;
            cout << "Enter shearing value: ";
            cin >> sh;
            sh=(sh*3.1416)/180.0;
            applyShearing(sh, axis);
            break;
        }
        default:
            cout << "Invalid option" << endl;
            return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Transformation");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
