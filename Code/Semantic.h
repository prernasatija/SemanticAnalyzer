#include<stack>
#ifndef SEMANTIC_H_
#define SEMANTIC_H_
#include<map>
#include<string>
#include<stdio.h>
#include<iostream>
#include "lexer.h"

using namespace std;


struct Value { 
    string type;
	string scope; 

    bool operator==(const Value &o) {
        return type == o.type && scope == o.scope;
    }

    bool operator<(const Value &o) {
        return type < o.type || (type == o.type && scope < o.scope);
    }
};


class Semantic{

  public :
 
    void insert(string name, string type, string scope);
	bool search(string name);
	bool search(string name, string scope);
	string getType(string name);
	string checkScope(string name, string currScope);
	string getType(string name, string scope);
	string getScope(string name);
    std::stack <string> first; 
    int funcCubeUnary(int state, int type);
    int funcCubeBinary(int state, int type1, int type2);
    void displaySymbol();
    string calculateTypeBinary(string type1,string type2, string op);
    string calculateTypeUnary(string type1,string op);
    int op_Func(string op);
    int Operand(string oper);
    bool isTypeMatching(string type1, string type2);
    string pushType(int cubeState);
    bool isBoolean(string type);
    	
};
extern Semantic sem;
extern stack<string> stack1;  
    
// your code goes here

#endif
