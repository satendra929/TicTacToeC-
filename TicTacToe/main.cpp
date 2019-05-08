#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <Windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//Current position
int cursor = 0;
int blinker = 0;


void printStatus(int* status);
void setCursorPosition(int x, int y);
int checkWinner(int* status);

void main() {
	int* status = (int*)malloc(9 * sizeof(int));
	//int* prestat = (int*)malloc(9 * sizeof(int));
	int i;
	for (i = 0; i < 9; i++) {
		status[i] = -1;
		//prestat[i] = -1;
	}
	printStatus(status);

	while (true) {
		int result = checkWinner(status);
		if (result != -1) {
			if (result == 1) {
				std::cout << "X wins";
				break;
			}
			else {
				std::cout << "O wins";
				break;
			}
		}
		//not recommended to use this
		//system("CLS");
		//std::cout << std::string(50,'\n');
		char input = _getch();

		switch (input)
		{
		case 'x':
			status[cursor] = 1;
			break;
		case 'o':
			status[cursor] = 0;
			break;
		//cursor cases
		case KEY_UP:
			//up
			if (cursor > 2) {
				cursor = cursor - 3;
			}
			break;
		case KEY_DOWN:
			//down
			if (cursor < 6) {
				cursor = cursor + 3;
			}
			break;
		case KEY_RIGHT:
			//right
			if (cursor < 8) {
				cursor++;
			}
			break;
		case KEY_LEFT:
			//left
			if (cursor > 0) {
				cursor--;
			}
			break;
		default:
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
		printStatus(status);
	}
}

void printStatus(int *status) {
	setCursorPosition(0, 0);
	int i;
	int everyThree = 0;
	for (i = 0; i < 9; i++) {
		if (i == cursor) {
			std::cout << "*|";
		}
		else {
			if (status[i] == -1) {
				std::cout << " |";
			}
			else {
				if (status[i] == 0) {
					std::cout << "O";
				}
				else {
					std::cout << "X";
				}
				std::cout << "|";
			}
		}
		
		if (everyThree == 2) {
			std::cout << std::endl;
			std::cout << "_ _ _" << std::endl;
			everyThree = -1;
		}
		everyThree++;
	}
}

void setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x , (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

int checkWinner(int* status) {
	//vertical
	int i, j;
	for (i = 0; i < 3; i++) {
		int temp = status[i];
		for (j = 1; j < 3; j++) {
			if (status[i+j*3] != temp) {
				break;
			}
		}
		return status[i] ;
	}
	//horizontal
	for (i = 0; i < 3; i++) {
		int temp = status[i];
		for (j = 1; j < 3; j++) {
			if (status[i + j] != temp) {
				break;
			}
		}
	}
	//diagonal
	if (status[0] == status[4] && status[4] == status[8]) {
		return status[0];
	}
	if (status[2] == status[4] && status[4] == status[6]) {
		return status[2];
	}
	return -1;
}