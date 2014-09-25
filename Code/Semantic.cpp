#include<stdio.h>
#include<iostream>
#include<string>
#include<map>
#include<stack>
#include "Semantic.h"
#define OP_PLUS 1
#define OP_MINUS 2
#define OP_MULTIPLY 3
#define OP_DIVIDE 4
#define OP_GREATER 5
#define OP_LOWER 6
#define OP_NOT 7
#define OP_AND 8
#define OP_OR 9
#define OP_MINUS_UNARY 10
#define INT 11
#define FLOAT 12
#define CHAR 13
#define STRING 14
#define BOOLEAN 15
#define VOID 16
#define ERROR 17
 
using namespace std;
 
    int cube[500][500][500];
    int cube1[100][100];  
	
	    
    std::multimap<string,Value> Symbols;
    multimap<string,Value>::iterator mi;
    
    Semantic sem;
    stack<string> stack1;
    
    
 int Semantic::op_Func(string op){
 	
	 int state;
 	
	 if(op=="+"){
 		state = OP_PLUS;
 	}
 	if(op=="-"){
 		state = OP_MINUS;
 	}
 	if(op=="*"){
 		state = OP_MULTIPLY;
 	}
    if(op=="/"){
 		state = OP_DIVIDE;
 	}
 	if(op==">"){
 		state = OP_GREATER;
 	}
 	if(op=="<"){
 		state = OP_LOWER;
 	} 
 	if(op=="|"){
 		state = OP_OR;
 	}
 	if(op=="&"){
 		state = OP_AND;
 	}
	if(op=="!"){
 		state = OP_NOT;
 	}  
 		
	return state;  
 }  
 
 string Semantic::pushType(int cubeState){
 	
	if(cubeState==INT){
 	 return "int";	
 	}
 	if(cubeState==FLOAT){
 	 return "float";	
 	}
 	if(cubeState==CHAR){
 	 return "char"; 	
 	}
 	if(cubeState==STRING){
 	 return "string";	
 	}
 	if(cubeState==BOOLEAN){
 	 return "boolean";	
 	}
 	if(cubeState==VOID){
 	 return "void"; 	
 	}
    else{
     return "ERROR";	
    }	
 }
 
 int Semantic::Operand(string oper){
 	 int type;
	 if(oper=="int"){
 	  	type = INT;
 	 }
 	 if(oper=="float"){
 	 	type = FLOAT;
 	 }
 	 if(oper=="char"){
 	  	type = CHAR;
 	 }
 	 if(oper=="string"){
 	 	type = STRING;
 	 }
 	 if(oper=="boolean"){
 	  	type = CHAR;
 	 }
 	 if(oper=="void"){
 	 	type = STRING;
 	 }
 	 if(oper=="ERROR"){
 	 	type = ERROR;
 	 }
 	 
 	 return type;
 }  
 
