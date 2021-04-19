#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<math.h>

// constant values (elements, species, and biome) and Helper functions
HANDLE dragonBook_Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD dragonBook_CursorPosition;

// 1. Function to move console 
void dragonBook_gotoXY(int x, int y){
	dragonBook_CursorPosition.X = x;
	dragonBook_CursorPosition.Y = y;
	SetConsoleCursorPosition(dragonBook_Console, dragonBook_CursorPosition);
}

const char dragonBook_ELEMENTS[5][25] = {
	"Wind", "Earth", 
	"Lightning", "Fire", 
	"Water"
};

const char dragonBook_SPECIES[7][50] = {  
	"Eastern Dragon", "Western Dragon", 
	"Wyvern", "Drake", 
	"Amphithere", "Wyrm", 
	"Lindwurm"
};

const char dragonBook_BIOME[7][50] = {
	"Ancient Forest", "Shady Swamp", 
	"Mystic Highlands", "Grassroots March", 
	"Sea of Monsters", "Volcanic Mountains", 
	"Dark Lands"
};

// function to print logo
void dragonBook_logo(){
	printf(" ___  ___                _                                  _   _    _ _                     _         ______ _           _   _____ _ \n");                    
	printf(" |  \\/  |               | |                                | | | |  | | |                   | |        |  ___(_)         | | |_   _| |   \n");                 
	printf(" | .  . | ___  _ __  ___| |_ ___ _ __ ___    __ _ _ __   __| | | |  | | |__   ___ _ __ ___  | |_ ___   | |_   _ _ __   __| |   | | | |__   ___ _ __ ___ \n");   
	printf(" | |\\/| |/ _ \\| '_ \\/ __| __/ _ \\ '__/ __|  / _` | '_ \\ / _` | | |/\\| | '_ \\ / _ \\ '__/ _ \\ | __/ _ \\  |  _| | | '_ \\ / _` |   | | | '_ \\ / _ \\ '_ ` _ \\  \n");
	printf(" | |  | | (_) | | | \\__ \\ ||  __/ |  \\__ \\ | (_| | | | | (_| | \\  /\\  / | | |  __/ | |  __/ | || (_) | | |   | | | | | (_| |   | | | | | |  __/ | | | | | \n");
	printf(" \\_|  |_/\\___/|_| |_|___/\\__\\___|_|  |___/  \\__,_|_| |_|\\__,_|  \\/  \\/|_| |_|\\___|_|  \\___|  \\__\\___/  \\_|   |_|_| |_|\\__,_|   \\_/ |_| |_|\\___|_| |_| |_| \n");
	return;
}

// global Helper variable

int dragonBook_NumDragon; // keep track of number of dragons

// Single Linked List inside the Dragon struct 
struct dragonBook_List{
	int element;
	struct dragonBook_List *next;
};

// create node for List
struct dragonBook_List *dragonBook_createNode(int value){
	struct dragonBook_List *newElement = (struct dragonBook_List*)malloc(sizeof(struct dragonBook_List));
	newElement->element = value;
	newElement->next = NULL;
	return newElement;
}

//push node into List
struct dragonBook_List* dragonBook_pushList(struct dragonBook_List *head, int value){
	struct dragonBook_List *curr = dragonBook_createNode(value);
	if(!head){
		head = curr;
	}
	else{
		struct dragonBook_List *temp = head;
		while(temp->next){
			temp = temp->next;
		}
		temp->next = curr;
	}
	return head;
}

//AVL TREE
struct dragonBook_Dragon{
	char name[255];
	struct dragonBook_List *eHead, *rHead,*wHead;
	double minSize, maxSize;
	int height, species, biome;
	struct dragonBook_Dragon *left, *right;
};

// get max value (Helper function for AVL Tree)
int dragonBook_max(int a, int b){
	return(a>b)? a:b;
}

// get node Height (Helper function for AVL Tree)
int dragonBook_getHeight(struct dragonBook_Dragon *root){
	if(root){
		return root->height;
	}
	else return 0;
}

// get balance Factor (Helper function for AVL Tree)
int dragonBook_getBalanceFactor(struct dragonBook_Dragon *root){
	if(root){
		return dragonBook_getHeight(root->left)-dragonBook_getHeight(root->right);
	}
	else return 0;
}

// rotate the AVL Tree depends on direction
struct dragonBook_Dragon* dragonBook_rotationType(struct dragonBook_Dragon *curr, const char* direction){
	struct dragonBook_Dragon *temp1, *temp2;
	if(strcmp(direction,"right")==0){
		temp1 = curr->left;
		temp2 = temp1->right;
		temp1->right = curr;
		curr->left = temp2;
	}
	else{
		temp1 = curr->right;
		temp2 = temp1->left;
		temp1->left = curr;
		curr->right = temp2;
	}
	curr->height = dragonBook_max(dragonBook_getHeight(curr->left), dragonBook_getHeight(curr->right))+1;
	temp1->height = dragonBook_max(dragonBook_getHeight(temp1->left), dragonBook_getHeight(temp1->right))+1;
	return temp1;
}

// find direction for rotating AVL Tree
struct dragonBook_Dragon* dragonBook_rotation(struct dragonBook_Dragon *root){
	root->height = dragonBook_max(dragonBook_getHeight(root->left), dragonBook_getHeight(root->right))+1;
	int balanceFactor = dragonBook_getBalanceFactor(root);
	if(balanceFactor<-1){
		//left rotation
		if(dragonBook_getBalanceFactor(root->right)>0){
			//Left Right Rotation
			root->right = dragonBook_rotationType(root->right, "right");
			return dragonBook_rotationType(root, "left");
		}
		else if(dragonBook_getBalanceFactor(root->right)<=0){
			return dragonBook_rotationType(root, "left");
		}
	}
	else if(balanceFactor>1){
		//right rotation
		if(dragonBook_getBalanceFactor(root->left)<0){
			root->left = dragonBook_rotationType(root->left, "left");
			return dragonBook_rotationType(root,"right");
		}
		else if(dragonBook_getBalanceFactor(root->left)>=0){
			return dragonBook_rotationType(root,"right");
		}
	}
	return root;
}

