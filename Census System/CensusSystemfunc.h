#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<windows.h>

const int censusSystem_TABLESIZE = 65536;
const int censusSystem_STATE = 51;

unsigned char censusSystem_mockData[256] = {
    251, 175, 119, 215, 81, 14, 79, 191, 103, 49, 181, 143, 186, 157,  0,
    232, 31, 32, 55, 60, 152, 58, 17, 237, 174, 70, 160, 144, 220, 90, 57,
    223, 59,  3, 18, 140, 111, 166, 203, 196, 134, 243, 124, 95, 222, 179,
    197, 65, 180, 48, 36, 15, 107, 46, 233, 130, 165, 30, 123, 161, 209, 23,
    97, 16, 40, 91, 219, 61, 100, 10, 210, 109, 250, 127, 22, 138, 29, 108,
    244, 67, 207,  9, 178, 204, 74, 98, 126, 249, 167, 116, 34, 77, 193,
    200, 121,  5, 20, 113, 71, 35, 128, 13, 182, 94, 25, 226, 227, 199, 75,
    27, 41, 245, 230, 224, 43, 225, 177, 26, 155, 150, 212, 142, 218, 115,
    241, 73, 88, 105, 39, 114, 62, 255, 192, 201, 145, 214, 168, 158, 221,
    148, 154, 122, 12, 84, 82, 163, 44, 139, 228, 236, 205, 242, 217, 11,
    187, 146, 159, 64, 86, 239, 195, 42, 106, 198, 118, 112, 184, 172, 87,
    2, 173, 117, 176, 229, 247, 253, 137, 185, 99, 164, 102, 147, 45, 66,
    231, 52, 141, 211, 194, 206, 246, 238, 56, 110, 78, 248, 63, 240, 189,
    93, 92, 51, 53, 183, 19, 171, 72, 50, 33, 104, 101, 69, 8, 252, 83, 120,
    76, 135, 85, 54, 202, 125, 188, 213, 96, 235, 136, 208, 162, 129, 190,
    132, 156, 38, 47, 1, 7, 254, 24, 4, 216, 131, 89, 21, 28, 133, 37, 153,
    149, 80, 170, 68, 6, 169, 234, 151
};

char censusSystem_stateAlias[censusSystem_STATE][5]={
	"AK", "AL", "AR", "AZ", "CA", "CO", "CT", "DE", "FL", "GA", "HI", "IA", "ID", "IL", "IN", "KS", "KY",
	"LA", "MA", "MD", "ME", "MI", "MN", "MO", "MS", "MT", "NC", "ND", "NE", "NH", "NJ", "NM", "NV", "NY",
	"OH", "OK", "OR", "PA", "RI", "SC", "SD", "TN", "TX", "UT", "VA", "VT", "WA", "WI", "WV", "WY", "DC"
};

void censusSystem_printState(){
	printf("\n  Available States:\n\n");
	for(int i=0;i<censusSystem_STATE;i+=17){
		printf(" ");
		for(int j=i;j<i+17;++j){
			printf("%s ", censusSystem_stateAlias[j]);
		}
		printf("\n");
	}
}

unsigned long long censusSystem_pearsonHash(char*string){
	int len = strlen(string);
	unsigned char h;
	unsigned long long returnValue;
	for(int i=0;i<8;++i){
		h = censusSystem_mockData[(string[0]+i)%256];
		for(int j=0;j<len;++j){
			h = censusSystem_mockData[h^string[j]];
		}
		returnValue = (returnValue<<8)|h;
	}
	return returnValue;	
}

int censusSystem_getNameHash(char*string){
	unsigned long long hash = censusSystem_pearsonHash(string);
	return hash%censusSystem_TABLESIZE;
}

int censusSystem_getStateHash(char*string){
    for(int i=0;i<censusSystem_STATE;++i){
    	if(strcmpi(censusSystem_stateAlias[i],string)==0){
    		return i;
		}
	}
	return -1;
}
struct censusSystem_citizen{
	char name[255];
	long long quantity;
	struct censusSystem_citizen* next;
}*censusSystem_hashTable[censusSystem_STATE][censusSystem_TABLESIZE]={NULL};

struct censusSystem_citizen* censusSystem_createData(char *name, long long qty){
	struct censusSystem_citizen *newData = (struct censusSystem_citizen*)malloc(sizeof(struct censusSystem_citizen));
	strcpy(newData->name, name);
	newData->quantity = qty;
	newData->next = NULL;
	return newData;
}

