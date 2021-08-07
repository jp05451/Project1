#include "Formula.h"
#include "BigInt.h"
#include <sstream>
#define START_OF_BIG_NUM 7
#define SYNTAX_ERROR_SET 1
#define ERROR_UNKNOWN_TYPE 2
#define SYNTAX_ERROR_EQUAL 3
#define ERROR_UNKNOWN_VARIABLE 4
#define ERROR_DUPLICATED_VARIABLE_NAME 5
#define SYNTAX_ERROR_FAC 6
#define SYNTAX_ERROR_POWER 7
#define SYNTAX_ERROR_NEG 8
#define SYNTAX_ERROR_MULT_OR_DIVIDE 9
#define SYNTAX_ERROR_PLUS_OR_MINUS 10

std::vector<variable> Formula::var = {};
Formula::Formula()
{
	/*
	int code -> operation
	1 -> +
	2 -> -
	3 -> *
	4 -> /
	5 -> !
	6 -> ^
	7 + n -> nth number, stored in vector numbers
	0 - n -> nth sub_formula, stored in vector subformulas
	*/
}

Formula::Formula(const std::string& input)
{
	setForm(input);
}

bool Formula::inputCommand(const std::string& input)
{
	errorType = 0;
	std::string str = input;
	while (!str.empty() && str[0] == ' ')str.erase(str.begin());
	if (str.empty())return 0;
	if (str[0] == 'S' && str[1] == 'e' && str[2] == 't') {
		//Set variable
		str.erase(str.begin(), str.begin() + 3);
		if (str.empty()) {
			errorType = SYNTAX_ERROR_SET; // "Syntax Error\n";
			return 0;
		}
		while (!str.empty() && str[0] == ' ')str.erase(str.begin());
		std::string typeDetect = "";
		while (!str.empty() && str[0] != ' ') {
			typeDetect.push_back(str[0]);
			str.erase(str.begin());
		}
		while (!str.empty() && str[0] == ' ')str.erase(str.begin());
		std::string variable_name = "";
		while (!str.empty() && str[0] != ' ') {
			variable_name.push_back(str[0]);
			str.erase(str.begin());
		}
		for (size_t index = 0; index < var.size(); index++) {
			if (variable_name == var[index].name) {
				errorType = ERROR_DUPLICATED_VARIABLE_NAME;//Error Duplicated variable name
				return 1;
			}
		}
		while (!str.empty() && str[0] == ' ' || str[0] == '=')str.erase(str.begin());
		if (typeDetect == "Decimal") {
			if (str.empty())
				var.push_back(variable(variable_name, BigFloat("0")));
			else {
				Formula temp(str);
				BigFloat bf = temp.calculate();
				if (temp.errorType > 0) {
					errorType = temp.errorType;
					return 1;
				}
				var.push_back(variable(variable_name, bf));
			}

			return 0;
		}
		else if (typeDetect == "Integer") {
			if (str.empty())
				var.push_back(variable(variable_name, BigFloat("0")));
			else {
				Formula temp(str);
				BigFloat bf = temp.calculate();
				if (temp.errorType > 0) {
					errorType = temp.errorType;
					return 1;
				}
				std::stringstream ss;
				ss << bf;
				std::string resultStr;
				ss >> resultStr;
				std::stringstream ss2;
				ss2 << BigInt(resultStr);
				ss2 >> resultStr;
				bf = resultStr;
				var.push_back(variable(variable_name, bf, 1));
			}
			return 0;
		}
		else {
			errorType = ERROR_UNKNOWN_TYPE;//"Error! Unknown type" 
			return 1;
		}
	}
	else {
		bool isEquation = 0;
		for (size_t index = 0; index < str.size(); index++) {
			if (str[index] == '=') {
				isEquation = 1;
				break;
			}
		}
		if (isEquation) {
			std::string variable_name = "";
			while (!str.empty() && str[0] != ' ') {
				variable_name += str[0];
				str.erase(str.begin());
			}
			while (!str.empty() && (str[0] == ' ' || str[0] == '='))str.erase(str.begin());
			if (str.empty()) {
				errorType = SYNTAX_ERROR_EQUAL;// "Syntax Error around '='";
				return 1;
			}
			for (size_t index = 0; index < var.size(); index++) {
				if (variable_name == var[index].name) {
					Formula temp(str);
					BigFloat bf = temp.calculate();
					if (temp.errorType > 0) {
						errorType = temp.errorType;
						return 1;
					}
					if (var[index].isInt) {
						std::stringstream ss;
						ss << bf;
						std::string resultStr;
						ss >> resultStr;
						std::stringstream ss2;
						ss2 << BigInt(resultStr);
						ss2 >> resultStr;
						bf = resultStr;
					}
					var[index].value = bf;
					return 0;
				}
			}
			errorType = ERROR_UNKNOWN_VARIABLE; //"Error unknown variable";
			return 1;


		}
		else {
			setForm(str);
			// << "The answer is:\n";
			return 1;
		}
	}
}

