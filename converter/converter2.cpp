#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;


string HexToBinary(string hexas)
{
    string binary;
    map<char, string> kon = {
    {'0',"0000"},
    {'1',"0001"},
    {'2',"0010"},
    {'3',"0011"},
    {'4',"0100"},
    {'5',"0101"},
    {'6',"0110"},
    {'7',"0111"},
    {'8',"1000"},
    {'9',"1001"},
    {'A',"1010"},
    {'B',"1011"},
    {'C',"1100"},
    {'D',"1101"},
    {'E',"1110"},
    {'F',"1111"}
    };
    for (int i = 0; i < hexas.length(); i++)
    {
        binary.append(kon[hexas[i]]);
    }
    return binary;
}

string UniBinaryToUtfBinary(int sk, string binary)
{
    /*string utf_binary;
    utf_binary.append("1110");
    utf_binary.append(binary.substr(0, 4));
    utf_binary.append("10");
    utf_binary.append(binary.substr(4, 6));
    utf_binary.append("10");
    utf_binary.append(binary.substr(10, 6));
    return utf_binary;*/
    string utf_binary;
    if (sk < 128)
    {
        utf_binary.append("0");
        utf_binary.append(binary.substr(9, 7));
    }
    else if (sk < 2048)
    {
        utf_binary.append("110");
        utf_binary.append(binary.substr(5, 5));
        utf_binary.append("10");
        utf_binary.append(binary.substr(10, 6));
    }
    else if (sk < 65536)
    {
        utf_binary.append("1110");
        utf_binary.append(binary.substr(0, 4));
        utf_binary.append("10");
        utf_binary.append(binary.substr(4, 6));
        utf_binary.append("10");
        utf_binary.append(binary.substr(10, 6));
    }
    else {
        utf_binary.append("11110");
        utf_binary.append(binary.substr(binary.length() - 21, 3));
        utf_binary.append("10");
        utf_binary.append(binary.substr(binary.length() - 18, 6));
        utf_binary.append("10");
        utf_binary.append(binary.substr(binary.length() - 12, 6));
        utf_binary.append("10");
        utf_binary.append(binary.substr(binary.length() - 6, 6));
    }
    return utf_binary;
}

string utfToHex(string utf_binary)
{
    string utf;
    map<string, string> konverteris = {
    {"0000","0"},
    {"0001","1"},
    {"0010","2"},
    {"0011","3"},
    {"0100","4"},
    {"0101","5"},
    {"0110","6"},
    {"0111","7"},
    {"1000","8"},
    {"1001","9"},
    {"1010","A"},
    {"1011","B"},
    {"1100","C"},
    {"1101","D"},
    {"1110","E"},
    {"1111","F"}
    };
    for (int i = 0; i < utf_binary.length() / 4; i++)
    {
        utf.append(konverteris[utf_binary.substr(i * 4, 4)]);
    }
    return utf;
}


int main()
{
    ifstream fd("386intel.txt");
    ofstream fr("final.txt");//, ios::binary);
    //ifstream test("386intell.txt");
    while (!fd.eof())
    {
            unsigned char p;
            fd >> noskipws >> p;
            //printf("%c ", p);
            if (p == '\n')
            {
                fr << endl;
                continue;
            }
            int dec = static_cast<int>(p);
            ifstream fd1("CP437.txt");
            int index = 0;
            string h;
            while (!fd1.eof())
            {
                if (index == dec)
                {
                    fd1 >> h;
                    break;
                }
                string temp;
                fd1 >> temp;
                index++;
            }
            index = 0;
            //cout << h << " ";
            string binary = HexToBinary(h);
            char h1[10];
            for (int i = 0; i < h.length(); i++)
                h1[i] = h[i];
            long int sk = strtol(h1, NULL, 16);
            string utf_binary = UniBinaryToUtfBinary(sk, binary);
            string utf = utfToHex(utf_binary);
            //cout << utf << endl;
            int tarp[10];
            for (int f = 0; f < utf.length(); f++)
            {

                if (isdigit(utf[f]))
                    tarp[f] = utf[f] - '0';
                else tarp[f] = utf[f] - 'A' + 10;
            }
            for (int f = 0; f < utf.length(); f += 2)
            {
                char b = tarp[f] * 16 + tarp[f + 1];
                fr << b;
            }
    }
    cout << "Baigta";
}