struct censusSystem_citizen* censusSystem_pushCitizen(char*state, char *name, long long quantity){
	struct censusSystem_citizen *temp = censusSystem_createData(name, quantity);
	int hashName = censusSystem_getNameHash(name), hashState = censusSystem_getStateHash(state);
	if(!censusSystem_hashTable[hashState][hashName]){
		censusSystem_hashTable[hashState][hashName] = temp;
	}
	else{
		struct censusSystem_citizen *curr = censusSystem_hashTable[hashState][hashName];
		while(curr->next){
			if(strcmp(name, curr->name)==0){
				curr->quantity += quantity;
				return curr;;
			}
			curr = curr->next;
		}
		curr->next = temp;
	}
	return temp;
}

int censusSystem_popCitizen(char *state, char *name){
	int hashName = censusSystem_getNameHash(name), hashState = censusSystem_getStateHash(state);
	if(!censusSystem_hashTable[hashState][hashName]){
		return 0;
	}
	else{
		struct censusSystem_citizen *curr = censusSystem_hashTable[hashState][hashName];
		if(strcmp(curr->name, name)==0){
			struct censusSystem_citizen *temp = curr;
			curr = curr->next;
			free(temp);
			censusSystem_hashTable[hashState][hashName] = curr;
			return 1;
		}
		else{
			while(curr->next && strcmp(curr->next->name, name)!=0){
				curr = curr->next;
			}
			if(!curr->next){
				return 0;
			}
			else{
				struct censusSystem_citizen *temp = curr->next;
				curr->next = curr->next->next;
				free(temp);
				return 1;
			}
		}
	}
}

void censusSystem_insertCitizen(){
	char name[255], state[5];
	long long qty;
	int insertFlag = 1;
	system("cls");
	printf("\n");
	do{
		insertFlag = 1;
		printf(" Please enter citizen's name [3 - 20 characters | First name only | Case Sensitive][cancel to exit]: ");
		scanf("%[^\n]", name);
		getchar();
		if(strcmpi(name,"cancel")==0){
			return;
		}
		int len = strlen(name);
		if(len<3 || len>20){
			insertFlag = 0;
			printf(" Citizen's name must be between 3-20 characters!\n");
		}
		else{
			for(int i=0;i<len;++i){
				if(name[i]==' '){
					insertFlag = 0;
					printf(" Citizen's name must only be the first name!\n");
					break;
				}
			}
		}
	}while(insertFlag==0);
	system("cls");
	printf("\n");
	do{
		insertFlag = 1;
		censusSystem_printState();
		printf("\n Insert the citizen's state [cancel to exit]: ");
		scanf("%s", state);
		getchar();
		if(strcmpi(state,"cancel")==0){
			return;
		}
		int stateId = censusSystem_getStateHash(state);
		if(stateId==-1){
			insertFlag = 0;
			printf(" Selected state must be one of US States!\n\n");
		}
	}while(insertFlag==0);
	system("cls");
	printf("\n");
	do{
		insertFlag=1;
		printf(" Insert citizen's quantity: ");
		scanf("%lld", &qty);
		getchar();
		if(qty<=0){
			printf(" Number of citizen must be larger than 0!\n");
			insertFlag = 0;
		}
	}while(insertFlag==0);
	struct censusSystem_citizen *curr = censusSystem_pushCitizen(state, name, qty);
	printf(" There are now %lld citizen(s) whose name is \'%s\'!\n", curr->quantity, curr->name);
	printf(" Press enter to continue..");
	getchar();
	return;
}

