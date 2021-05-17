#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void nacteni();
void vypis();
void preklad();
void test();
void nahodny_test();

int main() {
	
	int volba, konec;
	
	do {
	
		
		printf("\n");
		printf("\n Nabidka:");
		printf("\n");
		printf("\n   0) Konec");
		printf("\n   1) Pridani slov");
		printf("\n   2) Vypis vsech slov v slovniku");
		printf("\n   3) Preklad slova CZ>EN & EN>CZ");
		printf("\n   4) Test slov z urcite lekce");
		printf("\n   5) Nahodne testovani z celeho slovniku");
		printf("\n");
		printf("\n   > ");
		fflush(stdin);
		scanf("%d",&volba);
		
		switch(volba) {
			case 1: {
				nacteni();
				konec = 0;
				break;
			}
			
			case 2: {
				vypis();
				konec = 0;
				break;
			}
			
			case 3: {
				preklad();
				konec = 0;
				break;
			}
			
			case 4: {
				test();
				konec = 0;
				break;
			}
			
			case 5: {
				nahodny_test();
				konec = 0;
				break;
			}
			
			case 0: {
				konec = 1;
				break;
			}
			
			default: {
				konec = 0;
			}
		}
		
		
	} while (konec != 1);
	
	return 0;
}

void nacteni() {
	
	FILE *f, *x;
	int konec=0, stejne;
	char lekce[50], lekce_old[50], cz[40], en[40],cz_old[40], en_old[40], radek[80], * p;
	
	f = fopen("slovicka.txt", "a+");
	
	system("cls");
	
	do {
		
		konec = 0;
		
		system("cls");
		
		printf("Zadej id lekce: ");
		fflush(stdin);
		gets(lekce);
		
		printf("Zadej cesky nazev: ");
		fflush(stdin);
		scanf("%s",&cz);
		
		printf("Zadej anglicky nazev: ");
		fflush(stdin);
		scanf("%s",&en);
		
		x = fopen("slovicka.txt", "r");
		
		while (fgets(radek, 80, x) != NULL) {
		
			p = strtok(radek, "/");
			
			strcpy(lekce_old,p);
			
			p = strtok(NULL, "/");
			
			strcpy(cz_old,p);
			
			p = strtok(NULL, "\n");
			
			strcpy(en_old,p);
			
			if (strcmp(cz_old,cz) == 0) { 
			
				stejne=1;
			
			}
		}	
		
		if (stejne == 0) {
				
			fflush(stdin);
			fprintf(f, "%s/%s/%s\n", lekce, cz, en);
			
		} else {
			
			printf("\nToto slovicko se jiz ve slovniku vyskytuje!");
			
		}
		
		printf("\n\nDalsi slovicko? \n1 - ANO \n0 - NE \n\n> ");
		fflush(stdin);
		scanf("%d",&konec);
		
	} while ( konec != 0);
	
	fclose(f);
	
	fclose(x);
	
}

void vypis() {
	
	FILE *f;
	
	char s;
	int i;
	
	f = fopen("slovicka.txt", "r");
	
	system("cls");
	
	if (f == NULL) {
	 
        printf("Soubor nemuze byt otevren \n"); 
        exit(0); 
        
    } else {
    
		printf("\n\nObsah slovniku je: \n\n");
		printf(" Lekce \tCZ \tEN \n\n");	
    }
    
    i = 0;
    
    do {
    	
    	s = fgetc(f);
    	
    	if (s == '/') {
    		
    		printf("\t");
    		
    	} else if ( s >= '0' && s <= '9' ) {
			
				printf(" %c", s);    
						
    		} else {
    			
    			printf ("%c", s); 
    		}
    	
    } while(s != EOF);
	
	fclose(f);

}

void preklad() {
	
	char radek[80], * p, cz[10], en[10], lekce[10], hl[10];
	int nasel, chyba;
	
	FILE *f;
	
	f = fopen("slovicka.txt", "r");
	
	system("cls");
	
	fflush(stdin);
	
	printf("\nZadej slovo: ");
	gets(hl);
	
	nasel = 1;
	
	while (fgets(radek, 80, f) != NULL && nasel != 2) {
		
		p = strtok(radek, "/");
		
		strcpy(lekce,p);
		
		p = strtok(NULL, "/");
		
		strcpy(cz,p);
		
		p = strtok(NULL, "\n");
		
		strcpy(en,p);
		
		if ((strcmp(hl,lekce) == 0) || (strcmp(hl,cz) == 0) || (strcmp(hl,en) == 0)) {
			
			if (strcmp(hl,cz) == 0) {
				
				printf("\nPeklad slova %s je %s", hl, en);
				printf("\n'- Lekce %s\n", lekce);
				
			} 
			
			if (strcmp(hl,en) == 0) {
				
				printf("\nPeklad slova %s je %s", hl, cz);
				printf("\n'- Lekce %s\n", lekce);
				
			}
			
			nasel = 2;
			

		} else {
			
			if (chyba != 2) {
			
				chyba = 1;
				
			}
			 
		}
		
	}
	
	if (chyba == 1 && nasel != 2) {
			
		printf("\nNenasel jsem hledane slovo\n");
		chyba = 2;
		
	}
	
	fclose(f);
}

