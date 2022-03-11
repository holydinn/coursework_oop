#include <windows.h>
#include "classes.h"

extern HDC hdc; //объявим контекст устройства
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*---------------------------------------------*/
/*            МЕТОДЫ КЛАССА location           */
/*---------------------------------------------*/
location::location(int initx, int inity) 
{	x = initx;	y = inity; }//location()
//получить значение х
int location::getx() {	return x; }
//получить значение y
int location::gety() {	return y; }

/*---------------------------------------------*/
/*            МЕТОДЫ КЛАССА point              */
/*---------------------------------------------*/
point::point(int initx, int inity) : location(initx, inity)
{	visible = false; }//point()
//узнать светимость точки
bool point::isvisible() { return visible; }

/*---------------------------------------------*/
/*            МЕТОДЫ КЛАССА object             */
/*---------------------------------------------*/
//object::object(int initx, int inity, double initscale) : point(initx, inity)
//{	x = 0; y = 0; scale = 0; }

/*---------------------------------------------*/
/*            МЕТОДЫ КЛАССА ship               */
/*---------------------------------------------*/
ship::ship(int initx, int inity, double initscale) : point(initx, inity) 
{	x = initx;  y = inity; 	scale = initscale;}

void ship::moveto(int newx, int newy) {
	hide();  //спрятать по текущим координатам
	x = newx;  //новые координаты
	y = newy;
	if (x > 880) x = 880;
	if (y - 175 > 430) y -= 430;
	if (x - 15 < 0) x = 15;
	if (y - 175 < 0) y += 430;
	show(); //показать по новым координатам
}
void ship::drag(int step)    //буксировка фигуры
{
	int figx, figy;   //новые координаты фигуры

	figx = getx();    //получаем начальное положение фигуры
	figy = gety();

		//направление движения объекта

	if (KEY_DOWN(VK_LEFT)) //стрелка влево  37
	{
		figx -= step;
		moveto(figx, figy);
		Sleep(10);
	}//end if

	if (KEY_DOWN(VK_RIGHT)) //стрелка вправо  39
	{
		figx += step;
		moveto(figx, figy);
		Sleep(10);
	}//end if

	if (KEY_DOWN(VK_DOWN)) //стрелка вниз  40
	{
		figy += step;
		moveto(figx, figy);
		Sleep(10);
	}//end if

	if (KEY_DOWN(VK_UP)) //стрелка вверх  38
	{
		figy -= step;
		moveto(figx, figy);
		Sleep(10);
	}//end if
//}//while
}//drag()
void ship::body(int r, int g, int b, int outline) {
	HPEN pen = CreatePen(PS_INSIDEFRAME, 2, RGB(outline, outline, outline));
	SelectObject(hdc, pen);

	HBRUSH bot = CreateSolidBrush(RGB(r, g, b));//цвет корпуса
	HBRUSH up = CreateSolidBrush(RGB(outline, outline, outline));//цвет полоски

	POINT polygon1[8] = { x,y,x,y - 55 * scale,x + 250 * scale,y - 55 * scale,x + 250 * scale,y }; //координаты корпус
	POINT polygon2[8] = { x,y - 55 * scale,x, y - 75 * scale, x + 250 * scale,y - 75 * scale,x + 250 * scale,y - 55 * scale }; //координаты полоска на корме

	HRGN boat = CreatePolygonRgn(polygon1, 4, 1);
	HRGN lineboat = CreatePolygonRgn(polygon2, 4, 1);

	FillRgn(hdc, boat, bot);
	FillRgn(hdc, lineboat, up);
	//контур
	MoveToEx(hdc, x + 250 * scale, y, NULL);
	LineTo(hdc, x, y);
	LineTo(hdc, x, y - 75 * scale);
	LineTo(hdc, x + 250 * scale, y - 75 * scale);
		MoveToEx(hdc, x, y - 55 * scale, NULL);
	LineTo(hdc, x + 250 * scale, y - 55 * scale);

	//уничтожим созданные объекты
	DeleteObject(pen);
	DeleteObject(bot);
	DeleteObject(up);
}
void ship::bow(int r, int g, int b, int outline) {
	HPEN pen = CreatePen(PS_INSIDEFRAME, 2, RGB(outline, outline, outline));
	SelectObject(hdc, pen);

	HBRUSH bot = CreateSolidBrush(RGB(r, g, b));//цвет корпуса
	HBRUSH up = CreateSolidBrush(RGB(outline, outline, outline));//цвет полоски

	POINT polygon1[6] = { x + 250 * scale,y,x + 250 * scale,y - 55 * scale,x + 300 * scale,y - 55 * scale }; //координаты нос
	POINT polygon2[8] = { x + 250 * scale,y - 55 * scale,x + 250 * scale, y - 75 * scale, x + 320 * scale,y - 75 * scale,x + 300 * scale,y - 55 * scale }; //координаты полоски на носу

	HRGN boatnose = CreatePolygonRgn(polygon1, 3, 1);
	HRGN lineboatnose = CreatePolygonRgn(polygon2, 4, 1);

	FillRgn(hdc, boatnose, bot);
	FillRgn(hdc, lineboatnose, up);

	//контур
	MoveToEx(hdc, x + 250 * scale, y - 75 * scale, NULL);
	LineTo(hdc, x + 320 * scale, y - 75 * scale);
	LineTo(hdc, x + 250 * scale, y);
	MoveToEx(hdc, x + 250 * scale, y - 55 * scale, NULL);
	LineTo(hdc, x + 300 * scale, y - 55 * scale);

	//уничтожим созданные объекты
	DeleteObject(pen);
	DeleteObject(bot);
	DeleteObject(up);
}
void ship::deck(int r, int g, int b, int outline) {

	HPEN pen = CreatePen(PS_INSIDEFRAME, 2, RGB(outline, outline, outline));
	SelectObject(hdc, pen);

	HBRUSH color = CreateSolidBrush(RGB(r, g, b));//выбираем цвет
	POINT polygon3[8] = { x + 45 * scale,y - 75 * scale,x + 45 * scale,y - 130 * scale, x + 210 * scale,y - 130 * scale,x + 210 * scale,y - 75 * scale }; //координаты палубы
	HRGN cargo = CreatePolygonRgn(polygon3, 4, 1);
	FillRgn(hdc, cargo, color);

	//контур
	MoveToEx(hdc, x + 45 * scale, y - 75 * scale, NULL);
	LineTo(hdc, x + 45 * scale, y - 130 * scale);
	LineTo(hdc, x + 210 * scale, y - 130 * scale);
	LineTo(hdc, x + 210 * scale, y - 75 * scale);

	//уничтожим созданные объекты
	DeleteObject(pen);
	DeleteObject(color);

}
void ship::pipe(int r, int g, int b,int outline) {
	HPEN pen = CreatePen(PS_INSIDEFRAME, 2, RGB(outline, outline, outline));
	SelectObject(hdc, pen);

	HBRUSH color = CreateSolidBrush(RGB(r, g, b));//выбираем цвет
	POINT polygon4[8] = { x + 90 * scale,y - 130 * scale,x + 90 * scale,y - 175 * scale,x + 120 * scale,y - 175 * scale,x + 120 * scale,y - 130 * scale }; //координаты трубы
	HRGN tube = CreatePolygonRgn(polygon4, 4, 1);
	FillRgn(hdc, tube, color);

	//контур
	MoveToEx(hdc, x + 90 * scale, y - 130 * scale, NULL);
	LineTo(hdc, x + 90 * scale, y - 175 * scale);
	LineTo(hdc, x + 120 * scale, y - 175 * scale);
	LineTo(hdc, x + 120 * scale, y - 130 * scale);

	//уничтожим созданные объекты
	DeleteObject(pen);
	DeleteObject(color);
}
void ship::window(int r, int g, int b) {

	HBRUSH color = CreateSolidBrush(RGB(r, g, b));//выбираем цвет
	HRGN window = CreateEllipticRgn(x + 150 * scale, y - 115 * scale, x + 180 * scale, y - 85 * scale); //окошко
	FillRgn(hdc, window, color);

	//уничтожим созданные объекты
	DeleteObject(color);
}
void ship::expand(double delta) //увеличить радиус
{
	hide(); //спрятать текущий корабль
	scale += delta; //change 
	if (delta < 0) //для отриц приращения 
		delta = 0.1;
	show(); //показать новый корабль

}//ship::expand
void ship::show(void) {
	visible = true;
	body(61, 70, 205,255);
	bow(61, 70, 205,255);
	deck(113, 147, 205,255);
	pipe(113, 147, 205,255);
	window(255, 255, 255);
}
void ship::hide(void) {
	visible = false;
	body(12, 12, 12,12);
	bow(12, 12, 12,12);
	deck(12, 12, 12,12);
	pipe(12, 12, 12,12);
}

