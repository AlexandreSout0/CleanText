#include <iostream>
#include <string>
#include "Includes.hpp"
#include <algorithm>
#include <filesystem>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fixed;
using std::left;
using std::right;
using std::ios;
using std::string;

//clang++ -std=c++17 main.cpp -o main
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string Amarelo = "\033[33m";
const std::string Azul = "\033[34m";
const std::string Roxo= "\033[35m";
const std::string reset = "\033[0m";
// std::cout << red << "Texto em vermelho!" << reset << std::endl;
// std::cout << green << "Texto em verde!" << reset << std::endl;



std::string chunckFile = "EXT2377894";
std::string cnpjOld = "07587384000130";
std::string cnpjNew = "12456606000115";
std::string dir = "./";
std::vector<std::string> listFoundFiles;
char aux;

std::vector<std::string> findFiles(std::string dir_, std::string chunckFile_);
void processFile(std::string fileName_, std::string cnpjOld_, std::string cnpjNew_);
int menu();
void notPage();
void index();

int main() {
    

    index(); 
    while(1)
    {

        menu();
        return 0;
    }


}  


std::vector<std::string> findFiles(std::string dir_, std::string chunckFile_){
    
    std::vector<std::string> listFiles;
    std::string chunckFileName = chunckFile_;
    std::string diretorio = dir_;

    if (!std::filesystem::exists(diretorio)) {
        std::cerr << red <<"Diretório não encontrado." << std::endl;
        std::cout << "Press any key and Enter to continue...";
        cin >> aux;
        menu();

    }

    for (const auto& file : std::filesystem::directory_iterator(diretorio)) { // Percorrer os arquivos no diretório

        std::string fileNameFull = file.path().filename().string();
        
        if (fileNameFull.find(chunckFileName) == 0) { // Verificar se o arquivo começa com o nome desejado
            listFiles.push_back(fileNameFull);
            //std::cout << "Arquivo encontrado: " << fileNameFull << std::endl;
        }
    }

    return listFiles;

}


void processFile(std::string fileName_, std::string cnpjOld_, std::string cnpjNew_)
{       

    //std::string inputFileName = fileName;
    //std::string outputFileName = fileName;
    ifstream inputFile(fileName_);
    ofstream outputFile("temp.txt");

    size_t pos = 0;
    string line;
    string termo = cnpjOld_;
    string cnpj  = cnpjNew_;

    int contador = 0;

    if (inputFile.is_open() && outputFile.is_open()) {
        while (getline(inputFile, line)) {
            while ((pos = line.find(termo, pos + cnpj.length())) != std::string::npos){
                line.replace(pos, termo.length(), cnpj);
                pos += cnpj.length();
            }
            
            outputFile << line << endl;
        }

        cout << fileName_ + " Ok!\n";
    }else{
        cout << fileName_ + " Error File\n";
    }

    inputFile.close();
    outputFile.close();

    if (std::remove(fileName_.c_str()) != 0) {
        std::cout << "Não foi possível remover o arquivo original." << std::endl;
    }
    if (std::rename("temp.txt", fileName_.c_str()) != 0) {
        std::cout << "Não foi possível renomear o arquivo temporário." << std::endl;
    }


}


void index(){

     std::cout << red << R"(
             ___       __      ___   ___ 
            /   \     |  |     \  \ /  / 
           /  ^  \    |  |      \  V  / 
          /  /_\  \   |  |       >   <  
         /  _____  \  |  `----. /  .  \    
        /__/     \__\ |_______|/__/ \__\  
                                                                        
    )" << reset << std::endl;

}

int menu(){

    std::cout << "\033[2J\033[1;1H";
    index();
    char choice;

    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "|             File Text Editor               |" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "|" << std::setw(3) << " 1 - Path Files" << std::setw(30)    << "|" << std::endl;
    std::cout << "|" << std::setw(3) << " 2 - CNPJ remove" << std::setw(29)   << "|" << std::endl;
    std::cout << "|" << std::setw(3) << " 3 - CNPJ New" << std::setw(32)      << "|" << std::endl;
    std::cout << "|" << std::setw(3) << " 4 - Chunk File" << std::setw(30)    << "|" << std::endl;
    std::cout << "|" << std::setw(3) << " 5 - Processing" << std::setw(30)    << "|" << std::endl;
    std::cout << "|" << std::setw(3) << " 6 - Quit" << std::setw(36)          << "|" << std::endl;
    std::cout << "+--------------------------------------------+" << std::endl;
    std::cout << "-> " << green;
    cin >> choice;

    switch (choice) {
        case '1':
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Defaut Path: ";
            std::cout << green << dir << reset << std::endl;
            std::cout << "Type a new Path: " << red;
            cin >> dir;
            menu();
            break;

        case '2':
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Defaut CNPJ remove: ";
            std::cout << green << cnpjOld << reset << std::endl;
            std::cout << "Type a new CNPJ remove: " << red; 
            cin >> cnpjOld;
            menu();
            break;

        case '3':
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Defaut new CNPJ: ";
            std::cout << green << cnpjNew << reset << std::endl;
            std::cout << "Type a new CNPJ: " << red;
            cin >> cnpjNew;
            menu();

            break;

        case '4':
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Chunk File: ";
            std::cout << green << chunckFile << reset << std::endl;
            std::cout << "Type a new Chunk File: " << red;
            cin >> chunckFile;

            menu();

            break;
        
        case '5':

            std::cout << "\033[2J\033[1;1H";
            listFoundFiles = findFiles(dir, chunckFile);
            
            for (const auto& nameFile : listFoundFiles) {
                processFile(nameFile, cnpjOld, cnpjNew);
                std::cout << "Arquivo -> " << nameFile << std::endl;
            }
            std::cout << "Press any key and Enter to continue..." << red;
            cin >> aux;
            menu();

            break;

        case '6':
            
            std::cout << red << "Saindo da aplicação..." << std::endl;
            return 0;

        default:
            std::cout << "\033[2J\033[1;1H";
            notPage ();
            std::cout << "Press any key and Enter to continue..." << red;
            cin >> aux;
            menu();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}


void notPage (){

    std::cout << R"(
        \       What a maze!        /
         \                         /
          \    This page does     /
           ]     not exist.      [    ,'|
           ]                     [   /  |
           ]___               ___[ ,'   |
           ]  ]\             /[  [ |:   |
           ]  ] \           / [  [ |:   |
           ]  ]  ]         [  [  [ |:   |
           ]  ]  ]__     __[  [  [ |:   |
           ]  ]  ] ]\ _ /[ [  [  [ |:   |
           ]  ]  ] ] (#) [ [  [  [ :===='
           ]  ]  ]_].nHn.[_[  [  [
           ]  ]  ]  HHHHH. [  [  [
           ]  ] /   `HH("N  \ [  [
           ]__]/     HHH  "  \[__[
           ]         NNN         [
           ]         N/"         [
           ]         N H         [
          /          N            \
         /           q,            \
        /                           \
    )" << std::endl;


}




    






