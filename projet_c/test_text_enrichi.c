#include <stdlib.h>
#include <stdio.h>
#include "p_text_enrichi.h"
//#include "p_nanodom.h"



int main(){

    ouvrir_bloc();
    ouvrir_bloc();
    indenter();
    entamer_ligne();
    ecrire_mot("testaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    terminer_ligne();
    desindenter();
    ouvrir_bloc();
    ouvrir_bloc();
    indenter();
    indenter();
    entamer_ligne();
    pucer();
    ecrire_mot("test");
    terminer_ligne();
    desindenter();
    fermer_bloc();
    fermer_bloc();
    entamer_ligne();
    pucer();
    ecrire_mot("test2");
    terminer_ligne();
    fermer_bloc();
    fermer_bloc();

}