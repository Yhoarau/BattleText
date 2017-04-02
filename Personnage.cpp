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
    cout << "Bouclier : " << m_bouclier << endl;
    cout << "Mana : " << m_mana << endl;
    cout << "Bonus : ";
    if(m_bonus.size() == 0) cout << "Aucun";
    for(const vector<int> & B : m_bonus)
        {
            switch(B[0])
            {
            case SOIN :
                cout << "Soin ";
                break;
            case RAGE :
                cout << "Rage ";
                break;
            case INVINCIBILITE :
                cout << "Invincibilite";
                break;
            }


        }
    cout << endl << "Malus : ";
    if(m_malus.size() == 0) cout << "Aucun";
    for( const vector<int> & M : m_malus)
        {
            switch(M[0])
            {
            case POISON :
                cout << "Poison ";
                break;
            case GEL :
                cout << "Gel ";
                break;
            case CHARGE :
                cout << "Charge ";
                break;
            case MARQUE :
                cout << "Marque ";
                break;
            default :
                break;
            }
        }
    cout << endl << "Posture : " << m_posture << endl;
    m_arme.afficher();
    cout <<endl;
}
void Personnage::recevoirDegats(int NbDegats)
{
    bool estInvincible(false);
    for(vector<int> & B : m_bonus)
        if(B[0] == INVINCIBILITE)
            estInvincible = true;
    if (estInvincible) return;
    if (m_posture == "Defense") NbDegats = NbDegats/2;
    if(m_bouclier != 0)
    {
        if(m_bouclier <= NbDegats)
        {
            NbDegats = NbDegats - m_bouclier;
            m_bouclier = 0;
        }
        else
            m_bouclier -= NbDegats;
    }
     m_vie -= NbDegats;

    if (m_vie < 0) m_vie = 0;
}
void Personnage::attaquer(Personnage &cible)
{
    if (m_posture != "Attaque") return;
    bool Enrage(false);

    for(vector<int> & B : m_bonus)
        if(B[0] == RAGE)
            Enrage = true;
    if(m_arme.getNom() == "Bombe nucléaire")
        this->recevoirDegats(m_arme.getDegats());
    if(Enrage)
        cible.recevoirDegats(2*(m_arme.getDegats()));
    else
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

void Personnage::appliquerBonus()
{
    for(unsigned i(0); i < m_bonus.size(); ++i)
    {
        switch(m_bonus[i][0])
        {
        case SOIN :
            this->boirePotionDeVie(m_bonus[i][2]) ;
            if(  --m_bonus[i][1] == 0 ) m_bonus.erase(m_bonus.begin() + i);
            break;
        case RAGE :
            if( --m_bonus[i][1] == 0)
                m_bonus.erase(m_bonus.begin() + i);
        case INVINCIBILITE :
            if( --m_bonus[i][1] == 0)
                m_bonus.erase(m_bonus.begin() + i);
        }
    }
}

void Personnage::appliquerMalus()
{

    for(unsigned i(0); i < m_malus.size(); ++i)
    {
        switch(m_malus[i][0])
        {
        case POISON :
            m_vie -= m_malus[i][2];
            if(m_vie < 0) m_vie =0;
            if( --m_malus[i][1] == 0)
                m_malus.erase(m_malus.begin() + i);
            break;
        case GEL :
            if( --m_malus[i][1] == 0)
                m_malus.erase(m_malus.begin() + i);
            break;
        case CHARGE :
            if ( --m_malus[i][1] == 0)
            {
                m_malus.erase(m_malus.begin() + i);
            }
            break;
        case MARQUE :
            if ( --m_malus[i][1] == 0)
            {
                m_malus.erase(m_malus.begin() + i);
                this->recevoirDegats(m_malus[i][2]);
            }
            break;
        }

    }
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

void Personnage::setMana(int mana)
{
    m_mana = mana;
}

void Personnage::setBouclier(int bouclier)
{
    m_bouclier = bouclier;
}

void Personnage::setInventaire(vector<Objet*> objs, vector<unsigned> nbObj)
{
    m_inventaire.setContenu(objs);
    m_inventaire.setExemplaires(nbObj);
    //m_inventaire.setType(type);
   // m_inventaire.setDescription(desc);
}

void Personnage::setBonus(vector<vector<int>> Bonus)
{
    m_bonus = Bonus;
}

void Personnage::ajouterBonus(vector<int> Bonus)
{
    m_bonus.push_back(Bonus);
}

void Personnage::setMalus(vector<vector<int>> Malus)
{
    m_malus = Malus;
}

void Personnage::ajouterMalus(vector<int> Malus)
{
    m_malus.push_back(Malus);
}

string Personnage::getNom()
{
    return m_nom;
}

int Personnage::getMana()
{
    return m_mana;
}

int Personnage::getBouclier()
{
    return m_bouclier;
}

string Personnage::getPosture()
{
    return m_posture;
}

vector<vector<int>> Personnage::getBonus()
{
    return m_bonus;
}

vector<vector<int>> Personnage::getMalus()
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



