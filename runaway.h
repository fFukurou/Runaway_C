#ifndef _RUNAWAY_H_
#define _RUNAWAY_H_

#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
#define BOMB 'b'


void move(char direction);
int finished();

int isValidInput(char direction);
void ghosts();
int whereGhostGoes(int currentX, int currentY, int* xDestiny, int* yDestiny);
void explode();
void explode2(int x, int y, int sumX, int sumY, int amt);

#endif