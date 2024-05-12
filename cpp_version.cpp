#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

using namespace std;

class stock{

    char nume[30];
    char model[60];
    char an[30];
    char disponibilitate[30];
    char pret_per_zi_ron[30];
public:
    
    stock();
    stock(char[],char[],char[],char[],char[]);
    friend ostream & operator << (ostream &, const stock &);
    char *get_dispon(){
        return disponibilitate;
    }
    char *get_nume(){
        return nume;
    }
    char *get_model(){
        return model;
    }
    char *get_an(){
        return an;
    }
    char *get_pret(){
        return pret_per_zi_ron;
    }
    friend void change_disp(stock &,const char[]);
    friend void change_price(stock &,const char []);
};

stock::stock(){

    strcpy(this->nume,"");
    strcpy(this->model,"");
    strcpy(this->an,"");
    strcpy(this->disponibilitate,"");
    strcpy(this->pret_per_zi_ron,"");

}

stock::stock(char nume[],char model[],char an[],char disponibilitate[],char pret_per_zi_ron[]){

    strcpy(this->nume,nume);
    strcpy(this->model,model);
    strcpy(this->an,an);
    strcpy(this->disponibilitate,disponibilitate);
    strcpy(this->pret_per_zi_ron,pret_per_zi_ron);

}

ostream & operator << (ostream &st, const stock &x){
    
    st << x.nume << ' ' << x.model << ' ' << x.an << ' ' << x.disponibilitate << ' ' << x.pret_per_zi_ron;
    return st;
    
}
void change_disp(stock &x,const char s[]){

    strcpy(x.disponibilitate,s);

}
void change_price(stock &x,const char s[]){

    strcpy(x.pret_per_zi_ron,s);

}
typedef struct om{

    char user[256];
    char durata_inchieriere_zile[30];
    char telefon[30];
    char masina_nume[30];
    char model[30];
    char an[30];
    char pret[30];

}om;

stock Masini[1005];
om Oameni[1005];
int nrMasini,nrOameni;
int blocheaza_stergere;

void coloredtext(WORD Culoare,const char* text){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, Culoare);
    
    cout << text;

    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void admin_help(){

    char pass[26];
    
    coloredtext(FOREGROUND_GREEN,"=== MENIU ADMIN ===\n");
    int trys = 3;
    int intrat = 0;
    while(trys > 0 && intrat == 0){
        cout << "Introdu parola de administrator (exit pentru a iesi): ";

        int i = 0;
        while(1){
            pass[i] = getch();

            if(pass[i] == 13) 
                break;

            else if(i >= 1 && pass[i] == '\b'){
                cout <<"\b \b";
                i -= 2;
            }
            else
                coloredtext(FOREGROUND_RED,"*");

            i++;
        }
        pass[i] = '\0';

        if(strcmp(pass,"admin123") == 0){
            intrat = 1;
            system("cls");
            coloredtext(FOREGROUND_RED,"Informatii pentru membrii staff \n");
            printf("Sintaxa adaugare : NUME | MODEL | AN | DISPONIBIL/INDISPONIBIL | PRET_PER_ZI\n");
            printf("Se pune 1 singur spatiu intre campurile de completat al masinilor\n");
            printf("Pentru modele ce sunt compuse din mai multe cuvinte, se folosesc separatori (\"-\",\"_\")\n");
            printf("Orice neclaritate raportati la manager\n");
            printf("Aplicatia este in teste, pot aparea erori. Reporniti daca se blocheaza\n");
            printf("Parola si PIN-ul de admin se primesc fizic de la manager\n");
            coloredtext(FOREGROUND_RED,"Daca introduceti codul PIN gresit sau parola apelati la supervizor pentru deblocare\n\n");

            coloredtext(FOREGROUND_GREEN,"Folositi \"exit\" pentru a iesi din programe\n\n");
            

            printf("\n--------------------------\n");
            coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
            char tasta = getch();

            while(tasta != 27)
                tasta = getch();
            
            if(tasta == 27)
                return;
        
        }
        else if(strcmp(pass,"exit") == 0)
            return;
        else{
            coloredtext(FOREGROUND_RED,"\nParola gresita !\n");
            printf("Incercari ramase %d\n\n",trys - 1);
        }
        trys--;
    }
    if(!intrat){
        coloredtext(FOREGROUND_RED,"\nParola gresita, se reintoarce la ecran principal in 5 sau mai putine secunde");
        Sleep(5600);
    }

}

