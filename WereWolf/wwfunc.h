#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
	roles:
	0 = healer;
	1 = werewolves;
	2 = seer;
	3 = villager;
	4 = ww_numWitch;
	5 = ww_numGunner;
*/
void ww_delay (int numsec){
	clock_t start_time = clock();
	while(clock()<start_time+numsec*1000);
}
typedef struct ww_player{
	int roles;
	char names[100];
	int lives =1;
	int bullet=0;
	int cure =0;
};

int ww_numPlayer, ww_numWolf, ww_numHealer, ww_numSeer, ww_numVillager, ww_numGunner, ww_numWitch;
void ww_roles(int ww_numPlayer, struct ww_player *players){
	ww_numHealer=1, ww_numSeer=1, ww_numGunner=0,ww_numWitch=0;
	if(ww_numPlayer>=10){
		ww_numHealer=2;
		ww_numSeer=2;
		ww_numGunner=1;
		ww_numWitch=1;
	}
	ww_numWolf = ww_numPlayer/3, ww_numVillager = ww_numPlayer-ww_numWolf-ww_numSeer-ww_numHealer-ww_numGunner-ww_numWitch;
	printf("\n\t\t\t\t\t\t\tPlease enter each player's name!\n");
	getchar();
	for(int a=0;a<ww_numPlayer;a++){
		printf("\t\t\t\t\t\tPlayer %d: ", a+1);
		scanf("%[^\n]", players[a].names);
		getchar();
	}
	for(int c=0;c<ww_numWolf;c++)players[c].roles=1;
	for(int d=ww_numWolf,e=0;e<ww_numHealer;e++, d++){
		players[d].roles=0;
		players[d].cure=1;
	}
	for(int f=ww_numWolf+ww_numHealer,g=0;g<ww_numSeer;f++,g++)players[f].roles=2;
	for(int h=ww_numWolf+ww_numHealer+ww_numSeer,k=0;k<ww_numWitch;h++,k++){
		players[h].roles = 4;
		players[h].bullet = 1;
		players[h].cure=1;
	}
	for(int i=ww_numWolf+ww_numHealer+ww_numSeer+ww_numWitch,l=0;l<ww_numGunner;i++,l++){
		players[i].roles = 5;
		players[i].bullet = 2;
	}
	for(int j=ww_numWolf+ww_numHealer+ww_numSeer+ww_numWitch+ww_numGunner;j<ww_numPlayer;j++)players[j].roles = 3;
	system("cls");
}
void ww_identity(int ww_numPlayer, struct ww_player *players){
	for(int b=0;b<ww_numPlayer;b++){
		printf("\t\t\t\t\t\t\tPlayer %d : %s, role: ", b+1, players[b].names);
		if(players[b].roles== 0)printf("HEALER\n");
		else if(players[b].roles== 1)printf("WEREWOLF\n");
		else if(players[b].roles== 2)printf("SEER\n");
		else if(players[b].roles== 3)printf("VILLAGER\n");
		else if(players[b].roles== 4)printf("WITCH\n");
		else if(players[b].roles== 5)printf("GUNNER\n");
	}
}
 void ww_logo(){
	printf("			   __        _______ ____  _______        _____  _     _____ \n");
	printf("			   \\ \\      / / ____|  _ \\| ____\\ \\      / / _ \\| |   |  ___|\n");
	printf("			    \\ \\ /\\ / /|  _| | |_) |  _|  \\ \\ /\\ / / | | | |   | |_   \n");
	printf("			     \\ V  V / | |___|  _ <| |___  \\ V  V /| |_| | |___|  _|  \n");
	printf("			      \\_/\\_/  |_____|_| \\_\\_____|  \\_/\\_/  \\___/|_____|_|    \n\n");
	printf("				    ______	                     	|\\---/|\n");
	printf("				   / *  * \\		               /  , , |\n");
	printf("				   |  /_  |			  __.-'|  / \\ /\n");
	printf("				    \\__V__/        	 __ ___.-'        ._O|\n");
	printf("				      ||	    .-'  '        :      _/\n");
	printf("			              ||	  / ,    .        .     |\n");
	printf("				     /||\\	 :  ;    :        :   _/\n");
	printf("				    / || \\	|  |   .'     __:   /\n");
	printf("				   /  ||  \\	|  :   /'----'| \\  |\n");
	printf("				      ||	\\  |\\  |      | /| |\n");
	printf("				      ||	 '.'| /       || \\ |\n");
	printf("			             / 	\\	 | /|.'       '.l \\\\_\n");
	printf("				    /	 \\	 || ||             '-'\n");
	printf("				   /	  \\	 '-''-'\n");
}

