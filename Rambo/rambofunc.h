#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
int rambo_points=0; 
char rambo_map[20][100]={
	"----------------------------------------",
	"|   #            #                 #   |",
	"|   #            #                 #   |",
	"|   @            #       ##########@## |",
	"|   @#######     @          #       #  |",
	"|          #     #          #       #  |",
	"|          #     #          #          |",
	"|          #                # #@####   |",
	"|          ##@####@##       #          |",
	"|      #                               |",
	"|   @###         #    #    #####@######|",
	"|   #  #         #    @         #      |",
	"|   #  #         #    #  ###@## #      |",
	"|   #  ##@#######@##  #         #      |",
	"|   #  #   #          #         #      |",
	"| @##  #   #                    #      |",
	"|      #   ####@######@######   #      |",
	"|      #   #                    ###### |",
	"|      #                  #            |",
	"----------------------------------------"
};
int rambo_x, rambo_y;
void rambo_printmap(char rambo_map[100][100]){
	for(int a=0;a<20;a++){
		for(int b=0;b<40;b++){
			if(a==rambo_y && b==rambo_x){
				printf("x");
			}
			else printf("%c", rambo_map[a][b]);
		}
		printf("\n");
	}
}
void rambo_play(){
	int rambo_flag=1, rambo_len;
	char rambo_move[10];
	do{
		system("cls");
		rambo_printmap (rambo_map);
		do{
			rambo_flag =1;
			printf(" >> ");
			scanf("%s", rambo_move);
			int rambo_len = strlen(rambo_move);
			if(rambo_len>10){
				rambo_flag=0;
			}
			else{
				for(int j=0;j<rambo_len;j++){
					if(rambo_move[j]=='q'){
						rambo_flag=20;
						break;
					}
					else if(rambo_move[j]!='d' && rambo_move[j]!='s' && rambo_move[j]!='a' && rambo_move[j]!='w' && rambo_move[j]!='e'){
						rambo_flag=0;
						break;
					}
				}
			}
		}while(rambo_flag==0);
		int rambo_len = strlen(rambo_move);
		for(int i=0;i<rambo_len;i++){
			if(rambo_move[i]=='d' && rambo_map[rambo_y][rambo_x+1]==' '){
				rambo_x++;	
			}
			else if(rambo_move[i]=='s'&& rambo_map[rambo_y+1][rambo_x]==' '){
				rambo_y++;
			}
			else if(rambo_move[i]=='a'&& rambo_map[rambo_y][rambo_x-1]==' '){
				rambo_x--;
			}
			else if(rambo_move[i]=='w'&& rambo_map[rambo_y-1][rambo_x]==' '){
				rambo_y--;
			}
			else if(rambo_move[i]=='e'){
				if(rambo_move[i-1]=='s'&& rambo_map[rambo_y+1][rambo_x]=='#'){
					rambo_map[rambo_y+1][rambo_x]=' ';	
					rambo_points+=75;
				}
				else if(rambo_move[i-1]=='s'&& rambo_map[rambo_y+1][rambo_x]=='@'){
					rambo_map[rambo_y+1][rambo_x]=' ';
					rambo_points/=15;
				}
				else if(rambo_move[i-1]=='d'&& rambo_map[rambo_y][rambo_x+1]=='#'){
					rambo_map[rambo_y][rambo_x+1]=' ';
					rambo_points+=75;
				}
				else if(rambo_move[i-1]=='d'&& rambo_map[rambo_y][rambo_x+1]=='@'){
					rambo_map[rambo_y][rambo_x+1]=' ';
					rambo_points/=15;
				}
				else if(rambo_move[i-1]=='a'&& rambo_map[rambo_y][rambo_x-1]=='#'){
					rambo_map[rambo_y][rambo_x-1]=' ';
					rambo_points+=75;
				}
				else if(rambo_move[i-1]=='a'&& rambo_map[rambo_y][rambo_x-1]=='@'){
					rambo_map[rambo_y][rambo_x-1]=' ';
					rambo_points/=15;
				}	
				else if(rambo_move[i-1]=='w'&& rambo_map[rambo_y-1][rambo_x]=='#'){
					rambo_map[rambo_y-1][rambo_x]=' ';
					rambo_points+=75;
				}
				else if(rambo_move[i-1]=='w'&& rambo_map[rambo_y-1][rambo_x]=='@'){
					rambo_map[rambo_y-1][rambo_x]=' ';
					rambo_points/=15;
				}
			}
			system("cls");
			rambo_printmap (rambo_map);
		}
		printf("points : %d\n", rambo_points);
	}while(rambo_flag!=20);
	printf("press ENTER to go back to main menu..");
	getchar();
	getchar();
	system("cls");
	return;
}
void rambo_htp(){
	system("cls");
	printf("\n Ten Hut!!!\n");
	printf(" Soldier, Welcome to Vietnam, the year is 1972.\n");
	printf(" You are lost in the wilderness of Vietnam and surrounded by enemies(#).\n");
	printf(" Some of your allies(@) are hidden between the enemies\n");
	printf(" Your Task is to shoot all the enemy and gain as much point as possible, shooting an ally will deduct your point!\n");
	printf(" Best of luck to you!\n\n\n");
	printf("  Use WASD to move\n");
	printf(" -E to shoot(make sure you're facing the correct direction)\n");
	printf(" -Q to quit\n");
	printf(" Press [Enter] to return\n");
	printf(" >> ");
	getchar();
}
void rambo_game(){
	
	char rambo_map[100][100]={
		"----------------------------------------",
		"|   #            #                 #   |",
		"|   #            #                 #   |",
		"|   @            #       ##########@## |",
		"|   @#######     @          #       #  |",
		"|          #     #          #       #  |",
		"|          #     #          #          |",	
		"|          #                # #@####   |",
		"|          ##@####@##       #          |",
		"|      #                               |",
		"|   @###         #    #    #####@######|",
		"|   #  #         #    @         #      |",
		"|   #  #         #    #  ###@## #      |",	
		"|   #  ##@#######@##  #         #      |",
		"|   #  #   #          #         #      |",
		"| @##  #   #                    #      |",		
		"|      #   ####@######@######   #      |",
		"|      #   #                    ###### |",
		"|      #                  #            |",
		"----------------------------------------"
	};
	char rambo_choose;
	do{
		do{ 
			system("cls");
			printf("		                AAA                                       BBBBBBBBBBBBBBBBB\n");
   			printf("                               A:::A                                      B::::::::::::::::B\n");
    		printf("                              A:::::A                                     B::::::BBBBBB:::::B\n");
    		printf("                             A:::::::A                                    BB:::::B     B:::::B\n");
    		printf("   rrrrr   rrrrrrrrr        A:::::::::A              mmmmmmm    mmmmmmm     B::::B     B:::::B   ooooooooooo\n");
    		printf("   r::::rrr:::::::::r      A:::::A:::::A           mm:::::::m  m:::::::mm   B::::B     B:::::B oo:::::::::::oo\n");
    		printf("   r:::::::::::::::::r    A:::::A A:::::A         m::::::::::mm::::::::::m  B::::BBBBBB:::::B o:::::::::::::::o\n");
    		printf("   rr::::::rrrrr::::::r  A:::::A   A:::::A        m::::::::::::::::::::::m  B:::::::::::::BB  o:::::ooooo:::::o\n");
    		printf("    r:::::r     r:::::r A:::::A     A:::::A       m:::::mmm::::::mmm:::::m  B::::BBBBBB:::::B o::::o     o::::o\n");
    		printf("    r:::::r     rrrrrrrA:::::AAAAAAAAA:::::A      m::::m   m::::m   m::::m  B::::B     B:::::Bo::::o     o::::o\n");
    		printf("    r:::::r           A:::::::::::::::::::::A     m::::m   m::::m   m::::m  B::::B     B:::::Bo::::o     o::::o\n");
    		printf("    r:::::r          A:::::AAAAAAAAAAAAA:::::A    m::::m   m::::m   m::::m  B::::B     B:::::Bo::::o     o::::o\n");
    		printf("    r:::::r         A:::::A             A:::::A   m::::m   m::::m   m::::mBB:::::BBBBBB::::::Bo:::::ooooo:::::o\n");
    		printf("    r:::::r        A:::::A               A:::::A  m::::m   m::::m   m::::mB:::::::::::::::::B o:::::::::::::::o\n");
    		printf("    r:::::r       A:::::A                 A:::::A m::::m   m::::m   m::::mB::::::::::::::::B   oo:::::::::::oo\n");
    		printf("    rrrrrrr      AAAAAAA                   AAAAAAAmmmmmm   mmmmmm   mmmmmmBBBBBBBBBBBBBBBBB      ooooooooooo\n\n");
			printf("\t\t\t\t\t\t1. Play Game\n");
			printf("\t\t\t\t\t\t2. How to Play\n");
			printf("\t\t\t\t\t\t3. Exit\n");
			printf("\t\t\t\t\t\t>> ");
			rambo_choose = getch();
			printf("%c\n", rambo_choose);
		}while(rambo_choose-'0'<1 && rambo_choose-'0'>3);
		switch(rambo_choose-'0'){
			case 1:
				strcpy(rambo_map[0], "----------------------------------------");
				strcpy(rambo_map[1], "|   #            #                 #   |");
				strcpy(rambo_map[2], "|   #            #                 #   |");
				strcpy(rambo_map[3], "|   @            #       ##########@## |");
				strcpy(rambo_map[4], "|   @#######     @          #       #  |");
				strcpy(rambo_map[5], "|          #     #          #       #  |");
				strcpy(rambo_map[6], "|          #     #          #          |");
				strcpy(rambo_map[7], "|          #                # #@####   |");
				strcpy(rambo_map[8], "|          ##@####@##       #          |");
				strcpy(rambo_map[9], "|      #                               |");
				strcpy(rambo_map[10],"|   @###         #    #    #####@######|");
				strcpy(rambo_map[11],"|   #  #         #    @         #      |");
				strcpy(rambo_map[12],"|   #  #         #    #  ###@## #      |");
				strcpy(rambo_map[13],"|   #  ##@#######@##  #         #      |");
				strcpy(rambo_map[14],"|   #  #   #          #         #      |");
				strcpy(rambo_map[15],"| @##  #   #                    #      |");
				strcpy(rambo_map[16],"|      #   ####@######@######   #      |");
				strcpy(rambo_map[17],"|      #   #                    ###### |");
				strcpy(rambo_map[18],"|      #                  #            |");
				strcpy(rambo_map[19],"----------------------------------------");
				do{
					rambo_x = rand()%40;
					rambo_y = rand()%20;
				}while(rambo_map[rambo_y][rambo_x]!=' ');	
				rambo_points = 0;
				rambo_play();
				break;
			case 2:
				rambo_htp();
				break;
			case 3:
				break;
		}
	}while(rambo_choose-'0'!=3);
	return;
}
