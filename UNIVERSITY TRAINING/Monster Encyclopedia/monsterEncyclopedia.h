#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

const int monsterEncyclopedia_SIZE = 256;

struct monsterEncyclopedia_Monster{
	char id[255], name[255], type[255], location[255];
	double size;
	struct monsterEncyclopedia_Monster *next;
}*monsterEncyclopedia_hashTable[monsterEncyclopedia_SIZE]={NULL};

struct monsterEncyclopedia_Monster *monsterEncyclopedia_createMonster(char*id, char*name, char*type, char*loc, double size){
	struct monsterEncyclopedia_Monster *newMonster = (struct monsterEncyclopedia_Monster*)malloc(sizeof(struct monsterEncyclopedia_Monster));
	strcpy(newMonster->id, id);
	strcpy(newMonster->name, name);
	strcpy(newMonster->type, type);
	strcpy(newMonster->location, loc);
	newMonster->size = size;
	newMonster->next = NULL;
	return newMonster;
}

int monsterEncyclopedia_getHash(char*id){
	int len = strlen(id), res = 0;
	for(int i=0;i<len;++i){
		res+=id[i];
	}
	return res%256;
}

void monsterEncyclopedia_push(char*id, char*name, char*type, char*loc, double size){
	struct monsterEncyclopedia_Monster *newMonster = monsterEncyclopedia_createMonster(id,name,type,loc,size);
	int index = monsterEncyclopedia_getHash(id);
	if(!monsterEncyclopedia_hashTable[index]){
		monsterEncyclopedia_hashTable[index] = newMonster;
	}	
	else{
		struct monsterEncyclopedia_Monster*curr = monsterEncyclopedia_hashTable[index];
		while(curr->next){
			curr = curr->next;
		}
		curr->next = newMonster;
	}
	return;
}

bool monsterEncyclopedia_pop(char *id){
	int index = monsterEncyclopedia_getHash(id);
	if(!monsterEncyclopedia_hashTable[index]){
		return false;
	}
	struct monsterEncyclopedia_Monster *curr = monsterEncyclopedia_hashTable[index];
	if(strcmp(monsterEncyclopedia_hashTable[index]->id,id)==0){
		monsterEncyclopedia_hashTable[index] = curr->next;
		free(curr);
		curr = NULL;
		return true;
	}
	else{
		while(curr->next && strcmp(curr->next->id,id)!=0){
			curr = curr->next;
		}
		if(!curr->next){
			return false;
		}
		struct monsterEncyclopedia_Monster *temp = curr->next;
		curr->next = temp->next;
		free(temp);
		temp = NULL;
		return true;
	}
}

bool monsterEncyclopedia_displayAll(){
	bool empty = true;
	for(int i =0;i<monsterEncyclopedia_SIZE;++i){
		struct monsterEncyclopedia_Monster *temp = monsterEncyclopedia_hashTable[i];
		while(temp){
			printf(" =================================\n");
			printf(" ID      : %s\n", temp->id);
			printf(" Name    : %s\n", temp->name);
			printf(" Type    : %s\n", temp->type);
			printf(" Size    : %.1lf\n", temp->size);
			printf(" Location: %s\n", temp->location);
			printf(" =================================\n\n");
			temp = temp->next;
			empty = false;
		}
	}
	if(empty){
		return false;
	}
	return true;
}

struct monsterEncyclopedia_Monster *monsterEncyclopedia_searchMonster(char *id){
	int index = monsterEncyclopedia_getHash(id);
	if(!monsterEncyclopedia_hashTable[index]){
		return NULL;
	}
	struct monsterEncyclopedia_Monster *curr = monsterEncyclopedia_hashTable[index];
	if(strcmp(monsterEncyclopedia_hashTable[index]->id,id)==0){
		return curr;	
	}
	else{
		while(curr->next && strcmp(curr->next->id,id)!=0){
			curr = curr->next;
		}
		if(!curr->next){
			return NULL;
		}
		return curr->next;
	}
}

void monsterEncyclopedia_insertMonster(){
	system("cls");
	printf("\n\n");
	getchar();
	int addFlag = 1;
	char name[255];
	do{
		addFlag = 1;
		printf(" Input monster name[3 - 20 characters | Starts with Capital Letter]: ");
		scanf("%[^\n]", name);
		getchar();
		int len = strlen(name);
		if(len<3||len>20){
			addFlag = 0;
		}
		else if(!(name[0]>='A' && name[0]<='Z')){
			addFlag = 0;
		}
	}while(addFlag==0);
	char type[255];
	do{
		addFlag = 1;
		printf(" Input monster type[Large | Small | Endemic | Pets](case sensitive): ");
		scanf("%[^\n]", type);
		getchar();
		if(strcmp(type,"Large")!=0 && strcmp(type,"Small")!=0 && strcmp(type,"Endemic")!=0 && strcmp(type,"Pets")!=0){
			addFlag = 0;
		}
	}while(addFlag==0);
	double size;
	do{
		addFlag = 1;
		printf(" Input monster size[100.0 - 5000.0](inclusive): ");
		scanf("%lf", &size);
		getchar();
		if(size<100.0 || size>5000.0){
			addFlag = 0;
		}
	}while(addFlag==0);
	char loc[255];
	do{
		addFlag = 0;
		printf(" Input monster location[ends with Biome](case sensitive): ");
		scanf("%[^\n]", loc);
		getchar();
		int len = strlen(loc);
		if(loc[len-1]=='e' && loc[len-2]=='m' && loc[len-3]=='o' && loc[len-4]=='i' && loc[len-5]=='B' && loc[len-6]==' '){
			addFlag = 1;
		}
	}while(addFlag==0);
	char id[7];
	for(int i=0;i<3;++i){
		id[i] = name[i];
		if(id[i]>='a' && id[i]<='z'){
			id[i]+='A'-'a';
		}
	}
	srand(time(0));
	int num = rand()%1000;
	char temp[3]="";
	sprintf(temp,"%03d", num);
	for(int i=3;i<6;++i){
		id[i] = temp[i-3];
	}
	id[6] = '\0';
	printf(" Monster ID : %s\n", id);
	monsterEncyclopedia_push(id,name,type,loc,size);
	printf(" New Monster successfully added!\n");
	printf(" Press enter to continue..");
	getchar();
	return;
}

