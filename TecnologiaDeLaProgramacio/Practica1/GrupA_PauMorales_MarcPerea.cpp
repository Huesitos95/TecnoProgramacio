// Contenidors STL
// 1- Vector, 2- Deque, 3- queue, 4- priority_queue, 5- stack, 6- list, 7- forward_list, 8- map i 9- set
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <forward_list>
#include <map>
#include <set>

//Constructores Vector
std::vector<int> A;           //vector de ints vacio
std::vector<int> B(5, 50);         //vector de 5 ints con valor 50
std::vector<int> C(B.begin(), B.end());      //vector de ints iterando en el vector B
std::vector<int> D(C);          //vector de ints copiando C
std::vector<int> E = { 1,2,3,4,5 };       //vector de ints que nosotros indicamos

//Constructores List
std::list<int> A6;
std::list<int> B6(5, 50);
std::list<int> C6(B6.begin(), B6.end());
std::list<int> D6(C6);
std::list<int> E6 = { 1,2,3,4,5 };

//Constructores Deque
std::deque<int> A2;                                // deque de entero vacio
std::deque<int> B2(4, 100);                        // deque de 4 enteros con valor 100
std::deque<int> C2(B2.begin(), B2.end());     // deque de enteros iterado sobre B2 
std::deque<int> D2(C2);          // una copia del B2
std::deque<int> E2{ 1,2,3,4,5 };       //deque de 5 enteros con los valores que le indicamos

//Constructores Queue
std::queue<int> A3;           // queue vacia
std::queue<int> B3(B2);          // queue inicializada a partir de una copia de deque
std::queue<int, std::list<int> > C3;      // queue vacia a partir de una list
std::queue<int, std::list<int> > D3(B6);     // queue copia de la lista B6

////Constructores Priority Queue
//std::queue<int> A3;           // queue vacia
//std::queue<int> B3(B2);          // queue inicializada a partir de una copia de deque
//std::queue<int, std::list<int> > C3;      // queue vacia a partir de una list
//std::queue<int, std::list<int> > D3(B6);     // queue copia de la lista B6


int main()
{
	//Comentar los contenedores que no se van a usar para evitar error de nomenclatura en los iteradores (se llaman igual en todos)

	//VECTOR
	std::cout << "Iteradores Vector" << '\n';
	std::cout << "Iteradores Begin" << '\n';
	for (std::vector<int>::iterator it = E.begin(); it != E.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "Iterador rBegin" << '\n';
	std::vector<int>::reverse_iterator rit = E.rbegin();
	for (; rit != E.rend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';

	std::cout << "Iterador cBegin" << '\n';
	for (auto it = E.cbegin(); it != E.cend(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "Iterador crBegin" << '\n';
	for (auto rit = E.crbegin(); rit != E.crend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';

	//DEQUE
	std::cout << "Iteradores Deque" << '\n';
	std::cout << "Iteradores Begin" << '\n';
	for (std::deque<int>::iterator it = E2.begin(); it != E2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "Iterador rBegin" << '\n';
	std::deque<int>::reverse_iterator rit = E2.rbegin();
	for (; rit != E2.rend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';

	std::cout << "Iterador cBegin" << '\n';
	for (auto it = E2.cbegin(); it != E2.cend(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "Iterador crBegin" << '\n';
	for (auto rit = E2.crbegin(); rit != E2.crend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';

	system("PAUSE");
}