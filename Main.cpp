#include "Plateau.h"
#include <iostream>
using namespace std;

/** @file main.cpp
 * @brief Programme principal.
 * @author David Maxime - Adjab Mehdi
 */



int main() {
	srand(time(NULL));
	unsigned int MAXL, MAXH, i;

	/*Saisie des donn�es pr�liminaires tant qu'elle ne sont pas correctes*/
    do
        MAXH=saisirChiffre("Entrez la hauteur du plateau ?");
    while (MAXH<2 || MAXH>26);
    do
           MAXL=saisirChiffre("Entrez la largeur du plateau ?");
    while (MAXL<2 || MAXL>26);

    /*Constructeur de plateau*/
	Plateau p(MAXH,MAXL);
	unsigned tind[MAXH*MAXL+2];

	/*Initialisation du tableau d'indice � vide*/
	for(i=0;i<MAXH*MAXL+2;++i)
		tind[i]=' ';

	/*Tirage au sort du joueur*/
	p.joueur();

	/*Cr�ation de la matrice d'affichage*/
	p.EditerMatrice();
	bool victoire=false;
	unsigned int macase;
	/*Le premier joueur joue sur une case*/
	macase=p.jouer();

	/*Mise � jour de l'aafichage*/
	p.EditerMatrice();

	/*Ex�cution du swap ou non*/
	if(!p.Nswap(macase)) {
		/*Si non le joueur 2 joue ,m�j de l'affichage
		 et on inverse la couleur pour le le joueur 1*/
		macase=p.jouer();
		p.EditerMatrice();
		p.inverseCouleur();
	}

    /*Tant que personne gagne on joue*/
	while(!victoire) {
		macase=p.jouer();
        p.EditerMatrice();
        /* A chaque coup la liste des cases visit�es est remise � zero */
        for(i=0;i<MAXH*MAXL+3;++i)
        		tind[i]=8000;
        /*Apr�s avoir jouer, v�rification r�cursive de la victoire*/
        victoire=p.recurs(0,macase,tind);
        if(!victoire)
        	p.inverseCouleur();
	}
	/* on cherche le gagnant*/
	if(p.estCouleur1())
		cout << "Joueur 1 gagne";
	else
		cout << "Joueur 2 gagne";
	cout<<endl<<"Fin du jeu"<<endl;

	return 0;
}
 /* Le destructeur est appel�
  * lib�ration de l'espace m�moire allou� pour un plateau */





