#include "headers/HuffmanUtility.hpp"

int main(){
    //give a menu option 1 for compress , 2 for decompress and 3 for exit
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
        huffman f(path, save_path);
        f.compress();
        cout << "Compressed Successfully to file " << save_path << endl;
    }
    else if(choice==2){
        cout<<"Enter the file path to be decompressed"<<endl;
        string path;
        cin>>path;
        cout<<"Enter the file path to be saved"<<endl;
        string save_path;
        cin>>save_path;
        huffman f(path, save_path);
        f.decompress();
        cout << "Decompressed Successfully to file " << save_path << endl;
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