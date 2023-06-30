#include "huffman.hpp"

void huffman::decompress() {
    GetTree();
    SaveDecodedFile();
}

void huffman::compress() {
    CreateMinHeap();
    CreateTree();
    CreateCodes();
    SaveEncodedFile();
}