void censusSystem_removeCitizen(){
	char name[255], state[5];
	long long qty;
	int deleteFlag = 1;
	system("cls");
	printf("\n");
	do{
		deleteFlag = 1;
		printf(" Please enter citizen's name [3 - 20 characters | First name only | Case Sensitive][cancel to exit]: ");
		scanf("%[^\n]", name);
		getchar();
		if(strcmpi(name,"cancel")==0){
			return;
		}
		int len = strlen(name);
		if(len<3 || len>20){
			deleteFlag = 0;
			printf(" Citizen's name must be between 3-20 characters!\n");
		}
		else{
			for(int i=0;i<len;++i){
				if(name[i]==' '){
					deleteFlag = 0;
					printf(" Citizen's name must only be the first name!\n");
					break;
				}
			}
		}
	}while(deleteFlag==0);
	system("cls");
	printf("\n");
	do{
		deleteFlag = 1;
		censusSystem_printState();
		printf("\n Insert the citizen's state [cancel to exit]: ");
		scanf("%s", state);
		getchar();
		if(strcmpi(state,"cancel")==0){
			return;
		}
		int stateId = censusSystem_getStateHash(state);
		if(stateId==-1){
			deleteFlag = 0;
			printf(" Selected state must be one of US States!\n\n");
		}
	}while(deleteFlag==0);
	system("cls");
	printf("\n");
	char choice;
	do{
		deleteFlag = 0;
		printf(" Are you sure you want to remove %s from %s? [y/n]: ", name, state);
		choice = getchar();
		getchar();
		if(choice=='y' || choice=='n'){
			deleteFlag = 1;
		}
	}while(deleteFlag==0);
	if(choice=='y'){
		int res = censusSystem_popCitizen(state, name);
		if(res==0){
			printf(" Combination of state and name not found!\n");
		}
		else{
			printf(" Successfully removed %s from %s\n", name, state);
		}
	}
	printf(" Press enter to continue..");
	getchar();
	return;
	
}

bool censusSystem_directoryExists(char *path){
	struct stat stats;
    stat(path, &stats);
    // Check for file existence
    if (S_ISDIR(stats.st_mode)){
	    return true;
	}
    return false;
}

bool censusSystem_fileInUse(char* szFilename){   
	HANDLE hFile = CreateFile(szFilename, GENERIC_READ|GENERIC_WRITE, 0, NULL,      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);   
	if(hFile == INVALID_HANDLE_VALUE){
		CloseHandle(hFile);
		return true;   
	}
	CloseHandle(hFile);
	return false;

}

void censusSystem_searchCitizen(){
	char name[255];
	int searchFlag = 1;
	system("cls");
	printf("\n Insert citizen's name that you want to find [Case Sensitive][cancel to exit]: ");
	scanf("%[^\n]", name);
	getchar();
	if(strcmp(name,"cancel")==0){
		return;
	}
	printf(" Searching for \'%s\' in all states....\n", name);
	long long resultQty[censusSystem_STATE], totalQty = 0;
	int resultIndex = 0;
	char resultState[censusSystem_STATE][255];
	int hash = censusSystem_getNameHash(name);
	for(int i=0;i<censusSystem_STATE;++i){
		if(censusSystem_hashTable[i][hash]){
			struct censusSystem_citizen *curr = censusSystem_hashTable[i][hash];
			while(curr){
				if(strcmp(curr->name, name)==0){
					strcpy(resultState[resultIndex], censusSystem_stateAlias[i]);
					resultQty[resultIndex] = curr->quantity;
					resultIndex++;
					totalQty+=curr->quantity;
				}
				curr = curr->next;
			}
		}
	}
	if(resultIndex==0){
		printf(" There is no \'%s\' in the table!\n", name);
	}
	else{
		printf(" '\%s\' is found in %d state(s)!\n", name, resultIndex);
		printf(" +===========================+=======+=========+\n");
		printf(" | Name                      | State | Count   |\n");
		printf(" +===========================+=======+=========+\n");
		for(int i=0;i<resultIndex;++i){
			printf(" | %-25s | %s    | %-7lld |\n", name, resultState[i], resultQty[i]);
		}
		printf(" +===========================+=======+=========+\n");
		printf("  Grand Total: %lld people\n\n", totalQty);
		char choice;
		do{
			searchFlag = 1;
			printf(" Do you want to save the search result? [y/n]: ");
			choice = getchar();
			getchar();
			if(choice!='y' && choice!='n'){
				searchFlag = 1;
			}
		}while(searchFlag==0);
		if(choice=='n'){
			printf(" Press enter to continue..");
			getchar();
			return;
		}
		else{
			char result[255] = ".\\Census System\\results";
			if(!censusSystem_directoryExists(result)){
				printf(" The directory haven't been created yet!\n");
				printf(" Press enter to continue..");
				getchar();
				return;
			}
			strcat(result, "\\");
			strcat(result, (const char*)name);
			strcat(result,".txt");
			// due to an unidentified bug, the program will not check if the file is in use
			// it doesn't really matter since the file is saved in .txt format, if open with notepad, will be seen as not in use (different case if its open in a text editor
//			if(censusSystem_fileInUse(result)){
//				printf(" File is currently in use!\n");
//				printf(" Press enter to continue..");
//				getchar();
//				return;
//			}
			FILE *fResult = fopen(result, "w");
			fprintf(fResult," +===========================+=======+=========+\n");
			fprintf(fResult," | Name                      | State | Count   |\n");
			fprintf(fResult, " +===========================+=======+=========+\n");
			for(int i=0;i<resultIndex;++i){
				fprintf(fResult, " | %-25s | %s    | %-7lld |\n", name, resultState[i], resultQty[i]);
			}
			fprintf(fResult, " +===========================+=======+=========+\n");
			fprintf(fResult, "  Grand Total: %lld people\n\n", totalQty);
			fclose(fResult);
			printf(" Save completed!\n");
		}
	}
	printf(" Press enter to continue..");
	getchar();
}

