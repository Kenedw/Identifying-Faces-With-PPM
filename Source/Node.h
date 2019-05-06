#ifndef PPMC_NODE_H_
#define PPMC_NODE_H_

#include <iostream>
#include <vector>

const char NORMAL = 0;
const char ROOT = 1;
const char ESC = 2;

class Node {

private:

    unsigned char symbol;
    unsigned char type = NORMAL;
    
    unsigned int count = 1;
    unsigned int childrenCount = 0;

    Node *pVine = nullptr;
    Node *pEsc = nullptr;
    Node *pChild = nullptr;
    Node *pSibiling = nullptr;

public:

    explicit Node(const unsigned char symbol_);

    explicit Node(char type_);

    ~Node();

    void InsertEsc();

    void PrintChildren();

    void IncreaseCount();

    void SetSibiling(Node *node);

    void SetVine(Node *node);

    Node* InsertChild(unsigned char symbol_);

    Node* FindChild(unsigned char symbol_);

    Node* GetVine();

    Node* GetEsc();

    Node* GetSibiling();

    Node* GetChild();

    unsigned char GetSymbol();

    unsigned char GetType();
    
    unsigned int GetCount();

    unsigned int GetChildrenCount();

    void freeNode(Node* node);

    void SaveNode(Node* node, std::fstream *file);

};



#endif //PPMC_NODE_H_