#include <stdio.h>
#include <stdlib.h>
#include "LSI.h"
#include <assert.h>

int main()
{
    int l = 0;
    pLST prim = NULL;
    l = parcurgere1(prim); //NULL
    printf("Lungimea initiala: %d \n", l);
    printf("\n");

    pLST pozitie = NULL;
    adauganod(&prim, pozitie);
    l = parcurgere1(prim);//1
    printf("Lungime dupa adaugare nod 1: %d \n", l);
    printf("\n");

    pozitie = prim;   //!!!
    adauganod(&prim, pozitie);
    l = parcurgere1(prim);//2
    printf("Lungime dupa adaugare nod 2: %d \n", l);
    printf("\n");

    pozitie = prim->pDR; //pozitie=NULL ca sa adaugam un nod la inceput, pozitie=prim ca sa adaugam un nod dupa primul si pozitie=pozitie->pDR ca sa adaugam la final si pozitie=prim->pDR ca sa punem in a 3a pozitie
    adauganod(&prim, pozitie);
    l = parcurgere1(prim);//3
    printf("Lungime dupa adaugare nod 3: %d \n", l);
    printf("\n");

    pozitie = pozitie->pDR;   //!!!
    adauganod(&prim, pozitie);
    l = parcurgere1(prim);//4
    printf("Lungime dupa adaugare nod 4: %d \n", l);
    printf("\n");

    parcurgere2(prim);

    stergere_nod(&prim, pozitie);  //stergem pe ultimul
    l = parcurgere1(prim);
    printf("Lungime dupa adaugare nod : %d \n", l);
    parcurgere2(prim);

    pozitie = NULL;
    stergere_nod(&prim, pozitie);  //stergem pe primul
    l = parcurgere1(prim);
    printf("Lungime dupa adaugare nod : %d \n", l);
    parcurgere2(prim);

    stergere_nod(&prim, pozitie);  //stergem pe primul
    l = parcurgere1(prim);
    printf("Lungime dupa adaugare nod : %d \n", l);
    parcurgere2(prim);

    stergere_nod(&prim, pozitie);  //stergem pe primul
    l = parcurgere1(prim);
    printf("Lungime dupa adaugare nod : %d \n", l);
    parcurgere2(prim);

    test_lista_vida(prim) ? printf("Lista este vida \n") : printf("Lista nu este vida\n");
    //tema:sa se modifice functia sterge nod astfel incat sa afiseze adresa nodului sters
    //sa se creeze f parcurgere 3 care sa numere cate el din lista au varsta mai mare decat 10 si sa se afiseze acele el care sarisfac aceasta conditie

}