void load_from_file_car_stock(){

    ifstream fp("masini.txt");

    if(!fp){
        coloredtext(FOREGROUND_RED,"Fisierul masini.txt nu este creat !");
        Sleep(5000);
        fp.close();
        exit(0);
    }
    else{
        char linie[256];
        char mat[256][256];
        nrMasini = 0;
        while(fp.getline(linie,255)){

            //printf("%s",linie);
            strcpy(mat[++nrMasini],linie);
        
        }
        for(int i = 1 ; i <= nrMasini ; ++i){
            char *p = strtok(mat[i]," ");
            char nume[50],model[50],an[50],dispon[50],pret[50];
            strcpy(nume,p);
            p = strtok(NULL," ");
            strcpy(model,p);
            p = strtok(NULL," ");
            strcpy(an,p);
            p = strtok(NULL," ");
            strcpy(dispon,p);
            p = strtok(NULL," ");
            strcpy(pret,p);

            Masini[i] = stock(nume,model,an,dispon,pret);

        }
        
        fp.close();
    }
}
void load_from_file_people(){

    ifstream fp2("rent.txt");
    char linie[256];
    char mat[256][256];
    nrOameni = 0;

    if(!fp2){
        coloredtext(FOREGROUND_RED,"Fisierul rent.txt nu este creat !");
        Sleep(5000);
        fp2.close();
        exit(0);
    }
    else{
        while(fp2.getline(linie,255)){

            //printf("%s",linie);
            strcpy(mat[++nrOameni],linie);
        
        }
        for(int i = 1 ; i <= nrOameni ; ++i){
            char *p = strtok(mat[i]," ");
            strcpy(Oameni[i].user,p);
            p = strtok(NULL," ");
            strcpy(Oameni[i].telefon,p);
            p = strtok(NULL," ");
            strcpy(Oameni[i].durata_inchieriere_zile,p);
            p = strtok(NULL," ");
            
        }
        fp2.close();
    }
}

void auto_load(){

    FILE *fp = fopen("masini.txt","w");
    fprintf(fp,"%s","");
    fclose(fp);

    ofstream fp2("masini.txt");

    for(int i = 1 ; i <= nrMasini ; ++i){
        fp2 << Masini[i] << '\n';
    }

    fp2.close();
                
    load_from_file_car_stock();

}
void auto_load_users_passwords(int nr,char useri[][256],char parole[][256]){

    FILE *fp = fopen("users.txt","w");
    fprintf(fp,"%s","");
    fclose(fp);
 
    FILE *fp2 = fopen("users.txt","a");

    for(int i = 1 ; i <= nr ; ++i)
        fprintf(fp2,"%s",useri[i]);
    

    fclose(fp2);

    fp = fopen("passwords.txt","w");
    fprintf(fp,"%s","");
    fclose(fp);
 
    fp2 = fopen("passwords.txt","a");

    for(int i = 1 ; i <= nr ; ++i)
        fprintf(fp2,"%s",parole[i]);
    

    fclose(fp2);

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
        char aux[256];
        strcpy(aux,"Vehiculul \"");
        strcat(aux,newcar);
        strcat(aux,"\" a fost adaugat cu succes !");
        coloredtext(FOREGROUND_GREEN,aux);
        

        Sleep(2500);
        
    }
}

