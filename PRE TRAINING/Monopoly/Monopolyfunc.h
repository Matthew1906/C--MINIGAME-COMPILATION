#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

int monopoly_index, monopoly_index2, monopoly_numplayer;
char monopoly_map[105][205]={0};

void monopoly_delay (int numsec){ // time dilation
	clock_t start_time = clock();
	while(clock()<start_time+numsec*1000);
}
struct monopoly_player{
	char name[10]; //player name
	char icon; // player symbol
	int money; // player money
	int assets; // player assets
	int row1; // player position in y axis
	int col1; // player position in x axis
	bool lose = false; // player status (win/lose)
	int location; // player block location
	bool angel = false ;// ownership of angelcard.
	bool freeze = false; // determine if the player can move
	bool travel = false; // determine if the player can travel
	int ownership[28]; // location of owned islands
};

struct monopoly_block{
	char name[50];
	int cost;
	char info[50];
	int owner = -1;
	int multiplier = 1;
};
// print map function
void monopoly_currmap(struct monopoly_player *players, struct monopoly_block *blocks, int curr){
	// sort players in the leaderboard (descending based on total money+assets)
	int sort[monopoly_numplayer];
	for(int i=0;i<monopoly_numplayer;i++){
		sort[i] = i;
	}
	for(int j=monopoly_numplayer;j>0;j--){
		for(int k=1;k<monopoly_numplayer;k++){
			if((players[sort[k]].money+players[sort[k]].assets)>(players[sort[k-1]].money+players[sort[k-1]].assets)){
				int temp = sort[k];
				sort[k]=sort[k-1];
				sort[k-1]= temp;
			}
		}
	}
	//PRINT MAP
	printf("\n");
	for(int i=0;i<monopoly_index;i++){
		printf(" %s", monopoly_map[i]);
		// PRINT LEADERBOARD
		if(i==2){
			printf(" Leaderboard");
		}
		else if(i==3){
			printf(" ===========");
		}
		else if(i==5 || i==5+monopoly_numplayer+1){
			printf(" -----------------------------------------");
		}
		else if(i==6){
			printf(" | 1. %-8s %5d K (%5d K + %5d K)|", players[sort[0]].name, players[sort[0]].money+players[sort[0]].assets, players[sort[0]].money, players[sort[0]].assets);
		}
		else if(i==7){
			printf(" | 2. %-8s %5d K (%5d K + %5d K)|", players[sort[1]].name, players[sort[1]].money+players[sort[1]].assets, players[sort[1]].money, players[sort[1]].assets);
		}
		else if(i==8 && monopoly_numplayer>2){
			printf(" | 3. %-8s %5d K (%5d K + %5d K)|", players[sort[2]].name, players[sort[2]].money+players[sort[2]].assets, players[sort[2]].money, players[sort[2]].assets);
		}
		else if(i==9 && monopoly_numplayer>3){
			printf(" | 4. %-8s %5d K (%5d K + %5d K)|", players[sort[3]].name, players[sort[3]].money+players[sort[3]].assets, players[sort[3]].money, players[sort[3]].assets);
		}
		// print BLOCK INFO
		else if(i==monopoly_numplayer+9){
			printf(" Block Information");
		}
		else if(i==monopoly_numplayer+10){
			printf(" =================");
		}
		else if(players[curr].location==14 && i==monopoly_numplayer+11){
			printf(" Welcome to the Festival Block!");
		}
		else if(players[curr].location==14 && i==monopoly_numplayer+12){
			printf(" Choose any of your island~");
		}
		else if(players[curr].location==14 && i==monopoly_numplayer+13){
			printf(" The Chosen island price will be doubled!");
		}
		else if(strcmp(blocks[players[curr].location].info, "island")==0 && (i==monopoly_numplayer+11||i==monopoly_numplayer+20)){
			printf(" ------------------------------");
		}
		else if(strcmp(blocks[players[curr].location].info, "island")==0 && (i==monopoly_numplayer+12 || i==monopoly_numplayer+16 || i==monopoly_numplayer+19)){
			printf(" |                             |");
		}
		else if(strcmp(blocks[players[curr].location].info, "island")==0 && i==monopoly_numplayer+13){
			printf(" |   Island Name :             |");
		}
		else if(strcmp(blocks[players[curr].location].info, "island")==0 && i==monopoly_numplayer+14){
			printf(" |   %-10s                |",blocks[players[curr].location].name);
		}	
		else if(strcmp(blocks[players[curr].location].info, "island")==0 && i==monopoly_numplayer+15){
			printf(" |=============================|");
		}
		else if(strcmp(blocks[players[curr].location].info, "island")==0 && i==monopoly_numplayer+17){
			if(blocks[players[curr].location].owner==-1){
				printf(" |   Fee         : %6d K    |", blocks[players[curr].location].cost);
			}
			else if(blocks[players[curr].location].owner!=-1){
				printf(" |   Rent        : %6d K    |", blocks[players[curr].location].multiplier*((3*blocks[players[curr].location].cost)/2));
			}
		}
		else if(strcmp(blocks[players[curr].location].info, "island")==0 && i==monopoly_numplayer+18){
			if(blocks[players[curr].location].owner!=-1){
				printf(" |   Status      : ");
				char status[8];
				if(blocks[players[curr].location].multiplier==1){
					strcpy(status, "Normal");
				}
				else if(blocks[players[curr].location].multiplier==2){
					strcpy(status, "Price x2");
				}
				else if(blocks[players[curr].location].multiplier==4){
					strcpy(status, "Price x4");
				}
				else if(blocks[players[curr].location].multiplier==8){
					strcpy(status, "Price x8");
				}
				printf("%8s    |", status);
			}
			else printf(" |                             |");	
		}
		// PRINT CURRENT PLAYER INFO
		else if(i==monopoly_numplayer+24){
			printf(" Current Player");
		}
		else if(i==monopoly_numplayer+25){
			printf(" ==============");
		}
		else if(i==monopoly_numplayer+26 || i==monopoly_numplayer+34){
			printf(" -----------------------");
		}
		else if(i==monopoly_numplayer+27||i==monopoly_numplayer+29||i==monopoly_numplayer+32){
			printf(" |                     |");
		}
		else if(i==monopoly_numplayer+28){
			printf(" |   Name   : %-8s |", players[curr].name);
		}
		else if(i==monopoly_numplayer+30){
			printf(" |   Money  : %6d K |", players[curr].money);
		}
		else if(i==monopoly_numplayer+31){
			printf(" |   Total  : %6d K |", players[curr].money+players[curr].assets);
		}
		else if(i==monopoly_numplayer+33){
			printf(" |                  P%d |", curr+1);
		}
		printf("\n");
	}	
}
// CHECK EACH PLAYERS CONDITION (WIN/LOSE/STASIS)
int monopoly_cekwin(struct monopoly_player *players){
	for(int i=0;i<monopoly_numplayer;i++){
		if(players[i].lose == true){
			return -1;
		}
	}
	return 1;
}

