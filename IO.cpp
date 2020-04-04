#include "IO.h"
#include "Delimiter.h"
#include "GenStack.h"

IO::IO(){
  //default constructor
  cout << "Enter filename" << endl;
}

IO::IO(string filename){
  this->filename = filename;
}


IO::~IO(){
  //delete
}


void IO::runProgram(){
  string input = "yes";
  while(input == "yes"){
    GenStack<Delimiter*>* g= new GenStack<Delimiter*>(10);
    GenStack<Delimiter*>* oppo= new GenStack<Delimiter*>(10);
  try{
    ifs.open(filename);
    ifs.exceptions( ifstream::badbit );
    string str;
      int line = 0;
      while(getline(ifs,str)){
        line++;
        for(int i=0;i<str.size();++i){
          if(str[i]=='('){
            g->push(new Delimiter('(',line));
          }else if(str[i]==')'){
            if(g->peek()->getOpposite() == ')'){
              g->pop();
            }else{
              oppo->push(new Delimiter(')',line));
            }
          }else if(str[i]=='{'){
            g->push(new Delimiter('{',line));
          }else if(str[i]=='}'){
            if(g->peek()->getOpposite() == '}'){
              g->pop();
            }else{
              oppo->push(new Delimiter('}',line));
            }
          }else if(str[i]=='['){
            g->push(new Delimiter('[',line));
          }else if(str[i]==']'){
            if(g->peek()->getOpposite() == ']'){
              g->pop();
            }else{
              oppo->push(new Delimiter(']',line));
            }
          }
        }
      }
  }catch(const ifstream::failure& e){
    cout <<"error opening/reading file" << endl;
  }

  // while(!g->isEmpty()){
  //   cout << g->peek()->getDelimiter() << g->peek()->getLine() << endl;
  //   g->pop();
  // }

  try{
    GenStack<Delimiter*>* c= new GenStack<Delimiter*>(10);
    while(!oppo->isEmpty()){
      c->push(oppo->pop());
    }
      if(g->getSize()==c->getSize()){ //even number of delimiters check if there are any mismatched
        while(!g->isEmpty()){
          if(g->peek()->getDelimiter() == c->peek()->getDelimiter()){ //the ends are the same
            g->pop();
            c->pop();

          }else{
            if(g->peek()->getDelimiter() != c->peek()->getDelimiter()){ //
              cout << "Line " << g->peek()->getLine() << ": expected " << g->peek()->getOpposite() << " and found " << c->peek()->getDelimiter() << endl;
              exit(EXIT_FAILURE);
            }
          }
        }
      }else{ //odd number of delimiters check which one needs adding
        while(!c->isEmpty()&&!g->isEmpty()){
          if(g->peek()->getDelimiter() == c->peek()->getDelimiter()){
            g->pop();
            c->pop();

          }else{
            if(g->peek()->getDelimiter() != c->peek()->getDelimiter()){
              cout << "Line " << g->peek()->getLine() << ": missing " << g->peek()->getOpposite() << endl;
              exit(EXIT_FAILURE);
            }
          }
          cout << "Reached end of file: missing " << g->pop()->getOpposite() << endl;
          exit(EXIT_FAILURE);
        }
      }

      cout << "all good!" <<endl;
      ifs.close();
      cout << "continue? (yes/no)" << endl;
      cin >> input;
      if(input =="yes"){
        cout << "enter filename: " << endl;
        cin >> filename;
        runProgram();
      }
      delete c;
    }catch(const char* msg){
      cout << msg << endl;
    }
    delete g;
    delete oppo;
  }
}
