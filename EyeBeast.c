
/*
max width = 80 columns
tab = 4 spaces
01234567890123456789012345678901234567890123456789012345678901234567890123456789
*/

/*	Linguagens e Ambientes de Programação - Projeto de 2021/2022
	Eye Beast
	Program written in C/C ++ over the wxWidget platform.
	The wxWidget platform runs on Windows, MacOS and Linux.
	This file is only a starting point fo your work. The entire file can
	be changed, starting with this comment.
 AUTHORS IDENTIFICATION
    Student 1: 60180, João Pereira
    Student 2: 59213, Pedro Grilo
Comments:
******************************************************************************
Extra functionalities:
Extra functionalities:
    - When the hero catches the mystery box it spawns random features.
        - Options:
            - Add a new Monster to the game
            - Remove a monster from the game
            - The player gains a point of life
            - Increase the monsters' speed (+Speed)
            - Decreases the monsters' speed (-Speed)

    - How mystery box works?
        - A Mystery box appears every 6 seconds;
        - If the hero doesn't catch it in 6 seconds, it disappears and
        spawns again after another 6 seconds;
        - If the hero catches it, one of the random features written above will
        be triggered.
            - When the feature is triggered, it is executed for 6 seconds,
            and then,a new Mystery Box appears.
*******************************************************************************

 Place here the names and numbers of the authors, plus some comments, as
 asked in the listing of the project. Do not deliver an anonymous file with
 unknown authors.
*/

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* IDENTIFICATION */

#define APP_NAME    "Eye Beast"

#define AUTHOR1        "Joao Pereira (60180)"
#define AUTHOR2        "Pedro Grilo (59213)"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* INCLUDES */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "wxTiny.h"


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* STRINGS */

#define MAX_STRING    256
#define MAX_LINE    1024

typedef char String[MAX_STRING];
typedef char Line[MAX_LINE];


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* IMAGES */

/******************************************************************************
 * The images are specified in the XPM format [http://en.wikipedia.org/wiki/X_PixMap]
 * After created, each image is represented by an integer in the wxTiny library.
 ******************************************************************************/

typedef int Image;

static Image emptyImg, heroImg, chaserImg, blockImg, boundaryImg, invalidImg,
                mysteryBoxImg;


