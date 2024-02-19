#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LINE 28
#define COL 120

char console[LINE][COL];
char equipped [LINE][COL];

typedef struct {
	int tip[2];
	int health;
	int bullet[10][2]; // max 10 bullets on screen (with coordinates)
	int last_move;
} ROCKET;

ROCKET rocket;

// int bullet[2];

typedef struct {
	int tip[2];
	int health;
} AIR_MINE;

typedef struct {
	int tip[2];
	int health;
} CARGO_SHIP;

typedef struct {
	int tip[2];
	int health;
	bool side; // side = true -> right | side = false -> left
	int bombs[10][2];
} BOMBER;

typedef struct {
	int tip[2];
	int health;
	int bullet[10][2];
} FIGHTER;

AIR_MINE air_mine[10];
CARGO_SHIP cargo_ship[10];
BOMBER bomber;
FIGHTER fighter[10];
time_t start, end;
long int score;
int difficulty = 1;

int menu() {
	printf("\n\n\n\n\n\n\n");
	printf("                                            _ __ ___   ___ _ __  _   _ \n");
	printf("                                           | '_ ` _ \\ / _ \\ '_ \\| | | |\n");
	printf("                                           | | | | | |  __/ | | | |_| |\n");
	printf("                                           |_| |_| |_|\\___|_| |_|\\__,_|\n\n");
	printf("                                                      <PLAY>\n");
	printf("                                                       LOGS\n");
	printf("                                                       LEVEL\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	char c;
	int choice = 1;
	int final = 0;
	while(c != 13) {
		c = getch();
		switch (c) {
			case 119: // w (up)
				if (choice == 1) { choice = 3;}
				else {choice--;}
				printf("\n");
				break;
			case 115: // s (down)
				if (choice == 3) { choice = 1;} 
				else { choice++;}
				printf("\n");
				break;
			case 13: // enter
				break;
			default:
				printf("Invalid key. Use s for down and w for up.\n");
		}
		switch (choice) {
			case 1:
				system("cls");
				printf("\n\n\n\n\n\n\n");
				printf("                                            _ __ ___   ___ _ __  _   _ \n");
				printf("                                           | '_ ` _ \\ / _ \\ '_ \\| | | |\n");
				printf("                                           | | | | | |  __/ | | | |_| |\n");
				printf("                                           |_| |_| |_|\\___|_| |_|\\__,_|\n\n");
				printf("                                                      <PLAY>\n");
				printf("                                                       LOGS\n");
				printf("                                                       LEVEL\n");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n");
				break;
			case 2:
				system("cls");
				printf("\n\n\n\n\n\n\n");
				printf("                                            _ __ ___   ___ _ __  _   _ \n");
				printf("                                           | '_ ` _ \\ / _ \\ '_ \\| | | |\n");
				printf("                                           | | | | | |  __/ | | | |_| |\n");
				printf("                                           |_| |_| |_|\\___|_| |_|\\__,_|\n\n");
				printf("                                                       PLAY\n");
				printf("                                                      <LOGS>\n");
				printf("                                                       LEVEL\n");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n");
				break;
			case 3:
				system("cls");
				printf("\n\n\n\n\n\n\n");
				printf("                                            _ __ ___   ___ _ __  _   _ \n");
				printf("                                           | '_ ` _ \\ / _ \\ '_ \\| | | |\n");
				printf("                                           | | | | | |  __/ | | | |_| |\n");
				printf("                                           |_| |_| |_|\\___|_| |_|\\__,_|\n\n");
				printf("                                                       PLAY\n");
				printf("                                                       LOGS\n");
				printf("                                                      <LEVEL>\n");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n");
				break;
		}
		final = choice;
 	}
	return final;
}

unsigned long long current_timestamp() {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	ULARGE_INTEGER timestamp;
	timestamp.LowPart = ft.dwLowDateTime;
	timestamp.HighPart = ft.dwHighDateTime;
	unsigned long long milliseconds = timestamp.QuadPart / 10000ULL;
	return milliseconds;
}

void end_game() {
	system("cls"); 
	end = time(NULL); 
	printf("\n\n\n\n\n");
	printf("                                               >>==================<<\n");
	printf("                                               ||                _ ||\n");
	printf("                                               ||  ___ _ __   __| |||\n");
	printf("                                               || / _ \\ '_ \\ / _` |||\n");
	printf("                                               |||  __/ | | | (_| |||\n");
	printf("                                               || \\___|_| |_|\\__,_|||\n");
	printf("                                               >>==================<<\n");
	printf("                                                  YOUR SCORE: %ld\n\n", score);
	printf("                                             (Press any key to continue)\n");
	getch();
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("                                                  What's you name?\n");
	printf("                                                  ");
	char name[20];
	fgets(name, 20, stdin);
	name[strlen(name) - 1] = '\0';
	FILE *logs = fopen("logs.txt", "a");
	fprintf(logs, "PLAYER: %s\tSCORE: %ld\tTIME SPENT: %.0f seconds\tDATE: %s\n", name, score, difftime(end, start), ctime(&start));
	fclose(logs);
}

void countdown() {
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("                                               TO MOVE ROCKET, USE\n");
	printf("                                                     ____ \n");
	printf("                                                    ||w ||\n");
	printf("                                                    ||__||\n");
	printf("                                                    |/__\\|\n");
	printf("                                                ____ ____ ____ \n");
	printf("                                               ||a |||s |||d ||\n");
	printf("                                               ||__|||__|||__||\n");
	printf("                                               |/__\\|/__\\|/__\\|\n");
	Sleep(3000);
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("                                                  TO SHOOT, USE\n");
	printf("                                                __________________ \n");
	printf("                                               ||    spacebar    ||\n");
	printf("                                               ||________________||\n");
	printf("                                               |/________________\\|\n");
	Sleep(3000);
	system("cls");
	printf("\n\n\n");
	printf("                                                               _          \n");
	printf("                                            _ __ ___  __ _  __| |_   _    \n");
	printf("                                           | '__/ _ \\/ _` |/ _` | | | |  \n");
	printf("                                           | | |  __/ (_| | (_| | |_| |_  \n");
	printf("                                           |_|  \\___|\\__,_|\\__,_|\\__, ( ) \n");
	printf("                                                                 |___/|/  \n");
	Sleep(1000);
	printf("                                                     _\n");
	printf("                                            ___  ___| |_  \n");
	printf("                                           / __|/ _ \\ __|                 \n");
	printf("                                           \\__ \\  __/ |_ _                \n");
	printf("                                           |___/\\___|\\__( )               \n");
	printf("                                                        |/         \n");
	Sleep(1000);
	printf("                                             ____  ___  _   \n");
	printf("                                            / ___|/ _ \\| |                \n");
	printf("                                           | |  _| | | | |                \n");
	printf("                                           | |_| | |_| |_|                \n");
	printf("                                            \\____|\\___/(_)                \n");
	Sleep(1000);
}

void print_console() {
	// printf("print console\n"); Sleep(1000);
	if (rocket.health <= 100 && rocket.health > 80) {
		printf("                                                         %ld                                HEALTH |*****|\n", score);
	}
	else if (rocket.health <= 80 && rocket.health > 60) {
		printf("                                                         %ld                                HEALTH |**** |\n", score);
	}
	else if (rocket.health <= 60 && rocket.health > 40) {
		printf("                                                         %ld                                HEALTH |***  |\n", score);
	}
	else if (rocket.health <= 400 && rocket.health > 20) {
		printf("                                                         %ld                                HEALTH |**   |\n", score);
	}
	else if (rocket.health <= 20 && rocket.health > 0) {
		printf("                                                         %ld                                HEALTH |*    |\n", score);
	}
	else {end_game(); exit(-1);}

	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%c", console[i][j]);
		}
		printf("\n");
	}
}

