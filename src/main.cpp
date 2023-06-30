#include "../include/main.h"

int main(int argc, char* argv[]){
    if (argc < 3){
        cerr << USAGE_ERROR << endl;
        exit(EXIT_FAILURE);
    } else{
        LZW algoritmo(argv[FILENAME_POSITION]);
        string parameter = argv[PARAMETER_POSITION];
        if (parameter == COMPRESS_PARAMETER){
            algoritmo.compressor();
        } else if (parameter == DECOMPRESS_PARAMETER) {
            algoritmo.decompressor();
        } else{
            cerr << PARAMETER_ERROR << endl;
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}