//AST file to imporve the tree from parser


#pragma once


#include <string>
#include <iostream>
#include "IRcode.h"
#include "symbolTable.h"
using namespace std;

int scope = 0;



// a Node for a tree
struct Node {
	int nodetype;
	string type;
	int rtntype;
	string code;
	string data;
	string val;
	Node* Left = NULL;
	Node* Right = NULL;
	struct Entry *s;
};

// Binary tree class
class BinTree {
public:
	Node* root = NULL; // the root node
	BinTree() {}
	Node * addNode(string data, Node* left, Node* right);
	Node * addSym(Entry* entry);
	Node * addNum(int num);
	void printTree(Node* thisNode, int indent);
	void genIR(Node* thisNode);
	bool isBinOp(string data);
};

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

void BinTree::genIR(Node* thisNode)
{
  	if (thisNode == NULL){
    	return;
	}
	string thisData = thisNode->data;
	cout << "|-----"<<thisNode->data << "\n";
	if(thisData == "Program"){
		cout << "FOUND START\n";
	}else if(thisData == "Func"){
		cout << "FOUND FUNC\n";
		IRStartFunc(thisNode->Left->data);
		scope = getScope(thisNode->Left->data);
		cout << "SCOPE: " << thisNode->Left->data << ".\n\tAt index : " << scope << "\n";
		int parNum = getParamNum(scope);
		for(int i = 0; i < parNum; i++){
			IRSetParam(i);
		}
	}else if(thisData == "StmtList"){

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
			int thisID = findID(const_cast<char*>(thisNode->Left->Left->data.c_str()), scope);
			IRWrite(thisID);
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

bool BinTree::isBinOp(string data){
	if(data == "*" || data == "/" || data == "+" || data == "-"){
		return true;
	}
	return false;
}

