
  /********************************************************************************************************************/
  // Name: Ankur Chaudhary   ASU ID: 1206281930
  // Desc: Program to design a parser for lexical analyzer  
           
  // Contents: Lexer.cpp
  //           Ankur_Chaudhary_Project2_input1.txt
  //           Ankur_Chaudhary_Project2_output.txt   
  //           Ankur_Chaudhary_Project2_input2.txt
  //           Ankur_Chaudhary_Project2_output2new.txt
  //	       Makefile
  //	       Ankur_Output -Executable file generated by makefile   

  // Assumption: Program compiled and executed on Ubuntu 13.04. gcc compiler creates a character
  //             carrige return at end by itself. That has been taken care of here. 
  /*******************************************************************************************************************/

		
		//#include "lexer.cpp"
		
		#include<iostream>
		#include<fstream>
		#include<string.h>
		#include<map>
		#include<stack>
		#include<ctype.h>
		#include<sstream>
		#include<vector>
		#include "lexer.h"
	    #include "Semantic.h"
		
		using namespace std;
          
        string currentScope;
          string signature;
           string meth_type;
            string exprType;
             string typeMatch;
              string call_type;
			     
         //Create Reference of Semantic
          
		  ofstream out;
		  string strm;
		  int loop;
		  
		  int currentToken = 0;
		    int flag_line=0;
		    int flag_decl=0;
		  void dvar_global();
		  void dmethod();
		   void parameter();
		     void line();
		      void if_func();
		       void isWhile();
		         void assign();
		          void chkReturn();
		           void call_function();
		          void exprlog();
		         void exprel();
		        void opand();
		       void opno();
		      void expr();
		     void product();
		   void sign();
		  void term();
		  bool checkTerm(Token);
		  bool checkLine(Token);
     
	 //Skip Line
	 void skipLine(){
	 	int line;
	     line = myTokens[currentToken].tokenLine;
	     while(line==myTokens[currentToken].tokenLine){
	     currentToken++;
	   }	
	}
		 
		  //Parsing starts
		     
		  Token nextToken(){
			  Token next = myTokens[currentToken];
			  currentToken++;
			  return next;
		  }
		
		  void backToken(){
			  currentToken--;
		  }
		
		
		//Main Program check begins here 
		
		//Skip Line
 
   bool isDataType(string str){
   	
	if(str=="int"||str=="float"||str=="OCTAL"||str=="HEXADECIMAL"||str=="char"||str=="string"
	   ||str=="IDENTIFIER"){
	   	//mystack.push(myTokens[currentToken].tokenWord));
      return true;
   	}
     return false;	
   }
   
   //void skipLine(){
 	// int line,line1;
   //}

     //Check if function is dvar_local
   void dvar_local(){
   	string dvar,dvar1,dvar_loc;
   	
   	  dvar = nextToken().tokenName;
   	  
   	  //Check for closing bracket
   	    
	    if(dvar=="IDENTIFIER"){
	          
		  cout<<currentToken;
	      //Enter the Local Variable into Symbol Table currentScope from dmethod
	      dvar_loc = myTokens[currentToken-1].tokenWord;
	      
	      if(!sem.search(dvar_loc,currentScope)){
		 		sem.insert(dvar_loc,meth_type,currentScope);
		 		dvar_loc="";
		 	}
		  else{
  		        cout<<"Duplicated Variable:"<<myTokens[currentToken].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine;
  		         out<<"Duplicated Variable:"<<myTokens[currentToken-1].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine<<endl;
  		  }
  		    
		  dvar =  nextToken().tokenWord; 
		  
		  if(dvar=="="){
   		
   		    if(checkTerm(nextToken())){
   		    	backToken();
   		    	exprlog();
   		    }  
			else{
				backToken();
				cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
			    //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
			    skipLine();
				return;
				dvar="";
			} 
			
			dvar=nextToken().tokenWord;
			
			if(dvar==";"){
				return;
			}
			else if(dvar==","){
				dvar_local();
			}
			else{
				backToken();
				cout<<"Line:"<<myTokens[currentToken].tokenLine-1<<"\t"<<"expected Delimiter\n";
			    //out<<"Line:"<<myTokens[currentToken].tokenLine-1<<"\t"<<"expected Delimiter\n";
			    skipLine();
			    return;
				dvar="";
			}	
   		  }	  
   		  else if(dvar==","){
	    	dvar_local();
	      }
	      
	      else if(dvar==";"){
	    	  //do nothing
	      }
	      else{	
			  //backToken();
			  
			  cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
			  //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
			  skipLine();
			  return;				
		  }	
		 //do nothing	
	    }   	    
		else{
			
			  //backToken();
			  
			  cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
			   //out<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Delimiter\n";
			   skipLine();
			   return;				
		  }			
		//Check if next token is an Identifier		
   	
   }
   
   //Check if function is of type if
   void if_func(){
   	
   	string dif_func,dif_func1;
   	
   	cout<<currentToken;
   	
   	dif_func = nextToken().tokenWord;
   	
   	if(dif_func=="("){
   		
   		if(checkTerm(nextToken())){
   			backToken();
   			exprlog();
   		 
   		 //Checking for expression validity
   		 
   		 if(sem.isBoolean(exprType)) {
   		   //Do nothing	
   		 }
   		 else{
   		 	cout<<"Boolean Expression expected in line:"<<myTokens[currentToken].tokenLine-1<<"\n";
   		 		out<<"Boolean Expression expected in line:"<<myTokens[currentToken].tokenLine<<"\n";
   		 }
   		 
   		dif_func=nextToken().tokenWord;
   		
   		if(dif_func==")"){
   			//closing braces
   		}
   		else{
   			backToken();
   		    cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n"; 
   		    //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Exprlog\n"; 
   		}
   	 }
   	   else{
   	 	backToken();
   		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n"; 
   	 }
   	  	 
   }
    else{
    	backToken();
   		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
        //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";   		
    }
    
    //Single line
    
    //Check for single and multiple lines
      
      if(checkLine(nextToken())){
			backToken();
			line();
		}
		else{
			backToken();
		}
      
      dif_func = nextToken().tokenWord;
      
      	if(dif_func=="{"){
	     
	     dif_func=nextToken().tokenWord;
	     
			if(dif_func=="}"){
				//do nothing
			}
			else{
			while(myTokens[currentToken].tokenWord!="}"){
				
				backToken();
				line();
				
				if(myTokens[currentToken].tokenWord!="}"){
					currentToken++;
				}
				cout<<currentToken;
			
			}
			currentToken++;
		  }
		}
		else{
			backToken();
		}
	  
	    //Else
	    
	    dif_func=nextToken().tokenWord;
	    
	    if(dif_func=="else"){
	    
		 if(checkLine(nextToken())){
			backToken();
			line();
		}
		else{
			backToken();
		}
      
      dif_func = nextToken().tokenWord;
      
      	if(dif_func=="{"){
	     
	     dif_func=nextToken().tokenWord;
	       
		   if(dif_func=="}"){
	       	return;
	       }   
			
			while(myTokens[currentToken].tokenWord!="}"){
				
				backToken();
				line();
				
				if(myTokens[currentToken].tokenWord!="}"){
					currentToken++;
				}
				cout<<currentToken;
			
			}
			currentToken++;
		}
		else{
			backToken();
		}
			
	    	
	    }
	    else{
	    	backToken();
	    	
	    }
    
 }
   
   //Check if function is while
   void while_func(){
   	
   	string dif_func,dif_func1;
   	
   	dif_func = nextToken().tokenWord;
   	
	   if(dif_func=="("){
   		
   		 	
   				//Check Exprlog
			if(checkTerm(nextToken())){
   				 backToken();
				 exprlog();
   				  			
   				 dif_func = nextToken().tokenWord; 
						
			    //Check for boolean expression
				if(sem.isBoolean(exprType)) {
   		            //Do nothing	
   		         }
   		        else{   		           	
   		  	       cout<<"Boolean Expression expected in line:"<<myTokens[currentToken].tokenLine-1<"\n";
   		  	        out<<"Boolean Expression expected in line:"<<myTokens[currentToken].tokenLine<<endl;
   		        }
				   			
   				//Check closing  braces 
   			    if(dif_func==")"){
   			    	
					//Closing braces found
   			    }	
   			    else{
   			    	
   			    	backToken();
   			    	cout<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Delimiter\n";  
				    //out<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Delimiter\n";    	
   			    }
   				
   			 }
   			
		   	    
   		   else{
   		   	        backToken();
   				    dif_func=nextToken().tokenWord;
   				    
					if(dif_func==")"){
   				    	//do nothing
   				    }
   				    else{  
					//dif_func=nextToken().tokenName; 			
					backToken();
   		            cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";	
	              }
			}
		   
      }
	      else{
   				    dif_func=""; 			
					backToken();
   		            cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";	
	                //skipLine();
				} 			 
   	   	
      //Check for single and multiple lines
      
      if(checkLine(nextToken())){
			backToken();
			line();
			return;
		}
		else{
			backToken();
		}
      
      dif_func = nextToken().tokenWord;
      
      	if(dif_func=="{"){
	     
	     dif_func=nextToken().tokenWord;
	     
	      if(dif_func=="}"){
	      	return;
	      }
			
			
			while(myTokens[currentToken].tokenWord!="}"){
				
				backToken();
				line();
				
				if(myTokens[currentToken].tokenWord!="}"){
					currentToken++;
				}
				cout<<currentToken;
			
			}
			currentToken++;
		}
	  
	     	
   	  
   }
   
   //Check if its a return function
   void return_func(){
   
    string dif_func,dif_func1;
   	dif_func = nextToken().tokenWord;

	   			
   				//Check Exprlog
			if(dif_func=="true"||dif_func=="false"||dif_func=="("||dif_func=="-"||dif_func=="!"){
   				backToken();
				exprlog();
				
   				//Check if return value matches
   		        if(sem.isTypeMatching(meth_type,exprType)){
   		        	//do nothing
   		        }		
   				else{
   				   cout<<"Return type mismatch in line:"<<myTokens[currentToken].tokenLine-1<<endl;
					  out<<"Return type mismatch in line:"<<myTokens[currentToken].tokenLine<<endl;
		
					  	
   				}
   				
				dif_func = nextToken().tokenWord;   			
   				//Check closing  ; 
   			    if(dif_func==";"){   
				   return;			    	
					//Closing semi colon found
   			    }	
   			    else{
   			    	dif_func="";
   			    	backToken();
   			    	cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";  	
   			    }
   				
   			 }
			else{
   				    	backToken();
			        	dif_func=nextToken().tokenName; 			
				
   		            cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";	
	                //skipLine();
			}  
			
					
   				//Check Exprlog
			if(isDataType(dif_func)){
   				backToken();
				exprlog();
   				
				dif_func = nextToken().tokenWord;   			
   				//Check closing  ; 
   				
   				//Check Return type matching
   				//Check if return value matches
   		        if(sem.isTypeMatching(meth_type,exprType)){
   		        	//do nothing
   		        }		
   				else{
   				   cout<<"Return type mismatch in line:"<<myTokens[currentToken].tokenLine-1<"\n";	
   				    out<<"Return type mismatch in line:"<<myTokens[currentToken].tokenLine-1<"\n";	
   				}
   				
   				
   			    if(dif_func==";"){   			    	
					//Closing semi colon found
   			    }	
   			    else{
   			    	dif_func="";
   			    	backToken();
   			    	cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";  	
   			    }
   				
   			 }
			else{
   				    dif_func=""; 			
					backToken();
   		            cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";	
   		             //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Exprlog\n";
	                skipLine();
	                return;
			} 
			
		    if(dif_func==";"){
   				//do nothing
   			} 
			else{
   				    dif_func=""; 			
					backToken();
   		            cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";	
   		            //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
	                //skipLine();
			}     
			
   }
   
   void parameter(){
  	  
  	     string dcoma;
  	     string tok_Word;
  	     
  	     dcoma = myTokens[currentToken].tokenWord;
  	     
		 if(isType(dcoma)){
	     	currentToken++;
		 } 
	     else{
	          cout<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Delimiter\n";	
			  //out<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Delimiter\n";         
		 }
         
		 if(myTokens[currentToken].tokenName=="IDENTIFIER"){
		 	
		 	
		 	tok_Word = myTokens[currentToken].tokenWord;
		 	
			 if(!sem.search(tok_Word,signature)){
		 		sem.insert(myTokens[currentToken].tokenWord,myTokens[currentToken-1].tokenWord,signature);
		 	}
		 	else{
  		        cout<<"Duplicated Variable:"<<myTokens[currentToken].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine;
  		          out<<"Duplicated Variable:"<<myTokens[currentToken].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine<<endl;
  		        meth_type="";
  		    }
	     	currentToken++;
		 } 
	     else{
	          cout<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Identifier\n";
			  out<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Identifier\n";				          
			}
         
		 dcoma = nextToken().tokenWord;
		  	
         if(dcoma==","){
            parameter();
         }  
		 else{
		 	//dcoma = nextToken().tokenWord;
		 	
		 	if(dcoma ==")"){
		 		backToken();
		 	}
		 	else{
		 		 cout<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Demilimiter \n";
		 		 //out<<"Line:"<<myTokens[currentToken].tokenLine<<" "<<"expected Demilimiter \n";
				 backToken();
				 parameter();
		 	}
		 	//backToken();
		 }	
   }
   
   void line(){
   	
   	string linestr;
   	
   	linestr = nextToken().tokenWord;
   	//In start of line make loop zero
	   loop=0;
   	//Check for dvar_local
   	if(isType(linestr)){
   		
		//Set meth_type for dvar_local
   		
   		meth_type=myTokens[currentToken-1].tokenWord;
   	    //backToken();
	   	dvar_local();
   		meth_type="";
		return;
   		//backToken();
   	}
   	
   	//Check for if keyword
	else if(linestr=="if"){
		if_func();
		return;
	}
	
	//Check for while keyword
	else if(linestr=="while"){
		while_func();
		return;
	}
   	
   	//Check for return keyword
   	else if(linestr=="return"){
   		return_func();
   		return;
   	}
   	else{
   		backToken();
   		linestr=nextToken().tokenName;
   		
   	}
   	
   	//Come back to previous token assign lienstr-TokenName
   	//else if(linestr!="}"){
   	//	backToken();
   	//	linestr=nextToken().tokenName;
   	//}
   	
   	//Check for identfier
   	if(linestr=="IDENTIFIER"){
   		  
   		//Assign linestr tokenword
   	    linestr=nextToken().tokenWord;
		  if(linestr=="="){
		  	
		  //out<<myTokens[currentToken-2].tokenWord<<endl;
	
		  
		  if(!sem.search(myTokens[currentToken-2].tokenWord,currentScope)){
		  	
   		  	 out<<"Variable :"<<myTokens[currentToken-2].tokenWord<<" not found in Line:"<<myTokens[currentToken-1].tokenLine<<endl;
   		  }
   		  else{
   		  	     flag_decl = 1;
   		  	   
		         typeMatch = sem.checkScope(myTokens[currentToken-2].tokenWord,currentScope);
   	       
   	     }
		  	
		  //Call assign function 
		  	assign();
		  	return;
		  
		  }
		  else if(linestr=="("){
		     call_type = "";
		     
		     call_type = myTokens[currentToken-2].tokenWord;
		  
		  	 //backToken();
		  	//Call call_function-Need to add read and print here
		  /*  
		  if(!sem.search(myTokens[currentToken-2].tokenWord)){
   		  	 out<<"Method :"<<myTokens[currentToken-2].tokenWord<<"not found in Line"<<myTokens[currentToken-1].tokenLine<<endl;
   		  }
   		  else{
   		  	    call_type = myTokens[currentToken-2].tokenWord;
   	          }
		  	*/
			call_function();
			return;
		  }
	   	  else{
	   	  	
	   	  	//move one token back
		    //backToken();
	   	  	cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";	
	   	  	//out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
	        skipLine();
	        return;
			//linestr=nextToken().tokenWord;
	   	  }
   	}
   	else{
   		backToken();
   		linestr=nextToken().tokenWord;
   	}
   	
   	if(linestr=="print"||linestr=="read"){
   	   //backToken();
   	   linestr=nextToken().tokenWord;
   	   
   	   if(linestr=="("){
   	      call_function();	
		  return;	 	
   	   }
   	   else{ 
   	   	  	cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
   	   }
	     	
   	}	
   	else{
   		cout<<currentToken;
   			cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected IDENTIFIER\n";
   			//out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected IDENTIFIER\n";
		//backToken();
   		skipLine();
   		return;
   		//cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected IDENTIFIER, KEYWORD OR TYPE";	
	    //skipLine(); 
   	  }
   	//linestr = nextToken().tokenWord; 
   	 //cout<<currentToken;
   	 //linestr = nextToken().tokenWord;

    return;
   	   	
   }
   
  //dmethod
  void dmethod(){
	    
		int c_method=0; 
		 
	    string darg;
		darg=nextToken().tokenWord; 
		 //parameter();
		 
	     //Update currentScope to signature from program
	     //currentScope=signature
		  
	     if(isType(darg)){
	      backToken();
	      
		  //Add until receive ")" to signature
		   while(myTokens[currentToken].tokenWord!=")"){   
		      if(myTokens[currentToken].tokenWord==","||myTokens[currentToken].tokenName=="IDENTIFIER"){
		      	currentToken++;
		      	c_method++;
		      }
		      else{ 
			  signature +="-"+myTokens[currentToken].tokenWord;
	          currentToken++;
	          c_method++;
	         }
		   }
          
		  currentToken-= c_method;
           
		  if(!sem.search(signature)){
             sem.insert(signature,meth_type,"function");		  	
		  }
		   else{
  		    cout<<"Duplicated Method:"<<signature<<":in line:"<<myTokens[currentToken].tokenLine-1<<"\n";
  		     out<<"Duplicated Method:"<<signature<<":in line:"<<myTokens[currentToken].tokenLine-1<<"\n";
  		   } 
		  parameter();
		  //return;	
	    }
	     else{
	     	backToken();
	     }
	     //Current Scope changed to updated signature
		 currentScope=signature;
	     
	     darg="";
	     darg = nextToken().tokenWord;
         cout<<currentToken;
         
		 if(darg==")"&&currentToken!=myTokens.size()){
		 
		 if(c_method==0){
		 
		  if(!sem.search(signature)){
             sem.insert(signature,meth_type,"function");		  	
		  }
		   else{
  		    cout<<"Duplicated Method:"<<signature<<":in line:"<<myTokens[currentToken].tokenLine<<"\n";
  		     out<<"Duplicated Method:"<<signature<<":in line:"<<myTokens[currentToken].tokenLine<<"\n";
  		   } 
	      }
			 if(currentToken==myTokens.size()){
			   return;  	
			 } 
			 
			darg=nextToken().tokenWord;
		 	if(darg=="{"){
		 		backToken();
		 		//do nothing
		 	}
	     	else{
	     	   backToken();
			   return;	
	     	}
			 
			 //currentToken++;
	     	//do nothing
	     } 
	     else{ 
	        if(currentToken==myTokens.size()){
	        
			  cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
			   //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n"; 	
	          return;
			 }
			}
		cout<<currentToken;
		
		darg = nextToken().tokenWord;
		
		cout<<currentToken;
				
		if(darg=="{"){
	     
	     
	     darg=nextToken().tokenWord;
	     
		   
		//	cout<<myTokens.size();
			if(darg=="}"){
				
				return;
			}
			
			while(myTokens[currentToken].tokenWord!="}"){
				
				backToken();
				line();
				
				if(myTokens[currentToken].tokenWord!="}"){
					currentToken++;
				}
				cout<<currentToken;
			
			}
			
		     if(myTokens[currentToken].tokenWord=="}"){
		     	currentToken++;
		     }
		
		}
		else{
				cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter";
			}
		
		}
		
  //checkToken-Line
  
  bool checkLine(Token t){
  	string str1;
  	if(t.tokenWord=="if"||t.tokenWord=="while"||t.tokenWord=="return"||isType(t.tokenWord)||
	   t.tokenWord=="print"||t.tokenWord=="read"){
  		return true;
  	}
  	else if(t.tokenName=="IDENTIFIER"){
  		
		  str1=nextToken().tokenWord;
		  
  		if(str1=="("||str1=="="){
  		  backToken();	
  		  return true;	
  		}
  		else{
  			backToken();
  			return false;
  		}
  	}
  	return false;
  }		
  
