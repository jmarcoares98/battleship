#include "header.h"

void welcome_screen(void)
{
	printf("**********WELCOME TO BATTLESHIP**********\n");
	printf("\nRules of the Game:\n");
	printf("\n1. This game will consist of two players\n");
	printf("\n2. Player 1 would be you and BOT would be the second player\n");
	printf("\n3. The objective of the game is to sink the all the other player's ships\n");
	printf("\n4. Each player will have 5 ships:\n");
	printf("\ta. The Carrier: It has 5 cells\n");
	printf("\tb. The Battleship: It has 4 cells\n");
	printf("\tc. The Cruiser: It has 3 cells\n");
	printf("\td. The Submarine: Also has 3 cells\n ");
	printf("\te. The Destroyer: It has 2 cells\n");
	printf("\n5. You will then place your ships on a 10x10 board, and the bot will do the same\n");
	printf("\n6. After placing all your ships, The game begins!\n");
	printf("\n7. If you hit a ship, then the it will tell you. Then it will be the change turns\n");
	printf("\n8. If you miss, then it will display miss and change turns\n");
	printf("\n9. A ship will sunk, when you hit all of the cells of a certain ship\n");
	printf("\n10. Once you sunk all of your opponents ship then the you have won the game!\n");
	printf("\tPS. Check the stats of the game at battleships.log afterwards\n");
}

//This is where the board gets initialized values of multiple arrays
void initialize_game_board(Board board[][MAX_COLS], int num_rows, int num_cols)
{
	int row = 0, cols = 0;

	for (row = 0; row < num_rows; ++row)
	{
		for (cols = 0; cols < num_cols; ++cols)
		{
			board[row][cols].symbol = '~';
		}
	}
}

//Prints out the board of the game, will display how the game will look
void print_board(Board board[][MAX_COLS], int num_rows, int num_cols, Stats player, int sunk, BattleShip ship[], int storedship[])
{
	int rows = 0, cols = 0;

	printf("\t					**************\n");
	printf("\t               B               \t\tGame Stats\n\n");
	printf("\t   0  1  2  3  4  5  6  7  8  9\t\tTotal Shots: %d", player.total_shots);
	printf("\n");
	for (rows = 0; rows < num_rows; ++rows)
	{
		if (rows == 4)
		{
			printf("   A");
		}
		printf("\t%d ", rows);

		//Display stats in-game
		for (cols = 0; cols < num_cols; ++cols)
		{
			printf(" %c ", board[rows][cols]);
		}
		if (rows == 0)
		{
			printf("\tHits:        %d", player.total_hits);
		}
		if (rows == 1)
		{
			printf("\tMisses:      %d", player.total_misses);
		}
		if (rows == 2)
		{
			printf("\tSunk Ships:  %d", sunk);
		}
		if (rows == 3)
		{
			if (storedship[0] == 0)
			{
				printf("\t>%s", ship[0].name);
			}
		}
		if (rows == 4)
		{
			if (storedship[1] == 0)
			{
				printf("\t>%s", ship[1].name);
			}
		}

		if (rows == 5)
		{
			if (storedship[2] == 0)
			{
				printf("\t>%s", ship[2].name);
			}
		}
		if (rows == 6)
		{
			if (storedship[3] == 0)
			{
				printf("\t>%s", ship[3].name);
			}
		}
		if (rows == 7)
		{
			if (storedship[4] == 0)
			{
				printf("\t>%s", ship[4].name);
			}
		}
		if (rows == 9)
		{
			printf("\n\n\t\t\t\t\t\t**************");
		}
		putchar('\n');
	}
	printf("************************************************\n");
}

//randomize to who starts first in game
int select_who_starts_first(void)
{
	Player random = You;
	random = (Player)rand() % 2; // 50/50 chance to whover plays first

	if (random == 0)
	{
		printf("You have been selected to play first\n");
	}
	else
	{
		printf("The BOT will make the move first\n");
	}
	system("pause");
	system("cls");
	return random;
}

//the direction of the placement of the ship if either vertical or horizontal
Dir gen_dir(void)
{
	Dir direction = HORIZONTAL;

	direction = (Dir)rand() % 2; // randomize either Horizontal or vertical

	return direction;
}


