

#ifndef __LEXER_H__
#define __LEXER_H__
#include<string>
#include<vector>
#include <iostream>
 
 using namespace std;
 
void splitLine(string);  
 void lexer(string); 
  bool isKeyWord(string);
  bool isType(string);
  
 class Token{

   public:
	string tokenName;
	string tokenWord;
	int tokenLine;
	
   	Token(string a, string b, int c);
   /*
    //void addElements()
    string showName();
    string showWord();
    int showLine();
    */
};

 void show();
   
 extern vector<Token> myTokens; 
 extern int state;
    
/*
std::ostream& operator<<(std::ostream& o, const Token &t)
{
  return o << t.tokenName << " " << t.tokenWord<<" "<<t.tokenLine;
}
*/

#endif
