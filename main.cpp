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
#include <ctime>
using namespace std;



int main(int argc, char* argv[])
{
    
    clock_t clock;
    double duration;
    clock = std::clock();
    
    
  /*  if (argc < 2)
        cout << "Format: BTree input=input1.txt output=output1.txt command=command1.txt" << endl;
    
    ArgumentManager am(argc, argv);
    std::string infilename = am.get("input");
    std::string outfilename = am.get("output");
    std::string commandsfile = am.get("command");
    */

    string inputfile, outputfile;


    //open the inpu˘ file & output file
    ifstream fin;
    fin.open(inputfile);
    ofstream fout;
    fout.open(outputfile);
    
    if (!fin.is_open())
    {
        cout << "Unable to open input file" << endl;
        return 0;
    }
    if (!fout.is_open())
    {
        cout << "Unable to open output file" << endl;
        return 0;
    }


    
    cout << "thdsiuogh";
    
    
}   //  end main




































