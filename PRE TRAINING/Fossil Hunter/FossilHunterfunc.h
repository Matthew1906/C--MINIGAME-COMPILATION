#include<stdio.h>
#include<stdlib.h>
char fossilHunter_board[50][50];
int fossilHunter_digchance, fossilHunter_fossils;
void fossilHunter_htp(){
	system("cls");
	printf("   === HELP ===\n");
  	printf(" 1. You are a fossil hunter, your job is to find fossils hidden somewhere in the dirt lot\n");
  	printf(" 2. You will need to find a certain number of fossil to win the game\n");
  	printf(" 3. You also have a limited number of chance to dig\n");
  	printf(" 4. If your chance to dig is smaller than the remaining fossil lot, you will lose\n");
  	printf(" 5. To dig a dirt lot, you will need to input the coordinate of that dirt lot\n");
  	printf(" 6. You can't dig a dirt lot that you have dug\n");
  	printf(" 7. These are some symbols that you need to know\n");
  	printf("     0 : Dirt Lot\n");
  	printf("     # : Fossil\n");
  	printf("     | : Dug Dirt\n");
	printf(" 8. Fossil will have various shape just like shown below\n");
	printf(" +=======+=========+========+=========+========+===========+\n");
    printf(" |  - #  |  - ###  |  - ##  |  -  #   |  - ##  |  - #####  |\n");
    printf(" |       |      #  |        |    ###  |    ##  |           |\n");
    printf(" +=======+=========+========+=========+========+===========+\n");
    printf(" \\\ Sorry but due to technical issues, there will be only one type ('#') in this game.\\\ \n");
  	printf(" 9. You will have different amount of chance to dig a dirt lot depends on the difficulty\n");
 	printf(" 10. Each difficulty will have its own number of fossil that you need to find\n");
	printf(" Press enter to continue...");
	getchar();
	return;
}
void fossilHunter_printboard(int size){
	char begin = '1';
	printf("  ");
	for(int i=1;i<=size;i++){
		if(begin>'9')begin='0';
		printf("%c ", begin);
		begin++;
	}
	printf("\n");
	begin = '1';
	for(int i=1;i<=size;i++){
		if(begin>'9')begin='0';
		printf("%c ", begin);
		begin++;
		for(int j=1;j<=size;j++){
			printf("%c ", fossilHunter_board[i][j]);
		}
		printf("\n");
	}
}
void fossilHunter_play(){
	char choose2;
	do{
		system("cls");
		printf(" === Choose Your Difficulty ===\n\n");
		printf(" 1. Easy ( 10 x 10 Dirty Lot, 10 Fossils, and 50 dig chance)\n");
		printf(" 2. Medium ( 20 x 20 Dirty Lot, 20 Fossils, and 150 dig chance)\n");
		printf(" 3. Hard ( 30 x 30 Dirty Lot, 30 Fossils, and 200 dig chance)\n");
		printf(" >> ");
		choose2 = getchar();
	}while(choose2-'0'<1 || choose2-'0'>3);
	int size;
	switch(choose2){
		case '1':
			fossilHunter_fossils = 10;
			fossilHunter_digchance = 50;
			size = 10;
			break;
		case '2':
			fossilHunter_fossils = 20;
			fossilHunter_digchance = 150;
			size = 20;
			break;
		case '3':
			fossilHunter_fossils = 30;
			fossilHunter_digchance = 200;
			size = 30;			
			break;
	}
	system("cls");
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			fossilHunter_board[i][j]= (char)254;
		}
	}
	fossilHunter_printboard(size);
	char location[size+1];
	for(int i=1;i<=size;i++){
		location[i]=(rand()%10)+1;
	}
	do{
		int x, y;
		do{
			system("cls");
			printf(" === Possil Hunter ===\n\n");
			fossilHunter_printboard(size);
			printf(" Remaining fossil lot to be found : %d\n", fossilHunter_fossils);
			printf(" Remaining dig chance: %d\n\n", fossilHunter_digchance);
			printf(" Input Coordinate[X-Y]: ");
			scanf("%d-%d", &x, &y);
		}while(x<1 || x>size || y<1 || y>size|| fossilHunter_board[y][x]!= (char)254);
		if(location[y]== x){
			fossilHunter_fossils--;
			fossilHunter_board[y][x]= '#';
		}
		else{
			fossilHunter_board[y][x]= (char)178;
		}
		fossilHunter_digchance--;
	}while(fossilHunter_fossils!=0 && fossilHunter_digchance>=fossilHunter_fossils);
	if(fossilHunter_fossils==0){
		printf(" _____.___.               __      __.__  \n");      
		printf(" \\__  |   | ____  __ __  /  \\    /  \\__| ____ \n"); 
		printf("  /   |   |/  _ \\|  |  \\ \\   \\/\\/   /  |/    \\ \n");
		printf("  \\____   (  <_> )  |  /  \\        /|  |   |  \\\n");
		printf("  / ______|\\____/|____/    \\__/\\  / |__|___|  /\n");
		printf("  \\/                            \\/          \\/\n");
		printf("\t\t\t\t\t\tYou have found all the fossils!\n");
	}
	else if(fossilHunter_digchance<fossilHunter_fossils){
		printf("    ________                        ________             \n");
		printf("   /  _____/_____    _____   ____   \\_____  \\___  __ ___________ \n");
		printf("  /   \\  ___\\__  \\  /     \\_/ __ \\   /   |   \\  \\/ // __ \\_  __ \\\n");
		printf("  \\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  /    |    \\   /\\  ___/|  | \\/\n");
		printf("   \\______  (____  /__|_|  /\\___  > \\_______  /\\_/  \\___  >__|   \n");
		printf("          \\/     \\/      \\/     \\/          \\/          \\/       \n");
		printf("\t\t\t\t\t\tYou have run out of chances!\n");
	}
	getchar();
	printf("\t\t\t\t\t\tPress enter to return to the main menu...");
	getchar();
	return;
}
void fossilHunter_game(){
	char choose1;
	do{
		do{
			system("cls");
			printf(" ___________                 .__.__      ___ ___               __             \n");   
			printf(" \\_   _____/___  ______ _____|__|  |    /   |   \\ __ __  _____/  |_  ___________ \n");
			printf("  |    __)/  _ \\/  ___//  ___/  |  |   /    ~    \\  |  \\/    \\   __\\/ __ \\_  __ \\\n");
			printf("  |     \\(  <_> )___ \\ \\___ \\|  |  |__ \\    Y    /  |  /   |  \\  | \\  ___/|  | \\/\n");
			printf("  \\___  / \\____/____  >____  >__|____/  \\___|_  /|____/|___|  /__|  \\___  >__|   \n");
			printf("      \\/            \\/     \\/                 \\/            \\/          \\/\n");       
			printf("\n\t\t\t\t\t1. Play\n");
			printf("\t\t\t\t\t2. Help\n");
			printf("\t\t\t\t\t3. Exit\n");
			printf("\t\t\t\t\t>> ");	
			choose1 = getch();
			printf("%c\n", choose1);
		}while(choose1-'0'<1 || choose1-'0'>3);
		switch(choose1){
			case '1':
				fossilHunter_play();
				break;
			case '2':
				fossilHunter_htp();
				break;
			case '3':
				break;
		}
	}while(choose1!='3');
	return;
}
