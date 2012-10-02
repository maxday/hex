#ifndef MACASE_H_
#define MACASE_H_

/**
 * @file MaCase.h
 * @author David Maxime - Adjab Mehdi
 * @brief D�finit le composant MaCase et les op�rations associ�es.
 */


class MaCase {
	public :


       enum color {a='b', b='r', vide=32};// 32 �tant le caract�re ASCII de l'espace


	    /** @brief Constructeur de case du plateau  .
        * @param [in] couleur: Initialisation � vide
        */
		MaCase(color couleur=vide);

		/** @brief Destructeur de case du plateau  .
        */
		~MaCase();

		/** @brief R�cup�re la couleur d'une case .
		* @return un caract�re correspondant � la couleur rouge ou bleue.
        */
		color getCoul() const;

		/** @brief Accorde les autorisations de d�placement vers les cases qui entoure
		* la case courante .
        * @param [in] macase: la case courante.
        * @param [in] tailleh: Hauteur du plateau.
        * @param [in] taillel: Largeur du plateau.
        * @pre  2<=tailleh && tailleh<=26
        * @pre  2<=taillel && taillel<=26
        */
		void definiAutor(const unsigned int macase,const unsigned int tailleh, const unsigned int taillel);


        /** @brief  Deposer sur le plateau le pion d'un joueur
        * avec la couleur correspondante.
        * @param [in] couleur: indice de la case.
        */
		void PutCoul(const color couleur);


		/** @brief Renvoi l'autorisation de d�placement sur cette case .
        * @param [in] i: indice de la case.
        * @pre 0 <= i && i <=6 .
        * @return un boolean true autoriser, false refuser.
        */
		bool getAutorisation(const unsigned int i) const ;

		/** @brief Permet de savoir si les priorit� d'une case on �t� d�finie .
        * @return un boolean est defini, false non defini.
        */
		bool getEstDefini() const;

	private :

		bool* autorisation_; //pointeur sur un tableau de bool�en
		color coloris_; //prend la valeur " " ou celle de a ou b
		bool estDefiniAutor_; //a t-on d�ja defini les autorisations pour cette case?


};



#endif /* CASE_H_ */
