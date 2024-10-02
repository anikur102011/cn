#include <GL/glut.h>
#include<windows.h>
#include <iostream>
#include<bits/stdc++.h>

using namespace std;


float x1, x2, y11, y2;

void init(void) {
    glClearColor(1.0, 1.0, 0.0, 0.0);
    gluOrtho2D(0, 100, 0, 100);
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);

    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y11);
    int stepx = (x1 < x2) ? 1 : -1;
    int stepy = (y11 < y2) ? 1 : -1;
    int p;

    int x = x1;
    int y = y11;
    float m = abs(dy / dx);

    if (m<1) {
        p = 2 * dy - dx;
        int steps = dx;

        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex2i(x, y);

        while (steps--) {
            if (p < 0) {
                p += 2 * dy;
            } else {
                y += stepy;
                p += 2 * (dy - dx);
            }
            x += stepx;
            glVertex2i(x, y);
        }

        glEnd();
    } else {
        // Line is more vertical
        p = 2 * dx - dy;
        int steps = dy;

        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex2i(x, y);

        while (steps--) {
            if (p < 0) {
                p += 2* dx;;
            } else {
                x += stepx;
                p += 2 * (dy - dx);
            }
            y += stepy;
            glVertex2i(x, y);
        }

        glEnd();
    }

    glFlush();
}


int main(int argc, char** argv) {

    cout<<"Enter x1 : ";
    cin>>x1;
    cout<<"Enter y11 : ";
    cin>>y11;
    cout<<"Enter x2 : ";
    cin>>x2;
    cout<<"Enter y2 : ";
    cin>>y2;


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Bresenham line draw");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
