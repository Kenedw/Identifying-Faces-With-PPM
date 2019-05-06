#ifndef PPMC_PPMC_H_
#define PPMC_PPMC_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <map>

#include "Node.h"
#include "arithmetic.h"

class PPMC {

private:
    
    unsigned int numCh = 256;
    unsigned int k = 0;
    
    bool usedCh[256] = {false};    
    int order = 0;
    int N_TRAINNER = 9; //numero de imagens para o treinamento

    std::vector<Node*> excluded;
    ArithmeticCoder arithmetic;

    Node* root = nullptr;
    Node* base = nullptr;
    
    double step_progess = 0.0;
    double progess = 0.0;
    double duration = 0.0;
    long   CompressionRate = 0;

    std::fstream input;
    std::fstream output;

    std::string* data;

    void Encode(unsigned char symbol_);

    void InsertSymbol(unsigned char symbol_);

    void GetInterval(Node *pDad, Node *pChild, bool *arr);

    void GetInverval2(unsigned char symbol_);

    void Progress();

    int GetContextDepth(Node *node);

    void FreeTree(Node* node);

    void Log(std::string msg);

public:

    PPMC(unsigned int order_, std::string inputname, std::string outputname);

    void Compress();

    void PrintTree(Node* node, int deep);

    void SetInput(std::string inputname,std::string outputname);

    void FreeTree();
  
};

#endif //PPMC_PPMC_H_