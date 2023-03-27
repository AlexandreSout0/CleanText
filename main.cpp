#include "Includes.hpp"
#include <algorithm>


int main() {

    


    string inputFileName = text_ctrl.GetValue()
    string outputFileName = "1177_clean1.txt";
    string outputFileName2 = "1177_clean2.txt";

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
                if (contador > 25000)
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
    return 0;
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