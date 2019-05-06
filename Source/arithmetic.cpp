//
// Created by Leoberto Soares on 2/18/19.
//

#include "arithmetic.h"


const unsigned int g_FirstQuarter = 0x20000000;
const unsigned int g_ThirdQuarter = 0x60000000;
const unsigned int g_Half         = 0x40000000;

ArithmeticCoder::ArithmeticCoder()
{
    mBitCount = 0;
    mBitBuffer = 0;

    mLow = 0;
    mHigh = 0x7FFFFFFF;
    mScale = 0;
    mStep = 0;
}

void ArithmeticCoder::SetFile( std::fstream *file )
{
    mFile = file;
}

void ArithmeticCoder::SetBit( const unsigned char bit )
{
    mBitBuffer = (mBitBuffer << 1) | bit;
    mBitCount++;

    if(mBitCount == 8)
    {
        mFile->write(reinterpret_cast<char*>(&mBitBuffer),sizeof(mBitBuffer));
        mBitCount = 0;
    }
}

void ArithmeticCoder::SetBitFlush()
{
    while( mBitCount != 0 )
        SetBit( 0 );
}

unsigned char ArithmeticCoder::GetBit()
{
    if(mBitCount == 0)
    {
        if( !( mFile->eof() ) )
            mFile->read(reinterpret_cast<char*>(&mBitBuffer),sizeof(mBitBuffer));
        else
            mBitBuffer = 0;

        mBitCount = 8;
    }

    unsigned char bit = mBitBuffer >> 7;
    mBitBuffer <<= 1;
    mBitCount--;

    return bit;
}

void ArithmeticCoder::Encode( const unsigned int low_count,
                              const unsigned int high_count,
                              const unsigned int total       )
{

    mStep = ( mHigh - mLow + 1 ) / total;
    mHigh = mLow + mStep * high_count - 1;

    mLow = mLow + mStep * low_count;

    while( ( mHigh < g_Half ) || ( mLow >= g_Half ) )
    {
        if( mHigh < g_Half )
        {
            SetBit( 0 );
            mLow = mLow * 2;
            mHigh = mHigh * 2 + 1;

            for(; mScale > 0; mScale-- )
                SetBit( 1 );
        }
        else if( mLow >= g_Half )
        {
            SetBit( 1 );
            mLow = 2 * ( mLow - g_Half );
            mHigh = 2 * ( mHigh - g_Half ) + 1;

            for( ; mScale > 0; mScale-- )
                SetBit( 0 );
        }
    }

    while( ( g_FirstQuarter <= mLow ) && ( mHigh < g_ThirdQuarter ) )
    {
        mScale++;
        mLow = 2 * ( mLow - g_FirstQuarter );
        mHigh = 2 * ( mHigh - g_FirstQuarter ) + 1;
    }
}

void ArithmeticCoder::EncodeFinish()
{
    if( mLow < g_FirstQuarter )
    {
        SetBit( 0 );

        for(unsigned int i=0; i<mScale+1; i++ )
            SetBit(1);
    }
    else
    {
        SetBit( 1 );
    }

    SetBitFlush();
}