// create node for AVL Tree
struct dragonBook_Dragon* dragonBook_createDragon(char *name, int species, double minHeight, double maxHeight, struct dragonBook_List *eHead,struct dragonBook_List * rHead , struct dragonBook_List *wHead){
	struct dragonBook_Dragon *newDragon = (struct dragonBook_Dragon*) malloc(sizeof(dragonBook_Dragon));
	strcpy(newDragon->name, name);
	newDragon->species = species;
	newDragon->maxSize = maxHeight;
	newDragon->minSize = minHeight;
	newDragon->eHead = eHead;
	newDragon->rHead = rHead;
	newDragon->wHead = wHead;
	newDragon->height = 1;
	newDragon->biome = 0;
	newDragon->left = newDragon->right = NULL;
	return newDragon;
}

// insert Node to AVL Tree
struct dragonBook_Dragon *dragonBook_insertDragon(struct dragonBook_Dragon* root, char *name, int species, double minHeight, double maxHeight, struct dragonBook_List *eHead, struct dragonBook_List * rHead , struct dragonBook_List *wHead){
	if(!root){
		return dragonBook_createDragon(name, species, minHeight, maxHeight, eHead, rHead, wHead);
	}
	else if(strcmp(root->name, name)<0){
		root->left = dragonBook_insertDragon(root->left, name, species, minHeight, maxHeight, eHead, rHead, wHead);
	}
	else if(strcmp(root->name, name)>0){
		root->right = dragonBook_insertDragon(root->right, name, species, minHeight, maxHeight, eHead, rHead, wHead);
	}
	return dragonBook_rotation(root);
}

// get replacement for delete in AVL TREE
struct dragonBook_Dragon *dragonBook_predecessor(struct dragonBook_Dragon *root){
	struct dragonBook_Dragon *curr = root;
	while(curr->right){
		curr = curr->right;
	}
	return curr;
}

// remove node from AVL Tree
struct dragonBook_Dragon *dragonBook_deleteDragon(struct dragonBook_Dragon *root, char *name){
	if(!root){
		return root;
	}
	else if(strcmp(root->name, name)<0){
		root->left = dragonBook_deleteDragon(root->left, name);
	}
	else if(strcmp(root->name, name)>0){
		root->right = dragonBook_deleteDragon(root->right, name);
	}
	else{
		struct dragonBook_Dragon *temp;
		if(!root->left || !root->right){
			if(root->left){
				temp = root->left;
			}
			else{
				temp = root->right;
			}
			if(!temp){
				temp = root;
				root = NULL;
			}
			else{
				*root = *temp;
				free(temp);
			}
		}
		else{
			temp = dragonBook_predecessor(root->left);
			strcpy(root->name,temp->name);
			root->species = temp->species;
			root->maxSize = temp->maxSize;
			root->minSize = temp->minSize;
			root->eHead = temp->eHead;
			root->rHead = temp->rHead;
			root->wHead = temp->wHead;
			root->biome = temp->biome;
			root->left = dragonBook_deleteDragon(root->left, temp->name);
		}
		if(root){
			return dragonBook_rotation(root);
		}
		else return root;
	}
}

// FILE PROCESSING

// 1. Initialize AVL Tree by reading file
struct dragonBook_Dragon* dragonBook_init(struct dragonBook_Dragon *root){
	dragonBook_NumDragon = 0;
	FILE *fDragon = fopen(".\\CORE TRAINING\\Dragon Book\\monsterList.txt", "r");
	char name[255], element[255], weakness[255], resistance[255];
	int species;
	double maxS,minS;
	while(fscanf(fDragon,"%[^#]#%d#%[^#]#%[^#]#%[^#]#%lf#%lf\n",name, &species, element, weakness, resistance, &minS, &maxS)!=EOF){
		// convert string into List
		struct dragonBook_List *eHead = NULL, *rHead = NULL,*wHead = NULL;
		int lenE = strlen(element), lenR = strlen(resistance), lenW = strlen(weakness);
		for(int i=0;i<lenE;++i){
			if(element[i]>='1' && element[i]<='5'){
				eHead = dragonBook_pushList(eHead,element[i]-'0');
			}
		}
		for(int i=0;i<lenR;++i){
			if(resistance[i]>='1' && resistance[i]<='5'){
				rHead = dragonBook_pushList(rHead, resistance[i]-'0');
			}
		}
		for(int i=0;i<lenW;++i){
			if(weakness[i]>='1' && weakness[i]<='5'){
				wHead = dragonBook_pushList(wHead, weakness[i]-'0');
			}
		}
		// push data into AVL Tree
		root = dragonBook_insertDragon(root, name, species-1, minS, maxS, eHead, rHead, wHead);
		dragonBook_NumDragon++;
	}	
	fclose(fDragon);
	return root;
}

// load data from AVL Tree to file when closing book
void dragonBook_loadData(struct dragonBook_Dragon *root){
	if(!root){
		return;
	}
	dragonBook_loadData(root->left);
	// convert List into string
	char elements[255]="", resistance[255]="", weakness[255]="";
	struct dragonBook_List *e = root->eHead;
	if(!e){
		strcat(elements, "0");
	}
	else{
		while(e){
			char str[10];
			sprintf(str, "%d", e->element);
			strcat(elements,(const char*)str);
			e = e->next;
			if(e){
				strcat(elements, ",");
			}
		}
	}
	struct dragonBook_List *w = root->wHead;
	if(!w){
		strcat(weakness, "0");
	}
	else{
		while(w){
			char str[10];
			sprintf(str, "%d", w->element);
			strcat(weakness,(const char*)str);
			w = w->next;
			if(w){
				strcat(weakness, ",");
			}
		}
	}
	struct dragonBook_List *r = root->rHead;
	if(!r){
		strcat(resistance, "0");
	}
	else{
		while(r){
			char str[10];
			sprintf(str, "%d", r->element);
			strcat(resistance,(const char*)str);
			r = r->next;
			if(r){
				strcat(resistance, ",");
			}
		}
	}
	// append to file
	FILE *fDragon = fopen(".\\CORE TRAINING\\Dragon Book\\monsterList.txt", "a");
	fprintf(fDragon, "%s#%d#%s#%s#%s#%.2lf#%.2lf\n", root->name, root->species+1, elements,weakness, resistance,root->minSize, root->maxSize);
	fclose(fDragon);
	dragonBook_loadData(root->right);
}

// MENU FUNCTIONS

// 1. Add Dragon

