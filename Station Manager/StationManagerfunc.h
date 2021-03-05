#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

void stationManager_logo(){
	printf("  ___ _____ _ _____ ___ ___  _  _   __  __   _   _  _   _   ___ ___ ___ \n");
	printf(" / __|_   _/_\\_   _|_ _/ _ \\| \\| | |  \\/  | /_\\ | \\| | /_\\ / __| __| _ \\\n");
	printf(" \\__ \\ | |/ _ \\| |  | | (_) | .` | | |\\/| |/ _ \\| .` |/ _ \\ (_ | _||   /\n");
	printf(" |___/ |_/_/ \\_\\_| |___\\___/|_|\\_| |_|  |_/_/ \\_\\_|\\_/_/ \\_\\___|___|_|_\\\n\n");
    return;                                                            
}

int stationManager_minRow, stationManager_minCol, stationManager_maxRow, stationManager_maxCol; // grid layout

struct stationManager_station{
	char name[255];
	long long price; 
	int rowPos, colPos;
	struct stationManager_station *east, *west, *north, *south /*Multiple Linked List*/;
	bool shown; // to prevent infinite looping
}*stationManager_curr = NULL;

// 1. Create Station
struct stationManager_station* stationManager_createStation(char* stationName, long long stationPrice){
	struct stationManager_station *newStation = (struct stationManager_station*)malloc(sizeof(struct stationManager_station));
	strcpy(newStation->name, stationName);
	newStation->colPos = 0;
	newStation->rowPos = 0;
	newStation->east = newStation->west = newStation->south = newStation->north= NULL;
	newStation->price = stationPrice;
	newStation->shown = false;
	return newStation;
}

// 2. Get Station by Name
struct stationManager_station* stationManager_findStationByName(struct stationManager_station *root, char *stationName){
	if(!root){
		return NULL;
	}
	if(root->shown){
		return root;
	}
	root->shown = true;
	if(strcmpi(root->name, stationName)==0){
		return root;
	}
	root->west = stationManager_findStationByName(root->west, stationName);
	if(root->west && strcmpi(root->west->name, stationName)==0){
		return root->west;
	}
	root->east = stationManager_findStationByName(root->east, stationName);
	if(root->east  && strcmpi(root->east->name, stationName)==0){
		return root->east;
	}
	root->north = stationManager_findStationByName(root->north, stationName);
	if(root->north  && strcmpi(root->north->name, stationName)==0){
		return root->north;
	}
	root->south = stationManager_findStationByName(root->south, stationName);
	if(root->south  && strcmpi(root->south->name, stationName)==0){
		return root->south;
	}
	return root;
}

// 3. Get Station by Coordinate ( rowPos and colPos attribute)
struct stationManager_station* stationManager_findStationByCoordinate(struct stationManager_station *root, int row, int col){
	if(!root){
		return NULL;
	}
	if(root->shown){
		return root;
	}
	root->shown = true;
	if(root->rowPos == row && root->colPos==col){
		return root;
	}
	struct stationManager_station* temp = NULL;
	temp = stationManager_findStationByCoordinate(root->east, row, col);
	if(temp && temp->rowPos == row && temp->colPos==col){
		return temp;
	}
	temp = stationManager_findStationByCoordinate(root->west, row, col);
	if(temp && temp->rowPos == row && temp->colPos==col){
		return temp;
	}
	temp = stationManager_findStationByCoordinate(root->north, row, col);
	if(temp && temp->rowPos == row && temp->colPos==col){
		return temp;
	}
	temp = stationManager_findStationByCoordinate(root->south, row, col);
	if(temp && temp->rowPos == row && temp->colPos==col){
		return temp;
	}
	return root;
}

// 4. set all shown attributes in each station to false
void stationManager_neutralizeShown(struct stationManager_station*root){
	if(!root){
		return;
	}
	if(!root->shown){
		return;
	}
	root->shown = false;
	stationManager_neutralizeShown(root->east);
	stationManager_neutralizeShown(root->west);
	stationManager_neutralizeShown(root->north);
	stationManager_neutralizeShown(root->south);
	return;
}

