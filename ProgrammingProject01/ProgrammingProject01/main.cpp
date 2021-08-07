#include"BigInt.h"
#include"BigFloat.h"
#include"Formula.h"
#include <sstream>
int main()
{
	/*string stra = { "70000000000000000000000000000000" };
	string strb = { "60000000000000000000000000000000" };
	BigFloat a(stra), b(strb), ans;
	ans = a / b;
	cout << "1/3=";
	cout << ans << endl;
	ans = a / b * b;
	cout << "1/3*3=";
	cout << ans;*/
	//Formula a;
	//string str;
	//getline(cin, str);
	Formula form;
	std::string command;
	
	std::cout << "Q==============================================================================Q" << std::endl;
	std::cout << "|Thank you for choosing our brand's most advanced calculator - CalcIt1991      |" << std::endl;
	std::cout << "|This calculator supports following functions:                                 |" << std::endl;
	std::cout << "|Basic math stuff - use +, -, * and / between numbers to get their result value|" << std::endl;
	std::cout << "|Factor!al! - !s pretty amaz!ng for Permutat!ons!!!                            |" << std::endl;
	std::cout << "|Powah^ - Use ^ to make numbers do themselves!                                 |" << std::endl;
	std::cout << "|(((((Brakets))))) - Numbers between these marks are so important,             |" << std::endl;
	std::cout << "|                    they'll always being done first.                          |" << std::endl;
	std::cout << "|Variables - Use Set Decimal/Integer name = (insert numbers here)              |" << std::endl;
	std::cout << "|            to give your favourite numbers cute names!                        |" << std::endl;
	std::cout << "Q==============================================================================Q" << std::endl;
	while (getline(std::cin, command))
	{
		if (form.inputCommand(command)) {
			if (form.getErrorType() > 0)
				std::cout << "Syntax Error " << form.getErrorType() << std::endl;
			else 
			{
				std::stringstream ss;
				BigFloat result = form.calculate();
				ss << result;
				std::string resultStr;
				ss >> resultStr;
				BigInt resultInt(resultStr);
				ss << resultInt;
				std::string resultIntStr;
				ss >> resultIntStr;
				BigFloat intButFloat(resultIntStr);
				//std::cout <<"resultStr: "<< resultStr << std::endl;
				//std::cout <<"resultIntStr: "<< resultIntStr << std::endl;
				if (resultIntStr.empty()|| BigFloat("0.00000000000000000000000000000000000000000000000001") < result - intButFloat)
					std::cout << resultStr << std::endl;
				else
					std::cout << resultIntStr << std::endl;
			}
				//form.calculate().Print();
		}
	}
		/*cout << "BigFloat part" << endl;
		ans = a +b;
		cout << a << " + " << b << "= " << ans << endl;
		ans = a - b;
		cout << a << " - " << b << "= " << ans << endl;
		ans = a * b;
		cout << a << " x " << b << "= " << ans << endl;
		ans = a / b;
		cout << a << " / " << b << "= " << ans << endl;
		ans = sqrt(a);
		cout<<" sqrt(" <<a<<") = "<< ans<<endl;
		ans = a.Fac();
		cout << a << "! = " << ans << endl;

		cout << "BigInt part" << endl;
		BigInt a_(stra), b_(strb), ans_;
		ans_ = a_ + b_;
		cout << a_ << " + " << b_ << "= " << ans_ << endl;
		ans_ = a_ -  b_ ;
		cout << a << " - " << b << "= " << ans_ << endl;
		ans_ = a_ * b_;
		cout << a_ << " x " << b_ << "= " << ans_ << endl;
		ans_ = a_ / b_;
		cout << a_ << " / " << b_ << "= " << ans_ << endl;
		ans_ = sqrt(a_);
		cout << " sqrt(" << a_ << ") = " << ans_ << endl;
		ans_ = a_.Fac();
		cout << a_ << "! = " << ans_ << endl;*/

}