int are_you_sure() {
	end = time(NULL); // if the player decides to end game, we should keep the time
	                  // if player changes their decision, we change the end time later
	system("cls"); 
	printf("\n\n\n\n\n\n\n");
	printf("                                              Are you sure you want to quit?\n");
	printf("                                                           <Yes>\n");
	printf("                                                            No  \n");

	char c;
	int choice = 1;
	int final = 0;
	while(c != 13) {
		c = getch();
		switch (c) {
			case 119: // w (up)
				if (choice == 1) { choice = 2;}
				else {choice--;}
				printf("\n");
				break;
			case 115: // s (down)
				if (choice == 2) { choice = 1;} 
				else { choice++;}
				printf("\n");
				break;
			default:
				printf("Invalid key. Use s for down and w for up.\n");
		}
		switch (choice) {
			case 1:
				system("cls"); 
				printf("\n\n\n\n\n\n\n");
				printf("                                              Are you sure you want to quit?\n");
				printf("                                                           <Yes>\n");
				printf("                                                            No  \n");
				break;
			case 2:
				system("cls"); 
				printf("\n\n\n\n\n\n\n");
				printf("                                              Are you sure you want to quit?\n");
				printf("                                                            Yes\n");
				printf("                                                           <No>  \n");
				break;
		}
		final = choice;
 	}
	return final;
}

void init_console() {
	// printf("init_console\n"); Sleep(1000);
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COL; j++) {
			console[i][j] = ' ';
		}
	}
}

void init_equipped() {
	// printf("init_equipped\n"); Sleep(1000);
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COL; j++) {
			equipped[i][j] = '\0';
		}
	}
}

void clear_rocket() {
	// printf("clear_rocket\n"); Sleep(1000);
	int i = rocket.tip[0], j = rocket.tip[1];
	console[i][j] = ' ';
	console[i + 1][j - 1] = ' '; console[i + 1][j] = ' '; console[i + 1][j + 1] = ' ';
	console[i + 2][j - 2] = ' '; console[i + 2][j - 1] = ' '; console[i + 2][j] = ' '; console[i + 2][j + 1] = ' '; console[i + 2][j + 2] = ' ';
	console[i + 3][j - 3] = ' '; console[i + 3][j - 2] = ' '; console[i + 3][j - 1] = ' '; console[i + 3][j] = ' '; console[i + 3][j + 1] = ' '; console[i + 3][j + 2] = ' '; console[i + 3][j + 3] = ' ';
	console[i + 4][j - 1] = ' '; console[i + 4][j] = ' '; console[i + 4][j + 1] = ' ';
	console[i + 5][j + 1] = ' '; console[i + 5][j - 1] = ' '; console[i + 5][j] = ' ';
	equipped[i][j] = '\0';
	equipped[i + 1][j - 1] = '\0'; equipped[i + 1][j] = '\0'; equipped[i + 1][j + 1] = '\0';
	equipped[i + 2][j - 2] = '\0'; equipped[i + 2][j - 1] = '\0'; equipped[i + 2][j] = '\0'; equipped[i + 2][j + 1] = '\0'; equipped[i + 2][j + 2] = '\0';
	equipped[i + 3][j - 3] = '\0'; equipped[i + 3][j - 2] = '\0'; equipped[i + 3][j - 1] = '\0'; equipped[i + 3][j] = '\0'; equipped[i + 3][j + 1] = '\0'; equipped[i + 3][j + 2] = '\0'; equipped[i + 3][j + 3] = '\0';
}

void create_rocket() {
	// printf("create_rocket\n"); Sleep(1000);
	int i = rocket.tip[0], j = rocket.tip[1];
	console[i][j] = '.';
	console[i + 1][j - 1] = '/'; console[i + 1][j] = ' '; console[i + 1][j + 1] = '\\';
	console[i + 2][j - 2] = '|'; console[i + 2][j - 1] = ' '; console[i + 2][j] = '0'; console[i + 2][j + 1] = ' '; console[i + 2][j + 2] = '|';
	console[i + 3][j - 3] = '/'; console[i + 3][j - 2] = '|'; console[i + 3][j - 1] = '_'; console[i + 3][j] = '_'; console[i + 3][j + 1] = '_'; console[i + 3][j + 2] = '|'; console[i + 3][j + 3] = '\\';
	console[i + 4][j - 1] = '*'; console[i + 4][j] = '*'; console[i + 4][j + 1] = '*';
	console[i + 5][j] = '*';
	if (rocket.last_move == -1) {console[i + 5][j + 1] = '*';}
	else if (rocket.last_move == 1) {console[i + 5][j - 1] = '*';}
	equipped[i][j] = '1';
	equipped[i + 1][j - 1] = '1'; equipped[i + 1][j] = '1'; equipped[i + 1][j + 1] = '1';
	equipped[i + 2][j - 2] = '1'; equipped[i + 2][j - 1] = '1'; equipped[i + 2][j] = '1'; equipped[i + 2][j + 1] = '1'; equipped[i + 2][j + 2] = '1';
	equipped[i + 3][j - 3] = '1'; equipped[i + 3][j - 2] = '1'; equipped[i + 3][j - 1] = '1'; equipped[i + 3][j] = '1'; equipped[i + 3][j + 1] = '1'; equipped[i + 3][j + 2] = '1'; equipped[i + 3][j + 3] = '1';
	return;
}

