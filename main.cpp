#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#define HEI 20
#define WID 10
using namespace std;
///Tetris class
int Score = 0;
void drawText(const char *text, int length, int x, int y){
glMatrixMode(GL_PROJECTION);
double *matrix = new double[16];
glGetDoublev(GL_PROJECTION_MATRIX,matrix);
glLoadIdentity();
glOrtho(0,800,0,600,-5,5);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glPushMatrix();
glLoadIdentity();
glRasterPos2i(x,y);
for(int i = 0; i < length; i++){
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
}
glPopMatrix();
glMatrixMode(GL_PROJECTION);
glLoadMatrixd(matrix);
glMatrixMode(GL_MODELVIEW);
}
class Tetris {
public:
    Tetris();
    ~Tetris();

    void rand_tetris();

    // draw grid of Tetris
    void draw_grid();

    // draw seven difformity block
    void draw_tetris();

    // if the block collide a wall return 1, otherwise return 2
    int collision();

    bool over();

    void restart();

    void rotate();

    void remove_line();

    void move_left();
    void move_right();
    void move_down();

    int get_x();
    int get_y();

private:
    void update();

    GLfloat r;
    GLfloat g;
    GLfloat b;

    int __x;
    int __y;

    int __grid[HEI][WID];

    int __shape[4][4];
};

///implemnet of tetris clas

// I shape
const int __shape_I[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
};

// J shape
const int __shape_J[4][4] = {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
};

// L shape
const int __shape_L[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
};

// O shape
const int __shape_O[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
};

// S shape
const int __shape_S[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
};

// T shape
const int __shape_T[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
};

// Z shape
const int __shape_Z[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
};

Tetris::Tetris() : r(0.0), g(0.0), b(0.0), __x(3), __y(0)
{
    __shape[4][4] = {0};
    __grid[HEI][WID] = {0};

    rand_tetris();
}

Tetris::~Tetris()
{

}

void Tetris::rand_tetris()
{
    switch (rand() % 7) {
        case 0:
            memcpy(__shape, __shape_I, 4 * 4 * sizeof(int));
            r = 0.0;
            g = 1.0;
            b = 1.0;
            break;
        case 1:
            memcpy(__shape, __shape_J, 4 * 4 * sizeof(int));
            r = 0.0;
            g = 1.0;
            b = 0.0;
            break;
        case 2:
            memcpy(__shape, __shape_L, 4 * 4 * sizeof(int));
            r = 0.0;
            g = 0.0;
            b = 1.0;
            break;
        case 3:
            memcpy(__shape, __shape_O, 4 * 4 * sizeof(int));
            r = 1.0;
            g = 1.0;
            b = 0.0;
            break;
        case 4:
            memcpy(__shape, __shape_S, 4 * 4 * sizeof(int));
            r = 1.0;
            g = 0.0;
            b = 1.0;
            break;
        case 5:
            memcpy(__shape, __shape_T, 4 * 4 * sizeof(int));
            r = 1.0;
            g = 0.0;
            b = 0.0;
            break;
        case 6:
            memcpy(__shape, __shape_Z, 4 * 4 * sizeof(int));
            r = 1.0;
            g = 0.5;
            b = 1.0;
            break;
    }
}

void Tetris::draw_grid()
{
    //draw vertical lines
   /* for (int i = 0; i < WID * 8; i += 8) {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(i, 0);
        glVertex2f(i, HEI * 8);
        glEnd();
    }

    //draw horizontal lines
    for (int j = 0; j < HEI * 8; j += 8) {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(0, j);
        glVertex2f(WID * 8, j);
        glEnd();
    }*/

    for (int i = 0; i < HEI; i++) {
        for (int j = 0; j < WID; j++) {
            if (__grid[i][j] == 1) {
                int x_1 = j * 8;
                int y_1 = i * 8;
                int x_2 = x_1 + 8;
                int y_2 = y_1 + 8;

                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_QUADS);
                glVertex2f(x_1, y_1);
                glVertex2f(x_2, y_1);
                glVertex2f(x_2, y_2);
                glVertex2f(x_1, y_2);
                glEnd();

                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x_1, y_1);
                glVertex2f(x_2, y_1);
                glVertex2f(x_2, y_2);
                glVertex2f(x_1, y_2);
                glEnd();
            }
        }
    }
}

void Tetris::draw_tetris()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (__shape[i][j] == 1) {
                int x_1 = (j + __x) * 8;
                int y_1 = (i + __y) * 8;
                int x_2 = x_1 + 8;
                int y_2 = y_1 + 8;

                glColor3f(r, g, b);
                glBegin(GL_QUADS);
                glVertex2f(x_1, y_1);
                glVertex2f(x_2, y_1);
                glVertex2f(x_2, y_2);
                glVertex2f(x_1, y_2);
                glEnd();

                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x_1, y_1);
                glVertex2f(x_2, y_1);
                glVertex2f(x_2, y_2);
                glVertex2f(x_1, y_2);
                glEnd();
            }
        }
    }
}