void censusSystem_init(){
	system("cls");
	FILE *fCitizen = fopen(".\\Census System\\censusData.csv", "r");
	printf("\n Attempting to find censusData.csv...\n");
	if(!fCitizen){
		printf(" censusData.csv not found!\n");
		int counter = 1, loadFlag = 1;
		char fileName[255];
		do{
			loadFlag = 1;
			if(counter == 5){
				fCitizen = fopen(".\\Census System\\censusData.csv", "r");
				printf(" File is still not found.\n");
				printf(" Application will start without any existing data!\n");
				return;
			}
			else{
				printf(" Please enter the correct file name : ");
				scanf("%[^\n]", fileName);
				getchar();
				fCitizen = fopen(fileName, "r");
				printf(" Attempting to find %s...\n", fileName);
				if(!fCitizen){
					printf(" %s not found!\n", fileName);
					loadFlag = 0;
					counter++;
				} 
				else printf(" File has been found!\n");
			}
		}while(loadFlag==0);
	}
	else{
		printf(" File has been found!\n");
	}
	struct censusSystem_citizen*curr = NULL;
	char name[255], state[5];
	long long qty;
	printf(" Initializing data...\n");
	while(fscanf(fCitizen, "%[^,],%[^,],%lld\n", state, name, &qty)!=EOF){
		curr = censusSystem_pushCitizen(state, name, qty);
	}
	fclose(fCitizen);
	printf(" Initialization completed!\n");
	printf(" Press enter to continue..");
	getchar();
}

void censusSystem_loadData(){
	FILE *fCitizen = fopen(".\\Census System\\censusData.csv", "w");
	for(int i=0;i<censusSystem_STATE;++i){
		for(int j=0;j<censusSystem_TABLESIZE;++j){
			if(censusSystem_hashTable[i][j]){
				struct censusSystem_citizen *curr = censusSystem_hashTable[i][j];
				while(curr){
					fprintf(fCitizen,"%s,%s, %lld\n", censusSystem_stateAlias[i], curr->name, curr->quantity);
					curr = curr->next;
				}
			}
		}
	}
	fclose(fCitizen);
}

void censusSystem_logo(){
	printf("    ______                              _____            __             \n");  
	printf("   / ____/__  ____  _______  _______   / ___/__  _______/ /____  ____ ___ \n");
	printf("  / /   / _ \\/ __ \\/ ___/ / / / ___/   \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\\n");
	printf(" / /___/  __/ / / (__  ) /_/ (__  )   ___/ / /_/ (__  ) /_/  __/ / / / / /\n");
	printf(" \\____/\\___/_/ /_/____/\\__,_/____/   /____/\\__, /____/\\__/\\___/_/ /_/ /_/ \n");
	printf("                                          /____/                          \n\n");
}
void censusSystem_game(){	
	censusSystem_init();
	char choice;
	do{
		system("cls");
		censusSystem_logo();
		printf("\t\t\t 1. Insert Citizen\n");
		printf("\t\t\t 2. Search Citizen By Name\n");
		printf("\t\t\t 3. Delete Citizen\n");
		printf("\t\t\t 4. Exit\n");
		printf("\t\t\t >> ");
		choice = getch();
		printf("%c\n", choice);
		switch(choice-'0'){
			case 1:
				censusSystem_insertCitizen();
				break;
			case 2:
				censusSystem_searchCitizen();
				break;
			case 3:
				censusSystem_removeCitizen();
				break;
		}
	}while(choice-'0'!=4);
	censusSystem_loadData();
	return;
}
