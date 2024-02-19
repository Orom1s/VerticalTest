#pragma once

#include <vector>
#include <string>

size_t FindPosWord(const std::vector<std::string>& dims_al, const std::string& word) {
	auto it = std::find(dims_al.begin(), dims_al.end(), word);
	auto pos = std::distance(dims_al.begin(), it) - 1;
	return pos;
}