void init_rocket() {
	// printf("init_rocket\n"); Sleep(1000);
	rocket.tip[0] = LINE - 7; rocket.tip[1] = COL / 2;
	create_rocket();
}

void clear_air_mine(int slot) {
	// printf("clear air mine \n"); Sleep(1000);
	int i = air_mine[slot].tip[0], j = air_mine[slot].tip[1];
	if (i < LINE) {
		console[i][j - 1] = ' '; console[i][j] = ' '; console[i][j + 1] = ' ';
		equipped[i][j - 1] = '\0'; equipped[i][j] = '\0'; equipped[i][j + 1] = '\0';
	}
	if (i + 1 < LINE) {
	    console[i + 1][j - 3] = ' '; console[i + 1][j - 2] = ' '; console[i + 1][j - 1] = ' '; console[i + 1][j] = ' '; console[i + 1][j + 1] = ' '; console[i + 1][j + 2] = ' '; console[i + 1][j + 3] = ' ';
		equipped[i + 1][j - 3] = '\0'; equipped[i + 1][j - 2] = '\0'; equipped[i + 1][j - 1] = '\0'; equipped[i + 1][j] = '\0'; equipped[i + 1][j + 1] = '\0'; equipped[i + 1][j + 2] = '\0'; equipped[i + 1][j + 3] = '\0';
	}
	if (i + 2 < LINE) {
		console[i + 2][j - 3] = ' '; console[i + 2][j - 2] = ' '; console[i + 2][j - 1] = ' '; console[i + 2][j] = ' '; console[i + 2][j + 1] = ' '; console[i + 2][j + 2] = ' '; console[i + 2][j + 3] = ' ';
		equipped[i + 2][j - 3] = '\0'; equipped[i + 2][j - 2] = '\0'; equipped[i + 2][j - 1] = '\0'; equipped[i + 2][j] = '\0'; equipped[i + 2][j + 1] = '\0'; equipped[i + 2][j + 2] = '\0'; equipped[i + 2][j + 3] = '\0';
	}
	return;
}

void create_air_mine(int slot) {
	// printf("create air mine \n"); Sleep(1000);
	int i = air_mine[slot].tip[0], j = air_mine[slot].tip[1];
	if (i < LINE) {
		console[i][j - 1] = '_'; console[i][j] = '_'; console[i][j + 1] = '_';
		equipped[i][j - 1] = '1'; equipped[i][j] = '1'; equipped[i][j + 1] = '1';
	}
	if (i + 1 < LINE) {
	    console[i + 1][j - 3] = '<'; console[i + 1][j - 2] = '('; console[i + 1][j - 1] = ' '; console[i + 1][j] = '*'; console[i + 1][j + 1] = ' '; console[i + 1][j + 2] = ')'; console[i + 1][j + 3] = '>';
		equipped[i + 1][j - 3] = '1'; equipped[i + 1][j - 2] = '1'; equipped[i + 1][j - 1] = '1'; equipped[i + 1][j] = '1'; equipped[i + 1][j + 1] = '1'; equipped[i + 1][j + 2] = '1'; equipped[i + 1][j + 3] = '1';
	}
	if (i + 2 < LINE) {
		console[i + 2][j - 3] = '<'; console[i + 2][j - 2] = '('; console[i + 2][j - 1] = '_'; console[i + 2][j] = '_'; console[i + 2][j + 1] = '_'; console[i + 2][j + 2] = ')'; console[i + 2][j + 3] = '>';
		equipped[i + 2][j - 3] = '1'; equipped[i + 2][j - 2] = '1'; equipped[i + 2][j - 1] = '1'; equipped[i + 2][j] = '1'; equipped[i + 2][j + 1] = '1'; equipped[i + 2][j + 2] = '1'; equipped[i + 2][j + 3] = '1';
	}
}

void check_air_mine() {
	// printf("check air mine \n"); Sleep(1000);
	for (int i = 0; i < 10; i++) {
		if (air_mine[i].tip[0] >= LINE) {
			clear_air_mine(i); air_mine[i].tip[0] = air_mine[i].tip[1] = 0; air_mine[i].health = 0;
		}
		else if (((air_mine[i].tip[0] + 2) >= rocket.tip[0] && rocket.tip[1] < air_mine[i].tip[1] + 5 && rocket.tip[1] > air_mine[i].tip[1] - 5)) {
			rocket.health -= 20; clear_air_mine(i); air_mine[i].tip[0] = air_mine[i].tip[1] = 0; air_mine[i].health = 0;
		}
		else if (air_mine[i].tip[0] > 0 && air_mine[i].tip[0] < LINE) {
			clear_air_mine(i);
			air_mine[i].tip[0] += 1;
			create_air_mine(i);
		}
	}
	return;
}

void init_air_mine() {
	// printf("init air mine \n"); Sleep(1000);
	srand(current_timestamp());
	if (rand() % (20 / difficulty) != 0) {return;}
	for (int i = 0; i < 10; i++) { 
		if (air_mine[i].health == 0) { // check for empty slots
			air_mine[i].tip[0] = 1; 
			air_mine[i].tip[1] = rand() % 110 + 5; 
			air_mine[i].health = 100;
			for (int j = 0; j < i; j++) { 
				if (air_mine[j].tip[0] < 3 && air_mine[j].tip[1] < air_mine[i].tip[1] + 2 && air_mine[j].tip[1] > air_mine[i].tip[1] - 2) { // prevent them overlapping
					air_mine[i].tip[0] = 0; air_mine[i].tip[1] = 0; air_mine[i].health = 0;
					return;
				}
			}
			create_air_mine(i);
			return;
		}
	}
	return;
}