/*---------------------------------------------*/
/*          МЕТОДЫ КЛАССА rich_ship            */
/*---------------------------------------------*/
rich_ship::rich_ship(int initx, int inity, double initscale) :ship(initx, inity, initscale)
{	x = initx; y = inity; scale = 1.2*initscale; }
void rich_ship::pipe(int r, int g, int b, int outline) {
	ship::pipe(r, g, b, outline);

	//добавим вторую трубу
	HPEN pen = CreatePen(PS_INSIDEFRAME, 2, RGB(outline, outline, outline));
	SelectObject(hdc, pen);
	HBRUSH color = CreateSolidBrush(RGB(r, g, b));//голубой
	POINT polygon4[8] = { x + 135 * scale,y - 130 * scale,x + 135 * scale,y - 175 * scale,x + 165 * scale,y - 175 * scale,x + 165 * scale,y - 130 * scale }; //координаты трубы
	HRGN tube = CreatePolygonRgn(polygon4, 4, 1);
	FillRgn(hdc, tube, color);
	MoveToEx(hdc, x + 135 * scale, y - 130 * scale, NULL);
	LineTo(hdc, x + 135 * scale, y - 175 * scale);
	LineTo(hdc, x + 165 * scale, y - 175 * scale);
	LineTo(hdc, x + 165 * scale, y - 130 * scale);
	
	//уничтожим созданные объекты
	DeleteObject(pen);
	DeleteObject(color);
}
void rich_ship::window(int r, int g, int b) {
	ship::window(r, g, b);
	//добавим иллюминатор
	HBRUSH color = CreateSolidBrush(RGB(r, g, b));
	HRGN window = CreateEllipticRgn(x + 90 * scale, y - 115 * scale, x + 120 * scale, y - 85 * scale); 
	FillRgn(hdc, window, color);

	//уничтожим созданные объекты
	DeleteObject(color);
}
void rich_ship::show(void) {
	visible = true;
	body(212, 34, 6, 255);
	bow(212, 34, 6, 255);
	deck(242, 177, 46, 255);
	pipe(242, 177, 46, 255);
	window(255, 255, 255);
}

