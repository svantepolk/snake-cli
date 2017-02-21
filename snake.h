#include <stdint.h>

typedef struct {
    int x;
    int y;
} Point;

struct Snake {
    Point position;
    struct Snake* next;
    struct Snake* previous;
};

typedef struct Snake Snake;

// picked specifically so that the opposite direction = one's complement
#define UP 0x00
#define DOWN 0xFF
#define LEFT 0xF0
#define RIGHT 0x0F

