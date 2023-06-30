#include "huffman.hpp"

void huffman::decompress() {
    GetTree();
    SaveDecodedFile();
}