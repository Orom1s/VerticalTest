#include <fstream>

#include "APRK_Parser.h"

int main() {
	std::ifstream file("Test2.APRk");
	if (file) {
		Parser pars(file);
	}
	file.close();
}