void clear_cargo_ship(int slot) {
	// printf("clear cargo ship \n"); Sleep(1000);
	int i = cargo_ship[slot].tip[0], j = cargo_ship[slot].tip[1];
	if (i < LINE) {
		console[i][j] = ' ';
		equipped[i][j] = '\0';
	}
	if (i - 1 < LINE) {
		console[i - 1][j - 1] = ' '; console[i - 1][j] = ' '; console[i - 1][j + 1] = ' ';
		equipped[i - 1][j - 1] = '\0'; equipped[i - 1][j] = '\0'; equipped[i - 1][j + 1] = '\0';
	}
	if (i - 2 < LINE) {
		console[i - 2][j - 1] = ' '; console[i - 2][j] = ' '; console[i - 2][j + 1] = ' ';
		equipped[i - 2][j - 1] = '\0'; equipped[i - 2][j] = '\0'; equipped[i - 2][j + 1] = '\0';
	}
	if (i - 3 < LINE) {
		console[i - 3][j - 2] = ' '; console[i - 3][j - 1] = ' '; console[i - 3][j] = ' '; console[i - 3][j + 1] = ' '; console[i - 3][j + 2] = ' ';
		equipped[i - 3][j - 2] = '\0'; equipped[i - 3][j - 1] = '\0'; equipped[i - 3][j] = '\0'; equipped[i - 3][j + 1] = '\0'; equipped[i - 3][j + 2] = '\0';
	}
}

void create_cargo_ship(int slot) {
	// printf("create cargo ship \n"); Sleep(1000);
	int i = cargo_ship[slot].tip[0], j = cargo_ship[slot].tip[1];
	if (i < LINE) {
		console[i][j] = '\'';
		equipped[i][j] = '1';
	}
	if (i - 1 < LINE) {
		console[i - 1][j - 1] = '\\'; console[i - 1][j] = ' '; console[i - 1][j + 1] = '/';
		equipped[i - 1][j - 1] = '1'; equipped[i - 1][j] = '1'; equipped[i - 1][j + 1] = '1';
	}
	if (i - 2 < LINE) {
		console[i - 2][j - 1] = '|'; console[i - 2][j] = '+'; console[i - 2][j + 1] = '|';
		equipped[i - 2][j - 1] = '1'; equipped[i - 2][j] = '1'; equipped[i - 2][j + 1] = '1';
	}
	if (i - 3 < LINE) {
		console[i - 3][j - 2] = '\\'; console[i - 3][j - 1] = '.'; console[i - 3][j] = '_'; console[i - 3][j + 1] = '.'; console[i - 3][j + 2] = '/';
		equipped[i - 3][j - 2] = '1'; equipped[i - 3][j - 1] = '1'; equipped[i - 3][j] = '1'; equipped[i - 3][j + 1] = '1'; equipped[i - 3][j + 2] = '1';
	}
	return;
}

void check_cargo_ship() {
	// printf("check cargo ship \n"); Sleep(1000);
	for (int i = 0; i < 10; i++) {
		if (cargo_ship[i].tip[0] >= LINE + 3) {
			clear_cargo_ship(i); cargo_ship[i].tip[0] = cargo_ship[i].tip[1] = 0; cargo_ship[i].health = 0;
		}
		else if ((cargo_ship[i].tip[0] >= rocket.tip[0] && cargo_ship[i].tip[0] - 3 <= rocket.tip[0] + 5 && rocket.tip[1] < cargo_ship[i].tip[1] + 4 && rocket.tip[1] > cargo_ship[i].tip[1] - 4)) {
			rocket.health -= 20; clear_cargo_ship(i); cargo_ship[i].tip[0] = cargo_ship[i].tip[1] = 0; cargo_ship[i].health = 0;
		}
		else if (cargo_ship[i].tip[0] > 0 && cargo_ship[i].tip[0] < LINE + 3) {
			clear_cargo_ship(i);
			cargo_ship[i].tip[0] += 2;
			create_cargo_ship(i);
		}
	}
	return;
}

void init_cargo_ship() {
	// printf("init cargo ship\n"); Sleep(1000);
	srand(current_timestamp());
	if (rand() % (20 / difficulty) != 1) {return;}
	for (int i = 0; i < 10; i++) { 
		if (cargo_ship[i].tip[0] == 0) { // check for empty slots
			cargo_ship[i].tip[0] = 3; cargo_ship[i].tip[1] = rand() % 114 + 3; 
			cargo_ship[i].health = 100;
			for (int j = 0; j < i; j++) { 
				if (cargo_ship[j].tip[0] < 4 && cargo_ship[j].tip[1] < cargo_ship[i].tip[1] + 3 && cargo_ship[j].tip[1] > cargo_ship[i].tip[1] - 3) { // prevent them overlapping
					cargo_ship[i].tip[0] = 0; cargo_ship[i].tip[1] = 0; cargo_ship[i].health = 0;
					return;
				}
			}
			create_cargo_ship(i);
			return;
		}
	}
	return;
}