// 5. print all stations in grid layout (basically convert queartenary graph (multiple linked list) into grid layout)
void stationManager_showStation(struct stationManager_station *root){
	if(!root){
		return;
	}
	printf(" All Stations:\n\n");	
	char showTemp[300][450];
	for(int i=0;i<300;++i){
		strcpy(showTemp[i],"");
	}
	int rowIndex = 0;
	for(int i=stationManager_minRow;i<=stationManager_maxRow;++i){
		int storeLength[stationManager_maxCol-stationManager_minCol+1]={0};
		int index = 0;
		strcat(showTemp[rowIndex],"   ");
		struct stationManager_station *find = NULL;
		char trinket[255]="   ";
		char trinket1[255]="   ";
		for(int j=stationManager_minCol;j<=stationManager_maxCol;++j){
			find = stationManager_findStationByCoordinate(root, i, j);
			stationManager_neutralizeShown(root);
			if(find && find->rowPos==i && find->colPos==j){
				strcat(trinket,"+ ");
				strcat(trinket1,"+ ");
				for(int i=0;i<25;++i){
					strcat(trinket,"-");
					strcat(trinket1,"-");
				}
				strcat(trinket," +");
				strcat(trinket1," +");
				char name[255];
				strcpy(name, find->name);
				int len = strlen(name);
				char extraStr[25-len]="";
				for(int k=0;k<25-len;++k){
					strcat(extraStr," ");
				}
				strcat(name, extraStr);
				strcat(showTemp[rowIndex],"| ");
				strcat(showTemp[rowIndex], (const char*)name);
				strcat(showTemp[rowIndex]," |");
				strcat(trinket, "       ");
				strcat(trinket1, "       ");
				if(find->east){
					strcat(showTemp[rowIndex], " ----- ");
				}
				else{
					strcat(showTemp[rowIndex],"       ");
				}
				
				if(find->south){
					storeLength[index] = len;
				}
				else{
					storeLength[index] = -1;
				}
			}
			else{
				char extraStr[36]="";
				for(int i=0;i<36;++i){
					strcat(extraStr," ");
					strcat(trinket," ");
					strcat(trinket1," ");
				}
				strcat(showTemp[rowIndex],(const char*)extraStr);
				storeLength[index] = -1;
			}
			index++;
		}
		printf("%s\n", trinket);
		printf("%s\n", showTemp[rowIndex]);
		printf("%s\n", trinket1);
		rowIndex++;
		for(int j=0;j<3;++j){
			strcat(showTemp[rowIndex],"   ");
			for(int k=0;k<index;++k){
				if(storeLength[k]!=-1){
					int length = 12;
					char extraStr[length]="";
					for(int l=0;l<length;++l){
						strcat(extraStr," ");
					}
					strcat(showTemp[rowIndex], (const char*)extraStr);
					strcat(showTemp[rowIndex], "|");
					int extra = 25-length;
					char extraStr1[extra+7]="";
					for(int l=0;l<extra+7;++l){
						strcat(extraStr1," ");
					}
					strcat(showTemp[rowIndex],(const char*)extraStr1);
				}
				else{
					char extraStr[32]="";
					for(int l=0;l<32;++l){
						strcat(extraStr," ");
					}
					strcat(showTemp[rowIndex],(const char*)extraStr);
				}
			}
			printf("%s\n", showTemp[rowIndex]);
			rowIndex++;
		}
	}
}

//6. Helper function to delete
int stationManager_floodfill(int matrix[][450], int row, int col){
	if(row<0 || col<0 || row>stationManager_maxRow-stationManager_minRow || col>stationManager_maxCol-stationManager_minCol || matrix[row][col] == 0){
		return 0;
	}
	int temp = 1;
	matrix[row][col] = 0;
	temp+=stationManager_floodfill(matrix, row+1, col);
	temp+=stationManager_floodfill(matrix, row-1, col);
	temp+=stationManager_floodfill(matrix, row, col+1);
	temp+=stationManager_floodfill(matrix, row, col-1);
	return temp;
}

//7. determine if a station is safe to be deleted
bool stationManager_setSafety(struct stationManager_station *root, int row, int col){
	int safetyMatrix[300][450], stationCount = 0;
	int rowIndex = 0, colIndex=0;
	for(int i=stationManager_minRow;i<=stationManager_maxRow;++i){
		for(int j=stationManager_minCol;j<=stationManager_maxCol;++j){
			struct stationManager_station *find = stationManager_findStationByCoordinate(root, i, j);
			stationManager_neutralizeShown(root);
			if(find && find->rowPos == i && find->colPos==j){
				if(i==row && j==col){
					safetyMatrix[rowIndex][colIndex] = 0;
				}
				else{
					safetyMatrix[rowIndex][colIndex] = 1;
					stationCount++;
				}
			}
			else{
				safetyMatrix[rowIndex][colIndex] = 0;
			}
			colIndex++;
		}
		rowIndex++;
		colIndex=0;
	}
	int max = 0;
	for(int i=0;i<=stationManager_maxRow-stationManager_minRow;++i){
		for(int j=0;j<=stationManager_maxCol-stationManager_minCol;++j){
			int spanned = stationManager_floodfill(safetyMatrix, i, j);
			if(spanned == stationCount){
				return true;
			}
		}
	}
	return false;
}

