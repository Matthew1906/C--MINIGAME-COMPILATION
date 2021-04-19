#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int opercooked_profit = 0,opercooked_dessertIndex = 0, opercooked_drinkIndex=0, opercooked_orderDrink=0, opercooked_orderDessert = 0;

// SUPPOSEDLY IMPLEMENTED USING LINKED LISTS, BUT MEH

struct opercooked_dessert {
    char food_name[500];
    int food_price;
    char topping[20];
    float calories;
    int cooking_time;
    char order_time[100];
};

struct opercooked_drink {
    char food_name[500];
    int food_price;
    char flavor[20];
    char size;
    int cooking_time;
    char order_time[100];
};

void opercooked_Add(struct opercooked_dessert *addDessert, struct opercooked_drink *addDrink){
	system("cls");
	char add[8];
	int add_flag = 0;
	do{
		system("cls");
		add_flag = 0;
		printf("What do you want to add?\n");
		printf("1. dessert\n2. drink\n");
		printf("Choose: ");
		scanf("%[^\n]", add);
		getchar();
		if(strcmp(add, "dessert")==0 || strcmp(add, "drink")==0){
			add_flag = 1;
		}
	}while(add_flag==0);
	char name[500], flavor[20], orderTime[100], topping[20], size;
	int price, name_len=0, cookTime;
	float calories;
	
	do{
		name_len = 0;
		printf("Input the name [at least 5 characters]: ");
		scanf("%[^\n]", name);
		getchar();
		name_len = strlen(name);
	}while(name_len <5);
	do{
		printf("Input the price [10 - 500]: $ ");
		scanf("%d", &price);
		getchar();
	}while(price<10 || price>500);
	if(strcmp(add, "dessert")==0){
		int topping_flag=0, extraTime=0;
		do{
			topping_flag=0;
			printf("Input the topping ['Caramel' | 'Honey' | 'Syrup'](Case Sensitive): ");
			scanf("%[^\n]", topping);
			getchar();
			if(strcmp(topping,"Caramel")==0 || strcmp(topping, "Honey")==0 || strcmp(topping, "Syrup")==0){
				topping_flag=1;
			}
		}while(topping_flag==0);
		int calories_flag = 1;
		do{
			calories_flag =1;
			printf("Insert calories [1.00 - 99.00]: ");
			scanf("%f", &calories);
			getchar();
			if(calories<1.00 || calories>99.00){
//				printf("Must be between 1.00 and 99.00 calories!\n");
//				printf("%f", calories);
				calories_flag=0;
//				getchar();
			}
		}while(calories_flag==0);
		strcpy(addDessert[opercooked_dessertIndex].food_name, name);
		addDessert[opercooked_dessertIndex].food_price = price;
		strcpy(addDessert[opercooked_dessertIndex].topping, topping);
		addDessert[opercooked_dessertIndex].calories= calories;
		strcpy(addDessert[opercooked_dessertIndex].order_time, __DATE__);
		strcat(addDessert[opercooked_dessertIndex].order_time," ");
		strcat(addDessert[opercooked_dessertIndex].order_time, __TIME__);
		if(strcmp(topping, "Caramel")==0){
			extraTime = 10;
		}
		else if(strcmp(topping, "Honey")==0){
			extraTime = 15;
		}
		else extraTime = 20;
		srand(time(0));
		addDessert[opercooked_dessertIndex].cooking_time = (50 + rand()%41)+ extraTime;
//		printf("%d\n", addDessert[opercooked_dessertIndex].cooking_time);
		opercooked_dessertIndex++;
	}
	else if(strcmp(add, "drink")==0){
		int flavor_flag=0, extraTime = 0;
		do{
			flavor_flag=0;
			printf("Input the flavor ['Mint' | 'Mix Berry' | 'Cheese'](Case Sensitive): ");
			scanf("%[^\n]", flavor);
			getchar();
			if(strcmp(flavor,"Mint")==0 || strcmp(flavor, "Mix Berry")==0 || strcmp(flavor, "Cheese")==0){
				flavor_flag=1;
			}
		}while(flavor_flag==0);
		do{
			printf("Input the size [S | M | L](Case Sensitive): ");
			size = getchar();
			getchar();
		}while(size!='S'&& size!='M' && size!='L');
		strcpy(addDrink[opercooked_drinkIndex].food_name, name);
		addDrink[opercooked_drinkIndex].food_price = price;
		strcpy(addDrink[opercooked_drinkIndex].flavor, flavor);
		addDrink[opercooked_drinkIndex].size= size;
		strcpy(addDrink[opercooked_drinkIndex].order_time, __DATE__);
		strcat(addDrink[opercooked_drinkIndex].order_time," ");
		strcat(addDrink[opercooked_drinkIndex].order_time, __TIME__);
		if(strcmp(flavor, "Mint")==0){
			extraTime = 10;
		}
		else if(strcmp(topping, "Mix Berry")==0){
			extraTime = 15;
		}
		else extraTime = 20;
		srand(time(0));
		addDrink[opercooked_drinkIndex].cooking_time = (50 + rand()%41)+ extraTime;
//		printf("%d\n", addDrink[opercooked_drinkIndex].cooking_time);
		opercooked_drinkIndex++;
	}
	printf("\nSuccessfully added a new menu!\n");
	printf("Press enter to continue...");
	getchar();
	return;
}