// - Find Dragon By Name - returns the node 
struct dragonBook_Dragon* dragonBook_findDragonByName(struct dragonBook_Dragon *root, char *name){
	if(!root){
		return NULL;
	}
	else if(strcmp(root->name, name)<0){
		return dragonBook_findDragonByName(root->left, name);
	}
	else if(strcmp(root->name, name)>0){
		return dragonBook_findDragonByName(root->right, name);
	}
	return root;
}

// - Driver Function to add Dragon into the AVL Tree
struct dragonBook_Dragon *dragonBook_addDragon(struct dragonBook_Dragon *root){
	// push
	char name[255];
	bool addFlag = true;
	int start = 0;
	printf("\n");
	do{
		addFlag = true;
		start++;
		printf(" Insert Dragon's Name [3-25 characters | Case Sensitive | Unique][cancel to exit]: ");
		scanf("%[^\n]", name);
		getchar();
		if(strcmpi(name, "cancel")==0){
			return root;
		}
		int len = strlen(name);
		if(len<3|| len>25){
			printf("  Must be between 3 - 25 characters!\n");
			addFlag = false;
		}
		struct dragonBook_Dragon *find =  dragonBook_findDragonByName(root, name);
		if(find && strcmp(find->name, name)==0){
			printf("  Must be Unique!\n");
			addFlag = false;
		}
	}while(!addFlag);
	int pos = start+2, index = 1, species, curr = pos+1;
	dragonBook_gotoXY(2,pos+1);
	printf("-> ");
	addFlag = false;
	while(!addFlag){
		dragonBook_gotoXY(2, pos);
		printf(" Select Species:");
		for(int i=0;i<7;++i){
			dragonBook_gotoXY(5, pos+1+i);
			printf("%s", dragonBook_SPECIES[i]);
		}
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && curr!=pos+1){
			dragonBook_gotoXY(2, curr);
			printf("   ");
			curr--;
			dragonBook_gotoXY(2, curr);
			printf("-> ");
			index--;
			continue;
		}
		if(GetAsyncKeyState(VK_DOWN) && curr!=pos+7){
			dragonBook_gotoXY(2, curr);
			printf("   ");
			curr++;
			dragonBook_gotoXY(2, curr);
			printf("-> ");
			index++;
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN)){
			addFlag = true;
			species = index-1;
			dragonBook_gotoXY(0,pos+9);
		}
	}
	index = 1, curr = pos+1;
	dragonBook_gotoXY(27, pos+1);
	printf("->");
	addFlag = false;
	bool eFlag[5];
	for(int i=0;i<5;++i){
		eFlag[i] = false;
	}
	while(!addFlag){
		dragonBook_gotoXY(27, pos);
		printf(" Select Element:");
		for(int i=0;i<5;++i){
			dragonBook_gotoXY(32, pos+1+i);
			printf("%s", dragonBook_ELEMENTS[i]);
			int len = strlen(dragonBook_ELEMENTS[i]);
			if(eFlag[i]){
				dragonBook_gotoXY(32+len, pos+1+i);
				printf(" *");
			}
			else{
				dragonBook_gotoXY(32+len, pos+1+i);
				printf("  ");
			}
		}
		dragonBook_gotoXY(32, pos+6);
		printf("End");
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && curr!=pos+1){
			dragonBook_gotoXY(27, curr);
			printf("   ");
			curr--;
			dragonBook_gotoXY(27, curr);
			printf("-> ");
			index--;
			continue;
		}
		if(GetAsyncKeyState(VK_DOWN) && curr!=pos+6){
			dragonBook_gotoXY(27, curr);
			printf("   ");
			curr++;
			dragonBook_gotoXY(27, curr);
			printf("-> ");
			index++;
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN)){
			if(curr==pos+6){
				addFlag = true;
			}
			else{
				if(eFlag[index-1]){
					eFlag[index-1] = false;	
				}
				else eFlag[index-1] = true;
			}
		}
	}
	index = 1, curr = pos+1;
	dragonBook_gotoXY(47, pos+1);
	printf("->");
	addFlag = false;
	bool wFlag[5];
	for(int i=0;i<5;++i){
		wFlag[i] = false;
	}
	while(!addFlag){
		dragonBook_gotoXY(47, pos);
		printf(" Select Weakness:");
		for(int i=0;i<5;++i){
			dragonBook_gotoXY(52, pos+1+i);
			printf("%s", dragonBook_ELEMENTS[i]);
			int len = strlen(dragonBook_ELEMENTS[i]);
			if(wFlag[i]){
				dragonBook_gotoXY(52+len, pos+1+i);
				printf(" *");
			}
			else{
				dragonBook_gotoXY(52+len, pos+1+i);
				printf("  ");
			}
		}
		dragonBook_gotoXY(52, pos+6);
		printf("End");
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && curr!=pos+1){
			dragonBook_gotoXY(47, curr);
			printf("   ");
			curr--;
			dragonBook_gotoXY(47, curr);
			printf("-> ");
			index--;
			continue;
		}
		if(GetAsyncKeyState(VK_DOWN) && curr!=pos+6){
			dragonBook_gotoXY(47, curr);
			printf("   ");
			curr++;
			dragonBook_gotoXY(47, curr);
			printf("-> ");
			index++;
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN)){
			if(curr==pos+6){
				addFlag = true;
			}
			else{
				if(wFlag[index-1]){
					wFlag[index-1] = false;	
				}
				else wFlag[index-1] = true;
			}
		}
	}
	index = 1, curr = pos+1;
	dragonBook_gotoXY(67, pos+1);
	printf("->");
	addFlag = false;
	bool rFlag[5];
	for(int i=0;i<5;++i){
		rFlag[i] = false;
	}
	while(!addFlag){
		dragonBook_gotoXY(67, pos);
		printf(" Select Resistance:");
		for(int i=0;i<5;++i){
			dragonBook_gotoXY(72, pos+1+i);
			printf("%s", dragonBook_ELEMENTS[i]);
			int len = strlen(dragonBook_ELEMENTS[i]);
			if(rFlag[i]){
				dragonBook_gotoXY(72+len, pos+1+i);
				printf(" *");
			}
			else{
				dragonBook_gotoXY(72+len, pos+1+i);
				printf("  ");
			}
		}
		dragonBook_gotoXY(72, pos+6);
		printf("End");
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && curr!=pos+1){
			dragonBook_gotoXY(67, curr);
			printf("   ");
			curr--;
			dragonBook_gotoXY(67, curr);
			printf("-> ");
			index--;
			continue;
		}
		if(GetAsyncKeyState(VK_DOWN) && curr!=pos+6){
			dragonBook_gotoXY(67, curr);
			printf("   ");
			curr++;
			dragonBook_gotoXY(67, curr);
			printf("-> ");
			index++;
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN)){
			if(curr==pos+6){
				addFlag = true;
			}
			else{
				if(rFlag[index-1]){
					rFlag[index-1] = false;	
				}
				else rFlag[index-1] = true;
			}
		}
	}
	dragonBook_gotoXY(0, pos+9);
	addFlag = true;
	double minS, maxS;
	do{
		addFlag = true;
		printf(" Enter Dragon Min Size [>=50  & <100000][-1 to cancel]: ");
		scanf("%lf", &minS);
		getchar();
		if(minS==-1){
			return root;
		}
		if((int)minS<50 || (int)minS>100000){
			addFlag = 0;
			printf("  Minimum Size must be between 50 - 100000!\n");
		}
	}while(!addFlag);
	do{
		addFlag = true;
		printf(" Enter Dragon Max Size [>=Min Size  & <100000][-1 to cancel]: ");
		scanf("%lf", &maxS);
		getchar();
		if(maxS==-1){
			return root;
		}
		if((int)maxS<minS || (int)maxS>100000){
			addFlag = 0;
			printf("  Maximum Size must be between Min Size - 100000!\n");
		}
	}while(!addFlag);
	struct dragonBook_List *eHead = NULL, *rHead = NULL,*wHead = NULL;
	for(int i=0;i<5;++i){
		if(eFlag[i]){
			eHead = dragonBook_pushList(eHead,i+1);
		}
		if(rFlag[i]){
			rHead = dragonBook_pushList(rHead, i+1);
		}
		if(wFlag[i]){
			wHead = dragonBook_pushList(wHead, i+1);
		}
	}
	root = dragonBook_insertDragon(root, name, species, minS, maxS, eHead, rHead, wHead);
	dragonBook_NumDragon++;
	printf(" %s has been added to the book!\n\n", name);
	printf(" Press enter to continue..");
	getchar();
	return root;
}