void clear_bomber() {
	// printf("clear bomber\n"); Sleep(2000);
	int i = bomber.tip[0], j = bomber.tip[1];
	if (i < LINE) {
		console[i][j - 1] = ' '; console[i][j] = ' '; console[i][j + 1] = ' '; console[i][j + 2] = ' '; console[i][j + 3] = ' ';
		equipped[i][j - 1] = '\0'; equipped[i][j] = '\0'; equipped[i][j + 1] = '\0'; equipped[i][j + 2] = '\0'; equipped[i][j + 3] = '\0';
	}
	if (i + 1 < LINE) {
		console[i + 1][j - 1] = ' '; console[i + 1][j] = ' '; console[i + 1][j + 1] = ' '; console[i + 1][j + 2] = ' '; console[i + 1][j + 3] = ' '; console[i + 1][j + 4] = ' ';
		equipped[i + 1][j - 1] = '\0'; equipped[i + 1][j] = '\0'; equipped[i + 1][j + 1] = '\0'; equipped[i + 1][j + 2] = '\0'; equipped[i + 1][j + 3] = '\0'; equipped[i + 1][j + 4] = '\0';
	}
	if (i + 2 < LINE ) {
		console[i + 2][j - 1] = ' '; console[i + 2][j] = ' '; console[i + 2][j + 1] = ' '; console[i + 2][j + 2] = ' '; console[i + 2][j + 3] = ' '; console[i + 2][j + 4] = ' ';
		equipped[i + 2][j - 1] = '\0'; equipped[i + 2][j] = '\0'; equipped[i + 2][j + 1] = '\0'; equipped[i + 2][j + 2] = '\0'; equipped[i + 2][j + 3] = '\0'; equipped[i + 2][j + 4] = '\0';
	}
	if (i + 3 < LINE ) {
		console[i + 3][j - 1] = ' '; console[i + 3][j] = ' '; console[i + 3][j + 1] = ' '; console[i + 3][j + 2] = ' '; console[i + 3][j + 3] = ' ';
		equipped[i + 3][j - 1] = '\0'; equipped[i + 3][j] = '\0'; equipped[i + 3][j + 1] = '\0'; equipped[i + 3][j + 2] = '\0'; equipped[i + 3][j + 3] = '\0';
	}
}

void create_bomber() {
	// printf("create bomber\n"); Sleep(2000);
	int i = bomber.tip[0], j = bomber.tip[1];
	if (i < LINE && j + 4 < COL && j - 1 > -1) {
		console[i][j - 1] = ' '; console[i][j] = '_'; console[i][j + 1] = '_'; console[i][j + 2] = '_'; console[i][j + 3] = '_';
		equipped[i][j - 1] = '1'; equipped[i][j] = '1'; equipped[i][j + 1] = '1'; equipped[i][j + 2] = '1'; equipped[i][j + 3] = '1';
	}
	if (i + 1 < LINE && j + 4 < COL && j - 1 > -1) {
		console[i + 1][j - 1] = '|'; console[i + 1][j] = 'B'; console[i + 1][j + 1] = 'O'; console[i + 1][j + 2] = 'M'; console[i + 1][j + 3] = 'B'; console[i + 1][j + 4] = '|';
		equipped[i + 1][j - 1] = '1'; equipped[i + 1][j] = '1'; equipped[i + 1][j + 1] = '1'; equipped[i + 1][j + 2] = '1'; equipped[i + 1][j + 3] = '1'; equipped[i + 1][j + 4] = '1';
	}
	if (i + 2 < LINE && j + 4 < COL && j - 1 > -1) {
		console[i + 2][j - 1] = '('; console[i + 2][j] = ' '; console[i + 2][j + 1] = ' '; console[i + 2][j + 2] = ' '; console[i + 2][j + 3] = ' '; console[i + 2][j + 4] = ')';
		equipped[i + 2][j - 1] = '1'; equipped[i + 2][j] = '1'; equipped[i + 2][j + 1] = '1'; equipped[i + 2][j + 2] = '1'; equipped[i + 2][j + 3] = '1'; equipped[i + 2][j + 4] = '1';
	}
	if (i + 3 < LINE && j + 4 < COL && j - 1 > -1) {
		console[i][j - 1] = ' '; console[i + 3][j] = '\''; console[i + 3][j + 1] = '\''; console[i + 3][j + 2] = '\''; console[i + 3][j + 3] = '\'';
		equipped[i][j - 1] = '1'; equipped[i + 3][j] = '1'; equipped[i + 3][j + 1] = '1'; equipped[i + 3][j + 2] = '1'; equipped[i + 3][j + 3] = '1';
	}
}

void check_bomber() {
	// printf("check bomber\n"); Sleep(500);
	if (bomber.tip[0] + 3 >= rocket.tip[0] && bomber.tip[0] <= rocket.tip[0] + 5 && bomber.tip[1] - 3 <= rocket.tip[1] && bomber.tip[1] + 6 >= rocket.tip[1]) {
		clear_bomber(); bomber.tip[0] = 0; bomber.tip[1] = 0; bomber.health = 0; rocket.health -= 20;
	}
	else if (bomber.tip[0] >= LINE) {
		clear_bomber(); bomber.tip[0] = 0; bomber.tip[1] = 0;
	}
	else if (bomber.tip[1] != 0) {
		if (bomber.side == true) {
			clear_bomber(); bomber.tip[0] += 1; bomber.tip[1] += 4; create_bomber();
		}
		else {
			clear_bomber(); bomber.tip[0] += 1; bomber.tip[1] -= 4; create_bomber();
		}
	}
}

void init_bomber() {
	// printf("init bomber\n"); Sleep(2000);
	srand(current_timestamp());
	if (bomber.tip[1] != 0) {return;}
	if (rand() % (20 / difficulty) == 2) {
		if (rand() % 2 == 0) { // zero means right
			// printf("bomber tip[1] = 0\n"); Sleep(2000);
			bomber.side = true; bomber.tip[0] = 0; bomber.tip[1] = 1; bomber.health = 100;
			create_bomber();
		}
		else {
			bomber.side = false; bomber.tip[0] = 0 ; bomber.tip[1] == COL - 5;
			create_bomber();
		}
	}
}

void clear_bomb(int slot) {
	int i = bomber.bombs[slot][0], j = bomber.bombs[slot][1];
	if (i < LINE) {
		console[i][j - 1] = ' '; console[i][j] = ' '; console[i][j + 1] = ' '; console[i][j + 2] = ' '; console[i][j + 3] = ' ';
		equipped[i][j - 1] = '\0'; equipped[i][j] = '\0'; equipped[i][j + 1] = '\0'; equipped[i][j + 2] = '\0'; equipped[i][j + 3] = '\0';
	}
	if (i + 1 < LINE) {
		console[i + 1][j - 1] = ' '; console[i + 1][j] = ' '; console[i + 1][j + 1] = ' '; console[i + 1][j + 2] = ' ';
		equipped[i + 1][j - 1] = '\0'; equipped[i + 1][j] = '\0'; equipped[i + 1][j + 1] = '\0'; equipped[i + 1][j + 2] = '\0';
	}
}

