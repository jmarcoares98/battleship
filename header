#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
 
//defining the variables
#define MAX_ROWS 10
#define MAX_COLS 10
#define WATER '~'
#define HIT 'X'
#define MISS 'O'

//definition for ships
#define CARRIER 'c'
#define BATTLESHIP 'b'
#define CRUISER 'r'
#define SUBMARINE 's'
#define DESTROYER 'd'

//direction of either vertical or horizontal
typedef enum dir
{
	HORIZONTAL = 0,
	VERTICAL = 1
} Dir;

//to determine which player goes first
typedef enum player
{
	You = 0,
	Bot = 1
}Player;

//to target ships on board
typedef struct coordinate {
	int row;
	int column;
} Coordinate;

//to store stuff on the ships
typedef struct battleship
{
	char symbol;
	int length;
	char *name;
} BattleShip;

//to outfile to battleship.log
typedef struct stats
{
	int total_shots;
	int total_hits;
	int total_misses;
	double ratio_hitmiss;

}Stats;

//to store stuff in board and retrieve it for later
typedef struct board
{
	char symbol;
	int row;
	int col;
}Board;

void welcome_screen(void);
void initialize_game_board(Board board[][MAX_COLS], int num_rows, int num_cols);
void print_board(Board board[][MAX_COLS], int num_rows, int num_cols, Stats player, int sunk, BattleShip ships[], int storedship[]);
int select_who_starts_first(void);
Dir gen_dir(void);
void manually_place_ships_on_board(Board board[][MAX_COLS], BattleShip ships[], Stats player, int sunk, int storedship[]);
void randomly_place_ships_on_board(Board board[][MAX_COLS], BattleShip ships[]);
Coordinate take_shot(void);
int check_shot(Board board[][MAX_COLS], Board show[][MAX_COLS], Coordinate target);
Coordinate computers_shot(void);
int check_shot_computer(Board board[][MAX_COLS], Coordinate target);
int check_if_sunk_ship(int ship[5], char symbol, FILE * OUTFILE);
