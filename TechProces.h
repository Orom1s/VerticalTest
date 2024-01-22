#include "APRK_Parser.cpp"


class TechProc  {
public:
	TechProc() = default;

	TechProc(Parser& data);
private:
	std::vector<Drawing> drawings;
	std::vector<Operation> operations;
};

class Operation {
public:

private:
	std::string nameoper;
	std::string indexoper;
	Scetch scetch;
	std::vector<Step> steps;
};

class Drawing {
public:

private:
	std::string caption;
	std::string kompasfile;
};

class Scetch {
public:

private:
	std::string caption;
	std::string kompasfile;
};

class Step {
public:

private:
	std::string name;
	std::string numstep;
	std::vector<Parameter> parameters;
};

class Parameter {
public:

private:
	std::string param;
	std::string value_dimVAL;
	double value_upDEV;
	double value_lowDEV;
	std::string value_QUAL;
};