// Helper struct for display
struct dragonBook_Helper{
	char name[255], elements[255], resistance[255], weakness[255];
	int species, biome;
	bool removable;
	double minSize, maxSize;
};

// load data from AVL Tree into the Helper array
void dragonBook_insertHelper(struct dragonBook_Dragon *root, struct dragonBook_Helper *tempData, bool *inserted, const char *purpose, int biome){
	if(!root){
		return;
	}
	dragonBook_insertHelper(root->left, tempData, inserted, purpose, biome);
	if(!(strcmp(purpose,"adventure")==0 && root->biome!=biome)){
		int index = 0;
		for(int i=0;i<dragonBook_NumDragon;++i){
			if(!inserted[i]){
				index = i;
				break;
			}
		}
		char elements[255]="", resistance[255]="", weakness[255]="";
		struct dragonBook_List *e = root->eHead;
		if(!e){
			strcat(elements, "0");
		}
		else{
			while(e){
				char str[10];
				sprintf(str, "%d", e->element);
				strcat(elements,(const char*)str);
				e = e->next;
				if(e){
					strcat(elements, ",");
				}
			}
		}
		struct dragonBook_List *w = root->wHead;
		if(!w){
			strcat(weakness, "0");
		}
		else{
			while(w){
				char str[10];
				sprintf(str, "%d", w->element);
				strcat(weakness,(const char*)str);
				w = w->next;
				if(w){
					strcat(weakness, ",");
				}
			}
		}
		struct dragonBook_List *r = root->rHead;
		if(!r){
			strcat(resistance, "0");
		}
		else{
			while(r){
				char str[10];
				sprintf(str, "%d", r->element);
				strcat(resistance,(const char*)str);
				r = r->next;
				if(r){
					strcat(resistance, ",");
				}
			}
		}
		strcpy(tempData[index].elements, elements);
		strcpy(tempData[index].weakness, weakness);
		strcpy(tempData[index].resistance, resistance);
		strcpy(tempData[index].name, root->name);
		tempData[index].species = root->species;
		tempData[index].minSize = root->minSize;
		tempData[index].maxSize = root->maxSize;
		tempData[index].biome = root->biome;
		// different set of actions depending on the purpose
		if(strcmp(purpose,"addBiome")==0 && root->biome!=0){
			tempData[index].removable = false;
		}
		else if(strcmp(purpose,"deleteBiome")==0 && root->biome != biome){
			tempData[index].removable = false;
		}
		else tempData[index].removable = true;
		inserted[index] = true;
	}
	dragonBook_insertHelper(root->right, tempData, inserted, purpose, biome);
}

// Merge Sort to sort the Helper array lexicographically 
void dragonBook_merge(struct dragonBook_Helper *arr, int left, int right){
	int mid = (left+right)/2;
	int start = left, next = mid+1, index = 0;
	struct dragonBook_Helper temp[right-left+1];
	while(start<=mid && next<=right){
		if(strcmp(arr[start].name, arr[next].name)<0){
			temp[index] = arr[start];
			start++;
		}
		else{
			temp[index] = arr[next];
			next++;
		}
		index++;
	}
	while(start<=mid){
		temp[index] = arr[start];
		start++, index++;
	}
	while(next<=right){
		temp[index] = arr[next];
		next++, index++;
	}
	for(int i=0;i<index;++i){
		arr[left+i] = temp[i];
	}
}

// Driver function for merge sort
void dragonBook_mergeSort(struct dragonBook_Helper *arr, int left, int right){
	if(left==right){
		return;
	}
	int mid = (left+right)/2;
	dragonBook_mergeSort(arr, left, mid);
	dragonBook_mergeSort(arr, mid+1, right);
	dragonBook_merge(arr, left, right);
}

// 2. Remove Dragon

