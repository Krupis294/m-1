#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct data {
	int id;
	char jmeno[8];
	int vek;
	struct data *next, *last;
} Tdata;

void add();
void remove();
void list();
void save();
void load();

Tdata *first = NULL;

int main() {
	int action = 0;
	
	do {
		printf("\n");
		printf(" Akce:\n");
		printf("  1 - Add \n");
		printf("  2 - Remove \n");
		printf("  3 - List \n");
		printf("  4 - Save \n");
		printf("  5 - Load \n");
		printf("  0 - Cancel\n"); 
		printf("\n");
		printf("   --> ");
		scanf("%d", &action);
		
		switch(action) {
			case 1: {
				printf("\n\n");
				
				add();
				
				break;
			}
			
			case 2: {
				printf("\n\n");
				
				remove();
				
				break;
			}
			
			case 3: {
				printf("\n\n");
				
				list();
				
				break;
			}
			
			case 4: {
				save();
				
				break;
			}
			
			case 5: {
				load();
				
				break;
			}
			
			default: {
				break;
			}
		}
	} while (action != 0);
}

void add() {
	Tdata *nev;
	nev = (Tdata*) malloc(sizeof(Tdata));
	nev->last = NULL;
	nev->next = NULL;
	
	printf(" Zadej id: ");
	scanf("%d", &nev->id);
	
	printf(" Zadej jmeno: ");
	scanf("%s", &nev->jmeno);
	
	printf(" Zadej vek: ");
	scanf("%d", &nev->vek);
	
	system("cls");
	
	printf("\n Zaznam pridan\n");
	printf("  -> %d\t%s\t%d\n", nev->id, nev->jmeno, nev->vek);
	printf("\n");
	
	if (first == NULL) {
		first = nev;
	} else {
		nev->next = first;
		first->last = nev;
		first = nev;
	}
}

void remove() {
	system("cls");
	
	int action = 0;
	
	do {
		printf("\n  Smazat podle: \n");
		printf("  1 - ID\n");
		printf("  2 - Jmena\n");
		printf("  0 - Cancel\n"); 
		printf("\n");
		printf("   --> ");
		scanf("%d",&action);
		
		switch(action) {
			case 1: {
				action = -1;
				int id = 0;
				
				printf("\n  ID: ");
				scanf("%d",&id);
				
				for (Tdata *data = first; data != NULL; data = data->next) {
					if (data->id == id) {
						action = 0;
						
						if (data->last == NULL && data->next == NULL) {
							first = NULL; 
							printf("NULL");
							break;
						}
						
						if (data->last == NULL) { // Prvni
							free(first);
							
							first = NULL;
							first = data->next;
							data->next->last = NULL;
							
						} else if (data->next == NULL) { // Posledni
							data->last->next = NULL;
							
							free(data);
						} else { // Mezi
							data->last->next = data->next;
							data->next->last = data->last;
						
							free(data);
						}
					}
					
					printf("  %d. %s - %d", data->id, data->jmeno, data->vek);
				}
				
				break;
			}
			
			case 2: {
				action = -1;
				char jmeno[8];
				
				printf("\n  Jmeno: ");
				scanf("%s",&jmeno);
				
				
				for (Tdata *data = first; data != NULL; data = data->next) {
					if (strcmp(data->jmeno,jmeno) == 0) {
						action = 0;
						
						if (data->last == NULL && data->next == NULL) {
							first = NULL; 
							printf("NULL");
							break;
						}
						
						if (data->last == NULL) { // Prvni
							free(first);
							
							first = NULL;
							first = data->next;
							data->next->last = NULL;
							
						} else if (data->next == NULL) { // Posledni
							data->last->next = NULL;
							
							free(data);
						} else { // Mezi
							data->last->next = data->next;
							data->next->last = data->last;
						
							free(data);
						}
					}
				}
				
				break;
			}
			
			case -1: {
				printf(" \n Zaznam nenalezen. \n");
			}
		}
	} while (action != 0);
}

void list() {
	system("cls");
	printf("\n Vypis:\n");
	
	for (Tdata *data = first; data != NULL; data = data->next) {
		printf("  %d. %s - %d\n", data->id, data->jmeno, data->vek);
	}
	
	printf("\n\n");
}

void save() {
	system("cls");
	
	FILE *f = fopen("save.dat","wb");
	
	for (Tdata *data = first; data != NULL; data = data->next) {
		fwrite(data,sizeof(Tdata),1,f);
	}
	
	fclose(f);	
}

void load() {
	system("cls");
	
	FILE *f = fopen("save.dat","rb");
	
	Tdata *nev;
	Tdata buff;
	
	first = NULL;
	
	while(fread(&buff,sizeof(Tdata),1,f) == 1) {
		nev = (Tdata*) malloc(sizeof(Tdata));
		*nev = buff;
		
		nev->last = NULL;
		nev->next = NULL;
			
		if (first == NULL) {
			first = nev;
		} else {
			nev->next = first;
			first->last = nev;
			first = nev;
		}
	}
	
	fclose(f);
}

