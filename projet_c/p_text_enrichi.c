#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "p_text_enrichi.h"

int indentation = 0;

int nb_char = 0;

int nb_bloc = 0;

t_mode actuelmode = NORMAL;


void changer_mode(t_mode mode){
    actuelmode = mode;
}



t_mode mode(){
    return actuelmode;
}



void ouvrir_bloc(){

    nb_bloc++;

    printf("\n");

    for(int i= 0;i<nb_bloc;i++){
        printf("|");
    }

    printf("+");
    for(int i =0; i<80-(nb_bloc*2);i++){
        printf("-");
    }
    printf("+");

    for(int i= 0;i<nb_bloc;i++){
        printf("|");
    }
}

void fermer_bloc(){

    printf("\n");


    for(int i= 0;i<nb_bloc;i++){
        printf("|");
    }
    printf("+");
    for(int i =0; i<80-(nb_bloc*2);i++){
        printf("-");
    }
    printf("+");
    for(int i= 0;i<nb_bloc;i++){
        printf("|");
    }

    nb_bloc--;

}

void indenter(){
    indentation++;

}

void desindenter(){
    indentation--;


}

int est_en_fin_de_ligne(){
    if(nb_char < 80){
        return 1;
    }else{
        return -1;
    }
}

int est_au_debut_de_ligne(){
    if(nb_char == 1){
        return 1;
    }else{
        return -1;
    }
}

void entamer_ligne(){
    printf("\n");
    for(int i=0;i<nb_bloc;i++){
        printf("|");
    }
    for(int i=0;i<indentation; i++){
        printf("    ");
        nb_char += 4;
    }
} 

void indentation_enrichi(){
     for(int i=0;i<indentation; i++){
        printf("    ");
    }
}


void terminer_ligne(){
    for(int i=nb_char; i<=81-(nb_bloc*2);i++){
        printf(" ");
    }
    for(int i= 0;i<nb_bloc;i++){
        printf("|");
    }
    nb_char = 0;
}

void pucer(){

    if(indentation == 0){
        printf("° ");
        nb_char+= 2;

    }
    else if(indentation > 0){
        printf("* ");
        nb_char += 2;
    }

}


void ecrire_mot(const char* mot){

    if(actuelmode == MAJUSCULE){
        if(peut_ecrire(strlen(mot))){
            int i = 0;
            while(mot[i]!= '\0'){
                printf("%c", toupper(mot[i]));
                i++;
                nb_char ++;
            }
        }
    }  
    else if(actuelmode == MINUSCULE){
        if(peut_ecrire(strlen(mot))){
            int i = 0;
            while(mot[i]!= '\0'){
                printf("%c", tolower(mot[i]));
                i++;
                nb_char ++;
            }
        }
    }  
    else{
        if(peut_ecrire(strlen(mot))){
            int i = 0;
            while(mot[i]!= '\0'){
                printf("%c", tolower(mot[i]));
                i++;
                nb_char ++;
            }
        }

    }
    
   

}

int peut_ecrire(int nb_caracteres){
    if(nb_caracteres > (80-nb_char)){
        return 0;
    }
    else{
        return 1;
    }
}