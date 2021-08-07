#include "BigInt.h"
BigInt::BigInt()
{
    neg = 0;
    iSize = 0;
    iL = 1;
    intv.resize(1);
}
BigInt::BigInt(string s)
{
    int pos = 0, L = s.size(), cut = L, t_pos = 0, t_iSize = 0;
    if (s[0] == '-')
        neg = 1;
    iL = L - neg;
    intv.resize(iL);

    for (pos = L-1, t_pos = 0; pos >= neg&&s[pos]!='.'; pos--, t_pos++)
    {
        intv[t_pos] = s[pos] - '0';
    }
    t_iSize = iL - 1;
    if (t_iSize >= 0)
    {
        while (intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    iSize = t_iSize;
}
BigInt::BigInt(int t)
{
    stringstream str;//sstream error:string stream str(t)
    str << t;
    string s;
    str >> s;
    int pos = 0, L = s.size(), cut = L, t_pos = 0, t_iSize = 0;
    if (s[0] == '-')
        neg = 1;
    iL = L - neg;
    intv.resize(iL);

    for (pos = L - 1, t_pos = 0; pos >= neg&&s[pos]!='.'; pos--, t_pos++)
    {
        intv[t_pos] = s[pos] - '0';
    }
    t_iSize = iL - 1;
    if (t_iSize >= 0)
    {
        while (intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    iSize = t_iSize;
}
BigInt::BigInt(const BigInt& B)
{
                intv = B.intv;
                iL = B.iL;
                iSize = B.iSize;
                neg = B.neg;
}
int BigInt::compare(BigInt B)
{ /*兩個都是正數*/
    int pos;
    if (iSize > B.iSize)
        return 1;
    if (iSize < B.iSize)
        return 0;
    for (pos = iSize; pos >= 0; pos--)
        if (intv[pos] > B.intv[pos])
            return 1;
        else if (intv[pos] < B.intv[pos])
            return 0;
    return 1;
}
BigInt BigInt::operator+(BigInt B)//error(a+(-b))
{
/*  BigInt tempA=(*this);//copy this to tempA
    BigInt tempB=B;
    int L = max(iL, B.iL);
    if (neg == 0 && B.neg == 1)
    {
        tempB.neg = 0;
        return tempA - tempB;
    }*/
                int L = max(iL, B.iL);
                if (neg == 0 && B.neg == 1)
                {
                                B.neg = 0;
                                return (*this) - B;
                }
    else if (neg == 1 && B.neg == 0)
    {
        neg = 0;
                    return B- (*this);
    }
    int pos, t_iSize;
    BigInt C;
    C.intv.resize(L + 1);
    C.neg = neg;
    for (pos = 0; pos <= iSize; pos++)
        C.intv[pos] += intv[pos];
    for (pos = 0; pos <= B.iSize; pos++)
        C.intv[pos] += B.intv[pos];
    t_iSize = (iSize > B.iSize) ? iSize : B.iSize; /*max*/
    for (pos = 0; pos <= t_iSize; pos++)
        C.intv[pos + 1] += C.intv[pos] / 10, C.intv[pos] %= 10;
    t_iSize = L;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    C.iSize = t_iSize;
    C.iL = t_iSize + 1;
    return C;
}
BigInt BigInt::operator-(BigInt B)
{
    int L = max(iL, B.iL);
    if (neg == 1 && B.neg == 1)
    {
        B.neg = 0, neg = 0;
        return B - (*this);
    }
    else if (neg == 1 && B.neg == 0)
    {
        neg = 0;
        B.neg = 0;
        BigInt C = (*this) + B;
        C.neg = 1;
        return C;
    }
    else if (neg == 0 && B.neg == 1)
    {
        B.neg = 0;
        return (*this) + B;
    }
    if (compare(B) == 0)
    {
        neg = 0;
        BigInt C = B - (*this);
        C.neg = 1;
        return C;
    }
    int pos, t_iSize;
    BigInt C;
    C.intv.resize(L + 1);
    for (pos = 0; pos <= iSize; pos++)
        C.intv[pos] = intv[pos];
    for (pos = 0; pos <= B.iSize; pos++)
        C.intv[pos] -= B.intv[pos];
    for (pos = 0; pos < L; pos++)
        while (C.intv[pos] < 0)
            C.intv[pos + 1]--, C.intv[pos] += 10;
    t_iSize = L;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }

    C.iSize = t_iSize;
    C.iL = t_iSize + 1;
    return C;
}
BigInt BigInt::operator*(BigInt B)
{
    int L = max(iL, B.iL);
    BigInt C;
    vector<int>Aa(L + 1, 0);
    vector<int>Bb(L + 1, 0);
    vector<int>Cc(2 * L + 1, 0);
    C.intv.resize(2 * L + 1, 0);
    int pos, t_pos, Al = 0, Bl = 0, t_iSize;
    for (pos = 0; pos <= iSize; pos++)
        Aa[Al++] = intv[pos];
    for (pos = 0; pos <= B.iSize; pos++)
        Bb[Bl++] = B.intv[pos];
    for (pos = 0; pos < Al; pos++)
    {
        for (t_pos = 0; t_pos < Bl; t_pos++)
            Cc[pos + t_pos] += Aa[pos] * Bb[t_pos];
    }
    for (pos = 0; pos < Al + Bl; pos++)
        Cc[pos + 1] += Cc[pos] / 10, Cc[pos] %= 10;
    for (pos = 0, t_pos = 0; pos < 2 * L + 1; pos++, t_pos++)
        C.intv[t_pos] = Cc[pos];
    t_iSize = 2 * L;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    C.iSize = t_iSize;
    C.iL = t_iSize + 1;
    C.neg = neg ^ B.neg;
    return C;
}
BigInt BigInt::operator/(BigInt B)
{
    BigInt C;
    int L = max(iL, B.iL);
    vector<int>Aa(3 * L + 1, 0);
    vector<int>Bb(3 * L + 1, 0);
    vector<int>Cc(2 * L + 1, 0);
    C.intv.resize(2 * L + 1);
    int pos, Al = 0, Bl = 0, t_iSize, t_fSize, i, j;
    for (pos = 0; pos <= iSize; pos++)
        Aa[Al++] = intv[pos];
    for (pos = 0; pos <= B.iSize; pos++)
        Bb[Bl++] = B.intv[pos];
    Al++, Bl++;
    for (i = Al - Bl; i >= 0; i--)
    {
        while (Check(Aa, Bb, Bl, i))
        {
            Cc[i]++;
            for (j = 0; j < Bl; j++)
            {
                Aa[i + j] -= Bb[j];
                if (Aa[i + j] < 0)
                {
                    Aa[i + j] += 10;
                    Aa[i + j + 1]--;
                }
            }
        }
    }
    for (pos = 0; pos <2 * L + 1; pos++)
        C.intv[pos] = Cc[pos];
    t_iSize = 2 * L;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    C.iSize = t_iSize;
    C.iL = t_iSize + 1;
    C.neg = neg ^ B.neg;
    return C;
}
BigInt BigInt::operator^(BigInt B)
{
                BigInt temp=(*this);
                for (BigInt i(2); i <= B; i = i + 1)
                {
                                temp = temp * (*this);
                }
                return temp;
}

BigInt BigInt::operator+(string s)
{
    BigInt B(s);
    return *this + B;
}
BigInt BigInt::operator-(string s)
{
    BigInt B(s);
    return *this - B;
}
BigInt BigInt::operator*(string s)
{
    BigInt B(s);
    return *this * B;
}
BigInt BigInt::operator/(string s)
{
    BigInt B(s);
    return *this / B;
}
BigInt BigInt::operator^(string B)
{
                stringstream str;
                float f;
                str <<B;
                str >> f;
                BigInt temp;
                return(*this) ^ f;
}


BigInt BigInt::operator+(int s)
{
    BigInt B(s);
    return *this + B;
                /*int i = 0;
                int c = 0;
                while (s != 0)
                {
                                intv[i] += s % 10+c;
                                c = intv[i] / 10;
                                s /= 10;
                                i++;
                }
                return *this;*/
}
BigInt BigInt::operator-(int s)
{
    BigInt B(s);
    return *this - B;
}
BigInt BigInt::operator*(int s)
{
    BigInt B(s);
    return *this * B;
}
BigInt BigInt::operator/(int s)
{
    BigInt B(s);
    return *this / B;
}
BigInt BigInt::operator^(float B)
{
                BigInt square;
                if (fmod(B, 1) == 0.5)
                {
                                square = sqrt(*this);
                }
                else
                {
                                cout << "unable to calculate root except square root" << endl;
                }
                                
                BigInt temp = B;
                for (BigInt i(2); i <= B; i = i + 1)
                {
                                temp = temp * B;
                }
                return temp*square;
}

BigInt operator+(string s, BigInt B)
{
    BigInt A(s);
    return  A + B;
}
BigInt operator-(string s, BigInt B)
{
    BigInt A(s);
    return  A - B;
}
BigInt operator*(string s, BigInt B)
{
    BigInt A(s);
    return  A * B;
}
BigInt operator/(string s, BigInt B)
{
    BigInt A(s);
    return  A / B;
}
BigInt operator+(int s, BigInt B)
{
    BigInt A(s);
    return  A + B;
}
BigInt operator-(int s, BigInt B)
{
    BigInt A(s);
    return  A - B;
}
BigInt operator*(int s, BigInt B)
{
    BigInt A(s);
    return  A * B;
}
BigInt operator/(int s, BigInt B)
{
    BigInt A(s);
    return  A / B;
}
BigInt& BigInt::operator=(string s)
{
    int pos = 0, L = s.size(), cut = L, t_pos = 0, t_iSize = 0, neg = 0;
    if (s[0] == '-')
        neg = 1;
    iL = L - neg;
    intv.resize(iL);

    for (pos = L - 1, t_pos = 0; pos >= neg; pos--, t_pos++)
    {
        intv[t_pos] = s[pos] - '0';
    }
    t_iSize = iL - 1;
    if (t_iSize >= 0)
    {
        while (intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    iSize = t_iSize;
    return *this;
}
BigInt& BigInt::operator=(BigInt B)
{
    intv.clear();
    iL = B.iL;
    intv.resize(iL);
    for (int i = 0; i < iL; i++)
    {
        intv[i] = B.intv[i];
    }
    neg = B.neg;
    iSize = B.iSize;
    return *this;
}
BigInt& BigInt::operator=(double d)
{
                /*stringstream str;
                string s;
                str << d;
                str >> s;*/
                BigInt temp(d);
                *this = temp;
                return *this;
}

BigInt BigInt::Power(string num)
{
    string t = "1";
    BigInt C = t;
    BigInt B = *this;
    int temp = atoi(num.c_str());
    for (int i = 0; i < temp; i++)
    {
        C = C * B;
    }

    return C;
}
BigInt BigInt::Power(BigInt B)
{
    string t = "1";
    BigInt C = t;
    BigInt pos = *this;
    int temp = 0;
    for (int i = 0; i < B.intv.size(); i++)
    {
        temp += B.intv[i] * pow(10, i);
    }
    for (int i = 0; i < temp; i++)
    {

        C = C * pos;
    }

    return C;
}
int BigInt::Check(vector<int> a, vector<int> b, int lb, int lc)
{
    int pos;
    for (pos = lb - 1; pos >= 0; pos--)
    {
        if (a[pos + lc] < b[pos])
            return 0;
        if (a[pos + lc] > b[pos])
            return 1;
    }
    return 1;
}
BigInt BigInt::Fac(void)
{
    BigInt C;

    int temp = 0;
    for (int i = 0; i < intv.size(); i++)
    {
        temp += intv[i] * pow(10, i);
    }
    int digit = 1, i, j;
    vector<int> result;

    result.push_back(1);

    for (j = 1; j <= temp; j++)
    {

        //檢查要做幾位數
        digit = result.size() - 1;
        while (result[digit] == 0)
        {
            digit--;
        }

        //進行乘法
        //每個digit都抓出來乘
        for (i = 0; i <= digit; i++)
            result[i] *= j;
        //處理各個digit進位的問題
        for (i = 0; i <= digit; i++)
        {
            int k = 0; //偏移量，處理超過雙位數的問題
            result.push_back(0);
            while (result[i + k] >= 10)
            {
                if (result.size() <= i + k)
                {
                    result.push_back(0);
                    result.push_back(0);
                }
                result[i + k + 1] += result[i + k] / 10;
                result[i + k] = result[i + k] % 10;
                k++;
                if (result.size() <= i + k)
                {
                    result.push_back(0);
                }
            }
        }

    }
    digit = result.size() - 1;
    while (result[digit] == 0)
    {
        digit--;
    }

    C.intv.resize(digit + 1);
    for (int i = 0; i <= digit; i++)
    {
        C.intv[i] = result[i];
    }
    C.iSize = digit;
    C.iL = digit + 1;
    return C;
}
void BigInt::Print()
{
    int pos;
    if (neg == 1)
        cout << "-";
    for (pos = iSize; pos >= 0; pos--)
        cout << intv[pos];
    if (iSize == -1)
        cout << '0';
    cout << '\n';

}

BigInt sqrt(BigInt B)
{
                BigInt ans;//answer
                BigInt T;//小的被除數(一次跳兩位)
                BigInt Tans;//左邊的a+2b
                if (B.neg == 1)
                //開根好只開正數
                                return ans;
               //確定長度是偶數
                if (B.iL % 2 != 0)
                                B.intv.push_back(0);
                while (!B.intv.empty())
                {
                                string str;
                                str.clear();
                                //取兩位數
                                for (int i = 0; i < 2; i++)
                                {
                                                str+= (*(B.intv.end()-1)+'0');
                                                B.intv.erase(B.intv.end()-1);
                                }
                                str += '\0';//結尾
                                int t;
                                t = stoi(str);
                                T = T * 100;//左移兩位
                                T = T + t;//加上下兩位數
                                Tans = Tans * 10;//Tans 左移一位
                                int x;
                                for (x=9;x>=0; x--)
                                {
                                                BigInt test;
                                                test = Tans + x;
                                                if (test * x <= T)
                                                {
                                                                T = T - test * x;
                                                                Tans =test+ x;
                                                                ans = ans * 10 + x;
                                                                break;
                                                }
                                }
                }
               // ans.iSize = ans.intv.size();
                //ans.iL = ans.iSize + 1;
                return ans;
}

bool BigInt::operator == (const BigInt& B)
{
                if (iSize != B.iSize || neg != B.neg)
                                return 0;
                for (int i = 0; i < B.intv.size(); i++)
                {
                                if (intv[i] != B.intv[i])
                                                return 0;
                }
                return 1;
}
bool BigInt::operator <= (const BigInt& B)
{
                if (neg == 1 && B.neg == 0)//*this<0&&B>0
                                return 1;
                if(neg==0&&B.neg==1)
                                return 0;
                if (*this == B)//A length is = B
                                return 1;
                if (neg == 0 && B.neg == 0)//A>0&&B>0
                {
                                if (iSize > B.iSize)
                                                return 0;
                                if (iSize < B.iSize)
                                                return 1;
                                if(iSize==B.iSize)
                                {
                                                for (int i =iL-1; i >= 0; i--)
                                                {
                                                                if (intv[i] < B.intv[i])
                                                                                return 1;
                                                                else if (intv[i] > B.intv[i])
                                                                                return 0;
                                                }
                                }
                }
                else//B<0&&A<0
                {
                                if (iSize < B.iSize)//B is longer
                                                return 0;
                                if (iSize > B.iSize)//B is shorter
                                                return 1;
                                if (iSize == B.iSize)
                                {
                                                for (int i = iL - 1; i >= 0; i--)
                                                {
                                                                if (intv[i] > B.intv[i])
                                                                                return 1;
                                                                else if (intv[i] < B.intv[i])
                                                                                return 0;
                                                }
                                }
                }
                return 0;
}
bool BigInt::operator < (const BigInt& B)
{
                if (neg == 1 && B.neg == 0)//*this<0&&B>0
                                return 1;
                if (neg == 0 && B.neg == 1)
                                return 0;
                if (*this == B)//A length is = B
                                return 0;
                if (neg == 0 && B.neg == 0)//A>0&&B>0
                {
                                if (iSize > B.iSize)
                                                return 0;
                                if (iSize < B.iSize)
                                                return 1;
                                if (iSize == B.iSize)
                                {
                                                for (int i = iL - 1; i >= 0; i--)
                                                {
                                                                if (intv[i] < B.intv[i])
                                                                                return 1;
                                                                else if (intv[i] > B.intv[i])
                                                                                return 0;
                                                }
                                }
                }
                else//B<0&&A<0
                {
                                if (iSize < B.iSize)//B is longer
                                                return 0;
                                if (iSize > B.iSize)//B is shorter
                                                return 1;
                                if (iSize == B.iSize)
                                {
                                                for (int i = iL; i >= 0; i--)
                                                {
                                                                if (intv[i] > B.intv[i])
                                                                                return 1;
                                                                else if (intv[i] < B.intv[i])
                                                                                return 0;
                                                }
                                }
                }
                return 0;
}


ostream& operator << (ostream& ostr, BigInt B)
{
                if (B.neg == 1)
                                ostr << "-";
                for (int i = B.iSize;i>=0; i--)
                {
                                ostr << B.intv[i];
                }
                return ostr;
}
