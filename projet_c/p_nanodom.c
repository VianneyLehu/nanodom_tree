#include "p_nanodom.h"
#include "p_text_enrichi.h"
#include <stdlib.h>
#include <stdio.h>


void creer_noeud(
    p_noeud* ceci,
    t_token etiquette,
    const char* contenu,
    p_noeud pere,
    p_noeud premier_fils,
    p_noeud dernier_fils,
    p_noeud grand_frere,
    p_noeud petit_frere)
    {

        (*ceci) = (p_noeud)malloc(sizeof(t_noeud));
        (*ceci)->l_etiquette = etiquette;
        (*ceci)->le_contenu = contenu;
        (*ceci)->les_parentes[PERE] = pere;
        (*ceci)->les_parentes[PREMIER_FILS] = premier_fils;
        (*ceci)->les_parentes[DERNIER_FILS] = dernier_fils;
        (*ceci)->les_parentes[GRAND_FRERE] = grand_frere;
        (*ceci)->les_parentes[PETIT_FRERE] = petit_frere;
        
    }

void detruire_noeud(p_noeud* ceci){
    
    for(int i=0; i<=4;i++){ //on free les tableaux ligne par lignes
        free((*ceci)->les_parentes[i]);
    }
    free((*ceci));
    
}

void modifier_etiquette_noeud(p_noeud ceci, t_token nouvelle_etiquette){
    ceci->l_etiquette = nouvelle_etiquette;
}

void modifier_contenu_noeud(p_noeud ceci, char* nouveau_contenu){
    ceci->le_contenu = nouveau_contenu;
}

void modifier_parente_noeud(p_noeud ceci, t_parente lien_de_parente, p_noeud nouveau_parent){
    ceci->les_parentes[lien_de_parente] = nouveau_parent;
}



const char* t_token_image(t_token ceci){ //permet d'afficher tous les types de l'enum t_token


    switch(ceci){

        case 0:
            return "DOCUMENT";
            break;

        case 1:
            return "ANNEXE";
            break;

        case 2:
            return "SECTION";
            break;  

        case 3:
            return "TITRE";
            break;  
        
        case 4:
            return "LISTE";
            break;    
        
        case 5:
            return "ITEM";
            break;   
            
        case 6:
            return "IMPORTANT";
            break;   
        
        case 7:
            return "RETOUR_A_LA_LIGNE";
            break;
        
        
        case 8:
            return "MOT";
            break;

        default:
            return "ERREURE";
            break;

    }


}

const char* t_parente_image(t_parente ceci){//permet d'afficher tous les types de l'enum t_parente

      switch(ceci){

        case 0:
            return "PERE";
            break;

        case 1:
            return "PREMIER_FILS";
            break;

        case 2:
            return "DERNIER_FILS";
            break;  

        case 3:
            return "GRAND_FRERE";
            break;  
        
        case 4:
            return "PETIT_FRERE";
            break;    
        
        case 5:
            return "NB_PARENTES";
            break;   

        default:
            return "ERREURE";
            break;
            
     
    }

     
}


void debugger_noeud(p_noeud ceci){


    printf("\n");
    printf("\n");
    printf("Noeud range à l'adresse: %p", ceci);
    printf("\n");
    printf("- ETIQUETTE: %s ",t_token_image(ceci->l_etiquette));
    printf("\n");
    printf("- CONTENU: %s", ceci->le_contenu);
    printf("\n");
    for(int i=PERE; i<=NB_PARENTES;i++){
        printf("- %s : %p",t_parente_image(i), (ceci->les_parentes[i])); //affiche l'adresse des noeuds de lien de parenté
        printf("\n");
    }
}


void inserer_aine(p_noeud ceci, p_noeud orphelin){

    if(ceci != NULL && orphelin != NULL){

        if(ceci->les_parentes[PREMIER_FILS]==NULL){  //cas ou ceci n'a pas de fils
            ceci->les_parentes[PREMIER_FILS] = orphelin;
            ceci->les_parentes[DERNIER_FILS] = orphelin;
            ceci->les_parentes[PREMIER_FILS]->les_parentes[PERE] = ceci;

        }
        else if(ceci->les_parentes[PREMIER_FILS]!=NULL){
            orphelin->les_parentes[PETIT_FRERE] = ceci->les_parentes[PREMIER_FILS];//on lie l'orphelin au premier fils
            ceci->les_parentes[PREMIER_FILS]->les_parentes[GRAND_FRERE] = orphelin;
            ceci->les_parentes[PREMIER_FILS] = orphelin;//on lie l'orphelin à son nouveau pere
            ceci->les_parentes[PREMIER_FILS]->les_parentes[PERE] = ceci;

            
        }

    }
        
}   

