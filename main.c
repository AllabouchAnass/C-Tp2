#include<stdio.h>
#include<stdlib.h>

//Structure
typedef struct ElementListe {
    int valeur; 
    struct ElementListe *precedent; 
    struct ElementListe *suivant;
}Element;

//Creation de la list
Element *creer(int v) {
    Element *elm=(Element *) malloc(sizeof(Element));
    if(elm==NULL) exit(1);
    elm->valeur=v;
    elm->suivant=NULL;
    elm->precedent=NULL;
    return elm;
}

//Inseration au debut de la liste
Element *ins_debut (Element *lis,int v) {
    Element *elm=creer(v);
    if(lis==NULL) lis=elm;
    else {
        elm->suivant=lis;
        lis->precedent=elm;
        lis=elm;
    }
    return lis;
}

//Inseration a la fin de la liste
Element *ins_fin(Element *lis,int v) {
    Element *elm=creer(v);
    if(lis==NULL) lis=elm;
    else {
        Element *temp=lis;
        while(temp->suivant!=NULL) temp=temp->suivant;
        elm->precedent=temp;
        temp->suivant=elm;
    }
    return lis;
}

//Cherche position
Element *cherche_pos(Element *lis,int pos) {
    Element *temp=lis;
    for(int i=1;i<pos;i++) temp=temp->suivant;
    return temp;
}

//Inseration avant position
Element *ins_av(Element *lis,int pos,int v) {
    Element *elm=creer(v);
    Element *temp=cherche_pos(lis,pos);
    elm->suivant=temp;
    elm->precedent=temp->precedent;
    if(temp->precedent==NULL) lis=elm;
    else (temp->precedent)->suivant=elm;  
    temp->precedent=elm;    
    return lis;
}

//Inseration apres element
Element *ins_ap(Element *lis,int pos,int v) {
    Element *elm=creer(v);
    Element *temp=cherche_pos(lis,pos);
    elm->precedent=temp;
    elm->suivant=temp->suivant;
    if(temp->suivant!=NULL) (temp->suivant)->precedent=elm; 
    temp->suivant=elm;    
    return lis;
}

//Affichage de droite à gauche, et de gauche à droite
void affichage(Element *lis,char gd) {
    Element *temp=lis;
    switch (gd)
    {
    case 'g':
        while(temp!=NULL) {
            printf("%d\t",temp->valeur);
            temp=temp->suivant;
        }
        break;
    case 'd':
        while(temp!=NULL) temp=temp->suivant;
        while(temp!=NULL) {
            printf("%d\t",temp->valeur);
            temp=temp->precedent;
        }
        break;
    default:
        break;
    }
}

//Remplissage liste
Element *remplissage(int nbre) {
    Element E,*lis=NULL;
    for(int i=0;i<nbre;i++) {
        printf("Element %d:",i+1);scanf("%d",&E.valeur);
        lis=ins_fin(lis,E.valeur);
    }
    return lis;
}


Element *supprimer(Element *lis,Element *temp) {
    Element *sup;
    if(temp->precedent==NULL) {
        sup=lis;
        lis=lis->suivant;
        if(lis!=NULL) lis->precedent=NULL;
    }
    else {
        if(temp->suivant==NULL) {
            sup=temp;
            temp->precedent->suivant=NULL;
        }
        else {
            sup=temp;
            temp->precedent->suivant=temp->suivant;
            temp->suivant->precedent=temp->precedent;
        }
    }
    //free(sup->valeur);
    free(sup);
    return lis;
}
//Supprimer
Element *supprimer_iff(Element *lis,int val) {
    Element *temp=lis;
    while(temp!=NULL) {
        if(temp->valeur<=val) {
            lis=supprimer(lis,temp);
            temp=lis;
        }
        else temp=temp->suivant;
    }
    return lis;
} 

//Menu
void menu() {
    int nbre,pos,v;
    printf("Donner le nombre d'element:");scanf("%d",&nbre);
    Element *lis=remplissage(nbre);
    printf("Donner la position:");scanf("%d",&pos);
    printf("Donner la valeur a ajouter:");scanf("%d",&v);
    lis=ins_ap(lis,pos,v);
    printf("\nVotre liste est:\n");affichage(lis,'g');
    printf("\nDonner la valeur a suprimer:");scanf("%d",&v);
    lis=supprimer_iff(lis,v);
    printf("\nVotre liste est:\n");affichage(lis,'g');
}

//Main
void main() {
    menu();
    system("pause");
}