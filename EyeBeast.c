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

?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????
?????????????????????????


 Place here the names and numbers of the authors, plus some comments, as
 asked in the listing of the project. Do not deliver an anonymous file with
 unknown authors.
*/

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* IDENTIFICATION */

#define APP_NAME	"Eye Beast"

#define AUTHOR1		"Joao Pereira (60180)"
#define AUTHOR2		"Pedro Grilo (59213)"

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

#define MAX_STRING	256
#define MAX_LINE	1024

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

static Image emptyImg, heroImg, chaserImg, blockImg, boundaryImg, invalidImg;

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
void imagesCreate(void)
{
	emptyImg = tyCreateImage(empty_xpm);
	heroImg = tyCreateImage(hero_xpm);
	chaserImg = tyCreateImage(chaser_xpm);
	blockImg = tyCreateImage(block_xpm);
	boundaryImg = tyCreateImage(boundary_xpm);
	invalidImg = tyCreateImage(invalid_xpm);
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* ACTORS */

/******************************************************************************
 * Constants, types and functions for all kinds of actors
 ******************************************************************************/

#define ACTOR_PIXELS_X	16
#define ACTOR_PIXELS_Y	16

typedef enum {
	EMPTY, HERO, CHASER, BLOCK, BOUNDARY
} ActorKind;



typedef struct {
// specific fields can go here, but probably none will be needed
} Hero;

typedef struct {
// specific fields can go here, but probably none will be needed
} Chaser;

typedef struct {
// specific fields can go here, but probably none will be needed
} Block;

typedef struct {
// specific fields can go here, but probably none will be needed
} Boundary;

typedef struct {
// factored common fields
    ActorKind kind;
 	int x, y;
	Image image;
    union {
// specific fields for each kind
        Hero hero;
        Chaser chaser;
        Block block;
        Boundary boundary;
    } u;
} ActorStruct, *Actor;

#define WORLD_SIZE_X	31
#define WORLD_SIZE_Y	18
#define N_MONSTERS		5

typedef struct {
	Actor world[WORLD_SIZE_X][WORLD_SIZE_Y];
	Actor hero;
	Actor monsters[N_MONSTERS];
} GameStruct, *Game;

/******************************************************************************
 * actorImage - Get the screen image corresponding to some kind of actor
 ******************************************************************************/
Image actorImage(ActorKind kind)
{
	switch( kind ) {
		case EMPTY:		return emptyImg;
		case HERO:		return heroImg;
		case CHASER:	return chaserImg;
		case BLOCK:		return blockImg;
		case BOUNDARY:	return boundaryImg;
		default:		return invalidImg;
	}
}

/******************************************************************************
 * cellSet - Useful function to update one cell in the matrix and in the screen
 ******************************************************************************/
void cellSet(Game g, Actor a, int x, int y, Image img)
{
	tyDrawImage(img, x * ACTOR_PIXELS_X, y * ACTOR_PIXELS_Y);
	g->world[x][y] = a;	
}

/******************************************************************************
 * cellIsEmpty - Check in the matrix if a cell is empty (if contains NULL)
 ******************************************************************************/
bool cellIsEmpty(Game g, int x, int y)
{
	return g->world[x][y] == NULL;
}

/******************************************************************************
 * actorShow - Install an actor in the matrix and in the screen
 ******************************************************************************/
void actorShow(Game g, Actor a)
{
	cellSet(g, a, a->x, a->y, a->image);
}

/******************************************************************************
 * actorHide - Removes an actor from the matrix and from the screen
 ******************************************************************************/
void actorHide(Game g, Actor a)
{
	cellSet(g, NULL, a->x, a->y, emptyImg);
}

/******************************************************************************
 * actorMove - Move an actor to a new position
 * pre: the new position is empty
 ******************************************************************************/
void actorMove(Game g, Actor a, int nx, int ny)
{
	actorHide(g, a);
	a->x = nx;
	a->y = ny;
	actorShow(g, a);
}

/******************************************************************************
 * actorNew - Creates a new actor and installs it in the matrix and the screen
 ******************************************************************************/
Actor actorNew(Game g, ActorKind kind, int x, int y)
{
	Actor a = malloc(sizeof(ActorStruct));
	a->kind = kind;
	a->x = x;
	a->y = y;
	a->image = actorImage(kind);
	actorShow(g, a);
	return a;
}

bool checkIfMoveIsPossible(Game g, int dx, int dy,int nx, int ny, int appendX, int appendY){

    /*const char* dayNames[] = {"EMPTY", "HERO", "CHASER","BLOCK","BOUNDARY" };
    //TODO REMOVER ISTO QUANDO FOR PARA ENTREGAR, APENAS PARA TESTES
/*if((!cellIsEmpty(g,nx+appendX,ny) && dx > 0 &&(g->world[nx + appendX][ny]->kind == BOUNDARY || g->world[nx + appendX][ny]->kind == CHASER ) )){
        printf("dir %s\n",dayNames[g->world[nx + appendX][ny]->kind]);
    }
    if((!cellIsEmpty(g,nx-appendX,ny) && dx < 0 &&(g->world[nx - appendX][ny]->kind == BOUNDARY || g->world[nx - appendX][ny]->kind == CHASER ) )){
        printf("esq %s\n",dayNames[g->world[nx - appendX][ny]->kind]);
    }
    if((!cellIsEmpty(g,nx,ny+appendY) && dy > 0 && (g->world[nx][ny+appendY]->kind == BOUNDARY || g->world[nx][ny+appendY]->kind == CHASER ) )){
        printf("baixo %s\n",dayNames[g->world[nx][ny+appendY]->kind]);
    }if((!cellIsEmpty(g,nx,ny-appendY) && dy < 0&&(g->world[nx][ny-appendY]->kind == BOUNDARY || g->world[nx][ny-appendY]->kind == CHASER ) )){
        printf("cima %s\n",dayNames[g->world[nx][ny-appendY]->kind]);
    }/*
    */
    return !(!cellIsEmpty(g,nx+appendX,ny)  && dx > 0 && (g->world[nx + appendX][ny]->kind == BOUNDARY || g->world[nx + appendX][ny]->kind == CHASER ) ||
               !cellIsEmpty(g,nx-appendX,ny)  && dx < 0 &&(g->world[nx - appendX][ny]->kind == BOUNDARY || g->world[nx - appendX][ny]->kind == CHASER ) ||
               !cellIsEmpty(g,nx,ny+appendY)  && dy > 0 && (g->world[nx][ny+appendY]->kind == BOUNDARY || g->world[nx][ny+appendY]->kind == CHASER ) ||
               !cellIsEmpty(g,nx,ny-appendY)  && dy < 0 && (g->world[nx][ny-appendY]->kind == BOUNDARY || g->world[nx][ny-appendY]->kind == CHASER ));
}

/******************************************************************************
 * heroAnimation - The hero moves using the cursor keys
 * INCOMPLETE!
 ******************************************************************************/
void heroAnimation(Game g, Actor a)
{
	int dx = tyKeyDeltaX(), dy = tyKeyDeltaY();

	int nx = a->x + dx, ny = a->y + dy;
    int  appendX = 0,  appendY =0;
	if (cellIsEmpty(g, nx, ny)){
        actorMove(g, a, nx, ny);
    }else{
        if(g->world[nx][ny]->kind == BLOCK){
            int existsBlock = 1;
            while(existsBlock == 1){
                if ((dx > 0 && !cellIsEmpty(g,nx+appendX,ny) && g->world[nx + appendX][ny]->kind == BLOCK) //direita
                    || dx < 0 && !cellIsEmpty(g,nx-appendX,ny) && g->world[nx - appendX][ny]->kind == BLOCK)  //esquerda
                    appendX = appendX +1;
                else if((dy > 0 && !cellIsEmpty(g,nx,ny+appendY) && g->world[nx][ny+appendY]->kind == BLOCK) //cima
                        || dy < 0 &&!cellIsEmpty(g,nx,ny-appendY) && g->world[nx][ny-appendY]->kind == BLOCK) //baixo
                    appendY = appendY + 1;
                else //none
                    existsBlock = 0;
            }
            if(checkIfMoveIsPossible(g,dx,dy,nx,ny,appendX,appendY)){
                    actorMove(g,g->world[nx][ny],dx > 0 ? nx+appendX : dx < 0 ? nx-appendX: nx, dy > 0 ? ny+appendY : dy < 0 ? ny-appendY: ny);
                    actorMove(g, a, nx, ny);
            }
        }
    }
}

void chaserAnimation(Game g, Actor a) {
		int whichWay = tyRand(2);
		int nextX, nextY;
		if(whichWay == 0)
			nextX = a->x + tyRand(2);
		else 
			nextX = a->x - tyRand(2);
		whichWay = tyRand(2);
		if(whichWay == 0)
			nextY = a->y + tyRand(2);
		else 
			nextY = a->y - tyRand(2);
		
		if (cellIsEmpty(g, nextX, nextY)) {
			actorMove(g, a, nextX, nextY);
			
		}
	
}


/******************************************************************************
 * actorAnimation - The actor behaves according to its kind
 * INCOMPLETE!
 ******************************************************************************/

int monsterCounter = 1;

void actorAnimation(Game g, Actor a)
{
	
	switch( a->kind ) {
		case HERO:
			heroAnimation(g, a); 
			monsterCounter++;
		break;
		case CHASER:
			chaserAnimation(g,a);
			break;
		default: break;
	}
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* GAME */

/******************************************************************************
 * gameClearWorld - Clears the matrix and the screen
 ******************************************************************************/
void gameClearWorld(Game g)
{
    for(int y = 0; y < WORLD_SIZE_Y ; y++)
        for(int x = 0; x < WORLD_SIZE_X ; x++ )
			cellSet(g, NULL, x, y, emptyImg);
}

/******************************************************************************
 * gameInstallBoundaries - Install the boundary blocks
 ******************************************************************************/
void gameInstallBoundaries(Game g)
{
     for(int y = 0; y < WORLD_SIZE_Y ; y++)
        for(int x = 0; x < WORLD_SIZE_X ; x++)
            if( x == 0 || x == WORLD_SIZE_X - 1
            || y == 0 || y == WORLD_SIZE_Y - 1 ) {
               actorNew(g, BOUNDARY, x, y);
             }
}

/******************************************************************************
 * gameInstallBlocks - Install the movable blocks
 * INCOMPLETE! -- ja ta completo
 ******************************************************************************/
void gameInstallBlocks(Game g)
{
	  
  


	   
	
    int i = 0;
    int max = 110;
    int counter = 0;
    while (i <= max){
        int x = tyRand(WORLD_SIZE_X-2) + 1;
        int y = tyRand(WORLD_SIZE_Y-2) + 1;
        if(cellIsEmpty(g,x,y)) {
            actorNew(g, BLOCK, x, y);
           /*printf("contador %d\n",tyRand(2));*/
        }else
            max++;
        i++;
    }
}

/******************************************************************************
 * gameInstallMonsters - Install the monsters
 * INCOMPLETE! ja ta completoz
 ******************************************************************************/
void gameInstallMonsters(Game g)
{

	
    int i = 0;
    int max = N_MONSTERS;
    int countMonsters = 0;
    while (i <= max){
        int x = tyRand(WORLD_SIZE_X-2) + 1;
        int y = tyRand(WORLD_SIZE_Y-2) + 1;
        if(cellIsEmpty(g,x,y) ) {
            g->monsters[countMonsters] = actorNew(g, CHASER, x, y);
            countMonsters++;
        }else
            max++;
        i++;
    }
}

/******************************************************************************
 * gameInstallHero - Install the hero
 * INCOMPLETE! This code is to change  ja ta completo
 ******************************************************************************/
void gameInstallHero(Game g)
{
    int counterMonsters = 0;
    int x,y;
    while(counterMonsters < N_MONSTERS){
        counterMonsters = 0;
        x = tyRand(WORLD_SIZE_X-2) + 1;
        y = tyRand(WORLD_SIZE_Y-2) + 1;
        if(cellIsEmpty(g, x, y)){
            for(int i = 0; i < N_MONSTERS; i++) {
                if (tyDistance(g->monsters[i]->x, g->monsters[i]->y, x, y) > 4)
                    counterMonsters++;
            }
        }
    }
    g->hero = actorNew(g, HERO, x, y);

}

/******************************************************************************
 * gameInit - Initialize the matrix and the screen
 ******************************************************************************/
Game gameInit(Game g)
{
	if (g == NULL)
		g = malloc(sizeof(GameStruct));
	imagesCreate();
    gameClearWorld(g);
    gameInstallBoundaries(g);
    gameInstallBlocks(g);
    gameInstallMonsters(g);
	gameInstallHero(g);
	return g;
}

/******************************************************************************
 * gameRedraw - Redraws the entire scenario. This function is called by
 * tyHandleRedraw in very specific circumstances. It should not be used anywhere
 * else because you don't want to be constantly redrawing the whole scenario.
 ******************************************************************************/
void gameRedraw(Game g)
{
	for(int y = 0; y < WORLD_SIZE_Y; y++)
		for(int x = 0; x < WORLD_SIZE_X; x++) {
			Actor a = g->world[x][y];
			if( !cellIsEmpty(g, x, y) )
				actorShow(g, a);
		}
}

/******************************************************************************
 * gameAnimation - Sends animation events to all the animated actors
 * This function is called every tenth of a second (more or less...)
 * INCOMPLETE!
******************************************************************************/
bool checkDeath(Game g,Actor a) {
	for(int i = 0 ; i < N_MONSTERS ; i++) {
		if(tyDistance(a->x, a->y, g->monsters[i]->x,  g->monsters[i]->y) <= 1)
			return true;
	}
	return false;
	
}

bool checkIfIsTrapped(Game g, Actor a) {
	int counter = 0;
	int N_CELLS_TO_TRAP = 9;
	int actorX = a->x;
	int actorY = 	a->y;
	for(int i = -1; i <=1; i++ ) {
		for(int j = -1; j <=1; j++) {
			if(!cellIsEmpty(g,actorX + i, actorY +j))
				counter++;
		}
	}
	if(counter == N_CELLS_TO_TRAP) return true;
	return false;

	
}

bool allTrapped(Game g) {
	int counter = 0;
	for(int i = 0 ; i < N_MONSTERS ; i++) {
		if(checkIfIsTrapped(g,g->monsters[i]))
			counter++;
	}
	if(counter == N_MONSTERS) 
		return true;
	return false;
}

void commandDeath(void) {
	tyAlertDialog("You lose!","Dead Meat!!");
	tyQuit();
}


void commandWin(void)
{
	tyAlertDialog("Game Over", "You Won!");
	tyQuit();
}

void gameAnimation(Game g) {
	
	if(allTrapped(g))
		commandWin();

	actorAnimation(g, g->hero);
	
	if(monsterCounter%10==0) {
	for(int i = 0 ; i < N_MONSTERS ; i++)
		actorAnimation(g, g->monsters[i]);	
	}
	

	if(checkDeath( g, g->hero))
		commandDeath();

	
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* STATUS BAR */

/******************************************************************************
 * The function status populates the status bar, at the bottom of the window
 ******************************************************************************/

#define STATUS_ITEMS	5

void status(void)
{
	String s;
	sprintf(s, "TIME = %d seg.", tySeconds());
	tySetStatusText(4, s);
}



/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* MENU COMMANDS */

/******************************************************************************
 * Each function handles one menu command
 ******************************************************************************/

void comandAbout(void)
{
	tyAlertDialog("About", "%s\n%s\n\n%s\n%s",
		APP_NAME,
		"(Reimplementation of the original game of Chuck Shotton)",
		AUTHOR1,
		AUTHOR2);


}

void comandRestart(void)
{
	tyHandleStart();
}


void comandFinish(void)
{
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
tyStr tyAppName(void)
{
	return APP_NAME;
}

/****************************************************************************** 
 * tyWidth - specify the width of the window
 ******************************************************************************/
int tyWidth(void)
{
	return WORLD_SIZE_X * ACTOR_PIXELS_X;
}

/****************************************************************************** 
 * tyHeight - specify the height of the window
 ******************************************************************************/
int tyHeight(void)
{
	return WORLD_SIZE_Y * ACTOR_PIXELS_Y;
}

/****************************************************************************** 
 * tyStatusItems - specify the number of slots available in the status bar
 ******************************************************************************/
int tyStatusItems(void)
{
	return STATUS_ITEMS;
}

/****************************************************************************** 
 * tyMenus - specify the menus
 ******************************************************************************/
tyStr tyMenus(void)
{
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
void tyHandleMenuCommand(tyStr command)
{
	if( strcmp(command, "About") == 0 )
		comandAbout();
	else if( strcmp(command, "Restart") == 0 )
		comandRestart();
	else if( strcmp(command, "Quit") == 0 )
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
void tyHandleRedraw(void)
{
	gameRedraw(game);
}

/****************************************************************************** 
 * tyHandleTime - Called periodically, around 10 time per second
 * 
 * This function does the following: animate the actors; update the status bar;
 *    possibly more things
 ******************************************************************************/
void tyHandleTime(void)
{
	status();
	gameAnimation(game);
}

/****************************************************************************** 
 * tyHandleStart - Program initialization
 ******************************************************************************/
void tyHandleStart(void)
{
	tySecondsSetZero();
	tySetSpeed(5);
	game = gameInit(game);
}