//rich_shipv2::rich_shipv2(int initx, int inity, double initscale) : rich_ship(initx, inity, initscale)
//{	x = initx; y = inity; scale = 1.2 * initscale;	}
//
// void rich_shipv2::pipe(int r, int g, int b, int outline) {
//	 //добавим вторую трубу
//	 HPEN pen = CreatePen(PS_INSIDEFRAME, 2, RGB(outline, outline, outline));
//	 SelectObject(hdc, pen);
//	 HBRUSH color = CreateSolidBrush(RGB(r, g, b));//голубой
//	 POINT polygon4[8] = { x + 135 * scale,y - 130 * scale,x + 135 * scale,y - 175 * scale,x + 165 * scale,y - 175 * scale,x + 165 * scale,y - 130 * scale }; //координаты трубы
//	 HRGN tube = CreatePolygonRgn(polygon4, 4, 1);
//	 FillRgn(hdc, tube, color);
//	 MoveToEx(hdc, x + 135 * scale, y - 130 * scale, NULL);
//	 LineTo(hdc, x + 135 * scale, y - 175 * scale);
//	 LineTo(hdc, x + 165 * scale, y - 175 * scale);
//	 LineTo(hdc, x + 165 * scale, y - 130 * scale);
//
//	 //уничтожим созданные объекты
//	 DeleteObject(pen);
//	 DeleteObject(color);
//	}

