//#include"BigFloat.h"
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#pragma once
using namespace std;
class BigInt
{

    vector<int>intv;
    int neg = 0;
    int iSize = 0;
    int iL = 1;

    /*
123.456
pv[] = '321'
hv[] = '456'
*/
public:
                //friend class BigFloat;
    BigInt();
    BigInt(string s);
    BigInt(int t);
    BigInt(const BigInt& B);
    int compare(BigInt B);

    BigInt operator+(BigInt B);
    BigInt operator-(BigInt B);
    BigInt operator*(BigInt B);
    BigInt operator/(BigInt B);
    BigInt operator^(BigInt B);

    BigInt operator+(string s);
    BigInt operator-(string s);
    BigInt operator*(string s);
    BigInt operator/(string s);
    BigInt operator^(string B);


    BigInt operator+(int s);
    BigInt operator-(int s);
    BigInt operator*(int s);
    BigInt operator/(int s);
    BigInt operator^(float B);


    bool operator == (const BigInt& B);
    bool operator <= (const BigInt& B);
    bool operator < (const BigInt& B);


    friend BigInt operator+(string s, BigInt B);
    friend BigInt operator-(string s, BigInt B);
    friend BigInt operator*(string s, BigInt B);
    friend BigInt operator/(string s, BigInt B);

    friend BigInt operator+(int s, BigInt B);
    friend BigInt operator-(int s, BigInt B);
    friend BigInt operator*(int s, BigInt B);
    friend BigInt operator/(int s, BigInt B);
    
    friend BigInt sqrt(BigInt B);

    friend ostream& operator << (ostream& ostr, BigInt B);


    BigInt Fac(void);
    BigInt Power(string num);
    BigInt Power(BigInt B);
    BigInt& operator=(string s);
    BigInt& operator=(BigInt B);
    BigInt& operator=(double d);
    int Check(vector<int> a, vector<int> b, int lb, int lc);
    void Print();
};

