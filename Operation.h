#pragma once

#include "Step.h"
#include "Drawing.h"

class Operation {
public:
	Operation() = default;

	Operation(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::string& path, const std::vector<std::string>& dims_al);
private:
	std::string nameoper;
	std::string indexoper;
	Drawing scetch_;
	std::vector<Step> steps;

	void SetType(const std::string& etp);
	void AssignSteps(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::vector<std::string>& dims_al);
};