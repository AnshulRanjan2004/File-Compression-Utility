#include "headers/decoding.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Error in detecting files, use the following format:" <<endl
        <<"compiled_file.exe source_file destination_file"<<endl;
		exit(1);
	}

    huffman f(argv[1], argv[2]);
    f.decompress();
    cout << "Decompressed Successfully to file " << argv[2] << endl;

    return 0;
}