// 8. Show all connected stations
void stationManager_showConnectedStations(struct stationManager_station* root, const char*purpose){
	for(int i=stationManager_minRow;i<=stationManager_maxRow;++i){
		for(int j=stationManager_minCol;j<=stationManager_maxCol;++j){
			struct stationManager_station *find = stationManager_findStationByCoordinate(root, i, j);
			stationManager_neutralizeShown(root);
			if(find && find->rowPos==i && find->colPos==j){
				printf(" - %s ", find->name);
				if(strcmpi(purpose,"connect")==0 && find->north && find->south && find->west && find->east){
					printf("[FULL]");
				}
				else if(strcmpi(purpose,"delete")==0){
					bool safeFlag = stationManager_setSafety(root, find->rowPos, find->colPos);
					if(safeFlag){
						printf("[SAFE TO BE DELETED]");
					}
				}
				printf("\n");
			}
		}
	}
} 

// 9. Add Station Menu
struct stationManager_station * stationManager_addStation(struct stationManager_station *root){
	system("cls");
	int addFlag = 1;
	char stationName[255];
	stationManager_showStation(root);
	// insert Name, validated through length, number of words, and originality
	do{
		addFlag = 1;
		printf(" Enter the Station Name [5-25 characters, 2 Words Minimal, Unique][x to exit] : ");
		scanf("%[^\n]", stationName);
		getchar();
		if(strcmp(stationName,"x")==0){
			return root;
		}
		int length = strlen(stationName);
		if(length<5 || length>25){
			addFlag = 0;
			printf(" Station name must be between 5 - 25 characters!\n");
		}
		else{
			int flag = 0;
			for(int i=1;i<length-1;++i){
				if(stationName[i]==' '){
					flag = 1;
					break;
				}
			}
			if(!flag){
				addFlag=0;
				printf(" Station name must be composed of at least 2 words!\n");
			}
			else{
				struct stationManager_station* check = stationManager_findStationByName(root, stationName);
				stationManager_neutralizeShown(root);
				if(check && strcmpi(check->name, stationName)==0){
					addFlag = 0;
					printf(" Station name must be unique!\n");
				}	
			}
		}
	}while(addFlag==0);
	long long stationPrice;
	// insert price
	do{
		stationPrice = 0;
		addFlag = 1;
		printf(" Enter the Station Ticket Price [Rp. 100.000 - Rp. 1.000.000] [-1 to exit]: Rp. ");
		scanf("%lld", &stationPrice);
		getchar();
		if(stationPrice == -1){
			return root;
		}
		if(stationPrice<100000 || stationPrice>1000000){
			addFlag = 0;
			printf(" Price must be between Rp. 100.000 - Rp. 1.000.000!\n");
		}
	}while(addFlag==0);
	// create the stationManager_station
	struct stationManager_station*temp = stationManager_createStation(stationName, stationPrice);
	// sort where to put the created station
	if(!root){
		root = temp;
	}
	else{
		system("cls");
		char connectName[255];	
		// determine which station to connect with
		do{
			system("cls");
			addFlag = 1;
			stationManager_showStation(root);
			printf(" Which station can connect to this new station? [cancel to exit]?\n");
			stationManager_showConnectedStations(root, "connect");
			printf(" >> ");
			scanf("%[^\n]", connectName);
			getchar();
			if(strcmpi(connectName,"cancel")==0){
				return root;
			}
			stationManager_curr = stationManager_findStationByName(root, connectName);
			stationManager_neutralizeShown(root);
			if(!stationManager_curr){
				addFlag = 0;
			}
			else if(stationManager_curr->north && stationManager_curr->south && stationManager_curr->west && stationManager_curr->east){
				addFlag = 0;
			}
			else if(strcmpi(stationManager_curr->name, connectName)!=0){
				addFlag = 0;
			}
		}while(addFlag == 0);
		int directionChoice = 0;
		// select on where will the new sstation be connected to the chosen station
		do{
			system("cls");
			addFlag = 1;
			stationManager_showStation(root);
			printf(" Selected Station[-1 to exit]: %s\n", stationManager_curr->name);
			printf(" 1. North -> ");
			if(stationManager_curr->north){
				printf("%s\n", stationManager_curr->north->name);
			}
			else{
				printf("None\n");
			}
			printf(" 2. South -> ");
			if(stationManager_curr->south){
				printf("%s\n", stationManager_curr->south->name);
			}
			else{
				printf("None\n");
			}
			printf(" 3. West  -> ");
			if(stationManager_curr->west){
				printf("%s\n", stationManager_curr->west->name);
			}	
			else{
				printf("None\n");
			}
			printf(" 4. East  -> ");
			if(stationManager_curr->east){
				printf("%s\n", stationManager_curr->east->name);
			}
			else{
				printf("None\n");
			}
			printf(" >> ");
			scanf("%d", &directionChoice);
			getchar();
			if(directionChoice==-1){
				return root;
			}
			else if(directionChoice<1 || directionChoice>4){
				addFlag = 0;
			}
			else if(directionChoice==1 && stationManager_curr->north){
				addFlag = 0;
			}
			else if(directionChoice==2 && stationManager_curr->south){
				addFlag = 0;
			}
			else if(directionChoice==3 && stationManager_curr->west){
				addFlag = 0;
			}
			else if(directionChoice==4 && stationManager_curr->east){
				addFlag = 0;
			}
		}while(addFlag==0);
		// link based on the direction and update position
		switch(directionChoice){
			case 1:
				temp->south = stationManager_curr;
				stationManager_curr->north = temp;
				temp->rowPos = stationManager_curr->rowPos-1;
				temp->colPos = stationManager_curr->colPos;
				break;
			case 2:
				temp->north = stationManager_curr;
				stationManager_curr->south = temp;
				temp->rowPos = stationManager_curr->rowPos+1;
				temp->colPos = stationManager_curr->colPos;
				break;
			case 3:
				temp->east = stationManager_curr;
				stationManager_curr->west = temp;
				temp->rowPos = stationManager_curr->rowPos;
				temp->colPos = stationManager_curr->colPos-1;
				break;
			case 4:
				temp->west = stationManager_curr;
				stationManager_curr->east = temp;
				temp->rowPos = stationManager_curr->rowPos;
				temp->colPos = stationManager_curr->colPos+1;
				break; 
		}	
		// update minimum and maximum column and row	
		if(temp->colPos<stationManager_minCol){
			stationManager_minCol = temp->colPos;
		}
		else if(temp->colPos>stationManager_maxCol){
			stationManager_maxCol = temp->colPos;
		}
		if(temp->rowPos<stationManager_minRow){
			stationManager_minRow = temp->rowPos;
		}
		else if(temp->rowPos>stationManager_maxRow){
			stationManager_maxRow = temp->rowPos;
		}
		// prompt if the user wants to connect the station to other available and possible stations
		bool connectAgain = true;
		while(connectAgain){
			char connectPrompt[255];
			connectAgain = true;
			do{
				system("cls");
				stationManager_showStation(root);
				addFlag = 1;
				printf(" Do you want to connect more stations? [Yes | No]? : ");
				scanf("%[^\n]", connectPrompt);
				getchar();
				if(strcmpi(connectPrompt, "Yes")!=0 && strcmpi(connectPrompt, "No")!=0){
					addFlag = 0;
				}
			}while(addFlag ==0);
			if(strcmpi(connectPrompt,"No")==0){
				connectAgain = false;
				break;
			}	
			else{
				int connectMore = 0;
				struct stationManager_station *find = NULL;
				do{
					int directionAvailable[4]={0};
					system("cls");
					addFlag = 1;
					stationManager_showStation(root);	
					printf(" Neighbor Stations:\n");
					//north
					printf(" 1. North : ");
					find = stationManager_findStationByCoordinate(root, temp->rowPos-1, temp->colPos);
					stationManager_neutralizeShown(root);
					if(find && find->rowPos == temp->rowPos-1 && find->colPos == temp->colPos){
						directionAvailable[0] = 1;
						if(temp->north){
							printf("%s\n", find->name);
						}
						else{
							printf("None [%s]\n", find->name);
						}
					}
					else{
						printf("None\n");
					}
					//south
					printf(" 2. South : ");
					find = stationManager_findStationByCoordinate(root, temp->rowPos+1, temp->colPos);
					stationManager_neutralizeShown(root);
					if(find && find->rowPos == temp->rowPos+1 && find->colPos == temp->colPos){
						directionAvailable[1] = 1;
						if(temp->south){
							printf("%s\n", find->name);
						}
						else{
							printf("None [%s]\n", find->name);
						}
					}
					else{
						printf("None\n");
					}
					//west
					printf(" 3. West  : ");
					find = stationManager_findStationByCoordinate(root, temp->rowPos, temp->colPos-1);
					stationManager_neutralizeShown(root);
					if(find && find->rowPos == temp->rowPos && find->colPos == temp->colPos-1){
						directionAvailable[2] = 1;
						if(temp->west){
							printf("%s\n", find->name);
						}
						else{
							printf("None [%s]\n", find->name);
						}
					}
					else{
						printf("None\n");
					}
					//east
					printf(" 4. East  : ");
					find = stationManager_findStationByCoordinate(root, temp->rowPos, temp->colPos+1);
					stationManager_neutralizeShown(root);
					if(find && find->rowPos == temp->rowPos && find->colPos == temp->colPos+1){
						directionAvailable[3] = 1;
						if(temp->east){
							printf("%s\n", find->name);
						}
						else{
							printf("None [%s]\n", find->name);
						}
					}
					else{
						printf("None\n");
					}
					
					printf(" Select station [-1 to exit]: ");
					scanf("%d", &connectMore);
					getchar();
					if(connectMore!=-1 && (connectMore<0 || connectMore>4)){
						addFlag = 0;
					}
					if(connectMore==1 && (temp->north || directionAvailable[0] == 0)){
						addFlag = 0;
					}
					if(connectMore==2 && (temp->south || directionAvailable[1] == 0)){
						addFlag = 0;
					}
					if(connectMore==3 && (temp->west || directionAvailable[2] == 0)){
						addFlag = 0;
					}
					if(connectMore==4 && (temp->east || directionAvailable[3] == 0)){
						addFlag = 0;
					}
				}while(addFlag==0);
				switch(connectMore){
					case 1:
						find = stationManager_findStationByCoordinate(root, temp->rowPos-1, temp->colPos);
						stationManager_neutralizeShown(root);
						temp->north = find;
						find->south = temp;
						break;
					case 2:
						find = stationManager_findStationByCoordinate(root, temp->rowPos+1, temp->colPos);
						stationManager_neutralizeShown(root);
						temp->south = find;
						find->north = temp;
						break;
					case 3:
						find = stationManager_findStationByCoordinate(root, temp->rowPos, temp->colPos-1);
						stationManager_neutralizeShown(root);
						temp->west = find;
						find->east = temp;
						break;
					case 4:
						find = stationManager_findStationByCoordinate(root, temp->rowPos, temp->colPos+1);
						stationManager_neutralizeShown(root);
						temp->east = find;
						find->west = temp;
						break;
				}
			}
		}
	}
	system("cls");
	stationManager_showStation(root);
	printf(" %s has been added to the system!\n", stationName);
	printf(" Press enter to continue..");
	getchar();
	return root;
}

