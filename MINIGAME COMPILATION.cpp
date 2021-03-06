#include"WereWolf\wwfunc.h"
#include"Hangman\hangmanfunc.h"
#include"TicTacToe\tictactoefunc.h"
#include"Rambo\rambofunc.h"
#include"Fossil Hunter\FossilHunterfunc.h"
#include"Monopoly\Monopolyfunc.h"
#include"Opercooked\Opercookedfunc.h"
#include"Dungeon Escape\DungeonEscapefunc.h"
#include"Monster Maze\MonsterMazefunc.h"
#include"Snakes\Snakesfunc.h"
#include"Station Manager\StationManagerfunc.h"
#include"Census System\CensusSystemfunc.h"

void subMenu_coreTraining(){
	char option;
	do{
		do{
			system("cls");
			printf("\t\t\t\t   _____ ____  _____  ______   _______ _____            _____ _   _ _____ _   _  _____            _   _          _____  \n");
			printf("\t\t\t\t  / ____/ __ \\|  __ \\|  ____| |__   __|  __ \\     /\\   |_   _| \\ | |_   _| \\ | |/ ____|          | \\ | |   /\\   |  __ \\ \n");
			printf("\t\t\t\t | |   | |  | | |__) | |__       | |  | |__) |   /  \\    | | |  \\| | | | |  \\| | |  __   ______  |  \\| |  /  \\  | |__) |\n");
			printf("\t\t\t\t | |   | |  | |  _  /|  __|      | |  |  _  /   / /\\ \\   | | | . ` | | | | . ` | | |_ | |______| | . ` | / /\\ \\ |  _  / \n");
			printf("\t\t\t\t | |___| |__| | | \\ \\| |____     | |  | | \\ \\  / ____ \\ _| |_| |\\  |_| |_| |\\  | |__| |          | |\\  |/ ____ \\| | \\ \\ \n");
			printf("\t\t\t\t  \\_____\\____/|_|  \\_\\______|    |_|  |_|  \\_\\/_/    \\_\\_____|_| \\_|_____|_| \\_|\\_____|          |_| \\_/_/    \\_\\_|  \\_\\\n\n");                                                                                                            
			printf("\n\t\t\t\t\t\t\t\t Due to copyright issues, the name of the games will be changed\n\n");
			printf("\t\t\t\t\t\t\t\t\t =======================================\n");
			printf("\t\t\t\t\t\t\t\t\t| 1. STATION MANAGER                   |\n");
			printf("\t\t\t\t\t\t\t\t\t| 2. CENSUS SYSTEM                     |\n");
			printf("\t\t\t\t\t\t\t\t\t| 3. MONSTERS AND WHERE TO FIND THEM   |\n");
			printf("\t\t\t\t\t\t\t\t\t| 4. THE MATCHMAKER                    |\n");
			printf("\t\t\t\t\t\t\t\t\t| 5. OTHELLO                           |\n");
			printf("\t\t\t\t\t\t\t\t\t| 6. COLLECTOR OF STARS                |\n");
			printf("\t\t\t\t\t\t\t\t\t| 7. GOAT HUNTER                       |\n");
			printf("\t\t\t\t\t\t\t\t\t| 0. BACK TO MENU                      |\n");
			printf("\t\t\t\t\t\t\t\t\t =======================================\n");
			printf("\t\t\t\t\t\t\t\t\t>> ");
			option = getch();
			printf("%c\n", option);
		}while(option-'0'<0 || option-'0'>7);
		switch(option-'0'){
			case 1:
				stationManager_game();//original name = kereta aPHi
				// implements Multiple Linked Lists and Breadth First Transversal
				break;
			case 2:
				censusSystem_game();// original name = The Census Team
				// implements hashtable using pearson hash function, implementing separate chaining to handle collisions, and file processing
				break;
			case 3:
				// original name = Handler Book
				break;
			case 4:
				// original name = Couple Vinder
				break;
			case 5:
				// original name = Feel Good Othello
				break;
			case 6:
				// original name = SUDUT and Precious Stars
				break;
			case 7:
				// original name = Chasing Goat
				break;
			default:
				return;
				break;				
		}
		system("cls");
		}while(option-'0'!=0);
}