void veh_update_status(){

    int stop_update = 0,pointer_update = 1,next_page_update = 0;
    int pagina = 1;
    while(stop_update == 0){

        system("cls");

        coloredtext(FOREGROUND_GREEN,"=== MENIU UPDATE ===\n");
        
        for(int i = 5 * (pagina - 1) + 1 ; i <= min(5 * pagina,nrMasini) ; ++i){

            int auxi = i % 5;
            if(auxi == 0)
                auxi = 5;

            sageata(pointer_update,auxi);

            cout << i << ". " << Masini[i] << "\n\n";
    
        }
        printf("\nPagina %d",pagina);
        printf("\n--------------------------\n");
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        loopsageata(&pointer_update,0,min(6,nrMasini - 5 * (pagina - 1) + 1));
        
        char tasta = getch();

        if(tasta == 13)
            next_page_update = 1;
        else if(pagina > 1 && tasta == 75)
            pagina--,pointer_update = 1;
        else if((5 * (pagina + 1) <= nrMasini || nrMasini - (5 * pagina) > 0) && tasta == 77)
            pagina++,pointer_update = 1;
        else if(tasta == 80)
            pointer_update++;
        else if(tasta == 72)
            pointer_update--;
        else if(tasta == 27)
            stop_update = 1;

        system("cls");

        if(next_page_update == 1 && pointer_update >= 1 && pointer_update <= 5){

            next_page_update = 0;

            int pointer_adevarat = 5 * (pagina - 1) + pointer_update;

            system("cls");

            int ok = 0;
            if(strcmp(Masini[pointer_adevarat].get_dispon(),"Disponibil") == 0){
                change_disp(Masini[pointer_adevarat],"Indisponibil");
    
                ok = 1;
            }
            else
                change_disp(Masini[pointer_adevarat],"Disponibil");
                    
            if(ok == 1){
                char aux[256];
                strcpy(aux,"Status schimbat din \"Disponibil\" in \"Indisponibil\" pentru vehiculul ");
                strcat(aux,Masini[pointer_adevarat].get_nume());
                strcat(aux," ");
                strcat(aux,Masini[pointer_adevarat].get_model());
                strcat(aux," ");
                strcat(aux,Masini[pointer_adevarat].get_an());
                
                coloredtext(FOREGROUND_GREEN,aux);
            }
            else if(ok == 0){
                char aux[256];
                strcpy(aux,"Status schimbat din \"Indisponibil\" in \"Disponibil\" pentru vehiculul ");
                strcat(aux,Masini[pointer_adevarat].get_nume());
                strcat(aux," ");
                strcat(aux,Masini[pointer_adevarat].get_model());
                strcat(aux," ");
                strcat(aux,Masini[pointer_adevarat].get_an());
                
                coloredtext(FOREGROUND_GREEN,aux);
            }

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

    int stop_update = 0,pointer_update = 1,next_page_update = 0;
    int pagina = 1;

    while(stop_update == 0){

        system("cls");

        coloredtext(FOREGROUND_GREEN,"=== MENIU UPDATE ===\n");
        for(int i = 5 * (pagina - 1) + 1 ; i <= min(5 * pagina,nrMasini) ; ++i){

            int auxi = i % 5;
            if(auxi == 0)
                auxi = 5;

            sageata(pointer_update,auxi);

            cout << i << ". " << Masini[i] << "\n\n";

        }
        printf("\nPagina %d",pagina);
        printf("\n--------------------------\n");
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        loopsageata(&pointer_update,0,min(6,nrMasini - 5 * (pagina - 1) + 1));
        
        char tasta = getch();

        if(tasta == 13)
            next_page_update = 1;
        else if(pagina > 1 && tasta == 75)
            pagina--,pointer_update = 1;
        else if((5 * (pagina + 1) <= nrMasini || nrMasini - (5 * pagina) > 0) && tasta == 77)
            pagina++,pointer_update = 1;
        else if(tasta == 80)
            pointer_update++;
        else if(tasta == 72)
            pointer_update--;
        else if(tasta == 27)
            stop_update = 1;

        system("cls");

        if(next_page_update == 1 && pointer_update >= 1 && pointer_update <= nrMasini){

            int iesi = 0;
            next_page_update = 0;
            int pointer_adevarat = 5 * (pagina - 1) + pointer_update;

            system("cls");

            int value = getprice(Masini[pointer_adevarat].get_pret());

            printf("Introdu noul pret/zi al vehiculului \"%s %s %s\". Pret curent : %d (exit pentru a iesi) : "
            ,Masini[pointer_adevarat].get_nume(),Masini[pointer_adevarat].get_model(),Masini[pointer_adevarat].get_an(),value);

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
                    coloredtext(FOREGROUND_RED,"Pret in format incorect, reincearca : ");
            }

            if(iesi == 0){
                
                change_price(Masini[pointer_adevarat],pret);
            
                int undepun_n = strlen(pret);

                if(strlen(Masini[pointer_adevarat].get_pret()) < undepun_n)
                    undepun_n = strlen(Masini[pointer_adevarat].get_pret());

                Masini[pointer_adevarat].get_pret()[undepun_n] = '\n';

                Masini[pointer_adevarat].get_pret()[undepun_n + 1] = '\0';
                
                auto_load();

                coloredtext(FOREGROUND_GREEN,"Pret actualizat cu succes ! ");

                Sleep(2500);
            }
                    
        }
    }
}

void actualizeaza_veh(){

    int stopexec_veh = 0,pointer = 1,next_page;
    
    while(stopexec_veh == 0){
        
        system("cls");

        coloredtext(FOREGROUND_GREEN,"=== MENIU UPDATE ===\n");

        sageata(pointer,1);
        printf("1. Disponibilitate\n");
    
        sageata(pointer,2);
        printf("2. Pret\n\n");
        
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
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

    int pagina = 1;

    while(stopexec_veh == 0){

        system("cls");

        coloredtext(FOREGROUND_GREEN,"=== MENIU DELETE ===\n");
    
        for(int i = 5 * (pagina - 1) + 1 ; i <= min(5 * pagina,nrMasini) ; ++i){


            int auxi = i % 5;
            if(auxi == 0)
                auxi = 5;

            sageata(pointer,auxi);

            cout << i << ". " << Masini[i] << "\n\n";

        }
        printf("\nPagina %d",pagina);
        printf("\n--------------------------\n");
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        loopsageata(&pointer,0,min(6,nrMasini - 5 * (pagina - 1) + 1));
        
        char tasta = getch();

        if(tasta == 13)
            next_page = 1;
        else if(pagina > 1 && tasta == 75)
            pagina--,pointer = 1;
        else if((5 * (pagina + 1) <= nrMasini || nrMasini - (5 * pagina) > 0) && tasta == 77)
            pagina++,pointer = 1;
        else if(tasta == 80)
            pointer++;
        else if(tasta == 72)
            pointer--;
        else if(tasta == 27)
            stopexec_veh = 1;

        system("cls");
    
        if(next_page == 1 && pointer >= 1 && pointer <= 5){

            system("cls");

            int pointer_adevarat = 5 * (pagina - 1) + pointer;

            next_page = 0;
            char saveforoutput[5][256];

            strcpy(saveforoutput[0],Masini[pointer_adevarat].get_nume());
            strcpy(saveforoutput[1],Masini[pointer_adevarat].get_model());
            strcpy(saveforoutput[2],Masini[pointer_adevarat].get_an());
            strcpy(saveforoutput[3],Masini[pointer_adevarat].get_dispon());
            strcpy(saveforoutput[4],Masini[pointer_adevarat].get_pret());

            saveforoutput[4][strlen(saveforoutput[4]) - 1] = 0;
            
            cout << "Sunteti sigur ca doriti sa stergeti vehiculul";
            cout << Masini[pointer_adevarat] << "(y/n) :";
            
            char ch = getch();

            printf("%c\n\n", ch);
            

            if(ch == 'y'){

                for(int i = pointer_adevarat ; i < nrMasini ; ++i)
                    Masini[i] = Masini[i + 1];
                
                nrMasini--;

                auto_load();
                
                stopexec_veh = 1;

                char aux[256];
                strcpy(aux,"Vehiculul \"");
                strcat(aux,saveforoutput[0]);
                strcat(aux," ");
                strcat(aux,saveforoutput[1]);
                strcat(aux," ");
                strcat(aux,saveforoutput[2]);
                strcat(aux," ");
                strcat(aux,saveforoutput[3]);
                strcat(aux," ");
                strcat(aux,saveforoutput[4]);
                strcat(aux,"\" a fost sters cu succes ! ");

                coloredtext(FOREGROUND_GREEN,aux);

                Sleep(2500);
            }
            else{
                printf("Se reintoarce la ecran anterior...");
                Sleep(2000);
            }
        }   
    }
}
void del_user(){

    int stopexec = 0,pointer = 1,next_page;

    int pagina = 1;

    char useri[256][256];
    char parole[256][256];
    char linie[256];
    int nr = 0,nr2 = 0;

    FILE *fp = fopen("users.txt","r");
    FILE *fp2 = fopen("passwords.txt","r");

    while(fgets(linie,256,fp) != NULL){

        strcpy(useri[++nr],linie);

    }
    while(fgets(linie,256,fp2) != NULL){

        strcpy(parole[++nr2],linie);

    }

    fclose(fp);
    fclose(fp2);
    
    while(stopexec == 0){

        system("cls");

        coloredtext(FOREGROUND_GREEN,"=== MENIU DELETE ===\n");

        for(int i = 5 * (pagina - 1) + 1 ; i <= min(5 * pagina,nr) ; ++i){

            int auxi = i % 5;
            if(auxi == 0)
                auxi = 5;

            sageata(pointer,auxi);

            printf("%d. %s",i,useri[i]);

        }
        printf("\nPagina %d",pagina);
        printf("\n--------------------------\n");
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        loopsageata(&pointer,0,min(6,nr - 5 * (pagina - 1) + 1));
        
        char tasta = getch();

        if(tasta == 13)
            next_page = 1;
        else if(pagina > 1 && tasta == 75)
            pagina--,pointer = 1;
        else if((5 * (pagina + 1) <= nr || nr - (5 * pagina) > 0) && tasta == 77)
            pagina++,pointer = 1;
        else if(tasta == 80)
            pointer++;
        else if(tasta == 72)
            pointer--;
        else if(tasta == 27)
            stopexec = 1;

        system("cls");
    
        if(next_page == 1 && pointer >= 1 && pointer <= 5){

            next_page = 0;

            system("cls");

            int pointer_adevarat = 5 * (pagina - 1) + pointer;

            char saveforoutput[30];

            strcpy(saveforoutput,useri[pointer_adevarat]);

            saveforoutput[strlen(saveforoutput) - 1] = 0;

            printf("Sunteti sigur ca doriti sa stergeti user-ul \"%s\" (y/n) : ", saveforoutput);

            char ch = getch();

            printf("%c\n\n", ch);

    
            if(ch == 'y'){

                for(int i = pointer_adevarat ; i < nr ; ++i)
                    strcpy(useri[i],useri[i + 1]);
                
                for(int i = pointer_adevarat ; i < nr ; ++i)
                    strcpy(parole[i],parole[i + 1]);
                
                nr--;
                auto_load_users_passwords(nr,useri,parole);

                stopexec = 1;

                char aux[256];
                strcpy(aux,"User-ul \"");
                strcat(aux,saveforoutput);
                strcat(aux,"\" a fost sters cu succes ! ");
                coloredtext(FOREGROUND_GREEN,aux);

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

        coloredtext(FOREGROUND_GREEN,"=== MENIU ADMIN ===\n");
        sageata(newpointer, 1);
        printf("1. Adauga autovehicul\n");

        sageata(newpointer,2);
        printf("2. Actualizare autovehicul\n");

        sageata(newpointer,3);
        printf("3. Stergere autovehicul\n");

        sageata(newpointer,4);
        printf("4. Stergere User\n\n");
        
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");

        loopsageata(&newpointer,0,5);

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
                    coloredtext(FOREGROUND_RED,"Inventar gol...");
                    Sleep(2500);
                }
                else
                    sterge_veh();
                
            }
            else if(newpointer == 4){
                system("cls");
                del_user();
            }
        }
    }
}
void solve_admin_page(){

    char pass[26];
    coloredtext(FOREGROUND_GREEN,"=== MENIU ADMIN ===\n");
        if(blocheaza_stergere == 0){
        int trys = 3;
        int intrat = 0;
        while(trys > 0 && intrat == 0){
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
                    coloredtext(FOREGROUND_RED,"*");

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
                coloredtext(FOREGROUND_RED,"\nParola gresita\n");
                printf("Incercari ramase %d\n\n",trys - 1);
            }
            trys--;
        }
        if(!intrat){
            coloredtext(FOREGROUND_RED,"\nParola gresita, se reintoarce la ecran principal in 5 sau mai putine secunde");
            Sleep(5600);
        }
    }
    else{
        coloredtext(FOREGROUND_RED,"Functii blocate(PIN Gresit)");
        Sleep(3500);
    }

}
void listare_stoc_masini(int pagina,int nrMasini,stock Masini[]){

    while(1){

        system("cls");

        for(int i = 5 * (pagina - 1) + 1 ; i <= min(5 * pagina,nrMasini) ; ++i){
            cout << i << ". " << Masini[i] << "\n\n";
        }

        printf("\nPagina %d",pagina);
        printf("\n--------------------------\n");
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        char tasta = getch();

        if(pagina > 1 && tasta == 75)
            pagina--;
        else if((5 * (pagina + 1) <= nrMasini || nrMasini - (5 * pagina) > 0) && tasta == 77)
            pagina++;
        else if(tasta == 27)
            return;

    }

}

