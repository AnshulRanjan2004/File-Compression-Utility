#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

//Class for the basic Node of the Huffman Tree
class Node {
    public:
        char data;
        unsigned freq;
        string code;
        Node *left, *right;

        Node() {
            left = right = NULL;
        }
};

//Main class
class huffman {
    private:
        vector <Node*> characters;
        fstream source, destination;
        string SourceFileName, DestinationFileName;
        Node *root;
        
        class Compare {
            public:
                bool operator() (Node* l, Node* r)
                {
                    return l->freq > r->freq;
                }
        };

        priority_queue <Node*, vector<Node*>, Compare> minHeap;
        
        //Initializing a vector containing 128 tree nodes representing characters
        // with ascii value from 0 to 127 and initializing its frequency with 0
        void InitializeVector();
        
        //A recursive method for CreateCodes function to generate huffman codes of each present character
        void CreateCode(Node*, string);
        
        //To convert a binary string to its equivalent decimal value
        int BinToDec(string);
        
        //To convert a decimal number to its equivalent binary string
        string DecToBin(int);
        
        //To Reconstruct the Huffman tree while Decoding the file
        void GetTree();

        //To Create Min Heap of Nodes by frequency of characters in the input file
        void CreateMinHeap();
        
        //To create the Huffman tree
        void CreateTree();
        
        //To generate Huffman codes
        void CreateCodes();
        
        //To save the meta data and encoded text to the output file
        void SaveEncodedFile();
        
        //To retrieve and decode the encoded text to the output file
        void SaveDecodedFile();
        

    public:
        //Constructor
        huffman(string SourceFileName, string DestinationFileName)
        {
            this->SourceFileName = SourceFileName;
            this->DestinationFileName = DestinationFileName;
            InitializeVector();
        }
        //To compress input file
        void compress();
        //To decompress input file
        void decompress();
};

void huffman::InitializeVector() {
    for (int i = 0; i < 128; i++) {
        characters.push_back(new Node());
        characters[i]->data = i;
        characters[i]->freq = 0;
    }
}


int huffman::BinToDec(string inStr) {
    int res = 0;
    for (auto c : inStr) {
        res = res * 2 + c - '0';
    }
    return res;
}

string huffman::DecToBin(int inNum) {
    string temp = "", res = "";
    while (inNum > 0) {
        temp += (inNum % 2 + '0');
        inNum /= 2;
    }
    res.append(8 - temp.length(), '0');
    for (int i = temp.length() - 1; i >= 0; i--) {
        res += temp[i];
    }
    return res;
}

void huffman::CreateMinHeap() {
    char c;
    source.open(SourceFileName, ios::in);
    source.get(c);

    //Assiging frequency to characters
    while (!source.eof()) {
        characters[c]->freq++; //character "c" gets typecasted to its ascii value
        source.get(c);
    }
    source.close();

    //Adding characters that appear to the minimum heap
    for (int i = 0; i < 128; i++) {
        if (characters[i]->freq > 0) {
            minHeap.push(characters[i]);
        }
    }
}

void huffman::CreateTree() {
    Node *left, *right;
    priority_queue <Node*, vector<Node*>, Compare> min(minHeap);
    while (min.size() != 1)
    {
        left = min.top();
        min.pop();
            
        right = min.top();
        min.pop();
            
        root = new Node();
        root->freq = left->freq + right->freq;

        root->left = left;
        root->right = right;
        min.push(root);
    }
}

void huffman::CreateCode(Node* n, string str) {
    if (n->left == NULL && n->right == NULL) {
        n->code = str;
        return;
    }

    CreateCode(n->left, str + '0');
    CreateCode(n->right, str + '1');
}

void huffman::CreateCodes() {
    CreateCode(root, "");
}