// Driver function to remove Dragon
struct dragonBook_Dragon *dragonBook_removeDragon(struct dragonBook_Dragon *root){
	//pop
	if(!root){
		printf(" There are no Dragon(s) in the book!\n");
		printf("\n Press enter to continue..");
		getchar();
	}
	else{
		struct dragonBook_Helper tempData[dragonBook_NumDragon];
		bool inserted[dragonBook_NumDragon];
		for(int i=0;i<dragonBook_NumDragon;++i){
			inserted[i] = false;
		}
		dragonBook_insertHelper(root, tempData, inserted, "else", 0);
		dragonBook_mergeSort(tempData, 0, dragonBook_NumDragon-1);
		printf(" << Choose the Dragon that you want to remove from the book >>\n");
		printf("    +================================+======================+============+============+============+==========+==========+===========+\n");
		printf("    | Name                           | Species              | Element    | Weakness   | Resistance | Min Size | Max Size | Removable |\n");
		printf("    +================================+======================+============+============+============+==========+==========+===========+\n");
		dragonBook_gotoXY(1,4);
		printf("->");
		int currPos = 0; // 0 - numDragon
		int currHeight = 4; // constant height
		int pos = 4; // position of arrow
		int choice = 4; // Dragon
		int deleted = 0;
		bool running = true;
		while(running){
			int h = 0;
			for(int i=0;i<10;++i){		
				if(currPos+i<dragonBook_NumDragon && currPos+i>=0 ){
					h++;
					dragonBook_gotoXY(4, currHeight+i);
					printf("| %-30s | %-20s | %-10s | %-10s | %-10s | %-8.2lf | %-8.2lf |", tempData[currPos+i].name, dragonBook_SPECIES[tempData[currPos+i].species], tempData[currPos+i].elements, tempData[currPos+i].weakness, tempData[currPos+i].resistance, tempData[currPos+i].minSize, tempData[currPos+i].maxSize);
					if(!tempData[currPos+i].removable){
						printf(" False     |");
					}
					else printf(" True      |");
				}
			}
			dragonBook_gotoXY(4, currHeight+h);
			printf("+================================+======================+============+============+============+==========+==========+===========+");
			dragonBook_gotoXY(2, currHeight+2+h);
			printf("Press enter to select , arrow up or down to move, escape to return");
			system("pause>nul");
			if(GetAsyncKeyState(VK_UP) && pos!=currHeight){
				dragonBook_gotoXY(1, pos);
				printf("  ");
				pos--;
				choice--;
				dragonBook_gotoXY(1, pos);
				printf("->");
				continue;
			}
			else if(GetAsyncKeyState(VK_UP) && currPos>0){
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0 && tempData[currPos+i].minSize!=-1){
						dragonBook_gotoXY(4, currHeight+i);
						printf("  ");
					}
				}
				currPos--;
				choice--;
				continue;
			}
			if(GetAsyncKeyState(VK_DOWN) && pos!=currHeight+h-1){
				dragonBook_gotoXY(1, pos);
				printf("   ");
				pos++;
				dragonBook_gotoXY(1, pos);
				printf("-> ");
				choice++;
				continue;
			}
			else if(GetAsyncKeyState(VK_DOWN) && currPos+10<dragonBook_NumDragon){
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0 && tempData[currPos+i].minSize!=-1){
						dragonBook_gotoXY(4, currHeight+i);
						printf(" ");
					}
				}
				choice++;
				currPos++;
				continue;
			}
			if(GetAsyncKeyState(VK_RETURN) && tempData[choice-4].removable){
				char agreement;
				bool flag = false;
				do{
					flag = false;
					dragonBook_gotoXY(2, currHeight+4+h);
					printf("Are you sure you want to remove %s? [y/n]: ", tempData[choice-4].name);
					agreement = getch();
					if(agreement=='y' || agreement=='Y' || agreement=='n' || agreement=='N'){
						flag = true;
					}
				}while(!flag);
				if(agreement=='y'|| agreement=='Y'){
					root = dragonBook_deleteDragon(root, tempData[choice-4].name);
					deleted++;
					dragonBook_gotoXY(2, currHeight+6+h);
					printf("%s has been removed from the book!", tempData[choice-4].name);
					tempData[choice-4].removable = false;
					for(int i=0;i<10;++i){		
						if(currPos+i<dragonBook_NumDragon && currPos+i>=0){
							dragonBook_gotoXY(4, currHeight+i);
							printf(" ");
						}
					}	
				}
				dragonBook_gotoXY(2, currHeight+4+h);
				printf("                                                                            ");
				dragonBook_gotoXY(2, currHeight+6+h);
				printf("                                                                            ");
			}
			if(GetAsyncKeyState(VK_ESCAPE)){
				running = false;
				dragonBook_gotoXY(2, currHeight+4+h);
			}
			
		}
		dragonBook_NumDragon-=deleted;
		printf("Press enter to continue..");
		getchar();
	}
	return root;
}

// 3. Manage Biome