//void rich_ship::hide(void) {
//	visible = false;
//	ship::body(12, 12, 12, 12);
//	ship::bow(12, 12, 12, 12);
//	ship::deck(12, 12, 12, 12);
//	pipe(12, 12, 12, 12);
//
//}

/*---------------------------------------------*/
/*         МЕТОДЫ КЛАССА wrecked_ship          */
/*---------------------------------------------*/
wrecked_ship::wrecked_ship(int initx, int inity, double initscale) :ship(initx, inity, initscale) 
{	x = initx; y = inity; scale = initscale; }
void wrecked_ship::body(int r, int g, int b, int outline) {
	ship::body(r, g, b, outline);
	//добавим контур правой части корпуса
	HPEN pen = CreatePen(PS_INSIDEFRAME, 2, RGB(outline, outline, outline));
	SelectObject(hdc, pen);

	MoveToEx(hdc, x + 250 * scale, y, NULL);
	LineTo(hdc, x + 250 * scale, y - 75 * scale);
	DeleteObject(pen);
}
//void wrecked_ship::show(void) {
//	visible = true;
//	body(61, 70, 205, 255);
//	ship::deck(113, 147, 205, 255);
//}
//void wrecked_ship::hide(void) {
//	visible = false;
//	body(12, 12, 12, 12);
//	ship::deck(12, 12, 12, 12);
//}

/*---------------------------------------------*/
/*            МЕТОДЫ КЛАССА item               */
/*---------------------------------------------*/
item::item(int initx, int inity, double initscale) : point(initx, inity) 
{	x = initx;	y = inity;	scale = initscale;}
void item::moveto(int newx, int newy) {
	hide();  //hide по текущим координатам
	x = newx;
	y = newy;
	if (x > 900) x -= 900;
	if (y > 600) y -= 600;
	if (x -150 < 0) x = 900;
	if (y - 80 < 0) y += 520;
	show(); //показать по новым координатам
}
void item::expand(double delta) //увеличить радиус
{
	hide(); //спрятать текущий объект
	scale += delta; //change 
	if (delta < 0) //для отриц приращения 
		delta = 0.1;
	show(); //показать новый объект
}

/*---------------------------------------------*/
/*            МЕТОДЫ КЛАССА bomb               */
/*---------------------------------------------*/
bomb::bomb(int initx, int inity, double initscale) : item(initx, inity, initscale) 
{	x = initx;	y = inity;	scale = initscale; }
void bomb::show() {
	visible = true;
	HBRUSH red = CreateSolidBrush(RGB(133, 9, 9));//выбираем цвет
	POINT polygon2[12] = { x + 33,y - 70,x + 37,y - 70,x + 35,y - 80,x + 39,y - 80,x + 37,y - 90,x + 41,y - 90 };
	HRGN circ = CreateEllipticRgn(x, y-50*scale, x + 50 * scale, y);
	FillRgn(hdc, circ, red);

	DeleteObject(red);
}
void bomb::hide() {
	visible = false;
	HBRUSH back = CreateSolidBrush(RGB(12, 12, 12));//фон
	HRGN circ = CreateEllipticRgn(x, y - 50 * scale , x + 50 * scale, y);
	FillRgn(hdc, circ, back);

	DeleteObject(back);
}

