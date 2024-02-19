#include "Drawing.h"

Drawing::Drawing(std::string name, const std::string& file, const std::string& path) {
	caption = name;
	kompasfile = path + file;
}