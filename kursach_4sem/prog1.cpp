/**************************************************************************
*                           О  О  П                                       *
*-------------------------------------------------------------------------*
*                                                                         *
* Project Name  : \ООП\Курсовая_ООП\Курсовая                              *
* Project Type  : Win32 Console application                               *
* File Name     : Курсовая                                                *
* Language      : Visual C++           MS VS 2017                         *
* Programmer(s) : Имамиева Д.Э.                                           *
* Modified By   : Имамиева Д.Э.                                           *
* Created       : 8 / 04 / 2021                                          *
* Last Revision : 2 / 06 / 2021                                          *
* Comment(s)    : Курсовая по ООП (наследование, интерфейс,               *
*                 динамический полиморфизм                                *
*                                                                         *
 **************************************************************************/
#pragma once   
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;  //пространство имен std
#include "classes.h" 	//объявление классов
#include "GetConlWin.h"	//указатель на консольное окно

 //макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

void PressKey(int VkCode);
HDC hdc;	// Объявим контекст устройства

void main()
{
	int curx, cury;  //текущие координаты
	int x0 = 150, y0 = 250;	//стартовые координаты 
	double scale0 = 0.8, ship_scale = 0.6;

	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();

	//если дескриптор существует - можем работать
	if (hwnd != NULL)
	{
		//получим контекст устройства для консольного окна
		hdc = GetWindowDC(hwnd);

		//если контекст существует - можем работать
		if (hdc != 0)
		{
			ship regularship(x0, y0, ship_scale);  //обычный корабль
			rich_ship richship(x0, y0, ship_scale);  //корабль с сокровищами
			wrecked_ship wrecked(x0, y0, ship_scale);  //подорванный корабль
			bomb abomb(850, y0-50, scale0); //бомбы
			bomb bbomb(850, y0 +125, scale0);
			bomb cbomb(850, y0+300 , scale0);
			medcine med(x0+700, y0, scale0);  //аптечка
			treasure treasure(x0+700, y0+250, scale0*1.5);  //сокровища

			//rich_shipv2 shipfordef(x0, y0, ship_scale);
			ship* pointership = &regularship; //указатель на объекты класса кораблей
			while (1)
			{
				if (KEY_DOWN(VK_ESCAPE))
					break;

				abomb.moveto(abomb.getx() - 2, abomb.gety()); 
				bbomb.moveto(bbomb.getx() - 2, bbomb.gety()); 
				cbomb.moveto(cbomb.getx() - 2, cbomb.gety()); 
				med.show();
				treasure.show();	
				
				pointership->show();
				pointership->drag(10);
				//возможные столкновения с объектами
				//с бомбой
				if ((pointership->getx() +250 < bbomb.getx()+100) && (pointership->getx()+250 > bbomb.getx()+75) && (pointership->gety() +50< bbomb.gety()+100) && (pointership->gety()+50 > bbomb.gety() +10)|| 
					(pointership->getx() + 250 < abomb.getx() + 100) && (pointership->getx() + 250 > abomb.getx() + 75) && (pointership->gety() + 50 < abomb.gety() + 100) && (pointership->gety() + 50 > abomb.gety() + 10)||
					(pointership->getx() + 250 < cbomb.getx() + 100) && (pointership->getx() + 250 > cbomb.getx() + 75) && (pointership->gety() + 50 < cbomb.gety() + 100) && (pointership->gety() + 50 > cbomb.gety() + 10))
				{
					pointership->expand(0.1);
					Sleep(200);
					pointership->expand(-0.1);
					pointership->hide(); //скрыть корабль
					curx = pointership->getx();
					cury = pointership->gety();
					pointership = &wrecked;
					pointership->setx(curx-150); //показать срубленную елку
					pointership->sety(cury);
					pointership->show();
					Sleep(500);
				}
				//c аптечкой
				if ((pointership->getx() + 250 < med.getx() + 100) && (pointership->getx() + 250 > med.getx() + 75) && (pointership->gety() + 50 < med.gety() + 100) && (pointership->gety() + 50 > med.gety() + 10)&&pointership!=&richship)
				{
					pointership->hide(); //скрыть корабль
					med.expand(0.5);
					Sleep(200);
					med.expand(-0.5);
					curx = pointership->getx();
					cury = pointership->gety();
					pointership = &regularship;
					pointership->setx(curx - 50); 
					pointership->sety(cury);
					pointership->show();
					Sleep(500);
				}
				//с сокровищами
				if ((pointership->getx() + 250 < treasure.getx() + 100) && (pointership->getx() + 250 > treasure.getx() + 75) && (pointership->gety() + 50 < treasure.gety() + 100) && (pointership->gety() + 50 > treasure.gety() + 10) && pointership != &wrecked)
				{
					pointership->hide(); //скрыть корабль
					treasure.expand(0.5);
					Sleep(200);
					treasure.expand(-0.5);
					curx = pointership->getx();
					cury = pointership->gety();
					pointership = &richship;
					pointership->setx(curx - 50); 
					pointership->sety(cury);
					pointership->show();
					Sleep(500);
				}
				Sleep(50);
			}
		}// end if
	}// end if
}//end main()

void PressKey(int VkCode) {
	while (1) if (KEY_DOWN(VkCode)) break;
}

