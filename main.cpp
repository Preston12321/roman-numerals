#include <iostream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

int romanToInt(const string &input);
string intToRoman(int input);

int main() {

    while (true) {

        cout << endl;
        cout << "1: Convert from roman numeral to integer" << endl;
        cout << "2: Convert from integer to roman numeral" << endl;
        cout << "3: Exit" << endl;
        cout << endl << "> ";

        int choice;
        cin >> choice;

        if (choice == 1) {

            cout << endl;
            cout << "Please enter a valid roman numeral to be converted." << endl;
            cout << endl << "> ";

            string input;
            cin >> input;

            int output = romanToInt(input);

            if (output == -1) {

                cout << endl;
                cerr << "ERROR: Invalid roman numeral input" << endl;

            }
            else {

                cout << endl;
                cout << input << " = " << romanToInt(input) << endl;

            }

        } else if (choice == 2) {

            cout << endl;
            cout << "Please enter a valid integer to be converted." << endl;
            cout << endl << "> ";

            int input;
            cin >> input;

            if (input < 1 || input > 3999) {

                cout << endl;
                cerr << "ERROR: Integer input out of bounds" << endl;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }
            else {

                cout << endl;
                cout << input << " = " << intToRoman(input) << endl;

            }

        } else if (choice == 3) {

            return 0;

        } else {

            cout << endl;
            cerr << "ERROR: Invalid choice input" << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }

    }

}

/*
 * Takes in a capitalized string that represents a roman numeral
 * and returns the corresponding integer value.
 */
int romanToInt(const string &input) {

    // Validate input to roman numeral rules
    if (!regex_match(input, regex("M{0,3}(CM)?D?(CD)?C{0,3}(XC)?L?(XL)?X{0,3}(IX)?V?I{0,3}"))) {

        return -1;

    }

    if (input.length() == 1) {

        if (input == "I") return 1;
        if (input == "V") return 5;
        if (input == "X") return 10;
        if (input == "L") return 50;
        if (input == "C") return 100;
        if (input == "D") return 500;
        if (input == "M") return 1000;
        return -1;

    }

    // The number of characters to split off the front; equals either 1 or 2
    unsigned int split;

    // Test first two chars for special subtraction combinations
    if (regex_match(input.substr(0, 2), regex("(IV|IX|XL|XC|CD|CM)"))) {

        if (input.length() == 2) {

            if (input == "IV") return 4;
            if (input == "IX") return 9;
            if (input == "XL") return 40;
            if (input == "XC") return 90;
            if (input == "CD") return 400;
            if (input == "CM") return 900;
            return -1;

        }
        else {

            split = 2;

        }

    }
    else {

        split = 1;

    }

    int lhs = romanToInt(input.substr(0, split));
    int rhs = romanToInt(input.substr(split));

    if (lhs == -1 || rhs == -1) {
        return -1;
    }

    return lhs + rhs;

}

const string numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
const int integers[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

/*
 * Takes in an integer value and returns the corresponding
 * capitalized string representing a roman numeral.
 */
string intToRoman(int input) {

    stringstream output;

    for (int i = 0; i < 13; i++) {

        while (input >= integers[i]) {

            output << numerals[i];

            input -= integers[i];

        }

    }

    return output.str();

}