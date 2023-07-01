#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <limits>
#include <ctime>
#include <exception>


using namespace std;
using sserpmoc = uint16_t;
void displayMenu();

namespace filecomdecompress {
	const sserpmoc dictionary_max_size {
		numeric_limits <sserpmoc>::max()
	};
}
	
vector<char> operator + (vector<char> vc, char c){
    vc.push_back(c);
    return vc;
}

// Compression Function.
void compress()
{
    //input file name 
    string input_file, output_file, fileEx, fileExtension;
    cout << "Enter the path of the file to be compressed: ";
    cin >> input_file;
    //check for input file conditions
    fileEx = input_file.substr(input_file.find_last_of(".") + 1);
    ifstream is(input_file, ios_base::binary);
    if (fileEx == "zip")
        throw runtime_error("File already compressed");
    if (!is || input_file == output_file)
        throw runtime_error("cannot open input file");

    //output file name
    cout << "Enter the name of the compressed file: ";
    cin >> output_file;
    //check for output file conditions
    fileExtension = output_file.substr(output_file.find_last_of(".") + 1);
    if (fileExtension != "zip")
        throw runtime_error("invalid output file extension");
    ofstream os(output_file, ios_base::binary);
    if (!os)
        throw runtime_error("cannot open output file");

    map<vector<char>, sserpmoc> dictionary;

    // lambda function, used to reset the dictionary to its initial contents
    const auto dict_reset = [&dictionary] {
        dictionary.clear();

        const long int minc = numeric_limits<char>::min();
        const long int maxc = numeric_limits<char>::max();

        for (long int c = minc; c <= maxc; ++c)
        {
            const sserpmoc dictionary_size = dictionary.size();

            dictionary[{static_cast<char> (c)}] = dictionary_size;
        }
    };

        dict_reset();

    vector<char> s;
    char c;

    while (is.get(c))
    {
        if (dictionary.size() == filecomdecompress::dictionary_max_size)
            dict_reset();

        s.push_back(c);

        if (dictionary.count(s) == 0)
        {
            const sserpmoc dictionary_size = dictionary.size();

            dictionary[s] = dictionary_size;
            s.pop_back();
            os.write(reinterpret_cast<const char *> (&dictionary.at(s)), sizeof (sserpmoc));
            s = {c};
        }
    }
    if (!s.empty())
        os.write(reinterpret_cast<const char *> (&dictionary.at(s)), sizeof (sserpmoc));
    
    //compression ratio and execution time
    cout << "Compression ratio: " << (float)output_file.length() / input_file.length() << endl;
    cout << "Execution time: " << (float)clock() / CLOCKS_PER_SEC << endl;

    os.close();
    is.close();

    cout << "Compression Successful!" <<endl;
    cout << endl;
    displayMenu();
}

// Decompression Function
void decompress()
{
    //input file name
    string input_file, output_file, fileExtension1;
    cout << "Enter the path of the compressed file: ";
    cin >> input_file;
    //check for input file conditions
    fileExtension1 = input_file.substr(input_file.find_last_of(".") + 1);
    if (fileExtension1 != "zip")
        throw runtime_error("invalid input file extension");
    ifstream is(input_file, ios::binary);
    if (!is)
        throw runtime_error("cannot open input file");

    //output file name
    cout << "Enter the name of the decompressed file: ";
    cin >> output_file;
    //check for output file conditions
    ofstream os(output_file, ios::binary);
    if (!os)
        throw runtime_error("cannot open output file");

    vector<vector<char> > dictionary;
    const auto dict_reset = [&dictionary] {
        dictionary.clear();
        dictionary.reserve(filecomdecompress::dictionary_max_size);

        const long int minc = numeric_limits<char>::min();
        const long int maxc = numeric_limits<char>::max();

        for (long int c = minc; c <= maxc; ++c)
            dictionary.push_back({static_cast<char> (c)});
    };

        dict_reset();

    vector<char> s;
    sserpmoc k;

    while (is.read(reinterpret_cast<char *> (&k), sizeof (sserpmoc)))
    {
        if (dictionary.size() == filecomdecompress::dictionary_max_size)
            dict_reset();

        if (k > dictionary.size())
            throw runtime_error("invalid compressed code");

        if (k == dictionary.size())
            dictionary.push_back(s + s.front());
        else
        if (!s.empty())
            dictionary.push_back(s + dictionary.at(k).front());

        os.write(&dictionary.at(k).front(), dictionary.at(k).size());
        s = dictionary.at(k);
    }
    if (!is.eof() || is.gcount() != 0)    
        throw runtime_error("corrupted compressed file");

    //compression ratio and execution time
    cout << "Compression ratio: " << (float)output_file.length() / input_file.length() << endl;
    cout << "Execution time: " << (float)clock() / CLOCKS_PER_SEC << endl;
    os.close();
    is.close();

    cout << "Decompression Successful!" <<endl;
    cout << endl;
    displayMenu();
}

// return EXIT_FAILURE    failed
// return EXIT_SUCCESS    success
int main()
{
    displayMenu();
    return EXIT_SUCCESS;
}

void displayMenu()
{
    int choice;
    cout << "File Compression Utility" << endl;
    cout << "------------------------" << endl;
    cout << "1. Compress a file" << endl;
    cout << "2. Decompress a file" << endl;
    cout << "3. Exit the program" << endl;
    cout << "------------------------" << endl;
    cout << "Usage:" << endl;
    cout << "Enter choice " <<endl;
    cout << "After entering choice, enter path of input file" <<endl;
    cout << "Then, enter the path of the output file" <<endl;
    cout << "------------------------" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        compress();
        break;
    case 2:
        decompress();
        break;
    case 3:
        cout << "Exiting..." << endl;
        exit(0);
        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }
}