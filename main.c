#include "header.h"

int main()
{
	int option, turn, shot = 0, cpt_shot = 0;
	int exit = 0;
	Board player1_board[MAX_ROWS][MAX_COLS] = { '\0' },
		 bot_board[MAX_ROWS][MAX_COLS] = { '\0' },
		 displayed_board[MAX_ROWS][MAX_COLS] = { '\0' };

	Stats player_stats = { 0, 0, 0, 0.0 };
	Stats bot_stats = { 0, 0, 0, 0.0 };

	Dir direction = HORIZONTAL;

	BattleShip ships[5] = {{'c', 5, "CARRIER"}, 
						   {'b', 4, "BATTLESHIP"}, 
						   {'r', 3, "CRUISER"}, 
						   {'s', 3, "SUBMARINE"}, 
						   {'d', 2, "DESTROYER"}};
	BattleShip compships[5] = { { 'c', 5, "CARRIER" },
								{ 'b', 4, "BATTLESHIP" },
								{ 'r', 3, "CRUISER" },
								{ 's', 3, "SUBMARINE" },
								{ 'd', 2, "DESTROYER" } };
	Coordinate target;
	Coordinate cpt_target;

	//initialize for sunk ship function
	int sunk_ship = 0;
	int has_sunk = 0;
	char store_symbol = '\0';
	char store_comp_symbol = '\0';
	int player_ship[5] = { 5, 4, 3, 3, 2 };
	int bot_ship[5] = { 5, 4, 3, 3, 2 };

	//Output stats to file
	FILE * outfile = NULL;
	outfile = fopen("battleship.log", "w");

	srand((unsigned int)time(NULL));
	//Introduction of the game
	welcome_screen();
	system("pause");
	system("cls");

	//Board has been set up
	initialize_game_board(player1_board, MAX_ROWS, MAX_COLS);
	initialize_game_board(bot_board, MAX_ROWS, MAX_COLS);
	initialize_game_board(displayed_board, MAX_ROWS, MAX_COLS);

	//Display board
	do
	{
		printf("\n**************B A T T L E S H I P***************\n");
		print_board(player1_board, MAX_ROWS, MAX_COLS, player_stats, sunk_ship, ships, player_ship);
		printf("Please select from the Menu:\n");
		printf("[1] Manually place ships\n");
		printf("[2] Randomly place ships\n");
		printf("Enter option: ");
		scanf("%d", &option);
		if (option == 1 || option == 2)
		{
			break;
		}
		if (option > 2 || option < 1)
		{
			printf("INVALID INPUT\n");
			system("pause");
			system("cls");
		}
	} while (option != 1 || option != 2);
	system("cls");
	printf("\n**************B A T T L E S H I P***************\n");
	print_board(player1_board, MAX_ROWS, MAX_COLS, player_stats, sunk_ship, ships, player_ship);

	//The game menu
	switch (option)
	{
		case 1: 
			system("cls");
			manually_place_ships_on_board(player1_board, ships, player_stats, sunk_ship, ships, player_ship);
			break;
		case 2:
			printf("Ships has been randomly placed in board...\n");
			randomly_place_ships_on_board(player1_board, ships);
			system("pause");
			system("cls");
			break;
	}
	printf("\n****************PLAYER 1's BOARD****************\n");
	print_board(player1_board, MAX_ROWS, MAX_COLS, player_stats, sunk_ship, ships, player_ship);
	printf("LETS BATTLESHIP BOII!!\n");
	randomly_place_ships_on_board(bot_board, ships);
	system("pause");
	system("cls");
	printf("\n****************PLAYER 1's BOARD****************\n");
	print_board(player1_board, MAX_ROWS, MAX_COLS, player_stats, sunk_ship, ships, player_ship);

	//Determines who plays first
	turn = 0; 
	turn = select_who_starts_first();

	//This is where the game starts
	while (exit != 1){
		switch (turn)
		{

		case 0:
			//displays opponents board for player
			printf("\n****************OPPONENT's BOARD****************\n");
			print_board(displayed_board, MAX_ROWS, MAX_COLS, player_stats, sunk_ship, ships, player_ship);

			//loops or redos shot it if shot was already taken
			do {

				//displays the board again if invalid input
				if (shot == 2)
				{
					printf("\n****************OPPONENT's BOARD****************\n");
					print_board(displayed_board, MAX_ROWS, MAX_COLS, player_stats, sunk_ship, ships, player_ship);
				}
				//player attacks opponents board
				target = take_shot();

				//stores the symbol if it was a ship
				store_symbol = bot_board[target.row][target.column].symbol;

				//checks whether or not player hits a ship then displays miss or hit
				shot = check_shot(bot_board, displayed_board, target, player_stats);
				if (shot == 0)
				{
					player_stats.total_misses++;
				}
				if (shot == 1)
				{
					player_stats.total_hits++;
				}
			} while (shot == 2);
			//for stats
			player_stats.total_shots++;

			//prints the moves on battleship.log
			if (sunk_ship < 5)
			{
				fprintf(outfile, "Player's Shot:\n");
				fprintf(outfile, "Row: %d Column: %d\n", target.row, target.column);
				if (shot == 0)
				{
					fprintf(outfile, "MISS!\n");
				}
				if (shot == 1)
				{
					fprintf(outfile, "HIT!\n");
				}
			}

			//checks if a ship was sunk
			sunk_ship += check_if_sunk_ship(player_ship, store_symbol, outfile);

			system("pause");
			system("cls");

			//updates board
			printf("\n****************OPPONENT's BOARD****************\n");
			print_board(displayed_board, MAX_ROWS, MAX_COLS, player_stats, sunk_ship, ships, player_ship);


			//stops printing this if the game has ended
			if (sunk_ship < 5 )
			{
				printf("COMPUTERS TURN\n");
				system("pause");
				system("cls");
			}

			//changes turns
			turn += 1;


			//breaks when the game has ended
			if (player_stats.total_hits == 17 || sunk_ship == 5)
			{
				break;
			}

		case 1:
			printf("\n****************PLAYER 1's BOARD****************\n");
			print_board(player1_board, MAX_ROWS, MAX_COLS, bot_stats, has_sunk, compships, bot_ship);

			//loop until it doesnt hit the same shot

			do {
				//randomize shot for computer
				if (cpt_shot == 0 || cpt_shot == -1)
				{
					cpt_target = computers_shot();
				}

				//if it hits the first time then it will try and hit the one next to it
				if (cpt_shot > 0)
				{
					do {
						if (cpt_target.row >= 9 || cpt_target.column >= 9)
						{
							cpt_shot = 0;
							break;
						}
						else
						{
							if (cpt_shot < 1)
							{
								direction = gen_dir();
							}

							if (direction == HORIZONTAL)
							{
								player1_board[cpt_target.row][cpt_target.column += 1];
								break;
							}

							if (direction == VERTICAL)
							{
								player1_board[cpt_target.row += 1][cpt_target.column];
								break;
							}
						}
					} while (cpt_shot <= 1);
				}
				store_comp_symbol = player1_board[cpt_target.row][cpt_target.column].symbol;
				cpt_shot = check_shot_computer(player1_board, cpt_target, bot_stats);
			} while (cpt_shot == -1);

			if (cpt_shot == 0)
			{
				bot_stats.total_misses++;
			}
			if (cpt_shot == 1)
			{
				bot_stats.total_hits++;
			}

			bot_stats.total_shots++;
			if (has_sunk < 5)
			{
				fprintf(outfile, "Computer's Shots:\n");
				fprintf(outfile, "Row: %d Column: %d\n", cpt_target.row, cpt_target.column);
				if (cpt_shot == 0)
				{
					fprintf(outfile, "MISS!\n");
				}
				if (cpt_shot == 1)
				{
					fprintf(outfile, "HIT!\n");
				}
			}
			has_sunk += check_if_sunk_ship(bot_ship, store_comp_symbol, outfile);

			//Updates the layout
			system("pause");
			system("cls");
			printf("\n****************PLAYER 1's BOARD****************\n");
			print_board(player1_board, MAX_ROWS, MAX_COLS, bot_stats, has_sunk, compships, bot_ship);

			if (has_sunk < 5)
			{
				printf("PLAYER'S TURN\n");
				system("pause");
				system("cls");
			}

			turn -= 1;
			if (bot_stats.total_hits == 17 || has_sunk == 5)
			{
				break;
			}
		}

		//When the game ends
		if (player_stats.total_hits == 17 || sunk_ship == 5)
		{
			printf("YOU SUNK ALL OF YOUR OPPONENTS SHIPS!!\n");
			printf("CONGRATULATIONS YOU WON!!!!!!\n");
			fprintf(outfile, "Player Won, Computer Loss!\n");
			system("pause");
			system("cls");
			exit = 1;
		}
		if (bot_stats.total_hits == 17 || has_sunk == 5)
		{
			printf("THE COMPUTER HAS SUNK ALL YOUR SHIPS\n");
			printf("YOU LOSE THE GAME\n");
			fprintf(outfile, "Computer Won, Player Loss!\n");
			system("pause");
			system("cls");
			exit = 1;
		}
	}


	player_stats.ratio_hitmiss = ((double)player_stats.total_hits / (double)player_stats.total_misses) * 100;
	bot_stats.ratio_hitmiss = ((double)bot_stats.total_hits / (double)bot_stats.total_misses) * 100;
	//This is where all the stats go in to the battleship log
	fprintf(outfile, "************************************************\n");
	fprintf(outfile, "**                GAME STATS                  **\n");
	fprintf(outfile, "**--------------------------------------------**\n");
	fprintf(outfile, "** PLAYER : %d  hits                          **\n", player_stats.total_hits);
	fprintf(outfile, "**        : %d  misses                        **\n", player_stats.total_misses);
	fprintf(outfile, "**        : %d  total shots                   **\n", player_stats.total_shots);
	fprintf(outfile, "**        : %d  ships sunk                    **\n", sunk_ship);
	fprintf(outfile, "**        : %.2lf%%  Hit Miss Ratio           **\n", player_stats.ratio_hitmiss);
	fprintf(outfile, "** BOT    : %d  hits                          **\n", bot_stats.total_hits);
	fprintf(outfile, "**        : %d  misses                        **\n", bot_stats.total_misses);
	fprintf(outfile, "**        : %d  total shots                   **\n", bot_stats.total_shots);
	fprintf(outfile, "**        : %d  ships sunk                    **\n", has_sunk);
	fprintf(outfile, "**        : %.2lf%%  Hit Miss Ratio           **\n", bot_stats.ratio_hitmiss);
	fprintf(outfile, "************************************************\n");

	fclose(outfile);
	return 0;
}