//dvar_global
  
  void dvar_global(){
       
       string var_g ="global";
       //First Token Insert Into map if not exists already
       string var_type = myTokens[currentToken-2].tokenWord;
       
      	if(!sem.search(myTokens[currentToken-1].tokenWord,var_g)){		   
             sem.insert(myTokens[currentToken-1].tokenWord,var_type,var_g);
	    }
	    else{
  		    cout<<"Duplicated Variable:"<<myTokens[currentToken].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine<<"\n";
  		      out<<"Duplicated Variable:"<<myTokens[currentToken].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine<<"\n";
  		}
	    
	  while(currentToken!=myTokens.size()&&myTokens[currentToken].tokenWord==","){
		  currentToken++;
  		
  		if(myTokens[currentToken].tokenName=="IDENTIFIER"){
  			
  			//Insert into map if Identifier found and not existing already
  	
	  		if(!sem.search(myTokens[currentToken].tokenWord,var_g)){
  			  sem.insert(myTokens[currentToken].tokenWord,var_type,var_g);
  		    }
  		    else{
  		      	cout<<"Duplicated Variable:"<<myTokens[currentToken].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine<<"\n";
  		      	 out<<"Duplicated Variable:"<<myTokens[currentToken].tokenWord<<":in line:"<<myTokens[currentToken].tokenLine<<"\n";
  		    }
  		    currentToken++;
  		}
  		else{
  		  cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected IDENTIFIER\n";
	      //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected IDENTIFIER\n";
		  return;		
  		}
  	  }
  	  
  	  if(currentToken!=myTokens.size()&&myTokens[currentToken].tokenWord==";"){    
  	  	    
			currentToken++;
  	  	
  	  }
  	  else{	
		 cout<<"Line:"<<myTokens[currentToken].tokenLine-1<<"\t"<<"expected Semicolon\n";
	     //out<<"Line:"<<myTokens[currentToken].tokenLine-1<<"\t"<<"expected  Delimiter\n";
	     if(currentToken==myTokens.size()-1){
	       skipLine();
		   return;	
	       //currentToken++;
		 }
		 
		  //line=myTokens[currentToken].tokenLine;
		 	
		}
          	  
  }
  
