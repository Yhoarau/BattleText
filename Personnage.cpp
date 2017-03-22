#include "Personnage.h"

using namespace std;

Personnage::Personnage() :m_nom("Inconnu"), m_vie(100), m_mana(100), m_posture("Defense")

{
    //ctor
}

Personnage::Personnage(std::string nom) : m_nom(nom), m_vie(100), m_mana(100), m_posture("Defense")
{
    //ctor
}
/*
Personnage::Personnage(std::string nom, std::string nomArme, int degatsArme, int durabiliteArme) : m_nom(nom), m_vie(100), m_mana(100),
                         m_posture("Defense"), m_arme(nomArme, degatsArme, durabiliteArme)
{

} */

Personnage::~Personnage()
{
    //dtor
}

void Personnage::afficherEtat()const
{
    cout << "Etat de : " << m_nom << endl;
    cout << "Vie : " << m_vie << endl;
    cout << "Mana : " << m_mana << endl;
    cout << "Posture : " << m_posture << endl;
    m_arme.afficher();
    cout <<endl;
}
void Personnage::recevoirDegats(int NbDegats)
{
    if (m_posture == "Defense") m_vie -= NbDegats/2;
    else m_vie -= NbDegats;

    if (m_vie < 0) m_vie = 0;
}
void Personnage::attaquer(Personnage &cible)
{
    if (m_posture != "Attaque") return;
    cible.recevoirDegats(m_arme.getDegats());
    m_arme.abimer(1);
}
void Personnage::boirePotionDeVie(int quantitePotion)
{
    m_vie += quantitePotion;
    if (m_vie > 100) m_vie = 100;
}
void Personnage::changerArme(Arme nomNouvelleArme)
{
    m_arme = nomNouvelleArme;
}

void Personnage::changerPosture(std::string nouvellePosture)
{
    m_posture = nouvellePosture;
}

void Personnage::checkArme()
{
        if (m_arme.getDurabilite() == 0)
        {
            vector<string> Contenu = m_inventaire.getNomsObj();
            vector<unsigned> Exemplaires = m_inventaire.getExemplaires();
            /* for(unsigned i(0); i < Contenu.size(); ++i)
                if(Types[i] == "Arme" && Contenu[i] == m_arme.getNom())
                {
                    --Exemplaires[i];
                } */

            vector<string>::iterator it = find(Contenu.begin(), Contenu.end(), m_arme.getNom() );
            unsigned i = distance(Contenu.begin(), it);
            if(it != Contenu.end()) --Exemplaires[i];

            m_inventaire.setExemplaires(Exemplaires);
            m_inventaire.refreshInventaire();

            m_arme.changer("", 0, 0);

        }

}

void Personnage::refreshInventaire()
{
    m_inventaire.refreshInventaire();
}

bool Personnage::checkInventaire()
{
    m_inventaire.checkInventaire();
}

bool Personnage::estVivant() const
{
    return (m_vie > 0);
}

bool Personnage::estArme()
{
    return (m_arme.getDegats() != 0);
}

void Personnage::setNom(string nom)
{
    m_nom = nom;
}

void Personnage::setInventaire(vector<Objet> objs, vector<unsigned> nbObj)
{
    m_inventaire.setContenu(objs);
    m_inventaire.setExemplaires(nbObj);
    //m_inventaire.setType(type);
   // m_inventaire.setDescription(desc);
}

void Personnage::setBonus(vector<string> Bonus)
{
    m_bonus = Bonus;
}

void Personnage::setMalus(vector<string> Malus)
{
    m_malus = Malus;
}

string Personnage::getNom()
{
    return m_nom;
}
string Personnage::getPosture()
{
    return m_posture;
}

vector<string> Personnage::getBonus()
{
    return m_bonus;
}

vector<string> Personnage::getMalus()
{
    return m_malus;
}

Inventaire Personnage::getInventaire()
{
    return m_inventaire;
}

Arme Personnage::getArme()
{
    return m_arme;
}

