#include<stdio.h>
#include<stdlib.h>
#define IME 100
#define MAX_LINE 1024


typedef struct                                                              //struct student
{
  int ocjene;
  char ime[IME];
  char prezime[IME];
}Student;



int procitajDatoteku(char *imeDatoteke);                                    //prototip funkcije
Student* alocirajIProcitajIzDatoteke(char* imeDatoteke, int brojStudenata); //prototip funkcije
int maxBodovi(Student *studenti,int brojStudenata);                             //prototip funkcije



int main()                                                                  // main funkcija
{
    int brojRedaka;
    int i=0;
    Student *studenti;
    char *imeDat = "datoteka.txt";
    brojRedaka = procitajDatoteku(imeDat);
    printf("Ova datoteka ima %d redaka.\n",brojRedaka);
    
    studenti = alocirajIProcitajIzDatoteke(imeDat, brojRedaka);
    int max=maxBodovi(studenti,brojRedaka);
    printf("IME PREZIME APS_BOD REL_BOD \n");
    for(i=0;i<brojRedaka;i++)
    {
        printf("%s %s %d %.0lf\n",studenti[i].ime,studenti[i].prezime,studenti[i].ocjene,100*(double)studenti[i].ocjene/(double)max);
    }
    
    return 0;
}



int procitajDatoteku(char *imeDatoteke)                                     // funkcija 1
{
    int br=0;
    FILE *fp=NULL;
    char buffer[MAX_LINE]={0};
    
    fp=fopen(imeDatoteke,"r");
    if(!fp)
    {
        printf("Neuspjesno otvaranje datoteke.\n");
        return -1;
    }
    
    while(!feof(fp))
    {
        fgets(buffer,MAX_LINE,fp);
        br++;
    }
    fclose(fp);
    return br;
}



Student *alocirajIProcitajIzDatoteke(char *imeDatoteke,int brojStudenata)   //funkcija 2
{
    Student *studenti = NULL;
    int i=0;
    FILE *fp=NULL;
    studenti = (Student *)malloc(sizeof(Student)*brojStudenata);
    if(!studenti)
    {
        printf("Neuspjesna alokacija memorije.\n");
        return NULL;
    }
    fp = fopen(imeDatoteke,"r");
    if(!fp)
    {
        printf("Neuspjesno otvaranje datoteke.\n");
        return NULL;
    }
    while(!feof(fp))
    {
        fscanf(fp," %s %s %d\n",studenti[i].ime,studenti[i].prezime,&studenti[i].ocjene);
        i++;
    }
    fclose(fp);
    return studenti;
}



int maxBodovi(Student *studenti,int brojStudenata)                              //funkcija 3
{
    int i=0,max=0;
    for(i=0;i<brojStudenata;i++)
    {
        if(studenti[i].ocjene > max)max=studenti[i].ocjene;    
    }
    return max;
}

