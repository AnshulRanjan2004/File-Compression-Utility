#include "../include/LZW.h" 


LZW::LZW(string filename)
{
    nome_arquivo_original = filename;
    int posicao = nome_arquivo_original.find(DOT);
    nome_arquivo_modificado = nome_arquivo_original.substr(0, posicao);
}

void LZW::compressor()
{
    ifstream arquivo(nome_arquivo_original);
    InputSymbol arquivo_original(arquivo);
    nome_arquivo_modificado = nome_arquivo_modificado + DOT + EXTENSION;
    ofstream arquivo_compactado(nome_arquivo_modificado);
    OutputSymbol arquivo_modificado(arquivo_compactado, tamanho_maximo);

    int size = (tamanho_maximo * 11) / 10;
    unordered_map<string, unsigned int> simbolos(size);
    for (unsigned int i = 0; i < ALPHABET_SIZE; i++)
        simbolos[string(1, i)] = i;
    string simbolo_atual = "";
    char caracter;
    unsigned int proximo_codigo = ALPHABET_SIZE + 1;

    while( arquivo_original >> caracter){
        simbolo_atual += caracter;
        if(simbolos.find(simbolo_atual) == simbolos.end()){
            if(proximo_codigo <= tamanho_maximo){
                simbolos [simbolo_atual] = proximo_codigo++;
            }
            simbolo_atual.erase(simbolo_atual.size()-1);
            arquivo_modificado << simbolos[simbolo_atual];
            simbolo_atual = caracter; 
        }
    }
    if( simbolo_atual.size()){
        arquivo_modificado << simbolos[simbolo_atual];
    }
}

void LZW::decompressor()
{
    if (!is_compacted_type()) 
        return;
  
    ifstream arquivo(nome_arquivo_original);
    InputStream arquivo_compactado(arquivo, tamanho_maximo);    
    
    ofstream arquivo_final(nome_arquivo_modificado);
    OutputStream arquivo_descompactado(arquivo_final);
    
    int size = (tamanho_maximo * 11) / 10;
    unordered_map<unsigned int, string> simbolos(size);
    
    for (unsigned int i = 0; i < ALPHABET_SIZE; i++)
        simbolos[i] = string(1, i);
    
    string simbolo_anterior;
    unsigned int codigo;
    unsigned int proximo_codigo = ALPHABET_SIZE + 1;
    while(arquivo_compactado >> codigo)
    {
        /**
         * Caso em que o código do simbolo descoberto não está no dicionário
         **/
        if(simbolos.find(codigo) == simbolos.end())
            simbolos[codigo] = simbolo_anterior + simbolo_anterior[0];
        
        arquivo_descompactado << simbolos[codigo];
        
        /**
         * Caso em que o código do simbolo descoberto esteja muito a frente no dicionário
         **/
        if (simbolo_anterior.size() && proximo_codigo <= tamanho_maximo)
            simbolos[proximo_codigo++] = simbolo_anterior + simbolos[codigo][0];
        simbolo_anterior = simbolos[codigo];
    }
}

bool LZW::is_compacted_type()
{
    int posicao = nome_arquivo_original.find(DOT);
    nome_arquivo_modificado = nome_arquivo_original.substr(0, posicao);
    string extensao = nome_arquivo_original.substr(posicao + 1);
    if (extensao != EXTENSION)
    {
        cerr << EXTENSION_ERROR;
        exit(EXIT_FAILURE);
    }
    return true;
}

LZW::~LZW(){}