/* XPM */
static tyImage empty_xpm = {
        "16 16 2 1",
        "   c None",
        ".  c #FFFFFF",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................"};

/* XPM */
static tyImage hero_xpm = {
        "16 16 3 1",
        "   c None",
        ".  c #FFFFFF",
        "+  c #000000",
        "................",
        "...+++...+++....",
        "..+...+.+...+...",
        ".+.....+.....+..",
        ".+...+++++...+..",
        ".+...+++++...+..",
        ".+...+++++...+..",
        ".+.....+.....+..",
        "..+...+.+...+...",
        "...+++...+++....",
        "................",
        ".....+++++......",
        "....+.....+.....",
        "................",
        "................",
        "................"};


/* XPM */
static tyImage chaser_xpm = {
        "16 16 3 1",
        "   c None",
        ".  c #FFFFFF",
        "+  c #000000",
        "................",
        "...+++...+++....",
        "..++.++.+.+++...",
        ".+..+++++++..+..",
        ".+...+++++...+..",
        ".+...+++++...+..",
        ".+...+++++...+..",
        "..+...+.+...+...",
        "...+++...+++....",
        "................",
        "................",
        "....+++++++.....",
        "................",
        "................",
        "................",
        "................"};

/* XPM */
static tyImage block_xpm = {
        "16 16 3 1",
        "   c None",
        ".  c #000000",
        "+  c #FFFFFF",
        "................",
        "................",
        "..............+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "................",
        "..+.+.+.+.+.+.+.",
        "................"};

static tyImage mysteryBox_xpm = {
        "16 16 4 1",
        "     c None",
        ".    c #000000",
        "+    c #FFFFFF",
        "@    c #FFE400",
        "................",
        ".+.@@@@@@@@@@.+.",
        "...@........@...",
        ".@@..+++++++.@@.",
        ".@@.++....++.@@.",
        ".@@.+.@@@@.+.@@.",
        ".@@...@@..++.@@.",
        ".@@@@@@.+++..@@.",
        ".@@@@@.++..@@@@.",
        ".@@@@@.++.@@@@@.",
        ".@@@@@@..@@@@@@.",
        ".@@@@@....@@@@@.",
        ".@@@@@.++.@@@@@.",
        "...@@@....@@@...",
        ".+.@@@@@@@@@@.+.",
        "................"};

/* XPM */
static tyImage boundary_xpm = {
        "16 16 3 1",
        "   c None",
        ".  c #000000",
        "+  c #FFFFFF",
        "................",
        "................",
        "..............+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "....+.+.+.+.+...",
        "...+.+.+.+.+..+.",
        "................",
        "..+.+.+.+.+.+.+.",
        "................"};

/* XPM */
static tyImage invalid_xpm = {
        "16 16 2 1",
        "   c None",
        ".  c #FFFFFF",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................",
        "................"};


/******************************************************************************
 * imagesCreate - Converts all the XPM images to the type Image
 ******************************************************************************/
void imagesCreate(void) {
    emptyImg = tyCreateImage(empty_xpm);
    heroImg = tyCreateImage(hero_xpm);
    chaserImg = tyCreateImage(chaser_xpm);
    blockImg = tyCreateImage(block_xpm);
    boundaryImg = tyCreateImage(boundary_xpm);
    mysteryBoxImg = tyCreateImage(mysteryBox_xpm);
    invalidImg = tyCreateImage(invalid_xpm);
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* ACTORS */

/******************************************************************************
 * Constants, types and functions for all kinds of actors
 ******************************************************************************/

#define ACTOR_PIXELS_X    16
#define ACTOR_PIXELS_Y    16
#define DEFAULT_N_MONSTERS    5
#define MAX_N_MONSTERS    20
#define MAX_OPTIONS_MYSTERY_BOX 5
#define DEFAULT_HERO_LIFES 1
#define DEFAULT_MONSTER_SPEED 10
#define NUMBER_MAX_BLOCKS 110;
#define COOLDOWN_MYSTERY_BOX 6
#define FASTER_VELOCITY 5
#define SLOW_VELOCITY 20

#define MAX_MONSTERS_EXCEDED "MAXIMUM"

const char *randomRandomEvents[MAX_OPTIONS_MYSTERY_BOX] = {"-1 ENEMY",
                                                           "+1 ENEMY", "+1 ♥",
                                                           "+SPEED", "-SPEED"};

typedef enum {
    EMPTY, HERO, CHASER, BLOCK, BOUNDARY, MYSTERY_BOX
} ActorKind;


typedef struct {
// specific fields can go here, but probably none will be needed
    int heroLifes;
} Hero;

typedef struct {
// specific fields can go here, but probably none will be needed
    int monsterSpeed;
} Chaser;

typedef struct {
// specific fields can go here, but probably none will be needed
} Block;

typedef struct {
// specific fields can go here, but probably none will be needed
} Boundary;
typedef struct {
// specific fields can go here, but probably none will be needed
} MysteryBox;

typedef struct {
// factored common fields
    ActorKind kind;
    int x, y;
    Image image;
    bool isPushable;
    union {
// specific fields for each kind
        Hero hero;
        Chaser chaser;
        Block block;
        Boundary boundary;
        MysteryBox mysteryBox;
    } u;
} ActorStruct, *Actor;

#define WORLD_SIZE_X    31
#define WORLD_SIZE_Y    18


typedef struct {
    Actor world[WORLD_SIZE_X][WORLD_SIZE_Y];
    Actor hero;
    Actor monsters[MAX_N_MONSTERS];
    Actor mysteryBox;
    int numberOfMonsters;
    char *lastRandomEvent;
    int monsterCounter;
    bool mysteryBoxPlaced;
    int mysteryBoxTimePlaced;
    int mysteryBoxTimeHide;
    int lastActionTime;

} GameStruct, *Game;

/******************************************************************************
 * actorImage - Get the screen image corresponding to some kind of actor
 ******************************************************************************/
Image actorImage(ActorKind kind) {
    switch (kind) {
        case EMPTY:
            return emptyImg;
        case HERO:
            return heroImg;
        case CHASER:
            return chaserImg;
        case BLOCK:
            return blockImg;
        case BOUNDARY:
            return boundaryImg;
        case MYSTERY_BOX:
            return mysteryBoxImg;
        default:
            return invalidImg;
    }
}

/******************************************************************************
 * cellSet - Useful function to update one cell in the matrix and in the screen
 ******************************************************************************/
void cellSet(Game g, Actor a, int x, int y, Image img) {
    tyDrawImage(img, x * ACTOR_PIXELS_X, y * ACTOR_PIXELS_Y);
    g->world[x][y] = a;
}

/******************************************************************************
 * cellIsEmpty - Check in the matrix if a cell is empty (if contains NULL)
 ******************************************************************************/
bool cellIsEmpty(Game g, int x, int y) {
    return g->world[x][y] == NULL;
}

/******************************************************************************
 * actorShow - Install an actor in the matrix and in the screen
 ******************************************************************************/
void actorShow(Game g, Actor a) {
    cellSet(g, a, a->x, a->y, a->image);
}

/******************************************************************************
 * actorHide - Removes an actor from the matrix and from the screen
 ******************************************************************************/
void actorHide(Game g, Actor a) {
    cellSet(g, NULL, a->x, a->y, emptyImg);
}

/******************************************************************************
 * actorMove - Move an actor to a new position
 * pre: the new position is empty
 ******************************************************************************/
void actorMove(Game g, Actor a, int nx, int ny) {
    actorHide(g, a);
    a->x = nx;
    a->y = ny;
    actorShow(g, a);
}

/******************************************************************************
 * actorNew - Creates a new actor and installs it in the matrix and the screen
 ******************************************************************************/

Actor actorNew(Game g, ActorKind kind, int x, int y, bool isPushable) {
    Actor a = malloc(sizeof(ActorStruct));
    a->kind = kind;
    a->x = x;
    a->y = y;
    a->image = actorImage(kind);
    a->isPushable = isPushable;
    actorShow(g, a);
    return a;
}

void generateCoordinates(Game g, int *coordinates, bool empty) {
    do {
        coordinates[0] = tyRand(WORLD_SIZE_X - 2) + 1;
        coordinates[1] = tyRand(WORLD_SIZE_Y - 2) + 1;
    } while (cellIsEmpty(g, coordinates[0], coordinates[1]) != empty);
}

/******************************************************************************
 * checkIfMoveIsPossible - Check if actor is pushable or not
 *******************************************************************************/
bool checkIfMoveIsPossible(Game g, int dx, int dy, int nx, int ny, int appendX,
                           int appendY) {
    return !(!cellIsEmpty(g, nx + appendX, ny) && dx > 0 &&
             !g->world[nx + appendX][ny]->isPushable ||
             !cellIsEmpty(g, nx - appendX, ny) && dx < 0 &&
             (!g->world[nx - appendX][ny]->isPushable) ||
             !cellIsEmpty(g, nx, ny + appendY) && dy > 0 &&
             (!g->world[nx][ny + appendY]->isPushable) ||
             !cellIsEmpty(g, nx, ny - appendY) && dy < 0 &&
             (!g->world[nx][ny - appendY]->isPushable));
}

/******************************************************************************
 * killMonster - Method created to kill monsters and remove
 * from array of monsters
 * EXTRA FUNCTIONALITY
 *******************************************************************************/
void killMonster(Game g) {
    Actor toKill = g->monsters[(g->numberOfMonsters) - 1];
    actorHide(g, toKill);
    g->monsters[g->numberOfMonsters--] = NULL;
}

/******************************************************************************
 * addMonster - Method created to add monsters in random cell
 * EXTRA FUNCTIONALITY
 *******************************************************************************/
void addMonster(Game g) {
    if (g->numberOfMonsters + 1 <= MAX_N_MONSTERS) {
        int coord[2];
        generateCoordinates(g, coord, true);
        Actor newMonster = actorNew(g, CHASER, coord[0], coord[1],
                                    false);
        g->monsters[g->numberOfMonsters] = newMonster;
        g->monsters[g->numberOfMonsters++]->u.chaser.monsterSpeed = DEFAULT_MONSTER_SPEED;
    }


}


/******************************************************************************
 * addOneLife - Method created to add 1 heart to hero life
 * EXTRA FUNCTIONALITY
 *******************************************************************************/
void addOneLife(Game g) {
    g->hero->u.hero.heroLifes++;
}

/******************************************************************************
 * setMonstersVelocity - Method created to setSpeed
 * EXTRA FUNCTIONALITY
 *******************************************************************************/
void setMonstersVelocity(Game g, int velocity) {
    for (int i = 0; i < g->numberOfMonsters; i++)
        g->monsters[i]->u.chaser.monsterSpeed = velocity;
}


/******************************************************************************
 * executeMysteryBoxOptions - Method used to call different option when hero catch the mysteryBox
 * EXTRA FUNCTIONALITY
 *******************************************************************************/
void executeMysteryBoxOptions(Game g, int n) {
    switch (n) {
        case 0:
            killMonster(g);
            break;
        case 1:
            addMonster(g);
            break;
        case 2:
            addOneLife(g);
            break;
        case 3:
            setMonstersVelocity(g, FASTER_VELOCITY);
            break;
        case 4:
            setMonstersVelocity(g, SLOW_VELOCITY);
            break;
        default:
            break;
    }

    g->mysteryBoxTimeHide = tySeconds();
    g->lastActionTime = tySeconds();
}

/******************************************************************************
 * heroAnimation - The hero moves using the cursor keys
 ******************************************************************************/
void heroAnimation(Game g, Actor a) {
    int dx = tyKeyDeltaX(), dy = tyKeyDeltaY();

    int nx = a->x + dx, ny = a->y + dy;
    int appendX = 0, appendY = 0;
    bool isMysteryBox = false;
    if (cellIsEmpty(g, nx, ny)) {
        actorMove(g, a, nx, ny);
    } else {
        if (g->world[nx][ny]->kind == MYSTERY_BOX) {
            int n = tyRand(MAX_OPTIONS_MYSTERY_BOX);
            executeMysteryBoxOptions(g, n);
            g->lastRandomEvent = randomRandomEvents[n];
            printf("CHEERY: %s\n", randomRandomEvents[n]);
            g->mysteryBoxPlaced = false;
            g->mysteryBox = NULL;
            isMysteryBox = true;
        }
        if (g->world[nx][ny]->kind == BLOCK) {
            int existsBlock = 1;
            while (existsBlock == 1) {
                if ((dx > 0 && !cellIsEmpty(g, nx + appendX, ny) &&
                     g->world[nx + appendX][ny]->kind == BLOCK) //direita
                    || dx < 0 && !cellIsEmpty(g, nx - appendX, ny) &&
                       g->world[nx - appendX][ny]->kind == BLOCK)  //esquerda
                    appendX = appendX + 1;
                else if ((dy > 0 && !cellIsEmpty(g, nx, ny + appendY) &&
                          g->world[nx][ny + appendY]->kind == BLOCK) //cima
                         || dy < 0 && !cellIsEmpty(g, nx, ny - appendY) &&
                            g->world[nx][ny - appendY]->kind == BLOCK) //baixo
                    appendY = appendY + 1;
                else //none
                    existsBlock = 0;
            }

        }

        if (checkIfMoveIsPossible(g, dx, dy, nx, ny, appendX, appendY) ||
            isMysteryBox) {
            actorMove(g, g->world[nx][ny],
                      dx > 0 ? nx + appendX : dx < 0 ? nx - appendX : nx,
                      dy > 0 ? ny + appendY : dy < 0 ? ny - appendY : ny);
            actorMove(g, a, nx, ny);
        }

    }
}

/******************************************************************************
 * heroInCell - Check if hero is in cell with x and y
 ******************************************************************************/
bool heroInCell(int x, int y, Actor a) {
    if ((y == a->y) && x == a->x)
        return true;
    return false;
}

/******************************************************************************
 * chaserCanMove - Check if hero can move it
 ******************************************************************************/
bool chaserCanMove(Game g, int x, int y) {
    return cellIsEmpty(g, x, y) || heroInCell(x, y, g->hero);
}

/******************************************************************************
 * horizontalWay - Assistant method to move monsters horizontally
 ******************************************************************************/
int horizontalWay(Game g, Actor a) {
    int heroX = g->hero->x;
    int result = 0;
    if (heroX < a->x)
        result = -1;

    if (heroX > a->x)
        result = 1;

    return result;
}

/******************************************************************************
 * verticalWay - Assistant method to move monsters verticalWay
 ******************************************************************************/
int verticalWay(Game g, Actor a) {
    int heroX = g->hero->y;
    int result = 0;
    if (heroX < a->y)
        result = -1;

    if (heroX > a->y)
        result = 1;

    return result;
}

/******************************************************************************
 * chaserAnimation - Method to move monsters to catch the player
 ******************************************************************************/
void chaserAnimation(Game g, Actor a) {

    if (chaserCanMove(g, a->x + horizontalWay(g, a),
                         a->y + verticalWay(g, a)))

        actorMove(g, a, a->x + horizontalWay(g, a),
                        a->y + verticalWay(g, a));

    else {
        int randX = a->x + tyRand(2);
        int randY = a->y + tyRand(2);
        if (chaserCanMove(g, randX, randY))
            actorMove(g, a, randX, randY);
    }
}


/******************************************************************************
 * actorAnimation - The actor behaves according to its kind
 ******************************************************************************/
void actorAnimation(Game g, Actor a) {
    switch (a->kind) {
        case HERO:
            heroAnimation(g, a);
            g->monsterCounter = g->monsterCounter + 1;
            break;
        case CHASER:
            chaserAnimation(g, a);
            break;
        default:
            break;
    }

}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* GAME */

/******************************************************************************
 * gameClearWorld - Clears the matrix and the screen
 ******************************************************************************/
void gameClearWorld(Game g) {
    for (int y = 0; y < WORLD_SIZE_Y; y++)
        for (int x = 0; x < WORLD_SIZE_X; x++)
            cellSet(g, NULL, x, y, emptyImg);
}

/******************************************************************************
 * gameInstallBoundaries - Install the boundary blocks
 ******************************************************************************/
void gameInstallBoundaries(Game g) {
    for (int y = 0; y < WORLD_SIZE_Y; y++)
        for (int x = 0; x < WORLD_SIZE_X; x++)
            if (x == 0 || x == WORLD_SIZE_X - 1
                || y == 0 || y == WORLD_SIZE_Y - 1) {
                actorNew(g, BOUNDARY, x, y, false);
            }
}


/******************************************************************************
 * gameInstallBlocks - Install the movable blocks
 ******************************************************************************/
void gameInstallBlocks(Game g) {
    int i = 0;
    int max = NUMBER_MAX_BLOCKS
    while (i < max) {
        int coord[2];
        generateCoordinates(g, coord, true);
        actorNew(g, BLOCK, coord[0], coord[1], true);
        i++;
    }
}

/******************************************************************************
 * gameInstallMonsters - Install the monsters
 ******************************************************************************/
void gameInstallMonsters(Game g) {
    int i = 0;
    while (i < DEFAULT_N_MONSTERS) {
        addMonster(g);
        i++;
    }
}

/******************************************************************************
 * gameInstallMysteryBox - To install mysteryBox's in empty cell
 ******************************************************************************/
void gameInstallMysteryBox(Game g) {
    int coord[2];
    generateCoordinates(g, coord, true);
    g->mysteryBox = actorNew(g, MYSTERY_BOX, coord[0], coord[1],
                             false);
    g->mysteryBoxPlaced = true;
}

/******************************************************************************
 * gameInstallHero - Install the hero
 ******************************************************************************/
void gameInstallHero(Game g) {
    int counterMonsters = 0;
    int coord[2];
    while (counterMonsters < g->numberOfMonsters) {
        counterMonsters = 0;
        generateCoordinates(g, coord, true);
        for (int i = 0; i < g->numberOfMonsters; i++) {
            if (tyDistance(g->monsters[i]->x, g->monsters[i]->y, coord[0],
                           coord[1]) > 4)
                counterMonsters++;
        }
    }

    g->hero = actorNew(g, HERO, coord[0], coord[1], false);
    g->hero->u.hero.heroLifes = DEFAULT_HERO_LIFES;
}

/******************************************************************************
 * gameInitVariables - To init variables
 ******************************************************************************/
void gameInitVariables(Game g) {
    g->mysteryBoxPlaced = false;
    g->lastActionTime = 0;
    g->lastRandomEvent = "";
    g->numberOfMonsters = 0;
    g->mysteryBoxTimePlaced = 0;
    g->mysteryBoxTimeHide = 0;
}

/******************************************************************************
 * gameInit - Initialize the matrix and the screen
 ******************************************************************************/
Game gameInit(Game g) {
    if (g == NULL)
        g = malloc(sizeof(GameStruct));
    gameInitVariables(g);
    imagesCreate();
    gameClearWorld(g);
    gameInstallBoundaries(g);
    gameInstallBlocks(g);
    gameInstallMonsters(g);
    gameInstallHero(g);
    return g;
}

/******************************************************************************
 * gameRedraw - Redraws the entire RandomEvent. This function is called by
 * tyHandleRedraw in very specific circumstances. It should not be used anywhere
 * else because you don't want to be constantly redrawing the whole RandomEvent.
 ******************************************************************************/
void gameRedraw(Game g) {
    for (int y = 0; y < WORLD_SIZE_Y; y++)
        for (int x = 0; x < WORLD_SIZE_X; x++) {
            Actor a = g->world[x][y];
            if (!cellIsEmpty(g, x, y))
                actorShow(g, a);
        }
}


/******************************************************************************
 * checkDeath - Method to check if someone monster belongs to hero cell,
 * if its true,hero dead, else, alive!
 ******************************************************************************/
bool checkDeath(Game g, Actor a) {
    for (int i = 0; i < g->numberOfMonsters; i++) {
        if (tyDistance(a->x, a->y, g->monsters[i]->x, g->monsters[i]->y) == 0)
            return true;
    }
    return false;
}

/******************************************************************************
 * checkIfIsTrapped - Method to check if someone monsters are trapped
 * in 9 around cells
 ******************************************************************************/
bool checkIfIsTrapped(Game g, Actor a) {
    int counter = 0;
    int N_CELLS_TO_TRAP = 9;
    int actorX = a->x;
    int actorY = a->y;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (!cellIsEmpty(g, actorX + i, actorY + j))
                counter++;
        }
    }
    if (counter == N_CELLS_TO_TRAP) return true;
    return false;
}

