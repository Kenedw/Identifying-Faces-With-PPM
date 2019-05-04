//
// Created by Leoberto Soares on 2/18/19.
//

#ifndef PPMC_ARITHMETIC_H
#define PPMC_ARITHMETIC_H

#include <iostream>
#include <fstream>

class ArithmeticCoder {

public:

    ArithmeticCoder();

    void SetFile(std::fstream *file );

    void Encode(unsigned int low_count,
                unsigned int high_count,
                unsigned int total );

    void EncodeFinish();

protected:

    void SetBit(unsigned char bit);
    void SetBitFlush();
    unsigned char GetBit();

    unsigned char mBitBuffer;
    unsigned char mBitCount;

    std::fstream *mFile;

    unsigned int mLow;
    unsigned int mHigh;
    unsigned int mStep;
    unsigned int mScale;
};


#endif //PPMC_ARITHMETIC_H
