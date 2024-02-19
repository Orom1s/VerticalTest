#pragma once

#include <string>

class Drawing {
public:
	Drawing() = default;

	Drawing(std::string name, const std::string& file, const std::string& path);

private:
	std::string caption;
	std::string kompasfile;
};