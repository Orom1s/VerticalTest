#include "TechProces.h"

TechProc::TechProc(Parser& data) {
	SetDraws(data);
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

}

Drawing::Drawing(std::string name, const std::string& file, const std::string& path) {

}

Operation::Operation(Parser& data) {

}
