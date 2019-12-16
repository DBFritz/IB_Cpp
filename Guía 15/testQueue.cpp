#include<iostream>
#include<string>
#include "queue.h"

using namespace std;

int main()
{
	Queue<string,5> *miQueue = new Queue<string,5>();

// 	string *inf;   tenes que tener un string, NO un puntero a string, ese string es el que va a recibir el valor
	string inf;
	string *int1 = new string("a");
	string *int2 = new string("b");
	miQueue->push(*int1);
	miQueue->push(*int2);
	miQueue->pop(&inf);     // le pasas la direccion de donde meter lo sacado
	cout<<inf<<endl;
	miQueue->pop(&inf);     // le pasas la direccion de donde meter lo sacado 
	cout<<inf<<endl;
	delete miQueue;
	delete int1;
	delete int2;
	return 0;
}
