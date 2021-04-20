#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

const int bookShop_SIZE = 100;

struct bookShop_Book{
	char id[10];
	char name[25];
	char genre[25];
	char author[255];
	char publisher[25];
	int price;
	struct bookShop_Book *next;
}*bookShop_hashTable[bookShop_SIZE]={NULL};

int bookShop_getHash(char*id){
	int len = strlen(id), key = 0;
	for(int i=0;i<len;++i){
		key+=id[i];
	}
	return key%bookShop_SIZE;
}

struct bookShop_Book* bookShop_addNewBook(char *id, char*name, char*genre, char*author, char*publisher, int price){
	struct bookShop_Book *newBook = (struct bookShop_Book*)malloc(sizeof(struct bookShop_Book));
	strcpy(newBook->id, id);
	strcpy(newBook->name, name);
	strcpy(newBook->genre, genre);
	strcpy(newBook->author, author);
	strcpy(newBook->publisher, publisher);
	newBook->price = price;
	newBook->next = NULL;
	return newBook;
}

void bookShop_push(char *id, char*name, char*genre, char*author, char*publisher, int price){
	struct bookShop_Book *newBook = bookShop_addNewBook(id,name,genre,author,publisher,price);
	int index = bookShop_getHash(id);
	if(!bookShop_hashTable[index]){
		bookShop_hashTable[index] = newBook;
	}
	else{
		struct bookShop_Book* temp = bookShop_hashTable[index];
		while(temp){
			temp = temp->next;
		}
		temp = newBook;
	}
}

bool bookShop_pop(char *id){
	int index = bookShop_getHash(id);
	struct bookShop_Book *temp = bookShop_hashTable[index];
	if(!bookShop_hashTable[index]){
		return false;
	}
	else if(strcmp(bookShop_hashTable[index]->id,id)==0){
		bookShop_hashTable[index] = bookShop_hashTable[index]->next;
		free(temp);
		temp = NULL;
		return true;
	}
	else{
		while(temp->next && strcmp(temp->next->id,id)!=0){
			temp = temp->next;
		}
		if(!temp->next){
			return false;
		}
		struct bookShop_Book *link = temp->next;
		temp->next = link->next;
		free(link);
		link = NULL;
		return true;
	}
}

void bookShop_addBook(){
	system("cls");
	printf("\n\n");
	char id[25]="";
	srand(time(0));
	int ch1 = rand()%26;
	int ch2 = rand()%26;
	int ch3 = rand()%26;
	int number = rand()%100;
	sprintf(id,"%s%c%c%c%02d",id,ch1+'A', ch2+'A', ch3+'A', number);
	printf(" ID: %s\n", id);
	getchar();
	int addFlag = 1;
	char name[25];
	do{
		addFlag = 1;
		printf(" Input Book Name [5..20]: ");
		scanf("%[^\n]", name);
		getchar();
		int n = strlen(name);
		if(n<5||n>20){
			addFlag = 0;
		}
	}while(addFlag == 0);
	char genre[25];
	do{
		addFlag = 1;
		printf(" Input Book Genre [Fantasy | Romance | Horror][case sensitive]: ");
		scanf("%s", genre);
		getchar();
		if(strcmp(genre,"Fantasy")!=0 && strcmp(genre,"Romance")!=0 && strcmp(genre,"Horror")!=0){
			addFlag = 0;
		}
	}while(addFlag == 0);
	char author[255];
	do{
		addFlag = 1;
		printf(" Input Book Author [minimum 1 character]: ");
		scanf("%[^\n]", author);
		getchar();
		int n = strlen(author);
		if(n<1){
			addFlag = 0;
		}
	}while(addFlag == 0);
	char publisher[255];
	do{
		addFlag = 1;
		printf(" Input Book Publisher [3..10]: ");
		scanf("%[^\n]", publisher);
		getchar();
		int n = strlen(publisher);
		if(n<3||n>10){
			addFlag = 0;
		}
	}while(addFlag == 0);
	int price;
	do{
		addFlag = 1;
		printf(" Input Book Price[cannot zero]: ");
		scanf("%d", &price);
		getchar();
		if(price<1){
			addFlag = 0;
		}
	}while(addFlag == 0);
	bookShop_push(id,name,genre,author,publisher,price);
	printf(" New Book successfully inserted!");
	getchar();
	return;
}

void bookShop_viewBook(){
	system("cls");
	printf("\n\n");
	int no = 1;
	for(int i=0;i<bookShop_SIZE;++i){
		struct bookShop_Book *curr = bookShop_hashTable[i];
		while(curr){
			printf(" Book %d\n", no);
			printf(" ID : %s\n", curr->id);
			printf(" Name : %s\n", curr->name);
			printf(" Genre : %s\n", curr->genre);
			printf(" Author : %s\n", curr->author);
			printf(" Price : %d\n", curr->price);
			printf(" ===================\n\n");
			no++;
			curr = curr->next;
		}
	}
	if(no==1){
		printf(" List is empty..");
	}
	getchar();
	getchar();
	return;
}

void bookShop_deleteBook(){
	system("cls");
	printf("\n\n");
	int no = 1;
	for(int i=0;i<bookShop_SIZE;++i){
		struct bookShop_Book *curr = bookShop_hashTable[i];
		while(curr){
			printf(" Book %d\n", no);
			printf(" ID : %s\n", curr->id);
			printf(" Name : %s\n", curr->name);
			printf(" Genre : %s\n", curr->genre);
			printf(" Author : %s\n", curr->author);
			printf(" Price : %d\n", curr->price);
			printf(" ===================\n\n");
			no++;
			curr = curr->next;
		}
	}
	if(no==1){
		printf(" List is empty..");
		getchar();
		getchar();
		return;
	}
	char toDelete[10];
	printf(" Enter Book ID to be deleted\nID: ");
	scanf("%s", toDelete);
	getchar();
	bool deleted = bookShop_pop(toDelete);
	if(deleted){
		printf(" Book successfully deleted!");
	}
	else{
		printf(" Book not found!");
	}
	getchar();
	return;
}


void bookShop_game(){
	char menu;
	do{
		system("cls");
		printf("\n\n Book Shop\n");
		printf(" ==========\n");
		printf(" 1. Add New Book\n");
		printf(" 2. View Books\n");
		printf(" 3. Delete Book\n");
		printf(" 4. Exit\n");
		printf(" >> ");
		menu = getchar();
		switch(menu-'0'){
			case 1:
				bookShop_addBook();
				break;
			case 2:
				bookShop_viewBook();
				break;
			case 3:
				bookShop_deleteBook();
				break;
		}
	}while(menu!='4');
	return;
}
