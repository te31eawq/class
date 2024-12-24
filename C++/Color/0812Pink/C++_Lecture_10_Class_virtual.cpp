#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shape
{
public:
	Shape() { cout << "Shape::Ctor" << endl; }
	virtual ~Shape() { cout << "Shape::Dtor" << endl; }
	virtual void Attack() { cout << "Shape::ShapeInfo" << endl; }
};

class Circle :public Shape
{
public:
	Circle() { cout << "Circle::Ctor" << endl; }
	~Circle() { cout << "Circle::Dtor" << endl; }
	void Attack() override
	{
		cout << "Circle::ShapeInfo" << endl;
		cout << "    +  " << endl;
		cout << "  +   +  " << endl;
		cout << " +     +  " << endl;
		cout << " +     +  " << endl;
		cout << "  +   +  " << endl;
		cout << "    +  " << endl;
	}
};

class Rectangle :public Shape
{
public:
	Rectangle() { cout << "Rectangle::Ctor" << endl; }
	~Rectangle() { cout << "Rectangle::Dtor" << endl; }
	void Attack() override
	{
		cout << "Rectangle::ShapeInfo" << endl;
	}
};

int main()
{
	Shape* pShape = nullptr;
	Circle *pCircle	= new Circle;
	pShape = dynamic_cast<Shape*>(pCircle);

	pShape->Attack();

	if (pShape != nullptr)
	{
		delete pShape;
		pShape = nullptr;
	}


	if (false)
	{

		Shape shape;
		Circle circle;
		Rectangle rectangle;


		Shape* pShape = nullptr;
		pShape = &rectangle;
		pShape->Attack();
		pShape = &shape;
		pShape->Attack();
		pShape = &circle;
		pShape->Attack();

		Shape* pArr[2] = { new Circle, new Rectangle };

		for (size_t i = 0; i < 2; i++)
		{
			pArr[i]->Attack();
		}


		for (size_t i = 0; i < 2; i++)
			delete pArr[i];
	}
	return 1;
}