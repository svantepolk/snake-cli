#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>

#include <ncurses.h>

#include "snake.h"

void draw(Snake*, Point*);

int main(void) {
    int rowc = 0;
    int colc = 0;
    
    // initialize ncurses
    initscr();
    noecho();
    raw();//cbreak();
    halfdelay(1);
    curs_set(0);
    keypad(stdscr, true);

    // initialize game objects
    Point apple = {0};
    Snake snakeHead = {0};
    Snake* snakeTail = &snakeHead;
    apple.x = 5;
    apple.y = 10;
        
    getmaxyx(stdscr, rowc, colc);
    
    snakeHead.position.x = colc / 2;
    snakeHead.position.y = rowc / 2;
    // start off moving upwards
    uint8_t snakeDirection = UP;

    uint8_t inputDirection = UP;
    while(true) {
        // collect input
        
        int c = getch();
	    switch (c) {
            case KEY_UP:
                inputDirection = UP;
                break;
            case KEY_DOWN:
                inputDirection = DOWN;
                break;
	        case KEY_LEFT:
                inputDirection = LEFT;
                break;
            case KEY_RIGHT:
                inputDirection = RIGHT;
                break;
        }
            
        // can't go immediately backwards
        if (inputDirection != ((uint8_t)~snakeDirection)) {
            snakeDirection = inputDirection;
        }

        int dx = 0;
        int dy = 0;

        switch (snakeDirection) {
            case UP:
                dy = -1;
                break;
            case DOWN:
                dy = 1;
                break;
            case LEFT:
                dx = -1;
                break;
            case RIGHT:
                dx = 1;
                break;
        }
        // move each piece before the head to the previous piece's spot
        Snake* snakePart = snakeTail;
        while (snakePart->previous != NULL) {
            int tempX = snakePart->previous->position.x;
            int tempY = snakePart->previous->position.y;
            
            snakePart->position.x = tempX;
            snakePart->position.y = tempY;

            snakePart = snakePart->previous;
        }
        // move the head
        snakeHead.position.x += dx;
        snakeHead.position.y += dy;

        // look for collisions
        if (snakeHead.position.x == apple.x && snakeHead.position.y == apple.y) {
            // grow the snake (it will be visible next iteration)
            Snake* newTail = malloc(sizeof(Snake));
            newTail->next = NULL;
            newTail->previous = snakeTail;
            newTail->position.x = snakePart->position.x;
            newTail->position.y = snakePart->position.y;
            snakeTail->next = newTail;
            snakeTail = newTail;
        }

        draw(&snakeHead, &apple);
        move(1, 1);
            printw(":%x", inputDirection);
            move(2, 1);
            printw(":%x", (uint8_t)~snakeDirection);       
        usleep(50000);
    }
    
    return 0;
}

void draw(Snake* snake, Point* apple) {
    int x = apple->x;
    int y = apple->y;
    erase();
    move(y, x);
    printw("@");
    
    while (snake != NULL) {
        x = snake->position.x;
        y = snake->position.y;
        move(y, x);
        printw("O");
        snake = snake->next;
    }
}
