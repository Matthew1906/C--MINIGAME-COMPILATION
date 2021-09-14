#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

const char* warungbudi_detectOS() {
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}

struct warungbudi_dish {
	char name[100];
	int price;
    char priceStr[100];
	int quantity;
	struct warungbudi_dish *next, *prev;
}*warungbudi_head = NULL, *warungbudi_tail = NULL;

struct warungbudi_dish* warungbudi_createDish(char *name, int price, int qty){
	struct warungbudi_dish *node = (struct warungbudi_dish*)malloc(sizeof(struct warungbudi_dish));
    char Strprice[100];
    Strprice[0] = 'R';
    Strprice[1] = 'p';
    Strprice[2] = '.';
    Strprice[3] = '\0';
    char str[100];
    int temp = price, lenTemp = 1;
    while(temp>9){
        temp/=10;
        lenTemp++;
    }
    int temp1 = price;
    for(int i=lenTemp-1;i>0;i--){
        str[i] = (temp1%10)+'0';
        temp1/=10;
    }
    str[0] = temp1+'0';
    str[lenTemp] = '\0';
    //printf("%s\n", str);
    strcat(Strprice, str);
    Strprice[lenTemp+3] = '\0';
    //printf("%s\n", Strprice);
	strcpy(node->name, name);
	strcpy(node->priceStr, Strprice);
	node->price = price;
	node->quantity = qty;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void warungbudi_pushDish(char *name, int price, int qty){
	struct warungbudi_dish * node = warungbudi_createDish(name, price, qty);
	if(warungbudi_head==NULL){
		warungbudi_head = warungbudi_tail = node;
	}
	else if(strcmp(name,warungbudi_head->name)<0){
		node -> next = warungbudi_head;
		warungbudi_head -> prev = node;
		warungbudi_head = node;
	}
	else if(strcmp(name,warungbudi_tail->name)>0){
		node->prev = warungbudi_tail;
		warungbudi_tail->next = node;
		warungbudi_tail = node;
	}
	else{
		struct warungbudi_dish *curr = warungbudi_head;
		while(curr->next!=NULL && strcmp(curr->next->name,name)<0){
			curr = curr->next;
		}
		node->prev = curr;
		node->next = curr->next;
		curr->next->prev = node;
		curr->next = node;
	}
}

int warungbudi_popDish(char *name){
    struct warungbudi_dish *curr = warungbudi_head;
	if(warungbudi_head==NULL){
		return -1;
	}
	else if(warungbudi_head==warungbudi_tail){
		free(curr);
		warungbudi_head=warungbudi_tail=NULL;
	}
	else if(strcmp(name, warungbudi_head->name)==0){
		warungbudi_head = warungbudi_head->next;
		free(curr);
		warungbudi_head->prev = NULL;
	}
	else if(strcmp(name,warungbudi_tail->name)==0){
		free(warungbudi_tail);
		warungbudi_tail = warungbudi_tail->prev;
		warungbudi_tail->next = NULL;
	}
	else{
		while(curr->next!=NULL && strcmp(curr->next->name,name)!=0){
			curr = curr->next;
		}
		if(curr == warungbudi_tail){
			return -1;
		}
		free(curr->next);
		curr->next->next->prev = curr;
		curr->next = curr->next->next;
		return 1;
	}
}

struct warungbudi_customer{
	char name[100];
	struct warungbudi_dish *bookedHead;
    struct warungbudi_dish *bookedTail;
	struct warungbudi_customer *next;
}*warungbudi_table[26]={NULL};

unsigned long warungbudi_DJB2(char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % 26;
}

void warungbudi_pushBook(struct warungbudi_customer *cust, char *name, int qty, int price){
	struct warungbudi_dish * node = warungbudi_createDish(name, price, qty);
	if(cust->bookedHead==NULL){
		cust->bookedHead = cust->bookedTail = node;
	}
	else if(strcmp(name,cust->bookedHead->name)<0){
		node -> next = cust->bookedHead;
		cust->bookedHead -> prev = node;
		cust->bookedHead = node;
	}
	else if(strcmp(name,cust->bookedTail->name)>0){
		node->prev = cust->bookedTail;
		cust->bookedTail->next = node;
		cust->bookedTail = node;
	}
	else{
		struct warungbudi_dish *curr1 = cust->bookedHead;
		while(curr1->next!=NULL && strcmp(curr1->next->name,name)<0){
			curr1 = curr1->next;
		}
		node->prev = curr1;
		node->next = curr1->next;
		curr1->next->prev = node;
		curr1->next = node;
	}
}
void warungbudi_insert(char *str){
	struct warungbudi_customer *node = (struct warungbudi_customer*)malloc(sizeof(struct warungbudi_customer));
	strcpy(node->name, str);
	node->next = NULL;
	node->bookedHead = NULL;
	node->bookedTail = NULL;
	int index = warungbudi_DJB2(str);
	if(warungbudi_table[index]==NULL){
		warungbudi_table[index] = node;
	}
	else{
		struct warungbudi_customer *curr = warungbudi_table[index];
		while(curr->next!=NULL){
			curr = curr->next;
		}
		curr->next = node;
	}
}

void warungbudi_AddDish(){
	char dishName[100];
    int price, quantity, addFlag = 1;
    do{
        addFlag = 1;
        printf(" Insert the name of the dish [lowercase letters]: ");
        scanf("%[^\n]", dishName);
        getchar();
        int len = strlen(dishName);
        for(int i=0;i<len;i++){
            if(dishName[i]!=' ' && !(dishName[i]>='a' && dishName[i]<='z')){
                addFlag = 0;
                break;
            }
        }
        struct warungbudi_dish *curr = warungbudi_head;
        while(curr!=NULL){
            if(strcmp(curr->name,dishName)==0){
                addFlag = 0;
                break;
            }
            curr = curr->next;
        }
    }while(addFlag==0);
    do{
        addFlag = 1;
        printf(" Insert the price of the dish [1000...50000]: ");
        scanf("%d", &price);
        getchar();
        if(price<1000 || price>50000){
            addFlag = 0;
        }
    }while(addFlag==0);
    do{
        addFlag = 1;
        printf(" Insert the quantity of the dish [1...999]: ");
        scanf("%d", &quantity);
        getchar();
        if(quantity<1 || quantity>999){
            addFlag = 0;
        }
    }while(addFlag = 0);
    warungbudi_pushDish(dishName, price, quantity);
    printf(" The dish has been added!\n");
    printf(" Please enter to continue..");
    getchar();
    return;
}

void warungbudi_RemoveDish(){
	//clearScreen();
    struct warungbudi_dish *curr = warungbudi_head;
    if(curr == NULL){
        return;
    }
	printf("               Bude's Menu\n");
    printf(" ========================================= \n");
    printf("  No.        Name        Quantity   Price\n");
    int index = 1;
    while(curr!=NULL){
    	int len = strlen(curr->name), lenP = strlen(curr->priceStr);
    	char str[100] = "";
        printf("  %2d. %*s%*s%03d     %*s\n", index, ((20-len)>>1)+len, curr->name,  ((20-len)>>1), str, curr->quantity, ((8-lenP)>>1)+lenP, curr->priceStr);
        curr = curr->next;
        index++;
    }
    printf(" ========================================= \n");
    char sellName[100];
    printf(" Insert dish name to be deleted: ");
    scanf("%[^\n]", sellName);
    getchar();
    int buang = warungbudi_popDish(sellName);
    if(buang == 1){
    	printf(" The dish has been removed!\n");
		printf(" Press enter to continue..");
		getchar();		
	}
    
    return;
}

void warungbudi_AddCustomer(){
	//clearScreen();
	//getchar();
	char customerName[100];
	int add_flag = 1;
	do{
		add_flag = 1;
		printf(" Insert the customer name [Without space]: ");
		scanf("%[^\n]", customerName);
		getchar();
		int len = strlen(customerName);
		for(int i=0;i<len;i++){
			if(customerName[i]==' '){
				add_flag = 0;
				break;
			}
		}
	}while(add_flag == 0);
	warungbudi_insert(customerName);
	printf(" Customer has been added!\n");
	printf(" Press enter to continue..");
	getchar();
	return;
}

int warungbudi_search(char *cust){
	unsigned long i = warungbudi_DJB2(cust);
	if(warungbudi_table[i]!=NULL){
		struct warungbudi_customer * curr = warungbudi_table[i];
		while(curr!=NULL && strcmp(curr->name,cust)!=0){
			curr = curr->next;
		}
		if(curr!=NULL){
			return i;
		}
		else return -1;
	}	
	return -1;
}

void warungbudi_SearchCustomer(){
	char find[100];
	printf(" Insert the customer's name to be searched: ");
	scanf("%[^\n]", find);
	getchar();
	int found = warungbudi_search(find);
	if(found==-1){
		printf(" %s is not present\n", find);
	}
	else{
		printf(" %d. %s\n", found+1, find);
	}
	printf(" Press enter to continue..");
	getchar();
	return;
}

int warungbudi_crowded(){
	for(int i=0;i<26;i++){
		if(warungbudi_table[i]!=NULL){
			return 1;
		}
	}
	return -1;
}
void warungbudi_ViewWarteg(){
	int cek = warungbudi_crowded();
	if(cek == -1){
		return;
	}
	printf("Customer List\n");
	for(int i=0;i<26;i++){
		if(warungbudi_table[i]!=NULL){
			struct warungbudi_customer *temp1 = warungbudi_table[i];
			printf("%d. ", i);
			while(temp1!=NULL){
				printf("%s ", temp1->name);
				temp1 = temp1->next;
				if(temp1!=NULL){
					printf("-> ");
				}
			}
			printf("\n");
		}
	}
	printf("Press enter to continue..");
	getchar();
	return;
}

void warungbudi_Order(){
	int cek = warungbudi_crowded();
	if(cek == -1){
		printf(" There is no customer!\n");
		printf(" Press enter to continue..");
		getchar();
		return;
	}
	char name[100];
	int find;
	do{
		printf(" Insert the customer's name: ");
		scanf("%[^\n]", name);
		getchar();
		find = warungbudi_search(name);
	}while(find==-1);
	unsigned long search = warungbudi_DJB2(name);
	if(warungbudi_table[search]!=NULL){
		struct warungbudi_customer * curr = warungbudi_table[search];
		while(curr!=NULL && strcmp(curr->name,name)!=0){
			curr = curr->next;
		}
		if(curr!=NULL){
			if(warungbudi_head==NULL){
				printf(" There are no food available!\n");
				printf(" Press enter to continue..");
				getchar();
				return;
			}
			int pesanan;
			printf(" Insert the amount of dish: ");
			scanf("%d", &pesanan);
			getchar();
			for(int i=1;i<=pesanan;i++){
				int quantity, flag = 1;
				char menu[100];
				do{
					flag = 1;
					printf(" [%d] Insert the dish's name and quantity: ", i);
					scanf("%[^x]x%d", menu, &quantity);
					getchar();
					int lenCurr = strlen(menu);
					menu[lenCurr-1] = '\0';
					struct warungbudi_dish *temp = warungbudi_head;
					while(temp!=NULL){
						if(strcmp(temp->name, menu)==0){
							break;
						}
						temp = temp->next;
					}
					if(temp==NULL){
						flag = 0;
					}
					else if(quantity>temp->quantity){
						flag = 0;
					}
					else{
						warungbudi_pushBook(curr, menu, quantity, quantity*(temp->price));
						temp->quantity -= quantity;
						if(temp->quantity == 0){
							int buang = warungbudi_popDish(temp->name);
						}
					}
				}while(flag ==0);
			}
			printf(" Order success!\n");
			printf(" Press enter to continue..");
			getchar();
		}
		else return;
	}	
	else return;
	
}

void warungbudi_Payment(){
	//clearScreen();
	int cek = warungbudi_crowded();
	if(cek == -1){
		return;
	}
	int index=0;
	do{
		printf("Insert Customer Index: ");
		scanf("%d", &index);
		getchar();
	}while(warungbudi_table[index]==NULL);
	struct warungbudi_customer *payNow = warungbudi_table[index];
	printf("%s\n", payNow->name);
	int i = 1, total = 0;
	struct warungbudi_dish* ordered = payNow->bookedHead;
	while(ordered!=NULL){
		printf("[%d] %s x %d\n", i, ordered->name, ordered->quantity);
		total+=ordered->price;
		ordered = ordered->next;
	}
	printf("Total = Rp.%d\n", total);
	struct warungbudi_customer *throws = warungbudi_table[index];
	warungbudi_table[index] = warungbudi_table[index]->next;
	throws = NULL;
	free(throws);
	printf("Press enter to continue..");
	getchar();
}

void warungbudi_game(){
    char choose;
    do{
        do{
        	time_t t;
    		time(&t);
            system("cls");
            printf(" System: %s\n", warungbudi_detectOS());
            printf(" %s\n",ctime(&t));
            printf(" 1. Add Dish\n");
            printf(" 2. Remove Dish\n");
            printf(" 3. Add Customer\n");
            printf(" 4. Search Customer\n");
            printf(" 5. View Warteg\n");
            printf(" 6. Order\n");
            printf(" 7. Payment\n");
            printf(" 8. Exit Warteg\n");
            printf(" >> ");
            choose = getchar();
            getchar();
        }while(choose-'0'<1 || choose-'0'>8);
        switch(choose-'0'){
            case 1:
                warungbudi_AddDish();
                break;
            case 2:
                warungbudi_RemoveDish();
                break;
            case 3:
                warungbudi_AddCustomer();
                break;
            case 4:
                warungbudi_SearchCustomer();
                break;
            case 5:
                warungbudi_ViewWarteg();
                break;
            case 6:
                warungbudi_Order();
                break;
            case 7:
                warungbudi_Payment();
                break;
            case 8:
                break;
        }
    }while(choose-'0'!=8);
    return;
}
