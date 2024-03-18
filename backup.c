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

void auto_load(){

    FILE *fp = fopen("masini.txt","w");
    fprintf(fp,"%s","");
    fclose(fp);

    FILE *fp2 = fopen("masini.txt","a");

    for(int i = 1 ; i <= nrMasini ; ++i){
        fprintf(fp2,"%s %s %s %s %s",Masini[i].nume,Masini[i].model,Masini[i].an,
        Masini[i].disponibilitare,Masini[i].pret_per_zi_ron);
    }

    fclose(fp2);
                
    load_from_file_car_stock();

}

void sageata(int pozitie_curenta, int pozitie_cautata){

    if(pozitie_curenta == pozitie_cautata)
        printf(" =>   ");
    else 
        printf("");

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

        fprintf(fp,"%s",newcar);
        fprintf(fp,"%s","\n");
        fclose(fp);    

        Sleep(400);

        system("cls");
        printf("Vehiculul \"%s\" a fost adaugat cu succes !",newcar);

        Sleep(2500);
        
    }
}

void veh_update_status(){

    int stop_update = 0,pointer_update = 0,next_page_update = 0;
    while(stop_update == 0){

        system("cls");

        printf("=== MENIU UPDATE ===\n");

        for(int i = 1 ; i <= nrMasini ; ++i){

            sageata(pointer_update, i);

            printf("%d. %s %s %s %s %s\n",i,Masini[i].nume,Masini[i].model,Masini[i].an,
            Masini[i].disponibilitare,Masini[i].pret_per_zi_ron);

        }

        printf("\nApasa ESC pentru a iesi");
        loopsageata(&pointer_update,0,nrMasini + 1);
        optiuni(&pointer_update,&stop_update,&next_page_update);

        if(next_page_update == 1 && pointer_update >= 1 && pointer_update <= nrMasini){

            next_page_update = 0;

            system("cls");

            int ok = 0;
            if(strcmp(Masini[pointer_update].disponibilitare,"Disponibil") == 0){
                strcpy(Masini[pointer_update].disponibilitare,"Indisponibil");
                ok = 1;
            }
            else
                strcpy(Masini[pointer_update].disponibilitare,"Disponibil");
                    
            if(ok == 1)
                printf("Status schimbat din \"Disponibil\" in \"Indisponibil\" pentru vehiculul \"%s %s %s\" ",
                Masini[pointer_update].nume,Masini[pointer_update].model,Masini[pointer_update].an);
            else if(ok == 0)
                printf("Status schimbat din \"Indisponibil\" in \"Disponibil\" pentru vehiculul \"%s %s %s\" ",
                Masini[pointer_update].nume,Masini[pointer_update].model,Masini[pointer_update].an);

            auto_load();

            Sleep(2500);
                    
        }
    }
}

int verifpret(char pret[]){

    for(int i = 0 ; pret[i] ; ++i)
        if(pret[i] < '0' || pret[i] > '9')
            return 0;
    
    return 1;

}
int getprice(char pret[]){

    int x = 0;
    for(int i = 0 ; i < strlen(pret) - 1 ; ++i)
        x = x * 10 + (pret[i] - '0');
    
    return x;

}

void veh_update_price(){

    int stop_update = 0,pointer_update = 0,next_page_update = 0;
    while(stop_update == 0){

        system("cls");

        printf("=== MENIU UPDATE ===\n");

        for(int i = 1 ; i <= nrMasini ; ++i){

            sageata(pointer_update, i);

            printf("%d. %s %s %s %s %s\n",i,Masini[i].nume,Masini[i].model,Masini[i].an,
            Masini[i].disponibilitare,Masini[i].pret_per_zi_ron);

        }

        printf("\nApasa ESC pentru a iesi");
        loopsageata(&pointer_update,0,nrMasini + 1);
        optiuni(&pointer_update,&stop_update,&next_page_update);

        if(next_page_update == 1 && pointer_update >= 1 && pointer_update <= nrMasini){

            int iesi = 0;
            next_page_update = 0;

            system("cls");

            int value = getprice(Masini[pointer_update].pret_per_zi_ron);

            printf("Introdu noul pret/zi al vehiculului \"%s %s %s\". Pret curent : %d (exit pentru a iesi) : ",Masini[pointer_update].nume,
            Masini[pointer_update].model,Masini[pointer_update].an,value);

            char pret[26];
            int ok = 0;
            while(ok == 0){
                scanf("%s", pret);
                getchar();
                printf("\n");

                if(strcmp("exit",pret) == 0){
                    iesi = 1;
                    break;
                }
                
                ok = verifpret(pret);
                if(ok == 0)
                    printf("Pret in format incorect, reincearca : ");
            }

            if(iesi == 0){
            
                strcpy(Masini[pointer_update].pret_per_zi_ron,pret);

                int undepun_n = strlen(pret);

                if(strlen(Masini[pointer_update].pret_per_zi_ron) < undepun_n)
                    undepun_n = strlen(Masini[pointer_update].pret_per_zi_ron);

                Masini[pointer_update].pret_per_zi_ron[undepun_n] = '\n';

                Masini[pointer_update].pret_per_zi_ron[undepun_n + 1] = '\0';
                
                auto_load();

                printf("Pret actualizat cu succes");

                Sleep(2500);
            }
                    
        }
    }
}

