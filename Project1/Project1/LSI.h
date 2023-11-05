#include <stdbool.h>

typedef struct nod
{
    char nume[20];
    char prenume[16];
    int varsta;
    float inaltime;
    struct nod* pDR;
}ND;

typedef ND* pLST;
typedef ND** ppLST; //ca sa modificam adresa

void adauganod(ppLST, pLST);  //pLST ne ajuta sa modificam adresa
//PPLSt ajuta la modificarea valorii
unsigned int parcurgere1(pLST);
void parcurgere2(pLST);
void stergere_nod(ppLST, pLST);
bool test_lista_vida(pLST);
