#include "MaCase.h"
#include <cassert>
#include <iostream>

/** @file MaCase.cpp
 * @brief Implémentation de la classe MaCase.
 * @author David Maxime - Adjab Mehdi
 */

MaCase::MaCase(color couleur) {
	estDefiniAutor_=false;
	if(couleur!=a || couleur!=b)
		coloris_=vide;
	else
		coloris_=couleur;

	autorisation_ = new bool[6];
		for(unsigned int i=0;i<6;++i)
			autorisation_[i]=false;
}
MaCase::~MaCase() {
	delete [] autorisation_;
}
MaCase::color MaCase::getCoul() const {
	return coloris_;
}
void MaCase::PutCoul(const color coul) {
	coloris_=color(coul);
}
bool MaCase::getAutorisation(const unsigned int i) const {
	assert(i<6);
	return autorisation_[i];
}
bool MaCase::getEstDefini() const {
	return estDefiniAutor_;
}
void MaCase::definiAutor(const unsigned int macase, const unsigned int tailleh, const unsigned int taillel) {
	assert((2<=tailleh && tailleh<=26) && (2<=taillel && taillel<=26));
	/*Regarde les déplacements possibles autour de la case*/
	if(macase>=tailleh*taillel-tailleh)
		autorisation_[4]=autorisation_[5]=true;
	if(macase<tailleh)
		autorisation_[1]=autorisation_[2]=true;
	if(macase%tailleh==0)
		autorisation_[0]=autorisation_[1]=true;
	if(macase%tailleh==tailleh-1)
		autorisation_[3]=autorisation_[4]=true;
}