void crypt(char pass[]){

    int skip = strlen(pass) / 2;
    for(int i = 1 ; i <= skip ; ++i){
        char ch = pass[0];
        for(int j = 0 ; j < strlen(pass) - 1 ; ++j)
            pass[j] = pass[j + 1];
        
        pass[strlen(pass) - 1] = ch;
    }
}
void uncrypt(char pass[]){

    int skip = strlen(pass) / 2;
    for(int i = 1 ; i <= skip ; ++i){
        char ch = pass[strlen(pass) - 1];
        for(int j = strlen(pass) - 1 ; j >= 1 ; --j)
            pass[j] = pass[j - 1];
        
        pass[0] = ch;
    }
}

void add_user(){

    FILE *fp = fopen("users.txt","r");

    char linie[256];
    char mat[256][256];
    int nrUsers = 0;

    while(fgets(linie,256,fp) != NULL){

        //printf("%s",linie);
        strcpy(mat[++nrUsers],linie);
    
    }
    char user[256];
    printf("Introdu numele de utilizator (exit pentru a iesi): ");
    scanf("%[^\n]",user);

    getchar();

    if(strcmp(user,"exit") == 0)
        return;

    while(1){
        int ok = 0;
        for(int i = 1 ; i <= nrUsers ; ++i)
            if(strcmp(mat[i],user) == 0)
                ok = 1;

        if(ok == 0)
            break;
        else{
            coloredtext(FOREGROUND_RED,"Nume de utilizator deja folosit\n\n");
            printf("Introdu numele de utilizator : ");
            scanf("%[^\n]",user);
            getchar();
        }
    }
    printf("Introdu parola (minim 6 caractere) : ");

    int i = 0;
    char pass[256];
    while(1){
        
        char ch = getch();

        if(ch != 13)
            pass[i] = ch;

        if(ch == 13 && i >= 6) 
            break;
        else if(ch == 13 && i < 6)
            continue;
        else if(i >= 1 && ch == '\b'){
            printf("\b \b");
            i -= 2;
        }
        else
            coloredtext(FOREGROUND_RED,"*");

        i++;
    }
    pass[i] = 0;
    printf("\n");
    crypt(pass);
    FILE *fp2 = fopen("users.txt","a");
    fprintf(fp2,"%s",user);

    fprintf(fp2,"%s","\n");

    fclose(fp2);

    FILE *fp3 = fopen("passwords.txt","a");

    printf("%s",pass);

    fprintf(fp3,"%s",pass);

    fprintf(fp3,"%s","\n");

    fclose(fp3);

    system("cls");
    
    coloredtext(FOREGROUND_GREEN,"Utilizator creat cu succes !");
    Sleep(2500);

}

