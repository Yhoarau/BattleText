#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Arme.h"
#include "Inventaire.h"

enum e_Effet
{
    SOIN, POISON, GEL, RAGE, CHARGE, MARQUE, INVINCIBILITE,
};

class Personnage
{
    public:
        Personnage();
        Personnage(std::string nom);
        Personnage(std::string nom, std::string nomArme, int degatsArme, int durabiliteArme);
        virtual ~Personnage();

        void afficherEtat() const;
        void recevoirDegats(int NbDegats);
        void attaquer(Personnage &cible) ;
        void boirePotionDeVie(int quantitePotion);
        void changerArme(Arme nomNouvelleArme);
        void changerPosture(std::string nouvellePosture);
        void checkArme();
        void refreshInventaire();
        void appliquerBonus();
        void appliquerMalus();
        bool checkInventaire();
        void setNom(std::string);
        void setMana(int);
        void setBouclier(int);
        void setInventaire(std::vector<Objet*> nomObj, std::vector<unsigned> nb);
        void setBonus(std::vector<std::vector<int>> Bonus);
        void ajouterBonus(std::vector<int>);
        void setMalus(std::vector<std::vector<int>> Malus);
        void ajouterMalus(std::vector<int>);
        bool estVivant() const;
        bool estArme() ;
        std::string getNom();
        int getMana();
        int getBouclier();
        std::string getPosture();
        std::vector<std::vector<int>> getBonus();
        std::vector<std::vector<int>> getMalus();
        Inventaire getInventaire();
        Arme getArme();

    protected:

    private:
        std::string m_nom;
        std::string m_posture;
        std::vector<std::vector<int>> m_bonus;
        std::vector<std::vector<int>> m_malus;
        int  m_vie;
        int m_mana;
        int m_bouclier;
        Arme m_arme;
        Inventaire m_inventaire;
};

#endif // PERSONNAGE_H
