#include "Delimiter.h"


Delimiter::Delimiter(){
  //default constructor
}

Delimiter::Delimiter(char delimiter, int linenumber){
  this->delimiter=delimiter;
  this->linenumber=linenumber;
}

Delimiter::~Delimiter(){
  //delete
}

char Delimiter::getDelimiter(){
  return delimiter;
}

int Delimiter::getLine(){
  return linenumber;
}

char Delimiter::getOpposite(){
  if(delimiter =='{'){
    return '}';
  }else if(delimiter == '['){
    return ']';
  }else if (delimiter == '('){
    return ')';
  }else if(delimiter == '}'){
    return '{';
  }else if (delimiter == ']'){
    return '[';
  }else{
    return '(';
  }
}