void actualizeaza_veh(){

    int stopexec_veh = 0,pointer = 0,next_page;
    
    while(stopexec_veh == 0){
        
        system("cls");

        printf("=== MENIU UPDATE ===\n");

        sageata(pointer,1);
        printf("1. Disponibilitate\n");
    
        sageata(pointer,2);
        printf("2. Pret\n\n");
        
        printf("Apasa ESC pentru a iesi");
        loopsageata(&pointer,0,3);

        optiuni(&pointer,&stopexec_veh,&next_page);

        if(next_page == 1 && pointer == 1){

            next_page = 0;
            system("cls");
            veh_update_status();
            
        }
        else if(next_page == 1 && pointer == 2){
            next_page = 0;
            system("cls");
            veh_update_price();
        }
    }
}
void sterge_veh(){

    int stopexec_veh = 0,pointer = 1,next_page;

    while(stopexec_veh == 0){

        system("cls");

        printf("=== MENIU DELETE ===\n");

        for(int i = 1 ; i <= nrMasini ; ++i){

            sageata(pointer, i);

            printf("%d. %s %s %s %s %s\n",i,Masini[i].nume,Masini[i].model,Masini[i].an,
            Masini[i].disponibilitare,Masini[i].pret_per_zi_ron);

        }
        printf("\nApasa ESC pentru a iesi");
        loopsageata(&pointer,0,nrMasini + 1);
        optiuni(&pointer,&stopexec_veh,&next_page);
    
        if(next_page == 1 && pointer >= 1 && pointer <= nrMasini){

            system("cls");

            next_page = 0;
            char saveforoutput[5][256];

            strcpy(saveforoutput[0],Masini[pointer].nume);
            strcpy(saveforoutput[1],Masini[pointer].model);
            strcpy(saveforoutput[2],Masini[pointer].an);
            strcpy(saveforoutput[3],Masini[pointer].disponibilitare);
            strcpy(saveforoutput[4],Masini[pointer].pret_per_zi_ron);

            saveforoutput[4][strlen(saveforoutput[4]) - 1] = 0;

            printf("Sunteti sigur ca doriti sa stergeti vehiculul \"%s %s %s %s %s\" (y/n) : ",saveforoutput[0],saveforoutput[1],
            saveforoutput[2],saveforoutput[3],saveforoutput[4]);

            char ch = getch();

            printf("%c\n\n", ch);
            

            if(ch == 'y'){

                for(int i = pointer ; i < nrMasini ; ++i){
                    strcpy(Masini[i].nume,Masini[i + 1].nume);
                    strcpy(Masini[i].model,Masini[i + 1].model);
                    strcpy(Masini[i].an,Masini[i + 1].an);
                    strcpy(Masini[i].disponibilitare,Masini[i + 1].disponibilitare);
                    strcpy(Masini[i].pret_per_zi_ron,Masini[i + 1].pret_per_zi_ron);

                }
                
                nrMasini--;

                auto_load();
                
                stopexec_veh = 1;

                printf("Vehiculul \"%s %s %s %s %s\" a fost sters cu succes ! ",saveforoutput[0],saveforoutput[1],saveforoutput[2]
                ,saveforoutput[3],saveforoutput[4]);

                Sleep(2500);
            }
            else{
                printf("Se reintoarce la ecran anterior...");
                Sleep(2000);
            }
        }   
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
                actualizeaza_veh();
            }
            else if(newpointer == 3){
                newpointer = 0;
                system("cls");
                if(nrMasini == 0){
                    printf("Inventar gol...");
                    Sleep(2500);
                }
                else
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
