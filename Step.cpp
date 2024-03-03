#include "Step.h"

Step::Step(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::vector<std::string>& dims_al) {
	SetType(etp);
	auto pos = FindPosWord(dims_al, "suboperSEQ");
	numstep = operdata[0][pos];
	//заполнение параметров по кличеству строк переданных в шаг
	for (auto data : operdata) {
		parameters.push_back(Parameter(data, dims_al));
	}
}

void Step::SetType(const std::string& etp) {
	if (etp.find("MO") != std::string::npos) {
		name = "mex_step";
	}
	else if (etp.find("TO") != std::string::npos) {
		name = "trm_step";
	}
	else {
		name = "pok_step";
	}
}