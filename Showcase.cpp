#include <bits/stdc++.h>
#include "BigReal.cpp"

using namespace std;

int main() {

    cout << "a)Calculate\nb)Compare\n";
    char c; cin >> c; string s;
    BigReal x(""); BigReal y(""); BigReal z("");

    switch (tolower(c)) {

        case 'a':
            cout << "Enter the first number: ";
            cin >> s;
            x = BigReal(s);

            cout << "choose the operation (+/-): ";
            cin >> c;

            cout << "Enter the second number: ";
            cin >> s;
            y = BigReal(s);

            switch (c) {
                case '+':
                    z = x + y;
                    break;

                case '-':
                    z = x - y;
                    break;
            }

            cout << z<<'\n';
            break;

        case 'b':

            cout << "Enter the first number: ";
            cin >> s;
            x = BigReal (s);

            cout << "Enter the second number: ";
            cin >> s;
            y = BigReal(s);

            if (y < x) cout << x << " is Bigger\n";

            if (y > x) cout << y << " is Bigger\n";

            if (x == y) cout << x << " is Equal to " << y << '\n';

    }
    system("pause");
}