#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "singleLL.hpp"
int main()
{
  SLL s1("demo");
  cout<< "before"<<endl;
  s1.displayList();
  cout<< "after"<<endl;
  s1.split("fluffy");
  s1.displayList();
  return 0;
}