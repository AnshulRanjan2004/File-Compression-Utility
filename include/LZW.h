#ifndef LZW_H
#define LZW_H

#define EXTENSION_ERROR "Unrecognized compressed file extension"
#define EXTENSION "cmp"
#define DOT "."
#define BITS 15
#define ALPHABET_SIZE 256

#include <fstream>
#include <iostream>
#include <unordered_map>
#include "file-manager.h"


using namespace std;

class LZW
{
    const unsigned int tamanho_maximo = (1 << BITS) - 1;
   
    string nome_arquivo_original;
    string nome_arquivo_modificado;

    public:
        LZW(string filename);
        void compressor();
        void decompressor();
        bool is_compacted_type();
        ~LZW();
};

#endif 