#include "APRK_Parser.cpp"

#include <optional>

	class Operation;
	class Drawing;
	class Step;
	class Parameter;
	


	class TechProc {
	public:
		TechProc() = default;

		TechProc(Parser& data);

	private:
		std::vector<Drawing> drawings;
		std::vector<Operation> operations;

		void SetDraws(Parser& data);
		void SetOpers(Parser& data);
	};

	class Drawing {
	public:
		Drawing() = default;

		Drawing(std::string name, const std::string& file, const std::string& path);

	private:
		std::string caption;
		std::string kompasfile;
	};

	class Operation {
	public:
		Operation() = default;

		Operation(const std::vector<std::vector<std::string>>& operdata, const std::string& etp, const std::string& path);
	private:
		std::string nameoper;
		std::string indexoper;
		Drawing scetch_;
		std::vector<Step> steps;

		void SetType(const std::string& etp);
		void AssignSteps(const std::vector<std::vector<std::string>>& operdata, const std::string& etp);
	};

	class Step {
	public:
		Step() = default;

		Step(const std::vector<std::vector<std::string>>& operdata, const std::string& etp);
	private:
		std::string name;
		std::string numstep;
		std::vector<Parameter> parameters;

		void SetType(const std::string& etp);
	};

	class Parameter {
	public:
		Parameter() = default;

		Parameter(const std::vector<std::string>& operdata);

	private:
		bool show = true;
		bool showname = true; 
		std::string param;
		
		struct Size {
			std::string value_dimVAL;
			double value_upDEV;
			double value_lowDEV;
			std::string value_QUAL;
		};

		Size size_;
	};

