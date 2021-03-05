#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char fish_playerName[25];
char fish_playerGender;
char fish_playerFishingEquipment[50] = "Fishing Rod";
int fish_playerLevel =1, fish_money = 1000, fish_numBait=10, fish_currFishWorth=0;
int fish_fishes[10];
void fish_logo(){
	printf("x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n");
	printf("x Coe Poe Fish A Fish...>>> x\n");
	printf("x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n\n");
	return;
}

void fish_buy(){
	printf("4. B. B E L I  U M P A N\n");
	printf("%%-----------------------------------%%\n\n\n");
	printf("** Level Pemain : %d\n", fish_playerLevel);
	printf("** Uang Pemain  : $%d\n\n", fish_money);
	printf(">> Nama Pemain  : %s\n", fish_playerName);
	printf("## Total Umpan  : %d\n\n", fish_numBait);
	printf("X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X\n\n");
	printf(" =====================================================\n");
	printf(":: No.  ::    Nama Umpan       ::     Harga Umpan    ::\n");
	printf(" =====================================================\n");
	printf(":: 01   ::    Green Big Worm   ::         $5         ::\n");
	printf(" =====================================================\n");
	int limit = fish_money/5, amount;
	do{
		printf("Berapa Banyak Umpan Yang Ingin Anda Beli [0..%d] : ",limit);
		scanf("%d", &amount);
	}while(amount<0 && amount>limit);
	printf("Pembelian Umpan Berhasil..^^\n");
	fish_numBait+=amount;
	fish_money-=5*amount;
	printf("Jumlah Umpan Anda Saat Ini Adalah : %d\n", fish_numBait);
	printf("Tekan ENTER untuk KEMBALI KE MENU UTAMA...");
	getchar();
	getchar();	
}
void fish_upgrade(){
	fish_logo();
	int no = 1;
	printf("4. A. U P G R A D E  P A N C I N G A N\n");
	printf("%%-----------------------------------%%\n\n\n");
	printf("** Level Pemain : %d\n", fish_playerLevel);
	printf("** Uang Pemain  : $%d\n\n", fish_money);
	printf(">> Nama Pemain  : %s\n", fish_playerName);
	printf("## Pancingan    : %s\n", fish_playerFishingEquipment);
	printf("X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X\n\n");
	printf(" ===============================================================\n");
	printf(":: No.  ::    Jenis Pancingan       ::     Harga Pancingan    ::\n");
	printf(" ===============================================================\n");
	printf(":: %02d ::    Fishing Pole          ::          $ 300         ::\n", no);
	no++;
	printf(":: %02d ::    Advance Fishing Rod   ::          $ 600         ::\n", no);
	no++;
	printf(":: %02d ::    Advance Fishing Pole  ::          $ 900         ::\n", no);
	no++;
	printf(":: %02d ::    Ultimate Fishing Rod  ::          $ 1200        ::\n", no);
	no++;
	printf(":: %02d ::    Ultimate Fishing Pole ::          $ 1500        ::\n", no);
	printf(" ===============================================================\n");
	int rod;
	do{
		printf("Pilihan [1...5] : ");
		scanf("%d", &rod);
	}while(rod<1 && rod>5);
	if(rod==1 && fish_money>300){
		fish_money-=300;
		printf("Jenis Pancingan : Fishing Pole\n");
		printf("Anda Telah Berhasil Melakukan Upgrade..^^\n\n");
		printf("Level Anda Sekarang : 1\n");
		if(fish_playerLevel==1){
			printf("Level Tidak Berubah.\n\n");
		}
		else if(fish_playerLevel>1){
			printf("Level Menurun..\n\n");
		}
		else{
			printf("Sukses Meningkatkan Level..\n\n");
		}
		fish_playerLevel=1;
		strcpy(fish_playerFishingEquipment, "Fishing Pole");
	}
	else if(rod==2 && fish_money>600){
		fish_money-=600;
		printf("Jenis Pancingan : Advanced Fishing Rod\n");
		printf("Anda Telah Berhasil Melakukan Upgrade..^^\n\n");
		printf("Level Anda Sekarang : 2\n");
		if(fish_playerLevel==2){
			printf("Level Tidak Berubah.\n\n");
		}
		else if(fish_playerLevel>2){
			printf("Level Menurun..\n\n");
		}
		else{
			printf("Sukses Meningkatkan Level..\n\n");
		}
		fish_playerLevel=2;
		strcpy(fish_playerFishingEquipment, "Advanced Fishing Rod");
	}
	else if(rod==3 && fish_money>900){
		fish_money-=900;
		printf("Jenis Pancingan : Advanced Fishing Pole\n");
		printf("Anda Telah Berhasil Melakukan Upgrade..^^\n\n");
		printf("Level Anda Sekarang : 3\n");
		if(fish_playerLevel==3){
			printf("Level Tidak Berubah.\n\n");
		}
		else if(fish_playerLevel>3){
			printf("Level Menurun..\n\n");
		}
		else{
			printf("Sukses Meningkatkan Level..\n\n");
		}
		fish_playerLevel=3;
		strcpy(fish_playerFishingEquipment, "Advanced Fishing Pole");
	}
	else if(rod==4 && fish_money>1200){
		fish_money-=1200;
		printf("Jenis Pancingan : Ultimate Fishing Rod\n");
		printf("Anda Telah Berhasil Melakukan Upgrade..^^\n\n");
		printf("Level Anda Sekarang : 4\n");
		if(fish_playerLevel==4){
			printf("Level Tidak Berubah.\n\n");
		}
		else if(fish_playerLevel>4){
			printf("Level Menurun..\n\n");
		}
		else{
			printf("Sukses Meningkatkan Level..\n\n");
		}
		fish_playerLevel=4;
		strcpy(fish_playerFishingEquipment, "Ultimate Fishing Rod");
	}
	else if(rod==5 && fish_money>1500){
		fish_money-=1500;
		printf("Jenis Pancingan : Ultimate Fishing Pole\n");
		printf("Anda Telah Berhasil Melakukan Upgrade..^^\n\n");
		printf("Level Anda Sekarang : 5\n");
		if(fish_playerLevel==5){
			printf("Level Tidak Berubah.\n\n");
		}
		else if(fish_playerLevel>5){
			printf("Level Menurun..\n\n");
		}
		else{
			printf("Sukses Meningkatkan Level..\n\n");
		}
		fish_playerLevel=5;
		strcpy(fish_playerFishingEquipment, "Ultimate Fishing Pole");
	}
	else{
		printf("Maaf Anda Tidak Punya Cukup Uang..^^\n");
	}
	printf("Tekan ENTER untuk KEMBALI KE MENU UTAMA...");
	getchar();
	getchar();	
	return;
}
void fish_levelingup(){
	fish_logo();
	printf("4. B E L A N J A / U P G R A D E  P E R L E N G K A P A N  M E M A N C I N G\n");
	printf("%%-------------------------------------------------------------------------%%\n\n\n");
	printf("** Level Pemain : %d\n", fish_playerLevel);
	printf("** Uang Pemain  : $%d\n\n", fish_money);
	printf(">> Nama Pemain  : %s\n", fish_playerName);
	printf("## Pancingan    : %s\n", fish_playerFishingEquipment);
	printf("## Total Umpan  : %d\n\n", fish_numBait);
	printf("X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X\n\n");
	char decision;
	printf("Pilih Menu Dibawah Ini Untuk Melanjutkan : \n");
	printf("A. Upgrade Pancingan\n");
	printf("B. Beli Umpan\n");
	printf("C. Kembali ke Menu Utama\n\n");
	do{
		getchar();
		printf("Pilihan [A..C] : ");
		scanf("%c", &decision);
	}while(decision!='A' && decision!='B' && decision!='C');
	switch(decision){
		case 'A':
			system("cls");
			fish_upgrade();
			break;
		case 'B':
			system("cls");
			fish_buy();
			break;
		case 'C':
			return;
			break;
	}
}
void fish_sell(){
	fish_logo();
	printf("3. J U A L  I K A N\n");
	printf("%%-----------------%%\n\n\n");
	printf("** Uang Pemain  : $%d\n\n", fish_money);
	printf(">> Nama Pemain  : %s\n", fish_playerName);
	printf("Total Penjualan Ikan : $%d\n", fish_currFishWorth);
	printf("==========================================\n");
	printf("::    Nama Ikan    ::    Jumlah Ikan    ::\n");
	printf("==========================================\n");
	printf("::    Guppy Blue   ::         %d        ::\n", fish_fishes[0]);
	printf("::    Apple Snail  ::         %d        ::\n", fish_fishes[1]);
	printf("::    Guppy Yellow ::         %d        ::\n", fish_fishes[2]);
	printf("::    Snake Snail  ::         %d        ::\n", fish_fishes[3]);
	printf("::    Flag Fish    ::         %d        ::\n", fish_fishes[4]);
	printf("::    Clown Fish   ::         %d        ::\n", fish_fishes[5]);
	printf("::    Tuna         ::         %d        ::\n", fish_fishes[6]);
	printf("::    Tiger Shark  ::         %d        ::\n", fish_fishes[7]);
	printf("::    White Shark  ::         %d        ::\n", fish_fishes[8]);
	printf("::    Whale        ::         %d        ::\n", fish_fishes[9]);
	printf("==========================================\n\n");
	char choice[5];
	printf("Ketik:\n");
	printf("      [JUAL] untuk menjual seluruh tangkapan\n");
	printf("      [EXIT] untuk kembali ke Menu Utama\n");
	do{
		printf("Masukkan Pilihan Anda : ");
		scanf("%s", choice);
	}while(strcmp(choice, "JUAL")!=0 && strcmp(choice, "EXIT")!=0 );
	if(strcmp(choice, "JUAL")==0){
		printf("\n\nAnda Telah Berhasil Menjual Ikan Sebesar $%d..\n", fish_currFishWorth);
		fish_money+=fish_currFishWorth;
		fish_currFishWorth=0;
		for(int i=0;i<10;i++){
			fish_fishes[i]=0;
		}
		printf("Uang Anda Sekarang Adalah $%d..\n\n\n", fish_money);
		printf("Tekan ENTER untuk KEMBALI KE MENU UTAMA...");
		getchar();
		getchar();	
		return;
	}
	else if(strcmp(choice, "EXIT")==0){
		return;
	}
}
void fish_rebound(){
	fish_logo();
	printf("2. P A N C I N G  I K A N\n");
	printf("%%------------------------%%\n\n\n");
	printf("Maaf fish_numBait anda sudah habis..^^\n");
	printf("Silahkan Perbanyak kembali Umpan Anda di Menu 4..^^\n");
	printf("List Hasil Tangkapan Ikan Anda dapat dilihat Pada Menu 3...\n");
	printf("Tekan ENTER untuk KEMBALI KE MENU UTAMA...");
	getchar();
	getchar();
	return;
}
void fish_fishing(){
	fish_logo();
	printf("2. P A N C I N G  I K A N\n");
	printf("%%------------------------%%\n\n\n");
	fish_numBait--;
	printf("** Level Pemain : %d\n", fish_playerLevel);
	printf(">> Nama Pemain  : %s\n", fish_playerName);
	printf("## Total Umpan  : %d\n\n", fish_numBait);
	int price;
	char yue[25];
	int ikan;
	if(fish_playerLevel==1){
		ikan = rand()%3;
	}
	else if(fish_playerLevel==2){
		ikan = rand()%5;
	}
	else if(fish_playerLevel==3){
		ikan = rand()%7;
	}
	else if(fish_playerLevel==4){
		ikan = rand()%9;
	}
	else if(fish_playerLevel==5){
		ikan = rand()%10;
	}
	if(ikan==0){
		price = 30;
		strcpy(yue, "Guppy Blue");
		fish_currFishWorth+=30;
		fish_fishes[ikan]++;
	}
	else if(ikan==1){
		price = 40;
		strcpy(yue, "Apple Snail");
		fish_currFishWorth+=40;
		fish_fishes[ikan]++;
	}
	else if(ikan==2){
		price = 50;
		strcpy(yue, "Guppy Yellow");
		fish_currFishWorth+=50;
		fish_fishes[ikan]++;
	}
	else if(ikan==3){
		price = 60;
		strcpy(yue, "Snake Snail");
		fish_currFishWorth+=60;
		fish_fishes[ikan]++;
	}
	else if(ikan==4){
		price = 70;
		strcpy(yue, "Flag Fish");
		fish_currFishWorth+=70;
		fish_fishes[ikan]++;
	}
	else if(ikan==5){
		price = 80;
		strcpy(yue, "Clown Fish");
		fish_currFishWorth+= 80;
		fish_fishes[ikan]++;
	}
	else if(ikan==6){
		price = 90;
		strcpy(yue, "Tuna");
		fish_currFishWorth += 90;
		fish_fishes[ikan]++;
	}
	else if(ikan==7){
		price = 100;
		strcpy(yue, "Tiger Shark");
		fish_currFishWorth += 100;
		fish_fishes[ikan]++;
	}
	else if(ikan==8){
		price = 110;
		strcpy(yue, "White Shark");
		fish_currFishWorth+=110;
		fish_fishes[ikan]++;
	}
	else if(ikan==9){
		price = 120;
		strcpy(yue, "Whale");
		fish_currFishWorth+=120;
		fish_fishes[ikan]++;
	}
	printf("Anda berhasil mendapatkan %s, seharga $%d...^^\n", yue, price);
	printf("Total Penjualan Ikan : $%d\n", fish_currFishWorth);
	printf("List Hasil Tangkapan Ikan Anda dapat dilihat Pada Menu 3...\n");
	printf("Tekan ENTER untuk KEMBALI KE MENU UTAMA...");
	getchar();
	getchar();
	return;
}
void fish_profile(){
	system("cls");
	fish_logo();
	printf("1. L I H A T  P R O F I L E  P E M A I N\n");
	printf("%%--------------------------------------%%\n\n\n");
	printf("** Level Pemain : %d\n", fish_playerLevel);
	printf("** Uang Pemain  : $%d\n\n", fish_money);
	printf(">> Nama Pemain  : %s\n", fish_playerName);
	printf(">> Jenis Kelamin: ");
	if(fish_playerGender=='L')printf("Laki-laki\n\n");
	else printf("Perempuan\n\n");
	printf("## Pancingan    : %s\n", fish_playerFishingEquipment);
	printf("## Total Umpan  : %d\n\n", fish_numBait);
	printf("Tekan ENTER untuk KEMBALI KE MENU UTAMA...");
	getchar();
	getchar();
	return;
}
void fish_mainmenu(){
	int pilihan;
	do{
		system("cls");
		printf(" M E N U  U T A M A\n");
		printf("%%-----------------%%\n\n\n");
		printf("1. Lihat profil pemain.\n");
		printf("2. Pancing ikan.\n");
		printf("3. Jual ikan.\n");
		printf("4. Belanja/Upgrade perlengkapan memancing.\n");
		printf("5. Keluar.\n");
		do{
			printf("Pilihan [1...5] : ");
			scanf("%d", &pilihan);
		}while(pilihan<1 && pilihan>5);
		switch(pilihan){
			case 1:
				system("cls");
				fish_profile();
				break;
			case 2:
				system("cls");
				if(fish_numBait<=0)fish_rebound();
				else fish_fishing();
				break;
			case 3:
				system("cls");
				fish_sell();
				break;
			case 4:
				system("cls");
				fish_levelingup();
				break;
			case 5:
				break;
		}
		system("cls");
	}while(pilihan!=5);
	
	
}
void fish_game(){
	system("cls");
	fish_logo();
	for(int i=0;i<10;i++){
		fish_fishes[i]=0;
	}
	printf("F O R M  P E N D A F T A R A N\n");
	printf("%%----------------------------%%\n\n\n");
	printf("*) Nama[2...25] : ");
	scanf("%[^\n]", fish_playerName);
	do{
		getchar();
		printf("*) Jenis Kelamin [L / P] : ");
		scanf("%c", &fish_playerGender);
	}while(fish_playerGender!='L' && fish_playerGender!='P');
	printf("Tekan ENTER untuk MASUK KE MENU UTAMA...");
	getchar();
	getchar();
	system("cls");
	fish_mainmenu();
	return;
}

