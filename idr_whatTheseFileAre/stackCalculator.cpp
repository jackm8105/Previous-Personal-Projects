#include <iostream>
#include "StackCalculator.hpp"


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-') 
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
    getStackHead();
    if(stackHead != NULL)
    {
        stackHead = NULL;
    }
    else
    {
        return;
    }
}

StackCalculator::~StackCalculator()
{
    while(!isEmpty())
    {
        pop();
    }
}

bool StackCalculator::isEmpty()
{
	if(stackHead == NULL)
    {
        return true;
    }
    return false;
}

void StackCalculator::push(float number)
{
    Operand* newNode = new Operand;
    newNode->next = stackHead;
    newNode->number = number;
    stackHead = newNode;
}

void StackCalculator::pop()
{
	if(stackHead != NULL)
    { 
        Operand* temp = stackHead->next;
        delete stackHead;
        stackHead = temp;
    }
    else
    {
        cout << "Stack empty, cannot pop an item." << endl;
        return;
    }
}

Operand* StackCalculator::peek()
{ 
	if(stackHead != NULL)
    {
        return stackHead;
    }
    else
    {
        cout << "stack empty, cannot peek." << endl;
        return nullptr;
    }
}

bool StackCalculator:: evaluate(string* s, int size)
{
    for(int i = size - 1; i >= 0; i--)
    {
        if(!isNumber(s[i]) && s[i] != "+" && s[i] != "*")
        {
            cout << "err: invalid operation" << endl;
            return false;
        }
        else if(isNumber(s[i]))
        {
            float sInt = stof(s[i]);
            push(sInt);
        }
        else if(s[i] == "+")
        {
            if(isEmpty())
            {
                cout << "err: not enough operands" << endl;
                return false;
            }
            float peekOne = peek()->number;
            pop();
            if(isEmpty())
            {
                cout << "err: not enough operands" << endl;
                return false;
            }
            float peekTwo = peek()->number;
            pop();
            float newValue = peekOne + peekTwo;
            push(newValue);
        }
        else if(s[i] == "*")
        {
            if(isEmpty())
            {
                cout << "err: not enough operands" << endl;
                return false;
            }
            float peekOne = peek()->number;
            pop();
            if(isEmpty())
            {
                cout << "err: not enough operands" << endl;
                return false;
            }
            float peekTwo = peek()->number;
            pop();
            float newValue = peekOne * peekTwo;
            push(newValue);
        }
    }
	return true;
}