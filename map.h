#ifndef _MAP_H_
#define _MAP_H_

#define HERO '@'
#define GHOST 'F'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'

struct map {
    char** matrix;
    int rows;
    int columns;
};

struct position {
    int x;
    int y;

};

typedef struct map MAP;
typedef struct position POSITION;



void allocateMap(MAP* m);
void readMap(MAP* m);
void freeMap(MAP* m);
int findMap(MAP*m, POSITION* p, char c);
int isValid(MAP* m, int x, int y);
int isEmpty(MAP* m, int x, int y);
int isWall(MAP* m, int x, int y);
int isPlayer(MAP* m, char player, int x, int y);
int canWalk(MAP* m, char player, int x, int y);
void walking(MAP* m, int xOrigin, int yOrigin, int xDestiny, int yDestiny);
void copyMap(MAP* destiny, MAP* origin);

#endif // _MAP_H_