// 10. Delete Station Menu
struct stationManager_station* stationManager_deleteStation(struct stationManager_station *root){
	if(!root){
		system("cls");
		printf(" There are no stations!");
		getchar();
		return NULL;
	}
	int deleteFlag = 1;
	char deleteName[255];
	do{
		system("cls");
		deleteFlag = 1;
		stationManager_showStation(root);
		printf(" Select Station that you want to delete [cancel to exit]!\n");
		stationManager_showConnectedStations(root, "delete");
		printf(" >> ");
		scanf("%[^\n]", deleteName);
		getchar();
		if(strcmpi(deleteName, "cancel")==0){
			return root;
		}
		stationManager_curr = stationManager_findStationByName(root, deleteName);
		stationManager_neutralizeShown(root);
		if(!stationManager_curr){
			deleteFlag = 0;
		}
		else if(!stationManager_setSafety(root, stationManager_curr->rowPos, stationManager_curr->colPos)){
			deleteFlag = 0;
		}
		else if(strcmpi(stationManager_curr->name, deleteName)!=0){
			deleteFlag = 0;
		}
	}while(deleteFlag==0);
	// selected stationManager_station is root
	if(stationManager_curr == root){
		if(stationManager_curr->north){
			root = stationManager_curr->north;
		}	
		else if(stationManager_curr->south){
			root = stationManager_curr->south;
		}
		else if(stationManager_curr->east){
			root = stationManager_curr->east;
		}
		else if(stationManager_curr->west){
			root = stationManager_curr->west;
		}
	}
	// sever all connections to other trains
	if(stationManager_curr->north){
		stationManager_curr->north->south = NULL;
	}
	if(stationManager_curr->south){
		stationManager_curr->south->north = NULL;
	}
	if(stationManager_curr->east){
		stationManager_curr->east->west = NULL;
	}
	if(stationManager_curr->west){
		stationManager_curr->west->east= NULL;
	}
	// update min and max row and col
	if(stationManager_minCol == stationManager_curr->colPos){
		int colFlag = 0;
		for(int i=stationManager_minRow;i<=stationManager_maxRow;++i){
			if(i==stationManager_curr->rowPos){
				continue;
			}
			struct stationManager_station* find = stationManager_findStationByCoordinate(root, i, stationManager_minCol);
			stationManager_neutralizeShown(root);
			if(find && find->colPos == stationManager_minCol && find->rowPos==i){
				colFlag = 1;
				break;
			}
		}
		if(!colFlag){
			stationManager_minCol++;
		}
	}
	else if(stationManager_maxCol== stationManager_curr->colPos){
		int colFlag = 0;
		for(int i=stationManager_minRow;i<=stationManager_maxRow;++i){
			if(i==stationManager_curr->rowPos){
				continue;
			}
			struct stationManager_station* find = stationManager_findStationByCoordinate(root, i, stationManager_maxCol);
			stationManager_neutralizeShown(root);
			if(find && find->colPos==stationManager_maxCol && find->rowPos==i){
				colFlag = 1;
				break;
			}
		}
		if(!colFlag){
			stationManager_maxCol--;
		}
	}
	if(stationManager_minRow == stationManager_curr->rowPos){
		int rowFlag = 0;
		for(int i=stationManager_minCol;i<=stationManager_maxCol;++i){
			if(i==stationManager_curr->colPos){
				continue;
			}
			struct stationManager_station* find = stationManager_findStationByCoordinate(root, stationManager_minRow, i);
			stationManager_neutralizeShown(root);
			if(find && find->colPos==i && find->rowPos == stationManager_minRow){
				rowFlag = 1;
				break;
			}
		}
		if(!rowFlag){
			stationManager_minRow++;
		}
	}
	else if(stationManager_maxRow== stationManager_curr->rowPos){
		int rowFlag = 0;
		for(int i=stationManager_minCol;i<=stationManager_maxCol;++i){
			if(i==stationManager_curr->colPos){
				continue;
			}
			struct stationManager_station* find = stationManager_findStationByCoordinate(root, stationManager_maxRow, i);
			stationManager_neutralizeShown(root);
			if(find && find->colPos==i && find->rowPos==stationManager_maxRow){
				rowFlag = 1;
				break;
			}
		}
		if(!rowFlag){
			stationManager_maxRow--;
		}
	}
	// free the selected station
	if(stationManager_curr==root){
		stationManager_minRow = 0;
		stationManager_maxRow = 0;
		stationManager_minCol = 0;
		stationManager_maxCol = 0;
		free(root);
		return NULL;
	}
	else{
		free(stationManager_curr);
		stationManager_curr = NULL;
		return root;
	}
}

