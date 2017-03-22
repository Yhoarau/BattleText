#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Arme.h"
#include "Inventaire.h"


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
        bool checkInventaire();
        void setNom(std::string);
        void setInventaire(std::vector<Objet> nomObj, std::vector<unsigned> nb);
        void setBonus(std::vector<std::string> Bonus);
        void setMalus(std::vector<std::string> Malus);
        bool estVivant() const;
        bool estArme();
        std::string getNom();
        std::string getPosture();
        std::vector<std::string> getBonus();
        std::vector<std::string> getMalus();
        Inventaire getInventaire();
        Arme getArme();

    protected:

    private:
        std::string m_nom;
        std::string m_posture;
        std::vector<std::string> m_bonus;
        std::vector<std::string> m_malus;
        int  m_vie;
        int m_mana;
        Arme m_arme;
        Inventaire m_inventaire;
};

#endif // PERSONNAGE_H