// MOVE PLAYER'S POSITION
void monopoly_find(int i, struct monopoly_player *players){
	monopoly_map[players[i].row1][players[i].col1]=' ';
	if(i%2==0)players[i].col1 = 5;
	else players[i].col1 = 7;
	if(i<2)players[i].row1 = 37;
	else players[i].row1= 38;
	if(players[i].location<=7){
		for(int j=0;j<players[i].location;j++){
			players[i].row1-=5;
		}
	}
	else if(players[i].location>7 && players[i].location<=14){
		for(int j=0;j<7;j++){
			players[i].row1-=5;
		}
		for(int k=0;k<players[i].location-7;k++){
			players[i].col1+=14;
		}
	}
	else if(players[i].location>14 && players[i].location<=21){
		for(int j=0;j<7;j++){
			players[i].row1-=5;
		}
		for(int k=0;k<7;k++){
			players[i].col1+=14;
		}
		for(int l=0;l<players[i].location-14;l++){
			players[i].row1+=5;
		}
	}
	else if(players[i].location>21 && players[i].location<=27){
		for(int k=0;k<7;k++){
			players[i].col1+=14;
		}
		for(int l=0;l<players[i].location-21;l++){
			players[i].col1-=14;
		}
	}
	monopoly_map[players[i].row1][players[i].col1]= players[i].icon;
}

