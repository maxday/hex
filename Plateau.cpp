#include <iostream>
#include <cassert>
#include "Plateau.h"
#include "MaCase.h"
using namespace std;

/**
 * @file Plateau.cpp
 * @brief Implémentation de la classe Plateau.
 * @author David Maxime - Adjab Mehdi
 */

void repete(string& matrice, string motif,unsigned int nbf) {
   for(unsigned int i=0;i<nbf;++i)
	       matrice=matrice+motif;
}

unsigned int saisirChiffre(const string msgSaisie) {
	unsigned int n;
	cout << msgSaisie << flush;
	cin >> n;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(CHAR_MAX, '\n');
	}

	return n;
}
char saisirChar(const string msgSaisie) {
    string e;
    cout << msgSaisie ;
	cin >> e;
	return e[0];
}






Plateau::Plateau(const unsigned int tailleh, const unsigned int taillel) {
    assert((2<=tailleh && tailleh<=26) && (2<=taillel && taillel<=26));
	tailleh_=tailleh;
	taillel_=taillel;
	couleur_=MaCase::color(0);
	CreerTableau();
}
Plateau::~Plateau() {
	delete [] tableau_;
}

void Plateau::CreerTableau() {
    assert((2<=tailleh_ && tailleh_<=26) && (2<=taillel_ && taillel_<=26));
	tableau_ = new MaCase[taillel_*tailleh_];
}
void  Plateau::joueur(){
	string nom1,nom2,tmp;
	cout<<"-----------Entrer le premier nom-----------"<<endl;
	cin>>nom1;
    cout<<"-----------Entrer le deuxieme nom----------"<<endl<<endl;
	cin>>nom2;

	/*Srand tire au sort le premier joueur*/
	if(rand()%2==1){
		tmp=nom1;
		nom1=nom2;
		nom2=tmp;
	}
	cout<<" le joueur n°1 est"<<" "<<nom1<<endl;
	cout<<" le joueur n°2 est"<<" "<<nom2<<endl<<endl;
}
bool Plateau::estCouleur1() {
	return couleur_==MaCase::color(0);
}
unsigned int Plateau::jouer(){
	unsigned int i=1,x,macase;
	char yletter;
	/*Détermine le joueur en cours,
	 * true joueur 1 (i=1) et false joueur 2 (i=2) */
	if(!couleur_)
		i=2;
	cout<<"C'est au tour du joueur n°"<<i<<endl;
	/*Demande de pose d'un pion tant qu'il n'écrase pas un autre*/
	do {
		/*Saisie le chiffre tant qu'il ne correspond pas au attente
		 (Lecture robuste)*/
	    do
	    	x=saisirChiffre("Entrez un chiffre ou 0 pour abandonner");
	    while (x!=0 && !estChiffreCorrect(x));
	    /*Si chiffre = 0 abandon demandé*/
		if(x==0) {
			quit();
	     do
	    	x=saisirChiffre("Entrez un chiffre");
	     while (!estChiffreCorrect(x));
		}
		do
	    	yletter=saisirChar("Saisir une lettre ");
	    while (!estCharCorrect(yletter));
	    	macase = getCXYOK(x,int(yletter)-(int('a')-1));
	    }
	    while(verifcase(macase));

	    /*Pose du pion*/
	    putXYOK(x,int(yletter)-(int('a')-1));
	    return macase;
}
bool Plateau::estCharCorrect(const char c) {
    return(c >= 'a' && c <= char(96+tailleh_));
}
bool Plateau::estChiffreCorrect(const unsigned int nb) {
	 return(nb > 0 && nb <= taillel_);
}
void Plateau::inverseCouleur() {
	couleur_=!couleur_;
}
void Plateau::putXYOK(const unsigned int x,const unsigned int y) {
    assert( 0 < x && x <= taillel_ &&   0 < y && y <= tailleh_);
	bool coul=getCouleur();
	if(coul)
		tableau_[(x-1)*tailleh_+y-1].PutCoul(MaCase::a);
	else
		tableau_[(x-1)*tailleh_+y-1].PutCoul(MaCase::b);

}
bool Plateau::estLibre(const unsigned int macase) {
	assert(0 <= macase && macase <= tailleh_*taillel_);
	return (tableau_[macase].getCoul()==32);
}
bool Plateau::getCouleur() {
	return couleur_;
}
unsigned int Plateau::getCXYOK(const unsigned int x,const unsigned int y){
    assert( 0 < x && x <= taillel_ &&   0 < y && y <= tailleh_);
    return (x-1)*tailleh_+y-1;
}
void Plateau::getXYOK(const unsigned int x,const unsigned int y)const {
    assert( 0 < x && x <= taillel_ &&   0 < y && y <= tailleh_);
    /*Affiche le pion sur la case du plateau en fonction
     du poste du tableau lui correspondant*/
    cout << " " <<char(tableau_[(x-1)*tailleh_+y-1].getCoul())<< " ";
}
bool Plateau::verifcase(const unsigned int macase){
    assert(0 <= macase && macase <= tailleh_*taillel_);
    if(!estLibre(macase)) {
		cout<<"Impossible de poser un pion"<<endl;
		return true;
	}
 	return false;
}