/******************************************************************************
 * removeLife - Method to remove 1 life from hero
 ******************************************************************************/
void removeLife(Game g, Actor a) {
    int coord[2];
    generateCoordinates(g, coord, true);
    actorMove(g, a, coord[0], coord[1]);
    g->hero->u.hero.heroLifes--;
}

/******************************************************************************
 * allTrapped - Check if all monsters are trapped
 ******************************************************************************/

bool allTrapped(Game g) {
    int counter = 0;
    for (int i = 0; i < g->numberOfMonsters; i++) {
        if (checkIfIsTrapped(g, g->monsters[i]))
            counter++;
    }
    if (counter == g->numberOfMonsters)
        return true;
    return false;
}


/******************************************************************************
 * commandDeath - Message to alert lose
 ******************************************************************************/
void commandDeath() {
    tyAlertDialog("You lose!", "Dead Meat!!");
    tyQuit();
}

/******************************************************************************
 * commandWin - Message to alert won game
 ******************************************************************************/
void commandWin(void) {
    tyAlertDialog("Game Over", "You Won!");
    tyQuit();
}

/******************************************************************************
 * monsterSpeedAnimation - Method used to control speed animation of monsters
 ******************************************************************************/
void monsterSpeedAnimation(Game g) {
    if (g->monsters[0]->u.chaser.monsterSpeed != DEFAULT_MONSTER_SPEED) {
        if (g->lastActionTime + COOLDOWN_MYSTERY_BOX >= tySeconds()) {
            if (g->monsterCounter % g->monsters[0]->u.chaser.monsterSpeed ==
                0) {
                for (int i = 0; i < g->numberOfMonsters; i++)
                    actorAnimation(g, g->monsters[i]);
            }
        } else setMonstersVelocity(g, DEFAULT_MONSTER_SPEED);

    } else {
        if (g->monsterCounter % g->monsters[0]->u.chaser.monsterSpeed == 0) {
            for (int i = 0; i < g->numberOfMonsters; i++)
                actorAnimation(g, g->monsters[i]);
        }
    }
}