// PLAYER'S ACTIVITY BASED ON THE BLOCK THEY ENTERED
void monopoly_todo(struct monopoly_player *players, int curr, struct monopoly_block*blocks){
	if(strcmp(blocks[players[curr].location].info, "island")==0){
		// EMPTY ISLAND
		if(blocks[players[curr].location].owner==-1 && players[curr].money>=blocks[players[curr].location].cost){
			char pilihan[4];
			do{
				printf("  Do you want to buy this island for %d K [ Yes | No ]? ", blocks[players[curr].location].cost);
				scanf("%s", pilihan);
				getchar();
			}while(strcmpi(pilihan,"Yes")!=0 && strcmpi(pilihan,"No")!=0);
			if(strcmpi(pilihan,"Yes")==0){
				players[curr].money-=blocks[players[curr].location].cost;
				blocks[players[curr].location].owner= curr;
				players[curr].assets+=blocks[players[curr].location].cost;
				int row2, col2;
				if(players[curr].location>=1 && players[curr].location<7){
					row2 = 36, col2 = 12;
					for(int i=0;i<players[curr].location;i++){
						row2-=5;
					}
				}
				else if(players[curr].location>=8 && players[curr].location<14){
					row2 = 1, col2 = 12;
					for(int i=7;i<players[curr].location;i++){
						col2+=14;
					}
				}
				else if(players[curr].location>=15 && players[curr].location<21){
					row2 = 1, col2 = 110;
					for(int i=14;i<players[curr].location;i++){
						row2+=5;
					}
				}
				else if(players[curr].location>=22 && players[curr].location<28){
					row2 = 36, col2 = 110;
					for(int i=21;i<players[curr].location;i++){
						col2-=14;
					}
				}
				monopoly_map[row2][col2] = 'P';
				monopoly_map[row2][col2+1] = curr+1+'0';
			}
		}
		else if(blocks[players[curr].location].owner==-1 && players[curr].money<blocks[players[curr].location].cost){
			printf("  You don't have enough money!\n");
			}
		//OCCUPIED ISLAND
		else if(blocks[players[curr].location].owner!=-1){
			printf("  Oops, you landed on %s's land~ You need to pay a rent!\n", players[blocks[players[curr].location].owner].name);
			printf("  Rent : %d K\n", blocks[players[curr].location].multiplier*((3*blocks[players[curr].location].cost)/2));
			int rent = 	blocks[players[curr].location].multiplier*((3*blocks[players[curr].location].cost)/2), rent_flag=0;	
			if(players[curr].angel==true){
				char pilihan1[10];
					do{
						printf("  Use Angel Card [ Yes | No ]?");
						scanf("%s", pilihan1);
					}while(strcmpi(pilihan1,"Yes")!=0 && strcmpi(pilihan1,"No")!=0);
					if(strcmpi(pilihan1, "Yes")==0){
						players[curr].angel = false;
						printf("  Angel Card has been used!\n");
						rent_flag=1;
					}	
			}
			if(rent_flag==0){
				players[blocks[players[curr].location].owner].money+=rent;
				if(players[curr].money>=rent){
					players[curr].money-=rent;
				}
				else{
					rent -= players[curr].money;
					if(players[curr].assets>=rent){
						int index = 0;	
						for(int i=0;i<28;i++){
							if(blocks[i].owner==curr){
								players[curr].ownership[index] = i;
								index++;
							}
						}
						int losing1;
						do{
							printf("  Your money isn't enough to pay rent!\n");
							printf("  1. Sell Island\n");
							printf("  2. Bankrupt\n");
							printf("  Choose [ 1 | 2 ]: ");
							scanf("%d", &losing1);
						}while(losing1< 1 || losing1> 2);
						if(losing1== 1){
							int currmoney =0;
							while(currmoney<rent){
								int index = 0;	
								for(int i=0;i<28;i++){
									if(blocks[i].owner==curr){
										players[curr].ownership[index] = i;
										index++;
									}
								}
								printf("  Choose the island you want to sell!\n");
								int sell_flag=0;
								int sell;
								do{
									sell_flag=0;
									for(int i=0;i<index;i++){
										printf("  %d. %s - %d\n", players[curr].ownership[i], blocks[players[curr].ownership[i]].name, blocks[players[curr].ownership[i]].cost);
									}
									printf("  0. Back\n");
									printf("  >> ");
									scanf("%d", &sell);
									getchar();
									if(sell==0)sell_flag = 1;
									else{
										for(int i=0;i<index;i++){
											if(sell== players[curr].ownership[i]){
												sell_flag= 2;
												break;
											}
										}
									}
								}while(sell_flag==0);
								if(sell_flag==1){
									printf("  %s are bankrupt. The game will be ended.\n", players[curr].name);
									players[curr].lose = true;
									players[curr].money = 0;
									players[curr].assets = 0;
									break;
								}
									currmoney += blocks[sell].cost;
									blocks[sell].owner = -1;
									players[curr].assets-=blocks[sell].cost;
									int row2, col2;
									int location = sell;
									if(location>=1 && location<7){
										row2 = 36, col2 = 12;
										for(int i=0;i<location;i++){
											row2-=5;
										}
									}
									else if(location>=8 && location<14){
										row2 = 1, col2 = 12;
										for(int i=7;i<location;i++){
											col2+=14;
										}
									}
									else if(location>=15 && location<21){
										row2 = 1, col2 = 110;
										for(int i=14;i<location;i++){
											row2+=5;
										}
									}
									else if(location>=22 && location<28){
										row2 = 36, col2 = 110;
										for(int i=21;i<location;i++){
											col2-=14;
										}
									}
									monopoly_map[row2][col2] = ' ';
									monopoly_map[row2][col2+1] = ' ';
							}
							players[curr].money = currmoney-rent;							
						}
						else{
							printf("  %s are bankrupt. The game will be ended.\n", players[curr].name);
							players[curr].lose = true;
							players[curr].money = 0;
							players[curr].assets = 0;
						}
					}
					else{
						printf("  %s are bankrupt. The game will be ended.\n", players[curr].name);
						players[curr].lose = true;
					}
				}
			}
			blocks[players[curr].location].multiplier = 1;
		}
	}
	// EXTRA CHANCE CARD
	else if(players[curr].location==8 || players[curr].location==16){
		srand(time(0));
		int chanceit = (rand()%10)+1;
		if(chanceit%5==0){
			players[curr].angel = true;
			printf("  Congratulations~ You got an angel card! (^v^)/\n");
			getchar();
		}
	}
	// tax
	else if(players[curr].location== 26){
		int tax = (players[curr].money+ players[curr].assets)/5;
		printf("  %d K will be taken for tax!\n", tax);
		if(players[curr].money>=tax){
			players[curr].money-=tax;
		}
		else if(players[curr].money+players[curr].assets>=tax){
			//sell or bankrupt
			int index = 0;	
			for(int i=0;i<28;i++){
				if(blocks[i].owner==curr){
					players[curr].ownership[index] = i;
					index++;
				}
			}
			tax -= players[curr].money;
			int losing;
			do{
				printf("  Your money isn't enough to pay tax!\n");
				printf("  1. Sell Island\n");
				printf("  2. Bankrupt\n");
				printf("  Choose [ 1 | 2 ]: ");
				scanf("%d", &losing);
			}while(losing!= 1 && losing!=2);
			if(losing==1){
					int currmoney =0;
					while(currmoney<tax){
						printf("  Choose the island you want to sell!\n");
						int sell_flag=0;
						int sell;
						do{
							for(int i=0;i<index;i++){
								printf("  %d. %s - %d\n", players[curr].ownership[i], blocks[players[curr].ownership[i]].name, blocks[players[curr].ownership[i]].cost);
							}
							printf("  0. Back\n");
							printf(" >> ");
							scanf("%d", &sell);
							if(sell==0)sell_flag = 1;
							for(int i=0;i<index;i++){
								if(sell== players[curr].ownership[i]){
									sell_flag= 2;
									break;
								}
							}
						}while(sell_flag==0);
						if(sell_flag==1){
							printf("  %s are bankrupt. The game will be ended.\n", players[curr].name);
							players[curr].lose = true;
							players[curr].money = 0;
							players[curr].assets = 0;
						}
						else if (sell_flag==2){
							currmoney += blocks[sell].cost;
							blocks[sell].owner = -1;
							players[curr].assets-=blocks[sell].cost;
							int row2, col2;
							int location = sell;
							if(location>=1 && location<7){
								row2 = 36, col2 = 12;
								for(int i=0;i<location;i++){
									row2-=5;
								}
							}
							else if(location>=8 && location<14){
								row2 = 1, col2 = 12;
								for(int i=7;i<location;i++){
									col2+=14;
								}
							}
							else if(location>=15 && location<21){
								row2 = 1, col2 = 110;
								for(int i=14;i<location;i++){
									row2+=5;
								}
							}
							else if(location>=22 && location<28){
								row2 = 36, col2 = 110;
								for(int i=21;i<location;i++){
									col2-=14;
								}
							}
							monopoly_map[row2][col2] = ' ';
							monopoly_map[row2][col2+1] = ' ';
						}
					}
					players[curr].money = currmoney-tax;
					tax = 0;
				}
				else if(losing==2){
					printf("  %s are bankrupt. The game will be ended.\n", players[curr].name);
					players[curr].lose = true;
					players[curr].money = 0;
					players[curr].assets = 0;
				}
			}
		else{
			printf("  %s are bankrupt. The game will be ended.\n", players[curr].name);
			players[curr].lose = true;
			players[curr].money = 0;
			players[curr].assets = 0;
		}				
	}
	// jail
	else if(players[curr].location == 7){
		printf("  1 more turn, and you'll be out of jail\n");
		printf("  This message will disappear after 1 sec");
		players[curr].freeze = true;
		monopoly_delay(1);
		system("cls");
		monopoly_currmap(players, blocks, curr);
	}
	// festival
	else if(players[curr].location == 14){
		printf("  Choose the island where you will hold the festival:\n");
		int index = 0;	
		for(int i=0;i<28;i++){
			if(blocks[i].owner==curr){
				players[curr].ownership[index] = i;
				index++;
			}
		}
		int host_flag=0;
		int host;
		do{
			getchar();
			for(int i=0;i<index;i++){
				int before = blocks[players[curr].ownership[i]].multiplier*((3*blocks[players[curr].ownership[i]].cost)/2);
				printf("  %d. %s |  Rent Price %d -> %d\n", players[curr].ownership[i], blocks[players[curr].ownership[i]].name, before, 2*before);
			}
			printf("  0. Cancel\n");
			printf("  >> ");
			scanf("%d", &host);
			if(host==0)host_flag = 1;
			for(int i=0;i<index;i++){
				if(host== players[curr].ownership[i]){
					host_flag= 2;
					break;
				}
			}
		}while(host_flag==0);
		if(host_flag==2){
			if(blocks[host].multiplier<=4)blocks[host].multiplier*=2;
			printf("  Yay! The chosen block rent price has been doubled!\n");
			getchar();
		}
	}
	// World travel
	else if(players[curr].location == 21){
		players[curr].travel = true;
		int travel;
		do{
			printf("  Choose any block that you want to go [0-27]: ");
			scanf("%d", &travel);
		}while(travel< 0 || travel>27);
		//instantly travel, but the player can do what he/she wants in the next round
		// if the player pass start, won't get 200 K money
		players[curr].location = travel;
		monopoly_find(curr, players);
	}
}
// GAME LOOP
void monopoly_gamemenu(struct monopoly_player* players, struct monopoly_block *blocks){
	system("cls");
	
	// SETUP
	for(int i=0;i<monopoly_numplayer;i++){
		monopoly_map[players[i].row1][players[i].col1] = players[i].icon;
		players[i].money = 1000; // INITIAL MONEY 1000 K
		players[i].location = 0; // PLAYERS ARE IN GO BLOCK (NUMBER 0)
		players[i].assets = 0; // ASSETS = 0
	}
	int check= monopoly_cekwin(players), curr=0, round=1, flag=1;
	monopoly_currmap(players, blocks, curr);
	//START GAME
	do{
		// CALCULATE ROUND
		if(curr>monopoly_numplayer-1){
			round++;
			curr=0;
		}
		system("cls");
		monopoly_currmap(players, blocks, curr);
		if(players[curr].freeze==true){ // for those in jail
			printf("  Sorry, but you're in jail!\n");
			printf("  You'll be able to move in the next round!\n");
			players[curr].freeze= false;
			curr++;
			printf("  Press any key to continue...");
			getch();
			continue;
		}
		if(players[curr].travel==true){
			monopoly_todo(players, curr, blocks);
			players[curr].travel = false;
			if(players[curr].lose==true)break;
			curr++;
			printf("  Press any key to continue...");
			getch();
			continue;
		}		
		printf("  [Press Q if you want to give up]\n");
		printf("  Press any key to roll dice...\n");
		printf("  Rolled dice: %d\n", round);
		char dice;
		dice = getch();
		if(dice=='q' && round>2){
			flag=0;
			break;
		}
		else{
			if(dice =='q'){
				printf("  You can't give up on 1~2 round!\n");
				printf("  Press any key to reroll...");
				getch();
				continue;
			}
			else{
				srand(time(0));
				int move = (rand()%12)+1;
				players[curr].location+=move;
				// IF PASS GO BLOCK, RECEIVE 200 K MONEY
				if(players[curr].location>27){
					players[curr].location-=27;
					players[curr].money+=200;
					printf("  You got 200 K money from the Bank\n");
					printf("  Press any key to continue...");
					getch();
				}
				//MOVE AND DETERMINE PLAYER'S ACTIONS
				monopoly_find(curr, players);
				system("cls");
				monopoly_currmap(players, blocks, curr);
				monopoly_todo(players, curr, blocks);
				if(players[curr].lose==true)break;				
			}
		}
		check = monopoly_cekwin(players);
		printf("  Press any key to continue...");
		getch();
		curr++;
	}while(check==1 && flag==1);
	if(flag==0){
		printf("  %s chose to give up!\n\n");
		getchar();	
	}
	int sort[monopoly_numplayer];
	for(int i=0;i<monopoly_numplayer;i++){
		sort[i] = i;
	}
	int win = 0;
	for(int k=0;k<monopoly_numplayer;k++){
		if((players[k].money+players[k].assets)>(players[win].money+players[win].assets)){
			win = k;
		}
	}
	system("cls");
	printf(" %s win the game! Congratulations~\n", players[win].name);
	printf(" List of assets: \n");
	for(int i=0;i<28;i++){
		if(blocks[i].owner==win){
			printf(" %d. %s %d K\n", i, blocks[i].name, blocks[i].cost);
		}
	}
	printf(" Total Assets: %d K\n", players[win].assets);
	printf(" Money: %d K\n", players[win].money);
	printf(" Total (Money + Assets): %d K\n\n", players[win].money+players[win].assets);
	FILE *fwinner = fopen(".\\PRE TRAINING\\Monopoly\\winnerlist.txt", "a");
	fprintf(fwinner, "%s %d\n", players[win].name, players[win].money+players[win].assets);
	fclose(fwinner);
	printf(" Press Enter to continue!");
	getchar();
}