void inserer_cadet(p_noeud ceci, p_noeud orphelin){


    if(ceci != NULL && orphelin != NULL){


        if(ceci->les_parentes[DERNIER_FILS]==NULL){
            ceci->les_parentes[PREMIER_FILS] = orphelin;
            ceci->les_parentes[DERNIER_FILS] = orphelin;
            ceci->les_parentes[DERNIER_FILS]->les_parentes[PERE] = ceci;

        }
        else if(ceci->les_parentes[DERNIER_FILS]!=NULL){
            orphelin->les_parentes[GRAND_FRERE] = ceci->les_parentes[DERNIER_FILS];
            ceci->les_parentes[DERNIER_FILS]->les_parentes[PETIT_FRERE] = orphelin;
            ceci->les_parentes[DERNIER_FILS] = orphelin;
            ceci->les_parentes[DERNIER_FILS]->les_parentes[PERE] = ceci;

            
        }

    }

}  

void inserer_apres(p_noeud ceci, p_noeud orphelin){
    if(ceci->les_parentes[PETIT_FRERE]==NULL){
        inserer_cadet(ceci->les_parentes[PERE],orphelin);
    }
    else{

        ceci->les_parentes[PETIT_FRERE]->les_parentes[GRAND_FRERE] = orphelin;
        orphelin->les_parentes[PETIT_FRERE] = ceci->les_parentes[PETIT_FRERE];
        ceci->les_parentes[PETIT_FRERE] = orphelin;
        orphelin->les_parentes[GRAND_FRERE] = ceci;
        orphelin->les_parentes[PERE] = ceci->les_parentes[PERE];
    }
}

void inserer_avant(p_noeud ceci, p_noeud orphelin){

    if(ceci->les_parentes[GRAND_FRERE]==NULL){
        inserer_aine(ceci->les_parentes[PERE],orphelin);
    }
    else{

        ceci->les_parentes[GRAND_FRERE]->les_parentes[PETIT_FRERE] = orphelin;
        orphelin->les_parentes[GRAND_FRERE] = ceci->les_parentes[GRAND_FRERE];
        ceci->les_parentes[GRAND_FRERE] = orphelin;
        orphelin->les_parentes[PETIT_FRERE] = ceci;
        orphelin->les_parentes[PERE] = ceci->les_parentes[PERE];
    }

}

void extraire(p_noeud ceci){

    if(ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] == ceci && ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] == ceci){ //cas ou les parents de ceci a un fils unique ceci.
        ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] = NULL;
        ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] = NULL;
        ceci->les_parentes[PERE] = NULL;

    }
    else if(ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] == ceci){//ceci est le premier fils de son pere
        ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] = ceci->les_parentes[PETIT_FRERE];
        ceci->les_parentes[PETIT_FRERE]->les_parentes[GRAND_FRERE] = NULL;//gerer les pointeurs qui pointent dans le vide 
        ceci->les_parentes[PERE] = NULL;
        ceci->les_parentes[PETIT_FRERE] = NULL;   

    }
    else if(ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] == ceci){//ceci est le dernier fils de son pere
        ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] = ceci->les_parentes[GRAND_FRERE];
        ceci->les_parentes[GRAND_FRERE]->les_parentes[PETIT_FRERE] = NULL;
        ceci->les_parentes[PERE] = NULL;
        ceci->les_parentes[GRAND_FRERE] = NULL;

    }

    else if(ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] != ceci && ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] != ceci){//cas ou le pere ne reconnais pas ceci

        ceci->les_parentes[GRAND_FRERE]->les_parentes[PETIT_FRERE] = ceci->les_parentes[PETIT_FRERE];
        ceci->les_parentes[PETIT_FRERE]->les_parentes[GRAND_FRERE] = ceci->les_parentes[GRAND_FRERE];
        ceci->les_parentes[PERE] = NULL;  
        ceci->les_parentes[GRAND_FRERE] = NULL;
        ceci->les_parentes[PETIT_FRERE] = NULL;

        
    }

}

void afficher_elabore(t_arbre_nanodom ceci){//problèmes d'indentations

    if(ceci != NULL){
        ceci = (p_noeud)ceci;
        if(ceci->l_etiquette == DOCUMENT){
            ouvrir_bloc(); 
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
        }
        if(ceci->l_etiquette == SECTION){
            ouvrir_bloc();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            fermer_bloc();
        }
        if(ceci->l_etiquette == TITRE){
            changer_mode(MAJUSCULE);
            entamer_ligne();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            terminer_ligne();
            changer_mode(NORMAL);
            
        }
        if(ceci->l_etiquette == LISTE){
            entamer_ligne();
            indenter();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
        }
        if(ceci->l_etiquette == ITEM){
            pucer();  
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
        }
        if(ceci->l_etiquette == IMPORTANT){
            changer_mode(MAJUSCULE);
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
    
        }

        if(ceci->l_etiquette == RETOUR_A_LA_LIGNE){
            terminer_ligne();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            

        }
        if(ceci->l_etiquette == MOT){
            entamer_ligne();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            ecrire_mot(ceci->le_contenu);
            changer_mode(NORMAL);
            terminer_ligne();         
        }
        afficher_elabore(ceci->les_parentes[PETIT_FRERE]);


    }





   
}



