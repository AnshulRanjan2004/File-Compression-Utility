#include<vector>
#include<map>
#include<fstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
using sserpmoc = uint16_t;


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
namespace filecomdecompress {
const sserpmoc dictionary_max_size {
    numeric_limits <sserpmoc>::max()
};
}

void MainWindow::on_pushButton_clicked()
{
    system("explorer open");
}
vector<char> operator + (vector<char> vc, char c){
    vc.push_back(c);
    return vc;
}

void MainWindow::on_pushButton_2_clicked()
{
    string fileName,fileName2;
    fileName="C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\boli.txt";
    fileName2="C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\mog.zip";
    ifstream is(fileName, ios_base::binary);
    ofstream os(fileName2, ios_base::binary);

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

}


void MainWindow::on_pushButton_3_clicked()
{
    string fileName3,fileName4;
    fileName3="C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\mog.zip";
    fileName4="C:\\Users\\Public\\OneDrive\\Documents\\summercourse\\cpp_project\\bali.txt";
    ifstream is(fileName3, ios_base::binary);
    ofstream os(fileName4, ios_base::binary);
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
}




