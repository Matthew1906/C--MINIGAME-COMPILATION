#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int petShop_SIZE = 120;

int petShop_counter = 0;

struct petShop_Product{
	char id[6], name[25], category[15], type[10];
	int price, quantity;
	struct petShop_Product *next;
}*petShop_hashTable[petShop_SIZE]={NULL};

int petShop_getHash(char *name){
	int total = 0, len = strlen(name);
	for(int i=0;i<len;++i){
		total+=name[i];
	}
	return total%petShop_SIZE;
}

struct petShop_Product *petShop_createProduct(char *id, char*name, char*category, char*type, int price, int qty){
	struct petShop_Product *newProduct = (struct petShop_Product *)malloc(sizeof(struct petShop_Product));
	strcpy(newProduct->id, id);
	strcpy(newProduct->name, name);
	strcpy(newProduct->category, category);
	strcpy(newProduct->type, type);
	newProduct->price = price;
	newProduct->quantity = qty;
	newProduct->next = NULL;
	return newProduct;
}

void petShop_push(char *id, char*name, char*category, char*type, int price, int qty){
	int index = petShop_getHash(name);
	struct petShop_Product *newProduct = petShop_createProduct(id,name,category,type,price,qty);
	if(!petShop_hashTable[index]){
		petShop_hashTable[index] = newProduct;
	}
	else{
		struct petShop_Product *curr = petShop_hashTable[index];
		while(curr->next){
			curr = curr->next;
		}
		curr->next = newProduct;
	}
}

bool petShop_pop(char *name){
	int index = petShop_getHash(name);
	if(!petShop_hashTable[index]){
		return false;
	}
	struct petShop_Product *curr = petShop_hashTable[index];
	if(strcmp(curr->name, name)==0){
		petShop_hashTable[index] = curr->next;
		free(curr);
		curr = NULL;
	}
	else{
		while(curr->next && strcmp(curr->next->name, name)!=0){
			curr = curr->next;
		}
		if(!curr->next){
			return false;
		}
		struct petShop_Product *temp = curr->next;
		curr->next = temp->next;
		free(temp);
		temp = NULL;
	}
	return true;
}

bool petShop_find(char *name){
	int index = petShop_getHash(name);
	if(!petShop_hashTable[index]){
		return false;
	}
	struct petShop_Product *curr = petShop_hashTable[index];
	if(strcmp(curr->name, name)==0){
		return true;
	}
	else{
		while(curr->next && strcmp(curr->next->name, name)!=0){
			curr = curr->next;
		}
		if(!curr->next){
			return false;
		}
		return true;
	}
}

void petShop_insertOrder(){
	system("cls");
	char id[6];
	sprintf(id, "OR%03d", ++petShop_counter);
	int addFlag = 1;
	char name[25];
	printf("\n\n");
	getchar();
	do{
		addFlag = 1;
		printf("    Product Name [Must be Unique] [5..20]: ");
		scanf("%[^\n]", name);
		getchar();
		int lenName = strlen(name);
		if(petShop_find(name)){
			printf("    Product Exists!\n");
			addFlag = 0;
		}
		else if(lenName<5 || lenName>20){
			printf("    Product Name length must be 5 - 20 characters!\n");
			addFlag = 0;
		}
	}while(addFlag == 0);
	char category[15];
	do{
		addFlag = 1;
		printf("    Product Category [Food | Treatment | Accessories] (Case Sensitive): ");
		scanf("%[^\n]", category);
		getchar();
		if(strcmp(category,"Food")!=0 && strcmp(category,"Treatment")!=0 && strcmp(category,"Accessories")!=0){
			printf("    Product Category must be between [Food | Treatment | Accessories]! (Case Sensitive)\n");
			addFlag = 0;
		}
	}while(addFlag == 0);
	char type[10];
	do{
		addFlag = 1;
		printf("    Product Age Type [Baby | Adult] (Case Insensitive): ");
		scanf("%[^\n]", type);
		getchar();
		if(strcmpi(type,"Baby")!=0 && strcmpi(type,"Adult")!=0){
			printf("    Product Age Type must be between [Baby | Adult]! (Case Insensitive)\n");
			addFlag = 0;
		}
	}while(addFlag == 0);
	int lenType = strlen(type);
	for(int i=0;i<lenType;++i){
		if(i==0 && type[i]>='a' && type[i]<='z'){
			type[i]+='A'-'a';
		}
		else if(i!=0 && type[i]>='A' && type[i]<='Z'){
			type[i]+='a'-'A';
		}
	}
	int price;
	do{
		addFlag = 1;
		printf("    Product Price [50..150]: $");
		scanf("%d", &price);
		getchar();
		if(price<50 || price>150){
			printf("    Product Price must be between 50 - 150!\n");
			addFlag = 0;
		}
	}while(addFlag == 0);
	int qty;
	do{
		addFlag = 1;
		printf("    Product Quantity [1..9]: ");
		scanf("%d", &qty);
		getchar();
		if(qty<1 || qty>9){
			printf("    Product Quantity must be between 1 - 9!\n");
			addFlag = 0;
		}
	}while(addFlag == 0);
	petShop_push(id, name, category, type, price, qty);
	printf("    Success Add Order!");
	getchar();
	return;
}

bool petShop_isEmpty(){
	for(int i=0;i<petShop_SIZE;++i){
		if(petShop_hashTable[i]){
			return false;
			break;
		}
	}
	return true;
}

void petShop_viewOrder(){
	system("cls");
	printf("\n\n");
	if(petShop_isEmpty()){
		printf("    No Order Yet.");
		getchar();
		getchar();
		return;
	}
	printf("    My Order\n");
	printf("    ===============================================================================\n");
	printf("    |  No   |         Name         |  Category   | Age Type |   Price  | Quantity |\n");
	printf("    ===============================================================================\n");
	for(int i=0;i<petShop_SIZE;++i){
		if(petShop_hashTable[i]){
			struct petShop_Product *curr = petShop_hashTable[i];
			while(curr){
				printf("    | %s | %-20s | %-11s | %-5s    | $%-3d     | $%-1d       |\n", curr->id, curr->name, curr->category, curr->type, curr->price, curr->quantity);
				curr = curr->next;
			}
		}
	}
	printf("    ===============================================================================\n");
	getchar();
	getchar();
}

void petShop_checkoutOrder(){
	system("cls");
	printf("\n\n");
	getchar();
	char toDelete[255];
	printf("    Input Product Name: ");
	scanf("%[^\n]", toDelete);
	getchar();
	bool deleted = petShop_pop(toDelete);
	if(deleted){
		printf("    Success Checkout %s!\n", toDelete);
	}
	else{
		printf("    %s not exist\n", toDelete);
	}
	getchar();
	getchar();
	return;
}

void petShop_game(){
	char menu;
	do{
		system("cls");
		printf("\n\n");
		printf("    Pet Shop\n");
		printf("    =================\n");
		printf("    1. Insert New Order\n");
		printf("    2. View My Order\n");
		printf("    3. Checkout My Order\n");
		printf("    0. Exit\n");
		printf("    Choice = ");
		menu = getchar();
		switch(menu-'0'){
			case 1:
				petShop_insertOrder();
				break;
			case 2:
				petShop_viewOrder();
				break;
			case 3:
				petShop_checkoutOrder();
				break;
		}
	}while(menu!='0');
	return;
}