/******************************************************************************
 * gameAnimation - Sends animation events to all the animated actors
 * This function is called every tenth of a second (more or less...)
******************************************************************************/
void gameAnimation(Game g) {

    if (allTrapped(g))
        commandWin();

    actorAnimation(g, g->hero);
    monsterSpeedAnimation(g);

    if ((g->mysteryBoxTimeHide + COOLDOWN_MYSTERY_BOX < tySeconds()) &&
        !g->mysteryBoxPlaced) {
        gameInstallMysteryBox(g);
        g->mysteryBoxPlaced = true;
        g->mysteryBoxTimePlaced = tySeconds();
    }

    if (g->mysteryBoxTimePlaced + COOLDOWN_MYSTERY_BOX < tySeconds() &&
        g->mysteryBoxPlaced) {
        actorHide(g, g->mysteryBox);
        g->mysteryBoxPlaced = false;
        g->mysteryBoxTimeHide = tySeconds();
    }


    if (checkDeath(g, g->hero)) {
        if (g->hero->u.hero.heroLifes <= DEFAULT_HERO_LIFES)
            commandDeath();
        else
            removeLife(g, g->hero);
    }

}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* STATUS BAR */

/******************************************************************************
 * The function status populates the status bar, at the bottom of the window
 ******************************************************************************/