void manually_place_ships_on_board(Board board[][MAX_COLS], BattleShip ships[], Stats player, int sunk, int storedship[])
{
	int i = 0, rows= 0, cols = 0;
	int direction;
	//loop till all the ships have been placed
	while (i < 5)
	{
		printf("\n****************PLAYER 1's BOARD****************\n");
		print_board(board, MAX_ROWS, MAX_COLS, player, sunk, ships, storedship);
		printf("Enter coordinates for %s (%d)\n", ships[i].name, ships[i].length);
		printf("[A] Row: ");
		scanf("%d", &rows);
		printf("[B] Column: ");
		scanf("%d", &cols);
		printf("Is it [0] Horizontal? Or [1] Vertical? "); //ask player to determine the direction it is going
		scanf("%d", &direction);
		if (direction == 0)//The restrictions in the horizontal direction
		{
			if ((cols + ships[i].length) > MAX_COLS)
			{
				printf("INVALID INPUT\n");
				printf("Enter Coordinates Again\n");
				system("pause");
				system("cls");
			}
			else if (board[rows][cols].symbol != '~')
			{
				printf("INVALID INPUT\n");
				printf("Enter Coordinates Again\n");
				system("pause");
				system("cls");
			}
			//this is where the ships are place on board
			else
			{
				for (int index = 0; index < ships[i].length; index++)
				{
						board[rows][cols].symbol = ships[i].symbol;
						cols++;
				}
				system("cls");
				i++;
			}
		}
		else //restrictions in vertical direction
		{
			if ((rows + ships[i].length) > MAX_ROWS)
			{
				printf("INVALID INPUT\n");
				printf("Enter Coordinates Again\n");
				system("pause");
				system("cls");
			}
			else if (board[rows][cols].symbol != '~')
			{
				printf("INVALID INPUT\n");
				printf("Enter Coordinates Again\n");
				system("pause");
				system("cls");
			}
			else
			{
				for (int index = 0; index < ships[i].length; index++)
				{
				
					board[rows][cols].symbol = ships[i].symbol;
					rows++;
				}
				system("cls");
				i++;
			}
		}
	}
}


//It randomly places the ship on the board 
void randomly_place_ships_on_board(Board board[][MAX_COLS], BattleShip ships[])
{
	int i = 0, rows = 0, cols = 0, j = 0, t = 0, n, k = 0;
	Dir direction;

	//loops until we get the best spots for the ships, no over lapping and no going away the board
	while (i < 5)
	{
		n = 10;
		//randomize what direction its going
		direction = gen_dir();

		if (direction == HORIZONTAL)
		{
			rows = (rand() % n);
			cols = (rand() % (n - ships[i].length));
			for (j = 0; j < ships[i].length; ++cols)
			{
				//loops to checks to see if it will overlap any ships or out the board
				while (k < ships[i].length)
				{
					//if it goes out the board it breaks and starts all over again
					if (k >= ships[i].length)
					{
						break;
					}
					//if it overlaps another ship then it loops al over again
					if (board[rows][cols + k].symbol != '~')
					{
						i--;
						t += 1;
						break;
					}
					k++;
				}
				if (t > 0) //if it overlaps
				{
					break;
				}
				else //if everything is chilling it will place the ship
				{
					board[rows][cols].symbol = ships[i].symbol;
					j++;
				}
			}
			k = 0;
			t = 0;
			i++;
		}

		else //for vertical direction
		{
			rows = (rand() % (n - ships[i].length));
			cols = (rand() % n);
			for (j = 0; j < ships[i].length; ++rows)
			{
				while (k < ships[i].length)
				{
					if (k >= ships[i].length)
					{
						break;
					}
					if (board[rows + k][cols].symbol != '~')
					{
						i--;
						t += 1;
						break;
					}
					k++;
				}
				if (t > 0)
				{
					break;
				}
				else
				{
					board[rows][cols].symbol = ships[i].symbol;
					j++;
				}
			}
			t = 0;
			k = 0;
			i++;
		}
	}
}

//prompts the player to take shot on opponents board
Coordinate take_shot(void)
{
	Coordinate shots_fired;

	printf("PLAYER'S TURN\n");
	printf("Enter Coordinates for target\n");
	printf("[A] Row: ");
	scanf("%d", &shots_fired.row);
	printf("[B] Column: ");
	scanf("%d", &shots_fired.column);

	return shots_fired;
}

