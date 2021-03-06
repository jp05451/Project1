#include "BigFloat.h"
BigFloat::BigFloat()
{
    neg = 0;
    iSize = 0;
    fSize = 0;
    iL = 1;
    fL = 100;
    intv.resize(1);
    floatv.resize(100);
}
BigFloat::BigFloat(string s)
{
    long long pos = 0, L = s.size(), cut = L, t_pos = 0, t_iSize = 0, t_fSize = 0;//neg=0
    if (s[0] == '-')
        neg = 1;
    for (pos = neg; pos < L; pos++)
        if (s[pos] == '.')
            cut = pos;
    iL = cut;
    fL = 100;
    intv.resize(iL);
    floatv.resize(fL);

    for (pos = cut - 1, t_pos = 0; pos >= neg; pos--, t_pos++)
    {
        intv[t_pos] = s[pos] - '0';
    }
    for (pos = cut + 1, t_pos = 0; pos < L && t_pos < 100; pos++, t_pos++)
    {
        floatv[t_pos] = s[pos] - '0';
    }
    t_iSize = iL - 1, t_fSize = fL - 1;
    if (t_iSize >= 0)
    {
        while (intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }

    if (t_fSize >= 0)
    {
        while (floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }
    iSize = t_iSize, fSize = t_fSize > 99 ? 99 : t_fSize;
}
BigFloat::BigFloat(long long t)
{
    stringstream str;//stringstream str(t)
    str << t;
    string s;
    str >> s;
    long long pos = 0, L = s.size(), cut = L, t_pos = 0, t_iSize = 0, t_fSize = 0;//neg=0
    if (s[0] == '-')
        neg = 1;
    for (pos = neg; pos < L; pos++)
        if (s[pos] == '.')
            cut = pos;
    iL = cut;
    fL = 100;
    intv.resize(iL);
    floatv.resize(fL);

    for (pos = cut - 1, t_pos = 0; pos >= neg; pos--, t_pos++)
    {
        intv[t_pos] = s[pos] - '0';
    }
    for (pos = cut + 1, t_pos = 0; pos < L && t_pos < 100; pos++, t_pos++)
    {
        floatv[t_pos] = s[pos] - '0';
    }
    t_iSize = iL - 1, t_fSize = fL - 1;
    if (t_iSize >= 0)
    {
        while (intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }

    if (t_fSize >= 0)
    {
        while (floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }
    iSize = t_iSize, fSize = t_fSize > 99 ? 99 : t_fSize;
}
BigFloat::BigFloat(double t)
{
    stringstream str;
    str << t;
    string s;
    str >> s;
    long long pos = 0, L = s.size(), cut = L, t_pos = 0, t_iSize = 0, t_fSize = 0, neg = 0;
    if (s[0] == '-')
        neg = 1;
    for (pos = neg; pos < L; pos++)
        if (s[pos] == '.')
            cut = pos;
    iL = cut;
    fL = 100;
    intv.resize(iL);
    floatv.resize(fL);

    for (pos = cut - 1, t_pos = 0; pos >= neg; pos--, t_pos++)
    {
        intv[t_pos] = s[pos] - '0';
    }
    for (pos = cut + 1, t_pos = 0; pos < L && t_pos < 100; pos++, t_pos++)
    {
        floatv[t_pos] = s[pos] - '0';
    }
    t_iSize = iL - 1, t_fSize = fL - 1;
    if (t_iSize >= 0)
    {
        while (intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }

    if (t_fSize >= 0)
    {
        while (floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }
    iSize = t_iSize, fSize = t_fSize > 99 ? 99 : t_fSize;
}
BigFloat::BigFloat(const BigFloat& B)
{
                intv = B.intv;
              /*  while (*(intv.end() - 1) != 0)
                {
                                intv.erase(intv.end() - 1);
                }*/
                floatv = B.floatv;
                fSize = B.fSize;
                iSize = B.iSize;
                iL = B.iL;
                fL = B.fL;
                neg = B.neg;
}


long long BigFloat::compare(BigFloat B)
{ /*???????O????*/
    long long pos;
    if (iSize > B.iSize)
        return 1;
    if (iSize < B.iSize)
        return 0;
    for (pos = iSize; pos >= 0; pos--)
        if (intv[pos] > B.intv[pos])
            return 1;
        else if (intv[pos] < B.intv[pos])
            return 0;
    for (pos = 0; pos <= fSize && pos <= B.fSize; pos++)
        if (floatv[pos] > B.floatv[pos])
            return 1;
        else if (floatv[pos] < B.floatv[pos])
            return 0;
    if (fSize > B.fSize)
        return 1;
    else if (fSize < B.fSize)
        return 0;
    return 1;
}
BigFloat BigFloat::operator+(BigFloat B)
{
    long long L = max(iL, B.iL);
    long long fL = max(fL, B.fL);
    if (neg == 0 && B.neg == 1)
    {
        B.neg = 0;
        return (*this) - B;
    }
    else if (neg == 1 && B.neg == 0)
    {
        neg = 0;
        return B - (*this);
    }
    long long pos, t_iSize, t_fSize;
    BigFloat C;
    C.intv.resize(L + 1);
    C.floatv.resize(fL + 1);
    C.neg = neg;
    for (pos = 0; pos <= iSize; pos++)
        C.intv.at(pos) += intv.at(pos);
    for (pos = 0; pos <= B.iSize; pos++)
        C.intv[pos] += B.intv[pos];
    for (pos = 0; pos <= fSize; pos++)
        C.floatv[pos] += floatv[pos];
    for (pos = 0; pos <= B.fSize; pos++)
        C.floatv[pos] += B.floatv[pos];
    t_fSize = (fSize < B.fSize) ? fSize : B.fSize; /*min*/
    for (pos = t_fSize; pos >= 1; pos--)
        C.floatv[pos - 1] += C.floatv[pos] / 10, C.floatv[pos] %= 10;
    C.intv[0] += C.floatv[0] / 10, C.floatv[0] %= 10;
    t_iSize = (iSize > B.iSize) ? iSize : B.iSize; /*max*/
    for (pos = 0; pos <= t_iSize; pos++)
        C.intv[pos + 1] += C.intv[pos] / 10, C.intv[pos] %= 10;
    t_iSize = L, t_fSize = fL;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    if (t_fSize >= 0)
    {
        while (C.floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }
    C.iSize = t_iSize, C.fSize = t_fSize > 99 ? 99 : t_fSize;
    C.iL = t_iSize + 1;
    C.fL = 100;
    return C;
}
BigFloat BigFloat::operator-(BigFloat B)
{
    long long L = max(iL, B.iL);
    long long fL = max(fL, B.fL);
    if (neg == 1 && B.neg == 1)
    {
        B.neg = 0, neg = 0;
        return B - (*this);
    }
    else if (neg == 1 && B.neg == 0)
    {
        neg = 0;
        B.neg = 0;
        BigFloat C = (*this) + B;
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
        BigFloat C = B - (*this);
        C.neg = 1;
        return C;
    }
    long long pos, t_iSize, t_fSize;
    BigFloat C;
    C.intv.resize(L + 1);
    C.floatv.resize(fL + 1);
    for (pos = 0; pos <= iSize; pos++)
        C.intv[pos] = intv[pos];
    for (pos = 0; pos <= fSize; pos++)
        C.floatv[pos] = floatv[pos];
    for (pos = 0; pos <= B.iSize; pos++)
        C.intv[pos] -= B.intv[pos];
    for (pos = 0; pos <= B.fSize; pos++)
        C.floatv[pos] -= B.floatv[pos];
    for (pos = fL - 1; pos >= 1; pos--)
        while (C.floatv[pos] < 0)
            C.floatv[pos - 1]--, C.floatv[pos] += 10;
    while (C.floatv[0] < 0)
        C.intv[0]--, C.floatv[0] += 10;
    for (pos = 0; pos < L; pos++)
        while (C.intv[pos] < 0)
            C.intv[pos + 1]--, C.intv[pos] += 10;
    t_iSize = L, t_fSize = fL;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    if (t_fSize >= 0)
    {
        while (C.floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }

    C.iSize = t_iSize, C.fSize = t_fSize > 99 ? 99 : t_fSize;
    C.iL = t_iSize + 1;
    C.fL = 100;
    return C;
}
BigFloat BigFloat::operator*(BigFloat B)
{
    long long L = max(iL, B.iL);
    long long fL = max(fL, B.fL);
    BigFloat C;
    vector<long long>Aa(L + fL + 1, 0);
    vector<long long>Bb(L + fL + 1, 0);
    vector<long long>Cc(2 * fL + 2 * L + 1, 0);
    C.intv.resize(2 * fL + 2 * L + 1, 0);
    C.floatv.resize(2 * fL + 2 * L + 1, 0);
    long long pos, t_pos, Al = 0, Bl = 0, t_iSize, t_fSize;
    for (pos = fSize; pos >= 0; pos--)
        Aa[Al++] = floatv[pos];
    for (pos = 0; pos <= iSize; pos++)
        Aa[Al++] = intv[pos];
    for (pos = B.fSize; pos >= 0; pos--)
        Bb[Bl++] = B.floatv[pos];
    for (pos = 0; pos <= B.iSize; pos++)
        Bb[Bl++] = B.intv[pos];
    for (pos = 0; pos < Al; pos++)
    {
        for (t_pos = 0; t_pos < Bl; t_pos++)
            Cc[pos + t_pos] += Aa[pos] * Bb[t_pos];
    }
    for (pos = 0; pos < Al + Bl; pos++)
        Cc[pos + 1] += Cc[pos] / 10, Cc[pos] %= 10;
    long long cut = (fSize + 1) + (B.fSize + 1);
    for (pos = cut, t_pos = 0; pos < 2 * fL + 2 * L + 1; pos++, t_pos++)
        C.intv[t_pos] = Cc[pos];
    for (pos = cut - 1, t_pos = 0; pos >= 0 && t_pos < 100; pos--, t_pos++)
        C.floatv[t_pos] = Cc[pos];
    t_iSize = 2 * fL + 2 * L, t_fSize = 2 * fL + 2 * L;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    if (t_fSize >= 0)
    {
        while (C.floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }
    C.iSize = t_iSize, C.fSize = t_fSize > 99 ? 99 : t_fSize;
    C.iL = t_iSize + 1;
    C.fL = 100;
    C.neg = neg ^ B.neg;
    return C;
}
BigFloat BigFloat::operator/(BigFloat B)
{
    BigFloat C;
    long long L = max(iL, B.iL);
    long long fL = max(fL, B.fL);
    long long tL = max(L, fL);
    vector<long long>Aa(3 * tL + 1, 0);
    vector<long long>Bb(3 * tL + 1, 0);
    vector<long long>Cc(2 * fL + 2 * L + 1, 0);
    C.intv.resize(2 * fL + 2 * L + 1);
    C.floatv.resize(2 * fL + 2 * L + 1);
    long long pos, t_pos, Al = L + fL, Bl = 0, t_iSize, t_fSize, i, j;
    for (int t = fSize + 1; t < 100; t++)
    {
        Aa[Al++] = 0;
    }
    for (pos = fSize; pos >= 0; pos--)
        Aa[Al++] = floatv[pos];
    for (pos = 0; pos <= iSize; pos++)
        Aa[Al++] = intv[pos];
    for (pos = B.fSize; pos >= 0; pos--)
        Bb[Bl++] = B.floatv[pos];
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
    long long cut = L + fL - B.fSize + 99;
    for (pos = cut, t_pos = 0; pos < 2 * fL + 2 * L + 1; pos++, t_pos++)
        C.intv[t_pos] = Cc[pos];
    for (pos = cut - 1, t_pos = 0; pos >= 0; pos--, t_pos++)
        C.floatv[t_pos] = Cc[pos];
    t_iSize = 2 * fL + 2 * L, t_fSize = 2 * fL + 2 * L;
    if (t_iSize >= 0)
    {
        while (C.intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }
    if (t_fSize >= 0)
    {
        while (C.floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }
    C.iSize = t_iSize, C.fSize = t_fSize > 99 ? 99 : t_fSize;
    C.iL = t_iSize + 1;
    C.fL = 100;
    C.neg = neg ^ B.neg;
    return C;
}
BigFloat BigFloat::operator+(string s)
{
    BigFloat B(s);
    return *this + B;
}
BigFloat BigFloat::operator-(string s)
{
    BigFloat B(s);
    return *this - B;
}
BigFloat BigFloat::operator*(string s)
{
    BigFloat B(s);
    return *this * B;
}
BigFloat BigFloat::operator/(string s)
{
    BigFloat B(s);
    return *this / B;
}
BigFloat BigFloat::operator^(string s)
{
                BigFloat B(s);
                return *this ^ B;
}


BigFloat BigFloat::operator+(long long s)
{
    BigFloat B(s);
    return *this + B;
}
BigFloat BigFloat::operator-(long long s)
{
    BigFloat B(s);
    return *this - B;
}
BigFloat BigFloat::operator*(long long s)
{
    BigFloat B(s);
    return *this * B;
}
BigFloat BigFloat::operator/(long long s)
{
    BigFloat B(s);
    return *this / B;
}

BigFloat BigFloat::operator^(long long s)
{
                BigFloat B(s);
                return *this ^ B;
}
BigFloat BigFloat::operator+(double s)
{
    BigFloat B(s);
    return *this + B;
}
BigFloat BigFloat::operator-(double s)
{
    BigFloat B(s);
    return *this - B;
}
BigFloat BigFloat::operator*(double s)
{
    BigFloat B(s);
    return *this * B;
}
BigFloat BigFloat::operator/(double s)
{
    BigFloat B(s);
    return *this / B;
}
BigFloat BigFloat::operator^(double  s)
{
                BigFloat B(s);
                return *this ^ B;
}

BigFloat operator+(string s, BigFloat B)
{
    BigFloat A(s);
    return  A + B;
}
BigFloat operator-(string s, BigFloat B)
{
    BigFloat A(s);
    return  A - B;
}
BigFloat operator*(string s, BigFloat B)
{
    BigFloat A(s);
    return  A * B;
}
BigFloat operator/(string s, BigFloat B)
{
    BigFloat A(s);
    return  A / B;
}
BigFloat operator+(long long s, BigFloat B)
{
    BigFloat A(s);
    return  A + B;
}
BigFloat operator-(long long s, BigFloat B)
{
    BigFloat A(s);
    return  A - B;
}
BigFloat operator*(long long s, BigFloat B)
{
    BigFloat A(s);
    return  A * B;
}
BigFloat operator/(long long s, BigFloat B)
{
    BigFloat A(s);
    return  A / B;
}
BigFloat operator+(double s, BigFloat B)
{
    BigFloat A(s);
    return  A + B;
}
BigFloat operator-(double s, BigFloat B)
{
    BigFloat A(s);
    return  A - B;
}
BigFloat operator*(double s, BigFloat B)
{
    BigFloat A(s);
    return  A * B;
}
BigFloat operator/(double s, BigFloat B)
{
    BigFloat A(s);
    return  A / B;
}
void BigFloat::operator=(string s)
{
    long long pos = 0, l = s.size(), cut = l, t_pos = 0, t_iSize = 0, t_fSize = 0, neg = 0;
    long long L = l;
    if (s[0] == '-')
        neg = 1;
    for (pos = neg; pos < l; pos++)
        if (s[pos] == '.')
            cut = pos;
    iL = cut;
    fL = 100;
    intv.resize(iL);
    floatv.resize(fL);

    for (pos = cut - 1, t_pos = 0; pos >= neg; pos--, t_pos++)
        intv[t_pos] = s[pos] - '0';
    for (pos = cut + 1, t_pos = 0; pos < l && t_pos < 100; pos++, t_pos++)
        floatv[t_pos] = s[pos] - '0';
    t_iSize = iL - 1, t_fSize = fL - 1;
    if (t_iSize >= 0)
    {
        while (intv[t_iSize] == 0)
        {
            t_iSize--;
            if (t_iSize == -1)
                break;
        }
    }

    if (t_fSize >= 0)
    {
        while (floatv[t_fSize] == 0)
        {
            t_fSize--;
            if (t_fSize == -1)
                break;
        }
    }
    iSize = t_iSize, fSize = t_fSize > 99 ? 99 : t_fSize;
}
void BigFloat::operator=(BigFloat B)
{
    intv.clear();
    floatv.clear();
    iL = B.iL;
    fL = 100;
    intv.resize(iL);
    floatv.resize(fL);
    for (int i = 0; i < iL; i++)
    {
        intv[i] = B.intv[i];
    }
    for (int i = 0; i < fL; i++)
    {
        floatv[i] = B.floatv[i];
    }
    neg = B.neg;
    iSize = B.iSize;
    fSize = B.fSize;

}
BigFloat BigFloat::Power(string num)
{
    string t = "1";
    BigFloat C = t;
    BigFloat B = *this;
    long long temp = atoi(num.c_str());
    for (int i = 0; i < temp; i++)
    {
        C = C * B;
    }

    return C;
}
BigFloat BigFloat::Power(BigFloat B)
{
    string t = "1";
    BigFloat C = t;
    BigFloat pos = *this;
    long long temp = 0;
    for (long long i = 0; i < B.intv.size(); i++)
    {
        temp += B.intv[i] * pow(10, i);
    }
    for (int i = 0; i < temp; i++)
    {

        C = C * pos;
    }

    return C;
}
long long BigFloat::Check(vector<long long> a, vector<long long> b, long long lb, long long lc)
{
    long long pos;
    for (pos = lb - 1; pos >= 0; pos--)
    {
        if (a[pos + lc] < b[pos])
            return 0;
        if (a[pos + lc] > b[pos])
            return 1;
    }
    return 1;
}
BigFloat BigFloat::Fac(void)
{
    BigFloat C;

    long long temp = 0;
    for (long long i = 0; i < intv.size(); i++)
    {
        temp += intv[i] * pow(10, i);
    }
    long long digit = 1, i, j;
    vector<long long> result;

    result.push_back(1);

    for (j = 1; j <= temp; j++)
    {

        //???d?n???X????
        digit = result.size() - 1;
        while (result[digit] == 0)
        {
            digit--;
        }

        //?i?????k
        //?C??digit?????X????
        for (i = 0; i <= digit; i++)
            result[i] *= j;
        //?B?z?U??digit?i???????D
        for (i = 0; i <= digit; i++)
        {
            int k = 0; //?????q?A?B?z?W?L???????????D
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
    for (long long i = 0; i <= digit; i++)
    {
        C.intv[i] = result[i];
    }
    C.floatv.resize(100);
    C.iSize = digit;
    C.iL = digit + 1;
    C.fSize = 0;
    return C;
}
void BigFloat::Print()
{
    long long pos;
    if (neg == 1)
        cout << "-";
    for (pos = iSize; pos >= 0; pos--)
        cout << intv[pos];
    if (iSize == -1)
        cout << '0';
    cout << '.';
    for (pos = 0; pos < 100; pos++)
        cout << floatv[pos];
    cout << '\n';

}

BigFloat BigFloat::operator^(const BigFloat& B)
{
                BigFloat tempA;
                BigFloat ans=(*this);
                if (B.floatv[0] == 5)
                {
                                tempA = sqrt((*this));
                }
                else if(B.floatv[0]!=0)
                {
                                cout << "operator ^ can only do square root " << endl;
                }
                for (BigFloat i("2"); i <= B; i = i + 1.0)
                {
                                ans = ans * (*this);
                }
                ans = ans + tempA;
                return ans;
}


BigFloat sqrt(BigFloat B)
{
                BigFloat ans;//return ans
                if (B.neg == 1)
                {
                                ans.neg = 1;
                                return ans;
                }
                ans.floatv.clear();

                if (B.iL % 2 != 0)
                                B.intv.push_back(0);
                if (B.fL % 2 != 0)
                                B.floatv.push_back(0);
                if (B.fL < 100)
                {
                                for (int i = 0; i < 100 - B.fL; i++)
                                {
                                                B.floatv.push_back(0);
                                }
                }
                BigFloat T;//?U?@?h????????????????
                BigFloat Tans;//??????a+2b
                while (!B.intv.empty())
                {
                                string str;
                                for (int i = 0; i < 2; i++)
                                {
                                                str += (*(B.intv.end() - 1) + '0');
                                                B.intv.erase(B.intv.end() - 1);
                                }
                                str += '\0';
                                long long t = stoi(str);//take the first two digit
                                T = T * 100.0;//left shift two digit
                                T = T + t;
                                Tans = Tans * 10.0;//Tans?????@??
                                for (double x= 9; x >= 0; x--)
                                {
                                                BigFloat test = Tans + x;
                                                if (test * x <= T)
                                                {
                                                                T = T - test * x;
                                                                Tans =test+x;
                                                                ans.intv.insert(ans.intv.begin(), x);
                                                                ans.iSize++;
                                                                ans.iL++;
                                                                break;
                                                }
                                }
                }
                while (!B.floatv.empty())//float point
                {
                                string str;
                                for (int i = 0; i < 2; i++)
                                {
                                                str += (*B.floatv.begin()) + '0';
                                                B.floatv.erase(B.floatv.begin() );
                                }
                                str += '\0';
                                long long t = stoi(str);//take the first two digit
                                T = T * 100.0;//left shift two digit
                                T = T + t;
                                Tans = Tans * 10.0;//Tans?????@??
                                for (double x = 9; x >= 0; x--)
                                {
                                                BigFloat test = Tans + x;
                                                if (test * x <= T)
                                                {
                                                                T = T - test * x;
                                                                Tans = test + x;
                                                                ans.floatv.push_back(x);
                                                                break;
                                                }
                                }
                                if (ans.floatv.size() < 100 && B.floatv.size() == 0)
                                {
                                                for (int i = 0; i < 2; i++)
                                                {
                                                                B.floatv.push_back(0);
                                                }
                                }
                }
                ans.iSize = ans.intv.size() - 1;
                if (ans.floatv.size() < 100)
                {
                                for (int i = ans.floatv.size(); i < 100; i++)
                                {
                                                ans.floatv.push_back(0);
                                }
                }
                ans.fSize = ans.floatv.size() - 1;
                ans.iL = ans.iSize + 1;
                ans.fL = ans.fSize + 1;
                return ans;
}

bool BigFloat::operator ==(const BigFloat& B)
{
                if (iSize != B.iSize||fSize!=B.fSize||neg!=B.neg)
                                return 0;
                for (int i = iSize ; i >= 0; i--)
                {
                                if (intv[i] != B.intv[i])
                                                return 0;
                }
                for (int i = 0; i <= fSize; i++)
                {
                                if (floatv != B.floatv)
                                {
                                                return 0;
                                }
                }
                return 1;
}
bool BigFloat::operator <(const BigFloat& B)
{
                if (neg == 1 && B.neg == 0)//-<+
                                return 1;
                if (neg == 0 && B.neg == 1)//+>-
                                return 0;
                if (neg == B.neg&&neg==0)//A>0B>0
                {
                                if (iSize < B.iSize)
                                                return 1;
                                if (iSize > B.iSize)
                                                return 0;
                                if (iSize == B.iSize)
                                {
                                                for (int i = iSize; i >= 0; i--)
                                                {
                                                                if (intv[i] < B.intv[i])
                                                                                return 1;
                                                                if (intv[i] > B.intv[i])
                                                                                return 0;
                                                }
                                                for (int i = 0; i < floatv.size(); i++)
                                                {
                                                                if (floatv[i] < B.floatv[i])
                                                                                return 1;
                                                                if (floatv[i] > B.floatv[i])
                                                                                return 0;
                                                }
                                }
                }
                if (neg == B.neg && neg ==1 )//A<0B<0
                {
                                if (iSize < B.iSize)
                                                return 0;
                                if (iSize > B.iSize)
                                                return 1;
                                if (iSize == B.iSize)
                                {
                                                for (int i = iSize; i >= 0; i--)
                                                {
                                                                if (intv[i] < B.intv[i])
                                                                                return 0;
                                                                if (intv[i] > B.intv[i])
                                                                                return 1;
                                                }
                                                for (int i = 0; i < floatv.size(); i++)
                                                {
                                                                if (floatv[i] < B.floatv[i])
                                                                                return 0;
                                                                if (floatv[i] > B.floatv[i])
                                                                                return 1;
                                                }
                                }
                }
}
bool BigFloat::operator <=(const BigFloat& B)
{
                return ((*this) == B || (*this) < B);
}

ostream& operator<<(ostream& ostr, const BigFloat& B)
{
                if (B.neg == 1)
                                ostr << "-";
                int i = B.iSize;
                while (i >= 0 && B.intv[i] == 0)
                {
                                i--;
                                if (i < 0)
                                {
                                                i = 0;
                                                break;
                                }
                }
                for (i; i >= 0; i--)
                {
                                ostr << B.intv[i];
                }
                int end = B.fSize;
                for (end ; end > 0; end--)
                {
                                if (B.floatv[end] != 0)
                                                break;
                }
                if(B.fSize!=-1)
                                ostr << ".";

                for (i=0 ; i <= end; i++)
                {
                                ostr << B.floatv[i];
                }
                return ostr;
}