/*---------------------------------------------*/
/*           МЕТОДЫ КЛАССА medcine             */
/*---------------------------------------------*/
medcine::medcine(int initx, int inity, double initscale) : item(initx, inity, initscale) 
{	x = initx;	y = inity;	scale = initscale; }
void medcine::show() {
	visible = true;
	//выбираем цвета
	HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));

	POINT polygon1[8] = { x,y,x,y - 50 * scale,x + 70 * scale,y - 50 * scale,x + 70 * scale,y }; //координаты аптечки
	POINT polygon2[24] = { x + 10 * scale,y - 20 * scale,
		x + 30 * scale,y - 20 * scale, x + 30 * scale,y - 10 * scale,x + 40 * scale,y - 10 * scale,	x + 40 * scale,y - 20 * scale,x + 60 * scale,y - 20 * scale,
		x + 60 * scale,y - 30 * scale,x + 40 * scale,y - 30 * scale,x + 40 * scale,y - 40 * scale,x + 30 * scale,y - 40 * scale,x + 30 * scale,y - 30 * scale,
		x + 10 * scale,y - 30 * scale }; //крест

	HRGN box = CreatePolygonRgn(polygon1, 4, 1);
	HRGN cross = CreatePolygonRgn(polygon2, 12, 1);
	FillRgn(hdc, box, white);
	FillRgn(hdc, cross, red);

	//уничтожим созданные объекты
	DeleteObject(red);
	DeleteObject(white);
}
void medcine::hide() {
	visible = false;
	HBRUSH back = CreateSolidBrush(RGB(12, 12, 12));//фон
	POINT polygon1[8] = { x,y,x,y - 50 * scale,x + 70 * scale,y - 50 * scale,x + 70 * scale,y }; 
	HRGN box = CreatePolygonRgn(polygon1, 4, 1);
	FillRgn(hdc, box, back);

	DeleteObject(back);
}

/*---------------------------------------------*/
/*          МЕТОДЫ КЛАССА treasure             */
/*---------------------------------------------*/
treasure::treasure(int initx, int inity, double initscale) : item(initx, inity, initscale) 
{	x = initx;	y = inity;	scale = initscale; }
void treasure::show() {
	visible = true;
	//выбираем цвета
	HBRUSH yellow = CreateSolidBrush(RGB(235, 212, 12));
	HBRUSH brown = CreateSolidBrush(RGB(61, 27, 7));

	POINT polygon1[8] = { x,y - 40 * scale,x + 20 * scale,y - 60 * scale,x + 80 * scale,y - 60 * scale,x + 60 * scale,y - 40 * scale }; //координаты сокровища
	POINT polygon2[12] = { x ,y ,x + 60 * scale,y,x + 80 * scale,y - 20 * scale ,	x + 80 * scale,y - 60 * scale,x + 60 * scale,y - 40 * scale, x ,y - 40 * scale }; //сундук
	POINT polygon3[8] = { x + 20 * scale,y - 60 * scale, x + 10 * scale,y - 80 * scale, x + 70 * scale,y - 80 * scale,x + 80 * scale,y - 60 * scale }; //крышка

	HRGN money = CreatePolygonRgn(polygon1, 4, 1);
	HRGN box = CreatePolygonRgn(polygon2, 6, 1);
	HRGN top = CreatePolygonRgn(polygon3, 4, 1);

	FillRgn(hdc, money, yellow);
	FillRgn(hdc, box, brown);
	FillRgn(hdc, top, brown);

	//уничтожим созданные объекты
	DeleteObject(yellow);
	DeleteObject(brown);
}
void treasure::hide() {
	visible = false;
	HBRUSH back = CreateSolidBrush(RGB(12, 12, 12));//фон

	POINT polygon1[8] = { x,y - 40 * scale,x + 20 * scale,y - 60 * scale,x + 80 * scale,y - 60 * scale,x + 60 * scale,y - 40 * scale }; //координаты сокровища
	POINT polygon2[12] = { x ,y ,x + 60 * scale,y,x + 80 * scale,y - 20 * scale ,	x + 80 * scale,y - 60 * scale,x + 60 * scale,y - 40 * scale, x ,y - 40 * scale }; //сундук
	POINT polygon3[8] = { x + 20 * scale,y - 60 * scale, x + 10 * scale,y - 80 * scale, x + 70 * scale,y - 80 * scale,x + 80 * scale,y - 60 * scale }; //крышка

	HRGN money = CreatePolygonRgn(polygon1, 4, 1);
	HRGN box = CreatePolygonRgn(polygon2, 6, 1);
	HRGN top = CreatePolygonRgn(polygon3, 4, 1);


	FillRgn(hdc, money, back);
	FillRgn(hdc, box, back);
	FillRgn(hdc, top, back);

	DeleteObject(back);
}