void monsterEncyclopedia_changeMonster(){
	system("cls");
	printf("\n\n");
	monsterEncyclopedia_displayAll();
	char id[255];
	printf(" Input monster id: ");
	scanf("%s", id);
	getchar();
	struct monsterEncyclopedia_Monster *find = monsterEncyclopedia_searchMonster(id);
	if(!find){
		printf(" Monster not found...");
	}
	else{
		printf(" [Input 0 to skip update]\n");
		int addFlag = 1;
		bool modify = true;
		char name[255];
		do{
			modify = true;
			addFlag = 1;
			printf(" Input monster name[3 - 20 characters | Starts with Capital Letter]: ");
			scanf("%[^\n]", name);
			getchar();
			int len = strlen(name);
			if(strcmp(name,"0")==0){
				modify = false;
				break;
			}
			if(len<3||len>20){
				addFlag = 0;
			}
			else if(!(name[0]>='A' && name[0]<='Z')){
				addFlag = 0;
			}
		}while(addFlag==0);
		if(modify){
			strcpy(find->name, name);
		}
		char type[255];
		do{
			modify = true;
			addFlag = 1;
			printf(" Input monster type[Large | Small | Endemic | Pets](case sensitive): ");
			scanf("%[^\n]", type);
			getchar();
			if(strcmp(type,"0")==0){
				modify = false;
				break;
			}
			if(strcmp(type,"Large")!=0 && strcmp(type,"Small")!=0 && strcmp(type,"Endemic")!=0 && strcmp(type,"Pets")!=0){
				addFlag = 0;
			}
		}while(addFlag==0);
		if(modify){
			strcpy(find->type, type);
		}
		double size;
		do{
			modify = true;
			addFlag = 1;
			printf(" Input monster size[100.0 - 5000.0](inclusive): ");
			scanf("%lf", &size);
			getchar();
			if(size==0){
				modify = false;
				break;
			}
			if(size<100.0 || size>5000.0){
				addFlag = 0;
			}
		}while(addFlag==0);
		if(modify){
			find->size = size;
		}
		char loc[255];
		do{
			modify = true;
			addFlag = 0;
			printf(" Input monster location[ends with Biome](case sensitive): ");
			scanf("%[^\n]", loc);
			getchar();
			if(strcmp(loc,"0")==0){
				modify = false;
				break;
			}
			int len = strlen(loc);
			if(loc[len-1]=='e' && loc[len-2]=='m' && loc[len-3]=='o' && loc[len-4]=='i' && loc[len-5]=='B'){
				addFlag = 1;
			}
		}while(addFlag==0);
		if(modify){
			strcpy(find->location, loc);
		}
		printf(" Monster successfully modified!\n");
		printf(" Press enter to continue..");
	}
	getchar();
	return;
}

void monsterEncyclopedia_removeMonster(){
	system("cls");
	printf("\n\n");
	monsterEncyclopedia_displayAll();
	char id[255];
	printf(" Input monster id: ");
	scanf("%s", id);
	getchar();
	struct monsterEncyclopedia_Monster *find = monsterEncyclopedia_searchMonster(id);
	if(find){
		system("cls");
		printf(" =================================\n");
		printf(" ID      : %s\n", find->id);
		printf(" Name    : %s\n", find->name);
		printf(" Type    : %s\n", find->type);
		printf(" Size    : %.1lf\n", find->size);
		printf(" Location: %s\n", find->location);
		printf(" =================================\n\n");
	}
	bool deleted = monsterEncyclopedia_pop(id);
	if(deleted){
		printf(" Monster successfully deleted!\n");
	}
	else printf(" Monster not found!\n");
	printf(" Press enter to continue..");
	getchar();
}

void monsterEncyclopedia_game(){
	char menu;
	do{
		system("cls");
		printf("\n\n");
		monsterEncyclopedia_displayAll();
		printf("\n");
		printf(" ==========================\n");
		printf(" << Monster Encyclopedia >>\n");
		printf(" ==========================\n");
		printf(" 1. Insert New Monster\n");
		printf(" 2. Change Monster Data\n");
		printf(" 3. Remove Monster\n");
		printf(" 4. Close Book\n");
		printf(" >> ");
		menu = getchar();
		switch(menu-'0'){
			case 1:
				monsterEncyclopedia_insertMonster();
				break;
			case 2:
				monsterEncyclopedia_changeMonster();
				break;
			case 3:
				monsterEncyclopedia_removeMonster();
				break;
		}
	}while(menu!='4');
	return;
}
