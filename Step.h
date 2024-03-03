#pragma once

#include "Parameter.h"

class Step {
public:
	Step() = default;

	//заполнение шага по переданным данным
	Step(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::vector<std::string>& dims_al);
private:
	std::string name;
	std::string numstep;
	std::vector<Parameter> parameters;

	//заполнение типа шага по аналогии с заполнением тип оперциии
	void SetType(const std::string& etp);
};