#include "huffman.hpp"

void huffman::compress() {
    CreateMinHeap();
    CreateTree();
    CreateCodes();
    SaveEncodedFile();
}