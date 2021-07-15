#include <iostream>
#include <conio.h>
#include <windows.h>


bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int n_tail = 0;
enum e_dir { STOP = 0, LEFT, RIGHT, UP, DOWN };
e_dir dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    fruit_x = std::rand() % width;
    fruit_y = std::rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; ++i) {
        std::cout << "#";
    }
    std::cout << std::endl;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == 0) {
                std::cout << "#";
            }
            if (i == y && j == x) {
                std::cout << "O";
            }
            else if (i == fruit_y && j == fruit_x) {
                std::cout << "F";
            }
            else {
                bool print = false;
                for (int k = 0; k < n_tail; ++k) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        std::cout << "o";
                        print = true;
                        }
                }
                if (!print) {
                    std::cout << " ";
                }
            }
            if (j == width - 1) {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; ++i) {
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        default:
            gameOver = true;
        }
    }
}

void Logic() {
    
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    int prev2_x, prev2_y;
    tail_x[0] = x;
    tail_y[0] = y;
    
    for (int i = 1; i < n_tail; ++i) {
        prev2_x = tail_x[i];
        prev2_y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev2_x;
        prev_y = prev2_y;
    }
    switch (dir)
    {
    case LEFT:
        --x;
        break;
    case RIGHT:
        ++x;
        break;
    case UP:
        --y;
        break;
    case DOWN:
        ++y;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0) {
        gameOver = true;
    }
    for (int i = 0; i < n_tail; ++i) {
        if (tail_x[i] == x && tail_y[i] == y) {
            gameOver = true;
        }
    }
    if (x == fruit_x && y == fruit_y) {
     
        score += 10;
        fruit_x = std::rand() % width;
        fruit_y = std::rand() % height;
        ++n_tail;
    }
}
 
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }
    Sleep(1000000);  
    return 0;
}