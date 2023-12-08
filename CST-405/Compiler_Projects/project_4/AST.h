#pragma once


#include <string>
#include <iostream>
#include "IRcode.h"

#include "symbolTable.h"
using namespace std;
// Global variables
int scope = 0;

int ifCount = -1;
bool isIF = false;
bool isElse = false;
int ifRecur = 0;
int elseRecur = -1;
bool isWhile = false;
int whileCount = -1;
int stringC = 0;



// Node structure represents a node in the abstract syntax tree
struct Node {
	int nodetype;
	string type;
	int rtntype;
	string code;
	string data;
	string val;
	Node* Left = NULL;
	Node* Right = NULL;
	struct Entry *s; // Symbol table entry
};

// Binary Tree class for constructing the abstract syntax tree
class BinTree {
public:
	Node* root = NULL; 
	BinTree() {}
	// Functions for adding nodes to the tree
	Node * addNode(string data, Node* left, Node* right);
	Node * addSym(Entry* entry);
	Node * addNum(int num);
	// Functions for printing, deleting, and optimizing the tree
	void printTree(Node* thisNode, int indent);
	void deleteTree(Node* thisNode);
	void optimizeTree(Node* thisNode);
	int deadCodeTree(Node* thisNode, string find, int c);
	void genIR(Node* thisNode);
	bool isBinOp(string data);
};
// Function to add a new node with data, left, and right children
Node * BinTree::addNode(string data, Node* left, Node* right)
{
	
	Node *addedNode = new Node;
	root = addedNode;
	root -> nodetype = 0;
	root -> data = data;
	root -> Left = left;
	root -> Right = right;
	return root;
}
// Function to add a symbol node to the tree
Node * BinTree::addSym(Entry* entry)
{
	Node *addedNode = new Node;
	addedNode -> s = entry;
	addedNode -> val = entry->itemName;
	addedNode -> nodetype = 1;
	addedNode -> type = entry->itemType;
	addedNode -> Left = NULL;
	addedNode -> Right = NULL;
	root = (struct Node *)addedNode;
	return root;
}
// Function to add a numerical node to the tree
Node * BinTree::addNum(int num)
{
	
	Node *addedNode = new Node;
	root = addedNode;
	root -> val = std::to_string(num);
	root -> nodetype = 2;
	root -> type = 1;
	root -> data = std::to_string(num);
	root -> Left = NULL;
	root -> Right = NULL;
	return root;
}
// Function to delete a subtree rooted at thisNode

void BinTree::deleteTree(Node* thisNode)
{
	thisNode->Right = thisNode->Right->Right;
	
}
// Function to print the tree with indentation

void BinTree::printTree(Node* thisNode, int indent)
{
  if (thisNode != NULL){
    for(int i = 0; i < indent; i++) {cout << "|     ";}
  }else
    return;
	
	cout << "|-----"<<thisNode->data << "\n";
	
	printTree(thisNode->Left,indent + 1);  
	printTree(thisNode->Right,indent + 1); 
}

// Function to optimize the tree (specific optimization for dead code in this case)

void BinTree::optimizeTree(Node* thisNode)
{
  if (thisNode == NULL){
    return;
  }

  if(thisNode->Right != NULL && thisNode->Right->Left != NULL && thisNode->Right->Left->data == "="){
	cout << "DeadCode::" << thisNode->Right->Left->Left->data << " = ";
	int deadC = deadCodeTree(root, thisNode->Right->Left->Left->data, 0);
	cout << deadC << "\n";
	if(deadC < 3){
		deleteTree(thisNode);
	}
  }

	optimizeTree(thisNode->Left);  
	optimizeTree(thisNode->Right); 
}

// Function to identify dead code in the tree

int BinTree::deadCodeTree(Node* thisNode, string find, int c)
{
  if (thisNode == NULL){
    return false;
  }
  if(c == 3){
	return c;
  }

  if(thisNode->data == find){
	c++;
	return c;
  }
	int c1 = deadCodeTree(thisNode->Left, find, c);
	if(c1 > c){
		c = c1;
	} 
	int c2 = deadCodeTree(thisNode->Right, find, c);
	if(c2 > c){
		c = c2;
	}
	return c;
}

// Function to generate intermediate code from the tree

