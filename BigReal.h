

#ifndef BIGREAL_BIGREAL_H
#define BIGREAL_BIGREAL_H

#include <bits/stdc++.h>
using namespace std;


class BigReal {

private:
    char sign;
    string whole;
    string decimal;

public:

    BigReal(string);
    BigReal(BigReal &another);

    BigReal operator+(BigReal another);
    BigReal operator-(BigReal another);

    bool operator==(BigReal another);
    bool operator<(BigReal another);
    bool operator>(BigReal another);

    friend ostream& operator<< (ostream& out, BigReal& num);

};




#endif //BIGREAL_BIGREAL_H
