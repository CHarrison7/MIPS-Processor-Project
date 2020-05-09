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
#include <sstream>
using namespace std;

string parseLine(string line)
{
    stringstream iss(line);
    string parsedLine;
    while(getline(iss, line, '\r')) // ditch the return character on the end
    {
        parsedLine += line;
        //cout << parsedLine << endl;
    }
    return parsedLine;
}



int main(int argc, char* argv[])
{
    int repeat = 1;
    while(repeat){
    
        string inputFilePath, outputFilePath;
        //inputFilePath = "/Users/caleb/Development/MIPS-Processor-Project/MIPS-Processor-Project/input.txt";
        //outputfile = "/Users/caleb/Development/MIPS-Processor-Project/MIPS-Processor-Project/output.txt";

    
    cout << "Please type the input file pathname exactly: " << endl;
    cin >> inputFilePath;
    cout << endl << inputFilePath << endl;
        
        cout << "Please type the output file pathname exactly: " << endl;
        cin >> outputFilePath;
        cout << endl << outputFilePath << endl;
        
        
        
    //open the input file & output file
    ifstream fin;
    fin.open(inputFilePath);
    ofstream fout;
    fout.open(outputFilePath);
    
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
    int memoryCells[249] = {0};
        int C = 0;
        int I = 0;
        
    
    string buffer, keyword;
    while(!fin.eof())
    {
        getline(fin, buffer);
        
        //if blank line, skip
        if(buffer == "")
            continue;

        //call parseLine function
        string parsedLine = parseLine(buffer);
        
        bool didKeywordChange = false;
        if(parsedLine == "REGISTERS")
        {
            keyword = "REGISTERS";
            didKeywordChange = true;
        }
        else if (parsedLine == "MEMORY")
        {
            keyword = "MEMORY";
            didKeywordChange = true;
        }
        else if (parsedLine == "CODE")
        {
            keyword = "CODE";
            didKeywordChange = true;
        }
        
        if(keyword == "REGISTERS" && didKeywordChange == false)
        {
            // "R1 16"
            int regNum = stoi(parsedLine.substr(1,1));
            registerContents[regNum] = stoi(parsedLine.substr(3,4));
        }
        else if(keyword == "MEMORY" && didKeywordChange == false)
        {
            string x, y;
            stringstream iss(parsedLine);
            getline(iss, x, ' ');
            getline(iss, y, '\r');

            int memAddress = stoi(x)/4;
            int memContent = stoi(y);
            
            memoryCells[memAddress] = memContent;
        }
        else if(keyword == "CODE"  && didKeywordChange == false)
        {
            C++;    // increment cycle number (sets to 1 on first round)
            I++;    // increment instuction number (1 for the first round/line)
            fout << "C#" + to_string(C) + " I" + to_string(I) + "-IF" << endl;  // instruction fetch
            string binInstrucLine, opcode;
            stringstream iss(parsedLine);
            getline(iss, binInstrucLine, '\r');
            
            opcode = binInstrucLine.substr(0,6);
            
            if(opcode == "100011")     // LW instruction
            {
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-ID" << endl;  // instruction decode
                int rs, rt, imm;
                rs = stoi(binInstrucLine.substr(6, 5), 0, 2);
                rt = stoi(binInstrucLine.substr(11, 5), 0, 2);
                imm = stoi(binInstrucLine.substr(16, 16), 0, 2);        //  implement
                
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                registerContents[rt] = memoryCells[rs];  // Reg[rt] = Mem[rs]
                
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-MEM" << endl;
                
                
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-WB" << endl;
            }
            else if(opcode == "101011")     // SW instruction
            {
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-ID" << endl;  // instruction decode
                int rs, rt, imm;
                rs = stoi(binInstrucLine.substr(6, 5), 0, 2);
                rt = stoi(binInstrucLine.substr(11, 5), 0, 2);
                imm = stoi(binInstrucLine.substr(16, 16), 0, 2);        //  implement
                
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                
                memoryCells[rt] = registerContents[rs];  // Mem[rt] = Reg[rs]
                
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-MEM" << endl;
            }
            else if(opcode == "000000")     // R-Type instruction
            {
                C++;
                fout << "C#" + to_string(C) + " I" + to_string(I) + "-ID" << endl;  // instruction decode
                int rs, rt, rd;
                string sa, func;
                rs = stoi(binInstrucLine.substr(6, 5), 0, 2);
                rt = stoi(binInstrucLine.substr(11, 5), 0, 2);
                rd = stoi(binInstrucLine.substr(16, 5), 0, 2);
                sa = binInstrucLine.substr(21, 5);
                func = binInstrucLine.substr(26, 6);
                //imm = stoi(binInstrucLine.substr(16, 16), 0, 2);        //  implement
                /*string q,w,e,r, t;
                q = binInstrucLine.substr(6, 5);
                w = binInstrucLine.substr(11, 5);
                e = binInstrucLine.substr(16, 5);
                r = binInstrucLine.substr(21, 5);
                t = binInstrucLine.substr(26, 6);*/
                
                if(func == "100000")        //  ADD function
                {
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                    registerContents[rd] = registerContents[rs] + registerContents[rt];
                    
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-WB" << endl;
                }
                else if(func == "100010")   //  SUB function
                {
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                    registerContents[rd] = registerContents[rs] - registerContents[rt];
                    
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-WB" << endl;
                }
                else if(func == "101010")   // SLT
                {
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                    if(registerContents[rs] < registerContents[rt])
                    {
                        registerContents[rd] = 1;
                    }
                    else
                    {
                        registerContents[rt] = 0;
                    }
                }
                else if(opcode == "001000")    //  opcode for I-type ADDI
                {
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-ID" << endl;  // instruction decode
                    int rs, rt, imm;
                    rs = stoi(binInstrucLine.substr(6, 5), 0, 2);
                    rt = stoi(binInstrucLine.substr(11, 5), 0, 2);
                    imm = stoi(binInstrucLine.substr(16, 16), 0, 2);
                    
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                    registerContents[rd] = registerContents[rs] + imm;
                    
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-WB" << endl;
                }
                else if(opcode == "000100")     //  BEQ I-type instruction
                {
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-ID" << endl;  // instruction decode
                    int rs, rt, imm;
                    rs = stoi(binInstrucLine.substr(6, 5), 0, 2);
                    rt = stoi(binInstrucLine.substr(11, 5), 0, 2);
                    imm = stoi(binInstrucLine.substr(16, 16), 0, 2);
                    
                    //  BEQ EXECUTION
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                }
                else if(opcode == "000101")     //  BNE I-type instruction
                {
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-ID" << endl;  // instruction decode
                    int rs, rt, imm;
                    rs = stoi(binInstrucLine.substr(6, 5), 0, 2);
                    rt = stoi(binInstrucLine.substr(11, 5), 0, 2);
                    imm = stoi(binInstrucLine.substr(16, 16), 0, 2);
                    
                    //  BNE EXECUTION
                    C++;
                    fout << "C#" + to_string(C) + " I" + to_string(I) + "-EX" << endl;
                }
            }
        }
        didKeywordChange = false;
    }
    
    
        fout << "REGISTERS" << endl;
    for(int i = 0; i < 32; i++)
    {
        if(registerContents[i] == 0)
            continue;
        fout << "R" + to_string(i) + " ";
        fout << registerContents[i] << endl;
    }
    
        fout << endl;
        
        fout << "MEMORY" << endl;
    for(int i = 0; i < 249; i++)
    {
        if(memoryCells[i] == 0)
            continue;
        fout << to_string(i) + " ";
        fout << memoryCells[i] << endl;
            
    }
    
        cout << "Would you like to repeat? Enter '1' for YES, '0' for NO: " << endl;
        cin >> repeat;
        
    cout << endl << endl;
    }
}   //  end main




































