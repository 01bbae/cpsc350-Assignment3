#ifndef DELIMITER_H
#define DELIMITER_H
#include <iostream>

using namespace std;

class Delimiter{
public:
  Delimiter();
  Delimiter(char delimiter, int linenumber);
  ~Delimiter();
  char getDelimiter();
  int getLine();
  char getOpposite();

private:
  char delimiter;
  int linenumber;
};

#endif
