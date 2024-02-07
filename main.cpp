#include <fstream>

#include "TechProces.h"

int main() {
	std::ifstream file;
	file.open("Корпус.APRk");
	if (file) {
		Parser pars(file);
		TechProc TP(pars);
	}
	file.close();
}