void Plateau::quit(){
	unsigned int num=2;
	if (couleur_)
		num=1;
	char rep=saisirChar("Voulez-vous abandonner la partie - y ou n");
	if (rep=='y'){
		cout<<"Fin du jeu"<<endl;
		/*Détermine le gagnant par forfait */
		cout<<"Victoire du joueur n°"<<((num+2)%2)+1<<" par abandon"<<endl;
		exit(1);
	}
}


bool Plateau::Nswap(const unsigned int macase){
	 assert(0 <= macase && macase <= tailleh_*taillel_);
	char rep;
	cout<<"Voulez-vous utiliser votre swap joueur n°2 - y ou n"<<endl;
	cin >>rep;

	if(rep=='y') {
		/*Swap accepté on remplace automatiquement le premier pion
		rouge posé par un bleu*/
		tableau_[macase].PutCoul(MaCase::a);
		/*màj affichage*/
		EditerMatrice();
		return true;
	}
	/*Si non le joueur 1 reprend la main*/
	inverseCouleur();
	return false;
}


bool Plateau::recurs(unsigned int nb, const unsigned int macase, unsigned int tind[]) {
	assert(0 <= macase && macase <= tailleh_*taillel_);
	/* Un gagant existe, on sort de la fonction */
	if(tind[tailleh_*taillel_+1]==tind[tailleh_*taillel_+2] && tind[tailleh_*taillel_+1]!=8000)
		return true;

	if(!tableau_[macase].getEstDefini())
		tableau_[macase].definiAutor(macase,tailleh_,taillel_);
	unsigned int i;

	for(i=0;i<nb && tind[i]!=macase;++i);
	if(i==nb) {
		tind[nb]=macase;
		nb++;
		/*Tableau correspondant aux indices des cases aux alentours
		 de la case courante, respectivement Hautgauche, Haut, Hautdroite,
		 Basdroite, bas, bas gauche*/
		unsigned int tcase[6]={macase-1,macase-tailleh_-1,macase-tailleh_,macase+1,macase+tailleh_+1,macase+tailleh_};

		/*Vérifie le droit de déplacement*/
		if(tableau_[macase].getAutorisation(4)  && tableau_[macase].getAutorisation(5)) {
			/*si joueur 2*/
			if(couleur_)
			/*Modification d'un poste définissant une victoire,
			  il n'est plus à 8000 */
			tind[tailleh_*taillel_+1]=4000;
		}
		if(tableau_[macase].getAutorisation(1)  && tableau_[macase].getAutorisation(2)) {
			if(couleur_)
				tind[tailleh_*taillel_+2]=4000;
		}
		if(tableau_[macase].getAutorisation(0)  && tableau_[macase].getAutorisation(1)) {
			/*si joueur 1*/
			if(!couleur_)
				tind[tailleh_*taillel_+2]=4000;
		}
		if(tableau_[macase].getAutorisation(3)  && tableau_[macase].getAutorisation(4)) {
			if(!couleur_)
				tind[tailleh_*taillel_+1]=4000;
		}

		/*Pour chaque case adjacentes s'il y à l'autorisation
		 et qu'il s'agit de la  bonne couleur on fait appel
		 à la même fonction*/
		for(unsigned int z=0;z<6;++z) {
			if(!tableau_[macase].getAutorisation(z)&& tableau_[tcase[z]].getCoul()==tableau_[macase].getCoul()) {

				recurs(nb,tcase[z],tind);
			}

		}
	}
	/*Si les deux premiers postes de Tind correspondent à 8000 il y à une victoire*/
	if(tind[tailleh_*taillel_+1]==tind[taillel_*tailleh_+2] && tind[tailleh_*taillel_+1]!=8000)
		return true;
	return false;
}