// - Add Dragon to Biome 
struct dragonBook_Dragon *dragonBook_addToBiome(struct dragonBook_Dragon* root, int idx, int row){
	struct dragonBook_Helper tempData[dragonBook_NumDragon];
	bool inserted[dragonBook_NumDragon];
	for(int i=0;i<dragonBook_NumDragon;++i){
		inserted[i] = false;
	}
	dragonBook_insertHelper(root, tempData, inserted, "addBiome", 0);
	dragonBook_mergeSort(tempData, 0, dragonBook_NumDragon-1);
	bool running = true;
	while(running){
		dragonBook_gotoXY(50,row);
		printf(" << Choose the Dragon that you want to add to the biome >>\n");
		dragonBook_gotoXY(47,row+1);
		printf("   +================================+======================+============+============+============+==========+==========+===========+\n");
		dragonBook_gotoXY(47,row+2);
		printf("   | Name                           | Species              | Element    | Weakness   | Resistance | Min Size | Max Size | Added     |\n");
		dragonBook_gotoXY(47,row+3);
		printf("   +================================+======================+============+============+============+==========+==========+===========+\n");
		dragonBook_gotoXY(47,row+4);
		printf("->");
		int currPos = 0; // 0 - numDragon
		int currHeight = row+4; // constant height
		int pos = row+4; // position of arrow
		int choice = row+4; // Dragon
		int deleted = 0;
		bool running = true;
		while(running){
			int h = 0;
			for(int i=0;i<10;++i){		
				if(currPos+i<dragonBook_NumDragon && currPos+i>=0){
					h++;
					dragonBook_gotoXY(50, currHeight+i);
					printf("| %-30s | %-20s | %-10s | %-10s | %-10s | %-8.2lf | %-8.2lf |", tempData[currPos+i].name, dragonBook_SPECIES[tempData[currPos+i].species], tempData[currPos+i].elements, tempData[currPos+i].weakness, tempData[currPos+i].resistance, tempData[currPos+i].minSize, tempData[currPos+i].maxSize);
					if(!tempData[currPos+i].removable){
						printf(" Added     |");
					}
					else printf(" Not Added |");
				}
			}
			dragonBook_gotoXY(50, currHeight+h);
			printf("+================================+======================+============+============+============+==========+==========+===========+");
			dragonBook_gotoXY(47, currHeight+2+h);
			printf("Press enter to select , arrow up or down to move, escape to return");
			system("pause>nul");
			if(GetAsyncKeyState(VK_UP) && pos!=currHeight){
				dragonBook_gotoXY(47, pos);
				printf("  ");
				pos--;
				choice--;
				dragonBook_gotoXY(47, pos);
				printf("->");
				continue;
			}
			else if(GetAsyncKeyState(VK_UP) && currPos>0){
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0 && tempData[currPos+i].minSize!=-1){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}
				currPos--;
				choice--;
				continue;
			}
			if(GetAsyncKeyState(VK_DOWN) && pos!=currHeight+h-1){
				dragonBook_gotoXY(47, pos);
				printf("   ");
				pos++;
				dragonBook_gotoXY(47, pos);
				printf("-> ");
				choice++;
				continue;
			}
			else if(GetAsyncKeyState(VK_DOWN) && currPos+10<dragonBook_NumDragon){
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0 && tempData[currPos+i].minSize!=-1){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}
				choice++;
				currPos++;
				continue;
			}
			if(GetAsyncKeyState(VK_RETURN) && tempData[choice-4-row].removable){
				struct dragonBook_Dragon *curr = dragonBook_findDragonByName(root, tempData[choice-row-4].name);
				curr->biome = idx;
				dragonBook_gotoXY(47, currHeight+6+h);
				printf("%s has been added to the biome!", tempData[choice-row-4].name);
				tempData[choice-row-4].removable = false;
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}	
				dragonBook_gotoXY(47, currHeight+6+h);
				printf("                                                                            ");
			}
			if(GetAsyncKeyState(VK_ESCAPE)){
				running = false;
				dragonBook_gotoXY(50,row);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+1);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+2);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+3);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+4);
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}	
				dragonBook_gotoXY(50, currHeight+h);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47, currHeight+2+h);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47, pos);
				printf("                                                                                                                                       ");
				return root;
			}
		}	
	}	
	return root;
}

// - remove Dragon from biome
struct dragonBook_Dragon *dragonBook_removeFromBiome(struct dragonBook_Dragon *root, int idx, int row){
	struct dragonBook_Helper tempData[dragonBook_NumDragon];
	bool inserted[dragonBook_NumDragon];
	for(int i=0;i<dragonBook_NumDragon;++i){
		inserted[i] = false;
	}
	dragonBook_insertHelper(root, tempData, inserted, "deleteBiome", idx);
	dragonBook_mergeSort(tempData, 0, dragonBook_NumDragon-1);
	bool running = false;
	for(int i=0;i<dragonBook_NumDragon;++i){
		if(tempData[i].removable==true){
			running = true;
		}
	}
	if(!running){
		dragonBook_gotoXY(50,row);
		printf(" There are no Dragons in here!");
		dragonBook_gotoXY(50, row+2);
		printf(" Press enter to continue..");
		getchar();
		dragonBook_gotoXY(50,row);
		printf("                                                                                                                                       ");
		dragonBook_gotoXY(50,row+2);
		printf("                                                                                                                                       ");
							
	}
	while(running){
		dragonBook_gotoXY(50,row);
		printf(" << Choose the Dragon that you want to remove from the biome >>\n");
		dragonBook_gotoXY(47,row+1);
		printf("   +================================+======================+============+============+============+==========+==========+===========+\n");
		dragonBook_gotoXY(47,row+2);
		printf("   | Name                           | Species              | Element    | Weakness   | Resistance | Min Size | Max Size | Owned     |\n");
		dragonBook_gotoXY(47,row+3);
		printf("   +================================+======================+============+============+============+==========+==========+===========+\n");
		dragonBook_gotoXY(47,row+4);
		printf("->");
		int currPos = 0; // 0 - numdragon
		int currHeight = row+4; // constant height
		int pos = row+4; // position of arrow
		int choice = row+4; // Dragon
		int deleted = 0;
		bool running = true;
		while(running){
			int h = 0;
			for(int i=0;i<10;++i){		
				if(currPos+i<dragonBook_NumDragon && currPos+i>=0){
					h++;
					dragonBook_gotoXY(50, currHeight+i);
					printf("| %-30s | %-20s | %-10s | %-10s | %-10s | %-8.2lf | %-8.2lf |", tempData[currPos+i].name, dragonBook_SPECIES[tempData[currPos+i].species], tempData[currPos+i].elements, tempData[currPos+i].weakness, tempData[currPos+i].resistance, tempData[currPos+i].minSize, tempData[currPos+i].maxSize);
					if(!tempData[currPos+i].removable){
						printf(" Not Owned |");
					}
					else printf(" Owned     |");
				}
			}
			dragonBook_gotoXY(50, currHeight+h);
			printf("+================================+======================+============+============+============+==========+==========+===========+");
			dragonBook_gotoXY(47, currHeight+2+h);
			printf("Press enter to select , arrow up or down to move, escape to return");
			system("pause>nul");
			if(GetAsyncKeyState(VK_UP) && pos!=currHeight){
				dragonBook_gotoXY(47, pos);
				printf("  ");
				pos--;
				choice--;
				dragonBook_gotoXY(47, pos);
				printf("->");
				continue;
			}
			else if(GetAsyncKeyState(VK_UP) && currPos>0){
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0 && tempData[currPos+i].minSize!=-1){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}
				currPos--;
				choice--;
				continue;
			}
			if(GetAsyncKeyState(VK_DOWN) && pos!=currHeight+h-1){
				dragonBook_gotoXY(47, pos);
				printf("   ");
				pos++;
				dragonBook_gotoXY(47, pos);
				printf("-> ");
				choice++;
				continue;
			}
			else if(GetAsyncKeyState(VK_DOWN) && currPos+10<dragonBook_NumDragon){
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0 && tempData[currPos+i].minSize!=-1){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}
				choice++;
				currPos++;
				continue;
			}
			if(GetAsyncKeyState(VK_RETURN) && tempData[choice-4-row].removable){
				struct dragonBook_Dragon *curr = dragonBook_findDragonByName(root, tempData[choice-row-4].name);
				curr->biome = 0;
				dragonBook_gotoXY(47, currHeight+6+h);
				printf("%s has been removed from the biome!", tempData[choice-row-4].name);
				tempData[choice-row-4].removable = false;
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}	
				dragonBook_gotoXY(47, currHeight+6+h);
				printf("                                                                            ");
			}
			if(GetAsyncKeyState(VK_ESCAPE)){
				running = false;
				dragonBook_gotoXY(50,row);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+1);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+2);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+3);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47,row+4);
				for(int i=0;i<10;++i){		
					if(currPos+i<dragonBook_NumDragon && currPos+i>=0){
						dragonBook_gotoXY(50, currHeight+i);
						printf("                                                                                                                                       ");
					}
				}	
				dragonBook_gotoXY(50, currHeight+h);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47, currHeight+2+h);
				printf("                                                                                                                                       ");
				dragonBook_gotoXY(47, pos);
				printf("                                                                                                                                       ");
				return root;
			}
		}	
	}	
	return root;
}