void create_bomb(int slot) {
	int i = bomber.bombs[slot][0], j = bomber.bombs[slot][1];
	if (i < LINE) {
		console[i][j - 1] = ' '; console[i][j] = '_'; console[i][j + 1] = '_'; console[i][j + 2] = '~'; console[i][j + 3] = '*';
		equipped[i][j - 1] = '1'; equipped[i][j] = '1'; equipped[i][j + 1] = '1'; equipped[i][j + 2] = '1'; equipped[i][j + 3] = '1';
	}
	if (i + 1 < LINE) {
		console[i + 1][j - 1] = '('; console[i + 1][j] = '_'; console[i + 1][j + 1] = '_'; console[i + 1][j + 2] = ')';
		equipped[i + 1][j - 1] = '1'; equipped[i + 1][j] = '1'; equipped[i + 1][j + 1] = '1'; equipped[i + 1][j + 2] = '1';
	}
}

void check_bomb() {
	// printf("check bomb\n"); Sleep(1000);
	for (int i = 0; i < 10; i++) {
		if (bomber.bombs[i][0] + 1 >= rocket.tip[0] && bomber.bombs[i][0] <= rocket.tip[0] + 5 && bomber.bombs[i][1] + 2 <= rocket.tip[1] + 3 && bomber.bombs[i][1] - 1 >= rocket.tip[1] - 3) {
			// printf("bomb %d hit rocket\n", i); Sleep(2000);
			clear_bomb(i); bomber.bombs[i][0] = 0; bomber.bombs[i][1] = 0; rocket.health -= 10;
		}
		else if (bomber.bombs[i][0] >= LINE) {
			clear_bomb(i); bomber.bombs[i][0] = 0; bomber.bombs[i][1] = 0;
		}
		else if (bomber.bombs[i][0] != 0) {
			clear_bomb(i); bomber.bombs[i][0] += 2; create_bomb(i);
		}
	}

}

void init_bombs() {
	// printf("init bombs\n"); Sleep(1000);
	srand(current_timestamp());
	if (bomber.tip[1] != 0 && rand() % 5 == 0) { // bomber exists and we are ready to create bomb
		// printf("init_bomb\n"); Sleep(2000);
		for (int i = 0; i < 10; i++) {
			if (bomber.bombs[i][0] == 0) { // finding empty slots
				// printf("slot %d available\n", i);
				bomber.bombs[i][0] = bomber.tip[0] + 4; bomber.bombs[i][1] = bomber.tip[1] + 1;
				create_bomb(i);
				return;
			}
		}
	}
}

void clear_fighter(int slot) {
	int i = fighter[slot].tip[0], j = fighter[slot].tip[1];
	if (i < LINE) {
		console[i][j] = ' ';
		equipped[i][j] = '\0';
	}
	if (i - 1 < LINE) {
		console[i - 1][j - 1] = ' '; console[i - 1][j] = ' '; console[i - 1][j + 1] = ' ';
		equipped[i - 1][j - 1] = '\0'; equipped[i - 1][j] = '\0'; equipped[i - 1][j + 1] = '\0';
	}
	if (i - 2 < LINE) {
		console[i - 2][j - 1] = ' '; console[i - 2][j] = ' '; console[i - 2][j + 1] = ' ';
		equipped[i - 2][j - 1] = '\0'; equipped[i - 2][j] = '\0'; equipped[i - 2][j + 1] = '\0';
	}
	if (i - 3 < LINE) {
		console[i - 3][j - 1] = ' '; console[i - 3][j] = ' '; console[i - 3][j + 1] = ' ';
		equipped[i - 3][j - 1] = '\0'; equipped[i - 3][j] = '\0'; equipped[i - 3][j + 1] = '\0';		
	}
	if (i - 4 < LINE) {
		console[i - 4][j - 2] = ' '; console[i - 4][j - 1] = ' '; console[i - 4][j] = ' '; console[i - 4][j + 1] = ' '; console[i - 4][j + 2] = ' ';
		equipped[i - 4][j - 2] = '\0'; equipped[i - 4][j - 1] = '\0'; equipped[i - 4][j] = '\0'; equipped[i - 4][j + 1] = '\0'; equipped[i - 4][j + 2] = '\0';
	}
	return;
}

void create_fighter(int slot) {
	int i = fighter[slot].tip[0], j = fighter[slot].tip[1];
	if (i < LINE) {
		console[i][j] = '*';
		equipped[i][j] = '1';
	}
	if (i - 1 < LINE) {
		console[i - 1][j - 1] = '\\'; console[i - 1][j] = ' '; console[i - 1][j + 1] = '/';
		equipped[i - 1][j - 1] = '1'; equipped[i - 1][j] = '1'; equipped[i - 1][j + 1] = '1';
	}
	if (i - 2 < LINE) {
		console[i - 2][j - 1] = '|'; console[i - 2][j] = '='; console[i - 2][j + 1] = '|';
		equipped[i - 2][j - 1] = '1'; equipped[i - 2][j] = '1'; equipped[i - 2][j + 1] = '1';
	}
	if (i - 3 < LINE) {
		console[i - 3][j - 1] = '|'; console[i - 3][j] = '='; console[i - 3][j + 1] = '|';
		equipped[i - 3][j - 1] = '1'; equipped[i - 3][j] = '1'; equipped[i - 3][j + 1] = '1';		
	}
	if (i - 4 < LINE) {
		console[i - 4][j - 2] = '\\'; console[i - 4][j - 1] = '\\'; console[i - 4][j] = '_'; console[i - 4][j + 1] = '/'; console[i - 4][j + 2] = '/';
		equipped[i - 4][j - 2] = '1'; equipped[i - 4][j - 1] = '1'; equipped[i - 4][j] = '1'; equipped[i - 4][j + 1] = '1'; equipped[i - 4][j + 2] = '1';
	}
	return;
}

