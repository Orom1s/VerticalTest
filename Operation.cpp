#include "Operation.h"

Operation::Operation(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::string& path, const std::vector<std::string>& dims_al) {
	SetType(etp);
	auto pos = FindPosWord(dims_al, "operID");
	indexoper = operdata[0][pos];
	pos = FindPosWord(dims_al, "CADfile");
	if (pos < operdata[0].size())
	{
		std::string file = operdata[0].at(pos);
		if (file != "0") {
			scetch_ = Drawing("Эскиз", file, path);
		}
	}
	AssignSteps(operdata, etp, dims_al);
}

void Operation::SetType(const std::string& etp) {
	if (etp.find("MO") != std::string::npos) {
		nameoper = "mex_oper";
	}
	else if (etp.find("TO") != std::string::npos) {
		nameoper = "trm_oper";
	}
	else {
		nameoper = "pok_oper";
	}
}

void Operation::AssignSteps(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::vector<std::string>& dims_al) {
	int count_steps = 0;
	std::vector<int> num_steps;
	auto pos = FindPosWord(dims_al, "suboperSEQ");
	for (auto& oper : operdata) {
		if (oper[pos] != "0") {
			++count_steps;
			num_steps.push_back(count_steps);
		}
	}
	//счетчик count_steps нужен для правильного определения количества шагов в операции 1 или больше
	if (count_steps) {
		for (int i = 0; i <= count_steps; ++i) {
			auto first = operdata.begin() + num_steps[i];
			auto last = operdata.end();
			if ((i + 1) < num_steps.size()) {
				last = operdata.begin() + num_steps[i + 1];
			}
			std::vector<std::vector<std::string>> step(first, last);
			steps.push_back(Step(step, etp, dims_al));
		}
	}
	else {
		steps.push_back(Step(operdata, etp, dims_al));
	}
}