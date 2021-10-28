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
  stackHead = NULL;
}

StackCalculator::~StackCalculator()
{
  Operand *n;
  while(stackHead != nullptr)
    {
        n = stackHead->next;
        delete stackHead;
        stackHead = n;
    }
}

bool StackCalculator::isEmpty()
{
	if(stackHead == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void StackCalculator::push(float number)
{
  Operand *n = new Operand;

  n->number = number;
  n->next = stackHead;
  stackHead = n;
}

void StackCalculator::pop()
{
	if(isEmpty() == true)
  {
    cout << "Stack empty, cannot pop an item." << endl;
  }
  else
  {
    Operand *n = stackHead;
    stackHead = stackHead->next;
    delete n;
  }
}

Operand* StackCalculator::peek()
{
  if(stackHead == nullptr)
  {
    cout << "Stack empty, cannot peek." << endl;
    return nullptr;
  }
  else
  {
    return stackHead;
  }
}

int getsize(Operand *stackHead)
{
  if(stackHead == nullptr)
  {
    return 0;
  }
  
  Operand *n = stackHead;
  int i = 1;
  while(n->next != nullptr)
  {
    i++;
    n = n->next;
  }
  return i;
}

bool StackCalculator:: evaluate(string* s, int size)
{
    /*TODO: 1.scan the array from the end
            2.Use isNumber function to check if the input is an operand
            3.push all operands to the stack
            4.If operator take two element of from the stack,
              compute and put the result back in stack
            5.Handle the boundery cases as required.
            6.Read the writeup for more details
    */
   string current;
   for(int i = size - 1; i >= 0; i--)
   {
      current = s[i];
      if(isNumber(current) == true)
      {
        push(std::stof(current));
      }
      else if(current == "+")
      {
        if(getsize(stackHead) < 2)
        {
          cout << "err: not enough operands" << endl;
          return false;
        }
        
        float f = stackHead->number;
        float n = stackHead->next->number;

        pop();
        pop();
        push(f + n);
      }
      else if(current == "*")
      {
        if(getsize(stackHead) < 2)
        {
          cout << "err: not enough operands" << endl;
          return false;
        }
        
        float f = stackHead->number;
        float n = stackHead->next->number;

        pop();
        pop();
        push(f * n);
      }
      else
      {
        cout << "err: invalid operation" << endl;
        return false;
      }
   }

		return true;
}