//Check Program
  void program(){
  	do{ 
  	     
  	     
	     cout<<currentToken;
	     		 		
		if(currentToken!=myTokens.size()&&isType(myTokens[currentToken].tokenWord)||myTokens[currentToken].tokenWord=="void"){
  			currentToken++;
		}
  		else{
  		    //currentToken++;
		  	   	
  		   cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Type\n";	
  		   out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Type\n";	
  		   skipLine();
		   continue;  
		}		
  		
  		if(currentToken!=myTokens.size()&&myTokens[currentToken].tokenName=="IDENTIFIER"){
  			currentToken++;
  		}
  		else{
  		    	
  		    cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected IDENTIFIER\n";
	        out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected IDENTIFIER\n";	 
		    skipLine();
		    continue;
		  }		  
		
		if(currentToken!=myTokens.size()&&myTokens[currentToken].tokenWord=="("){
			//Update Signature Variable
		    meth_type=myTokens[currentToken-2].tokenWord;	
			signature=myTokens[currentToken-1].tokenWord;
		    cout<<meth_type<<":"<<signature;
				
			currentToken++;
			dmethod();
		} 
		else{
			dvar_global();
		} 	
	}while(currentToken!=myTokens.size());
  	
  	 sem.displaySymbol();
  	 cout<<"Program finished successfully\n";
  	 out<<"Program finished successfully";
  	 
  }
   
   //Check if it is assign function
   void assign(){
   	
   	string dif_func,dif_func1;
  	
   	//dif_func1 = nextToken().tokenName;
	if(checkTerm(nextToken())){
		
		backToken();
		exprlog();
		
		dif_func=nextToken().tokenWord;
		
		//isTypeMatching is checked here
		if(flag_decl==1){		
		   if(sem.isTypeMatching(exprType,typeMatch)){
			   exprType="";		
		   	//do nothing
		    }
		   else{
			 cout<<"Type mismatch in line:"<<myTokens[currentToken].tokenLine-1<<"\n";
			 out<<"Type mismatch in line:"<<myTokens[currentToken].tokenLine-1<<"\n";
		    }
	   }
	   
		if(dif_func==";"){
			
			return;
		}
		else{
		     //currentToken++;	
			//backToken();
			cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter";
			//out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
			
		}
		
	}   
	else{
   		dif_func=""; 
		 
		 //currentToken=currentToken+2;  			
		//backToken();
   		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Exprlog";
   		//out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Exprlog\n";
		skipLine();   	
   		return;
	                //skipLine();
	}
   }
   
   //Check if its call function
   void call_function(){
   	 	
    string dif_func,dif_func1;
       	       	   
       	   
		   dif_func=nextToken().tokenWord;
		      
		   if(dif_func==")"){
		   	 dif_func=nextToken().tokenWord;
		   
		     if(!sem.search(myTokens[currentToken-2].tokenWord)){
   		  	       out<<"Method :"<<call_type<<"not found in Line "<<myTokens[currentToken-1].tokenLine<<endl;
   		       }  
			     
			if(dif_func==";"){
		   	 	return;
		   	 }
		   	 else{
		   	 		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter";
		   	 		//out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
		   	    }		  	
			 }
			 
		   else{
		   	backToken();
		   	//cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter";
		   }
		   
		   if(checkTerm(nextToken())){
		   	
		   	backToken();
		   	
			exprlog();
		   	
		   	dif_func = nextToken().tokenWord;
		   	 
				if(dif_func==")"){
		   	 	   dif_func=nextToken().tokenWord;
		   	 
		   	 
		   	       	//If all parameters have been accepted
		   	       	 if(!sem.search(call_type)){
   		  	             out<<"Type or number of parameters in method :"<<call_type<<" are incorrect in line:"<<myTokens[currentToken-1].tokenLine<<endl;
   		                } 
		   	       	
			       if(dif_func==";"){
			       	
			       
		   	  	   return;
		   	      }
		   	       else{
					cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter";
		   	 		//out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter\n";
		   	        }
		   	    }
		   	    else if(dif_func==","){
		   	        
		   	           if(checkTerm(nextToken())){
		   	           	
		   	           	  backToken();
		   	           	  call_function();
		   	           }
		   	           else{
		   	                cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Term";
		   	 		        //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Term\n";
		   	 		        skipLine();
							return;
						  }
					      	   
					  
		   	    }
		   	    else{
		   	       cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Delimiter";	
		   	    }
		   	    
		   	    //Check Parameter matching for call function
		   	    /*
		   	    if(sem.search(call_type)){
		   	    	//Do nothing
		   	    }
		   	    else{
		   	    	out<<"Type or number of parameters in method"<<call_type<<"are incorrect in line"<<myTokens[currentToken].tokenLine-1;
		   	    }*/
		   	
		   }
		   else{
		   		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Term\n";
		   		//out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected Term\n";
		   	     skipLine();
			   	return;
		   }
		   
	           
   }
   
   //Check exprlog
   void exprlog(){
   	
   	string tok_expr,type1,type2,bin;
   	int flag_sem;
   	
   	if(checkTerm(nextToken())){
   		backToken();
		opand();
		
	   tok_expr=nextToken().tokenWord;
		
	   if(tok_expr=="|"){
	   	
        bin = tok_expr;

       
		exprlog();
		flag_sem = 1;
		
		if(loop>=2&&flag_sem==1){       
   	           type1 = stack1.top();
   	           stack1.pop();
		       type2 = stack1.top();      
		       stack1.pop();
		       exprType = (sem.calculateTypeBinary(type1,type2,bin));
		       loop=loop-1;
			   bin="";	
   	          }    	
	   }
	   else{
	   	backToken();
	   }
   	}
	else{
		//backToken();
		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
	}
	return;
   }

   
   void opand(){
   	
   string tok_expr,type1,type2,bin;	
   int flag_sem;
    
	if(checkTerm(nextToken())){
   		backToken();
		opno();
	
	   tok_expr=nextToken().tokenWord;
	  	
	  if(tok_expr=="&"){
		
		bin=tok_expr;
		opand();
		flag_sem = 1;
		//Check Binary Expr
		if(loop>=2&&flag_sem==1){       
   	           type1 = stack1.top();
   	           stack1.pop();
		       type2 = stack1.top();      
		       stack1.pop();
		       exprType = (sem.calculateTypeBinary(type1,type2,bin));
		       loop=loop-1;
			   bin="";	
   	     }    	
	  }
	  else{
	  	backToken();
	  }
   	}

	else{
		//backToken();
		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
	}	
	return;
   
   }
   
   void opno(){
   	
   	string tok_exprel,type="";
   	tok_exprel = nextToken().tokenWord;
   	int flag_sem;
   	
   	if(tok_exprel=="!"){
   	     flag_sem = 1;
		//do nothing 
   	}
   	else{
   		backToken();
   	}
    if(checkTerm(nextToken())){
   		backToken();
		exprel();
   	}
   	else{
   		//backToken();
   		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM"; 		
   	 }
   	 
   	if(loop>=2&&flag_sem==1){
    	type = stack1.top();
   	    stack1.pop();
   	    exprType = (sem.calculateTypeUnary(type,"!"));
		loop=loop-1;	    
    }
   	 return;
   	 
   }
  
   void exprel(){
   
   string tok_expr,tok_expr1,type1,type2,bin;
   int flag_sem; 
   
   if(checkTerm(nextToken())){
   	backToken();
   	expr();
   	  tok_expr=nextToken().tokenWord;
      
	  if(tok_expr==">"||tok_expr=="<"||tok_expr=="!"||tok_expr=="="
	    ){
	    	
		bin = tok_expr;
		tok_expr1=nextToken().tokenWord;
	      if(tok_expr1=="="){
	      	
		  bin+=tok_expr1;
	   	   exprel();
	   	   flag_sem = 1; 
	   	    //Check Binary Expr 	  
			if(loop>=2&&flag_sem==1){       
   	            type1 = stack1.top();
   	            stack1.pop();
		        type2 = stack1.top();      
		        stack1.pop();
		        exprType = (sem.calculateTypeBinary(type1,type2,bin));
		        loop=loop-1;
				bin="";	
   	         }  
	      }
		  else{
		  	backToken();
		   exprel();
		   flag_sem = 1;
		   //Check Binary Expr
		   
		    if(loop>=2&&flag_sem==1){       
   	           type1 = stack1.top();
   	           stack1.pop();
		       type2 = stack1.top();      
		       stack1.pop();
		       exprType = (sem.calculateTypeBinary(type1,type2,bin));
		       loop=loop-1;
			   bin="";	
   	          }    	
		  }     
      }
	  else{
	  	backToken();
	  }		
   }   
   else{
   	 //backToken();
   	 cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
   }
   
   return;  	
   }
    
   void expr(){
   
   	string tok_p;
    string type1="",type2="",bin;
    int flag_sem;
    
    if(checkTerm(nextToken())){    	
    	 backToken();
		 product();
		 
    	 tok_p= nextToken().tokenWord;
    	        	         
    	 if(tok_p=="+"||tok_p=="-"){
    	 	 bin=tok_p;
			 expr();  
			 flag_sem = 1;	 	
			//Pop two elements  
			if(loop>=2&&flag_sem==1) {       
   	           type1 = stack1.top();
   	           stack1.pop();
		       type2 = stack1.top();      
		       stack1.pop();
		       exprType = (sem.calculateTypeBinary(type1,type2,bin));
		       loop=loop-1;	
   	    }    	 
    	 	
    	 }
    	 else{
    	 	backToken();
    	 }
    	
    }  
    else{
    	//backToken();
    	cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
    }
    return;
   }
   
   void product(){
   	string tok_p;
   	
	int flag_sem;
	
   	string type1="",type2="",bin;
		 
    if(checkTerm(nextToken())){
            backToken();
    		sign();	
    		tok_p = nextToken().tokenWord;
    		
    		//Checks loop variable and pops from stack
    
    		
    		if(tok_p=="/"||tok_p=="*"||tok_p=="%"){
    			
				bin = tok_p;
				
				product();
				flag_sem=1;
				
			if(loop>=2 && flag_sem==1){       
   	           type1 = stack1.top();
   	           stack1.pop();
		       type2 = stack1.top();      
		       stack1.pop();
		       exprType = (sem.calculateTypeBinary(type1,type2,bin));
		       loop=loop-1;
			  // stack1.push(exprType);	
   	                   }
						    
    		}
    		else{
    			backToken();
    		}
    }  
	else{
    	//backToken();
    	cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
    }
    return;
   }
   
   void sign(){
   	
   //int loop=0,firstEnter;
   	string tok_s;
   	string type="";
   	int flag_sem;
   	
   	tok_s = nextToken().tokenWord;
   	
   	if(tok_s=="-"){		
		flag_sem = 1;
		//do nothing 
		
   	}
   	else{
   		backToken();
   	}
   		  	
    if(checkTerm(nextToken())){
   		backToken();
		term();	
		
		if(loop>=2&&flag_sem==1){
    	type = stack1.top();
   	    stack1.pop();
   	    exprType = (sem.calculateTypeUnary(type,"-"));
		loop=loop-1;	    
        }
     
   	}
   	 else{
   		//backToken();
   		cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
   	 }
   
    
     return;	 
   }
   
    bool checkTerm(Token t){
    	
		if(t.tokenWord=="print"){
    	 return true;	
    	}
    	else if(t.tokenWord=="read"){
    	return true;	
    	}
    	else if(t.tokenWord=="true"){
    	return true;	
    	}
    	else if(t.tokenWord=="false"){
        return true;
	    }
    	else if(t.tokenWord=="("){
    	return true;	
    	}
    	else if(t.tokenWord=="-"){
    	return true;	
    	}
    	else if(t.tokenWord=="!"){
    	return true;	
    	}
    	else if(t.tokenName=="int"){
    	return true;	
    	}
    	else if(t.tokenName=="IDENTIFIER"){
    	return true;	
    	}
    	else if(t.tokenName=="OCTAL"){
    	return true;	
    	}
    	else if(t.tokenName=="HEXADECIMAL"){
    	return true;	
    	}
    	else if(t.tokenName=="float"){
    	return true;	
    	}
    	else if(t.tokenName=="string"){
    	return true;	
    	}
    	else if(t.tokenName=="OCTAL"){
    	return true;	
    	}
    	else if(t.tokenName=="char"){
    	return true;	
    	}
    	else if(t.tokenName=="HEXADECIMAL"){
    	return true;	
    	}
    	else if(t.tokenName=="boolean"){
    	return true;	
    	}
    	else{
    		return false;
    	}
    }
   
   //Check the term
   
   void term(){
   	
   	string term_str,currName;
   	
   	
   	term_str=nextToken().tokenWord;
    
    
     if(term_str=="true"||term_str=="false"){
        return;
      }
     else{
          backToken();
          term_str=nextToken().tokenName;
       }
     
	   
     if(isDataType(term_str)&&term_str!="IDENTIFIER"){
		    
			stack1.push(myTokens[currentToken-1].tokenName);
			loop++;
			exprType = stack1.top();
			call_type += "-"+myTokens[currentToken-1].tokenName;
			return;
      }
    
          
      if(term_str=="IDENTIFIER"){
      	
      	//Push to Stack after checking typefrom symbol table.
      	if(sem.search(myTokens[currentToken-1].tokenWord,currentScope)){
           stack1.push(sem.getType(myTokens[currentToken-1].tokenWord));
           exprType = stack1.top();
           
           call_type += "-" + sem.getType(myTokens[currentToken-1].tokenWord);
		   
		   loop++;	
        }
        
      	term_str= nextToken().tokenWord;
      	if(term_str=="("){
      	    
      	    if(checkTerm(nextToken())){
      	      backToken();	
      	      exprlog(); 	
      	    }
		  	else{
		  		backToken();
		  	}
      			term_str= nextToken().tokenWord;
      			if(term_str==")"){
      				return;
      			}
      			else{
      					cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected DELIMITER";
   			           // out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected DELIMITER";
      			}
      		
      	}
      	else{
      		backToken();
      		return;
      	}
      }
      else{
      	  backToken();
      	  term_str=nextToken().tokenWord;
      }
      
      if(term_str=="print"||term_str=="read"){
      	term_str= nextToken().tokenWord;
      	if(term_str=="("){
      		
      		exprlog();
      			term_str= nextToken().tokenWord;
      			if(term_str==")"){
      				return;
      			}
      			else{
      					cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected DELIMITER";
   			            //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected DELIMITER";
      			}
      		
      	}
      	else{
      		backToken();
      		return;
      	}
      }
      else{
      	  backToken();
      	  term_str=nextToken().tokenWord;
      }
      
      if(term_str=="("){
      	 exprlog();
		  
		  term_str=nextToken().tokenWord;
      	
      	  	if(term_str==")"){
      				return;
      			}
      		else{
      			
      			cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
   			    //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
      		}
        
      	
      }
      else{
      	  cout<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
   		  //out<<"Line:"<<myTokens[currentToken].tokenLine<<"\t"<<"expected TERM";
   		  skipLine();
   		  return;
      }
   	   
   	
    
    }
    
  
  
		 int main(int argc, char *argv[]){
		    
			string pattern;
		
                        ifstream in(argv[1]);
	
                        out.open(argv[2]); 
      			//ifstream in("test2.txt");
		
			if(in.is_open()){
		
			while(in.good()){
		
		    	getline(in,pattern,'\n');
				   splitLine(pattern);		   
			}
		
		  }
		   
		   
		   
		    else{
		    	cout<<"Unable to open the file";
		    }
		 
		 
		 
		     for ( int i = 0; i < myTokens.size(); i++) {
		            cout<< myTokens[i].tokenName<<" "<<myTokens[i].tokenWord<<" "<<myTokens[i].tokenLine<<"\n";
		        }
		
		  //Parsing begins here.
		  
		      program();
		   			
			return 0;
	}	
	
	