int Tetris::collision()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (__shape[i][j] == 1) {
                int x_1 = __x + j;
                int y_1 = __y + i;

                // hit the wall
                if (x_1 < 0 || x_1 >= WID)
                    return 1;

                // hit the floor or other block
                else if (y_1 >= HEI || __grid[y_1][x_1] == 1)
                    return 2;
            }
        }
    }

    return -1;
}

void Tetris::update()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (__shape[i][j] == 1)
                __grid[__y + i][__x + j] = 1;
        }
    }

    __x = 3;
    __y = 0;

    rand_tetris();
}

void Tetris::rotate()
{
    int tmp[4][4] = {0};

    memcpy(tmp, __shape, 4 * 4 * sizeof(int));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            __shape[i][j] = tmp[3 - j][i];
        }
    }

    // if collision then don't rotate the block
    if (collision() != -1)
        memcpy(__shape, tmp, 4 * 4 * sizeof(int));
}

void Tetris::remove_line()
{
    for (int i = HEI - 1; i > 0; i--) {
        int count = 0;

        for (int j = 0; j < WID; j++) {
            if (__grid[i][j] == 1)
                count++;
        }

        if (count == 10){
            Score += 1;
            for (int t = i; t > 0; t--) {
                for (int k = 0; k < WID; k++)
                    __grid[t][k] = __grid[t - 1][k];
            }
            sndPlaySound("lineRemoveSound.wav",SND_SYNC);

        }

        }
    }



bool Tetris::over()
{
    for (int i = 0; i < WID; i++)
        if (__grid[4][i] == 1){
            sndPlaySound("gameOverSound.wav",SND_SYNC);
            return true;
        }


    return false;
}

void Tetris::restart()
{
    Score = 0;
    for (int i = 0; i < HEI; i++) {
        for (int j = 0; j < WID; j++) {
            __grid[i][j] = 0;
        }
    }

    __x = 3;
    __y = 0;

    rand_tetris();
}

void Tetris::move_down()
{
    __y++;

    // collision
    if (collision() == 2) {
        __y--;


        update();
    }
}

void Tetris::move_left()
{
    __x--;

    // collision
    if (collision() != -1)
        __x++;
}

void Tetris::move_right()
{
    __x++;

    // collision
    if (collision() != -1)
        __x--;
}

int Tetris::get_x()
{
    return __x;
}

int Tetris::get_y()
{
    return __y;
}

///Engine class

class Engine {
public:
    Engine();
    ~Engine();

    void run();

    // set normal key, such as ESC Space and so on
    void normal_key(unsigned char key, int x, int y);

    // set special key using glut
    void special_key(int key, int x, int y);

    int get_speed();

private:
    int speed;

    Tetris __tetris;
};
///implement of Engine class

Engine::Engine() : speed(200)
{
    srand(time(NULL));
}

Engine::~Engine()
{

}

void Engine::run()
{

    //sndPlaySound("2.wav",SND_LOOP);
    __tetris.remove_line();
    __tetris.draw_grid();
    __tetris.draw_tetris();

    __tetris.move_down();

    if (__tetris.over()){
            Score = 0;
            std::string str = "Score: " + std::to_string(Score);
            drawText(str.data(),str.size(),0,580);
            sndPlaySound("2.wav",SND_LOOP);
            __tetris.restart();
    }


}

int Engine::get_speed()
{
    return speed;
}

void Engine::normal_key(unsigned char key, int x, int y)
{
    switch (key) {
        // press ESC key to exit game
        case 27:
            exit(EXIT_SUCCESS);
            break;
        // press space key to restart game
        case 32:
            __tetris.restart();
            break;
        default:
            break;
    }
}

void Engine::special_key(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            __tetris.rotate();
            break;
        case GLUT_KEY_DOWN:
            __tetris.move_down();
            break;
        case GLUT_KEY_LEFT:
            __tetris.move_left();
            break;
        case GLUT_KEY_RIGHT:
            __tetris.move_right();
            break;
        default:
            break;
    }
}

Engine game;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    game.run();
    std::string str = "Score: " + std::to_string(Score);
    drawText(str.data(),str.size(),0,580);
    glutSwapBuffers();
}

void on_timer(int value)
{
    if (value == 0) {
        glutTimerFunc(game.get_speed(), on_timer, value);
        display();
    }
}

void normal_key(unsigned char key, int x, int y)
{
    game.normal_key(key, x, y);
}

void special_key(int key, int x, int y)
{
    game.special_key(key, x, y);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(300, 600);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("CGL Tetris Game");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 8 * WID, 8 * HEI, 0, 0, 1.0);
    glDisable(GL_DEPTH_TEST);


    //PlaySound(TEXT("2.wav"), NULL,SND_LOOP);


    glutDisplayFunc(display);
    glutKeyboardFunc(normal_key);
    glutSpecialFunc(special_key);

    glutTimerFunc(game.get_speed(), on_timer, 0);
    glutFullScreen();

    sndPlaySound("2.wav",SND_LOOP);
    glutMainLoop();

    return 0;
}
