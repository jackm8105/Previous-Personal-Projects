#include<iostream>
#include<cmath>
#include<iomanip>
#include "StackCalculator.hpp"

using namespace std;



int main()
{
    // stack to hold the operands
    StackCalculator stack;

    int numElement = 0;
    string* inparr = new string[50];

    // enter a number
    string number;
    cout << "Enter the operators and operands ('+', '*') in a prefix format" << endl;

    while(true)
    {
        cout << "#> ";

        string token;
        cin >> token;

        if(token == "=")
        {
            if(numElement == 0)
            {
                cout << "No operands: Nothing to evaluate" << endl;
                return 0;
            }
            else
            {
                bool isValid = stack.evaluate(inparr, numElement);
                if(isValid)
                {
                    float result = stack.peek()->number;
                    cout << "Result= " << result << endl;
                    return 0;
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            inparr[numElement] = token;
            numElement++;
        }
    }
    return 0;
}