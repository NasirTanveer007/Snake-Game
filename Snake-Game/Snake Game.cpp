#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cstdlib>

// Structure to represent a 3D point
struct Point {
    float x, y, z;
    Point(float x, float y, float z) : x(x), y(y), z(z) {}
};

// Snake class
class Snake {
private:
    std::vector<Point> body;
    int length;
    float speed;
    float angle;

public:
    Snake(int initialLength, float initialSpeed)
        : length(initialLength), speed(initialSpeed), angle(0.0f) {
        // Initialize the snake body
        for (int i = 0; i < length; ++i) {
            body.push_back(Point(i, 0, 0));
        }
    }

    // Function to move the snake
    void move() {
        // Move the head
        body[0].x += speed * cos(angle);
        body[0].z += speed * sin(angle);

        // Move the body
        for (int i = length - 1; i > 0; --i) {
            body[i] = body[i - 1];
        }
    }

    // Function to change the direction of the snake
    void changeDirection(float newAngle) {
        angle = newAngle;
    }

    // Function to increase the length of the snake
    void increaseLength() {
        body.push_back(body[length - 1]);
        length++;
    }

    // Function to get the snake body
    std::vector<Point> getBody() const {
        return body;
    }
};

Snake snake(5, 0.1f);

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

    // Draw the snake
    glColor3f(0.0, 1.0, 0.0); // Green color
    std::vector<Point> body = snake.getBody();
    for (const auto& point : body) {
        glPushMatrix();
        glTranslatef(point.x, point.y, point.z);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// Timer function for game loop
void timer(int value) {
    snake.move();
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

// Keyboard function to handle arrow keys
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            snake.changeDirection(0.0f);
            break;
        case GLUT_KEY_DOWN:
            snake.changeDirection(180.0f);
            break;
        case GLUT_KEY_LEFT:
            snake.changeDirection(90.0f);
            break;
        case GLUT_KEY_RIGHT:
            snake.changeDirection(270.0f);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Snake Game");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}
