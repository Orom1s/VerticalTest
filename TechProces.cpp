#include "TechProces.h"

TechProc::TechProc(Parser& data) {
	SetDraws(data);
	SetOpers(data);
}

void TechProc::SetDraws(Parser& data) {
	const auto& detail = data.GetDetail();
	const auto& path = data.GetPath();
	drawings.push_back(Drawing("Деталь"s, detail, path));
	if (data.GetDims().at(0).size() > data.GetDimsTCad()) {
		const auto& blank = data.GetDims().at(0).at(data.GetDimsTCad());
		if (blank != "0") {
			drawings.push_back(Drawing("Заготовка"s, blank, path));
		}
	}
}

void TechProc::SetOpers(Parser& data) {
	const auto& etp = data.GetEtp();
	const auto& dims = data.GetDims();
	const auto& dims_al = data.GetDimsAlias();
	auto pos = FindPosWord(dims_al, "operID");
	std::vector<std::vector<std::string>> operdata;
	for (auto& [key, val] : etp) {
		if (key == 0) continue;
		for (auto& oper : dims) {
			if (std::stoi(oper[pos]) == key) {
				operdata.push_back(oper);
			}
		}
		if (!operdata.empty()) {
			operations.push_back(Operation(operdata, val, data.GetPath(), dims_al));
			operdata.clear();
		}
	}
	

}