void huffman::SaveEncodedFile() {
    source.open(SourceFileName, ios::in);
    destination.open(DestinationFileName, ios::out | ios::binary);
    string in = "";
    string s = "";
    char c;

    //Saving the meta data (huffman tree)
    in += (char)minHeap.size();
    priority_queue <Node*, vector<Node*>, Compare> min(minHeap);
    while (!min.empty()) {
        Node* curr = min.top();
        in += curr->data;
        //Saving 16 decimal values representing code of curr->data
        s.assign(127 - curr->code.length(), '0');
        s += '1';
        s += curr->code;
        //Saving decimal values of every 8-bit binary code 
        in += (char)BinToDec(s.substr(0, 8));
        for (int i = 0; i < 15; i++) {
            s = s.substr(8);
            in += (char)BinToDec(s.substr(0, 8));
        }
        min.pop();
    }
    s.clear();

    //Saving codes of every character appearing in the input file
    source.get(c);
    while (!source.eof()) {
        s += characters[c]->code;
        //Saving decimal values of every 8-bit binary code
        while (s.length() > 8) {
            in += (char)BinToDec(s.substr(0, 8));
            s = s.substr(8);
        }
        source.get(c);
    }

    //Finally if bits remaining are less than 8, append 0's
    int count = 8 - s.length();
	if (s.length() < 8) {
		s.append(count, '0');
	}
	in += (char)BinToDec(s);	
    //append count of appended 0's
    in += (char)count;

    //write the in string to the output file
	destination.write(in.c_str(), in.size());
	source.close();
	destination.close();
}

void huffman::GetTree() {
    source.open(SourceFileName, ios::in | ios::binary);
    //Reading size of MinHeap
    unsigned char size;
    source.read(reinterpret_cast<char*>(&size), 1);
    root = new Node();
    //next size * (1 + 16) characters contain (char)data and (string)code[in decimal]
    for(int i = 0; i < size; i++) {
        char aCode;
        unsigned char hCodeC[16];
        source.read(&aCode, 1);
        source.read(reinterpret_cast<char*>(hCodeC), 16);
        //converting decimal characters into their binary equivalent to obtain code
        string hCodeStr = "";
        for (int i = 0; i < 16; i++) {
            hCodeStr += DecToBin(hCodeC[i]);
        }
        //Removing padding by ignoring first (127 - curr->code.length()) '0's and next '1' character
        int j = 0;
        while (hCodeStr[j] == '0') {
            j++;
        }
        hCodeStr = hCodeStr.substr(j+1);
        //Adding node with aCode data and hCodeStr string to the huffman tree
        Node* curr = root;
        for (int i = 0; i < hCodeStr.length(); i++) {
            if (hCodeStr[i] == '0') {
                if (curr->left == NULL) {
                    curr->left = new Node();
                }
                curr = curr->left;
            }
            else if (hCodeStr[i] == '1') {
                if (curr->right == NULL) {
                    curr->right = new Node();
                }
                curr = curr->right;
            }
        }
        curr->data = aCode;
    }
    source.close();
}

void huffman::SaveDecodedFile() {
    source.open(SourceFileName, ios::in | ios::binary);
    destination.open(DestinationFileName, ios::out);
    unsigned char size;
    source.read(reinterpret_cast<char*>(&size), 1);
    //Reading count at the end of the file which is number of bits appended to make final value 8-bit
    source.seekg(-1, ios::end);
    char count0;
    source.read(&count0, 1);
    //Ignoring the meta data (huffman tree) (1 + 17 * size) and reading remaining file
    source.seekg(1 + 17 * size, ios::beg);

    vector<unsigned char> text;
    unsigned char textseg;
    source.read(reinterpret_cast<char*>(&textseg), 1);
    while (!source.eof()) {
        text.push_back(textseg);
        source.read(reinterpret_cast<char*>(&textseg), 1);
    }

    Node *curr = root;
    string path;
    for (int i = 0; i < text.size() - 1; i++) {
        //Converting decimal number to its equivalent 8-bit binary code
        path = DecToBin(text[i]);
        if (i == text.size() - 2) {
            path = path.substr(0, 8 - count0);
        }
        //Traversing huffman tree and appending resultant data to the file
        for (int j = 0; j < path.size(); j++) {
            if (path[j] == '0') {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }

            if (curr->left == NULL && curr->right == NULL) {
                destination.put(curr->data);
                curr = root;
            }
        }
    }
    source.close();
    destination.close();
}
