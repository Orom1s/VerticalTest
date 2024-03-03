#include "APRK_Parser.cpp"


#include "Operation.h"



	class TechProc {
	public:
		TechProc() = default;

		TechProc(Parser& data);

	private:
		std::vector<Drawing> drawings;
		std::vector<Operation> operations;

		//метод для заполнения эскизов
		void SetDraws(Parser& data);
		//метод для заполнения операций
		void SetOpers(Parser& data);
	};
