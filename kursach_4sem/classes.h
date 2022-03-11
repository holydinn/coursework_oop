#pragma once
//��������� ����� � ������������
class location {
protected:   //������������� ����������� �������� �����
	int x;   //������ � �������� ������
	int y;
public:
	location(int initx, int inity) ; //costructor
	~location() {};                    //destructor
	int getx();                     //��������  �
	int gety();
	void setx(int newx) {x = newx;};  //��������  �
	void sety(int newy) {y = newy;};

};// class location

class point : public location {                             
protected:
	bool visible;  //�������� ��� ���
public:
	point(int initx, int inity);
	~point() {};
	bool isvisible(); //������ ���������� �����
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void moveto(int newx, int newy) = 0;

};//class point

//-----------------------------������--------------------------//
//�������� ����� "������", ������� ��������� ��� ������� � ����������
//����������� �����
//class object : public point {
//protected:
//	double scale;  //�������
//public:
//	object(int initx, int inity, double initscale);
//	~object() {};
//	//������ ����������� �������
//	virtual void show(void) = 0;
//	virtual void hide(void) = 0;
//	virtual void expand(double delta) = 0;
//	virtual void moveto(int newx, int newy) = 0;
//
//};
//-----------------------------�������--------------------------//
//���������
class iship {
	virtual void body(int r, int g, int b, int outline) = 0;  //������
	virtual void bow(int r, int g, int b, int outline) = 0;  //���
	virtual void deck(int r, int g, int b, int outline) = 0;  //������
	virtual void pipe(int r, int g, int b, int outline) = 0;  //�����
	virtual void window(int r, int g, int b) = 0;  //�����������
};
//����� ������� ��� ������������
class ship :public point, public iship {
protected:
	double scale;
public:
	ship(int initx, int inity, double initscale);
	~ship() {};
	virtual void moveto(int newx, int newy); //����������� �����
	virtual void drag(int step);
	virtual void body(int r, int g, int b, int outline);
	virtual void bow(int r, int g, int b, int outline);
	virtual void deck(int r, int g, int b, int outline);
	virtual void pipe(int r, int g, int b,int outline);
	virtual void window(int r, int g, int b);
	virtual void show(); //�������� 
	virtual void hide(); //������ 
	virtual void expand(double delta); //��������� 

};//class ship
//����� ������� � �����������
class rich_ship :public ship {
public:
	rich_ship(int initx, int inity, double initscale);
	~rich_ship() {};
	virtual void show();
	//virtual void hide();
	virtual void pipe(int r, int g, int b, int outline);
	virtual void window(int r, int g, int b);
};
//����� ������� ��� ������
//class rich_shipv2 :public rich_ship {
//public:
//	rich_shipv2(int initx, int inity, double initscale);
//	~rich_shipv2() {};
//	//virtual void show();
//	//virtual void hide();
//	virtual void pipe(int r, int g, int b, int outline);
//	//virtual void window(int r, int g, int b);
//};
//����� ����������� �� ����� �������
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

//---------------------------�����������------------------------//
class item :public point {
protected:
	double scale;
public:
	item(int initx, int inity, double initscale);
	~item() {};
	virtual void moveto(int newx, int newy);
	virtual void expand(double delta);
};
//����� �����
class bomb :public item {
public:
	bomb(int initx, int inity, double initscale);
	~bomb() {};

	virtual void show(); //�������� 
	virtual void hide(); //������ 
};
//����� ���������
class treasure :public item {
public:
	treasure(int initx, int inity, double initscale);
	~treasure() {};

	virtual void show(); //�������� 
	virtual void hide(); //������ 
};
//����� ������
class medcine :public item {
public:
	medcine(int initx, int inity, double initscale);
	~medcine() {};

	virtual void show(); //�������� 
	virtual void hide(); //������ 
};