#include "Includes.hpp"
#include <algorithm>

void Processamento(string nameIn_, string nameOut1_, string nameOut2_ , int numeroLinhas_);

int main() {

    
    while(1)
    {
        string nameIn, nameOut1, nameOut2;
    int numeroLinhas;
        cout << "Digite o nome do arquivo de o entrada Ex.[nomeArquivo.txt].\n";
        cin >> nameIn;
        cout << "Digite o nome do arquivo de saida Ex.[nomeArquivo.txt].\n";
        cin >> nameOut1;
        nameOut2 = nameOut2 + "_2.txt";

        cout << "Numero de linhas por arquivo:";
        cin >> numeroLinhas;

        Processamento(nameIn,nameOut1,nameOut2,numeroLinhas);

        return 0;
    }


}

void Processamento(string nameIn_, string nameOut1_, string nameOut2_,int numeroLinhas_)
{

    string inputFileName = nameIn_;
    string outputFileName = nameOut1_;
    string outputFileName2 = nameOut2_;

    ifstream inputFile(inputFileName);
        ofstream outputFile(outputFileName);
        ofstream outputFile2(outputFileName2);

        size_t pos = 0;
        string line;
        string delimiter = "GPS:";
        string delimiter2 = ": ";
        int contador = 0;

        if (inputFile.is_open() && outputFile.is_open()) {
            while (getline(inputFile, line)) {
                if (line.find(delimiter) != string::npos) {
                    contador++;
                    while ((pos = line.find(delimiter2)) != string::npos)
                    {
                        line.erase(0, pos + delimiter2.length());
                        line = line;
                    }

                    if (contador > numeroLinhas_)
                    {
                        outputFile2 << line << endl;
                    }
                    else 
                    {
                        outputFile << line << endl;
                    }
                    
                }    
            }
            inputFile.close();
            outputFile2.close();

            cout << "Deu bom!\n";
        } else {
            cout << "Pau pra abrir essa porra.\n";
        }


}






/*

    while(getline(File,line))
    {
        while ((pos = line.find(delimiter)) != string::npos)
        {
            posicaoVetor++;
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());

        }

    }



*/