#pragma once
//#include"BigInt.h"
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <ctime>
//#include <Windows.h>
//#include <Psapi.h>
using namespace std;
class BigFloat
{
    vector<int>intv;
    vector<int>floatv;
    int neg = 0;
    int iSize = 0;
    int fSize = 0;
    int iL = 1;
    int fL = 100;

    /*
123.456
pv[] = '321'
hv[] = '456'
*/
public:
                //friend class BigInt;
    BigFloat();
    BigFloat(string s);
    BigFloat(int t);
    BigFloat(double t);
    BigFloat(const BigFloat& B);
    int compare(BigFloat B);
    BigFloat operator+(BigFloat B);
    BigFloat operator-(BigFloat B);
    BigFloat operator*(BigFloat B);
    BigFloat operator/(BigFloat B);
    BigFloat operator^(const BigFloat& B);

    BigFloat operator+(string s);
    BigFloat operator-(string s);
    BigFloat operator*(string s);
    BigFloat operator/(string s);
    BigFloat operator^(string s);


    BigFloat operator+(int s);
    BigFloat operator-(int s);
    BigFloat operator*(int s);
    BigFloat operator/(int s);
    BigFloat operator^(int s);


    BigFloat operator+(double s);
    BigFloat operator-(double s);
    BigFloat operator*(double s);
    BigFloat operator/(double s);
   BigFloat operator^(double s);

    friend BigFloat operator+(string s,BigFloat B);
    friend BigFloat operator-(string s,BigFloat B);
    friend BigFloat operator*(string s,BigFloat B);
    friend BigFloat operator/(string s,BigFloat B);

    friend BigFloat operator+(int s, BigFloat B);
    friend BigFloat operator-(int s, BigFloat B);
    friend BigFloat operator*(int s, BigFloat B);
    friend BigFloat operator/(int s, BigFloat B);

    friend BigFloat operator+(double s, BigFloat B);
    friend BigFloat operator-(double s, BigFloat B);
    friend BigFloat operator*(double s, BigFloat B);
    friend BigFloat operator/(double s, BigFloat B);
    friend BigFloat sqrt(BigFloat B);

    bool operator ==(const BigFloat& B);
    bool operator<(const BigFloat& B);
    bool operator <=(const BigFloat& B);

    friend ostream& operator<<(ostream& ostr, const BigFloat& B);
    BigFloat Fac(void);
    BigFloat Power(string num);
    BigFloat Power(BigFloat B);
    BigFloat& operator=(string s);
    BigFloat& operator=(BigFloat B);
    BigFloat& operator=(double B);
    int Check(vector<int > a, vector<int> b, int lb, int lc);
    void Print();
};

