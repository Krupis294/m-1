#include "library.h"

int main() {
	int select;
	Snemovna snemovna;
	
	do {
		cout << endl << " 1  - Ulozit do souboru";
        cout << endl << " 2  - Nacist ze souboru";
        cout << endl << " 3  - Pridat poslance";
        cout << endl << " 4  - Vypsat seznam";
        cout << endl << " 5  - Vyhledat poslance";
        cout << endl << " 6  - Seradit poslance podle veku";
        cout << endl << " 7  - Smazat poslance";
        cout << endl << " 8  - Upravit poslance";
        cout << endl << " 9  - Nejmladsi poslanec";
        cout << endl << " 10 - Nejstarsi poslanec";
        cout << endl << " 0  - Konec";
        cout << endl << "";
        cout << endl << " -> ";
        cin >> select;
        
        switch(select) {
        	
        	// AddToFile
        	case 1: {
        		system("cls");
        		
        		if (snemovna.saveToFile()) {
        			cout << endl << " Snemovna byla ulozena do souboru." << endl;
				} else {
					cout << endl << " Snemovnu se nepodarilo ulozit do souboru." << endl;
				}
				
				break;
			}
			
			// LoadFromFile
			case 2: {
				system("cls");
				
				if (snemovna.loadFromFile()) {
					cout << endl << " Snemovna byla nactena ze souboru." << endl;
				} else {
					cout << endl << " Snemovnu se nepodarilo nacist ze souboru." << endl;
				}
				
				break;
			}
			
			// Add
			case 3: {
				string name;
				string side;
				int age;
				
				cout << endl << endl <<" Zadej jmeno poslance: " << endl;
				cout << "  -> ";
				fflush(stdin);
				getline(cin, name);
				
				cout << endl << " Zadej stranu poslance: " << endl;
				cout << "  -> ";
				fflush(stdin);
				getline(cin, side);
				
				cout << endl << " Zadej vek poslance: " << endl;
				cout << "  -> ";
				fflush(stdin);
				cin >> age;
				
				Poslanec p(name, side, age);
				
				system("cls");
				
				if (snemovna.add(p)) {
					cout << endl << " Poslanec byl pridan" << endl;
				} else {
					cout << endl << " Snemovna je plna, poslance se nepodarilo pridat";
				}
				
				break;
			}
			
			// Print
			case 4: {
				system("cls");
				cout << endl;
				snemovna.print();
				
				break;
			}
			
			case 5: {
				int sel = 0;
				
				system("cls");
				
				do {
					cout << endl << " Vyhledat pomoci:";
					cout << endl << " 1 - Jmena";
        			cout << endl << " 2 - Strany";	
        			cout << endl << " 3 - Veku";
        			cout << endl << " 0 - Zrusit";
        			cout << endl << "";
					cout << endl << " -> ";
        			cin >> sel;
        			
        			if (!snemovna.search(sel)) {
        				system("cls");
        				
        				cout << endl << " Nenasel jsem zadneho poslance." << endl;
        				sel = 0;
					} else {
						if (sel == 1 || sel == 2 || sel == 3) {
							sel = 0;
						}
					}
				} while (sel != 0);
				
				if (sel = 0) {
					system("cls");
				}
				
				break;
			}
			
			// Order by age
			case 6: {
				if (snemovna.order()) {
					system("cls");
					cout << endl << " Snemovna byla serazena podle veku." << endl << endl;
				}
				
				snemovna.print();
				
				break;
			}
			
			// Delete
			case 7: {
				system("cls");
				cout << endl;
				snemovna.print();
				cout << endl;
				
				if (snemovna.del()) {
					cout << endl << " Poslanec byl uspesne smazan. " << endl;
				} else {
					cout << endl << " Poslanec nebyl nalezen." << endl;
				}
				
				break;
			}
			
			// Edit
			case 8: {
				system("cls");
				cout << endl;
				snemovna.print();
				cout << endl;
				
				if (snemovna.edit()) {
					cout << endl << " Poslanec byl uspesne upraven. " << endl;
				} else {
					cout << endl << " Poslanec nebyl upraven." << endl;
				}
				
				break;
			}
			
			// Lowest age
			case 9: {
				system("cls");
				cout << endl;
				
				Poslanec p = snemovna.lowestAge();
				
				cout << " Nejmladsi poslanec:" << endl;
				cout << " -> " << p.getName() << " " << p.getSide() << " " << p.getAge() << endl;
				
				break;
			}
			
			// Highest age
			case 10: {
				system("cls");
				cout << endl;
				
				Poslanec p = snemovna.highestAge();
				
				cout << " Nejstarsi poslanec:" << endl;
				cout << " -> " << p.getName() << " " << p.getSide() << " " << p.getAge() << endl;
				
				break;
			}
			
			case 0: {
				break;
			}
			
			default: {
				system("cls");
			}
		}
	} while (select != 0);
	
	return 0;
}
