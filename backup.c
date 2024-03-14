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

typedef struct om{

    char nume[30];
    char prenume[30];
    char durata_inchieriere_zile[30];
    char venit[30];

}om;

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

        int i = 0;
        while(1){
            pass[i] = getch();

            if(pass[i] == 13) 
                break;

            else if(i >= 1 && pass[i] == '\b'){
                printf("\b \b");
                i -= 2;
            }
            else
                printf("*");

            i++;
        }
        pass[i] = '\0';

        if(strcmp(pass,"admin123") == 0){
            intrat = 1;
            system("cls");
            printf("Informatii pentru membrii staff \n");
            printf("Sintaxa adaugare : NUME | MODEL | AN | DISPONIBIL/INDISPONIBIL | PRET_PER_ZI\n");
            printf("Se pune 1 singur spatiu intre campurile de completat al masinilor\n");
            printf("Pentru modele ce sunt compuse din mai multe cuvinte, se folosesc separatori (\"-\",\"_\")\n");
            printf("Orice neclaritate raportati la manager\n");
            printf("Aplicatia este in teste, pot aparea erori. Reporniti daca se blocheaza\n");
            printf("Parola si PIN-ul de admin se primesc fizic de la manager\n");
            printf("Daca introduceti codul PIN gresit sau parola apelati la supervizor pentru deblocare\n\n");


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
            printf("\nParola gresita\n");
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
    printf("Introdu Sintaxa (exit pentru a iesi): ");

    gets(newcar);
    
    if(strcmp("exit",newcar) == 0)
        return;
    
    else{

        FILE *fp = fopen("masini.txt","a");

        fprintf(fp,"%s\n",newcar);
        fclose(fp);    
        
    }
}

void actualizeaza_veh(){

    printf("%s","Se lucreaza");
    Sleep(2000);

}
void sterge_veh(){

    printf("%s","Se lucreaza");
    Sleep(2000);

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
                actualizeaza_veh();
            }
            else if(newpointer == 3){
                newpointer = 0;
                system("cls");
                sterge_veh();
            }
        }
    }
}
void solve_admin_page(){

    char pass[26];
    printf("=== MENIU ADMIN ===\n");
        if(blocheaza_stergere == 0){
        int try = 3;
        int intrat = 0;
        while(try > 0 && intrat == 0){
            printf("Introdu parola de administrator (exit pentru a iesi): ");

            int i = 0;
            while(1){
                pass[i] = getch();

                if(pass[i] == 13) 
                    break;

                else if(i >= 1 && pass[i] == '\b'){
                    printf("\b \b");
                    i -= 2;
                }
                else
                    printf("*");

                i++;
            }
            pass[i] = '\0';

            if(strcmp(pass,"admin123") == 0){
                intrat = 1;
                system("cls");
                adaugare_actualizare_stergere();
            }
            else if(strcmp(pass,"exit") == 0)
                return;
            else{
                printf("\nParola gresita\n");
                printf("Incercari ramase %d\n\n",try - 1);
            }
            try--;
        }
        if(!intrat){
            printf("\nParola gresita, se reintoarce la ecran principal in 5 sau mai putine secunde");
            Sleep(5600);
        }
    }
    else{
        printf("Functii blocate(PIN Gresit)");
        Sleep(3500);
    }

}
void listare_stoc_masini(int nrMasini,stock Masini[]){

    for(int i = 1 ; i <= nrMasini ; ++i){
        printf("%d. %s %s %s %s %s\n",i,Masini[i].nume,Masini[i].model,Masini[i].an,
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

    printf("%s","Se lucreaza");
    Sleep(2000);

}
void clear_data(){

    char pass[26];
    printf("=== MENIU ADMIN ===\n");
    int try = 3;
    int intrat = 0;
    while(try > 0 && intrat == 0){
        printf("Introdu parola de administrator (exit pentru a iesi): ");

        int i = 0;
        while(1){
            pass[i] = getch();

            if(pass[i] == 13) 
                break;

            else if(i >= 1 && pass[i] == '\b'){
                printf("\b \b");
                i -= 2;
            }
            else
                printf("*");

            i++;
        }
        pass[i] = '\0';

        if(strcmp(pass,"admin123") == 0){
            char ch;
            system("cls");
            printf("Sunteti sigur ca doriti eliminarea tuturor datelor din memorie ? (y/n) :");
            ch = getch();
            printf("%c",ch);
            if(ch == 'y'){
                char pin[25];
                printf("\nPentru siguranta introduceti codul PIN de admin (1 incercare, daca se gresete aplicatia blocheaza functia): ");

                int i = 0;
                while(1){
                    pin[i] = getch();
                    if(pin[i] == 13) 
                        break;
                    else if(i >= 1 && pin[i] == '\b'){
                        printf("\b \b");
                        i -= 2;
                    }
                    else
                        printf("*");

                    i++;
                }

                printf("\n");
                pin[i] = '\0';

                if(strcmp(pin,"0852") == 0){
                    FILE *fp = fopen("masini.txt","w");
                    fprintf(fp,"%s","");
                    load_from_file_car_stock();
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
            printf("\nParola gresita\n");
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

    FILE *check = fopen("status_functie_5.txt","r");
    if(fgetc(check) == -1){
        FILE *check2 = fopen("status_functie_5.txt","w");
        fprintf(check2,"%d",0);
        fclose(check2);
        fclose(check);
    }

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
        printf("2. Inchiriere\n");

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

        if(stopexec == 1){
            system("cls");
            printf("Sunteti sigur ca doriti sa inchideti aplicatia ? (y/n) :");
            char c = getch();
            if(c == 'y'){
                printf("\n\nAplicatia se va inchide in cateva secunde");
                Sleep(2600);
                stopexec = 1;
            }
            else
                stopexec = 0;
        }

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
                printf("Introduceti codul PIN (4 cifre / 0000 pentru revenire) : ");
                char PIN[5];
                int ok = 0;
                do{
                    int i = 0;
                    while(1){
                        PIN[i] = getch();

                        if(PIN[i] == 13) 
                            break;

                        else if(i >= 1 && PIN[i] == '\b'){
                            printf("\b \b");
                            i -= 2;
                        }
                        else
                            printf("*");

                        i++;
                    }
                    printf("\n");
                    PIN[i] = '\0';
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
                system("cls");
                printf("Functiile nu sunt blocate");
                Sleep(2500);
            }
            
        }
        FILE *pp = fopen("status_functie_5.txt","w");
        fprintf(pp,"%d",blocheaza_stergere);
        fclose(pp);
        
    }


    return 0;
}
/*
admin123
0852
1111

*/
