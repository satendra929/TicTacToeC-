#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <Windows.h>

//Current position
int cursor = 0;
int blinker = 0;


void printStatus(int* status, int *prestat);
void setCursorPosition(int x, int y);

void main() {
	int* status = (int*)malloc(9 * sizeof(int));
	int* prestat = (int*)malloc(9 * sizeof(int));
	int i;
	for (i = 0; i < 9; i++) {
		status[i] = -1;
		prestat[i] = -1;
	}
	printStatus(status, prestat);

	while (true) {
		//not recommended to use this
		//system("CLS");
		//std::cout << std::string(50,'\n');
		char input = _getch();

		switch (input)
		{
		case 'x':
			status[0] = 0;
			break;
		case 'c':
			status[0] = 1;
			break;
		default:
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
		printStatus(status, prestat);
	}
}

void printStatus(int *status, int *prestat) {
	setCursorPosition(0, 0);
	int i;
	int everyThree = 0;
	for (i = 0; i < 9; i++) {
		if (status[i] == -1) {
			std::cout << " |";
		}
		else {
			if (status[i] != prestat[i]) {
				std::cout << status[i];
				std::cout << "|";
				prestat[i] = status[i];
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