void opercooked_ViewProcess(struct opercooked_dessert *OrderedDessert, struct opercooked_drink *OrderedDrink){
	system("cls");
	int process_flag=0;
	for(int i=0;i<opercooked_orderDessert;i++){
		if(OrderedDessert[i].cooking_time>0){
			OrderedDessert[i].cooking_time-=10;
			if(OrderedDessert[i].cooking_time<=0){
				opercooked_profit += OrderedDessert[i].food_price;
			}
		}
	}
	for(int i=0;i<opercooked_orderDrink;i++){
		if(OrderedDrink[i].cooking_time>0){
			OrderedDrink[i].cooking_time-=10;
			if(OrderedDrink[i].cooking_time<=0){
				opercooked_profit+= OrderedDrink[i].food_price;
			}
		}
	}
	for(int i=0;i<opercooked_orderDessert;i++){
		if(OrderedDessert[i].cooking_time>0){
			process_flag = 1;
		}
	}
	for(int i=0;i<opercooked_orderDrink;i++){
		if(OrderedDrink[i].cooking_time>0){
			process_flag = 1;
		}
	}
	if(process_flag==0){
		printf("There is no cooking process recently!\n\n");
		getchar();
		printf("Press enter to continue...");
		getchar();
		return;
	}
	printf("-------------------------------------------------------------\n");
	printf("| No. | Type    | Name                 | Price | Time Left |\n");
	printf("-------------------------------------------------------------\n");
	int index = 1;
	for(int i=0;i<opercooked_orderDessert;i++){
		if(OrderedDessert[i].cooking_time>0)printf("| %-3d | dessert | %-20s | %-5d | %-9d |\n", index, OrderedDessert[i].food_name, OrderedDessert[i].food_price, OrderedDessert[i].cooking_time);
		index++;
	}
	for(int i=0;i<opercooked_orderDrink;i++){
		if(OrderedDrink[i].cooking_time>0)printf("| %-3d | drink   | %-20s | %-5d | %-9d |\n", index, OrderedDrink[i].food_name, OrderedDrink[i].food_price, OrderedDrink[i].cooking_time);
		index++;
	}
	printf("-------------------------------------------------------------\n");
	getchar();
	printf("Press enter to return to main menu...");
	getchar();
}

