#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "runaway.h"
#include "map.h"
#include "ui.h"


MAP m;
POSITION hero;
int hasPill = 0;

int whereGhostGoes(int currentX, int currentY, int* xDestiny, int* yDestiny) {
    int options[4][2] = {

        {currentX, currentY +1},
        {currentX +1, currentY},
        {currentX, currentY -1},
        {currentX -1, currentY}
    };


    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int position = rand() % 4;

        if (canWalk(&m, GHOST, options[position][0], options[position][1])){
            *xDestiny = options[position][0];
            *yDestiny = options[position][1];

            return 1;
        }

    }
    return 0;

}




void ghosts() {
    MAP copy;

    copyMap(&copy, &m);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.columns; j++) {
            if (copy.matrix[i][j] == GHOST) {

                int xDestiny;
                int yDestiny;

                int found = whereGhostGoes(i, j, &xDestiny, &yDestiny);

                if (found) {
                    walking(&m, i, j, xDestiny, yDestiny);
                }
            }
        }
    }
    freeMap(&copy);
}

int finished() {
    POSITION pos;
    int playerOnMap = findMap(&m, &pos, HERO);
    return !playerOnMap;
}

int isValidInput(char direction){
    return direction == 'w' ||
    direction == 'a' ||
    direction == 's' ||
    direction == 'd';
}

void move(char direction) {

    if (!isValidInput(direction))
        return;

    int nextX = hero.x;
    int nextY = hero.y;

    switch(direction) {
        case UP:
            nextX--;
            break;
        case LEFT:
            nextY--;
            break;
        case DOWN:
            nextX++;
            break;
        case RIGHT:
            nextY++;
            break;
    }
    if (!canWalk(&m, HERO, nextX, nextY))
        return;

    if (isPlayer(&m, PILL, nextX, nextY)) {
        hasPill = 1;
    }

    walking(&m, hero.x, hero.y, nextX, nextY);
    hero.x = nextX;
    hero.y = nextY;

}

void explode() {
    if (!hasPill) return;

    explode2(hero.x, hero.y, 0, 1, 3);
    explode2(hero.x, hero.y, 0, -1, 3);
    explode2(hero.x, hero.y, 1, 0, 3);
    explode2(hero.x, hero.y, -1, 0, 3);

    hasPill = 0;
}



void explode2(int x, int y, int sumX, int sumY, int amt) {

    if (amt == 0) return;

    int newX = x + sumX;
    int newY = y + sumY;


    if (!isValid(&m, newX, newY)) return;
    if (isWall(&m, newX, newY)) return;

    m.matrix[newX][newY] = EMPTY;
    explode2(newX, newY, sumX, sumY, amt - 1);
}


int main()
{

    readMap(&m);
    findMap(&m, &hero, HERO);

    do {
        printf("Has pill: %s\n", (hasPill ? "YES" : "NO"));
        printMap(&m);

        char command;
        scanf(" %c", &command);
        move(command);
        if (command == BOMB) explode();
        ghosts();
    } while (!finished());


    freeMap(&m);
    return 0;

}