void check_fighter() {
	// printf("check fighter\n"); Sleep(1000);
	for (int i = 0; i < 10; i ++) {
		if (fighter[i].tip[0] >= rocket.tip[0] && fighter[i].tip[0] <= rocket.tip[0] + 6 && fighter[i].tip[1] - 2 <= rocket.tip[1] + 3 && fighter[i].tip[1] + 2 >= rocket.tip[1] - 3) {
			rocket.health -= 20; fighter[i].health = 0; clear_fighter(i); fighter[i].tip[0] = 0; fighter[i].tip[1] = 0;
		}
		else if (fighter[i].tip[0] >= LINE + 4) {
			clear_fighter(i); fighter[i].tip[0] = fighter[i].tip[1] = 0; fighter[i].health = 0;
		}
		else if (fighter[i].tip[0] > 0 && fighter[i].tip[0] < LINE + 3) {
			clear_fighter(i);
			fighter[i].tip[0] += 2;
			create_fighter(i);
		}
	}
}

void init_fighter() {
	// printf("init fighter\n"); Sleep(1000);
	srand (current_timestamp());
	if (rand() % (20 / difficulty) == 4) {
		for (int i = 0; i < 10; i++) {
			if (fighter[i].tip[0] == 0) { // finding empty slots
				fighter[i].tip[0] = 4; fighter[i].tip[1] = rand() % 114 + 3;
				fighter[i].health = 100;
				for (int j = 0; j < 10; j++) {
					if (fighter[j].tip[0] + 2 <= fighter[i].tip[0] - 2 && fighter[j].tip[0] - 2 >= fighter[i].tip[0] + 2 && fighter[j].tip[1] <= 4) {
						fighter[i].tip[0] = 0; fighter[i].tip[1] = 0; fighter[i].health = 0; 
						return;
					} 
				}
				create_fighter(i);
				return;
			}  
		}
	}
	return;
}

void clear_fighter_bullets(int fighter_slot, int bullet_slot) {
	console[fighter[fighter_slot].bullet[bullet_slot][0]][fighter[fighter_slot].bullet[bullet_slot][1]] = ' ';
	return;
}

void create_fighter_bullets(int fighter_slot, int bullet_slot) {
	console[fighter[fighter_slot].bullet[bullet_slot][0]][fighter[fighter_slot].bullet[bullet_slot][1]] = 'v';
	return;
}

void check_fighter_bullets() {
	// printf("check fighter bullets\n"); Sleep(1000);
	for (int  i = 0; i < 10; i++) {
		if (fighter[i].tip[0] != 0) {
			for (int j = 0; j < 10; j++) {
				if (fighter[i].bullet[i][0] != 0) {
					if (fighter[i].bullet[j][0] >= LINE) {
						// printf("case 1\n"); Sleep(1000);
						clear_fighter_bullets(i, j); fighter[i].bullet[j][0] = 0; fighter[i].bullet[j][1] = 0;
					}
					else if (fighter[i].bullet[j][0] >= rocket.tip[0] && fighter[i].bullet[j][0] <= rocket.tip[0] + 6 && fighter[i].bullet[j][1] <= rocket.tip[1] + 3 && fighter[i].bullet[j][1] >= rocket.tip[1] - 3) {
						// printf("case 2\n"); Sleep(1000);
						rocket.health -= 5; clear_fighter_bullets(i, j); fighter[i].bullet[j][0] = 0; fighter[i].bullet[j][1] = 0;
					}
					else if (fighter[i].bullet[j][0] != 0) {
						// printf("case 3\n"); Sleep(1000);
						clear_fighter_bullets(i, j);
						fighter[i].bullet[j][0] += 3; fighter[i].bullet[j][1] = fighter[i].tip[1];
						create_fighter_bullets(i, j);
					} 
				}
			}
		}
	}
}

void init_fighter_bullets() {
	// printf("init fighter bullets\n"); Sleep(1000);
	srand(current_timestamp());
	if (rand() % 3 == 0) {
		// printf("process 1\n"); Sleep(1000);
		int size = 0;
		for (int i = 0; i < 10; i++) {
			if (fighter[i].tip[0] != 0) {
				size++;
			}
		}
		// printf("process 2\n"); Sleep(1000);
		if (size == 0) {return;}
		size = 0;
		int arr[size];
		for (int i = 0; i < 10; i++) {
			if (fighter[i].tip[0] != 0) {
				arr[size] = i; size++;
			}
		}
		// printf("process 3 \n"); Sleep(1000);
		int slot = rand() % size;
		for (int j = 0; j < 10; j++) {
			if (fighter[slot].bullet[j][0] == 0) {
				fighter[slot].bullet[j][0] = fighter[slot].tip[0] + 3; fighter[slot].bullet[j][1] = fighter[slot].tip[1]; create_fighter_bullets(slot, j);
			}
		}
		return;
	}
}

void clear_bullet(int slot) {
	console[rocket.bullet[slot][0]][rocket.bullet[slot][1]] = ' ';
}

void create_bullet(int slot) {
	console[rocket.bullet[slot][0]][rocket.bullet[slot][1]] = '^';
}