//SETUP GAME
void monopoly_setup(struct monopoly_player *players){
	//INPUT PLAYER'S NAME
	for(int i=1;i<=monopoly_numplayer;i++){
		int len, takenFlag;
		char name[255];
		do{
			takenFlag = 1;
			printf(" Input player %d name [must be 3 or 8 characters ]: ", i);
			scanf("%s", name);
			getchar();
			len = strlen(name);
			for(int j=0;j<i-1;++j){
				if(strcmp(players[j].name, name)==0){
					takenFlag = 0;
					break;
				}
			}
			if(len<3 || len>8){
				takenFlag=0;
			}
		}while(takenFlag==0);
		strcpy(players[i-1].name, name);
	}
	// GIVE SYMBOLS AND INITIAL LOCATION
	char icons = '#';
	for(int j=0;j<monopoly_numplayer;j++){
		players[j].icon = icons;
		icons++;
		if(j%2==0)players[j].col1 = 5;
		else players[j].col1 = 7;
		if(j<2)players[j].row1 = 37;
		else players[j].row1= 38;
	}
	// FILE PROCESSING TO SCAN MAP
	FILE *fmap = fopen(".\\PRE TRAINING\\Monopoly\\monopolyMap.txt", "r");
	monopoly_index =0;
	while(fscanf(fmap, "%[^\n]\n",monopoly_map[monopoly_index])!=EOF){
		monopoly_index++;
	}
	fclose(fmap);
}
// START GAME
void monopoly_playgame(){
	//setup block data.
	struct monopoly_block blocks[28];
	FILE *fblock = fopen(".\\PRE TRAINING\\Monopoly\\block_information.txt", "r");
	int monopoly_index2=0;
	while(fscanf(fblock, "%[^#]#%d#%s\n", blocks[monopoly_index2].name, &blocks[monopoly_index2].cost, blocks[monopoly_index2].info)!=EOF){
		monopoly_index2++;
	}
	fclose(fblock);
	system("cls");
	char choose2;
	do{
		printf(" Choose how many players to participate in the game[2-4]: ");
		choose2 = getchar();
		fflush(stdin);
	}while(choose2-'0'<2 || choose2-'0'>4);
	struct monopoly_player players[choose2-'0'];
	monopoly_numplayer = choose2-'0';
	system("cls");
	monopoly_setup(players);
	printf(" The Game will be started....\n");	
	monopoly_delay(5);
	monopoly_gamemenu(players, blocks);
	return;
}
void monopoly_highscore(){
	system("cls");
	int arr[105];
	char rank[105][105];
	int n = 0;
	FILE *fwinner = fopen(".\\PRE TRAINING\\Monopoly\\winnerlist.txt", "r");
	while(fscanf(fwinner, "%s %d\n",&rank[n], &arr[n])!=EOF){
		n++;
	}
	fclose(fwinner);
	int sorting[n];
	for(int i=0;i<n;i++){
		sorting[i]= i;
	}
	for(int j=n;j>0;j--){
		for(int i=1;i<n;i++){
			if(arr[sorting[i]]>arr[sorting[i-1]]){
				int temp = sorting[i];
				sorting[i] = sorting[i-1];
				sorting[i-1] = temp;
			}
		}
	}
	printf(" List Winner!\n");
	printf(" ------------\n");
	for(int i=0;i<n;i++){
		printf(" %d. %s %d K\n", i+1, rank[sorting[i]], arr[sorting[i]]);
	}
	printf("\n");
	printf(" Press any key to continue...");
	getch();
}