void rent_car(char user[]){

    int stopexec_veh = 0,pointer = 1,next_page;

    int pagina = 1;

    while(stopexec_veh == 0){

        system("cls");

        coloredtext(FOREGROUND_GREEN,"=== MENIU RENT ===\n");

        for(int i = 5 * (pagina - 1) + 1 ; i <= min(5 * pagina,nrMasini) ; ++i){

            int auxi = i % 5;
            if(auxi == 0)
                auxi = 5;

            sageata(pointer,auxi);

            cout << Masini[i] << "\n\n";
    
        }
        printf("\nPagina %d",pagina);
        printf("\n--------------------------\n");
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        loopsageata(&pointer,0,min(6,nrMasini - 5 * (pagina - 1) + 1));
        
        char tasta = getch();

        if(tasta == 13)
            next_page = 1;
        else if(pagina > 1 && tasta == 75)
            pagina--,pointer = 1;
        else if((5 * (pagina + 1) <= nrMasini || nrMasini - (5 * pagina) > 0) && tasta == 77)
            pagina++,pointer = 1;
        else if(tasta == 80)
            pointer++;
        else if(tasta == 72)
            pointer--;
        else if(tasta == 27)
            stopexec_veh = 1;

        system("cls");

        if(next_page == 1 && pointer >= 1 && pointer <= 5 && strcmp(Masini[5 * (pagina - 1) + pointer].get_dispon(),"Disponibil") == 0){

            next_page = 0;
            system("cls");

            int pointer_adevarat = 5 * (pagina - 1) + pointer;
            char pret[30];
            strcpy(pret,Masini[pointer_adevarat].get_pret());
            pret[strlen(pret) - 1] = 0;
            printf("Ati selectat masina : %s %s %s cu pretul pe zi : %s RON\n",
            Masini[pointer_adevarat].get_nume(),Masini[pointer_adevarat].get_model(),Masini[pointer_adevarat].get_an(),pret);

            char durata[30],telefon[30];

            printf("Introduceti numarul de telefon (exit pentru a iesi) : ");
            scanf("%[^\n]",telefon);
            getchar();

            if(strcmp("exit",telefon) == 0)
                return;

            printf("Durata in zile a contractului (exit pentru a iesi): ");
            scanf("%[^\n]",durata);
            getchar();

            if(strcmp("exit",durata) == 0)
                return;

            strcpy(Oameni[++nrOameni].user,user);
            strcpy(Oameni[nrOameni].telefon,telefon);
            strcpy(Oameni[nrOameni].durata_inchieriere_zile,durata);

            change_disp(Masini[pointer_adevarat],"Indisponibil");
    
            coloredtext(FOREGROUND_GREEN,"Cererea de inchiriere a fost transmisa, veti fi contactat de un agent la telefon !");
        
            ofstream fp("rent.txt");

            fp << Oameni[nrOameni].user << "| " << Oameni[nrOameni].telefon << ' ' << Oameni[nrOameni].durata_inchieriere_zile 
            << ' ' << Masini[pointer_adevarat].get_nume() << ' ' << Masini[pointer_adevarat].get_model() 
            << ' ' << Masini[pointer_adevarat].get_an() << ' ' << pret;
        
            fp.close();

            auto_load();

            Sleep(5600);

        }
        if(next_page == 1 && pointer >= 1 && pointer <= 5 && strcmp(Masini[5 * (pagina - 1) + pointer].get_dispon(),"Disponibil") != 0){
            system("cls");
            coloredtext(FOREGROUND_RED,"Masina este deja inchiriata sau este indisponibila momentan...");
            Sleep(3000);
            next_page = 0;
        }
    }
}