void subMenu_selfTraining(){
	char option;
	do{
		do{
			system("cls");
			printf("\t\t\t   _____ ______ _      ______   _______ _____            _____ _   _ _____ _   _  _____ \n");
			printf("\t\t\t  / ____|  ____| |    |  ____| |__   __|  __ \\     /\\   |_   _| \\ | |_   _| \\ | |/ ____|\n");
			printf("\t\t\t | (___ | |__  | |    | |__       | |  | |__) |   /  \\    | | |  \\| | | | |  \\| | |  __ \n");
			printf("\t\t\t  \\___ \\|  __| | |    |  __|      | |  |  _  /   / /\\ \\   | | | . ` | | | | . ` | | |_ |\n");
			printf("\t\t\t  ____) | |____| |____| |         | |  | | \\ \\  / ____ \\ _| |_| |\\  |_| |_| |\\  | |__| |\n");
			printf("\t\t\t |_____/|______|______|_|         |_|  |_|  \\_\\/_/    \\_\\_____|_| \\_|_____|_| \\_|\\_____|\n\n");
			printf("\t\t\t\t\t\t\t ==========================\n");
			printf("\t\t\t\t\t\t\t| 1. WEREWOLF              |\n");
			printf("\t\t\t\t\t\t\t| 2. HANGMAN               |\n");
			printf("\t\t\t\t\t\t\t| 3. TIC TAC TOE           |\n");
			printf("\t\t\t\t\t\t\t| 4. OPERCOOKED            |\n");
			printf("\t\t\t\t\t\t\t| 5. SNAKES                |\n");
			printf("\t\t\t\t\t\t\t| 0. BACK TO MENU          |\n");
			printf("\t\t\t\t\t\t\t ==========================\n");
			printf("\t\t\t\t\t\t\t>> ");
			option = getch();
			printf("%c\n", option);
		}while(option-'0'<0 || option-'0'>6);
		switch(option-'0'){
			case 1:
				ww_game(); 
				// implements selection, repetition, and struct manipulation
				break;
			case 2:
				hangman_game(); // Algorithm Bootcamp: Final Project (team) -> also improved and altered
				// implements linked lists, padding, file processing, repetition and functions, and string manipulation
				break;
			case 3:
				tictactoe_game(); // improved tictactoe with arrow key to select
				// implements selection, repetition, receiving key inputs
				break;
			case 4:
				opercooked_game(); // Algorithm Bootcamp: season 2 -> created by myself, but haven't added the linked list feature
				// implements struct manipulation
				break;
			case 5:
				snakes_game();
				// implements file processing, linked lists, padding, game loop, accepting key inputs, and altering consoles.
				break;
			default:
				return;
				break;				
		}
		system("cls");
		}while(option-'0'!=0);
}

void subMenu_preTraining(){
	char option;
	do{
		do{
			system("cls");
			printf("\t\t\t  _____   _____   ______   _______  _____             _____  _   _  _____  _   _   _____            _   _            _____   \n");
			printf("\t\t\t |  __ \\ |  __ \\ |  ____| |__   __||  __ \\     /\\    |_   _|| \\ | ||_   _|| \\ | | / ____|          | \\ | |    /\\    |  __ \\  \n");
			printf("\t\t\t | |__) || |__) || |__       | |   | |__) |   /  \\     | |  |  \\| |  | |  |  \\| || |  __   ______  |  \\| |   /  \\   | |__) | \n");
			printf("\t\t\t |  ___/ |  _  / |  __|      | |   |  _  /   / /\\ \\    | |  | . ` |  | |  | . ` || | |_ | |______| | . ` |  / /\\ \\  |  _  /  \n");
			printf("\t\t\t | |     | | \\ \\ | |____     | |   | | \\ \\  / ____ \\  _| |_ | |\\  | _| |_ | |\\  || |__| |          | |\\  | / ____ \\ | | \\ \\  \n");
			printf("\t\t\t |_|     |_|  \\_\\|______|    |_|   |_|  \\_\\/_/    \\_\\|_____||_| \\_||_____||_| \\_| \\_____|          |_| \\_|/_/    \\_\\|_|  \\_\\ \n\n");
			printf("\n\t\t\t\t\t\t\t Due to copyright issues, the name of the games will be changed\n\n");
			printf("\t\t\t\t\t\t\t\t ==========================\n");
			printf("\t\t\t\t\t\t\t\t| 1. RAMBO                 |\n");
			printf("\t\t\t\t\t\t\t\t| 2. FOSSIL HUNTER         |\n");
			printf("\t\t\t\t\t\t\t\t| 3. MONOPOLY              |\n");
			printf("\t\t\t\t\t\t\t\t| 4. DUNGEON ESCAPE        |\n");
			printf("\t\t\t\t\t\t\t\t| 5. MONSTER MAZE          |\n");
			printf("\t\t\t\t\t\t\t\t| 0. BACK TO MENU          |\n");
			printf("\t\t\t\t\t\t\t\t ==========================\n");
			printf("\t\t\t\t\t\t\t\t>> ");
			option = getch();
			printf("%c\n", option);
		}while(option-'0'<0 || option-'0'>5);
		switch(option-'0'){
			case 1:
				rambo_game(); // forgot the original name, but i think it's also rambo
				// implements standard selection and repetition
				break;
			case 2:
				fossilHunter_game(); // original name = Possil Hunter
				// implements standard selection and repetition + randomizer
				break;
			case 3:
				monopoly_game(); // original name = Mari Menjadi Kaya
				// implements selection, game loop, file processing, padding, and monopoly logic
				break;
			case 4:
				dungeonEscape_game(); // original name = Dungeon Master
				// implements randomizer, game loop, accepting key inputs
				break;
			case 5:
				monsterMaze_game(); // original name = Funescape
				// implements accepting key inputs, breadth first traversal, game loop, randomizer, game logic
				break;
			default:
				return;
				break;				
		}
		system("cls");
		}while(option-'0'!=0);
}