//This checks the shot and displays the opponents board
int check_shot(Board board[][MAX_COLS], Board show[][MAX_COLS], Coordinate target)
{
	int shot = 0, check = 0;

	while (check < 1)
	{
		//checks if its target was already shot
		if (show[target.row][target.column].symbol == MISS ||
			show[target.row][target.column].symbol == HIT)
		{
			printf("You already shot this target!\n");
			printf("Enter Coordinates Again\n");
			system("pause");
			system("cls");
			shot = 2;
			break;
		}
		if (target.row > MAX_ROWS ||
			target.column > MAX_COLS)
		{
			printf("INVALID INPUT\n");
			printf("Enter Coordinates Again\n");
			system("pause");
			system("cls");
			shot = 2;
			break;
		}

		//if its a miss
		if (board[target.row][target.column].symbol == WATER)
		{
			printf("You missed!\n");
			show[target.row][target.column].symbol = MISS; //This will update the board from WATER to MISS
			check = 2;
			shot = 0;
			break;
		}

		//if its a hit
		if (board[target.row][target.column].symbol != WATER)
		{
			printf("You hit a target!\n");
			show[target.row][target.column].symbol = HIT; //updateds the board from shiip symbol to HIT
			check = 2;
			shot = 1;
			break;
		}

	}
	return shot;
}

//function for computers turn to hit
Coordinate computers_shot(void)
{
	Coordinate random = { 0 };

	random.row = (rand() % MAX_ROWS);
	random.column = (rand() % MAX_COLS);


	
	return random;
}

//checks shots for computer
int check_shot_computer(Board board[][MAX_COLS], Coordinate cpt_target)
{
	int shot = 0, check = 0;

	while (check < 1)
	{
		//it will loop in main until it hits another target
		if (board[cpt_target.row][cpt_target.column].symbol == MISS ||
			board[cpt_target.row][cpt_target.column].symbol == HIT)
		{
			shot = -1;
			break;
		}

		//if its a miss
		if (board[cpt_target.row][cpt_target.column].symbol == WATER)
		{
			printf("COMPUTERS TURN\n");
			printf("Row: %d \nCol: %d\n", cpt_target.row, cpt_target.column);
			printf("It missed!\n");
			board[cpt_target.row][cpt_target.column].symbol = MISS; 
			shot = 0;
			break;
		}

		//if its a hit
		if (board[cpt_target.row][cpt_target.column].symbol != WATER &&
			board[cpt_target.row][cpt_target.column].symbol != MISS)
		{
			printf("COMPUTERS TURN\n");
			printf("Row: %d \nCol: %d\n", cpt_target.row, cpt_target.column);
			printf("It hit a target!\n");
			board[cpt_target.row][cpt_target.column].symbol = HIT;
			shot += 1;
			break;
		}

	}
	
	return shot;
}

//This is where we check to see if any of the ships were sunk
int check_if_sunk_ship(int ship[5], char symbol, FILE * outfile)
{
	int sunk = 0;
	switch (symbol)
	{
		case CARRIER:
			ship[0]--;
			if (ship[0] == 0)
			{
				printf("The Carrier is destroyed!\n");
				fprintf(outfile, ">Carrier has sunk!\n");
				sunk++;
			}
			break;
		case BATTLESHIP:
			ship[1]--;
			if (ship[1] == 0)
			{
				printf("The Battleship is destroyed!\n");
				fprintf(outfile, ">Battleship has sunk!\n");
				sunk++;
			}
			break;
		case CRUISER:
			ship[2]--;
			if (ship[2] == 0)
			{
				printf("The Cruiser is destroyed!\n");
				fprintf(outfile, ">Cruiser has sunk!\n");
				sunk++;
			}
			break;
		case SUBMARINE:
			ship[3]--;
			if (ship[3] == 0)
			{
				printf("The Submarine is destroyed!\n");
				fprintf(outfile, ">Submarine has sunk!\n");
				sunk++;
			}
			break;
		case DESTROYER:
			ship[4]--;
			if (ship[4] == 0)
			{
				printf("The Destroyer is destroyed!\n");
				fprintf(outfile, ">Destroyer has sunk!\n");
				sunk++;
			}
			break;
	}
	return sunk;
}