void afficher_enrichi(t_arbre_nanodom ceci){ //problèmes d'indentations
  
    if(ceci != NULL){
        ceci = (p_noeud)ceci;
        if(ceci->l_etiquette == DOCUMENT){
            printf("\n");
            printf("<DOCUMENT>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
        }
        if(ceci->l_etiquette == SECTION){
            printf("\n");
            indenter();
            indentation_enrichi();
            printf("<SECTION>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            printf("</SECTION>");
            printf("\n");
            desindenter();
        }
        if(ceci->l_etiquette == TITRE){
            printf("\n");
            indenter();
            indentation_enrichi();
            printf("<TITRE>");
            changer_mode(MAJUSCULE);
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            changer_mode(NORMAL);
            printf("</TITRE>");
            printf("\n");
            desindenter();
            
        }
        if(ceci->l_etiquette == LISTE){
            printf("\n");
            indenter();
            indentation_enrichi();
            printf("<LISTE>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            printf("</LISTE>");
            printf("\n");
            desindenter();
        }
        if(ceci->l_etiquette == ITEM){
            pucer();  
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
        }
        if(ceci->l_etiquette == IMPORTANT){
            changer_mode(MAJUSCULE);
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
    
        }

        if(ceci->l_etiquette == RETOUR_A_LA_LIGNE){
            printf("\n");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            

        }
        if(ceci->l_etiquette == MOT){
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            ecrire_mot(ceci->le_contenu);
            changer_mode(NORMAL);
        }
        afficher_enrichi(ceci->les_parentes[PETIT_FRERE]);


    }

}




void sauvegarder_enrichi(t_arbre_nanodom ceci, FILE* fichier){ //ne fonctionne pas 
    
    if(ceci != NULL){
        ceci = (p_noeud)ceci;
        if(ceci->l_etiquette == DOCUMENT){
            fprintf(fichier,"\n");
            fprintf(fichier, "<DOCUMENT>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
        }
        if(ceci->l_etiquette == SECTION){
            fprintf(fichier, "\n");
            indenter();
            indentation_enrichi();
            fprintf(fichier, "<SECTION>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            fprintf(fichier, "</SECTION>");
            fprintf(fichier,"\n");
            desindenter();
        }
        if(ceci->l_etiquette == TITRE){
            fprintf(fichier, "\n");
            indenter();
            indentation_enrichi();
            fprintf(fichier, "<TITRE>");
            changer_mode(MAJUSCULE);
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            changer_mode(NORMAL);
            fprintf(fichier, "</TITRE>");
            fprintf(fichier, "\n");
            desindenter();
            
        }
        if(ceci->l_etiquette == LISTE){
            fprintf(fichier, "\n");
            indenter();
            indentation_enrichi();
            fprintf(fichier, "<LISTE>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            fprintf(fichier, "</LISTE>");
            printf("\n");
            desindenter();
        }
        if(ceci->l_etiquette == ITEM){
            pucer();  
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
        }
        if(ceci->l_etiquette == IMPORTANT){
            changer_mode(MAJUSCULE);
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
    
        }

        if(ceci->l_etiquette == RETOUR_A_LA_LIGNE){
            fprintf(fichier, "\n");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            

        }
        if(ceci->l_etiquette == MOT){
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            ecrire_mot(ceci->le_contenu);
            changer_mode(NORMAL);
        }
        afficher_enrichi(ceci->les_parentes[PETIT_FRERE]);


    }

}


void detruire_nanodom(t_arbre_nanodom* ceci){ //ne fonctionne pas 



    if((*ceci)->les_parentes[PREMIER_FILS] == NULL && (*ceci)->les_parentes[DERNIER_FILS] == NULL){ //condition d'arret on arrive en bas de l'arbre il n'y a plus de fils
        return;
    }   

    if((*ceci)->les_parentes[DERNIER_FILS] != NULL){
        detruire_nanodom(&(*ceci)->les_parentes[DERNIER_FILS]);
    } 

    else if((*ceci)->les_parentes[GRAND_FRERE]!= NULL){
        detruire_nanodom(&(*ceci)->les_parentes[GRAND_FRERE]);
    }

    else if((*ceci)->les_parentes[PETIT_FRERE] != NULL){
        detruire_nanodom(&(*ceci)->les_parentes[PETIT_FRERE]);
    }

    else if((*ceci)->les_parentes[PREMIER_FILS] != NULL){
        detruire_nanodom(&(*ceci)->les_parentes[PREMIER_FILS]);
    }
    extraire((*ceci));
    detruire_noeud(&(*ceci));


}
