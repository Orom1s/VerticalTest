#include "TechProces.h"

TechProc::TechProc(Parser& data) {
	SetDraws(data);
	SetOpers(data);
}

void TechProc::SetDraws(Parser& data) {
	const auto& detail = data.GetDetail();
	const auto& blank = *(data.GetDims().at(0).end() - 1);
	const auto& path = data.GetPath();
	drawings.push_back(Drawing("Деталь"s, detail, path));
	if (blank != "0") {
		drawings.push_back(Drawing("Заготовка"s, blank, path));
	}
}

void TechProc::SetOpers(Parser& data) {
	const auto& etp = data.GetEtp();
	const auto& dims = data.GetDims();
	std::vector<std::vector<std::string>> operdata;
	for (auto& [key, val] : etp) {
		if (key == 0) continue;
		for (auto& oper : dims) {
			if (std::stoi(oper[0]) == key) {
				operdata.push_back(oper);
			}
		}
		if (!operdata.empty()) {
			operations.push_back(Operation(operdata, val, data.GetPath()));
			operdata.clear();
		}
	}
	

}

Drawing::Drawing(std::string name, const std::string& file, const std::string& path) {
	caption = name;
	kompasfile = path + file;
}

Operation::Operation(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::string& path) {
	SetType(etp);
	indexoper = operdata[0][0];
	std::string file = *(operdata[0].end() - 1);
	if (file != "0") {
		scetch_ = Drawing("Эскиз", file, path);
	}
	AssignSteps(operdata, etp);
}

void Operation::SetType(const std::string& etp) {
	if (etp.find("MO"s) != std::string::npos) {
		nameoper = "mex_oper";
	}
	else if (etp.find("TO"s) != std::string::npos) {
		nameoper = "trm_oper";
	}
	else {
		nameoper = "pok_oper";
	}
}

void Operation::AssignSteps(const std::vector<std::vector<std::string>>& operdata, const std::string& etp) {
	int count_steps = 0;
	std::vector<int> num_steps;
	for (auto& oper : operdata) {
		if (oper[1] != "0") {
			++count_steps;
			num_steps.push_back(count_steps);
		}
	}
	if (count_steps) {
		for (int i = 0; i < count_steps; ++i) {
			auto first = operdata.begin() + num_steps[i];
			auto last = operdata.end();
			if ((i + 1) < num_steps.size()) {
				last = operdata.begin() + num_steps[i + 1];
			}
			std::vector<std::vector<std::string>> step(first, last);
			steps.push_back(Step(step, etp));
		}
	}
	else {
		steps.push_back(Step(operdata, etp));
	}
}

Step::Step(const std::vector<std::vector<std::string>>& operdata, const std::string& etp) {
	SetType(etp);
	numstep = operdata[0][1];
	for (auto data : operdata) {
		parameters.push_back(Parameter(data));
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

Parameter::Parameter(const std::vector<std::string>& operdata) {
	param = *(operdata.end() - 2);
	size_.value_dimVAL = *(operdata.begin() + 7);
	if (*(operdata.begin() + 10) == "0") {
		size_.value_upDEV = std::stod(*(operdata.begin() + 8));
		size_.value_lowDEV = std::stod(*(operdata.begin() + 9));
	}
	else {
		size_.value_QUAL = *(operdata.begin() + 10);
	}
}