// 11. function to show station (seems redundant tho)
void stationManager_viewStation(struct stationManager_station *root){
	system("cls");
	if(!root){
		printf(" There are no stations!");
		getchar();
		return;
	}
	stationManager_showStation(root);
	printf("\n\n Press enter to continue..");
	getchar();
}

struct stationManager_coordinates{
	int row;
	int col;
};

// 12. function to find shortest route using bfs
void stationManager_findRoute(struct stationManager_station *root){
	int counter = 0;
	for(int i=stationManager_minRow;i<=stationManager_maxRow;++i){
		for(int j=stationManager_minCol;j<=stationManager_maxCol;++j){
			struct stationManager_station *cari = stationManager_findStationByCoordinate(root, i, j);
			stationManager_neutralizeShown(root);
			if(cari && cari->rowPos==i && cari->colPos==j){
				counter++;
			}
		}
	}
	if(counter<2){
		system("cls");
		printf(" There must be at least 2 stations!\n");
		printf(" Press enter to continue..");
		getchar();
		return;
	}
	int routeFlag = 1;
	struct stationManager_station *source = NULL, *destination = NULL;
	char sourceName[255], destinationName[255];
	do{
		system("cls");
		routeFlag = 0;
		stationManager_showStation(root);
		printf(" Select Station to depart [cancel to exit]:\n");
		stationManager_showConnectedStations(root, "findRoute");
		printf(" >> ");
		scanf("%[^\n]", sourceName);
		getchar();
		if(strcmpi(sourceName,"cancel")==0){
			return;
		}
		source= stationManager_findStationByName(root, sourceName);
		if(source && strcmpi(source->name, sourceName)==0){
			routeFlag = 1;
		}
		stationManager_neutralizeShown(root);
	}while(routeFlag==0);
	do{
		system("cls");
		routeFlag = 0;
		stationManager_showStation(root);
		printf(" Select Station as a destination [cancel to exit]:\n");
		stationManager_showConnectedStations(root, "findRoute");
		printf(" >> ");
		scanf("%[^\n]", destinationName);
		getchar();
		if(strcmpi(destinationName,"cancel")==0){
			return;
		}
		destination = stationManager_findStationByName(root, destinationName);
		if(destination && strcmpi(destination->name, destinationName)==0 && strcmpi(destination->name, source->name)!=0){
			routeFlag = 1;
		}
		stationManager_neutralizeShown(root);
	}while(routeFlag==0);
	int routeMatrix[300][450];
	bool visited[300][450];
	for(int i=stationManager_minRow;i<=stationManager_maxRow;++i){
		for(int j=stationManager_minCol;j<=stationManager_maxCol;++j){
			struct stationManager_station *find = stationManager_findStationByCoordinate(root, i, j);
			stationManager_neutralizeShown(root);
			if(find && find->rowPos == i && find->colPos==j){
				routeMatrix[i+stationManager_minRow][j+stationManager_minCol] = 1;
			}
			else{
				routeMatrix[i+stationManager_minRow][j+stationManager_minCol] = 0;
			}
			visited[i+stationManager_minRow][j+stationManager_minCol] = false;
		}
	}
	int queueIndex = 0;
	struct stationManager_coordinates queue[1005];
	struct stationManager_coordinates prev[300][450];
	// setup initial position
	queue[queueIndex].row = source->rowPos;
	queue[queueIndex].col = source->colPos;
	prev[queue[queueIndex].row][queue[queueIndex].col].row =  source->rowPos;
	prev[queue[queueIndex].row][queue[queueIndex].col].col =  source->colPos;
	int front = 0, length = 1, queueFlag = 1;
	int mRow[4]={1,0,-1,0}, mCol[4]={0,1,0,-1};
	for(int i=front;i<=length;++i){
		for(int j=0;j<4;++j){
			if(routeMatrix[queue[i].row+stationManager_minRow+mRow[j]][queue[i].col+stationManager_minCol+mCol[j]]==1 && !visited[queue[i].row+stationManager_minRow+mRow[j]][queue[i].col+stationManager_minCol+mCol[j]]){
				length++;
				queueIndex++;
				queue[queueIndex].row = queue[i].row + mRow[j];
				queue[queueIndex].col = queue[i].col + mCol[j];
				visited[queue[i].row+stationManager_minRow+mRow[j]][queue[i].col+stationManager_minCol+mCol[j]] = true;
				prev[queue[queueIndex].row][queue[queueIndex].col].row = queue[i].row;
				prev[queue[queueIndex].row][queue[queueIndex].col].col = queue[i].col;
			}
		}
	}
	int currRow = destination->rowPos, currCol = destination->colPos;
	char routeName[300][450];
	int routeIndex = 0;
	long long totalPrice = 0;
	int noteRow = currRow, noteCol = currCol;
	struct stationManager_station *temp= NULL;
	while(true){
		int nextRow = prev[currRow][currCol].row;
		int nextCol = prev[currRow][currCol].col;
		temp = stationManager_findStationByCoordinate(root, currRow, currCol);
		stationManager_neutralizeShown(root);
		strcpy(routeName[routeIndex], temp->name);
		totalPrice+= temp->price;
		routeIndex++;
		if(currRow==source->rowPos && currCol==source->colPos){
			break;
		}
		currRow = nextRow;
		currCol = nextCol;
	}
	system("cls");
	printf(" The most efficient route from %s to %s is:\n", source->name, destination->name);
	for(int i=routeIndex-1;i>=0;--i){
		printf(" %s", routeName[i]);
		if(i==0){
			printf("\n");
		}
		else{
			printf("->");
		}
	}
	printf(" Total Price : Rp. %lld\n", totalPrice);
	printf("\n Press enter to continue..");
	getchar();
	return;
}

