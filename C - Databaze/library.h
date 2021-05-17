#ifndef LIB
#define LIB

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

#define N 50

using namespace std;

class Poslanec {
	private:
		string name;
		string side;
		int age;
		
	public:
		Poslanec();
		Poslanec(string name);
		Poslanec(string name, string side);
		Poslanec(string name, string side, int age);
		
		string getName() { return name; }
		string getSide() { return side; }
		int getAge() { return age; }
};

class Snemovna {
	private:
		Poslanec poslanci[N];
		int size;
		
	public:
		Snemovna();
		
		int getSize() { return size; }
		
		bool loadFromFile();
		bool saveToFile();
		bool add(Poslanec p);
		void print();
		bool search(int by);
		bool order();
		bool del();
		bool edit();
		Poslanec lowestAge();
		Poslanec highestAge();
};

#endif
