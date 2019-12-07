#include "TXLib.h"
#include "knopka.cpp"
#include "kartinka.cpp"
#include "file.cpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const int VYSOTA_SHLEM= 165;
const int SHIRINA_SHLEM = 155;
const int VYSOTA_BRONI = 180;
const int SHIRINA_BRONI = 225;
const int VYSOTA_LAPKI = 190;
const int SHIRINA_LAPKI = 180;

const int KOLICH_KARTINOK = 12;

const int SPRAVOCHECHKA = 3;
const int CHTENIEISFAILA = 4;
const int SOHRANIT = 5;

int main()
{
    txCreateWindow (800, 600);

    HDC fon = txLoadImage("Pics\\���.bmp");
    txPlaySound ("������ ��� ����.wav");

    Knopka knopka[6];
    knopka[0] = {20,  30, "����"};
    knopka[1] = {20, 130, "�����"};
    knopka[2] = {20, 230, "�����"};
    knopka[3] = {20, 330, "C����������"};
    knopka[4] = {20, 430, "���������"};
    knopka[5] = {20, 530, "C��������"};

    Kartinka kart[KOLICH_KARTINOK];
    kart[0] = {  "Pics\\����\\����1.bmp"};
    kart[1] = {  "Pics\\����\\����2.bmp"};
    kart[2] = {  "Pics\\����\\����.bmp"};
    kart[3] = {  "Pics\\�����\\�����1.bmp"};
    kart[4] = {  "Pics\\�����\\�����2.bmp"};
    kart[5] = {  "Pics\\�����\\�����3.bmp"};
    kart[6] = {  "Pics\\�����\\�����1.bmp"};
    kart[7] = {  "Pics\\�����\\�����2.bmp"};
    kart[8] = {  "Pics\\�����\\�����3.bmp"};
    kart[9] = {  "Pics\\����\\����3.bmp"};
    kart[10] = { "Pics\\�����\\�����4.bmp"};
    kart[11] = { "Pics\\�����\\�����4.bmp"};

    //�� ������ ������ ��������� ��������� ����������, ��������� � ��� �����
    int yShlem = 0;
    int yBronia = 0;
    int yLapok = 0;
    for (int i = 0; i < KOLICH_KARTINOK; i = i + 1)
    {
        setlocale(LC_ALL,"Russian");

        string stroka = kart[i].adress;
        int pos1 = stroka.find("\\");
        int pos2 = stroka.find("\\", pos1 + 2);
        kart[i].chast = stroka.substr(pos1 + 1, pos2 - pos1 - 1);


        if (kart[i].chast == "�����")
        {
            kart[i].y = yLapok;
            yLapok = yLapok + 150;
        }

        if (kart[i].chast == "����")
        {
            kart[i].y = yShlem ;
            yShlem  = yShlem  + 150;
        }

        if (kart[i].chast == "�����")
        {
            kart[i].y = yBronia;
            yBronia = yBronia + 150;
        }

         kart[i].shirina = 100;
        kart[i].vysota = 100;
        kart[i].x = 655;
        kart[i].picture = txLoadImage(kart[i].adress.c_str());

        kart[i].vysota_bmp = get_height(kart[i].adress);
        kart[i].shirina_bmp = get_widht(kart[i].adress);
    }
         //������� ������ ��� ������ �������� ������ �� ������
    Kartinka pictr[KOLICH_KARTINOK];
    for (int i = 0; i < KOLICH_KARTINOK; i = i + 1)
    {
        pictr[i].adress = kart[i].adress;
        pictr[i].chast = kart[i].chast;
        pictr[i].picture = kart[i].picture;
        pictr[i].clicked = false;
        pictr[i].shirina_bmp = kart[i].shirina_bmp;
        pictr[i].vysota_bmp = kart[i].vysota_bmp;

        if (pictr[i].chast == "�����")
        {
            pictr[i].x = 330;
            pictr[i].y = 400;
            pictr[i].shirina = SHIRINA_LAPKI;
            pictr[i].vysota = VYSOTA_LAPKI;
        }
        if (pictr[i].chast == "����")
        {
            pictr[i].x = 320;
            pictr[i].y = 80;
            pictr[i].shirina = SHIRINA_SHLEM;
            pictr[i].vysota = VYSOTA_SHLEM;
        }
        if (pictr[i].chast == "�����")
        {
            pictr[i].x = 280;
            pictr[i].y = 235;
            pictr[i].shirina = SHIRINA_BRONI;
            pictr[i].vysota = VYSOTA_BRONI;
        }
    }




    string chast = "";
    bool spravka_vyzvana = false;
    int nomer_vybrannoi_chasti = -10;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();

        txBitBlt(txDC(), 0, 0, 800, 600,  fon, 0, 0);
        txRectangle(0,0,150,txGetExtentY());

        for (int i = 0; i < 6; i = i + 1)
        {
            risovatKnopka(knopka[i], chast);
        }



        //��������
        if (GetAsyncKeyState(VK_SNAPSHOT))
        {
            ScreenCapture(220,0,400,600, "1.bmp", txWindow());
            txMessageBox("��������� � 1.bmp");
        }


          //txTransparentBlt(txDC(), 275, 135, 250, 450,  picture, 0, 0, TX_WHITE);

        //����� �������� � ������ (����� ����� ����������� / ���������)
        for (int vybor = 0; vybor < KOLICH_KARTINOK; vybor = vybor + 1)
        {
            if (clickNaKartinka(pictr[vybor]))
            {
                nomer_vybrannoi_chasti = vybor;
            }
        }

        if (nomer_vybrannoi_chasti >= 0)
        {
            {
                if (GetAsyncKeyState(VK_LEFT))
                {
                    pictr[nomer_vybrannoi_chasti].x = pictr[nomer_vybrannoi_chasti].x - 2;
                }

                if (GetAsyncKeyState(VK_RIGHT))
                {
                    pictr[nomer_vybrannoi_chasti].x = pictr[nomer_vybrannoi_chasti].x + 2;
                }
                if (GetAsyncKeyState(VK_UP))
                {
                    pictr[nomer_vybrannoi_chasti].y = pictr[nomer_vybrannoi_chasti].y - 2;
                }
                if (GetAsyncKeyState(VK_DOWN))
                {
                    pictr[nomer_vybrannoi_chasti].y = pictr[nomer_vybrannoi_chasti].y + 2;
                }

                if (GetAsyncKeyState(VK_OEM_PLUS))
                {
                    pictr[nomer_vybrannoi_chasti].shirina = pictr[nomer_vybrannoi_chasti].shirina * 1.02;
                    pictr[nomer_vybrannoi_chasti].vysota = pictr[nomer_vybrannoi_chasti].vysota * 1.02;
                }

                if (GetAsyncKeyState(VK_OEM_MINUS))
                {
                    pictr[nomer_vybrannoi_chasti].shirina = pictr[nomer_vybrannoi_chasti].shirina / 1.02;
                     pictr[nomer_vybrannoi_chasti].vysota = pictr[nomer_vybrannoi_chasti].vysota / 1.02;
                }
            }
        }

        for (int i = 0; i < KOLICH_KARTINOK; i = i + 1)
        {
            if (pictr[i].clicked)
            {
                Win32::TransparentBlt(txDC(), pictr[i].x, pictr[i].y, pictr[i].shirina, pictr[i].vysota, pictr[i].picture, 0, 0, pictr[i].shirina_bmp, pictr[i].vysota_bmp, TX_WHITE);
            }
         }



        for (int i = 0; i <6; i = i + 1)
        {
        chast = getChast(knopka[i], chast);
        }


       //������ �� �����
    if (txMouseButtons() == 1 &&
        txMouseX() < knopka[CHTENIEISFAILA].x + 120 &&
        txMouseY() > knopka[CHTENIEISFAILA].y &&
        txMouseY() < knopka[CHTENIEISFAILA].y + 40)
        {
            string stroka;
            string stroka_x;
            string stroka_y;
            ifstream file("1.txt");

            while(file.good())
            {
                getline(file, stroka);
                if (stroka.size() > 1)
                {
                    getline(file, stroka_x);
                    getline(file, stroka_y);

                    for (int i = 0; i < KOLICH_KARTINOK; i = i + 1)
                    {
                        if (pictr[i].adress == stroka)
                        {
                            pictr[i].clicked = true;
                            pictr[i].x = atoi(stroka_x.c_str());
                             pictr[i].y = atoi(stroka_y.c_str());
                        }
                    }
                }
            }
            file.close();
        }


    if (txMouseButtons() == 1 &&
        txMouseX() < knopka[SOHRANIT].x + 120 &&
        txMouseY() > knopka[SOHRANIT].y &&
        txMouseY() < knopka[SOHRANIT].y + 40)
        {
            saveToFile(KOLICH_KARTINOK, pictr);
        }


        //�������
    if (txMouseButtons() == 1 && spravka_vyzvana)
    {
        spravka_vyzvana = false;
    }

    if (txMouseButtons() == 1 &&
        !spravka_vyzvana &&
        txMouseX() < knopka[SPRAVOCHECHKA].x + 120 &&
        txMouseY() > knopka[SPRAVOCHECHKA].y &&
        txMouseY() < knopka[SPRAVOCHECHKA].y + 40)
        {
            spravka_vyzvana = true;
            txSleep(200);
        }

        if (spravka_vyzvana)
        {
            txSelectFont("Arial", 50);
            txSetColor     (TX_BLACK);
            txRectangle (0, 0, 800, 600);
            txDrawText  (0, 0, 800, 600,
                "Copyright:\n"
                "��������� �������\n"
                "\n"
                "� ���� ��������� ��:\n"
                "������� ������� ���������� �� Star Wars\n"
                "� �����...                                                       \n"
                "...������                                                         \n"
                "\n"
                "����������:\n"
                 "����������� ���������, ����� �� Escape\n"
                 "+ ��������� ������ (�������� �������)\n"
                 "-  ��������� ������ (����� ����� �����)"
            );
        }


        for (int i = 0; i < KOLICH_KARTINOK; i = i + 1)
            {
            if(chast== kart[i].chast)
            {
                Win32::TransparentBlt(txDC(), kart[i].x,   kart[i].y, kart[i].shirina, kart[i].vysota, kart[i].picture,  0, 0, kart[i].shirina_bmp, kart[i].vysota_bmp, TX_WHITE);
            }
        }

        for (int vybor = 0; vybor < KOLICH_KARTINOK; vybor = vybor + 1)
        {
            if (clickNaVariant(kart[vybor], chast))
            {
                 for (int nomer = 0; nomer < KOLICH_KARTINOK; nomer = nomer + 1)
                 {
                     if (pictr[vybor].chast == pictr[nomer].chast)
                     {
                        pictr[nomer].clicked = false;
                     }
                 }

                 pictr[vybor].clicked = true;
            }
        }



        if (GetAsyncKeyState('U') && nomer_vybrannoi_chasti >= 0)
        {
            string adress = pictr[nomer_vybrannoi_chasti].adress;
            string chast2 = pictr[nomer_vybrannoi_chasti].chast;

            if (chast2 == "�����")
            {
                int pos = adress.find(chast2);
                adress = adress.replace(pos, chast2.size(), chast2 + "4");


                 int pos2 = adress.find("44");
                 if (pos2 > -1)
                 {
                    adress = adress.replace(pos2, 2, "");
                 }

                pictr[nomer_vybrannoi_chasti].adress = adress;
                pictr[nomer_vybrannoi_chasti].picture = txLoadImage(adress.c_str());
                txSleep(200);
            }
         }



        txSleep(10);
        txEnd();
    }

    txDeleteDC(fon);

    for (int i = 0; i < KOLICH_KARTINOK; i++)
    {
        txDeleteDC(pictr[i].picture);
    }



    return 0;
}
