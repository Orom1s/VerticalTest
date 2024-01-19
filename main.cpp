#include <fstream>

#include "APRK_Parser.cpp"

int main() {
	std::ifstream file;
	file.open("Test2.APRk");
	if (file) {
		Parser pars(file);
	}
	file.close();
}