void ww_daycount(int night, char *prefix){
	if(night%10 == 1){
		prefix[0]= 's';
		prefix[1]='t';
	}
	else if(night%10==2){
		prefix[0]='n';
		prefix[1]='d';
	}
	else if(night%10==3){
		prefix[0]='r';
		prefix[1]='d';
	}
	else{
		prefix[0]='t';
		prefix[1]='h';
	}
	prefix[2]='\0';
}
void ww_cont(){
	printf("\t\t\t\t\t\t\tPress Enter to Continue!");
	getchar();
	getchar();
	system("cls");
}
void ww_hunt(struct ww_player *players, int ww_numPlayer, int gunnerindex, int witchindex){
	int seer=0;
	for(int a=0;a<ww_numPlayer;a++){
		if(players[a].roles==2&&players[a].lives>0)seer++;
	}
	if(seer>0){
		int target, store;
		printf("\t\t\t\t\t\t\tIT'S THE SEER'S TURN!\nWHO DO YOU WANT TO SEE(type the number)?\n");
		for(int i=0;i<ww_numPlayer;i++){
			if(players[i].roles!=2&&players[i].lives==1){
				printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
				store = i;
			}
		}
		printf("\t\t\t\t\t\t\t >> ");
		scanf("%d", &target);
		printf("\t\t\t\t\t\t%s is a ", players[target].names);
		if(players[target].roles== 0)printf("HEALER\n");
		else if(players[target].roles== 1)printf("WEREWOLF\n");
		else if(players[target].roles== 2)printf("SEER\n");
		else if(players[target].roles== 3)printf("VILLAGER\n");
		else if(players[target].roles== 4)printf("WITCH\n");
		else if(players[target].roles== 5)printf("GUNNER\n");
		getchar();
		ww_cont();
	}
	if(ww_numWitch>0 && players[witchindex].lives==1 && players[witchindex].bullet>0 || players[witchindex].cure>0){
		printf("\t\t\t\t\t\t\tIT'S THE WITCH'S TURN!!\nDO YOU WANT TO DO SOMETHING?[y/n]\n");
		char choice;
		do{
			printf("\t\t\t\t\t\t\t >> ");
			scanf("%c", &choice);
		}while(choice!='y'&&choice!='n');
		if(choice=='y'){
			if(players[witchindex].bullet>0 && players[witchindex].cure>0){
				printf("\t\t\t\t\t\t\tDO YOU WANT TO HEAL OR KILL?[h/k]\n");
				char pilihan;
				do{
					printf("\t\t\t\t\t\t\t >> ");
					scanf("%c", &pilihan);
				}while(pilihan!='h'&&pilihan!='k');
				if(pilihan=='k'){
					printf("\t\t\t\t\t\t\tWHO DO YOU WANT TO KILL(type the number)?(YOU CAN ONLY USE THE KILLING CURSE ONCE)\n");
					int target,i;
					for(i=0;i<ww_numPlayer;i++){
						if(players[i].roles!=4 && players[i].lives>0){
							printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
						}
					}
					printf("\t\t\t\t\t\t\t >> ");
					scanf("%d", &target);
					players[target].lives=-2,players[witchindex].bullet=0;
				}
				else if(pilihan=='h'){
					printf("\t\t\t\t\t\t\tWHO DO YOU WANT TO HEAL(type the number)?(YOU CAN ONLY USE THE REVIVAL CHARM ONCE)\n");
					int patient,i;
					for(i=0;i<ww_numPlayer;i++){
						if(players[i].roles!=4 && players[i].lives>=0){
							printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
						}
					}
					printf("\t\t\t\t\t\t\t >> ");
					scanf("%d", &patient);
					if(players[patient].lives>=-2)players[patient].lives=1;
						players[witchindex].cure=0;
					}
				}
			else if(players[witchindex].bullet<=0 && players[witchindex].cure>0){
				printf("\t\t\t\t\t\t\tWHO DO YOU WANT TO HEAL(type the number)?(YOU CAN ONLY USE THE REVIVAL CHARM ONCE)\n");
				int patient,i;
				for(int i=0;i<ww_numPlayer;i++){
					if(players[i].roles!=4 && players[i].lives>=0){
						printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
					}
				}
				printf("\t\t\t\t\t\t\t >> ");
				scanf("%d", &patient);
				if(players[patient].lives>=-2)players[patient].lives=1;
				players[witchindex].cure=0;
			}
			else if(players[witchindex].bullet>0 && players[witchindex].cure<=0){
				printf("\t\t\t\t\t\t\tWHO DO YOU WANT TO KILL(type the number)?(YOU CAN ONLY USE THE KILLING CURSE ONCE)\n");
				int target,i;
				for(i=0;i<ww_numPlayer;i++){
					if(players[i].roles!=4 && players[i].lives>0){
						printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
					}
				}
				printf("\t\t\t\t\t\t\t >> ");
				scanf("%d", &target);
				players[target].lives=-2,players[witchindex].bullet=0;
			}
		}
		getchar();
		ww_cont();
	}
	if(ww_numGunner>0 && players[gunnerindex].lives==1 &&players[gunnerindex].bullet>0){
		printf("\t\t\t\t\t\t\tIT'S THE GUNNER'S TURN!!\nDO YOU WANT TO SHOOT SOMETHING?[y/n]\n");
		char choose;
		do{scanf("%c", &choose);}while(choose!='y' && choose!='n');
		if(choose == 'y'&&players[gunnerindex].bullet>0){
			int target,i;
			printf("\t\t\t\t\t\t\tWho do you want to shoot?(type the number)\n");
			for(i=0;i<ww_numPlayer;i++){
				if(players[i].roles!=5 && players[i].lives>0){
					printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
				}
			}
			printf("\t\t\t\t\t\t\t >> ");
			scanf("%d", &target);
			players[target].lives=0, players[gunnerindex].bullet--;
			printf("\t\t\t\t\t\t\tYOU HAVE %d BULLETS LEFT!\n", players[gunnerindex].bullet);
		}
		getchar();
		ww_cont();
	}
	printf("\t\t\t\t\t\t\tIT'S THE WEREWOLVES TURN!\nCHOOSE YOUR VICTIM(type the number)!\n");
	int victim;
	for(int i=0;i<ww_numPlayer;i++){
		if(players[i].roles!=1 && players[i].lives>0){
			printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
		}
	}
	printf("\t\t\t\t\t\t\t >> ");
	scanf("%d", &victim);
	players[victim].lives--;
	getchar();
	ww_cont();
	int healer =0;
	for(int a=0;a<ww_numPlayer;a++){
		if(players[a].roles==0 && players[a].lives>0)healer++;
	}
	if(healer>0){
		printf("\t\t\t\t\t\t\tIT'S THE HEALER'S TURN!\nCHOOSE YOUR PATIENT(type the number)!\n");
		int patient, i;
		for(i=0;i<ww_numPlayer;i++){
			if(players[i].roles!=0 && players[i].lives>=0){
				printf("\t\t\t\t\t\t%d %s\n", i, players[i].names);
			}
		}
		printf("\t\t\t\t\t\t\t >> ");
		scanf("%d", &patient);
		players[patient].lives++;
		getchar();
		ww_cont();	
	}
	for(int j=0;j<ww_numPlayer;j++){
		if(players[j].lives==0)players[j].lives=-2;
		else if(players[j].lives > 1)players[j].lives = 1;
	}
}

