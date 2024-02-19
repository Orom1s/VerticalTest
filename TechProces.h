#include "APRK_Parser.cpp"


#include "Operation.h"



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
