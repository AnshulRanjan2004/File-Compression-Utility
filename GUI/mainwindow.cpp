#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include<ctime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

using namespace std;
string a;
string destinationFileStr;
QString destinationFilePath;
QString qDestinationFilePath;
string dest;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class Node {
public:
    char data;
    unsigned freq;
    string code;
    Node* left, * right;


    Node() {
        left = right = NULL;
    }
};

class huffman {
private:
    vector<Node*> characters;
    fstream source, destination;
    string SourceFileName, DestinationFileName;
    Node* root;

    class Compare {
    public:
        bool operator()(Node* l, Node* r)
        {
            return l->freq > r->freq;
        }
    };


    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    void InitializeVector();
    void CreateCode(Node*, string);
    int BinToDec(string);
    string DecToBin(int);
    void GetTree();
    void CreateMinHeap();
    void CreateTree();
    void CreateCodes();
    void SaveEncodedFile();
    void SaveDecodedFile();

public:

    huffman(const string& SourceFileName, const string& DestinationFileName)
    {
        this->SourceFileName = SourceFileName;
        this->DestinationFileName = DestinationFileName;
        InitializeVector();
    }

    void compress();
    void decompress();
};

void huffman::compress() {
    CreateMinHeap();
    CreateTree();
    CreateCodes();
    SaveEncodedFile();
}

void huffman::decompress() {
    GetTree();
    SaveDecodedFile();
}

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

    while (!source.eof()) {
        characters[c]->freq++;
        source.get(c);
    }

    source.close();

    for (int i = 0; i < 128; i++) {
        if (characters[i]->freq > 0) {
            minHeap.push(characters[i]);
        }
    }
}

void huffman::CreateTree() {
    Node* left, * right;
    priority_queue<Node*, vector<Node*>, Compare> min(minHeap);
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

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C://Users//Public//OneDrive//Documents//summercourse//cpp_project",
        "All files (*.*);;Text File (*.txt);;Music file(*.mp3)"
        );
    QMessageBox::information(this, tr("File Name"), filename);
    a = filename.toStdString();
    cout << "This is the path of the file you chose:" << a << endl;
}

void MainWindow::on_pushButton_2_clicked()
{
    huffman huff(a, "C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\ram.zip");
    huff.compress();
    dest = "C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\ram.zip";
    cout << "File compressed successfully!" << endl;
}

void huffman::SaveEncodedFile() {
    source.open(SourceFileName, ios::in);
    destination.open(DestinationFileName, ios::out | ios::binary);
    string in = "";
    string s = "";
    char c;

    in += (char)minHeap.size();
    priority_queue<Node*, vector<Node*>, Compare> min(minHeap);
    while (!min.empty()) {
        Node* curr = min.top();
        in += curr->data;
        s.assign(127 - curr->code.length(), '0');
        s += '1';
        s += curr->code;
        in += (char)BinToDec(s.substr(0, 8));
        for (int i = 0; i < 15; i++) {
            s = s.substr(8);
            in += (char)BinToDec(s.substr(0, 8));
        }
        min.pop();
    }
    s.clear();

    source.get(c);
    while (!source.eof()) {
        s += characters[c]->code;
        while (s.length() > 8) {
            in += (char)BinToDec(s.substr(0, 8));
            s = s.substr(8);
        }
        source.get(c);
    }

    int count = 8 - s.length();
    if (s.length() < 8) {
        s.append(count, '0');
    }
    in += (char)BinToDec(s);
    in += (char)count;

    destination.write(in.c_str(), in.size());
    source.close();
    destination.close();
}

void huffman::GetTree() {
    source.open(SourceFileName, ios::in | ios::binary);
    unsigned char size;
    source.read(reinterpret_cast<char*>(&size), 1);
    root = new Node();
    for (int i = 0; i < size; i++) {
        char aCode;
        unsigned char hCodeC[16];
        source.read(&aCode, 1);
        source.read(reinterpret_cast<char*>(hCodeC), 16);
        string hCodeStr = "";
        for (int i = 0; i < 16; i++) {
            hCodeStr += DecToBin(hCodeC[i]);
        }
        int j = 0;
        while (hCodeStr[j] == '0') {
            j++;
        }
        hCodeStr = hCodeStr.substr(j + 1);
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

void MainWindow::on_pushButton_4_clicked()
{
    destinationFilePath = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),
        "C://Users//Public//OneDrive//Documents//summercourse//cpp_project",
        tr("All files (*.*)")
        );

    destinationFileStr = destinationFilePath.toStdString();
    cout << "This is the new file path:" << destinationFileStr << endl;


}

void MainWindow::on_pushButton_3_clicked()
{
    huffman huff("C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\ram.zip", destinationFileStr);
    huff.decompress();
    cout << "DeCompressed Successfully to file" << endl;
    cout <<"Time taken: "<<(float)clock() / CLOCKS_PER_SEC << endl;
    ifstream f1(a, ios::binary | ios::ate);
    ifstream f2(dest, ios::binary | ios::ate);
    int before = f1.tellg();
    cout << "Before: " << before << " Bytes"<< endl;
    int after = f2.tellg();
    cout << "After: " << after <<" Bytes"<< endl;
    double compression_ratio = (double)before / after;
    cout << "Compression Ratio: " << compression_ratio << endl;
}

void huffman::SaveDecodedFile() {
    source.open(SourceFileName, ios::in | ios::binary);
    destination.open(DestinationFileName, ios::out);
    unsigned char size;
    source.read(reinterpret_cast<char*>(&size), 1);
    source.seekg(-1, ios::end);
    char count0;
    source.read(&count0, 1);
    source.seekg(1 + 17 * size, ios::beg);

    vector<unsigned char> text;
    unsigned char textseg;
    source.read(reinterpret_cast<char*>(&textseg), 1);
    while (!source.eof()) {
        text.push_back(textseg);
        source.read(reinterpret_cast<char*>(&textseg), 1);
    }

    Node* curr = root;
    string path;
    for (int i = 0; i < text.size() - 1; i++) {
        path = DecToBin(text[i]);
        if (i == text.size() - 2) {
            path = path.substr(0, 8 - count0);
        }
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


void MainWindow::on_pushButton_5_clicked()
{
    QString qDestinationFilePath = QString::fromStdString(destinationFileStr);
    QDesktopServices::openUrl(QUrl::fromLocalFile(qDestinationFilePath));
}



void MainWindow::on_pushButton_6_clicked()
{
    system("explorer C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\File-Compression-Utility\\classdiagram.jpg");
}

