#pragma once

#include "Parameter.h"

class Step {
public:
	Step() = default;

	Step(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::vector<std::string>& dims_al);
private:
	std::string name;
	std::string numstep;
	std::vector<Parameter> parameters;

	void SetType(const std::string& etp);
};