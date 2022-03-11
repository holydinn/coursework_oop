/**************************************************************************
*                           �  �  �                                       *
*-------------------------------------------------------------------------*
*                                                                         *
* Project Name  : \���\��������_���\��������                              *
* Project Type  : Win32 Console application                               *
* File Name     : ��������                                                *
* Language      : Visual C++           MS VS 2017                         *
* Programmer(s) : �������� �.�.                                           *
* Modified By   : �������� �.�.                                           *
* Created       : 8 / 04 / 2021                                          *
* Last Revision : 2 / 06 / 2021                                          *
* Comment(s)    : �������� �� ��� (������������, ���������,               *
*                 ������������ �����������                                *
*                                                                         *
 **************************************************************************/
#pragma once   
#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;  //������������ ���� std
#include "classes.h" 	//���������� �������
#include "GetConlWin.h"	//��������� �� ���������� ����

 //������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

void PressKey(int VkCode);
HDC hdc;	// ������� �������� ����������

void main()
{
	int curx, cury;  //������� ����������
	int x0 = 150, y0 = 250;	//��������� ���������� 
	double scale0 = 0.8, ship_scale = 0.6;

	//������� ���������� ����������� ����
	HWND hwnd = GetConcolWindow();

	//���� ���������� ���������� - ����� ��������
	if (hwnd != NULL)
	{
		//������� �������� ���������� ��� ����������� ����
		hdc = GetWindowDC(hwnd);

		//���� �������� ���������� - ����� ��������
		if (hdc != 0)
		{
			ship regularship(x0, y0, ship_scale);  //������� �������
			rich_ship richship(x0, y0, ship_scale);  //������� � �����������
			wrecked_ship wrecked(x0, y0, ship_scale);  //����������� �������
			bomb abomb(850, y0-50, scale0); //�����
			bomb bbomb(850, y0 +125, scale0);
			bomb cbomb(850, y0+300 , scale0);
			medcine med(x0+700, y0, scale0);  //�������
			treasure treasure(x0+700, y0+250, scale0*1.5);  //���������

			//rich_shipv2 shipfordef(x0, y0, ship_scale);
			ship* pointership = &regularship; //��������� �� ������� ������ ��������
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
				//��������� ������������ � ���������
				//� ������
				if ((pointership->getx() +250 < bbomb.getx()+100) && (pointership->getx()+250 > bbomb.getx()+75) && (pointership->gety() +50< bbomb.gety()+100) && (pointership->gety()+50 > bbomb.gety() +10)|| 
					(pointership->getx() + 250 < abomb.getx() + 100) && (pointership->getx() + 250 > abomb.getx() + 75) && (pointership->gety() + 50 < abomb.gety() + 100) && (pointership->gety() + 50 > abomb.gety() + 10)||
					(pointership->getx() + 250 < cbomb.getx() + 100) && (pointership->getx() + 250 > cbomb.getx() + 75) && (pointership->gety() + 50 < cbomb.gety() + 100) && (pointership->gety() + 50 > cbomb.gety() + 10))
				{
					pointership->expand(0.1);
					Sleep(200);
					pointership->expand(-0.1);
					pointership->hide(); //������ �������
					curx = pointership->getx();
					cury = pointership->gety();
					pointership = &wrecked;
					pointership->setx(curx-150); //�������� ���������� ����
					pointership->sety(cury);
					pointership->show();
					Sleep(500);
				}
				//c ��������
				if ((pointership->getx() + 250 < med.getx() + 100) && (pointership->getx() + 250 > med.getx() + 75) && (pointership->gety() + 50 < med.gety() + 100) && (pointership->gety() + 50 > med.gety() + 10)&&pointership!=&richship)
				{
					pointership->hide(); //������ �������
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
				//� �����������
				if ((pointership->getx() + 250 < treasure.getx() + 100) && (pointership->getx() + 250 > treasure.getx() + 75) && (pointership->gety() + 50 < treasure.gety() + 100) && (pointership->gety() + 50 > treasure.gety() + 10) && pointership != &wrecked)
				{
					pointership->hide(); //������ �������
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