void monopoly_htp(){
	system("cls");
	printf(" About this game:\n\n");
	printf(" 1. 1000 K money will be given out to all players at the first round.\n");
	printf(" 2. Whenever you land on a block that no one owns, you can buy island on that block.\n");
	printf(" Once you own the block, other players must pay rent if they landed on your island.\n");
	printf(" 3. If you land on a Chance Card, you will get the chance to get Angel Card~\n");
	printf(" 4. When you pass Go, you will automatically receive 200 K money from the bank.\n");
	printf(" 5. Bankruptcy: You are automatically lost if you can't pay the rent.\n");
	printf(" 6. If one player goes bankrupt, the game is done\n");
	printf(" 7. The winner will be determined from the leaderboard.\n\n");
	printf(" Enjoy and Have fun!\n");
	getchar();
	printf(" Press Enter to continue!");
	getchar();
	return;
}

void monopoly_game(){ 
	char choose1;
	do{
		do{
			system("cls");			                                                                                                     
			printf("\n\t88b           d88                                                                   88         \n");      
			printf("\t888b         d888                                                                   88              \n"); 
			printf("\t88 8b       d8'88                                                                   88               \n");
			printf("\t88  8b     d8  88   ,adPPYba,   8b,dPPYba,    ,adPPYba,   8b,dPPYba,    ,adPPYba,   88  8b       d8  \n");
			printf("\t88   8b   d8   88  a8       8a  88P      8a   a8     8a  88P       8a  a8       8a  88   8b     d8  \n");
			printf("\t88    8b d8    88  8b       d8  88       88  8b       d8  88       d8  8b       d8  88    8b   d8   \n");
			printf("\t88     888     88   8a,   ,a8   88       88   8a,   ,a8   88b,   ,a8    8a,   ,a8   88     8b,d8     \n");
			printf("\t88      8      88     YbbdP     88       88     YbbdP     88 YbbdP      ` YbbdP     88      Y88      \n");
			printf("\t                                                          88                                d8       \n");
			printf("\t                                                          88                               d8        \n\n");
			printf("\t\t\t\t\t\t1. Play\n");
			printf("\t\t\t\t\t\t2. See all the winner\n");	
			printf("\t\t\t\t\t\t3. Basic Information\n");
			printf("\t\t\t\t\t\t4. Exit\n");
			printf("\t\t\t\t\t\t>> ");
			choose1 = getch();
			printf("%c\n", choose1);
		}while(choose1-'0'<1 || choose1-'0'>4);
		switch(choose1){
			case '1':
				monopoly_playgame();
				break;
			case '2':
				monopoly_highscore();	
				break;
			case '3':
				monopoly_htp();
				break;
			case '4':
				break;
		}
	}while(choose1-'0' != 4);
	return;
}
