//
//  main.cpp
//  MIPS Processor Project
//
//  Created by Caleb Harrison on 4/21/20.
//  Copyright © 2020 Caleb Harrison. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;




int main(int argc, char* argv[])
{
    
    string inputFilePath;
    string outputfile = "output.txt";

    cout << "Please type the input file pathname exactly: " << endl;
    cin >> inputFilePath;
    cout << endl << inputFilePath << endl;
    
    
    //open the input file & output file
    ifstream fin;
    fin.open(inputFilePath);
    ofstream fout;
    fout.open(outputfile);
    
    if (!fin)
    {
        cout << "Unable to open input file" << endl;
        return 0;
    }
    if (!fout.is_open())
    {
        cout << "Unable to open output file" << endl;
        return 0;
    }

    int registerContents[32] = {0};
    
    
    
    
    
    cout << endl << endl;
}   //  end main




































