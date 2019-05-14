#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <Windows.h>




//Current position
int cursor = 0;
int blinker = 0;
int activePlayer = 1;

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

		if (GetKeyState('X') & 0x8000) {
			if (activePlayer == 1) {
				status[cursor] = 1;
				activePlayer = 2;
			}
		}

		if (GetKeyState('O') & 0x8000) {
			if (activePlayer == 2) {
				status[cursor] = 0;
				activePlayer = 1;
			}
		}

		if (GetKeyState(VK_UP) & 0x8000) {
			//up
			if (cursor > 2) {
				cursor = cursor - 3;
			}
		}
		
		if (GetKeyState(VK_DOWN) & 0x8000) {
			//down
			if (cursor < 6) {
				cursor = cursor + 3;
			}
		}

		if (GetKeyState(VK_LEFT) & 0x8000) {
			//left
			if (cursor > 0) {
				cursor--;
			}
		}

		if (GetKeyState(VK_RIGHT) & 0x8000) {
			//right
			if (cursor < 8) {
				cursor++;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		printStatus(status);
		std::cout << "Turn : Player" << activePlayer << std::endl;
	}
	std::cin.get();
}

void printStatus(int *status) {
	setCursorPosition(0, 0);
	std::cout << std::endl;
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
	std::cout << std::endl;
}

void setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x , (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

int checkWinner(int* status) {
	//vertical

	int i;
	for (i = 0; i < 3; i++) {
		if (status[i] == status[i + 3] && status[i + 3] == status[i + 6]) {
			if (status[i] != -1) {
				return status[i];
			}
		}
	}
	//horizontal
	for (i = 0; i < 3; i++) {
		if (status[i] == status[i + 1] && status[i + 1] == status[i + 2]) {
			if (status[i] != -1) {
				return status[i];
			}
		}
	}
	//diagonal
	if (status[0] == status[4] && status[4] == status[8]) {
		if (status[0] != -1) {
			return status[0];
		}
	}
	if (status[2] == status[4] && status[4] == status[6]) {
		if (status[2] != -1) {
			return status[2];
		}
	}
	return -1;
}