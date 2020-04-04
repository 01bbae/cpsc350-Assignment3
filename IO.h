#include <iostream>
#include <fstream>
#include <ios>
#include <exception>

using namespace std;

class IO{
public:
  IO();
  IO(string filename);
  ~IO();
  void runProgram();

private:
  string filename;
  ifstream ifs;
};
