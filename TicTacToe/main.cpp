#include <iostream>

void printStatus(int* status);

void main() {
	int* status = (int*)malloc(10 * sizeof(int));
	int i;
	for (i = 0; i < 10; i++) {
		status[i] = -1;
	}
	printStatus(status);
	std::cin.get();
}

void printStatus(int *status) {
	int i;
	int everyThree = 0;
	for (i = 0; i < 10; i++) {
		everyThree++;
		if (status[i] == -1) {
			std::cout << " |";
		}
		else {
			std::cout << status[i];
			std::cout << "|";
		}
		if (everyThree == 3) {
			std::cout << std::endl;
			std::cout << "_ _ _" << std::endl;
			everyThree = 0;
		}
	}
}