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
  GenStack<Delimiter*>* g= new GenStack<Delimiter*>(10);
  while(input == "yes"){
  try{
    ifs.open(filename);
    ifs.exceptions( ifstream::badbit );

      string buffer;
      int line = 0;
      while(ifs>>buffer){
        line++;
        for(int i=0;i<buffer.size();++i){
          if(buffer[i]=='('){
            g->push(new Delimiter('(',line));
          }else if(buffer[i]==')'){
            g->push(new Delimiter(')',line));
          }else if(buffer[i]=='{'){
            g->push(new Delimiter('{',line));
          }else if(buffer[i]=='}'){
            g->push(new Delimiter('}',line));
          }else if(buffer[i]=='['){
            g->push(new Delimiter('[',line));
          }else if(buffer[i]==']'){
            g->push(new Delimiter(']',line));
          }
        }
      }
  }catch(const ifstream::failure& e){
    cout <<"error opening/reading file" << endl;
  }

  try{
      GenStack<Delimiter*>* c= new GenStack<Delimiter*>(g->getSize()/2);
      for(int i=0;i<g->getSize()/2;++i){
        c->push(g->pop());
      }
      if(g->getSize()%2==0){ //even number of delimiters
        while(!g->isEmpty()){
          if(g->peek()->getDelimiter() == c->peek()->getDelimiter()){
            g->pop();
            c->pop();

          }else{
            if(g->peek()->getDelimiter() != c->peek()->getDelimiter()){
              cout << "Line " << c->peek()->getLine() << ": expected " << c->peek()->getOpposite() << " and found " << c->peek()->getDelimiter() << endl;
              exit(EXIT_FAILURE);
            }
          }
        }
      }else{
        while(!c->isEmpty()){
          if(g->peek()->getDelimiter() == c->peek()->getDelimiter()){
            g->pop();
            c->pop();

          }else{
            if(g->peek()->getDelimiter() != c->peek()->getDelimiter()){
              cout << "Line " << c->peek()->getLine() << ": missing " << g->peek()->getOpposite() << endl;
              exit(EXIT_FAILURE);
            }
          }
          cout << "Reached end of file: missing " << g->pop()->getOpposite() << endl;
          exit(EXIT_FAILURE);
        }
      }

      cout << "all good!" <<endl;
      cout << "continue? (yes/no)" << endl;
      cin >> input;
      ifs.close();
      delete g;
      delete c;
      if(input =="yes"){
        cout << "enter filename: " << endl;
        cin >> filename;
      }
    }catch(const char* msg){
      cout << msg << endl;
    }
   input = "no";
  }
}
