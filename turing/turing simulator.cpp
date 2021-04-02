#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <thread>
#include <mutex>

using namespace std;

struct instruction {
    string current_state;
    char current_symbol;
    char new_symbol;
    char direction;
    string new_state;

};

mutex mtx;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void gotoxy(short x, short y)
{
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int sim(string name,int sety) {

    ShowConsoleCursor(false);
    string tape, state = "0";
    int position;
    instruction temp;
    vector <instruction> ins;
    vector <instruction> ::iterator it;
    ifstream fd(name);
    fd >> tape >> position;
    position--;
    while (!fd.eof())
    {
        fd >> temp.current_state >> temp.current_symbol >> temp.new_symbol >> temp.direction >> temp.new_state;
        ins.push_back(temp);
    }
    int count = 0;
    while (true)
    {
        
            for (it = ins.begin(); it != ins.end(); it++)
            {
                
                    if (it->current_state == state && tape[position] == it->current_symbol)
                    {
                        mtx.lock();
                        clearscreen();
                        gotoxy(0, sety);
                        cout << tape;
                        mtx.unlock();
                        if (it->new_state == "H")
                        {
                            mtx.lock();
                            clearscreen();
                            gotoxy(0, sety);
                            cout << endl;
                            cout << "Programa pasibaige";
                            mtx.unlock();
                            return 0;
                        }
                        tape[position] = it->new_symbol;
                        state = it->new_state;
                        switch (it->direction)
                        {
                        case 'R':
                            position++;
                            break;
                        case 'L':
                            position--;
                            break;
                        }
                        Sleep(0);
                        count = 0;
                    }
                    if (position<0 || position>tape.length())
                    {
                        mtx.lock();
                        clearscreen();
                        gotoxy(0, sety);
                        cout << endl << "Klaida. Uzeita uz juostos ribu";
                        mtx.unlock();
                        return 0;
                    }
                   if (count==3)
                    {
                       mtx.lock();
                       clearscreen();
                       gotoxy(0, sety);
                       cout << endl;
                        cout << "Klaida. Truksta instrukciju";
                        mtx.unlock();
                        return 0;
                    }
                   

                    
            }        

            count++;
    }
}



int main()
{
    int y=5,amount,index=0;
    string name[10];
    vector <thread> threads;
    cin >> amount;
    for (int i = 0; i < amount; i++)
    {
        cin >> name[i];
    }
    system("cls");
    for (int i = 0; i < amount; i++)
    {
        threads.push_back(thread(sim, name[i], y * i));
    }
    for (int i = 0; i < amount; i++)
    {
        threads[i].join();
    }
    while (true)
                   {
                                if (GetKeyState(VK_RETURN) < 0)
                                {
                                    return 0;
                                }
                            }
}