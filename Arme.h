#ifndef ARME_H
#define ARME_H

#include <iostream>
#include <string>
#include "Objet.h"

class Arme : public Objet
{
    public:
        Arme();
        Arme(std::string nom, int degats, int durabilite);
        virtual ~Arme();

        void changer(std::string nom, int degats, int durabilite);
        void afficher() const;
        void abimer(int dmg);
        std::string getNom() const;
        int getDegats() const;
        int getDurabilite() const;

    protected:

    private:
        int m_degats;
        int m_durabilite;
};

#endif // ARME_H
