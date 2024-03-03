#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

typedef struct stock{

    char nume[30];
    char an[30];
    int disponibilitate;
    int numar_locuri;
    int pret_per_zi;

}stock;

void load_cars_stock(){



}

void sageata(int pozitie_curenta, int pozitie_cautata){

    if(pozitie_curenta == pozitie_cautata)
        printf("=> ");
    else 
        printf("   ");

}
void loopsageata(int *pos,int min,int max){
    
    if(*pos > max) 
        *pos = min;

    if(*pos < min) 
        *pos = max;

}

void optiuni(int *pos,int *stopexec,int *next_pos,int *previous_pos,int meniuprincipal){

    int tasta = getch();

    if(tasta == 72) /// sageata sus
        (*pos)--;

    if(tasta == 80) /// sageata jos
        (*pos)++;

    if(tasta == 77) /// drepta
        *next_pos = 1;

    if(tasta == 27 && meniuprincipal == 1) /// Esc
        *stopexec = 1;

    if(tasta == 75) /// left
        *previous_pos = 1;

}

void adaugare_actualizare_stergere(){

    int newpointer = 1;
    int stopexec = 0,nextpage = 0,previouspage = 0;

    while(stopexec == 0){

        system("cls");
        printf("=== MENIU ADMIN ===\n");
        sageata(newpointer, 1);
        printf("1. Adauga autovehicul\n");

        sageata(newpointer,2);
        printf("2. Actualizare autovehicul\n");

        sageata(newpointer,3);
        printf("3. Stergere autovehicul\n\n");
        
        printf("Apasa ESC pentru a iesi");

        loopsageata(&newpointer,1,3);

        optiuni(&newpointer,&stopexec,&nextpage,&previouspage,1);

    }

}
void solve_admin_page(){

    char pass[26];
    printf("=== MENIU ADMIN ===\n");
    int try = 3;
    int intrat = 0;
    while(try > 0 && intrat == 0){
        printf("Introdu parola de administrator (exit pentru a iesi): ");
        scanf("%s",pass);
        if(strcmp(pass,"admin123") == 0){
            intrat = 1;
            system("cls");
            adaugare_actualizare_stergere();
        }
        else if(strcmp(pass,"exit") == 0)
            return;
        else{
            printf("Parola gresita\n");
            printf("Incercari ramase %d\n\n",try - 1);
        }
        try--;
    }
    if(!intrat){
        printf("\nParola gresita, se reintoarce la ecran principal in 5 sau mai putine secunde");
        Sleep(5600);
    }
    
}
void cauta_autovehicul(){

    char numeveh[26];
    printf("=== MENIU USER ===\n");
    printf("Introdu marca autoturismului dorit (exit pentru a iesi): ");
    scanf("%s",numeveh);
    
    if(strcmp(numeveh,"exit") == 0)
        return;
    else{

    }        


    exit(0);

}

int main(){

    int stopexec = 0;
    int pos = 1,nextpage,previouspage;
    stock Masini[1005];
    load_cars_stock();

    while(stopexec == 0){  

        
        system("cls");
        printf("=== MENIU PRINCIPAL ===\n");

        sageata(pos, 1);
        printf("1. Functii Autoturisme [ADMIN ONLY]\n");

        sageata(pos,2);
        printf("2. Cautare Autoturism\n");

        sageata(pos,3);
        printf("3. Vizualizare Autoturisme\n");

        sageata(pos,4);
        printf("4. Rezervari\n\n");

        printf("Apasa ESC pentru a iesi");
        
        loopsageata(&pos,1,4);

        optiuni(&pos,&stopexec,&nextpage,&previouspage,1);

        if(nextpage == 1){
            nextpage = 0;
            if(pos == 1){
                pos = 0;
                system("cls");
                solve_admin_page();
            }
            else if(pos == 2){
                pos = 0;
                system("cls");
                cauta_autovehicul();
            }
            else if(pos == 3){
                return 0;
            }
            else if(pos == 3){
                return 0;
            }
        }
    }


    return 0;
}
