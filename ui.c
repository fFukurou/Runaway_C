#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "ui.h"


char wallDrawing[4][7] = {
	{"......" },
	{"......" },
	{"......" },
	{"......" }
};

char ghostDrawing[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

char heroDrawing[4][7] = {
	{" .--. "  },
	{"/ _.-'"  },
	{"\\  '-." },
	{" '--' "  }
};

char pillDrawing[4][7] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}
};

char emptyDrawing[4][7] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}
};

void printPart(char drawing[4][7], int part) {
	printf("%s", drawing[part]);
}

void printMap(MAP* m) {
	for(int i = 0; i < m->rows; i++) {

		for(int part = 0; part < 4; part++) {
			for(int j = 0; j < m->columns; j++) {

				switch(m->matrix[i][j]) {
					case GHOST:
						printPart(ghostDrawing, part);
						break;
					case HERO:
						printPart(heroDrawing, part);
						break;
					case PILL:
						printPart(pillDrawing, part);
						break;
					case VERTICAL_WALL:
					case HORIZONTAL_WALL:
						printPart(wallDrawing, part);
						break;
					case EMPTY:
						printPart(emptyDrawing, part);
						break;
				}

			}
			printf("\n");
		}

	}
}