#define STATUS_ITEMS    5

void status(Game game) {
    String s, t;
    sprintf(s, "TIME = %d seg.", tySeconds());

    sprintf(t, "%d ♥", game->hero->u.hero.heroLifes);
    tySetStatusText(4, s);
    tySetStatusText(0, t);

    if (game->lastActionTime + COOLDOWN_MYSTERY_BOX >= tySeconds())
        if (game->lastRandomEvent == "+1 ENEMY" &&
            game->numberOfMonsters == MAX_N_MONSTERS)
            tySetStatusText(2, MAX_MONSTERS_EXCEDED);
        else
            tySetStatusText(2, game->lastRandomEvent);
    else
        tySetStatusText(2, "");

}



/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* MENU COMMANDS */

/******************************************************************************
 * Each function handles one menu command
 ******************************************************************************/

void comandAbout(void) {
    tyAlertDialog("About", "%s\n%s\n\n%s\n%s",
                  APP_NAME,
                  "(Reimplementation of the original game of Chuck Shotton)",
                  AUTHOR1,
                  AUTHOR2);
}

void comandRestart(void) {
    tyHandleStart();
}


void comandFinish(void) {
    tyAlertDialog("Quit", "See you later!");
    tyQuit();
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


/* FUNCTIONS REQUIRED BY THE FRAMEWORK wxTiny */

/******************************************************************************
 * Section with all the "root" "functions required by the wxTiny support system. 
 * 
 * There is no function "main" in a wxTiny program, as the main function is
 * hidden within the wxTiny library. The most important thing you need to know
 * is that the function "tyHandleStart" is called when the program begins,
 * and that function "tyHandleTime" is called periodically 10 times per second,
 * to make the program progress. In some sense, both this function make a kind
 * of main function.
 * 
 * More information about the wxTiny functions in the file "wxTiny.h".
 ******************************************************************************/

static Game game = NULL;  // defined here to be available to the "root" functions

/****************************************************************************** 
 * tyAppName - specify the name of the app
 ******************************************************************************/
tyStr tyAppName(void) {
    return APP_NAME;
}

/****************************************************************************** 
 * tyWidth - specify the width of the window
 ******************************************************************************/
int tyWidth(void) {
    return WORLD_SIZE_X * ACTOR_PIXELS_X;
}

/****************************************************************************** 
 * tyHeight - specify the height of the window
 ******************************************************************************/
int tyHeight(void) {
    return WORLD_SIZE_Y * ACTOR_PIXELS_Y;
}

/****************************************************************************** 
 * tyStatusItems - specify the number of slots available in the status bar
 ******************************************************************************/
int tyStatusItems(void) {
    return STATUS_ITEMS;
}

/****************************************************************************** 
 * tyMenus - specify the menus
 ******************************************************************************/
tyStr tyMenus(void) {
    return ":+Menu"
           ":&About\tCtrl-A"
           ":-"
           ":&Restart\tCtrl-R"
           ":-"
           ":&Quit\tCtrl-Q";
}

/****************************************************************************** 
 * tyHandleMenuCommand - Handles the menu commands
 ******************************************************************************/
void tyHandleMenuCommand(tyStr command) {
    if (strcmp(command, "About") == 0)
        comandAbout();
    else if (strcmp(command, "Restart") == 0)
        comandRestart();
    else if (strcmp(command, "Quit") == 0)
        comandFinish();
    else
        tyFatalError("Unknown command: \"%s\"", command);
}

/****************************************************************************** 
 * tyHandleRedraw - redraws the window
 *
 * Automatically called  in rare situations, for example if the game window is
 * minimized and then maximized
 ******************************************************************************/
void tyHandleRedraw(void) {
    gameRedraw(game);
}

/****************************************************************************** 
 * tyHandleTime - Called periodically, around 10 time per second
 * 
 * This function does the following: animate the actors; update the status bar;
 *    possibly more things
 ******************************************************************************/
void tyHandleTime(void) {
    status(game);
    gameAnimation(game);
}

/****************************************************************************** 
 * tyHandleStart - Program initialization
 ******************************************************************************/
void tyHandleStart(void) {
    tySecondsSetZero();
    tySetSpeed(5);
    game = gameInit(game);
}



