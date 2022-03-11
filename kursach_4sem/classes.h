#pragma once
//насальный класс с координатами
class location {
protected:   //предостовляет возможность потомкам иметь
	int x;   //доступ к закрытым данным
	int y;
public:
	location(int initx, int inity) ; //costructor
	~location() {};                    //destructor
	int getx();                     //получить  х
	int gety();
	void setx(int newx) {x = newx;};  //изменить  х
	void sety(int newy) {y = newy;};

};// class location

class point : public location {                             
protected:
	bool visible;  //светится или нет
public:
	point(int initx, int inity);
	~point() {};
	bool isvisible(); //узнать светимость точки
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void moveto(int newx, int newy) = 0;

};//class point

//-----------------------------ОБЪЕКТ--------------------------//
//Основной класс "объект", который наследуют все корабли и препятсвия
//АБСТРАКТНЫЙ КЛАСС
//class object : public point {
//protected:
//	double scale;  //масштаб
//public:
//	object(int initx, int inity, double initscale);
//	~object() {};
//	//чистые виртуальные функции
//	virtual void show(void) = 0;
//	virtual void hide(void) = 0;
//	virtual void expand(double delta) = 0;
//	virtual void moveto(int newx, int newy) = 0;
//
//};
//-----------------------------КОРАБЛИ--------------------------//
//ИНТЕРФЕЙС
class iship {
	virtual void body(int r, int g, int b, int outline) = 0;  //корпус
	virtual void bow(int r, int g, int b, int outline) = 0;  //нос
	virtual void deck(int r, int g, int b, int outline) = 0;  //палуба
	virtual void pipe(int r, int g, int b, int outline) = 0;  //труба
	virtual void window(int r, int g, int b) = 0;  //иллюминатор
};
//Класс корабль без особенностей
class ship :public point, public iship {
protected:
	double scale;
public:
	ship(int initx, int inity, double initscale);
	~ship() {};
	virtual void moveto(int newx, int newy); //переместить точку
	virtual void drag(int step);
	virtual void body(int r, int g, int b, int outline);
	virtual void bow(int r, int g, int b, int outline);
	virtual void deck(int r, int g, int b, int outline);
	virtual void pipe(int r, int g, int b,int outline);
	virtual void window(int r, int g, int b);
	virtual void show(); //показать 
	virtual void hide(); //скрыть 
	virtual void expand(double delta); //увеличить 

};//class ship
//Класс корабль с сокровищами
class rich_ship :public ship {
public:
	rich_ship(int initx, int inity, double initscale);
	~rich_ship() {};
	virtual void show();
	//virtual void hide();
	virtual void pipe(int r, int g, int b, int outline);
	virtual void window(int r, int g, int b);
};
//Класс корабля для защиты
//class rich_shipv2 :public rich_ship {
//public:
//	rich_shipv2(int initx, int inity, double initscale);
//	~rich_shipv2() {};
//	//virtual void show();
//	//virtual void hide();
//	virtual void pipe(int r, int g, int b, int outline);
//	//virtual void window(int r, int g, int b);
//};
//Класс подорванный на бомбе корабль
class wrecked_ship :public ship {
public:
	wrecked_ship(int initx, int inity, double initscale);
	~wrecked_ship() {};
	virtual void body(int r, int g, int b, int outline);

	virtual void bow(int r, int g, int b, int outline) { return; };
	virtual void pipe(int r, int g, int b, int outline) { return; };
	virtual void window(int r, int g, int b) { return; };
	//virtual void show();
	//virtual void hide();
};

//---------------------------ПРЕПЯТСТВИЯ------------------------//
class item :public point {
protected:
	double scale;
public:
	item(int initx, int inity, double initscale);
	~item() {};
	virtual void moveto(int newx, int newy);
	virtual void expand(double delta);
};
//Класс бомба
class bomb :public item {
public:
	bomb(int initx, int inity, double initscale);
	~bomb() {};

	virtual void show(); //показать 
	virtual void hide(); //скрыть 
};
//Класс сокровища
class treasure :public item {
public:
	treasure(int initx, int inity, double initscale);
	~treasure() {};

	virtual void show(); //показать 
	virtual void hide(); //скрыть 
};
//Класс атечка
class medcine :public item {
public:
	medcine(int initx, int inity, double initscale);
	~medcine() {};

	virtual void show(); //показать 
	virtual void hide(); //скрыть 
};