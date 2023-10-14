 //PKG_Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//#include <windows.h>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <iostream>
//
//using namespace std;
//
//
////COLORREF rgbRed = 0x000000FF;
//unsigned int getByte(ifstream & file, char byte1)
//{
//    unsigned int t, res = 0, base =256;
//    file.get(byte1);
//    t = byte1 & 255;
//    while (t != 0)
//    {
//        res += (t & 1) * (base >>= 1);
//        t >>= 1;
//    }
//    return res;
//}
//unsigned int newByte;
//int countp = 0, countB = 0, pixel = 0;
//int getColor(vector<unsigned int> &ind, unsigned int header)
//{
//    int bit = 0, pixel1 = 0;
//    while (countp < header && countB < 8)
//    {
//        bit = newByte & 1;
//        ind.push_back(bit);
//        //pixel = pixel | (bit);
//        newByte = newByte >> 1;
//        //pixel = pixel << 1;
//        countp++;
//        countB++;
//    }
//    if (countB == 8 && countp < header)
//    {
//        countB = 0;
//        return 100;
//    }
//    if (/*(countB != 0) ||*/ (countp == header))
//    {
//        countp = 0;
//        for (int i = ind.size() - header; i < ind.size(); i++)
//        {
//            pixel1 = pixel1 | ind[i];
//            pixel1 = pixel1 << 1;
//        }
//        /*pixel1 = pixel;
//        pixel = 0;*/
//    }
//    
//    return pixel1;
//}
//
//
//int main()
//{
//    ifstream file;
//    file.open("File3");
//    char byte1;
//    char byte2;
//    unsigned int header[4], leftMove = 240;
//
//    //----------------get fileData----------------
//    file.get(byte1);
//    file.get(byte2);
//    header[0] = byte1 << 16;
//    header[0] = header[0] | byte2;
//
//    file.get(byte1);
//    file.get(byte2);
//    header[1] = byte1 << 16;
//    header[1] = header[1] | byte2;
//
//    file.get(byte1);
//    header[2] = byte1;
//
//    file.get(byte1);
//    file.get(byte2);
//    header[3] = byte1 << 16;
//    header[3] = header[3] | byte2;
//
//
//    //-----------------get Colors------------------
//
//
//    vector<unsigned long int> argbAll;
//    unsigned long int rgb[4];
//    for (int i = 0; i < header[3]; i++)
//    {
//        file.get(byte1);
//        rgb[0] = byte1 & 255;
//        rgb[0] = !rgb[0];
//        rgb[0] = rgb[0] << 24;
//        file.get(byte1);
//        rgb[1] = byte1 & 255;
//        
//        file.get(byte1);
//        rgb[2] = byte1 & 255;
//        rgb[2] = rgb[2] << 8;
//        file.get(byte1);
//        rgb[3] = byte1 & 255;
//        rgb[3] = rgb[3] << 16;
//        argbAll.push_back(rgb[0]);
//        argbAll[i] = argbAll[i] | rgb[1];
//        argbAll[i] = argbAll[i] | rgb[2];
//        argbAll[i] = argbAll[i] | rgb[3];
//    }
//
//    //-------------------get image-------------
//
//    vector<unsigned int> ind, indAll;
//    unsigned int color, pixel = 0, bit;
//    string str;
//     
//
//    HWND sHwnd = GetConsoleWindow();
//    HDC hdc = GetDC(sHwnd);
//
//    
//
//    for (int y = 100; y < 100 + header[1]; y++)
//	{
//        for (int x =100; x < 100 + header[0]; x++)
//        {
//            //---------------------------
//            if (ind.size() % 8 == 0)
//            {
//                newByte = getByte(file, byte1);
//            }
//
//            pixel = getColor(ind, header[2]);
//            pixel = pixel >> 1;
//            if (pixel < header[3])
//            {
//                color = argbAll[pixel];
//                COLORREF argb = color;
//                SetPixel(hdc, x, y, color);
//            }
//            if (pixel == 50)
//            {
//                x--;
//            }
//            
//        }
//    }
//    while (true)
//    {
//
//    }
//    return 0;
//}
//
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
//#include <sys>

using namespace std;


//COLORREF rgbRed = 0x000000FF;
void getByte(char byte1, vector<unsigned int>& ind)
{
    unsigned int t, res = 0, base = 256;
    t = byte1 & 255;
    for (int i = 0; i < 8; i++)
    {
        res += (t & 1) * (base >>= 1);
        t >>= 1;
    }
    for (int i = 0; i < 8; i++)
    {
        ind.push_back(res & 1);
        res >>= 1;
    }
    return;
}

int getColor(vector<unsigned int>& ind, unsigned int header, int x)
{
    unsigned int pixel = 0;
    for (int i = 0; i < header; i++)
    {
        pixel = pixel | ind[i];
        pixel = pixel << 1;
    }
    auto begin = ind.cbegin(); // указатель на первый элемент
    ind.erase(begin, begin + header); // удаляем с третьего элемента до последнего
    return pixel;
}


int main()
{
    ifstream file;
    file.open("File4");
    char byte1;
    char byte2;
    unsigned int header[4], leftMove = 240;

    //----------------get fileData----------------
    file.get(byte1);
    file.get(byte2);
    header[0] = byte1 << 16;
    header[0] = header[0] | byte2;

    file.get(byte1);
    file.get(byte2);
    header[1] = byte1 << 16;
    header[1] = header[1] | byte2;

    file.get(byte1);
    header[2] = byte1;

    file.get(byte1);
    file.get(byte2);
    header[3] = byte1 << 16;
    header[3] = header[3] | byte2;


    //-----------------get Colors------------------


    vector<unsigned long int> argbAll;
    unsigned long int rgb[4];
    for (int i = 0; i < header[3]; i++)
    {
        file.get(byte1);
        rgb[0] = byte1 & 255;
        rgb[0] = !rgb[0];
        rgb[0] = rgb[0] << 24;
        file.get(byte1);
        rgb[1] = byte1 & 255;

        file.get(byte1);
        rgb[2] = byte1 & 255;
        rgb[2] = rgb[2] << 8;
        file.get(byte1);
        rgb[3] = byte1 & 255;
        rgb[3] = rgb[3] << 16;
        argbAll.push_back(rgb[0]);
        argbAll[i] = argbAll[i] | rgb[1];
        argbAll[i] = argbAll[i] | rgb[2];
        argbAll[i] = argbAll[i] | rgb[3];
    }

    //-------------------get image-------------

    vector<unsigned int> ind, indAll;
    unsigned int color, pixel = 0, bit;
    string str;


    HWND sHwnd = GetConsoleWindow();
    HDC hdc = GetDC(sHwnd);

    while (file.get(byte1))
    {
        getByte(byte1, ind);
    }



    for (int y = 100; y < 100 + header[1]; y++)
    {
        for (int x = 100; x < 100 + header[0]; x++)
        {
            //---------------------------

            pixel = getColor(ind, header[2], x);
            pixel = pixel >> 1;
            if (pixel < header[3])
            {
                color = argbAll[pixel];
                COLORREF argb = color;
                SetPixel(hdc, x, y,  (color));
            }

        }
    }
    while (true)
    {

    }
    return 0;
}