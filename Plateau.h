#ifndef PLATEAU_H_
#define PLATEAU_H_
#include "MaCase.h"
#include <iostream>

/**
 * @file Plateau.h
 * @author David Maxime - Adjab Mehdi
 * @brief D�finit le composant Plateau et les op�rations associ�es.
 */




class Plateau {
	public:


		//typedef enum {r,b,vide} color;

	    /** @brief Constructeur du plateau de jeu .
        * @param [in] tailleh: Hauteur du plateau.
        * @param [in] taillel: Largeur du plateau.
        * @pre  2<=tailleh && tailleh<=26
        * @pre  2<=taillel && taillel<=26
        */
		Plateau(const unsigned int tailleh, const unsigned int taillel);

		/** @brief Destruction du plateau de jeu .
        */
		~Plateau();

        /** @brief Retourne la couleur du joueur en cours .
        * @pre  0 < y && y <= tailleh_.
        * @return couleur du joueur.
        */
		bool getCouleur();

		/** @brief D�poser sur le plateau le pion d'un joueur .
        * @param [in] x : La colonne.
        * @param [in] y : La Ligne.
        * @pre  0 < x && x <= taillel_.
        * @pre  0 < y && y <= tailleh_.
        */
		void putXYOK(const unsigned int x,const unsigned int y);

		/** @brief R�cup�rer la position d'une case sur le plateau (Tableau).
        * @param [in] x : La colonne.
        * @param [in] y : La ligne.
        * @pre  0 < x && x <= taillel_.
        * @pre  0 < y && y <= tailleh_.
        * @return Le poste de la case.
        */
		unsigned int getCXYOK(const unsigned int x,const unsigned int y) ;

		/** @brief Affiche la couleur du pion sur le plateau (Tableau).
        * @param [in] x : La colonne.
        * @param [in] y : La ligne .
        * @pre  0 < x && x <= taillel_.
        * @pre  0 < y && y <= tailleh_.
        */
		void getXYOK(const unsigned int x,const unsigned int y) const;

		/** @brief Inverse la couleur � chaque tour .
        */
		void inverseCouleur();

		/** @brief Enregistrement et Tirage au sort des joueurs .
        */
		void joueur();

		/** @brief V�rifie si une case du tableau est occup�e .
        * @param [in] macase : Position de la case dans le plateau (Tableau).
        * @pre  0 <= macase && macase <= tailleh_*taillel_ .
        * @return true la case est libre, false la case est occup�e.
        */
		bool estLibre(const unsigned int macase);

        /** @brief Edite une matrice (n�cessaire � l'affichage).
        */
		void EditerMatrice();

        /** @brief Affiche la matrice �dit�e .
        * @param [in] matrice : chaine de caract�re qui sera lue s�quentiellement.
        */
        void lireMatrices(const std::string& matrice);

        /** @brief  Affiche l'�lement d'une case sur le plateau
        * @param [in] i : indice indiquant le calcul .
        * @param [in] nbligne : Nombre de ligne.
        * @param [in] var : Compteur d'it�ration .
        * @pre 0<nbligne && nbligne<=(tailleh_*taillel_) -1
        */
         void CalculCase(const unsigned int i,const unsigned int nbligne, const unsigned int var);

		/** @brief Identifie la couleur, gr�ce � laquelle le gagnant
		 * est d�sign�.
        */
		bool estCouleur1();

		/** @brief Permet au joueur de jouer sur une case .
        * @return la position de la case jou�e.
        */
		unsigned int jouer();

		/** @brief Permet d'effectuer un swap  .
        * @param [in] macase : Position de la case dans le plateau (Tableau).
        * @pre  0 <= macase && macase <= tailleh_*taillel_ .
        * @return true le swap � �t� utilis�, false le swap n'a pa �t� utilis�.
        */
		bool Nswap(const unsigned int macase);

		/** @brief Autorise ou non la pose d'un pion  .
        * @param [in] macase : Position de la case dans le plateau (Tableau).
        * @pre  0 <= macase && macase <= tailleh_*taillel_ .
        * @return true si interdit de poser un pion, false sinon.
        */
        bool verifcase(const unsigned int macase);

        /** @brief Permet l'abandon d'une partie par un joueur  .
        */
		void quit();

		/** @brief Apr�s la pose d'un pion cherche la victoire du joueur (r�cursif).
        * @param [in,out] nb : nombre d'indice enregsitr�
        * @param [in] macase : Position de la case dans le plateau (Tableau).
        * @param [in,out] tind[] : tableau d'indice des cases visit�es.
        * @pre  0 <= macase && macase <= tailleh_*taillel_ .
        * @return true il y a victoire, false sinon.
        */
		bool recurs(unsigned int nb,const unsigned int macase, unsigned int tind[]);

        /** @brief V�rifie que la lettre est dans le plateau .
        * @param [in] c : lettre � v�rifier .
        * @return true si comprise, false si non comprise.
        */
		bool estCharCorrect(const char c);

		/** @brief V�rifie que le chiffre est un dans le plateau.
        * @param [in] nb : chiffre � v�rifier.
        * @return un boolean compris, false non compris.
        */
		bool estChiffreCorrect(const unsigned int nb);

	private:
        /*Hauteur du plateau*/
		unsigned int tailleh_;
		/*Largeur du plateau*/
		unsigned int taillel_;
		/*Poiteur sur un tableau de type MaCase*/
		MaCase* tableau_;
		/*Bool�en indiquant la couleur en cours*/
		bool couleur_;


	   /** @brief Allocation Dynamique d'un tableau .
       * @pre  2<=tailleh_ && tailleh_<=26
       * @pre  2<=taillel_ && taillel_<=26
       */
	   void CreerTableau();



};


/** @brief Saisie d'un chiffre (lecture robuste).
* @param [in] msgSaisie : chiffre � v�rifier.
*/
unsigned int saisirChiffre(const std::string msgSaisie);

/** @brief Saisie d'un caract�re (lecture robuste).
* @param [in] msgSaisie : char � v�rifier.
*/
char saisirChar(const std::string msgSaisie);
#endif