// - Driver function to manage biome
void dragonBook_manageBiome(struct dragonBook_Dragon *root){
	//push and pop to biome
	if(!root){
		printf(" There are no Dragon(s) in the book!\n");
		printf("\n Press enter to continue..");
		getchar();
	}
	else{
		int pos = 2, choice = 1,curr = 3;
		bool running = true;
		dragonBook_gotoXY(2, 3);
		printf("->");
		while(running){	
			dragonBook_gotoXY(2, 2);
			printf(" Select Biome to edit:\n");
			for(int i=0;i<7;++i){
				dragonBook_gotoXY(5, pos+i+1);
				printf("%s", dragonBook_BIOME[i]);
			}
			dragonBook_gotoXY(5, pos+8);
			printf("Return");
			system("pause>nul");
			if(GetAsyncKeyState(VK_UP) && curr!=3){
				dragonBook_gotoXY(2, curr);
				printf("   ");
				curr--, choice--;
				dragonBook_gotoXY(2, curr);
				printf("->");
				continue;	
			}
			if(GetAsyncKeyState(VK_DOWN) && curr!=10){
				dragonBook_gotoXY(2, curr);
				printf("   ");
				curr++, choice++;
				dragonBook_gotoXY(2, curr);
				printf("->");
				continue;
			}
			if(GetAsyncKeyState(VK_RETURN)){
				if(choice>=1 && choice<=7){
					dragonBook_gotoXY(24, curr);
					printf("*");
					int col = 30, choice2 = 1, curr2 = curr+1;
					bool edit = true;
					dragonBook_gotoXY(col, curr+1);
					printf("->");
					while(edit){
						dragonBook_gotoXY(col, curr);
						printf("Select Activity:");
						dragonBook_gotoXY(col+3, curr+1);
						printf("Add Monster");
						dragonBook_gotoXY(col+3, curr+2);
						printf("Remove Monster");
						dragonBook_gotoXY(col+3, curr+3);
						printf("Return");
						system("pause>nul");
						if(GetAsyncKeyState(VK_UP) && curr2!=curr+1){
							dragonBook_gotoXY(col, curr2);
							printf("   ");
							curr2--, choice2--;
							dragonBook_gotoXY(col, curr2);
							printf("->");
							continue;	
						}
						if(GetAsyncKeyState(VK_DOWN) && curr2!=curr+3){
							dragonBook_gotoXY(col, curr2);
							printf("   ");
							curr2++, choice2++;
							dragonBook_gotoXY(col, curr2);
							printf("->");
							continue;
						}
						if(GetAsyncKeyState(VK_RETURN)){
							switch(choice2){
								case 1:
									root = dragonBook_addToBiome(root, choice, curr2);
									break;
								case 2:
									root = dragonBook_removeFromBiome(root, choice, curr2);
									break;
								case 3:
									dragonBook_gotoXY(col, curr);
									printf("                    ");
									dragonBook_gotoXY(col+3, curr+1);
									printf("                    ");
									dragonBook_gotoXY(col+3, curr+2);
									printf("                    ");
									dragonBook_gotoXY(col+3, curr+3);
									printf("                    ");
									dragonBook_gotoXY(col, curr2);
									printf("                    ");
									edit = false;
									dragonBook_gotoXY(24, curr);
									printf(" ");
									break;
							}
						}
					}
				}
				else{
					running = false;
				}
			}
		}
	}
}

// 4. MANAGE WORLD MENU (add Dragon, remove Dragon, manage Biome)
struct dragonBook_Dragon *dragonBook_manageWorld(struct dragonBook_Dragon *root){
	system("cls");
	bool picked = false;
	int pos = 7, choice= 1;
	while(!picked){      
		system("cls");
		dragonBook_logo();
		dragonBook_gotoXY(57,pos);
		printf("-> ");
		dragonBook_gotoXY(57, 12);
		printf("Arrow Up or Down to move selection...");
		dragonBook_gotoXY(57, 13);
		printf("Enter to select menu...");
		// make menu
		dragonBook_gotoXY(60, 7);
		printf("Add Dragon");
		dragonBook_gotoXY(60, 8);
		printf("Remove Dragon");
		dragonBook_gotoXY(60, 9);
		printf("Manage Biome");
		dragonBook_gotoXY(60,10);
		printf("Return");
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && pos!=7){
			dragonBook_gotoXY(57, pos);
			printf("   ");
			pos--;
			dragonBook_gotoXY(57, pos);
			printf("-> ");
			choice--;
			continue;
		}
		if(GetAsyncKeyState(VK_DOWN) && pos!=10){
			dragonBook_gotoXY(57, pos);
			printf("   ");
			pos++;
			dragonBook_gotoXY(57, pos);
			printf("-> ");
			choice++;
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN)){
			system("cls");
			dragonBook_gotoXY(0,0);
			switch(choice){
				case 1:
					root = dragonBook_addDragon(root);
					break;
				case 2:
					root = dragonBook_removeDragon(root);
					break;
				case 3:
					dragonBook_manageBiome(root);
					break;
				case 4:
					picked = true;
					break;
			}	
		}
	}
	system("cls");
	return root;
}

