#include "Parameter.h"

Parameter::Parameter(const std::vector<std::string>& operdata, const std::vector<std::string>& dims_al) {
	param = operdata.at(FindPosWord(dims_al, "TAG"));
	size_.value_dimVAL = operdata.at(FindPosWord(dims_al, "dimVAL"));
	auto pos = FindPosWord(dims_al, "QUAL");
	if (operdata.at(pos) == "0") {
		size_.value_upDEV = std::stod(operdata.at(FindPosWord(dims_al, "upDEV")));
		size_.value_lowDEV = std::stod(operdata.at(FindPosWord(dims_al, "lowDEV")));
	}
	else {
		size_.value_QUAL = operdata.at(pos);
	}
}

size_t FindPosWord(const std::vector<std::string>& dims_al, const std::string& word) {
	auto it = std::find(dims_al.begin(), dims_al.end(), word);
	auto pos = std::distance(dims_al.begin(), it);
	return pos;
}