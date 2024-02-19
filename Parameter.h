#pragma once

#include <vector>
#include <string>


class Parameter {
public:
	Parameter() = default;

	Parameter(const std::vector<std::string>& operdata, const std::vector<std::string>& dims_al);

private:
	bool show = true;
	bool showname = true;
	std::string param;

	struct Size {
		std::string value_dimVAL;
		double value_upDEV;
		double value_lowDEV;
		std::string value_QUAL;
	};

	Size size_;
};

size_t FindPosWord(const std::vector<std::string>& dims_al, const std::string& word);