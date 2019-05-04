#include "Node.h"

Node::Node(const unsigned char symbol_) : symbol(symbol_)
{}

Node::Node(const char type_) : type(type_)
{}

Node::~Node()
{
    free(pVine);
    free(pEsc);
    free(pChild);
    free(pSibiling);
}

void Node::PrintChildren()
{
    Node *pAux = this->pChild;

    while(pAux != nullptr) {
        std::cout << pAux->GetSymbol() << std::endl;
        pAux = pAux->GetSibiling();
    }
}


Node* Node::InsertChild(unsigned char symbol_)
{
    if(!pChild) {
        Node *pNewNode = new Node(symbol_);
        Node *pNewEsc = new Node(ESC);
        this->pChild = pNewNode;
        this->childrenCount += 2;
        this->pEsc = pNewEsc;
        return pNewNode;
    }

    Node *pAuxNode = pChild;
    Node *pNextNode = nullptr;

    while(pAuxNode != nullptr) {

        if(pAuxNode->GetSymbol() == symbol_) {
            pAuxNode->IncreaseCount();
            this->childrenCount++;
            return pAuxNode;
        }
        else if(pAuxNode->GetSymbol() < symbol_) {
            pNextNode = pAuxNode;
        }

        pAuxNode = pAuxNode->GetSibiling();
    }

    Node *pNewNode = new Node(symbol_);
    this->pEsc->IncreaseCount();
    this->childrenCount += 2;
    Node *pNewAuxNode = nullptr;

    if(pNextNode == nullptr) {
        pNewAuxNode = pChild;
        pChild = pNewNode;
        pChild->SetSibiling(pNewAuxNode);
    } 
    else {
        pNewAuxNode = pNextNode->GetSibiling();
        pNextNode->SetSibiling(pNewNode);
        pNewNode->SetSibiling(pNewAuxNode);
    }
    
    return pNewNode;
}

void Node::IncreaseCount()
{
    this->count++;
}

void Node::SetSibiling(Node *node)
{
    this->pSibiling = node;
}

void Node::SetVine(Node *node)
{
    this->pVine = node;
}

Node* Node::FindChild(unsigned char symbol_)
{
    Node* pAuxNode = this->pChild;

    while(pAuxNode != nullptr) {
        
        if(pAuxNode->GetSymbol() == symbol_) {
            return pAuxNode;
        }

        pAuxNode = pAuxNode->GetSibiling();        
    }

    return nullptr;
}

Node* Node::GetVine()
{
    return this->pVine;
}

Node* Node::GetEsc()
{
    return this->pEsc;
}

Node* Node::GetSibiling()
{
    return this->pSibiling;
}

Node* Node::GetChild()
{
    return this->pChild;
}

unsigned char Node::GetSymbol()
{
    return this->symbol;
}

unsigned char Node::GetType()
{
    return this->type;
}

unsigned int Node::GetCount()
{
    return this->count;
}

unsigned int Node::GetChildrenCount()
{
    return this->childrenCount;
}
