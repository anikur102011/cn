#include <GL/glut.h>
#include <windows.h>
#include<iostream>
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
        float dx = x2 - x1;
        float dy = y2 - y11;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
        float x = x1, y = y11;
        for (int i = 0; i <= steps; i++) {
            cout<<x<<", "<<y<<endl;
            glVertex2i(round(x),round(y));
            x += dx/steps;
            y += dy/steps;
        }

    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {

    cout<<"Enter x1 : ";
    cin>>x1;
    cout<<"Enter y1 : ";
    cin>>y11;
    cout<<"Enter x2 : ";
    cin>>x2;
    cout<<"Enter y2 : ";
    cin>>y2;



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Algorithm without m");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