void ww_votefunc(struct ww_player *players, char reveal, int ww_numPlayer){
	printf("\t\t\t\t\t\t\tHere are the list of current victim's\n");
	for(int j=0;j<ww_numPlayer;j++){
		if(players[j].lives<0){
			printf("\t\t\t\t\t\t\t%s", players[j].names);
			if(reveal=='y'){
				if(players[j].roles== 0)printf(" was a HEALER");
				else if(players[j].roles== 1)printf(" was a WEREWOLF");
				else if(players[j].roles== 2)printf(" was a SEER");
				else if(players[j].roles== 3)printf(" was a VILLAGER");
				else if(players[j].roles== 4)printf(" was a WITCH");
				else if(players[j].roles== 5)printf(" was a GUNNER");
			}
			if(players[j].lives==-10)printf("(HANGED)\n");
			else printf("\n");
		}
	}
	printf("\t\t\t\t\t\t\tWHO DO YOU WANT TO HANG?(type the number)\n");
	int hang;
	for(int k=0;k<ww_numPlayer;k++){
		if(players[k].lives>0)printf("%d %s\n", k, players[k].names);
	}
	printf("\t\t\t\t\t\t\t >> ");
	scanf("%d", &hang);
	players[hang].lives=-10;
}

void ww_htp(){
	system("cls");
	printf(" Welcome!\n");
	printf(" You are a resident living in the Village, in case you don't know, there are werewolves in our midst!\n");
	printf(" There are 2 sides in this game, the villagers side and the werewolves side.\n");
	printf(" -> Villagers Side: Your Goal is to eliminate all the werewolves, before their pack becomes stronger than yours!\n");
	printf(" -> Werewolves Side : Your Goal is to hunt as many villagers as you can!\n");
	printf(" Every player have roles assigned to them!\n");
	printf(" - Werewolves (Werewolves Side): Every night, vote which villager to hunt!\n");
	printf(" - Villager (Villagers Side): Just a normal villager, with normal rights.\n");
	printf(" - Gunner (Villagers Side): You are given 2 bullets, you can only spend one bullet on one night. Anyone you shoot dies, but can be revived at that turn!\n");
	printf(" - Witch (Villagers Side): You are given 1 killing curse and 1 healing charm, you can only spend one of them on one night. Anyone you curse dies permanently,\n");
	printf("                           and you can revive anyone who isn't lynched!\n");
	printf(" - Seer (Villagers Side): You are given a skill to see a single player's role once every night!\n");
	printf(" - Healer (Villagers Side): You can heal anyone you choose every night, but please take note that if the person you chose is healthy/cursed by the witch, then you can't heal them!\n");
	printf(" Every Day, it will be revealed who died (and their identity if you choose to), and take the time you have to discuss and vote on who to execute!\n");
	printf(" The game ends when either side wins!\n");
	printf(" Best of Luck, Enjoy!\n");
	printf(" Press enter to continue..");
	getchar();
	return;
}

