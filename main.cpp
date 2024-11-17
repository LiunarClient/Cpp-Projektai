#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

//global
const int plotis = 80;
const int aukstis = 20;
int x, y;
int saldX, saldY;
int taskai, highscore;
int UodX[100], UodY[100], uodL;
enum Kryptis
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Kryptis kr;
bool arBaiges;
void pradzia();
void gameRender(string vrd);
void atnaujinti();
int Sunkumas();
void inputai();
void skaityti();
void rasyti();
int main()
{
    string vrd;
    cout << "Iveskite savo varda: ";
    cin >> vrd;
    int dif = Sunkumas();

    pradzia();
    while (!arBaiges)
    {
        system("color A");
        gameRender(vrd);
        inputai();
        atnaujinti();
        Sleep(dif);
    }
    if(taskai > highscore) rasyti();
    return 0;
}
void pradzia()
{
    arBaiges = false;
    kr = STOP;
    x = plotis/2;
    y = aukstis/2;
    saldX = rand() % plotis;
    saldY = rand() % aukstis;
    taskai = 0;
    skaityti();
}
void gameRender(string vrd)
{
    system("cls");

    //virsutine siena
    for (int i = 0; i < plotis+2; i++) cout << "-";
    cout << endl;

    //sonines sienos
    for (int i= 0; i < aukstis; i++)
    {
        for (int j = 0; j <= plotis; j++)
        {
            if (j == 0 || j == plotis) cout << "|";
            if (i == y && j == x) cout << "O";
            else if (i == saldY && j == saldX) cout << "#";
            else
            {
                bool prUod = false;
                for (int k = 0; k < uodL; k++)
                {
                    if (UodX[k] == j && UodY[k] == i)
                    {
                        cout << "o";
                        prUod = true;
                    }
                }
                if (!prUod) cout << " ";
            }
        }
        cout << endl;
    }
    //apatine siena
    for (int i = 0; i < plotis+2; i++) cout << "-";
    cout << endl;

    cout << vrd << "'s Taskai: " << taskai << " " << "Highscore: " << highscore << endl;
}
void atnaujinti()
{
    int prX = UodX[0];
    int prY = UodY[0];
    int pr2X, pr2Y;
    UodX[0] = x;
    UodY[0] = y;

    for (int i = 1; i < uodL; i++)
    {
        swap(UodX[i], prX);
        swap(UodY[i], prY);
    }
    //krypties patikra
    switch (kr)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    //patikra ar neliecia sienos
    if (x >= plotis || x < 0 || y >= aukstis || y < 0) arBaiges = true;
    //patikra ar neliecia uodegos
    for (int i = 0; i < uodL; i++)
    {
        if (UodX[i] == x && UodY[i] == y) arBaiges = true;
    }
    //patikra ar liecia saldaini
    if (x == saldX && y == saldY)
    {
        taskai += 10;
        saldX = rand() % plotis;
        saldY = rand() % aukstis;
        uodL++;
    }
}
int Sunkumas()
{
    int dif, pas;
    cout << "\nPASIRINKITE SUNKUMA\n1: Lengvas\n2: Normalus\n3: Sunkus "
            "\nP.S.: Jei nepasirenksite sunkumo, bus automatiskai "
            "parinktas Vidutinis sunkumas\nPasirinkite sunkumo lygi: ";
    cin >> pas;
    switch (pas)
    {
    case '1':
        dif = 500;
        break;
    case '2':
        dif = 100;
        break;
    case '3':
        dif = 15;
        break;
    default:
        dif = 100;
    }
    return dif;
}
void inputai()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            kr = LEFT;
            break;
        case 'd':
            kr = RIGHT;
            break;
        case 'w':
            kr = UP;
            break;
        case 's':
            kr = DOWN;
            break;
        case 'x':
            arBaiges = true;
            break;
        }
    }
}
void skaityti()
{
    ifstream in ("taskai.txt");
    in >> highscore;
    in.close();
}
void rasyti()
{
    ofstream out ("taskai.txt");
    out << taskai;
    out.close();
}