int Formula::getErrorType()
{
	return errorType;
}

void Formula::setDecimalVariable(const std::string& name, const BigFloat& value)
{
	bool newName = 1;
	for (size_t index = 0; index < var.size(); index++) {
		if (var[index].name == name) {
			var[index].value = value;
			newName = 0;
		}
	}
	if (newName) {

		var.push_back(variable(name, value));
	}
}

void Formula::removeAllVarible()
{
	var.clear();
}

bool Formula::setForm(const std::string& input)
{
	numbers.clear();
	operations.clear();
	sub_formulas.clear();
	
	std::string str = input;
	while (!str.empty()) {
		if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == '!' || str[0] == '^') {
			//normal operations
			switch (str[0]) {
			case '+':
				operations.push_back(1);
				break;
			case '-':
				operations.push_back(2);
				break;
			case '*':
				operations.push_back(3);
				break;
			case '/':
				operations.push_back(4);
				break;
			case '!':
				operations.push_back(5);
				break;
			case '^':
				operations.push_back(6);
				break;
			}

			str.erase(str.begin());
		}
		else if (str[0] <= '9' && str[0] >= '0') {
			//numbers
			std::string bigNum1;
			while ((str[0] <= '9' && str[0] >= '0') || str[0] == '.') {
				bigNum1 += str[0];
				str.erase(str.begin());
			}
			BigFloat bigFloat1(bigNum1);
			operations.push_back(START_OF_BIG_NUM + numbers.size());
			numbers.push_back(bigFloat1);


		}
		else if (str[0] == '(') {
			//Brackets->Sub-formulas
			str.erase(str.begin());
			int bracketCount = 0;
			std::string subStr;
			while (!str.empty() && !(str[0] == ')' && bracketCount < 1)) {
				if (str[0] == '(')bracketCount++;
				else if (str[0] == ')')bracketCount--;
				subStr += str[0];
				str.erase(str.begin());
			}
			// << "Inserting:(" << subStr << ") as Sub-string\n";
			operations.push_back(sub_formulas.size() * -1);
			sub_formulas.push_back(Formula(subStr));


		}
		else if (str[0] == ' ' || str[0] == ')') str.erase(str.begin());
		else {
			std::string name = "";
			do {
				name += str[0];
				str.erase(str.begin());
			} while (!str.empty() && str[0] != '+' && str[0] != '-' && str[0] != '*' && str[0] != '/' && str[0] != '!' && str[0] != '^' && str[0] != '(' && str[0] != ' ' && str[0] != ')' && !(str[0] <= '9' && str[0] >= '0'));
			bool variable_not_found = 1;
			for (size_t index = 0; index < var.size(); index++) {
				if (var[index].name == name) {
					variable_not_found = 0;
					operations.push_back(START_OF_BIG_NUM + numbers.size());
					numbers.push_back(var[index].value);
					break;
				}
			}
			if (variable_not_found) {
				errorType = ERROR_UNKNOWN_VARIABLE; // << "Unknown Variable:" << name << std::endl;
				return 1;
			}
		}

	}
	//printFormula();
	return 0;
}

void Formula::printFormula()
{
	for (size_t step = 0; step < operations.size(); step++) {
		switch (operations[step]) {
		case 1:
			std::cout << " + ";
			break;
		case 2:
			std::cout << " - ";
			break;
		case 3:
			std::cout << " * ";
			break;
		case 4:
			std::cout << " / ";
			break;
		case 5:
			std::cout << "! ";
			break;
		case 6:
			std::cout << " ^ ";
			break;
		default:
			if (operations[step] >= START_OF_BIG_NUM)
				numbers[operations[step] - START_OF_BIG_NUM].Print();
			else if (operations[step] < 1) {
				std::cout << "(";
				sub_formulas[operations[step] * -1].printFormula();
				std::cout << ")";
			}
		}
	}

}