void make_ajutor(char ajutor[],stock Masini){

    strcat(ajutor,Masini.get_nume());
    strcat(ajutor," ");
    strcat(ajutor,Masini.get_model());
    strcat(ajutor," ");
    strcat(ajutor,Masini.get_an());
    strcat(ajutor," ");
    strcat(ajutor,Masini.get_pret());
    ajutor[strlen(ajutor) - 1] = 0;
    //printf("%s\n",ajutor);

}
int check_which_car(char ajutor[],char masina[]){

    for(int i = 0 ; i < strlen(masina) ; ++i){
        if(strcmp(ajutor,masina + i) == 0)
            return 1;
    }
    return 0;

}

void un_rent_car(char user[]){

    int nr = 0,nr2 = 0;
    char mat[256][1006];
    char repune[256][1006];
    char linie[1006];
    FILE *fp = fopen("rent.txt","r");
    while(fgets(linie,1006,fp) != NULL){

        strcpy(repune[++nr2],linie);

        int ok = 0;
        char aux[256];
        strcpy(aux,linie);
        char *p = strtok(aux,"|");
        if(strcmp(p,user) == 0)
            ok = 1;
    
        if(ok)
            strcpy(mat[++nr],linie);
        
    }
    int stopexec = 0,pointer = 1,next_page;

    int pagina = 1;

    while(stopexec == 0){

        system("cls");

        coloredtext(FOREGROUND_GREEN,"=== MENIU RENT ===\n");

        for(int i = 5 * (pagina - 1) + 1 ; i <= min(5 * pagina,nr) ; ++i){

            int auxi = i % 5;
            if(auxi == 0)
                auxi = 5;

            sageata(pointer,auxi);

            printf("%d. %s\n",i,mat[i]);
            
        }
        printf("\nPagina %d",pagina);
        printf("\n--------------------------\n");
        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        loopsageata(&pointer,0,min(6,nr - 5 * (pagina - 1) + 1));
        
        char tasta = getch();

        if(tasta == 13)
            next_page = 1;
        else if(pagina > 1 && tasta == 75)
            pagina--,pointer = 1;
        else if((5 * (pagina + 1) <= nr || nr - (5 * pagina) > 0) && tasta == 77)
            pagina++,pointer = 1;
        else if(tasta == 80)
            pointer++;
        else if(tasta == 72)
            pointer--;
        else if(tasta == 27)
            stopexec = 1;

        system("cls");

        if(next_page == 1 && pointer >= 1 && pointer <= 5){

            next_page = 0;
            int pointer_adevarat = 5 * (pagina - 1) + pointer;
            
            char aux[1006];
            strcpy(aux,mat[pointer_adevarat]);
            aux[strlen(aux) - 1] = 0;
            printf("Sunteti sigur ca doriti sa anulati cererea \"%s\" (y/n) : ",aux);
            char ch = getch();

            printf("%c\n",ch);

            Sleep(1000);

            if(ch == 'y'){

                int indice = 0;
                for(int i = 1 ; i <= nr2 ; ++i)
                    if(strcmp(repune[i],mat[pointer_adevarat]) == 0){
                        indice = i;
                        break;
                    }
                
                for(int i = pointer_adevarat ; i <= nr ; ++i)
                    strcpy(mat[i],mat[i + 1]);

                for(int i = indice ; i <= nr2 ; ++i)
                    strcpy(repune[i],repune[i + 1]);
                
                nr2--;
                nr--;

                FILE *fp = fopen("rent.txt","w");
                fprintf(fp,"%s","");

                fclose(fp);

                FILE *fp2 = fopen("rent.txt","a");

                for(int i = 1 ; i <= nr2 ; ++i)
                    fprintf(fp2,"%s",repune[i]);
                
                fclose(fp2);

                for(int i = 1 ; i <= nrMasini ; ++i){
                    char ajutor[256] = {0};
                    make_ajutor(ajutor,Masini[i]);
                    if(check_which_car(ajutor,aux) == 1){
                        change_disp(Masini[i],"Disponibil");
                        break;
                    }
                }
                auto_load();
                coloredtext(FOREGROUND_GREEN,"Cererea a fost anulata !");
                Sleep(3500);


            }
            else{
                printf("Se reintoarce la meniu anterior");
                Sleep(3000);
            }
        }
    }
}