int Semantic::funcCubeBinary(int state, int type1, int type2){
 	
	//OP_PLUS 
	cube [OP_PLUS][INT][INT]=INT;
	cube [OP_PLUS][INT][FLOAT]=FLOAT;
	cube [OP_PLUS][INT][CHAR]=ERROR;
	cube [OP_PLUS][INT][STRING]=STRING;
	cube [OP_PLUS][INT][BOOLEAN]=ERROR;
	cube [OP_PLUS][INT][VOID]=ERROR;
	cube [OP_PLUS][INT][ERROR]=ERROR;
	
	cube [OP_PLUS][FLOAT][INT]=FLOAT;
	cube [OP_PLUS][FLOAT][FLOAT]=FLOAT;
	cube [OP_PLUS][FLOAT][CHAR]=ERROR;
	cube [OP_PLUS][FLOAT][STRING]=STRING;
	cube [OP_PLUS][FLOAT][BOOLEAN]=ERROR;
	cube [OP_PLUS][FLOAT][VOID]=ERROR;
	cube [OP_PLUS][FLOAT][ERROR]=ERROR;
	
	cube [OP_PLUS][CHAR][INT]=ERROR;
	cube [OP_PLUS][CHAR][STRING]=STRING;
	cube [OP_PLUS][CHAR][FLOAT]=ERROR;
	cube [OP_PLUS][CHAR][CHAR]=ERROR;
	cube [OP_PLUS][CHAR][BOOLEAN]=ERROR;
	cube [OP_PLUS][CHAR][VOID]=ERROR;
	cube [OP_PLUS][CHAR][ERROR]=ERROR;
	
	cube [OP_PLUS][STRING][INT]=STRING;
	cube [OP_PLUS][STRING][STRING]=STRING;
	cube [OP_PLUS][STRING][FLOAT]=STRING;
	cube [OP_PLUS][STRING][CHAR]=STRING;
	cube [OP_PLUS][STRING][BOOLEAN]=STRING;
	cube [OP_PLUS][STRING][VOID]=ERROR;
	cube [OP_PLUS][STRING][ERROR]=ERROR;
	
	cube [OP_PLUS][BOOLEAN][INT]=ERROR;
	cube [OP_PLUS][BOOLEAN][STRING]=STRING;
	cube [OP_PLUS][BOOLEAN][FLOAT]=ERROR;
	cube [OP_PLUS][BOOLEAN][CHAR]=ERROR;
	cube [OP_PLUS][BOOLEAN][BOOLEAN]=ERROR;
	cube [OP_PLUS][BOOLEAN][VOID]=ERROR;
	cube [OP_PLUS][BOOLEAN][ERROR]=ERROR;
	
	cube [OP_PLUS][VOID][INT]=ERROR;
	cube [OP_PLUS][VOID][STRING]=ERROR;
	cube [OP_PLUS][VOID][FLOAT]=ERROR;
	cube [OP_PLUS][VOID][CHAR]=ERROR;
	cube [OP_PLUS][VOID][BOOLEAN]=ERROR;
	cube [OP_PLUS][VOID][VOID]=ERROR;
	cube [OP_PLUS][VOID][ERROR]=ERROR;
	
	cube [OP_PLUS][ERROR][INT]=ERROR;
	cube [OP_PLUS][ERROR][STRING]=ERROR;
	cube [OP_PLUS][ERROR][FLOAT]=ERROR;
	cube [OP_PLUS][ERROR][CHAR]=ERROR;
	cube [OP_PLUS][ERROR][BOOLEAN]=ERROR;
	cube [OP_PLUS][ERROR][VOID]=ERROR;
	cube [OP_PLUS][ERROR][ERROR]=ERROR;
	
	//OP_MINUS
	
	cube [OP_MINUS][INT][INT]=INT;
	cube [OP_MINUS][INT][FLOAT]=FLOAT;
	cube [OP_MINUS][INT][CHAR]=ERROR;
	cube [OP_MINUS][INT][STRING]=ERROR;
	cube [OP_MINUS][INT][BOOLEAN]=ERROR;
	cube [OP_MINUS][INT][VOID]=ERROR;
	cube [OP_MINUS][INT][ERROR]=ERROR;
	
	
	cube [OP_MINUS][FLOAT][INT]=FLOAT;
	cube [OP_MINUS][FLOAT][FLOAT]=FLOAT;
	cube [OP_MINUS][FLOAT][CHAR]=ERROR;
	cube [OP_MINUS][FLOAT][STRING]=ERROR;
	cube [OP_MINUS][FLOAT][BOOLEAN]=ERROR;
	cube [OP_MINUS][FLOAT][VOID]=ERROR;
	cube [OP_MINUS][FLOAT][ERROR]=ERROR;
	
	cube [OP_MINUS][CHAR][INT]=ERROR;
	cube [OP_MINUS][CHAR][STRING]=ERROR;
	cube [OP_MINUS][CHAR][FLOAT]=ERROR;
	cube [OP_MINUS][CHAR][CHAR]=ERROR;
	cube [OP_MINUS][CHAR][BOOLEAN]=ERROR;
	cube [OP_MINUS][CHAR][VOID]=ERROR;
	cube [OP_MINUS][CHAR][ERROR]=ERROR;
	
	cube [OP_MINUS][STRING][INT]=ERROR;
	cube [OP_MINUS][STRING][STRING]=ERROR;
	cube [OP_MINUS][STRING][FLOAT]=ERROR;
	cube [OP_MINUS][STRING][CHAR]=ERROR;
	cube [OP_MINUS][STRING][BOOLEAN]=ERROR;
	cube [OP_MINUS][STRING][VOID]=ERROR;
	cube [OP_MINUS][STRING][ERROR]=ERROR;
	
	cube [OP_MINUS][BOOLEAN][INT]=ERROR;
	cube [OP_MINUS][BOOLEAN][STRING]=ERROR;
	cube [OP_MINUS][BOOLEAN][FLOAT]=ERROR;
	cube [OP_MINUS][BOOLEAN][CHAR]=ERROR;
	cube [OP_MINUS][BOOLEAN][BOOLEAN]=ERROR;
	cube [OP_MINUS][BOOLEAN][VOID]=ERROR;
	cube [OP_MINUS][BOOLEAN][ERROR]=ERROR;
	
	cube [OP_MINUS][VOID][INT]=ERROR;
	cube [OP_MINUS][VOID][STRING]=ERROR;
	cube [OP_MINUS][VOID][FLOAT]=ERROR;
	cube [OP_MINUS][VOID][CHAR]=ERROR;
	cube [OP_MINUS][VOID][BOOLEAN]=ERROR;
	cube [OP_MINUS][VOID][VOID]=ERROR;
    cube [OP_MINUS][VOID][ERROR]=ERROR;

    cube [OP_MINUS][ERROR][INT]=ERROR;
	cube [OP_MINUS][ERROR][STRING]=ERROR;
	cube [OP_MINUS][ERROR][FLOAT]=ERROR;
	cube [OP_MINUS][ERROR][CHAR]=ERROR;
	cube [OP_MINUS][ERROR][BOOLEAN]=ERROR;
	cube [OP_MINUS][ERROR][VOID]=ERROR;
	cube [OP_MINUS][ERROR][ERROR]=ERROR;	
	
	//OP_MULTIPLY
	
	cube [OP_MULTIPLY][INT][INT]=INT;
	cube [OP_MULTIPLY][INT][FLOAT]=FLOAT;
	cube [OP_MULTIPLY][INT][CHAR]=ERROR;
	cube [OP_MULTIPLY][INT][STRING]=ERROR;
	cube [OP_MULTIPLY][INT][BOOLEAN]=ERROR;
	cube [OP_MULTIPLY][INT][VOID]=ERROR;
	cube [OP_MULTIPLY][INT][ERROR]=ERROR;
	
	cube [OP_MULTIPLY][FLOAT][INT]=FLOAT;
	cube [OP_MULTIPLY][FLOAT][FLOAT]=FLOAT;
	cube [OP_MULTIPLY][FLOAT][CHAR]=ERROR;
	cube [OP_MULTIPLY][FLOAT][STRING]=ERROR;
	cube [OP_MULTIPLY][FLOAT][BOOLEAN]=ERROR;
	cube [OP_MULTIPLY][FLOAT][VOID]=ERROR;
	cube [OP_MULTIPLY][FLOAT][ERROR]=ERROR;
	
	cube [OP_MULTIPLY][CHAR][INT]=ERROR;
	cube [OP_MULTIPLY][CHAR][STRING]=ERROR;
	cube [OP_MULTIPLY][CHAR][FLOAT]=ERROR;
	cube [OP_MULTIPLY][CHAR][CHAR]=ERROR;
	cube [OP_MULTIPLY][CHAR][BOOLEAN]=ERROR;
	cube [OP_MULTIPLY][CHAR][VOID]=ERROR;
	cube [OP_MULTIPLY][CHAR][ERROR]=ERROR;
	
	cube [OP_MULTIPLY][STRING][INT]=ERROR;
	cube [OP_MULTIPLY][STRING][STRING]=ERROR;
	cube [OP_MULTIPLY][STRING][FLOAT]=ERROR;
	cube [OP_MULTIPLY][STRING][CHAR]=ERROR;
	cube [OP_MULTIPLY][STRING][BOOLEAN]=ERROR;
	cube [OP_MULTIPLY][STRING][VOID]=ERROR;
	cube [OP_MULTIPLY][STRING][ERROR]=ERROR;
	
	cube [OP_MULTIPLY][BOOLEAN][INT]=ERROR;
	cube [OP_MULTIPLY][BOOLEAN][STRING]=ERROR;
	cube [OP_MULTIPLY][BOOLEAN][FLOAT]=ERROR;
	cube [OP_MULTIPLY][BOOLEAN][CHAR]=ERROR;
	cube [OP_MULTIPLY][BOOLEAN][BOOLEAN]=ERROR;
	cube [OP_MULTIPLY][BOOLEAN][VOID]=ERROR;
	cube [OP_MULTIPLY][BOOLEAN][ERROR]=ERROR;
	
	cube [OP_MULTIPLY][VOID][INT]=ERROR;
	cube [OP_MULTIPLY][VOID][STRING]=ERROR;
	cube [OP_MULTIPLY][VOID][FLOAT]=ERROR;
	cube [OP_MULTIPLY][VOID][CHAR]=ERROR;
	cube [OP_MULTIPLY][VOID][BOOLEAN]=ERROR;
	cube [OP_MULTIPLY][VOID][VOID]=ERROR;
	cube [OP_MULTIPLY][VOID][ERROR]=ERROR;
	
	cube [OP_MULTIPLY][ERROR][INT]=ERROR;
	cube [OP_MULTIPLY][ERROR][STRING]=ERROR;
	cube [OP_MULTIPLY][ERROR][FLOAT]=ERROR;
	cube [OP_MULTIPLY][ERROR][CHAR]=ERROR;
	cube [OP_MULTIPLY][ERROR][BOOLEAN]=ERROR;
	cube [OP_MULTIPLY][ERROR][VOID]=ERROR;
	cube [OP_MULTIPLY][ERROR][ERROR]=ERROR;
	
	//OP_DIVIDE
	
	cube [OP_DIVIDE][INT][INT]=INT;
	cube [OP_DIVIDE][INT][FLOAT]=FLOAT;
	cube [OP_DIVIDE][INT][CHAR]=ERROR;
	cube [OP_DIVIDE][INT][STRING]=ERROR;
	cube [OP_DIVIDE][INT][BOOLEAN]=ERROR;
	cube [OP_DIVIDE][INT][VOID]=ERROR;
	cube [OP_DIVIDE][INT][ERROR]=ERROR;
	
	cube [OP_DIVIDE][FLOAT][INT]=FLOAT;
	cube [OP_DIVIDE][FLOAT][FLOAT]=FLOAT;
	cube [OP_DIVIDE][FLOAT][CHAR]=ERROR;
	cube [OP_DIVIDE][FLOAT][STRING]=ERROR;
	cube [OP_DIVIDE][FLOAT][BOOLEAN]=ERROR;
	cube [OP_DIVIDE][FLOAT][VOID]=ERROR;
	cube [OP_DIVIDE][FLOAT][ERROR]=ERROR;
			
	cube [OP_DIVIDE][CHAR][INT]=ERROR;
	cube [OP_DIVIDE][CHAR][STRING]=ERROR;
	cube [OP_DIVIDE][CHAR][FLOAT]=ERROR;
	cube [OP_DIVIDE][CHAR][CHAR]=ERROR;
	cube [OP_DIVIDE][CHAR][BOOLEAN]=ERROR;
	cube [OP_DIVIDE][CHAR][VOID]=ERROR;
	cube [OP_DIVIDE][CHAR][ERROR]=ERROR;
		
	cube [OP_DIVIDE][STRING][INT]=ERROR;
	cube [OP_DIVIDE][STRING][STRING]=ERROR;
	cube [OP_DIVIDE][STRING][FLOAT]=ERROR;
	cube [OP_DIVIDE][STRING][CHAR]=ERROR;
	cube [OP_DIVIDE][STRING][BOOLEAN]=ERROR;
	cube [OP_DIVIDE][STRING][VOID]=ERROR;
	cube [OP_DIVIDE][STRING][ERROR]=ERROR;	
	
	cube [OP_DIVIDE][BOOLEAN][INT]=ERROR;
	cube [OP_DIVIDE][BOOLEAN][STRING]=ERROR;
	cube [OP_DIVIDE][BOOLEAN][FLOAT]=ERROR;
	cube [OP_DIVIDE][BOOLEAN][CHAR]=ERROR;
	cube [OP_DIVIDE][BOOLEAN][BOOLEAN]=ERROR;
	cube [OP_DIVIDE][BOOLEAN][VOID]=ERROR;
	cube [OP_DIVIDE][BOOLEAN][ERROR]=ERROR;	
	
	cube [OP_DIVIDE][VOID][INT]=ERROR;
	cube [OP_DIVIDE][VOID][STRING]=ERROR;
	cube [OP_DIVIDE][VOID][FLOAT]=ERROR;
	cube [OP_DIVIDE][VOID][CHAR]=ERROR;
	cube [OP_DIVIDE][VOID][BOOLEAN]=ERROR;
	cube [OP_DIVIDE][VOID][VOID]=ERROR;
	cube [OP_DIVIDE][VOID][ERROR]=ERROR;
	
	cube [OP_DIVIDE][ERROR][INT]=ERROR;
	cube [OP_DIVIDE][ERROR][STRING]=ERROR;
	cube [OP_DIVIDE][ERROR][FLOAT]=ERROR;
	cube [OP_DIVIDE][ERROR][CHAR]=ERROR;
	cube [OP_DIVIDE][ERROR][BOOLEAN]=ERROR;
	cube [OP_DIVIDE][ERROR][VOID]=ERROR;
	cube [OP_DIVIDE][ERROR][ERROR]=ERROR;
		
	 //OP_GREATER
	 
	cube [OP_GREATER][INT][INT]=BOOLEAN;
	cube [OP_GREATER][INT][FLOAT]=BOOLEAN;
	cube [OP_GREATER][INT][CHAR]=ERROR;
	cube [OP_GREATER][INT][STRING]=ERROR;
	cube [OP_GREATER][INT][BOOLEAN]=ERROR;
	cube [OP_GREATER][INT][VOID]=ERROR;
	cube [OP_GREATER][INT][ERROR]=ERROR;
	
	cube [OP_GREATER][FLOAT][INT]=BOOLEAN;
	cube [OP_GREATER][FLOAT][FLOAT]=BOOLEAN;
	cube [OP_GREATER][FLOAT][CHAR]=ERROR;
	cube [OP_GREATER][FLOAT][STRING]=ERROR;
	cube [OP_GREATER][FLOAT][BOOLEAN]=ERROR;
	cube [OP_GREATER][FLOAT][VOID]=ERROR;
	cube [OP_GREATER][FLOAT][ERROR]=ERROR;	
	
	cube [OP_GREATER][CHAR][INT]=ERROR;
	cube [OP_GREATER][CHAR][STRING]=ERROR;
	cube [OP_GREATER][CHAR][FLOAT]=ERROR;
	cube [OP_GREATER][CHAR][CHAR]=ERROR;
	cube [OP_GREATER][CHAR][BOOLEAN]=ERROR;
	cube [OP_GREATER][CHAR][VOID]=ERROR;
	cube [OP_GREATER][CHAR][ERROR]=ERROR;	
	
	cube [OP_GREATER][STRING][INT]=ERROR;
	cube [OP_GREATER][STRING][STRING]=ERROR;
	cube [OP_GREATER][STRING][FLOAT]=ERROR;
	cube [OP_GREATER][STRING][CHAR]=ERROR;
	cube [OP_GREATER][STRING][BOOLEAN]=ERROR;
	cube [OP_GREATER][STRING][VOID]=ERROR;
	cube [OP_GREATER][STRING][ERROR]=ERROR;
	
	cube [OP_GREATER][BOOLEAN][INT]=ERROR;
	cube [OP_GREATER][BOOLEAN][STRING]=ERROR;
	cube [OP_GREATER][BOOLEAN][FLOAT]=ERROR;
	cube [OP_GREATER][BOOLEAN][CHAR]=ERROR;
	cube [OP_GREATER][BOOLEAN][BOOLEAN]=ERROR;
	cube [OP_GREATER][BOOLEAN][VOID]=ERROR;
	cube [OP_GREATER][BOOLEAN][ERROR]=ERROR;	
	
	cube [OP_GREATER][VOID][INT]=ERROR;
	cube [OP_GREATER][VOID][STRING]=ERROR;
	cube [OP_GREATER][VOID][FLOAT]=ERROR;
	cube [OP_GREATER][VOID][CHAR]=ERROR;
	cube [OP_GREATER][VOID][BOOLEAN]=ERROR;
	cube [OP_GREATER][VOID][VOID]=ERROR;
	cube [OP_GREATER][VOID][ERROR]=ERROR;
	
	cube [OP_GREATER][ERROR][INT]=ERROR;
	cube [OP_GREATER][ERROR][STRING]=ERROR;
	cube [OP_GREATER][ERROR][FLOAT]=ERROR;
	cube [OP_GREATER][ERROR][CHAR]=ERROR;
	cube [OP_GREATER][ERROR][BOOLEAN]=ERROR;
	cube [OP_GREATER][ERROR][VOID]=ERROR;
	cube [OP_GREATER][ERROR][ERROR]=ERROR;	
	
	//OP_LOWER
	
	cube [OP_LOWER][INT][INT]=BOOLEAN;
	cube [OP_LOWER][INT][FLOAT]=BOOLEAN;
	cube [OP_LOWER][INT][CHAR]=ERROR;
	cube [OP_LOWER][INT][STRING]=ERROR;
	cube [OP_LOWER][INT][BOOLEAN]=ERROR;
	cube [OP_LOWER][INT][VOID]=ERROR;
	cube [OP_LOWER][INT][ERROR]=ERROR;
	
	cube [OP_LOWER][FLOAT][INT]=BOOLEAN;
	cube [OP_LOWER][FLOAT][FLOAT]=BOOLEAN;
	cube [OP_LOWER][FLOAT][CHAR]=ERROR;
	cube [OP_LOWER][FLOAT][STRING]=ERROR;
	cube [OP_LOWER][FLOAT][BOOLEAN]=ERROR;
	cube [OP_LOWER][FLOAT][VOID]=ERROR;
	cube [OP_LOWER][FLOAT][ERROR]=ERROR;
	
	cube [OP_LOWER][CHAR][INT]=ERROR;
	cube [OP_LOWER][CHAR][STRING]=ERROR;
	cube [OP_LOWER][CHAR][FLOAT]=ERROR;
	cube [OP_LOWER][CHAR][CHAR]=ERROR;
	cube [OP_LOWER][CHAR][BOOLEAN]=ERROR;
	cube [OP_LOWER][CHAR][VOID]=ERROR;
	cube [OP_LOWER][CHAR][ERROR]=ERROR;
	
	cube [OP_LOWER][STRING][INT]=ERROR;
	cube [OP_LOWER][STRING][STRING]=ERROR;
	cube [OP_LOWER][STRING][FLOAT]=ERROR;
	cube [OP_LOWER][STRING][CHAR]=ERROR;
	cube [OP_LOWER][STRING][BOOLEAN]=ERROR;
	cube [OP_LOWER][STRING][VOID]=ERROR;
	cube [OP_LOWER][STRING][ERROR]=ERROR;
	
	cube [OP_LOWER][BOOLEAN][INT]=ERROR;
	cube [OP_LOWER][BOOLEAN][STRING]=ERROR;
	cube [OP_LOWER][BOOLEAN][FLOAT]=ERROR;
	cube [OP_LOWER][BOOLEAN][CHAR]=ERROR;
	cube [OP_LOWER][BOOLEAN][BOOLEAN]=ERROR;
	cube [OP_LOWER][BOOLEAN][VOID]=ERROR;
	cube [OP_LOWER][BOOLEAN][ERROR]=ERROR;	
	
	cube [OP_LOWER][VOID][INT]=ERROR;
	cube [OP_LOWER][VOID][STRING]=ERROR;
	cube [OP_LOWER][VOID][FLOAT]=ERROR;
	cube [OP_LOWER][VOID][CHAR]=ERROR;
	cube [OP_LOWER][VOID][BOOLEAN]=ERROR;
	cube [OP_LOWER][VOID][VOID]=ERROR;
	cube [OP_LOWER][VOID][ERROR]=ERROR;	
	
	cube [OP_LOWER][ERROR][INT]=ERROR;
	cube [OP_LOWER][ERROR][STRING]=ERROR;
	cube [OP_LOWER][ERROR][FLOAT]=ERROR;
	cube [OP_LOWER][ERROR][CHAR]=ERROR;
	cube [OP_LOWER][ERROR][BOOLEAN]=ERROR;
	cube [OP_LOWER][ERROR][VOID]=ERROR;
	cube [OP_LOWER][ERROR][ERROR]=ERROR;
	
	//OP_AND
	
	cube [OP_AND][INT][INT]=ERROR;
	cube [OP_AND][INT][FLOAT]=ERROR;
	cube [OP_AND][INT][CHAR]=ERROR;
	cube [OP_AND][INT][STRING]=ERROR;
	cube [OP_AND][INT][BOOLEAN]=ERROR;
	cube [OP_AND][INT][VOID]=ERROR;
	cube [OP_AND][INT][ERROR]=ERROR;
	
	cube [OP_AND][FLOAT][INT]=ERROR;
	cube [OP_AND][FLOAT][FLOAT]=ERROR;
	cube [OP_AND][FLOAT][CHAR]=ERROR;
	cube [OP_AND][FLOAT][STRING]=ERROR;
	cube [OP_AND][FLOAT][BOOLEAN]=ERROR;
	cube [OP_AND][FLOAT][VOID]=ERROR;
    cube [OP_AND][FLOAT][ERROR]=ERROR;
	
	cube [OP_AND][CHAR][INT]=ERROR;
	cube [OP_AND][CHAR][STRING]=ERROR;
	cube [OP_AND][CHAR][FLOAT]=ERROR;
	cube [OP_AND][CHAR][CHAR]=ERROR;
	cube [OP_AND][CHAR][BOOLEAN]=ERROR;
	cube [OP_AND][CHAR][VOID]=ERROR;
	cube [OP_AND][CHAR][ERROR]=ERROR;	
	
	cube [OP_AND][STRING][INT]=ERROR;
	cube [OP_AND][STRING][STRING]=ERROR;
	cube [OP_AND][STRING][FLOAT]=ERROR;
	cube [OP_AND][STRING][CHAR]=ERROR;
	cube [OP_AND][STRING][BOOLEAN]=ERROR;
	cube [OP_AND][STRING][VOID]=ERROR;
	cube [OP_AND][STRING][ERROR]=ERROR;	
	
	cube [OP_AND][BOOLEAN][INT]=ERROR;
	cube [OP_AND][BOOLEAN][STRING]=ERROR;
	cube [OP_AND][BOOLEAN][FLOAT]=ERROR;
	cube [OP_AND][BOOLEAN][CHAR]=ERROR;
	cube [OP_AND][BOOLEAN][BOOLEAN]=BOOLEAN;
	cube [OP_AND][BOOLEAN][VOID]=ERROR;
	cube [OP_AND][BOOLEAN][ERROR]=ERROR;	
	
	cube [OP_AND][VOID][INT]=ERROR;
	cube [OP_AND][VOID][STRING]=ERROR;
	cube [OP_AND][VOID][FLOAT]=ERROR;
	cube [OP_AND][VOID][CHAR]=ERROR;
	cube [OP_AND][VOID][BOOLEAN]=ERROR;
	cube [OP_AND][VOID][VOID]=ERROR;
	cube [OP_AND][VOID][ERROR]=ERROR;
		
	cube [OP_AND][ERROR][INT]=ERROR;
	cube [OP_AND][ERROR][STRING]=ERROR;
	cube [OP_AND][ERROR][FLOAT]=ERROR;
	cube [OP_AND][ERROR][CHAR]=ERROR;
	cube [OP_AND][ERROR][BOOLEAN]=ERROR;
	cube [OP_AND][ERROR][VOID]=ERROR;
	cube [OP_AND][ERROR][ERROR]=ERROR;
	
	//OP_OR
	
	cube [OP_OR][INT][INT]=ERROR;
	cube [OP_OR][INT][FLOAT]=ERROR;
	cube [OP_OR][INT][CHAR]=ERROR;
	cube [OP_OR][INT][STRING]=ERROR;
	cube [OP_OR][INT][BOOLEAN]=ERROR;
	cube [OP_OR][INT][VOID]=ERROR;
	cube [OP_OR][INT][ERROR]=ERROR;
	
	cube [OP_OR][FLOAT][INT]=ERROR;
	cube [OP_OR][FLOAT][FLOAT]=ERROR;
	cube [OP_OR][FLOAT][CHAR]=ERROR;
	cube [OP_OR][FLOAT][STRING]=ERROR;
	cube [OP_OR][FLOAT][BOOLEAN]=ERROR;
	cube [OP_OR][FLOAT][VOID]=ERROR;
    cube [OP_OR][FLOAT][ERROR]=ERROR;	
	
	cube [OP_OR][CHAR][INT]=ERROR;
	cube [OP_OR][CHAR][STRING]=ERROR;
	cube [OP_OR][CHAR][FLOAT]=ERROR;
	cube [OP_OR][CHAR][CHAR]=ERROR;
	cube [OP_OR][CHAR][BOOLEAN]=ERROR;
	cube [OP_OR][CHAR][VOID]=ERROR;
    cube [OP_OR][CHAR][ERROR]=ERROR;	
	
	cube [OP_OR][STRING][INT]=ERROR;
	cube [OP_OR][STRING][STRING]=ERROR;
	cube [OP_OR][STRING][FLOAT]=ERROR;
	cube [OP_OR][STRING][CHAR]=ERROR;
	cube [OP_OR][STRING][BOOLEAN]=ERROR;
	cube [OP_OR][STRING][VOID]=ERROR;
    cube [OP_OR][STRING][ERROR]=ERROR;
	
	cube [OP_OR][BOOLEAN][INT]=ERROR;
	cube [OP_OR][BOOLEAN][STRING]=ERROR;
	cube [OP_OR][BOOLEAN][FLOAT]=ERROR;
	cube [OP_OR][BOOLEAN][CHAR]=ERROR;
	cube [OP_OR][BOOLEAN][BOOLEAN]=BOOLEAN;
	cube [OP_OR][BOOLEAN][VOID]=ERROR;
    cube [OP_OR][BOOLEAN][ERROR]=ERROR;	
	
	cube [OP_OR][VOID][INT]=ERROR;
	cube [OP_OR][VOID][STRING]=ERROR;
	cube [OP_OR][VOID][FLOAT]=ERROR;
	cube [OP_OR][VOID][CHAR]=ERROR;
	cube [OP_OR][VOID][BOOLEAN]=ERROR;
	cube [OP_OR][VOID][VOID]=ERROR;
    cube [OP_OR][VOID][ERROR]=ERROR;
	
	cube [OP_OR][ERROR][INT]=ERROR;
	cube [OP_OR][ERROR][STRING]=ERROR;
	cube [OP_OR][ERROR][FLOAT]=ERROR;
	cube [OP_OR][ERROR][CHAR]=ERROR;
	cube [OP_OR][ERROR][BOOLEAN]=ERROR;
	cube [OP_OR][ERROR][VOID]=ERROR;
	cube [OP_OR][ERROR][ERROR]=ERROR;		
	
	return cube[state][type1][type2];
 
 }
 
 int Semantic::funcCubeUnary(int state, int type){
 	
 	//OP_MINUS_UNARY
	cube1 [OP_MINUS][INT]=INT;
	cube1 [OP_MINUS][FLOAT]=FLOAT;
	cube1 [OP_MINUS][CHAR]=ERROR;
	cube1 [OP_MINUS][STRING]=ERROR;
	cube1 [OP_MINUS][BOOLEAN]=ERROR;
	cube1 [OP_MINUS][VOID]=ERROR;
	cube1 [OP_MINUS][ERROR]=ERROR;
	
	//OP_NOT
	cube1 [OP_NOT][INT]=ERROR;
	cube1 [OP_NOT][FLOAT]=ERROR;
	cube1 [OP_NOT][CHAR]=ERROR;
	cube1 [OP_NOT][STRING]=ERROR;
	cube1 [OP_NOT][BOOLEAN]=BOOLEAN;
	cube1 [OP_NOT][VOID]=ERROR;
	cube1 [OP_NOT][ERROR]=ERROR;
	 
	return cube1[state][type];
 }
 
 bool Semantic::isBoolean(string type){
   
   if(type=="boolean"){
   	 return true;
   }	
   
   return false;
 }
 
 void Semantic::displaySymbol(){
 	cout<<"\n";
 	for ( mi = Symbols.begin() ; mi != Symbols.end(); mi++ )
    {   
        cout<<mi->first<<":";
        cout<<mi->second.type<<":";
        cout<<mi->second.scope<<":";   
        cout<<"\n";
    }
 }
 
 void Semantic::insert(string name, string type, string scope){
  Symbols.insert(std::make_pair<string,Value>(name,Value{type,scope}));  	
 }
 
 bool Semantic::search(string name){
 	
     
 	for(mi = Symbols.find(name);mi != Symbols.end();mi++){
 		return true;
 	}
 	return false;
 }
 
  //Checks declaration and unicity of variables
 bool Semantic::search(string name, string scope){
    
	
 	for(mi = Symbols.find(name);mi!= Symbols.end();++mi){
       
	   //cout<<mi->first<<":"<<mi->second.scope<<"\n";
	           
 	    if(mi->second.scope==scope){
  		     return true;
  	    }
      
 	}
 	return false;	
 }
 
 
 string Semantic::getType(string name){
   
   mi = Symbols.find(name);
  	if(mi!=Symbols.end()){
        return mi->second.type;
   }
    else{
        return "Error";	
    }
 }
 
 
  string Semantic::getType(string name,string scope){
   
  	mi = Symbols.find(name);
	
 	for(mi=Symbols.begin();mi!= Symbols.end();++mi){
       
	   cout<<mi->first<<":"<<mi->second.scope<<"\n";
	           
 	    if(mi->second.scope==scope){
  		     return mi->second.type;
  	    }
      
 	}
 	return "Error";
 }
 
 string Semantic::getScope(string name){
   mi = Symbols.find(name);
  	
	if(mi!=Symbols.end()){
        return mi->second.scope;
   }
   else{
   	    return "Error";
   }
 }
 
 string Semantic::checkScope(string name, string currScope){
 	
 	for(mi=Symbols.find(name);mi!= Symbols.end();++mi){
               
 	    if(mi->second.scope==currScope){
  		     return mi->second.type;
  	    }
 	}
 	return "Error";
 }
 
 string Semantic::calculateTypeBinary(string type1,string type2,string op){
   
   int cubeState;
   string var1 = ""; 
   cubeState = funcCubeBinary(op_Func(op),Operand(type1),Operand(type2));
   
   var1 = pushType(cubeState);
   
   stack1.push(var1);
   
   return var1;       	
 }

 string Semantic::calculateTypeUnary(string type,string op){
   
   int cubeState1;
    string var2 = "";  
   //type = stack.pop();
   
   cubeState1 = funcCubeUnary(op_Func(op),Operand(type));
   var2 = pushType(cubeState1);
   
   stack1.push(var2);
   return var2;          	
 }
 
 bool Semantic::isTypeMatching(string type1, string type2){
  	
	if(type1==type2){
  		return true;
  	}
  	return false;
 }
 
 
 /*
 bool isBoolean(){
   	
   	if(calculateTypeBinary()=="boolean"||calculateTypeUnary()=="boolean"){
   		return true;
   	}
   	return false;
 } 
 
 bool is Boolean
 bool isTypeMatching(){
 	
 }
 */
 