void Plateau::EditerMatrice(){
	string matrice="";
	unsigned int i,borneBoucle1=taillel_,borneBoucle2,borneBoucle3,nbLignesEgales=0;
	bool sup=(taillel_>tailleh_),ega=(taillel_==tailleh_),inf=(taillel_<tailleh_);
	//VERIFICATIONS PRELIMINAIRES
	if(sup) {
		borneBoucle1 = tailleh_;
        nbLignesEgales = (taillel_+1)-(tailleh_+1)-1;
	}
	if(inf)
        nbLignesEgales=(tailleh_+1)-(taillel_+1)-1;

	//GENERATION DE LA MATRICE
	for(i=0;i<borneBoucle1;++i) {
		if(sup)
			borneBoucle2 = tailleh_+nbLignesEgales-i;
		else
			borneBoucle2 = taillel_-i-1;
		repete(matrice,"0",borneBoucle2);
		matrice=matrice+"h";
		repete(matrice,"12",i);
		if(inf || ega || (sup && i!=taillel_-1))
			matrice=matrice+"1";
		matrice=matrice+"e*";
	}
	if(inf)
		matrice=matrice+"3";
	if(ega) {
		matrice=matrice+"32";
		repete(matrice,"12",taillel_-1);
		matrice=matrice+"*";
		borneBoucle1=taillel_;
    }
	if(sup) {
		repete(matrice,"0",taillel_-tailleh_-1);
		matrice=matrice+"h";
        matrice=matrice+"";
        repete(matrice,"12",tailleh_);
        matrice=matrice+"*";
    }
	if(inf) {
		repete(matrice,"21",taillel_);
		matrice=matrice+"e*3";
		borneBoucle1=nbLignesEgales;
    }
	if(!sup) {
        for(i=0;i<borneBoucle1;++i) {
            if(inf)
                borneBoucle2=taillel_;
            if(ega)
                borneBoucle2=taillel_-i-1;
            if(i!=0) {
               	repete(matrice,"0",i-1);
            matrice=matrice+"m";
            }
            if(i==0 && ega)
                matrice=matrice+"3";
			repete(matrice,"45",borneBoucle2);
            if(inf)
                matrice=matrice+"71e*3";
			if(ega && i!=0)
                matrice=matrice+"4g*3";
            if(ega && i==0)
                matrice=matrice+"4*3";
        }
        if(inf){
           	if(i!=0) {
                repete(matrice,"0",i-1);
           	    matrice=matrice+"m";
            }
        repete(matrice,"45",taillel_-1);
        matrice=matrice+"46*3";
       }
	}
    else  {
		for(i=0;i<nbLignesEgales;++i) {
           if(!sup)
                repete(matrice,"0",nbLignesEgales-1);
           if(sup && i!=0)
                repete(matrice,"0",nbLignesEgales-1-i);
           if(sup && i==0)
                repete(matrice,"0",nbLignesEgales-1);
           if(sup)
                matrice=matrice+"h";
           matrice=matrice+"d";
		   repete(matrice,"12",tailleh_);
           if(i==0)
              matrice=matrice+"18*";
           else
              matrice=matrice+"18f*";
		}
		if(nbLignesEgales==0)
			matrice=matrice+"3";
		else
			matrice=matrice+"3";
		repete(matrice,"21",tailleh_);
		if(nbLignesEgales==0)
			matrice=matrice+"8*3";
		if(nbLignesEgales!=0)
			matrice=matrice+"8f*3";
    }
	if(!ega) {
        if(sup)
			borneBoucle1=tailleh_;
        if(inf)
            borneBoucle1=taillel_;
        for(i=0;i<borneBoucle1;++i) {
            if(sup) {
                borneBoucle2=i;
                borneBoucle3=tailleh_-i-1;
			}
			if(inf) {
				borneBoucle2=nbLignesEgales+i+1;
				borneBoucle3=taillel_-1-i;
			}
			if(i!=0 && sup)
				repete(matrice,"0",borneBoucle2-1);
			if(sup && i==0)
				repete(matrice,"0",borneBoucle2);
			if(inf)
				repete(matrice,"0",borneBoucle2-1);
			if(sup && i!=0)
				matrice=matrice+"m";
			if(!sup)
				matrice=matrice+"m";
			repete(matrice,"45",borneBoucle3);
			if(sup)
				matrice=matrice+"4f*3";
			else {
				if(i==0)
					matrice=matrice+"4*3";
				else
					matrice=matrice+"4f*3";
			}
		}
	}
	repete(matrice,"0",tailleh_-1);
    matrice=matrice+"S*";
    //une fois générée, on la lit.
    lireMatrices(matrice);
}