void meniu_rent(char user[]){

    int pos = 1,stopexec = 0,nextpage = 0;

    while(stopexec == 0){

        system("cls");
        coloredtext(FOREGROUND_GREEN,"=== MENIU RENT ===\n");

        sageata(pos,1);
        printf("1. Inchiriaza\n");

        sageata(pos,2);
        printf("2. Renuntare cerere inchiriere\n\n");

        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        
        loopsageata(&pos,0,3);

        optiuni(&pos,&stopexec,&nextpage);

        if(nextpage == 1){
            nextpage = 0;
            if(pos == 1){
                system("cls");
                rent_car(user);
            }
            else if(pos == 2){
                system("cls");
                un_rent_car(user);
            }
        }
    }
}

void log_in_user(){

    char user[256];
    
    char linie[256];
    char mat[256][256];
    int nrUsers = 0;

    FILE *fp = fopen("users.txt","r");

    while(fgets(linie,256,fp) != NULL){

        //printf("%s",linie);
        strcpy(mat[++nrUsers],linie);
        mat[nrUsers][strlen(mat[nrUsers]) - 1] = 0;
    
    }
    printf("Introdu numele de utilizator (exit pentru a iesi): ");
    scanf("%[^\n]",user);

    getchar();

    if(strcmp(user,"exit") == 0)
        return;

    int nr = 0;
    while(1){
        int ok = 0;
        for(int i = 1 ; i <= nrUsers ; ++i){
            if(strcmp(mat[i],user) == 0)
                ok = 1, nr = i;
        }
        if(ok == 1)
            break;
        else{
            coloredtext(FOREGROUND_RED,"Utilizator incorect\n");
            printf("Introdu numele de utilizator : ");
            scanf("%[^\n]",user);
            getchar();
        }
    }
    printf("Introdu parola (minim 6 caractere) : ");

    int i = 0;
    char pass[256];
    while(1){
        
        char ch = getch();

        if(ch != 13)
            pass[i] = ch;

        if(ch == 13 && i >= 6) 
            break;
        else if(ch == 13 && i < 6)
            continue;
        else if(i >= 1 && ch == '\b'){
            printf("\b \b");
            i -= 2;
        }
        else
            coloredtext(FOREGROUND_RED,"*");

        i++;
    }
    pass[i] = 0;

    FILE *fppas = fopen("passwords.txt","r");

    int ind = 1;
    while(ind < nr)
        fgets(linie,256,fppas),ind++;

    fgets(linie,256,fppas);

    linie[strlen(linie) - 1] = 0;

    uncrypt(linie);

    while(1){
        if(strcmp(linie,pass) == 0){
            system("cls");
            coloredtext(FOREGROUND_GREEN,"Logat cu succes !\n");
            
            printf("Redirectionare automata spre pagina de rent...");
            Sleep(3500);
            meniu_rent(user);
            break;
        }
        else{
            coloredtext(FOREGROUND_RED,"\nParola gresita, reincearca : ");
            int i = 0;
            while(1){
                
                char ch = getch();

                if(ch != 13)
                    pass[i] = ch;

                if(ch == 13 && i >= 6) 
                    break;
                else if(ch == 13 && i < 6)
                    continue;
                else if(i >= 1 && ch == '\b'){
                    printf("\b \b");
                    i -= 2;
                }
                else
                    coloredtext(FOREGROUND_RED,"*");
                

                i++;
            }
            pass[i] = 0;
        }

    }

}

