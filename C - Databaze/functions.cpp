#include "library.h"

Poslanec::Poslanec() {
	
}

Poslanec::Poslanec(string name) {
	this->name = name;
}

Poslanec::Poslanec(string name, string side) {
	this->name = name;
	this->side = side;
}

Poslanec::Poslanec(string name, string side, int age) {
	this->name = name;
	this->side = side;
	this->age = age;
}

Snemovna::Snemovna() {
	this->size = 0;
}

bool Snemovna::saveToFile() {
	ofstream file;
	
	file.open("data.txt");
	
	if (file.fail()) return false;
	
	for (int i = 0; i < size; i++) {
		file << poslanci[i].getName() << "|";
		file << poslanci[i].getSide() << "|";
		file << poslanci[i].getAge() << "|";
	}
	
	file.close();
	
	if (file.fail()) {
		return false;
	} else {
		return true;
	}
}

bool Snemovna::loadFromFile() {
	ifstream file;
	int i = 0;
	string radek = "";
	
	string name = "";
	string side = "";
	int age = 0;
		
	file.open("data.txt");
	
	if (file.fail()) return false;
	
	while(getline(file, radek, '|')) {		
		i++;
	
		switch(i) {
			case 1: {
				name = radek;
				break;
			}
			
			case 2: {
				side = radek;
				break;
			}
			
			case 3: {
				age = atoi(radek.c_str());
				
				Poslanec p(name, side, age);
				add(p);
				
				i = 0;
				
				break;
			}
		}
	}
	
	file.close();
	
	if (file.good()) {
		return false;
	} else {
		return true;
	}
}

bool Snemovna::add(Poslanec p) {
	if (N == size) {
		return false;
	} else {
		poslanci[size] = p;
		size++;
		
		return true;
	}
}

void Snemovna::print() {
	if (size == 0) {
		cout << " Snemovna je prazdna.." << endl;
	} else {
		cout << " List poslancu ve snemovne:" << endl;
	
		for (int i = 0; i < size; i++) {
			Poslanec p = poslanci[i];
			
			cout << "  " << i+1 << ". " << p.getName() << " - " << p.getSide() << " - " << p.getAge() << endl;
		}
	}
}

bool Snemovna::search(int by) {
	switch(by) {
		// Name
		case 1: {
			bool found = false;
			string str;
			
			cout << endl << " Zadej nazev poslance: " << endl;;
			cout << " -> ";
			fflush(stdin);
			getline(cin,str);
			
			for (int i = 0; i < size; i++) {
				if (poslanci[i].getName() == str) {
					if (!found) {
						system("cls");
						
						cout << endl << " Nalezeno:" << endl;
						found = true;
					}
					
					Poslanec p = poslanci[i];
					cout << " -> " << p.getName() << " " << p.getSide() << " " << p.getAge() << endl;
				}
			}
			
			return found;
		}
		
		// Side
		case 2: {
			bool found = false;
			string str;
			
			cout << endl << " Zadej stranu poslance: " << endl;;
			cout << " -> ";
			fflush(stdin);
			getline(cin,str);
			
			for (int i = 0; i < size; i++) {
				if (poslanci[i].getSide() == str) {
					if (!found) {
						system("cls");
						
						cout << endl << " Nalezeno:" << endl;
						found = true;
					}
					
					Poslanec p = poslanci[i];
					cout << " -> " << p.getName() << " " << p.getSide() << " " << p.getAge() << endl;
				}
			}
			
			return found;
		}
		
		// Age
		case 3: {
			bool found = false;
			int age;
			
			cout << endl << " Zadej vek poslance: " << endl;;
			cout << " -> ";
			fflush(stdin);
			cin >> age;
			
			for (int i = 0; i < size; i++) {
				if (poslanci[i].getAge() == age) {
					if (!found) {
						system("cls");
						
						cout << endl << " Nalezeno:" << endl;
						found = true;
					}
					
					Poslanec p = poslanci[i];
					cout << " -> " << p.getName() << " " << p.getSide() << " " << p.getAge() << endl;
				}
			}
			
			cout << endl;
			
			return found;
		}
		
		
		return false;
	}
	
	
	return true;
}

bool Snemovna::order() {
	int zamena;
	Poslanec pom;
	
	do {    
		zamena=0;         
       
		for (int i = 0; i < size-1; i++) {   
			if (poslanci[i].getAge() < poslanci[i+1].getAge()) {
				pom = poslanci[i];
				poslanci[i] = poslanci[i+1];
				poslanci[i+1] = pom;
				
				zamena = 1;
			}
		}    
    } while (zamena == 1);
}

bool Snemovna::del() {
	int id;
	bool smazano = false;
	Poslanec pom;
				
	cout << " Zadej id poslance pro smazani: " << endl;;
	cout << " -> ";
	cin >> id;
	
	for(int i = 0; i < size; i++) {
		if(i+1 == id) {
			smazano = true;
			
			for(int j = i; j < size - 1; j++) {
				pom = poslanci[j];
				poslanci[j] = poslanci[j+1];
				poslanci[j+1] = pom;
			}
			
			size--;
		}
	}
	
	system("cls");
				
	return smazano;
}

bool Snemovna::edit() {
	int id;
	bool edit = false;
				
	cout << " Zadej id poslance pro editaci: " << endl;;
	cout << " -> ";
	cin >> id;
	
	for(int i = 0; i < size; i++) {
		if(i+1 == id) {
			edit = true;
			
			string name;
			string side;
			int age;
			
			cout << endl << " Zadej nove jmeno:" << endl;
			cout << " -> ";
			fflush(stdin);
			getline(cin, name);
			
			cout << endl << " Zadej novou stranu:" << endl;
			cout << " -> ";
			fflush(stdin);
			getline(cin, side);
			
			cout << endl << " Zadej novy vek:" << endl;
			cout << " -> ";
			fflush(stdin);
			cin >> age;
			
			Poslanec neww(name, side, age);
			
			poslanci[i] = neww;
			
			system("cls");
			
			return edit;
		}
	}
	
	system("cls");
				
	return edit;
}

Poslanec Snemovna::lowestAge() {
	Poslanec p = poslanci[0];
	
	for (int i = 0; i < size; i++) {
		if (poslanci[i].getAge() < p.getAge()) {
			p = poslanci[i];
		}
	}
	
	return p;
}

Poslanec Snemovna::highestAge() {
	Poslanec p = poslanci[0];
	
	for (int i = 0; i < size; i++) {
		if (poslanci[i].getAge() > p.getAge()) {
			p = poslanci[i];
		}
	}
	
	return p;
}