BigFloat Formula::calculate()
{
	//Priority 1: ( )
	for (size_t index = 0; index < operations.size(); index++)
		if (operations[index] < 1) {
			numbers.push_back(sub_formulas[operations[index] * -1].calculate());
			if (sub_formulas[operations[index] * -1].errorType > 0) {
				errorType = sub_formulas[operations[index] * -1].errorType;
				return BigFloat("1");
			}
			operations[index] = START_OF_BIG_NUM + numbers.size() - 1;
		}

	//Priority 2: !
	for (size_t index = 0; index < operations.size(); index++)
		while (index < operations.size() && operations[index] == 5) {
			if (index < 1 || operations[index - 1] < START_OF_BIG_NUM) {
				errorType = SYNTAX_ERROR_FAC; // << "Syntax Error: !\n";

				return BigFloat("1");
			}
			numbers[operations[index - 1] - START_OF_BIG_NUM] = numbers[operations[index - 1] - START_OF_BIG_NUM].Fac();
			operations.erase(operations.begin() + index);
		}

	//Priority 3: ^
	for (int index = operations.size() - 1; index >= 0; index--)
		while (index < operations.size() && operations[index] == 6) {
			if (index < 1 || index >= operations.size() || operations[index - 1] < START_OF_BIG_NUM || operations[index + 1] < START_OF_BIG_NUM) {
				errorType = SYNTAX_ERROR_POWER; // << "Syntax Error: ^\n";

				return BigFloat("1");
			}
			numbers[operations[index - 1] - START_OF_BIG_NUM] = numbers[operations[index - 1] - START_OF_BIG_NUM] ^ numbers[operations[index + 1] - START_OF_BIG_NUM];
			operations.erase(operations.begin() + index + 1);
			operations.erase(operations.begin() + index);
		}

	//Priority 4: neg
	for (int index = operations.size() - 1; index >= 0; index--)
		while (index < operations.size() && (operations[index] == 1 || operations[index] == 2)) {
			if (index >= operations.size() || operations[index + 1] < START_OF_BIG_NUM) {
				errorType = SYNTAX_ERROR_NEG; // << "Syntax Error: -\n";

				return BigFloat("1");
			}
			if (operations[index] == 2)numbers[operations[index + 1] - START_OF_BIG_NUM] = numbers[operations[index + 1] - START_OF_BIG_NUM] * BigFloat("-1");
			operations.erase(operations.begin() + index);
		}

	//Priority 5: * /
	for (size_t index = 0; index < operations.size(); index++)
		while (index < operations.size() && (operations[index] == 3 || operations[index] == 4)) {
			if (index < 1 || index >= operations.size() || operations[index - 1] < START_OF_BIG_NUM || operations[index + 1] < START_OF_BIG_NUM) {
				errorType = SYNTAX_ERROR_MULT_OR_DIVIDE;// << "Syntax Error: * or /\n";

				return BigFloat("1");
			}
			if (operations[index] == 3)numbers[operations[index - 1] - START_OF_BIG_NUM] = numbers[operations[index - 1] - START_OF_BIG_NUM] * numbers[operations[index + 1] - START_OF_BIG_NUM];
			else numbers[operations[index - 1] - START_OF_BIG_NUM] = numbers[operations[index - 1] - START_OF_BIG_NUM] / numbers[operations[index + 1] - START_OF_BIG_NUM];
			operations.erase(operations.begin() + index + 1);
			operations.erase(operations.begin() + index);
		}
	//Priority 6: +
	while (operations.size() > 1) {
		if (operations[1] < START_OF_BIG_NUM) {
			errorType = SYNTAX_ERROR_PLUS_OR_MINUS; // << "Syntax Error: +\n";

			return BigFloat("1");
		}
		numbers[operations[0] - START_OF_BIG_NUM] = numbers[operations[0] - START_OF_BIG_NUM] + numbers[operations[1] - START_OF_BIG_NUM];
		operations.erase(operations.begin() + 1);
	}

	return numbers[operations[0] - START_OF_BIG_NUM];
}

std::istream& operator>>(std::istream& is, Formula* const& form)
{
	std::string input;
	std::getline(is, input);
	form->inputCommand(input);
	return is;
}

variable::variable(const std::string& name, const BigFloat& value, const bool& isInt)
{
	this->name = name;
	this->value = value;
	this->isInt = isInt;
}
