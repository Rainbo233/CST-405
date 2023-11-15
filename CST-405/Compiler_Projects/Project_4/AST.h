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
int elseRecur = 0;

// Node structure for the binary tree
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
    Node* root = NULL;
    BinTree() {}
    Node * addNode(string data, Node* left, Node* right);
    Node * addSym(Entry* entry);
    Node * addNum(int num);
    void printTree(Node* thisNode, int indent);
    void genIR(Node* thisNode);
    bool isBinOp(string data);
};

// Method to add a node to the binary tree
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

// Method to add a symbol to the binary tree
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

// Method to add a number node to the binary tree
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

// Method to print the binary tree
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

// Method to generate intermediate code from the binary tree
void BinTree::genIR(Node* thisNode)
{
    if (thisNode == NULL){
        return;
    }
    string thisData = thisNode->data;
    cout << "|-----"<<thisNode->data << "\n";
    
    // Check different cases for intermediate code generation
    if(thisData == "Program"){
        cout << "FOUND START\n";
        IRLargestVar(getEmptyID()+3);
    } else if(thisData == "Func"){
        cout << "FOUND FUNC\n";
        IRStartFunc(thisNode->Left->data);
        scope = getScope(thisNode->Left->data);
        cout << "SCOPE: " << thisNode->Left->data << ".\n\tAt index : " << scope << "\n";
        int parNum = getParamNum(scope);
        for(int i = 0; i < parNum; i++){
            IRSetParam(i);
        }
    } else if(thisData == "IF"){
        // Intermediate code generation for IF statement
        if(isIF){
            ifRecur++;
        } else {
            ifCount++;
            isIF = true;
        }
        if(thisNode->Right->Right != NULL){
            if(isElse = true){
                elseRecur++;
            }
            isElse = true;
        }
        // Intermediate code generation for comparison
        string thisL = thisNode->Left->Left->data;
        int thisLID = findID(const_cast<char*>(thisL.c_str()), scope);
        string thisR = thisNode->Left->Right->data;
        int thisRID = findID(const_cast<char*>(thisR.c_str()), scope);
        if(thisNode->Left->data == "=="){
            if(thisRID == -1){
                IRIfEqNum(thisLID, thisR, ifCount, ifRecur);
            } else {
                IRIfEqVar(thisLID, thisRID, ifCount, ifRecur);
            } 
        } else if(thisNode->Left->data == ">"){
            if(thisRID == -1){
                IRIfGrNum(thisLID, thisR, ifCount, ifRecur);
            } else {
                IRIfGrVar(thisLID, thisRID, ifCount, ifRecur);
            } 
        } else if(thisNode->Left->data == "<"){
            if(thisRID == -1){
                IRIfLeNum(thisLID, thisR, ifCount, ifRecur);
            } else {
                IRIfLeVar(thisLID, thisRID, ifCount, ifRecur);
            } 
        } else if(thisNode->Left->data == ">="){
            if(thisRID == -1){
                IRIfGrEqNum(thisLID, thisR, ifCount, ifRecur);
            } else {
                IRIfGrEqVar(thisLID, thisRID, ifCount, ifRecur);
            } 
        } else if(thisNode->Left->data == "<="){
            if(thisRID == -1){
                IRIfLeEqNum(thisLID, thisR, ifCount, ifRecur);
            } else {
                IRIfLeEqVar(thisLID, thisRID, ifCount, ifRecur);
            } 
        }
        IRIfEndGoto(ifCount, ifRecur);
        IRIfDecl(ifCount, ifRecur);
    } else if(thisData == "BlockEnd"){
        // Intermediate code generation for block end
        cout << "\n\n|||||||" << isIF << "|" << isElse << "|||||||\n|||||||" << ifRecur << "|" << elseRecur << "|||||||\n\n";
        if(isIF && isElse){
            cout << "\n1\n";
            IRElseEndGoto(ifCount, ifRecur);
            cout << "\n2\n";
            IRIfEndDecl(ifCount, ifRecur);
            if(ifRecur > 0){
                ifRecur--;
            } else {
                isIF = false;
            }
        } else if (isElse){
            IRElseEndDecl(ifCount, elseRecur);
            if(elseRecur > 0){
                elseRecur--;
            } else {
                isElse = false;
            }
        } else if (isIF){
            IRIfEndDecl(ifCount, ifRecur);
            if(ifRecur > 0){
                ifRecur--;
            } else {
                isIF = false;
            }
        }
    } else if(thisData == "StmtList" || thisData == "BlockList"){
        // Intermediate code generation for statements
        if(thisNode->Left->data == "="){
            // Intermediate code generation for assignment
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
                    } else {
                        varEqNum(thisLID, thisR);
                    }
                } else {
                    // Intermediate code generation for binary operations
                    int flip = 0;
                    Node* tempNode = thisNode->Left->Right;
                    string thisL = tempNode->Left->data;
                    int tempLID = findID(const_cast<char*>(thisL.c_str()), scope);
                    int tempRID;
                    string thisR;
                    if(tempLID == -1){
                        IRBinOpStart(getEmptyID() + (flip%2), thisL);
                    } else {
                        IRBinOpStart(getEmptyID() + (flip%2), tempLID);
                    }
                    flip++;
                    while(isBinOp(tempNode->Right->data)){
                        thisR = tempNode->Right->Left->data;
                        tempRID = findID(const_cast<char*>(thisR.c_str()), scope);

                        if(tempRID == -1){
                            IRBinOpAdd(tempNode->data, thisR, getEmptyID() + (flip%2), getEmptyID() + ((flip+1)%2));
                        } else {
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
                    } else {
                        IRBinOpEnd(tempNode->data, tempRID, tempID, getEmptyID() + (flip%2));
                    }
                }
            } else {
                varEqVar(thisLID, thisRID);
            }
        } else if (thisNode->Left->data == "WRITE"){
            // Intermediate code generation for WRITE statement
            int thisID = findID(const_cast<char*>(thisNode->Left->Left->data.c_str()), scope);
            IRWrite(thisID);
        } else if (thisNode->Left->data == "RETURN"){
            // Intermediate code generation for RETURN statement
            int thisID = findID(const_cast<char*>(thisNode->Left->Left->data.c_str()), scope);
            IRReturn(thisID);
        } else if (thisNode->Left->data == "WRITELN"){
            // Intermediate code generation for WRITELN statement
            IRWriteLn();
        }
        if(thisNode->Right->data != "StmtList"){
            if (thisNode->Right->data == "WRITE"){
                // Intermediate code generation for WRITE statement
                int thisID = findID(const_cast<char*>(thisNode->Right->Left->data.c_str()), scope);
                IRWrite(thisID);
            } else if (thisNode->Right->data == "RETURN"){
                // Intermediate code generation for RETURN statement
                int thisID = findID(const_cast<char*>(thisNode->Right->Left->data.c_str()), scope);
                IRReturn(thisID);
            }
        }
    }
    
    // Recursive calls for left and right nodes
    genIR(thisNode->Left);
    genIR(thisNode->Right);
}

// Method to check if a given operation is a binary operation
bool BinTree::isBinOp(string data){
    if(data == "*" || data == "/" || data == "+" || data == "-"){
        return true;
    }
    return false;
}
