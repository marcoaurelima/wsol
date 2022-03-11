#ifndef WSOL_H_INCLUDED
#define WSOL_H_INCLUDED
#include <windows.h>

/*** --------------------------------------------------------------------------------- ***                                                                                     *
 ***                                  wsol.h                                           ***
 ***                          Autor: Marco Aurélio Lima                                ***
 ***                            Ver. 2.1   26-09-2020                                  ***                                                           *
 *** --------------------------------------------------------------------------------- ***/

/// OBS.: Sempre que for usar as funcoes wsol_fontsize() e wsol_consolesize() no mesmo ///
/// código, chame a wsol_fontsize() primeiro.                                          ///

///  Muda o tamanho das letras.                                                        ///
///  Se bold == WSOL_FONT_NORMAL, ele sera normal.                                     ///
///  Se bold == WSOL_FONT_BOLD, sera negrito.                                          ///
void wsol_fontsize(int size, int bold);


/// Muda o tamanho da jenela de Console e centraliza no monitor. Tamanho em PIXELS.    ///
void wsol_consolesize(int sizeX, int sizeY);


/// Muda a cor das letras mostradas na janela de Console.                              ///
/// Use as constantes (ex.: WSOL_RED) definidas ou tipos inteiros.                     ///
/// As cores mudarão sempre que essa função for chamada. Isso significa que é possivel ///
/// colorir separadamente cada letra.
void wsol_fontcolor(int color_text, int color_background);


/// Muda a quantidade de caracteres maxima nas linhas. Eixo X.                         ///
/// valor minimo padrao do bufferSize no eixo X: 120                                   ///
void wsol_bufferX(int bufferSize);


/// Muda a quantidade de linhas maxima permitidas. Eixo Y.                             ///
/// valor minimo padrao do bufferSize no eixo X: 120                                   ///
void wsol_bufferY(int bufferSize);


/// Muda a quantidade de caracteres e linhas maxima permitido.                         ///
/// valor minimo padrao do bufferSize no eixo X: 120                                   ///
/// valor minimo padrao do bufferSize no eixo X: 120                                   ///
void wsol_bufferXY(int bufferSizeX, int bufferSizeY);

enum{
    WSOL_FONT_NORMAL,
    WSOL_FONT_BOLD
};

enum
{
    WSOL_BLACK,
    WSOL_BLUE,
    WSOL_GREEN,
    WSOL_BLUE_L2,
    WSOL_RED,
    WSOL_PURPLE,
    WSOL_YELLOW,
    WSOL_GRIZ_L1,
    WSOL_GRIZ,
    WSOL_BLUE_L1,
    WSOL_GREEN_L1,
    WSOL_BLUE_L3,
    WSOL_RED_L1,
    WSOL_PURPLE_L1,
    WSOL_YELLOW_L1,
    WSOL_WHITE

};

void wsol_bufferX(int bufferSize)
{
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO scrBuffer;
    GetConsoleScreenBufferInfo(handler, &scrBuffer);
    scrBuffer.dwSize.X = bufferSize;
    SetConsoleScreenBufferSize(handler, scrBuffer.dwSize);
}

void wsol_bufferY(int bufferSize)
{
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO scrBuffer;
    GetConsoleScreenBufferInfo(handler, &scrBuffer);

    scrBuffer.dwSize.Y = bufferSize;

    SetConsoleScreenBufferSize(handler, scrBuffer.dwSize);

}

void wsol_bufferXY(int bufferSizeX, int bufferSizeY)
{
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO scrBuffer;
    GetConsoleScreenBufferInfo(handler, &scrBuffer);
    scrBuffer.dwSize.X = bufferSizeX;
    scrBuffer.dwSize.Y = bufferSizeY;
    SetConsoleScreenBufferSize(handler, scrBuffer.dwSize);
}

void wsol_fullscreen()
{
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleDisplayMode(handler, CONSOLE_FULLSCREEN_MODE,NULL);
}

void wsol_consolesize(int sizeX, int sizeY)
{
    int scrSizeX = GetSystemMetrics(SM_CXMAXIMIZED);
    int scrSizeY = GetSystemMetrics(SM_CYMAXIMIZED);

    int posX = (scrSizeX - sizeX)/2;
    int posY = (scrSizeY - sizeY)/2;

    HWND hd = GetConsoleWindow();
    SetWindowPos(hd, HWND_TOP, posX, posY, sizeX, sizeY, SWP_NOZORDER);
}

void wsol_fontcolor(int color_text, int color_background)
{
    int code = color_text + (color_background * 16);
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handler, code);
}

void wsol_fontsize(int size, int bold)
{
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 0;
    fontInfo.dwFontSize.Y = size;
    fontInfo.FontFamily = FF_DONTCARE;
    wcscpy(fontInfo.FaceName, L"Consolas");

    if(bold) { fontInfo.FontWeight = FW_BOLD;   }
        else { fontInfo.FontWeight = FW_NORMAL; }

    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetCurrentConsoleFontEx(handler, 0, &fontInfo);
}


#endif // WSOL_H_INCLUDED
