#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#define EOF_CODE 256
#define BYTE 8
#define MASK 0xFF
#define INITIAL_SIZE 9
#define NEXT_BUMP 1 << INITIAL_SIZE
#define CURRENT_CODE 1 << (INITIAL_SIZE - 1)
#define ZERO 0
#define ONE 1

#include <fstream>
#include <iostream>
using namespace std;

// Compressor
class InputSymbol
{
    ifstream& input;
    public:
        InputSymbol(ifstream& input);
        bool operator>> ( char &c);
        ~InputSymbol();    
    
};

class OutputSymbol
{
    ofstream& output;
    int m_code_size;
    int m_pending_bits;
    unsigned int m_pending_output;
    unsigned int m_current_code;
    unsigned int m_next_bump;
    unsigned int m_max_code;
    public:
        OutputSymbol(ofstream& output, unsigned int maximo);
        void operator<< (const unsigned int &i);
        ~OutputSymbol();
    private:
        void flush(const int val);
};


// Decompressor
class InputStream
{
    ifstream& input;
    int m_code_size;
    int m_available_bits;
    unsigned int m_pending_bits;
    unsigned int m_current_code;
    unsigned int m_next_bump;
    unsigned int m_max_code;
    public:
        InputStream(ifstream& input, unsigned int maximo);
        bool operator>> (unsigned int& i);
        ~InputStream();
};

class OutputStream
{
    ofstream& output;
    public:
        OutputStream(ofstream& output);
        void operator<< (const string& simbolo);
        ~OutputStream();
};

#endif