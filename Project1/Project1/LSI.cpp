#include "LSI.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void adauganod(ppLST lst, pLST pozitia)
{
    pLST q = (pLST)calloc(1, sizeof(ND)); //q este adresa de inceput a nodului alocat
    assert(q != NULL);  //assert este o presupunere care testeaza daca q indica la o adresa valida, daca q indica la o aresa valida atunci programul se continua daca q indica la NULL, adica pp este falsa programul se opreste
    //Conventie: daca vreau sa inserez intre nodul x si x+1 atunci convenim ca inserarea sa o facem dupa nodul x
    //stabilesc parte informationala:
    printf("Introduceti numele: ");
    gets_s(q->nume, 19);//scanf("%s",q->nume);
    fflush(stdin); //curat bufferul de intrare in tastatura (enter)
    printf("Introduceti prenumele:");
    gets_s(q->prenume, 15);
    fflush(stdin); //curat bufferul de intrare al tastaturii, adica sterge enterul
    printf("Introduceti varsta:");
    scanf_s("%i", &q->varsta);
    //fflush(stdin);
    printf("Introduceti inaltimea:");
    scanf_s("%f", &q->inaltime);
    //fflush(stdin);

    if (pozitia == NULL)
    {
        q->pDR = *lst;
        *lst = q;
    }
    else
    {
        q->pDR = pozitia->pDR;
        pozitia->pDR = q;
    }
}

unsigned int parcurgere1(pLST start)
{
    pLST temp = NULL;
    int lungime = 0;
    temp = start;
    while (temp != NULL)
    {
        lungime++;
        temp = temp->pDR;
    }
    return lungime;
}

void parcurgere2(pLST start)
{
    pLST temp = start;
    while (temp != NULL)
    {
        printf("%s\t %s\t %d\t %f\n",
            temp->nume,
            temp->prenume,
            temp->varsta,
            temp->inaltime);
        temp = temp->pDR;
    }
}

void stergere_nod(ppLST lsx, pLST poz)
{
    pLST q;
    if (poz == NULL)  // daca poz indica la NULL inseamna ca am ales sa sterg NULL
    {
        q = *lsx;  //un backup pt adresa primului nod ca sa stiu ce sa sterg (*lsx), *indirectat la adresa nodului
        *lsx = (*lsx)->pDR;  //adresa de inceput a listei o mut sa indice la adresa nodului 2
        free(q); // eliberez ememoria pt primul nod pecare l=am selectat sa il sterg
    }
    else  //daca poz inica la o adresa valida inseamna ca am ales sa sterg elementul dupa poz
    {
        q = poz->pDR; //in q imi fac un backup si memorez adresa urm element dupa poz selectata
        //am facut acest backup ca sa nu pierd adresa el care il sterg
        if (q != NULL)
        {
            poz->pDR = q->pDR;  //pointerul dreapta al poz curente il rupem sa nu mai indice la pointerul care urm sa stergem 
            //si il vom muta sa indice la pointerul dreapta al nodului de sters adica sa indice la el de dupa nodul sters 
            free(q);
        }
        else //aici tratez cazul in care pDR e pozitiei indica la NULL, adica mi-am selectat sa sterg nodul de dupa ultimul care exista
        {
            printf("Am selectat gresit nodul dupa el nu am ce sa sterg");
        }
    }

}

bool test_lista_vida(pLST lsx)
{
    return (lsx == NULL) ? true : false;
}




