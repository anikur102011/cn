#include <GL/glut.h>
#include<windows.h>
#include <iostream>

using namespace std;

int xCenter, yCenter, radius;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);

    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    glVertex2i(xCenter + x, yCenter + y);
    glVertex2i(xCenter - x, yCenter + y);
    glVertex2i(xCenter + x, yCenter - y);
    glVertex2i(xCenter - x, yCenter - y);
    glVertex2i(xCenter + y, yCenter + x);
    glVertex2i(xCenter - y, yCenter + x);
    glVertex2i(xCenter + y, yCenter - x);
    glVertex2i(xCenter - y, yCenter - x);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        glVertex2i(xCenter + x, yCenter + y);
        glVertex2i(xCenter - x, yCenter + y);
        glVertex2i(xCenter + x, yCenter - y);
        glVertex2i(xCenter - x, yCenter - y);
        glVertex2i(xCenter + y, yCenter + x);
        glVertex2i(xCenter - y, yCenter + x);
        glVertex2i(xCenter + y, yCenter - x);
        glVertex2i(xCenter - y, yCenter - x);
    }

    glEnd();
    glFlush();
}



void init(void) {
    glClearColor(1.0, 1.0, 0.0, 0.0);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char ** argv) {

    cout<<"Radius r : ";
    cin>> radius;
    cout<<"Center x : ";
    cin>> xCenter;
    cout<<"Center y : ";
    cin>> yCenter;

    glutInit( & argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Circle");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
}