void inchiriaza_vehicul(){

    int pos = 1,stopexec = 0,nextpage = 0;

    while(stopexec == 0){

        system("cls");
        coloredtext(FOREGROUND_GREEN,"=== MENIU USER ===\n");

        sageata(pos,1);
        printf("1. Utilizator Nou\n");

        sageata(pos,2);
        printf("2. Utilizator Existent\n\n");

        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        
        loopsageata(&pos,0,3);

        optiuni(&pos,&stopexec,&nextpage);

        if(nextpage == 1){
            nextpage = 0;
            if(pos == 1){
                system("cls");
                add_user();
            }
            else if(pos == 2){
                system("cls");
                log_in_user();
            }
        }
    }
    //Sleep(2000);

}
void clear_data(){

    char pass[26];
    coloredtext(FOREGROUND_GREEN,"=== MENIU ADMIN ===\n");
    int trys = 3;
    int intrat = 0;
    while(trys > 0 && intrat == 0){
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
                coloredtext(FOREGROUND_RED,"*");

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
                    coloredtext(FOREGROUND_GREEN,"Fisierul a fost golit cu succes.\nSe revine la meniul principal in 5 sau mai putine secunde...");

                    Sleep(5600);
                    return;
                }
                else{
                    blocheaza_stergere = 1;
                    coloredtext(FOREGROUND_RED,"PIN gresit, se revine la meniu principal");
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
            coloredtext(FOREGROUND_RED,"\nParola gresita\n");
            printf("Incercari ramase %d\n\n",trys - 1);
        }
        trys--;
    }
    if(!intrat){
        coloredtext(FOREGROUND_RED,"\nParola gresita, se reintoarce la ecran principal in 5 sau mai putine secunde");
        Sleep(5600);
    }

}
bool is_emptyy(ifstream& pFile){

    return pFile.peek() == ifstream::traits_type::eof();

}

int main(int argc,char *argv[]){

    //Sleep(8000);
    system("cls");
    
    int stopexec = 0;
    int pos = 1,nextpage,previouspage;

    //FILE *check = fopen("status_functie_5.txt","r");
    ifstream check("status_functie_5.txt");
    if(is_emptyy(check)){
        ofstream check2("status_functie_5.txt");
        check2 << 0;
    }
    
    load_from_file_car_stock();
    load_from_file_people();
    
    while(stopexec == 0){  

        system("cls");
        coloredtext(FOREGROUND_GREEN,"=== MENIU PRINCIPAL ===\n");

        sageata(pos,1);
        cout << "1. Vizualizare Autoturisme\n";

        sageata(pos,2);
        cout << "2. Inchiriere\n";

        sageata(pos, 3);
        cout << "3. Functii Admin [ADMIN ONLY]\n";

        sageata(pos, 4);
        cout <<"4. Admin Help [ADMIN ONLY]\n";

        sageata(pos, 5);
        cout <<"5. Golire Date [ADMIN ONLY]\n";

        sageata(pos, 6);
        cout << "6. Deblocare aplicatie [ADMIN ONLY]\n\n";

        coloredtext(FOREGROUND_RED,"Apasa ESC pentru a iesi...");
        
        loopsageata(&pos,0,7);

        optiuni(&pos,&stopexec,&nextpage);

        if(stopexec == 1){
            system("cls");
            cout << "Sunteti sigur ca doriti sa inchideti aplicatia ? (y/n) :";
            char c = getch();
            if(c == 'y'){
                coloredtext(FOREGROUND_GREEN,"\n\nAplicatia se va inchide in cateva secunde");
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
                listare_stoc_masini(1,nrMasini,Masini);
                
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
                cout <<"Functie blocata(PIN gresit)";

                FILE *pp = fopen("status_functie_5.txt","w");
                fprintf(pp,"%d",blocheaza_stergere);
                fclose(pp);

                Sleep(1500);
            }
            else if(pos == 6 && blocheaza_stergere == 1){
                pos = 0;
                system("cls");
                cout << "=== MENIU ADMIN ===\n";
                cout << "Functie destinata supervizorului/managerului pentru a putea debloca anumite functii\n";
                cout << "Introduceti codul PIN (4 cifre / 0000 pentru revenire) : ";
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
                        cout << "Intoarcere la ecran principal...";
                        Sleep(5600);
                        ok = 1;
                    }
                    else{
                        if(strcmp(PIN,"1111") == 0){
                            coloredtext(FOREGROUND_GREEN,"Functii deblocate!");
                            FILE *pp = fopen("status_functie_5.txt","w");
                            fprintf(pp,"%d",0);
                            blocheaza_stergere = 0;
                            ok = 1;
                            Sleep(2000);
                        }
                        else
                            coloredtext(FOREGROUND_RED,"PIN Gresit. Incearca din nou...\n");
                        
                    }
                }while(ok == 0);
            }
            else if(pos == 6 && blocheaza_stergere == 0){
                system("cls");
                coloredtext(FOREGROUND_RED,"Functiile nu sunt blocate");
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