// START ADVENTURE MENU 

// - Calculate number of Dragon Species in the biome
void dragonBook_calcBiomeInhabitants(struct dragonBook_Dragon *root, int *ctr, int idx){
	if(!root){
		return;
	}
	dragonBook_calcBiomeInhabitants(root->left, ctr, idx);
	if(root->biome == idx){
		*ctr += 1;
	}
	dragonBook_calcBiomeInhabitants(root->right, ctr, idx);
}

int dragonBook_calcDragonIndex(int ctr){
	int n = floor(log10(ctr));
	srand(time(0));
	unsigned long long val = rand();
	srand(time(0));
	val = val<<(rand()%16);
	srand(time(0));
	val = val^rand();
	val%=10000;
	for(int i=0;i<n;++i){
		val = val*val;
		val = val / 10000; 
        val = val % 10000; 
	}
	return val%ctr;
}

// - Driver function to Start Adventure
struct dragonBook_Dragon *dragonBook_startAdventure(struct dragonBook_Dragon *root){
	system("cls");
	printf("\n         You're going on an adventure!\n");
	srand(time(0));
	int biomeIndex = rand()%7;
	printf("\n         You have arrived in %s Biome!!!\n\n", dragonBook_BIOME[biomeIndex]);
	int ctr = 0;
	dragonBook_calcBiomeInhabitants(root, &ctr, biomeIndex+1);
	if(ctr==0){
		printf("         There are no Dragon(s) here!\n");
	}
	else{
		struct dragonBook_Helper biomeDragons[ctr];
		bool inserted[ctr];
		for(int i=0;i<ctr;++i){
			inserted[i] = false;
		}
		dragonBook_insertHelper(root, biomeDragons, inserted, "adventure", biomeIndex+1);
		dragonBook_mergeSort(biomeDragons, 0, ctr-1);
		int idx = dragonBook_calcDragonIndex(ctr);
		srand(time(0));
		double size = biomeDragons[idx].minSize + (rand()%((int)(biomeDragons[idx].maxSize - biomeDragons[idx].minSize)));
		printf("         You found a %s (%.2lf cm)!\n", biomeDragons[idx].name, size);
		printf("         It\'s Species is %s.\n", dragonBook_SPECIES[biomeDragons[idx].species]);
		printf("         It\'s Element(s) is/are ");
		if(strcmp(biomeDragons[idx].elements, "0")==0){
			printf("None\n");
		}
		else{
			int lenE = strlen(biomeDragons[idx].elements);
			for(int i=0;i<lenE;++i){
				char val = biomeDragons[idx].elements[i];
				if(val>='1' && val<='5'){
					printf("%s", dragonBook_ELEMENTS[val-'0'-1]);
					if(i+1<lenE){
						printf(",");
					}
					printf(" ");
				}
				
			}
			printf("\n");
		}
		printf("         It\'s Weakness(es) is/are ");
		if(strcmp(biomeDragons[idx].weakness, "0")==0){
			printf("None\n");
		}
		else{
			int lenW = strlen(biomeDragons[idx].weakness);
			for(int i=0;i<lenW;++i){
				char val = biomeDragons[idx].weakness[i];
				if(val>='1' && val<='5'){
					printf("%s", dragonBook_ELEMENTS[val-'0'-1]);
					if(i+1<lenW){
						printf(",");
					}
					printf(" ");
				}
				
			}
			printf("\n");
		}
		printf("         It\'s Resistance(s) is/are ");
		if(strcmp(biomeDragons[idx].resistance, "0")==0){
			printf("None\n");
		}
		else{
			int lenR = strlen(biomeDragons[idx].resistance);
			for(int i=0;i<lenR;++i){
				char val = biomeDragons[idx].resistance[i];
				if(val>='1' && val<='5'){
					printf("%s", dragonBook_ELEMENTS[val-'0'-1]);
					if(i+1<lenR){
						printf(",");
					}
					printf(" ");
				}
			}
			printf("\n");
		}
	}
	printf("\n         Press enter to continue..");
	getchar();
	system("cls");
	return root;
}

// MAIN PROGRAM
void dragonBook_game(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const SMALL_RECT WinSize = {0,0,185,30};
    SetConsoleWindowInfo( hConsole, true, &WinSize);
	struct dragonBook_Dragon *handlerBook = NULL;
	handlerBook = dragonBook_init(handlerBook);
	bool picked = false;
	int pos = 7, choice= 1;
	while(!picked){ 
		system("cls");     
		dragonBook_logo();
		dragonBook_gotoXY(57,pos);
		printf("-> ");
		dragonBook_gotoXY(57, 11);
		printf("Arrow Up or Down to move selection...");
		dragonBook_gotoXY(57, 12);
		printf("Enter to select menu...");
		dragonBook_gotoXY(57,13);
		// make menu
		dragonBook_gotoXY(60, 7);
		printf("Manage World");
		dragonBook_gotoXY(60, 8);
		printf("Start Adventure");
		dragonBook_gotoXY(60, 9);
		printf("Close Book");
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && pos!=7){
			dragonBook_gotoXY(57, pos);
			printf("   ");
			pos--;
			dragonBook_gotoXY(57, pos);
			printf("-> ");
			choice--;
			continue;
		}
		if(GetAsyncKeyState(VK_DOWN) && pos!=9){
			dragonBook_gotoXY(57, pos);
			printf("   ");
			pos++;
			dragonBook_gotoXY(57, pos);
			printf("-> ");
			choice++;
			continue;
		}
		if(GetAsyncKeyState(VK_RETURN)){
			system("cls");
			dragonBook_gotoXY(0,0);
			switch(choice){
				case 1:
					handlerBook = dragonBook_manageWorld(handlerBook);
					break;
				case 2:
					handlerBook = dragonBook_startAdventure(handlerBook);
					break;
				case 3:
					FILE *fDragon = fopen(".\\CORE TRAINING\\Dragon Book\\monsterList.txt", "w");
					fclose(fDragon);
					dragonBook_loadData(handlerBook);
					picked = true;
					break;
			}	
		}
	}
	return;
}