void BinTree::genIR(Node* thisNode)
{
  	if (thisNode == NULL){
    	return;
	}
	string thisData = thisNode->data;
	cout << "|-----"<<thisNode->data << "\n";

	 // Intermediate code generation logic for different node types
	if(thisData == "Program"){
		cout << "FOUND START\n";
		IRLargestVar(getEmptyID()+3);
	}else if(thisData == "Func"){
		cout << "FOUND FUNC\n";
		IRStartFunc(thisNode->Left->data);
		scope = getScope(thisNode->Left->data);
		cout << "SCOPE: " << thisNode->Left->data << ".\n\tAt index : " << scope << "\n";
		int parNum = getParamNum(scope);
		for(int i = 0; i < parNum; i++){
			IRSetParam(i);
		}
	}else if(thisData == "WHILE"){
		if(isWhile){
			cout << "\n\n\n UH OH, while Recursion\n\n\n";
		}else{
			isWhile = true;
			whileCount++;
		}
		IRWhileStart(whileCount);
		string thisL = thisNode->Left->Left->data;
		int thisLID = findID(const_cast<char*>(thisL.c_str()), scope);
		string thisR = thisNode->Left->Right->data;
		int thisRID = findID(const_cast<char*>(thisR.c_str()), scope);
		if(thisNode->Left->data == "=="){
			if(thisRID == -1){
				IRWhileEqNum(thisLID, thisR, whileCount);
			}else{
				IRWhileEqVar(thisLID, thisRID, whileCount);
			} 
		} else if(thisNode->Left->data == ">"){
			if(thisRID == -1){
				IRWhileGrNum(thisLID, thisR, whileCount);
			}else{
				IRWhileGrVar(thisLID, thisRID, whileCount);
			} 
		} else if(thisNode->Left->data == "<"){
			if(thisRID == -1){
				IRWhileLeNum(thisLID, thisR, whileCount);
			}else{
				IRWhileLeVar(thisLID, thisRID, whileCount);
			} 
		} else if(thisNode->Left->data == ">="){
			if(thisRID == -1){
				IRWhileGrEqNum(thisLID, thisR, whileCount);
			}else{
				IRWhileGrEqVar(thisLID, thisRID, whileCount);
			} 
		} else if(thisNode->Left->data == "<="){
			if(thisRID == -1){
				IRWhileLeEqNum(thisLID, thisR, whileCount);
			}else{
				IRWhileLeEqVar(thisLID, thisRID, whileCount);
			} 
		}
		IRWhileEndGoTo(whileCount);
		IRWhileCode(whileCount);
	}else if(thisData == "IF"){
		if(isIF){
			ifRecur++;
		}else{
			ifCount++;
			isIF = true;
		}
		if(thisNode->Right->Right != NULL){
			if(isElse = true){
				elseRecur++;
			}
			isElse = true;
		}
		string thisL = thisNode->Left->Left->data;
		int thisLID = findID(const_cast<char*>(thisL.c_str()), scope);
		string thisR = thisNode->Left->Right->data;
		int thisRID = findID(const_cast<char*>(thisR.c_str()), scope);
		if(thisNode->Left->data == "=="){
			if(thisRID == -1){
				IRIfEqNum(thisLID, thisR, ifCount, ifRecur);
			}else{
				IRIfEqVar(thisLID, thisRID, ifCount, ifRecur);
			} 
		} else if(thisNode->Left->data == ">"){
			if(thisRID == -1){
				IRIfGrNum(thisLID, thisR, ifCount, ifRecur);
			}else{
				IRIfGrVar(thisLID, thisRID, ifCount, ifRecur);
			} 
		} else if(thisNode->Left->data == "<"){
			if(thisRID == -1){
				IRIfLeNum(thisLID, thisR, ifCount, ifRecur);
			}else{
				IRIfLeVar(thisLID, thisRID, ifCount, ifRecur);
			} 
		} else if(thisNode->Left->data == ">="){
			if(thisRID == -1){
				IRIfGrEqNum(thisLID, thisR, ifCount, ifRecur);
			}else{
				IRIfGrEqVar(thisLID, thisRID, ifCount, ifRecur);
			} 
		} else if(thisNode->Left->data == "<="){
			if(thisRID == -1){
				IRIfLeEqNum(thisLID, thisR, ifCount, ifRecur);
			}else{
				IRIfLeEqVar(thisLID, thisRID, ifCount, ifRecur);
			} 
		}
		IRIfEndGoto(ifCount, ifRecur);
		IRIfDecl(ifCount, ifRecur);
	}else if(thisData == "WhileEnd"){
		if(isWhile){
			IRWhileStartGoTo(whileCount);
			IRWhileEnd(whileCount);
			isWhile = false;
		}
	}else if(thisData == "BlockEnd"){
		cout << "\n\n|||||||" << isIF << "|" << isElse << "|||||||\n|||||||" << ifRecur << "|" << elseRecur << "|||||||\n\n";
		if(isIF && isElse){
			cout << "\n1\n";
			IRElseEndGoto(ifCount, ifRecur);
			cout << "\n2\n";
			IRIfEndDecl(ifCount, ifRecur);
			if(ifRecur > 0){
				ifRecur--;
			}else{
				isIF = false;
			}
		} else if (isElse){
			if(elseRecur > 0){
				elseRecur--;
				
			}else{
				isElse = false;
			}
			IRElseEndDecl(ifCount, elseRecur);
		}else if (isIF){
			IRIfEndDecl(ifCount, ifRecur);
			if(ifRecur > 0){
				ifRecur--;
			}else{
				isIF = false;
			}
			
		}
	}else if(thisData == "StmtList" || thisData == "BlockList"){
		if(thisNode->Left->data == "="){
			string thisL = thisNode->Left->Left->data;
			int thisLID = findID(const_cast<char*>(thisL.c_str()), scope);
			string thisR = thisNode->Left->Right->data;
			int thisRID = findID(const_cast<char*>(thisR.c_str()), scope);
			cout << "FOUND STMT \n LEFT: " << thisL << "\n RIGHT: " << thisR << "\n";
			cout << "ID LEFT: " << thisLID << " | ID RIGHT: " << thisRID << "\n";
			if(thisRID == -1){
				if(!isBinOp(thisNode->Left->Right->data))
				{	
					if(thisNode->Left->Right->data == "FuncCall"){
						
						
						int s = getScope(thisNode->Left->Right->Left->data);
						int paramNum = getParamNum(s);
						if(paramNum == 2){
						int thisID1 = findID(const_cast<char*>(thisNode->Left->Right->Right->Left->data.c_str()), scope);
						int thisID2 = findID(const_cast<char*>(thisNode->Left->Right->Right->Right->data.c_str()), scope);
						
						IRJalInput(0, thisID1);
						IRJalInput(1, thisID2);
						}
						cout << "FUNC CALL\n";
						IRJal(thisNode->Left->Right->Left->data);
						int thisID3 = findID(const_cast<char*>(thisNode->Left->Left->data.c_str()), scope);
						IRJalReturn(thisID3);
					}else{
						varEqNum(thisLID, thisR);
					}
				}else{
					int flip = 0;
					Node* tempNode = thisNode->Left->Right;
					string thisL = tempNode->Left->data;
					int tempLID = findID(const_cast<char*>(thisL.c_str()), scope);
					int tempRID;
					string thisR;
					if(tempLID == -1){
						IRBinOpStart(getEmptyID() + (flip%2), thisL);
					}else{
						IRBinOpStart(getEmptyID() + (flip%2), tempLID);
					}
					flip++;
					while(isBinOp(tempNode->Right->data)){
						thisR = tempNode->Right->Left->data;
						tempRID = findID(const_cast<char*>(thisR.c_str()), scope);

						if(tempRID == -1){
							IRBinOpAdd(tempNode->data, thisR, getEmptyID() + (flip%2), getEmptyID() + ((flip+1)%2));
						}else{
							IRBinOpAdd(tempNode->data, tempRID, getEmptyID() + (flip%2), getEmptyID() + ((flip+1)%2));
						}
						flip++;
						tempNode = tempNode->Right;
					}
					thisR = tempNode->Right->data;
					tempRID = findID(const_cast<char*>(thisR.c_str()), scope);
					int tempID = findID(const_cast<char*>(thisNode->Left->Left->data.c_str()), scope);
					flip++;
					if(tempRID == -1){
						IRBinOpEnd(tempNode->data, thisR, tempID, getEmptyID() + (flip%2));
					}else{
						IRBinOpEnd(tempNode->data, tempRID, tempID, getEmptyID() + (flip%2));
					}
					
				}
			}else
			{
				varEqVar(thisLID, thisRID);
			}
		}else if (thisNode->Left->data == "WRITE"){
			cout << "!!!" << thisNode->Left->Left->data << "\n";
			if(thisNode->Left->Left->data[0] == '\"'){
				IRWriteString(thisNode->Left->Left->data);
				string thisID = "out_string" + to_string(stringC);
				IRWriteStr(thisID);
				stringC++;
			}else{
				int thisID = findID(const_cast<char*>(thisNode->Left->Left->data.c_str()), scope);
				IRWrite(thisID);
			}
		}else if (thisNode->Left->data == "RETURN"){
			int thisID = findID(const_cast<char*>(thisNode->Left->Left->data.c_str()), scope);
			IRReturn(thisID);
		}else if (thisNode->Left->data == "WRITELN"){
			IRWriteLn();
		}
		if(thisNode->Right->data != "StmtList"){
			if (thisNode->Right->data == "WRITE"){
				int thisID = findID(const_cast<char*>(thisNode->Right->Left->data.c_str()), scope);
				IRWrite(thisID);
			} else if (thisNode->Right->data == "RETURN"){
				int thisID = findID(const_cast<char*>(thisNode->Right->Left->data.c_str()), scope);
				IRReturn(thisID);
			}
		}

	}
	
	genIR(thisNode->Left);  
	genIR(thisNode->Right); 
}
// Helper function to check if a given operator is binary

bool BinTree::isBinOp(string data){
	if(data == "*" || data == "/" || data == "+" || data == "-"){
		return true;
	}
	return false;
}

