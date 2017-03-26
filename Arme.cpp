#include "Arme.h"

using namespace std;

Arme::Arme() : Objet(ARME), m_degats(0), m_durabilite(0)
{
    //ctor
}

Arme::Arme(std::string nom, int degats, int durabilite)  : m_degats( degats), m_durabilite(durabilite),
        Objet(nom, ARME, (  string (30 - nom.size(), ' ') +  '(' +
                               "Degats : " + to_string(degats) + ", Durabilite : " + to_string(durabilite) + ')'))

{
   /* string Space(" ", 9);
    m_degats= degats; m_durabilite=durabilite;
    Objet(nom, "Arme", ( "Degats : " + to_string(degats) + ", Durabilite : " + to_string(durabilite)));
    */
}

Arme::~Arme()
{
    //dtor
}

void Arme::changer(string nom, int degats, int durabilite)
{
    m_nom = nom;
    m_degats = degats;
    m_durabilite = durabilite;
}

void Arme::afficher() const
{
    cout << "Arme : " << m_nom << " (Degats : " << m_degats << ", Durabilite : " << m_durabilite << ")" << endl;
}

void Arme::abimer(int dmg)
{
    m_durabilite -=dmg;
    if (m_durabilite < 0) m_durabilite = 0;
}

string Arme::getNom() const
{
    return m_nom;
}

int Arme::getDegats() const
{
    return m_degats;
}

int Arme::getDurabilite() const
{
    return m_durabilite;
}
