#include<stdio.h>
#include<stdlib.h>

int miningSimulator_maxDepth = 1;

struct miningSimulator_cave{
	int index, goldProduction, depth;
	struct miningSimulator_cave *left, *right;
};

struct miningSimulator_cave *miningSimulator_createCave(int index, int goldProduction, int depth){
	struct miningSimulator_cave *newCave = (struct miningSimulator_cave *)malloc(sizeof(struct miningSimulator_cave));
	newCave->index = index;
	newCave->goldProduction = goldProduction;
	newCave->depth = depth;
	newCave->left = newCave->right = NULL;
	return newCave;
}

struct miningSimulator_cave *miningSimulator_push(struct miningSimulator_cave *root, int index, int goldProduction, int depth){
	if(!root){
		root = miningSimulator_createCave(index, goldProduction, depth);
		printf("\n New cave index detected.\n Total gold production for Cave %d is %d.\n", index, root->goldProduction);
		if(depth>miningSimulator_maxDepth){
			miningSimulator_maxDepth = depth;
		}
	}
	else if(index<root->index){
		root->left = miningSimulator_push(root->left, index, goldProduction, depth+1);
	}
	else if(index>root->index){
		root->right = miningSimulator_push(root->right, index, goldProduction, depth+1);
	}
	else if(index==root->index){
		root->goldProduction+=goldProduction;
		printf("\n Cave index already exists.\n New total gold production for Cave %d is %d.\n", index, root->goldProduction);
	}
	return root;
}

struct miningSimulator_cave *miningSimulator_getPredecessor(struct miningSimulator_cave*root){
	struct miningSimulator_cave *curr = root->left;
	while(curr->right){
		curr = curr->right;
	}
	return curr;
}

struct miningSimulator_cave *miningSimulator_pop(struct miningSimulator_cave *root , int index){
	if(!root){
		return NULL;
	}
	else if(index<root->index){
		root->left = miningSimulator_pop(root->left, index);
	}
	else if(index>root->index){
		root->right = miningSimulator_pop(root->right, index);
	}
	else{
		if(!root->left && !root->right){
			free(root);
			root = NULL;
		}
		else if(!root->left && root->right){
			struct miningSimulator_cave *temp = root;
			root = root->right;
			free(temp);
			temp = NULL;
		}
		else if(root->left && !root->right){
			struct miningSimulator_cave *temp = root;
			root = root->left;
			free(temp);
			temp = NULL;
		}
		else{
			struct miningSimulator_cave *temp = miningSimulator_getPredecessor(root);
			root->goldProduction = temp->goldProduction;
			root->index = temp->depth;
			root->left = temp->left;
			root->right = temp->right;
			root->left = miningSimulator_pop(root->left, temp->index);
		}
	}
	return root;
}

struct miningSimulator_cave *miningSimulator_insertMiningData(struct miningSimulator_cave *root){
	system("cls");
	printf("\n");
	int insertFlag = 1, index, gold;
	do{
		insertFlag =1;
		printf(" Input cave index [1-999]: ");
		scanf("%d", &index);
		getchar();
		if(index<1|| index>999){
			insertFlag = 0;
		}
	}while(insertFlag==0);
	do{
		insertFlag =1;
		printf(" Input gold production [1-100]: ");
		scanf("%d", &gold);
		getchar();
		if(gold<1|| gold>100){
			insertFlag = 0;
		}
	}while(insertFlag==0);
	root = miningSimulator_push(root, index, gold, 1);
	printf("\n");
	printf(" Press enter to continue...");
	getchar();
	return root;
}

void miningSimulator_displayCaveData(struct miningSimulator_cave *root){
	if(!root){
		return;
	}
	miningSimulator_displayCaveData(root->left);
	printf(" >> Cave %-3d (depth %-3d), total gold production: %d\n", root->index, root->depth, root->goldProduction);
	miningSimulator_displayCaveData(root->right);
}

int miningSimulator_total = 0;

void miningSimulator_getTotalByDepth(struct miningSimulator_cave*root, int depth){
	if(!root){
		return;
	}
	miningSimulator_getTotalByDepth(root->left, depth);
	if(root->depth==depth){
		miningSimulator_total+=root->goldProduction;
	}
	miningSimulator_getTotalByDepth(root->right, depth);
}

void miningSimulator_displayMiningReport(struct miningSimulator_cave *root){
	for(int i=1;i<=miningSimulator_maxDepth;++i){
		miningSimulator_total = 0;
		miningSimulator_getTotalByDepth(root, i);
		printf(" >> Total gold production for depth %-3d is %d\n", i, miningSimulator_total);
	}
}

struct miningSimulator_cave *miningSimulator_popAll(struct miningSimulator_cave *root){
	for(int i =1;i<=999;++i){
		root = miningSimulator_pop(root,i);
	}
	return root;
}

void miningSimulator_game(){
	struct miningSimulator_cave *root = NULL;
	char menu;
	do{
		system("cls");
		printf("\n");
		printf(" Mining Simulator\n");
		printf(" ====================\n");
		printf(" [1] Insert Mining Data\n");
		printf(" [2] Display All Cave Data\n");
		printf(" [3] Display Mining Reports\n");
		printf(" [4] Exit\n");
		printf(" >> ");
		menu = getchar();
		switch(menu-'0'){
			case 1:
				root = miningSimulator_insertMiningData(root);
				break;
			case 2:
				system("cls");
				printf("\n");
				if(!root){
					printf(" Cave data is empty, nothing to display.\n");
				}
				else{
					miningSimulator_displayCaveData(root);
				}
				getchar();
				printf("\n Press enter to continue...");
				getchar();
				break;
			case 3:
				system("cls");
				printf("\n");
				if(!root){
					printf(" Cave data is empty, nothing to display.\n");
				}
				else{
					miningSimulator_displayMiningReport(root);
				}
				getchar();
				printf("\n Press enter to continue...");
				getchar();
				break;
			case 4:
				system("cls");
				root = miningSimulator_popAll(root);
				printf("\n All data has been removed from memory.\n Thankyou for playing, see you again...\n");
				getchar();
				getchar();
				break;
		}
	}while(menu!='4');
	return;
}
