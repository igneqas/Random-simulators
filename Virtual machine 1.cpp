#include <map>
#include <iostream>
#include <fstream>

using namespace std;
string decToHex(int sk);
map<char, int> kon = {
    {'0',0},
    {'1',1},
    {'2',2},
    {'3',3},
    {'4',4},
    {'5',5},
    {'6',6},
    {'7',7},
    {'8',8},
    {'9',9},
    {'A',10},
    {'B',11},
    {'C',12},
    {'D',13},
    {'E',14},
    {'F',15}
};
int main()
{
    ifstream in("decryptor.bin", ios::binary);
    ifstream ind("q1_encr.txt");
    ofstream out("q1_decrypted.txt");

    /*ifstream in("enc_new.bin", ios::binary);
    ifstream ind("message.txt");
    ofstream out("encrypted_message.txt");*/

    /*ifstream in("dec_new.bin", ios::binary);
    ifstream ind("encrypted_message.txt");
    ofstream out("decrypted_message.txt");*/
    int regs[16];
    char prog_mem[256];
    bool flag=false,eof = false;
    in.read(prog_mem, 256);
    int sk=0;
    while (sk < 256) {
        //cout <<regs[1]<<" "<< regs[2]<<" "<<regs[3] << endl;
        switch (prog_mem[sk])
        {
        case 1:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            regs[Rx]++;
            sk += 2;
            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 2:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            regs[Rx]--;
            sk += 2;
            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 3:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            int Ry = kon[R[0]];
            regs[Rx] = regs[Ry];
            sk += 2;
            break;
        }
        case 4:
            regs[0] = (unsigned int)prog_mem[sk + 1];
            sk += 2;
            if (regs[0] == 0)
                flag = true;
            else flag = false;
            break;
        case 5:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            //regs[Rx] << 1;
            regs[Rx] *= 2;
            sk += 2;
            break;
        }
        case 6:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            //regs[Rx] >> 1;
            regs[Rx] /= 2;
            sk += 2;
            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 7:
        {
            sk += (int)prog_mem[sk + 1];
            break;
        }
        case 8:
        {
            if (flag)
                sk += (int)prog_mem[sk + 1];
            else sk += 2;
            break;
        }
        case 9:
        {
            if (flag == false)
                sk += (int)prog_mem[sk + 1];
            else sk += 2;
            break;
        }
        case 10:
        {
            if (eof)
            {
                sk += (int)prog_mem[sk + 1];
            }
            else sk += 2;
            break;
        }
        case 11:
        {
            cout << "Virtuali masina baige darba";
            return 0;
            break;
        }
        case 12:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            int Ry = kon[R[0]];
            regs[Rx] += regs[Ry];
            sk += 2;
            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 13:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            int Ry = kon[R[0]];
            regs[Rx] -= regs[Ry];
            sk += 2;
            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 14:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            int Ry = kon[R[0]];
            regs[Rx] = regs[Rx] ^ regs[Ry];
            sk += 2;
            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 15:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            int Ry = kon[R[0]];
            regs[Rx] = regs[Rx] | regs[Ry];
            sk += 2;
            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 16:
        {
            unsigned char x;
            ind >> noskipws>>x;
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            regs[Rx]=(unsigned int)x;
            sk += 2;
            if (ind.eof())
                eof = true;
            else eof = false;

            if (regs[Rx] == 0)
                flag = true;
            else flag = false;
            break;
        }
        case 17:
        {
            string R = decToHex((int)prog_mem[sk + 1]);
            int Rx = kon[R[1]];
            out << (char)regs[Rx];
            sk += 2;
            break;
        }
        }
    }
}

string decToHex(int sk)
{
    string hexas="00";
    string temp;
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
    return hexas;
}