void ww_startgame(){
	system("cls");
	do{
		printf("\t\t\t\t\t\t\tNumber of players: ");
		scanf("%d", &ww_numPlayer);
		if(ww_numPlayer<5){
			printf("\t\t\t\t\t\t\t      <<<<<<<<<<<<<<<<<<<<<<<<< WARNING >>>>>>>>>>>>>>>>>>>>>>>>>\n");
			printf("\t\t\t\t\t\t\t// You don't have enough players, please reenter the number of players! //\n");
			getchar();
		}
	}while(ww_numPlayer<5);
	system("cls");
	ww_logo();
	// PEMBAGIAN ROLE
	ww_player players[ww_numPlayer];
	ww_roles(ww_numPlayer, players);
	// PRINT ROLE UNTUK MODERATOR
	char reveal = 'n';
	printf("\t\t\t\t\t\t\tDo you want to reveal the character's identity upon death?[y/n]\n");
	do{
		if(reveal!='y'&&reveal!='n')printf("\t\t\t\t\t\t\tYou can only choose \"y\" or \"n\" !!\n");
		getchar();
		printf("\t\t\t\t\t\t\t >> ");
		scanf("%c", &reveal);
	}while(reveal!='y'&&reveal!='n');
	getchar();
	ww_identity(ww_numPlayer, players);
	ww_cont();
	ww_logo();
	printf("\n\t\t\t\t\t\t\tIt's the 1st Day!! PREPARE YOURSELVES!!\n");	
	ww_delay(5);
	system("cls");
	int night =1, gunnerindex=-1,witchindex=-1;
	if(ww_numWitch>0 && ww_numGunner>0){
		for(int a=0;a<ww_numPlayer;a++){
			if(players[a].roles==4)witchindex=a;
			else if(players[a].roles==5)gunnerindex=a;
		}
	}
	char prefix[3];
	int alive = ww_numSeer+ww_numHealer+ww_numGunner+ww_numWitch+ww_numVillager, wolf=ww_numWolf;
	while(wolf>0 && wolf<alive){
		//the night
		ww_daycount(night,prefix);
		printf("\t\t\t\t\t\t\tIt's the %d%s night!!\n", night, prefix);
		night++;
		ww_hunt(players, ww_numPlayer, gunnerindex, witchindex);
		ww_daycount(night,prefix);
		printf("\t\t\t\t\t\t\tIt's the %d%s day!! TIME TO VOTE\n", night, prefix);
		ww_votefunc(players, reveal, ww_numPlayer);
		wolf=0,alive=0;
		for(int l=0;l<ww_numPlayer;l++){
			if(players[l].roles!=1&&players[l].lives==1)alive++;
			else if(players[l].roles==1&&players[l].lives==1)wolf++;
		}
		printf("\t\t\t\t\t\t\tLET'S CONTINUE THE GAME!\n");
		getchar();
		ww_cont();
	}
	if(wolf==0)printf("\t\t\t\t\t\t\tTHE VILLAGERS WIN!!\n");
	else if(alive<=wolf)printf("\t\t\t\t\t\t\tTHE WEREWOLVES WIN!!\n");
	getchar();
	ww_cont();
	return;
}

void ww_game(){
	char ww_menuChoice;
	do{
		do{
			system("cls");
			ww_logo();	
			printf("\t\t\t\t\t\t1. Start Game\n");
			printf("\t\t\t\t\t\t2. How to Play\n");
			printf("\t\t\t\t\t\t3. Exit\n");
			printf("\t\t\t\t\t\t>> ");
			ww_menuChoice = getchar();
			getchar();
		}while(ww_menuChoice-'0'<1 || ww_menuChoice-'0'>3);
		switch(ww_menuChoice-'0'){
			case 1:
				ww_startgame();
				break;
			case 2:
				ww_htp();
				break;
			case 3:
				break;
		}
	}while(ww_menuChoice-'0'!=3);

}