struct stationManager_station* stationManager_manageStation(struct stationManager_station *root){
	if(!root){
		system("cls");
		printf(" There are no stations!");
		getchar();
		return NULL;
	}
	char manageName[255];
	int manageFlag = 1;
	do{
		system("cls");
		manageFlag = 1;
		stationManager_showStation(root);
		printf(" Select station that you want to manage![cancel to exit]\n");
		stationManager_showConnectedStations(root, "manage");
		printf(" >> ");
		scanf("%[^\n]", manageName);
		getchar();
		stationManager_curr= stationManager_findStationByName(root, manageName);
		stationManager_neutralizeShown(root);
		if(!stationManager_curr){
			manageFlag = 0;
		}
		else if(strcmpi(stationManager_curr->name, manageName)!=0){
			manageFlag = 0;
		}
	}while(manageFlag==0);
	char choice;
	do{
		system("cls");
		printf(" Station Name: %s\n", stationManager_curr->name);
		printf(" Station Ticket Price: Rp. %lld\n\n", stationManager_curr->price);
		printf(" Select the attribute you want to change! [x to exit]\n");
		printf(" 1. Station Name\n");
		printf(" 2. Station Ticket Price\n");
		printf(" >> ");
		choice = getch();
		printf("%c\n");
		switch(choice){
			case '1':
				char name[255];
				do{
					manageFlag = 1;
					printf(" Enter the Station Name [5-25 characters, 2 Words Minimal, Unique][x to cancel] : ");
					scanf("%[^\n]", name);
					getchar();
					int length = strlen(name);
					if(strcmpi(name,"x")==0){
						break;
					}
					if(length<5 || length>25){
						manageFlag = 0;
						printf(" Station name must be between 5 - 25 characters!\n");
					}
					else{
						int flag = 0;
						for(int i=1;i<length-1;++i){
							if(name[i]==' '){
								flag = 1;
								break;
							}
						}
						if(!flag){
							manageFlag=0;
							printf(" Station name must be composed of at least 2 words!\n");
						}
						else{
							struct stationManager_station* check = stationManager_findStationByName(root, name);
							stationManager_neutralizeShown(root);
							if(check && strcmpi(check->name, name)==0){
								manageFlag = 0;
								printf(" Station name must be unique!\n");
							}	
						}
					}
				}while(manageFlag==0);
				if(strcmpi(name,"x")!=0){
					strcpy(stationManager_curr->name, name);
				}
				break;
			case '2':
				long long stationPrice = 0;
				do{
					stationPrice = 0;
					manageFlag = 1;
					printf(" Enter the Station Ticket Price [Rp. 100.000 - Rp. 1.000.000] [-1 to exit]: Rp. ");
					scanf("%lld", &stationPrice);
					getchar();
					if(stationPrice == -1){
						break;
					}
					if(stationPrice<100000 || stationPrice>1000000){
						manageFlag = 0;
						printf(" Price must be between Rp. 100.000 - Rp. 1.000.000!\n");
					}
				}while(manageFlag==0);
				if(stationPrice!=-1){
					stationManager_curr->price = stationPrice;
				}
				break;
		}
	}while(choice!='x');
	return root;
}

void stationManager_setup(){
	stationManager_minRow = 0, stationManager_maxRow = 0, stationManager_minCol = 0, stationManager_maxCol = 0;
}

void stationManager_game(){
	struct stationManager_station *root = NULL;
	stationManager_setup();
	char choice;
	do{
		do{
			system("cls");
			stationManager_logo();
			printf("\t\t\t 1. Add New Station\n");
			printf("\t\t\t 2. Delete Station\n");
			printf("\t\t\t 3. Manage Station\n");
			printf("\t\t\t 4. View All Station\n");
			printf("\t\t\t 5. Find Station Route\n");
			printf("\t\t\t 6. Exit\n");
			printf("\t\t\t >> ");
			choice = getch();
			printf("%c\n", choice);
		}while(choice-'0'<1 || choice-'0'>6);
		switch(choice-'0'){
			case 1:
				root = stationManager_addStation(root);
				break;
			case 2:
				root = stationManager_deleteStation(root);
				break;
			case 3:
				root = stationManager_manageStation(root);
				break;
			case 4:
				stationManager_viewStation(root);
				break;
			case 5:
				stationManager_findRoute(root);
				break;
		}
	}while(choice-'0'!=6);
	return;
}
