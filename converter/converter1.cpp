#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

void decToHex(int sk, vector<char>& hexas);
string HexToBinary(vector<char> hexas);
string UniBinaryToUtfBinary(int sk, string binary);
string utfToHex(string utf_binary);

int main()
{
        int sk;
        cin >> sk;
        vector<char> hexas;
        if (sk < 65536)
            hexas = { '0','0','0','0' };
        else if (sk > 65535 && sk < 1048576)
            hexas = { '0','0','0','0','0' };
        else
            hexas = { '0','0','0','0','0','0' };
        decToHex(sk, hexas);
        cout << "UNICODE: U+";
        for (int i = 0; i < hexas.size(); i++)
            cout << hexas[i];
        string binary = HexToBinary(hexas);
        string utf_binary = UniBinaryToUtfBinary(sk, binary);
        string utf = utfToHex(utf_binary);
        cout << endl << "UTF-8: " << utf << endl;
        cout << "CHAR: ";
        _setmode(_fileno(stdout), _O_U8TEXT);
        wprintf(L"%c\n", sk);
    
}

void decToHex(int sk, vector<char> &hexas)
{
    
    vector<char> temp;
    while (sk != 0)
    {
        int liek = sk % 16;
        sk /= 16;
        if (liek < 10)
        {
            temp.push_back(liek + 48);
        }
        else
            temp.push_back(liek + 55);
    }
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        hexas.push_back(temp[i]);
        hexas.erase(hexas.begin());
    }
}

string HexToBinary(vector<char> hexas)
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
    for (int i = 0; i < hexas.size(); i++)
    {
        binary.append(kon[hexas[i]]);
    }
    return binary;
}

string UniBinaryToUtfBinary(int sk, string binary)
{
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