void check_bullet() {
	// printf("check bullet\n"); Sleep(1000);
	for (int i = 0; i < 10; i++) {
		if (equipped[rocket.bullet[i][0]][rocket.bullet[i][1]] == '1') {
			if (bomber.tip[0] != 0 && rocket.bullet[i][0] >= bomber.tip[0] && rocket.bullet[i][1] <= bomber.tip[0] + 3 && rocket.bullet[i][1] >= bomber.tip[1] - 1 && rocket.bullet[i][1] <= bomber.tip[1] + 4) {
				clear_bomber(); bomber.health = 0; bomber.tip[0] = 0; bomber.tip[1] = 0;
				clear_bullet(i); rocket.bullet[i][0] = 0; rocket.bullet[i][1] = 0;
				break;
			}
			if (bomber.tip[1] != 0) {
				for (int j = 0; j < 10; j++) {
					if (bomber.bombs[j][0] <= rocket.bullet[i][0] && bomber.bombs[j][0] + 2>= rocket.bullet[i][0] && bomber.bombs[j][1] - 1 >= rocket.bullet[i][0] && bomber.bombs[j][1] + 2 <= rocket.bullet[i][1]) {
						clear_bomb(j); bomber.bombs[j][0] = 0; bomber.bombs[j][1] = 0;
						clear_bullet(i); rocket.bullet[i][0] = 0; rocket.bullet[i][1] = 0;
					}
				}
			}
			for (int j = 0; j < 10; j++) {
				if (air_mine[j].tip[0] != 0 && rocket.bullet[i][0] >= air_mine[j].tip[0] && rocket.bullet[i][0] <= air_mine[j].tip[0] + 2 && rocket.bullet[i][1] < air_mine[j].tip[1] + 4 && rocket.bullet[i][1] > air_mine[j].tip[1] - 4) {
					clear_air_mine(j); air_mine[j].health = 0; air_mine[j].tip[0] = 0; air_mine[j].tip[1] = 0; 
					clear_bullet(i); rocket.bullet[i][0] = 0; rocket.bullet[i][1] = 0;
					break;
				}
				else if (cargo_ship[j].tip[0] != 0 && rocket.bullet[i][0] >= cargo_ship[j].tip[0] - 3 && rocket.bullet[i][0] <= cargo_ship[j].tip[0] && rocket.bullet[i][1] < cargo_ship[j].tip[1] + 3 && rocket.bullet[i][1] > cargo_ship[j].tip[1] - 3) {
					clear_cargo_ship(j); cargo_ship[j].health = 0; cargo_ship[j].tip[0] = 0; cargo_ship[j].tip[1] = 0;
					clear_bullet(i); rocket.bullet[i][0] = 0; rocket.bullet[i][1] = 0;
					break;
				}
				else if (fighter[j].tip[0] != 0 && rocket.bullet[i][0] >= fighter[j].tip[0] - 3 && rocket.bullet[i][0] <= fighter[j].tip[0] && rocket.bullet[i][1] < fighter[j].tip[1] + 3 && rocket.bullet[i][1] > fighter[j].tip[1] - 3) {
					clear_fighter(j); fighter[j].health = 0; fighter[j].tip[0] = 0; fighter[j].tip[1] = 0;
					clear_bullet(i); rocket.bullet[i][0] = 0; rocket.bullet[i][1] = 0;
					break;
				}
			}
		}
		else if (rocket.bullet[i][0] < LINE && rocket.bullet[i][0] > 0) {
			// printf("rocket.bullet[%d][0] < LINE - 6 && rocket.bullet[%d][0] >= 0\n", i, i); Sleep(1000);
			clear_bullet(i); rocket.bullet[i][0] -= 2; create_bullet(i);
		}
		else if (rocket.bullet[i][0] <= 0) {
			clear_bullet(i); rocket.bullet[i][0] = 0; rocket.bullet[i][1] = 0;
		}
	}
}

void init_bullet() {
	for (int i = 0; i < 10; i++) { // finding empty slots
		if (rocket.bullet[i][0] == 0) {
			rocket.bullet[i][0] = rocket.tip[0] - 1; rocket.bullet[i][1] = rocket.tip[1];
			create_bullet(i);
			return;
		}
	}
	return;
}

void play() {

	printf("\33[?25l"); // hide cursor

	system("cls"); // clear screen

	countdown();

	init_equipped();
	init_console(); 
	init_rocket(); // rocket in the middle
	rocket.health = 100;
	bomber.tip[0] = 0; bomber.tip[1] = 0;

	start = time(NULL);

	while (1) {
		Sleep(200);
		score++; // 5 times per second
		Sleep(200); 

		difficulty = difftime(time(NULL), start) / 60 + 1;

		system("cls");

		create_bomber();
		create_rocket();
		print_console();

		rocket.last_move = 0;

		if (_kbhit()) { // key pressed?
			char c = getch();
			if (c == 'a') { // move left
				clear_rocket();
				rocket.tip[1] -= 2;
				if (rocket.tip[1] > COL - 3 || rocket.tip[1] < 3) {rocket.tip[1] += 2;}
				rocket.last_move = -1;
				create_rocket();
			}  
			else if (c == 'd') { // move right
				clear_rocket();
				rocket.tip[1] += 2;
				if (rocket.tip[1] > COL - 3 || rocket.tip[1] < 3) {rocket.tip[1] -= 2;}
				rocket.last_move = 1;
				create_rocket();
			}
			else if (c == 's') { // move down
				clear_rocket();
				rocket.tip[0] += 1;
				if (rocket.tip[0] < 0 || rocket.tip[0] + 5 >= LINE) {rocket.tip[0] -= 1;}
				create_rocket();
			}
			else if (c == 'w') { // move up
				clear_rocket();
				rocket.tip[0] -= 1;
				if (rocket.tip[0] < 0 || rocket.tip[0] + 5 >= LINE) {rocket.tip[0] += 1;}
				create_rocket();
			}
			else if (c == 'q') { // quit
				if (are_you_sure() == 1) {
					end_game();
					exit(-1);
				}
			}
			else if (c = ' ') { // shoot
				init_bullet();
			}
		}
		
		check_bullet();
		check_bomber();
		check_bomb();
		check_air_mine();
		check_cargo_ship();
		check_fighter();
		check_fighter_bullets();

		init_bomber();
		init_bombs();
		init_air_mine();
		init_cargo_ship();
		init_fighter();
		init_fighter_bullets();
	}
	printf("\33[?25h");
}

void logs() {
	system("cls");
	FILE *logs = fopen("logs.txt", "r");
	char logs_line[300];
	while (fgets(logs_line, 300, logs) != NULL) {
		printf("%s", logs_line);
	}
	fclose(logs);
	getch();
	return;
}

void level() {
	printf("\n\n\n\n\n\n\n\n\n");
	printf("                                                      LEVEL\n\n");
}

int main(void) {
	
	int final = menu();
	switch (final) {
		case 1:
			play();
			break;
		case 2:
			logs();
			break;
		case 3:
			level();
			break;
	}
	return 0;
}