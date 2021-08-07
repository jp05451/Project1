#pragma once
#include"BigFloat.h"
#include <iostream>
#include <vector>
#include <string>

typedef struct variable {
	std::string name;
	BigFloat value;
	bool isInt;
	variable(const std::string& name, const BigFloat& value, const bool& isInt = 0);
} variable;

class Formula {
private:
	std::vector<BigFloat> numbers;
	std::vector<int> operations;
	std::vector<Formula> sub_formulas;//Formula clips between ( )
	static std::vector<variable> var;


	static void setDecimalVariable(const std::string& name, const BigFloat& value);
	static void removeAllVarible();

	bool setForm(const std::string& input);

	void printFormula();
	int errorType = 0;


public:

	Formula();
	Formula(const std::string& input);

	bool inputCommand(const std::string& input);
	int getErrorType();
	BigFloat calculate();

	friend std::istream& operator>>(std::istream& is, Formula* const& form);//<-waitIJustRealizedThisIsUseless
	//friend std::ostream& operator<<(std::ostream& os, Formula form);
};

/*
Instruction of my stupid code:
Step 1: Poot string into inputCommand
Step 2: if it return yes, i think you should print sth
	if getErrorType = 0:
		Step 3: call calculate and do stuff to the result
	if getErrorType > 0:
		Step 3: print error
	if step1 return nah, do nothing
Step 3: ......?
Step 4: Profit

*/