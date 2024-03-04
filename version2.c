#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

typedef struct stock{

    char nume[30];
    char model[60];
    char an[30];
    char disponibilitare[30];
    char pret_per_zi_ron[30];

}stock;

stock Masini[1005];
int nrMasini;
int blocheaza_stergere;

void admin_help(){

    char pass[26];
    printf("=== MENIU ADMIN ===\n");
    int try = 3;
    int intrat = 0;
    while(try > 0 && intrat == 0){
        printf("Introdu parola de administrator (exit pentru a iesi): ");
        scanf("%s",pass);
        getchar();
        if(strcmp(pass,"admin123") == 0){
            intrat = 1;
            system("cls");
            printf("Informatii pentru membrii staff \n");
            printf("Sintaxa adaugare : NUME | MODEL | AN | DISPONIBIL/INDISPONIBIL | PRET_PER_ZI\n");
            printf("Se pune 1 singur spatiu intre campurile de completat al masinilor\n");
            printf("Pentru modele ce sunt compuse din mai multe cuvinte, se folosesc separatori (\"-\",\"_\")\n");
            printf("Nu aprobati contracte de inchiriere pentru salarii mai mici decat 1200 RON\n");
            printf("Orice neclaritate raportati la manager\n");
            printf("Aplicatia este in teste, pot aparea erori. Reporniti daca se blocheaza\n");
            printf("Parola si PIN-ul de admin se primesc fizic de la manager\n");
            printf("Nu introduceti date eronate, vor fi sterse si veti fi sanctionati\n\n");


            printf("Folositi \"exit\" pentru a iesi din programe\n\n");

            printf("\n--------------------------\nApasa ESC pentru a iesi...");
            char tasta = getch();

            while(tasta != 27)
                tasta = getch();
            
            if(tasta == 27)
                return;
        
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

void load_from_file_car_stock(){

    FILE *fp = fopen("masini.txt","r");
    char linie[256];
    char mat[256][256];
    nrMasini = 0;
    while(fgets(linie,256,fp) != NULL){

        //printf("%s",linie);
        strcpy(mat[++nrMasini],linie);
    
    }
    for(int i = 1 ; i <= nrMasini ; ++i){
        char *p = strtok(mat[i]," ");
        strcpy(Masini[i].nume,p);
        p = strtok(NULL," ");
        strcpy(Masini[i].model,p);
        p = strtok(NULL," ");
        strcpy(Masini[i].an,p);
        p = strtok(NULL," ");
        strcpy(Masini[i].disponibilitare,p);
        p = strtok(NULL," ");
        strcpy(Masini[i].pret_per_zi_ron,p);
    }
    
    fclose(fp);
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

void optiuni(int *pos,int *stopexec,int *next_pos){

    int tasta = getch();

    if(tasta == 72) /// sageata sus
        (*pos)--;

    if(tasta == 80) /// sageata jos
        (*pos)++;

    if(tasta == 77) /// drepta
        *next_pos = 1;

    if(tasta == 27) /// Esc
        *stopexec = 1;

}
void adauga_veh(){
    
    char newcar[256];
    printf("Introdu Sintaxa : ");

    gets(newcar);
    
    if(strcmp("exit",newcar) == 0)
        return;
    
    else{

        FILE *fp = fopen("masini.txt","a");

        fprintf(fp,"%s\n",newcar);
        fclose(fp);    
        
    }
}

void adaugare_actualizare_stergere(){

    int newpointer = 1;
    int stopexec = 0,nextpage = 0;

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

        loopsageata(&newpointer,0,4);

        optiuni(&newpointer,&stopexec,&nextpage);

        if(nextpage == 1){
            nextpage = 0;
            if(newpointer == 1){
                newpointer = 0;
                system("cls");
                adauga_veh();
                load_from_file_car_stock();
            }
            else if(newpointer == 2){
                newpointer = 0;
                system("cls");
            }
            else if(newpointer == 3){
                newpointer = 0;
                return;
            }
        }
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
        getchar();
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
void listare_stoc_masini(int nrMasini,stock Masini[]){

    for(int i = 1 ; i <= nrMasini ; ++i){
        printf("%s %s %s %s %s\n",Masini[i].nume,Masini[i].model,Masini[i].an,
        Masini[i].disponibilitare,Masini[i].pret_per_zi_ron);

    }
    printf("\n--------------------------\nApasa ESC pentru a iesi...");
    char tasta = getch();

    while(tasta != 27)
        tasta = getch();
            
    if(tasta == 27)
        return;

}
void inchiriaza_vehicul(){

    return;

}
void clear_data(){

    char pass[26];
    printf("=== MENIU ADMIN ===\n");
    int try = 3;
    int intrat = 0;
    while(try > 0 && intrat == 0){
        printf("Introdu parola de administrator (exit pentru a iesi): ");
        scanf("%s",pass);
        getchar();
        if(strcmp(pass,"admin123") == 0){
            char ch;
            system("cls");
            printf("Sunteti sigur ca doriti eliminarea tuturor datelor din memorie ? (y/n) :");
            ch = getch();
            printf("%c",ch);
            if(ch == 'y'){
                char pin[25];
                printf("\nPentru siguranta introduceti codul PIN de admin (1 incercare, daca se gresete aplicatia blocheaza functia): ");
                scanf("%s",pin);
                if(strcmp(pin,"0852") == 0){
                    FILE *fp = fopen("masini.txt","w");
                    fprintf(fp,"%s","");
                    printf("Fisierul a fost golit cu succes.\nSe revine la meniul principal in 5 sau mai putine secunde...");
                    Sleep(5600);
                    return;
                }
                else{
                    blocheaza_stergere = 1;
                    printf("PIN gresit, se revine la meniu principal");
                    Sleep(5600);
                    return;
                }
            }
            else{
                printf("\nFunctie anulata, se revine la ecranul principal...");
                Sleep(5600);
                return;
            }
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

int main(){

    system("cls");

    int stopexec = 0;
    int pos = 1,nextpage,previouspage;

    FILE *pp = fopen("status_functie_5.txt","r");
    fscanf(pp,"%d",&blocheaza_stergere);
    fclose(pp);

    load_from_file_car_stock();
    
    while(stopexec == 0){  

        system("cls");
        printf("=== MENIU PRINCIPAL ===\n");

        sageata(pos,1);
        printf("1. Vizualizare Autoturisme\n");

        sageata(pos,2);
        printf("2. Rezervari\n");

        sageata(pos, 3);
        printf("3. Functii Autoturisme [ADMIN ONLY]\n");

        sageata(pos, 4);
        printf("4. Admin Help [ADMIN ONLY]\n");

        sageata(pos, 5);
        printf("5. Golire Date [ADMIN ONLY]\n");

        sageata(pos, 6);
        printf("6. Deblocare aplicatie [ADMIN ONLY]\n\n");

        printf("Apasa ESC pentru a iesi");
        
        loopsageata(&pos,0,7);

        optiuni(&pos,&stopexec,&nextpage);

        if(nextpage == 1){
            nextpage = 0;
            if(pos == 1){
                pos = 0;
                system("cls");
                listare_stoc_masini(nrMasini,Masini);
                
            }
            else if(pos == 2){
                pos = 0;
                system("cls");
                inchiriaza_vehicul();
            }
            else if(pos == 3){
                pos = 0;
                system("cls");
                solve_admin_page();
            }
            else if(pos == 4){
                pos = 0;
                system("cls");
                admin_help();
            }
            else if(pos == 5 && blocheaza_stergere == 0){
                pos = 0;
                system("cls");
                clear_data();

                FILE *pp = fopen("status_functie_5.txt","w");
                fprintf(pp,"%d",blocheaza_stergere);
                fclose(pp);
                
            }
            else if(pos == 5 && blocheaza_stergere == 1){
                pos = 0;
                system("cls");
                printf("Functie blocata(PIN gresit)");

                FILE *pp = fopen("status_functie_5.txt","w");
                fprintf(pp,"%d",blocheaza_stergere);
                fclose(pp);

                Sleep(1500);
            }
            else if(pos == 6 && blocheaza_stergere == 1){
                pos = 0;
                system("cls");
                printf("=== MENIU ADMIN ===\n");
                printf("Functie destinata supervizorului/managerului pentru a putea debloca anumite functii\n");
                printf("Introduceti codul PIN (4 cifre / 0000 pentru revenire) :");
                char PIN[5];
                int ok = 0;
                do{
                    scanf("%s",PIN);
                    if(strcmp(PIN,"0000") == 0){
                        printf("Intoarcere la ecran principal...");
                        Sleep(5600);
                        ok = 1;
                    }
                    else{
                        if(strcmp(PIN,"1111") == 0){
                            printf("Functii deblocate!");
                            FILE *pp = fopen("status_functie_5.txt","w");
                            fprintf(pp,"%d",0);
                            blocheaza_stergere = 0;
                            ok = 1;
                            Sleep(2000);
                            
                        }
                        else
                            printf("PIN Gresit. Incearca din nou...\n");
                        
                    }
                }while(ok == 0);
            }
            else if(pos == 6 && blocheaza_stergere == 0){
                printf("Functiile nu sunt blocate");
                Sleep(2000);
            }
        }
    }


    return 0;
}