void subMenu_aboutThisGame(){
	system("cls");
	printf("\n\tThis is a compilation of games created by me (although some of them are finished through some help from friends, mentor, and internet).\n\n");
	printf("\tIt's purpose is to help me master C programming and for fun (who knows if i want to play them one day)\n\n");
	printf("\tPlease take note that all of these games are derived from real games that have been created before / from assignments from NAR 21-1\n\n");
	printf("\t** NAR 21-1 = New Assistant Recruitment 21 - 1 , by Software Laboratory Center, Bina Nusantara University\n\n");
	printf("\tThat's all, Have Fun!!\n\n");
	printf("\tPress enter to continue..");
	getchar();
}

int main(){
	char option;
	do{
		do{
			system("cls");
			printf("\t\t\t  __  __ _____ _   _ _____ _____          __  __ ______    _____ ____  __  __ _____ _____ _            _______ _____ ____  _   _ \n");
			printf("\t\t\t |  \\/  |_   _| \\ | |_   _/ ____|   /\\   |  \\/  |  ____|  / ____/ __ \\|  \\/  |  __ \\_   _| |        /\\|__   __|_   _/ __ \\| \\ | |\n");
			printf("\t\t\t | \\  / | | | |  \\| | | || |  __   /  \\  | \\  / | |__    | |   | |  | | \\  / | |__) || | | |       /  \\  | |    | || |  | |  \\| |\n");
			printf("\t\t\t | |\\/| | | | | . ` | | || | |_ | / /\\ \\ | |\\/| |  __|   | |   | |  | | |\\/| |  ___/ | | | |      / /\\ \\ | |    | || |  | | . ` |\n");
			printf("\t\t\t | |  | |_| |_| |\\  |_| || |__| |/ ____ \\| |  | | |____  | |___| |__| | |  | | |    _| |_| |____ / ____ \\| |   _| || |__| | |\\  |\n");
			printf("\t\t\t |_|  |_|_____|_| \\_|_____\\_____/_/    \\_\\_|  |_|______|  \\_____\\____/|_|  |_|_|   |_____|______/_/    \\_\\_|  |_____\\____/|_| \\_|\n\n");                                                                                                                     
			printf("\t\t\t\t\t\t\t\t\t ============================\n");
			printf("\t\t\t\t\t\t\t\t\t| PICK SUBMENU:             |\n");
			printf("\t\t\t\t\t\t\t\t\t| 1. SELF TRAINING          |\n");
			printf("\t\t\t\t\t\t\t\t\t| 2. PRE TRAINING NAR 21-1  |\n");
			printf("\t\t\t\t\t\t\t\t\t| 3. CORE TRAINING NAR 21-1 |\n");
			printf("\t\t\t\t\t\t\t\t\t| 4. ABOUT                  |\n");
			printf("\t\t\t\t\t\t\t\t\t| 0. EXIT GAME              |\n");
			printf("\t\t\t\t\t\t\t\t\t ============================\n");
			printf("\t\t\t\t\t\t\t\t\t>> ");
			option = getch();
			printf("%c\n", option);
		}while(option-'0'<0 || option-'0'>4);
		system("cls");
		switch(option-'0'){
			case 1:
				subMenu_selfTraining();
				break;
			case 2:
				subMenu_preTraining();
				break;
			case 3:
				subMenu_coreTraining();
				break;
			case 4:
				subMenu_aboutThisGame();
				break;
			default:
				return 0;
				break;				
		}
		system("cls");
		}while(option-'0'!=0);
}