void opercooked_ViewOrderHistory(struct opercooked_dessert *OrderedDessert, struct opercooked_drink *OrderedDrink){
	system("cls");
	int ordered_flag=0;
	for(int i=0;i<opercooked_orderDessert;i++){
	//printf("%d\n", OrderedDessert[i].cooking_time);
		if(OrderedDessert[i].cooking_time<=0){
			ordered_flag = 1;
		}
	}
	for(int i=0;i<opercooked_orderDrink;i++){
		if(OrderedDrink[i].cooking_time<=0){
		//	printf("%d\n", OrderedDrink[i].cooking_time);
			ordered_flag = 1;
		}
	}
	if(ordered_flag==0){
		printf("There is no Order History!\n\n");
		getchar();
		printf("Press enter to continue...");
		getchar();
		return;
	}
	int number = 1;
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("| No.  | Name                 | Price | Topping    | Calories  | Flavor     | Size | Order Time             |\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	for(int i=0;i<opercooked_orderDessert;i++){
		if(OrderedDessert[i].cooking_time<=0){
			printf("| %-3d  | %-20s | %-5d | %-10s | %05.2f     | -          | -    | %-22s |\n", number, OrderedDessert[i].food_name,  OrderedDessert[i].food_price, OrderedDessert[i].topping, OrderedDessert[i].calories, OrderedDessert[i].order_time);
			number++;
		}
	}
	for(int i=0;i<opercooked_orderDrink;i++){
		if(OrderedDrink[i].cooking_time<=0){
			printf("| %-3d  | %-20s | %-5d | -          | -         | %-10s | %c    | %-22s |\n", number, OrderedDrink[i].food_name,  OrderedDrink[i].food_price, OrderedDrink[i].flavor, OrderedDrink[i].size, OrderedDrink[i].order_time);
			number++;
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");
	getchar();
	printf("Press enter to continue...");
	getchar();
}

void opercooked_Order(struct opercooked_dessert *addDessert, struct opercooked_drink *addDrink, struct opercooked_dessert *OrderedDessert, struct opercooked_drink *OrderedDrink){
	int choice, number = 1;
	if(opercooked_dessertIndex==0 && opercooked_drinkIndex==0){
		system("cls");
		printf("There is no dessert or drink on the list!\n\n");
		getchar();
		printf("Press enter to continue...");
		getchar();
		return;
	}
	do{
		number = 1;
		system("cls");
		printf("------------------------------------------------------------------------------------\n");
		printf("| No.  | Name                 | Price | Topping    | Calories  | Flavor     | Size |\n");
		printf("------------------------------------------------------------------------------------\n");
		for(int i=0;i<opercooked_dessertIndex;i++){
			printf("| %-3d  | %-20s | %-5d | %-10s | %05.2f     | -          | -    |\n", number, addDessert[i].food_name,  addDessert[i].food_price, addDessert[i].topping, addDessert[i].calories);
			number++;
		}
		for(int i=0;i<opercooked_drinkIndex;i++){
			printf("| %-3d  | %-20s | %-5d | -          | -         | %-10s | %c    |\n", number+i, addDrink[i].food_name,  addDrink[i].food_price, addDrink[i].flavor, addDrink[i].size);
		}
		printf("------------------------------------------------------------------------------------\n");
		printf("Choose a menu to order [1 - %d]: ",number+opercooked_drinkIndex-1);
		scanf("%d", &choice);
	}while(choice<1 || choice>number+opercooked_drinkIndex-1);
	if(choice>=number){
		strcpy(OrderedDrink[opercooked_orderDrink].food_name,addDrink[choice-number].food_name);
		OrderedDrink[opercooked_orderDrink].food_price = addDrink[choice-number].food_price;
		strcpy(OrderedDrink[opercooked_orderDrink].flavor,addDrink[choice-number].flavor);
		OrderedDrink[opercooked_orderDrink].size = addDrink[choice-number].size;
		OrderedDrink[opercooked_orderDrink].cooking_time = addDrink[choice-number].cooking_time;
		strcpy(OrderedDrink[opercooked_orderDrink].order_time, __DATE__);
		strcat(OrderedDrink[opercooked_orderDrink].order_time," ");
		strcat(OrderedDrink[opercooked_orderDrink].order_time, __TIME__);
		opercooked_orderDrink++;
	}
	else{
		strcpy(OrderedDessert[opercooked_orderDessert].food_name,addDessert[choice-1].food_name);
		OrderedDessert[opercooked_orderDessert].food_price = addDessert[choice-1].food_price;
		strcpy(OrderedDessert[opercooked_orderDessert].topping,addDessert[choice-1].topping);
		OrderedDessert[opercooked_orderDessert].calories = addDessert[choice-1].calories;
		OrderedDessert[opercooked_orderDessert].cooking_time = addDessert[choice-1].cooking_time;
		strcpy(OrderedDessert[opercooked_orderDessert].order_time, __DATE__);
		strcat(OrderedDessert[opercooked_orderDessert].order_time," ");
		strcat(OrderedDessert[opercooked_orderDessert].order_time, __TIME__);	
		opercooked_orderDessert++;
	}
	getchar();
	printf("Press enter to continue...");
	getchar();
}

void opercooked_game(){
	char menuChoice;
	do{
		do{
			system("cls");
			printf("Welcome to OperCooked!\n");
			printf("Today Profit: $ %d\n", opercooked_profit);
			printf("======================\n");
			printf("1. Add dessert or Beverage\n");
			printf("2. View Cooking Process\n");
			printf("3. View Order History\n");
			printf("4. Order dessert or Beverage\n");
			printf("5. Exit\n");
			printf(">> ");
			menuChoice = getch();
			printf("%c\n", menuChoice);	
		}while(menuChoice-'0'<1 || menuChoice-'0'>5);
		getchar();
		struct opercooked_dessert addDessert[500];
		struct opercooked_drink addDrink[500];
		struct opercooked_dessert OrderedDessert[500];
		struct opercooked_drink OrderedDrink[500];
		switch(menuChoice-'0'){
			case 1:
				opercooked_Add(addDessert, addDrink);
				break;
			case 2:
				opercooked_ViewProcess(OrderedDessert, OrderedDrink);
				break;
			case 3:
				opercooked_ViewOrderHistory(OrderedDessert, OrderedDrink);
				break;
			case 4:
				opercooked_Order(addDessert, addDrink, OrderedDessert, OrderedDrink);
				break;
			case 5:
				break;
		}
	}while(menuChoice-'0'!=5);
	return;
}
