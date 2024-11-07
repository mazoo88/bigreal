
#include "BigReal.h"

BigReal::BigReal(string s) {

    whole = "0";
    if (s[0] == '-') sign = '-';
    else sign = '+';

    bool left = 1;
    for (int i = 0; i < s.size(); ++i) {
        if (i == 0 && (s[0] == '+' || s[0] == '-')) continue;
        if (s[i] == '.') left = 0;
        else if (left && isdigit(s[i])) whole += s[i];
        else if (isdigit(s[i])) decimal += s[i];
    }

    while (whole.size() > 1 && whole[0] == '0')
        whole = whole.substr(1, whole.size() - 1);

    while (decimal.size() > 0 && decimal[decimal.size() - 1] == '0')
        decimal = decimal.substr(0, decimal.size() - 1);

}

BigReal::BigReal(BigReal &another){
    *this = another;
}


bool compare(string& anotherWhole , string& whole, string& anotherDecimal, string& decimal){

    if (anotherWhole.size() > whole.size())
        return true;

    if (anotherWhole.size() < whole.size())
        return false;

    if (anotherWhole.size() == whole.size())
        for (int i = 0; i < whole.size(); ++i)

            if (anotherWhole[i] > whole[i])
                return true;

            else if (anotherWhole[i] < whole[i])
                return false;

    for (int i = 0; i < min(decimal.size(), anotherDecimal.size()); ++i)

        if (anotherDecimal[i] > decimal[i])
            return true;

        else if (anotherDecimal[i] < decimal[i])
            return false;

    if (anotherDecimal.size() > decimal.size())
        return true;

    return false;
}

bool BigReal::operator==(BigReal another) {
    if (sign != another.sign) return false;
    if (whole != another.whole) return false;
    if (decimal != another.decimal) return false;
    return true;
}

bool BigReal::operator<(BigReal another) {

    if (sign != another.sign) {

        if (another.sign == '+')
            return true;

        else if (sign == '+')
            return false;
    }

    else {

        if (sign == '-') {
            return compare(whole, another.whole, decimal, another.decimal);
        }

        else {
            return compare(another.whole, whole, another.decimal, decimal);
        }
    }
}

bool BigReal::operator>(BigReal another) {

   return (! (*this < another) && !(*this == another));
}


void padding (string& operand1 , string& operand2, string side){

    int length;
    if (operand1.empty())
        length = operand2.size();

    else if (operand2.empty())
        length = operand1.size();

    else
        length = operand1.size() - operand2.size();

    length = abs(length);

    string zeros = string(length, '0');


    if (operand1.size() > operand2.size()) {

        if (side == "right")
            operand2 += zeros;

        if (side == "left")
            operand2 = zeros + operand2;
    }

    else {
        if (side == "right")
            operand1 += zeros;

        if (side == "left")
            operand1 = zeros + operand1;
    }
}

int add(string &sum, int carry, string operand1, string operand2) {

    for (int i = operand1.size() - 1; i > -1; --i) {
        char digit = ((operand1[i] - 48 + operand2[i] - 48 + carry) % 10) + 48;
        carry = (operand1[i] - 48 + operand2[i] - 48 + carry) / 10;
        sum = digit + sum;
    }
    return carry;
}

int subtract(string &sum, int carry, string operand1, string operand2) {

    for (int i = operand1.size() - 1; i > -1; --i) {
        char digit = ((operand1[i] - 48) + 10 * (operand1[i] + carry < operand2[i]) - (operand2[i] - 48) + carry) + 48;
        carry = -1 * (operand1[i] + carry < operand2[i]);
        sum = digit + sum;
    }
    return carry;
}


BigReal BigReal::operator+(BigReal another) {

    string sum;
    padding (whole, another.whole, "left");
    padding (decimal, another.decimal, "right");

    if (sign == another.sign) {

        int carry = add(sum, 0, decimal, another.decimal);
        sum = "." + sum ;
        carry = add(sum, carry, whole, another.whole);
        if (carry) sum = "1" + sum;
        sum = sign + sum;

    }

    else {

        if (compare(another.whole, whole, another.decimal, decimal)) {

            int carry = subtract(sum, 0, another.decimal, decimal);
            sum = "." + sum ;
            subtract(sum, carry, another.whole, whole);
            sum = another.sign + sum;

        }

        else {

            int carry = subtract(sum, 0, decimal, another.decimal);
            sum = "." + sum ;
            subtract(sum, carry, whole, another.whole);
            sum = sign + sum;

        }
    }

    BigReal result(sum);
    return result;
}

BigReal BigReal::operator-(BigReal another) {

    string difference;
    padding (whole, another.whole, "left");
    padding (decimal, another.decimal, "right");

    if (sign != another.sign) {

        int carry = add(difference, 0, decimal, another.decimal);
        difference = "." + difference;
        carry = add(difference, carry, whole, another.whole);
        if (carry) difference = "1" + difference;
        difference = sign + difference;
    }

    else {

        if (compare(whole , another.whole, decimal, another.decimal)) {

            int carry = subtract(difference, 0, decimal, another.decimal);
            difference = "." + difference;
            carry = subtract(difference, carry, whole, another.whole);
            difference = sign + difference;
        }
        else {

            int carry = subtract(difference, 0, another.decimal, decimal);
            difference = "." + difference ;
            carry = subtract(difference, carry, another.whole, whole);
            difference = another.sign + difference;
        }

    }


    BigReal result(difference);
    return result;
}


ostream& operator<< (ostream& out, BigReal& num){
    out << (num.sign=='-' ? '-':' ') << num.whole << (num.decimal=="" ? ' ':'.') << num.decimal;
}