void Plateau::CalculCase(const unsigned int i,const unsigned int nbligne, const unsigned int var) {
	assert(0<nbligne && nbligne<=(tailleh_*taillel_)-1 );
	bool sup=(taillel_>tailleh_);
	bool ega=(taillel_==tailleh_);
	bool inf=(taillel_<tailleh_);
    unsigned int chiffre,lettre,borne;
	if(i==0) {
		 chiffre=nbligne+1-var;
		 lettre=var;
	}
	if(i==1 && (sup || inf))
		borne=taillel_;
	if(i==1 && ega)
		borne=tailleh_;
	if(i==1) {
		lettre=var+nbligne-borne;
		chiffre=borne-var+1;
	}
    if(i==2) {
    	chiffre=taillel_+1-var;
	    if(sup)
		    lettre=var+nbligne-tailleh_;
	    else
	    	lettre=tailleh_;
    }
	getXYOK(chiffre,lettre);
}

void Plateau::lireMatrices(const std::string& matrice) {

	string ligne="";
	ligne=char(MaCase::b);
	repete(ligne," ",4*(tailleh_+taillel_-1));
	ligne=ligne+char(MaCase::a);
	cout << ligne << endl;
	unsigned int t=0,u=0,nbligne=0,cpt1=1,cpt2=0,cpt3=0,cpt4=1,cpt5=1;
	for(unsigned int i=0;i<matrice.size();++i) {
	     switch(matrice[i]) {
			 case '*' :
				 nbligne++;
				 t=u=0;
				 cout << endl;
			 break;
			 case '0' :
				 cout << "    ";
			 break;
			 case '1' :
				 cout << "___";
			 break;
			 case '2' :
				 t++;
				 cout << "/";
				 CalculCase(0,nbligne,t);
				 cout<< "\\";
			 break;
			 case '3' :
				  cout << " ";
			 break;
			 case '4' :
				  cout << "\\___/";
			 break;
			 case '5' :
				 u++;
				 CalculCase(1,nbligne,u);
			 break;
			 case '6' :
				 u++;
				 CalculCase(2,nbligne,u);
				 cout<<"\\";
			 break;
			 case '7' :
				 cout << "\\";
			 break;
			 case '8' :
				  cout << "/";
			 break;
			 case 'h' :
				cout << cpt1;
				if(cpt1<10)
				   cout << " ";
				cpt1++;
			 break;
			 case 'e' :
				cout << char(97+cpt2);
				cpt2++;
			 break;
			 case 'g' :
				cout << "   ";
				cout << cpt4;
				cpt4++;
			 break;
			 case 'm' :
				cout << char(97+cpt3)<<"   ";
				cpt3++;
			 break;
			 case 'f' :
				cout << "   "<<cpt5;
				cpt5++;
			 break;
			 case 'S' :
				 cout <<char(96+tailleh_)<<"   "<<taillel_;
			 break;
	     }
	}
	ligne=char(MaCase::a);
	repete(ligne," ",4*(tailleh_+taillel_-1));
	ligne=ligne+char(MaCase::b);
	cout << ligne << endl;
}
