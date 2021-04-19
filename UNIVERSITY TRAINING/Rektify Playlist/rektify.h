#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct rektify_data{
	char title[255];
	int priority;
	struct rektify_data *next;
}*rektify_top = NULL;

struct rektify_data* rektify_createData(char *name, int priority){
	struct rektify_data *newData = (struct rektify_data *)malloc(sizeof(struct rektify_data));
	strcpy(newData->title, name);
	newData->priority = priority;
	newData->next = NULL;
}

bool rektify_findSong(char *name){
	struct rektify_data *temp = rektify_top;
	while(temp){
		if(strcmp(temp->title, name)==0){
			printf("Song %s is already in the playlist!\n", name);
			getchar();
			return true;
		}
		temp = temp->next;
	}
	return false;
}

void rektify_push(char *name, int priority){
	struct rektify_data *curr = rektify_createData(name, priority);
	bool check = rektify_findSong(name);
	if(check){
		return;
	}
	if(!rektify_top){
		rektify_top = curr;
	}
	else if(priority<rektify_top->priority){
		curr->next = rektify_top;
		rektify_top = curr;
	}
	else{
		struct rektify_data *temp = rektify_top;
		while(temp->next && temp->next->priority<=priority){
			temp = temp->next;
		}
		if(!temp->next){
			temp->next = curr;
		}
		else{
			curr->next = temp->next;
			temp->next = curr;
		}
	}
	getchar();
}

void rektify_pop(){
	if(!rektify_top){
		printf("No Song to be played...\n");
		getchar();
		return;
	}
	else{
		struct rektify_data *temp = rektify_top;
		printf("Song %s is being played now...\n", temp->title);
		getchar();
		rektify_top = temp->next;
		free(temp);
		getchar();
	}
}

void rektify_printAll(){
	printf("\n");
	if(!rektify_top){
		printf("No song in the playlist!\n");
	}
	else{		
		printf("Name                 | Prio |\n");
		struct rektify_data *temp = rektify_top;
		while(temp){
			printf("%-20s | %-3d  |", temp->title, temp->priority);
			if(temp==rektify_top){
				printf("    --> Top List Song\n");
			}
			else{
				printf("\n");
			}
			temp = temp->next;
		}	
	}
	printf("\n");
}

void rektify_game(){
	bool running = true;
	while(running){
		system("cls");
		char choice[255];
		bool choiceFlag = true;
		do{
			system("cls");
			choiceFlag = true;
			printf("-- Rektify Playlist --\n");
			printf("**********************\n");
			rektify_printAll();
			printf("1. Insert new song into your playlist\n");
			printf("2. Play song on the top list\n");
			printf("3. Exit\n");
			printf("Insert menu: ");
			scanf("%s", choice);
			getchar();
			if(strcmp(choice,"1")!=0 && strcmp(choice,"2")!=0 && strcmp(choice,"3")!=0){
				choiceFlag = false;
			}
		}while(!choiceFlag);
		if(strcmp(choice,"1")==0){
			char name[255];
			printf("Insert song name: ");
			scanf("%s", &name);
			getchar();
			int priority;
			printf("Insert priority[1|2|3]: ");
			scanf("%d", &priority);
			getchar();
			if(priority<1||priority>4){
				continue;
			}
			rektify_push(name, priority);
		}
		else if(strcmp(choice,"2")==0){
			rektify_pop();
		}
		else{
			running = false;
		}
	}
	return;
}
