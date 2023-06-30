#include "headers/HuffmanUtility.hpp"

int main(){
    do{
    int choice;
    cout<<"Enter 1 for Compressing a file"<<endl;
    cout<<"Enter 2 for Decompressing a file"<<endl;
    cout<<"Enter 3 for Exiting"<<endl;
    cin>>choice;
    if(choice==1){
        cout<<"Enter the file path to be compressed"<<endl;
        string path;
        cin>>path;
        cout<<"Enter the file path to be saved"<<endl;
        string save_path;
        cin>>save_path;
        clock_t tStart = clock();
        huffman f(path, save_path);
        f.compress();
        cout << "Compressed Successfully to file " << save_path << endl;
        cout <<"Time taken: "<<(1.0*(clock() - tStart)/CLOCKS_PER_SEC)<<" sec"<<endl;
        ifstream f1(path, ios::binary | ios::ate); 
        ifstream f2(save_path, ios::binary | ios::ate);
        int before = f1.tellg();
        cout << "Before: " << before << " Bytes"<< endl;
        int after = f2.tellg();
        cout << "After: " << after <<" Bytes"<< endl;
        double compression_ratio = (double)before / after;
        cout << "Compression Ratio: " << compression_ratio << endl;
    }
    else if(choice==2){
        cout<<"Enter the file path to be decompressed"<<endl;
        string path;
        cin>>path;
        cout<<"Enter the file path to be saved"<<endl;
        string save_path;
        cin>>save_path;
        clock_t tStart = clock();
        huffman f(path, save_path);
        f.decompress();
        cout << "Decompressed Successfully to file " << save_path << endl;
        cout <<"Time taken: "<<(1.0*(clock() - tStart)/CLOCKS_PER_SEC)<<" sec"<<endl;
        ifstream f1(path, ios::binary | ios::ate);
        ifstream f2(save_path, ios::binary | ios::ate);
        int before = f1.tellg();
        cout << "Before: " << before << " Bytes"<< endl;
        int after = f2.tellg();
        cout << "After: " << after <<" Bytes"<< endl;
        double compression_ratio = (double)after / before;
        cout << "Compression Ratio: " << compression_ratio << endl;
    }
    else if(choice==3){
        exit(0);
    }
    else{
        cout<<"Invalid choice"<<endl;
    }
    }while(1);
    return 0;
}