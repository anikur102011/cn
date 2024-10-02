#include <GL/glut.h>
#include <windows.h>
#include <iostream>

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
        float dx = (x2 - x1);
        float dy = (y2 - y11);
        float m = abs((float)dy / dx);
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
        if (m <= 1) {
            cout << "m <= 1\n";
            if (dx > 0 && dy > 0) {
                cout << "Case : 1\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x += 1;
                    y += m;
                }
            } else if (dx < 0 && dy < 0) {
                cout << "Case : 2\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x -= 1;
                    y -= m;
                }
            } else if (dx >= 0 && dy < 0) {
                cout << "Case : 3\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x += 1;
                    y -= m;
                }
            } else if (dx < 0 && dy >= 0) {
                cout << "Case : 4\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x -= 1;
                    y += m;
                }
            }

        } else {
            cout << "m > 1\n";
            if (dx > 0 && dy > 0) {
                cout << "Case : 1\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x += 1 / m;
                    y += 1;
                }
            } else if (dx < 0 && dy < 0) {
                cout << "Case : 2\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x -= 1 / m;
                    y -= 1;
                }
            } else if (dx >= 0 && dy < 0) {
                cout << "Case : 3\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x += 1 / m;
                    y -= 1;
                }
            } else if (dx < 0 && dy >= 0) {
                cout << "Case : 4\n";
                float x = x1, y = y11;
                for (int i = 0; i <= steps; i++) {
                    cout<<x<<", "<<y<<endl;
                    glVertex2i(x, y);
                    x -= 1 / m;
                    y += 1;
                }
            }
        }
    glEnd();

    glFlush();
}

int main(int argc, char* argv[]) {


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
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Algorithm with m");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
