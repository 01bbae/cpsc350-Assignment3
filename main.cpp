#include <iostream>
#include "IO.h"

using namespace std;

int main(int argc, char** argv){
  if(argc!=2){
    cout << "enter a filename in the command line arguement" << endl;
  }else{
    cout << argv[1] << endl;
    IO* i = new IO(argv[1]);
    i->runProgram();
  }
  return 0;
}