void test() {
	
	char radek[80], * p, cz[10], en[10], lekce[10], hl[10], prk[20];
	int slovicko=0, i=0;
	
	
	FILE *f;
	
	f = fopen("slovicka.txt", "r");
	
	system("cls");
	
	fflush(stdin);
	
	printf("\nZ jake lekce chces byt zkousen: ");
	gets(hl);
	
	while (fgets(radek, 80, f) != NULL) {
		
		p = strtok(radek, "/");
		
		strcpy(lekce,p);
		
		p = strtok(NULL, "/");
		
		strcpy(cz,p);
		
		p = strtok(NULL, "\n");
		
		strcpy(en,p);
		
		if (strcmp(hl,lekce) == 0) {
				
			slovicko++;
			
		} 
		
	}
	
	if (slovicko == 0) {
		
		printf("\nZ teto lekce te nemuzu vyzkouset, nemam slovicka, z teto lekce!");
	
	} else {
		
		printf("\nNalezl jsem %d slov\n\n",slovicko);
		
		f = fopen("slovicka.txt", "r");
		
		while (fgets(radek, 80, f) != NULL) {
		
			p = strtok(radek, "/");
			
			strcpy(lekce,p);
			
			p = strtok(NULL, "/");
			
			strcpy(cz,p);
			
			p = strtok(NULL, "\n");
			
			strcpy(en,p);
			
			if (strcmp(hl,lekce) == 0) {
					
				printf("Jakej je preklad slova %s? > \n",cz);
				gets(prk);
				
				if (strcmp(prk,en) != 0) {
					
					printf("\n\n\tSpatne!\n\n");
					
					system("pause");
					
					system("cls");
					
				} else {
					
					printf("\n\n\tSpravne!\n\n");
					
					system("pause");
					
					system("cls");
					
				}
			} 
		
		}
		
	}
	
	fclose(f);
	
}

void nahodny_test() {
	
	char radek[80], * p, cz[10], en[10], lekce[10], hl[10], prk[20];
	int slovicko=0, i=0, cislo, x=0, o=0;
	int nahodna_cisla[100];
	
	FILE *f;
	
	f = fopen("slovicka.txt", "r");
	
	system("cls");
	
	while (fgets(radek, 80, f) != NULL) {
		
		p = strtok(radek, "/");
		
		strcpy(lekce,p);
		
		p = strtok(NULL, "/");
		
		strcpy(cz,p);
		
		p = strtok(NULL, "\n");
		
		strcpy(en,p);
		
		slovicko++;
		
	}
	
	if (slovicko == 0) {
		
		printf("\nVe slovniku neni zadne slovo!");
		fclose(f);
		
		return;
		
	}
	
	srand((unsigned) time(0));
	
	nahodna_cisla[0] = rand() % slovicko+1;
	
	for (i=0;i < slovicko; i++) {
		
		cislo = rand() % slovicko+1;
		
		nahodna_cisla[i] = cislo;
		
		for(x=0;x < i; x++) {
			
			if (cislo == nahodna_cisla[x]) {
				cislo = rand() % slovicko+1;
				nahodna_cisla[i] = cislo;
				i=0;
			}
			
		}
		
	}
	
	for (i=0;i < slovicko; i++) {
	
		f = fopen("slovicka.txt", "r");
		
		o=0;
		
		while (fgets(radek, 80, f) != NULL) {
			
			p = strtok(radek, "/");
			
			strcpy(lekce,p);
			
			p = strtok(NULL, "/");
			
			strcpy(cz,p);
			
			p = strtok(NULL, "\n");
			
			strcpy(en,p);
			
			o++;
			
			if (o == nahodna_cisla[i]) {
				
				system("cls");
				
				printf("Jakej je preklad slova %s? > \n",cz);
				gets(prk);
				
				if (strcmp(prk,en) != 0) {
					
					printf("\n\n\tSpatne!\n\n");
					
					system("pause");
					
				} else {
					
					printf("\n\n\tSpravne!\n\n");
					
					system("pause");
					
				}
			}
			
		
		}
		
	}
	
	fclose(f);
	
}
