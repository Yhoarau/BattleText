#include "Personnage.h"

using namespace std;

Arme A1("Grosse epee rouillee", 10, 8);
Arme A2("Fine epee aiguisee", 20, 3);
Arme A3("Enorme massue a usage unique", 50, 1);
Arme A4("Excalibur", 80, 100);
Arme A5("Bombe nucleaire"," Touche les deux personnages", 1000, 1);
Objet O1("Potion de vie", POTION, "Regenere 10 points de vie");
Objet O2("Potion de poison", POTION, "Inflige 5 points de degats par tour a l'ennemi pendant 5 tours");
Objet O3("Potion de gel", POTION, "Empeche l'ennemi d'agir pendant 2 tours");
Objet O4("Potion de rage", POTION, "Double vos degats pendant les 2 prochains tours");
Objet O5("Potion de mana", POTION, "Rend 30 points de mana");
Objet O6("Potion d'invincibilite", POTION, "Vous imunise de tous degats pendant 3 tours");

std::vector<Objet*> ObjetsExistants = {&A1, &A2, &A3, &A4, &A5, &O1, &O2, &O3, &O4, &O5, &O6};

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
            case INVINCIBILITE :
                cout << "Invincibilite ";
                break;
            case PROVOQUE :
                cout << "Provoque ";
                break;
            case ETOURDI :
                cout << "Etourdi ";
                break;
            case DESARME :
                cout << "Desarme ";
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
        case PROVOQUE :
            if ( -- m_malus[i][1] == 0)
            {
                m_malus.erase(m_malus.begin() + 1);
            }
            break;
        case ETOURDI :
            if ( -- m_malus[i][1] == 0)
            {
                m_malus.erase(m_malus.begin() + 1);
            }
            break;
        case DESARME :
            if ( -- m_malus[i][1] == 0)
            {
                m_malus.erase(m_malus.begin() + 1);
            }
            break;
        }

    }
}

void Personnage::UtiliserTechnique(Personnage* Cible)
{
    unsigned Choix;
    cout << "1) Provoque " << setw(100 - 12)
    << " Force la position offensive de l'adversaire pendant 2 tours. " << endl;

    if(m_posture == "Defense")
    {
        cout << "2) Coup de bouclier " << setw(100 - 20)
        << " Inflige 5 points de degats et a 25% de chance d'étourdir l'ennemi. " << endl;
    }
    else if (m_posture == "Attaque")
    {
        cout << "2) Coup bas " << setw(100 - 12)
        << "Désarme l'ennemi pendant 2 tours." << endl;
    }
    cin >>Choix;

    while((m_posture == "Defense" && (Choix < 1 || Choix > 2)) ||( m_posture == "Attaque" && (Choix < 1 || Choix > 2)))
        {
            cout << "Veuillez saisir un chiffre correct" << endl ;
            if(cin.fail())
            {

                cin.clear();
                cin.ignore();

            }
            cin >> Choix;
        }

        switch(Choix)
        {
        case 1 :
            Cible->ajouterMalus({PROVOQUE, 2, 0});
            break;
        case 2 :
            if(m_posture == "Defense")
            {
                Cible-> recevoirDegats(5);
                if( (rand() % 3) == 0)
                    Cible -> ajouterMalus({ETOURDI, 1, 0});
            }
            else if (m_posture == "Attaque")
            {
                Cible -> ajouterMalus({DESARME, 2, 0});
            }
            break;
        }


}

bool Personnage::checkInventaire()
{
    return m_inventaire.checkInventaire();
}

bool Personnage::estVivant() const
{
    return (m_vie > 0);
}

bool Personnage::estArme()
{
    return (m_arme.getDegats() != 0);
}

unsigned Personnage::CheckNbObjet(string Obj)
{
    vector<string> Contenu = m_inventaire.getNomsObj();
    vector<unsigned> Exemplaires = m_inventaire.getExemplaires();

    vector<string>::iterator it = find(Contenu.begin(), Contenu.end(), Obj);
    unsigned i = distance(Contenu.begin(), it);
    if (it != Contenu.end()) return Exemplaires[i];
    return 0;

} //CheckNbObjet

void Personnage::UtiliserPotion(string nomPotion, Personnage* Cible)
{
    vector<string> Contenu = m_inventaire.getNomsObj();
    vector<unsigned> Exemplaires = m_inventaire.getExemplaires();
    vector<string> Types = m_inventaire.getType();
    vector<Objet*> Objs = m_inventaire.getContenu();

    for(unsigned i (0); i < Objs.size() ; ++i )
    {
         Objet O = *(Objs[i] );
        //cout << O.getType(); system("PAUSE");
        if(O.getType() == POTION)
        {
            if(O.getNom() == nomPotion && nomPotion == "Potion de vie")
            {
                this->ajouterBonus({SOIN, 1, 10});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de poison" )
            {
                Cible->ajouterMalus({POISON, 5, 5});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de gel")
            {
                Cible->ajouterMalus({GEL, 2, 0});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de rage")
            {
                this->ajouterBonus({RAGE, 3, 2});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de mana")
            {
                this->setMana(this->getMana() + 20);
                if(this->getMana() > 100) this->setMana(100);
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion d'invincibilite")
            {
                this->ajouterBonus({INVINCIBILITE, 4, 0});
                --Exemplaires[i];
            }

        }
    }

    this->setInventaire(Objs, Exemplaires);
    this->refreshInventaire();

} //UtiliserPotion

void Personnage::ChoixArme(Personnage* Cible)
{
    vector<Objet*> ObjetsP(m_inventaire.getContenu());
    vector<unsigned> NbObjetsP(m_inventaire.getExemplaires());
    vector<Arme> ArmesP;

    unsigned Choix(0);

    cout << "Veuillez choisir une arme parmi celles qui vous reste :" << endl << endl;

    unsigned ArmesRestantes(0);
    for (unsigned i(0); i < ObjetsP.size() ; ++i)
        {
            Objet O = *(ObjetsP[i]);
            if(O.getType() == ARME)
            {
                ++ArmesRestantes;

                cout << ArmesRestantes << ") " << O.getNom() << " (" << NbObjetsP[i] << ")" << O.getDescription() << endl;
                ArmesP.resize(ArmesP.size() + 1);

                 Arme* A = (Arme*)(ObjetsP[i]);

                /* Arme A (O.getNom(),
                         stoi(O.getDescription().substr((30 - O.getNom().size()) + 1 + 9, 4)),
                         stoi(O.getDescription().substr((30 - O.getNom().size()) + 1 + 28, 3))); */
                ArmesP[ArmesP.size() - 1] = *A;

            }
        }


    if (ArmesRestantes == 0)
        {
            cout << "Vous n'avez plus d'arme a disposition, vous ne pouvez plus attaquer" << endl << endl;
            return;
        }
    cout << ArmesRestantes + 1 << ") Retour" <<endl;
    cout << endl << "Entrez le numero de l'arme : ";
    cin >> Choix;

    while(Choix < 1 || Choix > ArmesRestantes + 1 || (Choix == ArmesRestantes + 1 && !(this->estArme())))
    {
        if(!(this->estArme())) cout << "Vous n'avez aucune arme equipee" << endl;
        cout << "Veuillez saisir un chiffre correct " << endl ;
        if(cin.fail())
        {

            cin.clear();
            cin.ignore();

        }
        cin >> Choix;
    }
    cout << endl << endl;

    if(Choix == ArmesRestantes + 1 && (this->estArme()))
        {
            system("cls");
            this->afficherEtat();
            this->ChoixActions(Cible);
        }
    else
    {
        for(Arme & A : ArmesP)
        if(A.getNom() == ArmesP[Choix - 1].getNom())
        this->changerArme(A);
    }

} // ChoixArme

void Personnage::ChoixActions(Personnage* Cible)
{
    unsigned Choix(0);

    if (!(this->checkInventaire()))
    {

        cout << "L'inventaire a rencontre un probleme"<< endl << endl;
        system("PAUSE");
        this->recevoirDegats(1000);
        return;
    }

    bool Block(false);
    bool Provock(false);
    bool Desarme(false);
    for(unsigned i(0); i < this->getMalus().size(); ++i)
    {
        if((this->getMalus()[i][0] == GEL) ||
           ((this->getMalus()[i][0] == CHARGE) && (this->getMalus()[i][1] >= 1)) ||
           (this->getMalus()[i][0] == ETOURDI))
                Block = true;

        if((this->getMalus()[i][0] == CHARGE) && (this->getMalus()[i][1] == 1))
            Cible->ajouterMalus({MARQUE, 1, this->getMalus()[i][2]});

        if(this->getMalus()[i][0] == PROVOQUE)
            Provock = true;

        if(this->getMalus()[i][0] == DESARME)
            Desarme = true;

    }

    if(Provock)
    {
        cout << "Vous etes contraints d'etre en position offensive" << endl << endl;
        this->changerPosture("Attaque");
        system("PAUSE");
    }

    if(Block)
    {
        cout << "Vous ne pouvez pas jouer ce tour." << endl << endl;
        system("PAUSE");
    }


    else if(this->getPosture() == "Defense")
    {
        cout << "1) Utiliser un objet du sac"  <<  endl;
        cout << "2) Utiliser une technique" << endl;
        cout << "3) Changer d'arme" << endl;
        cout << "4) Passer en posture offensive " << endl;
        cout << "5) Obtenir un objet au hasard" << endl;
        cout << "6) Ne rien faire " << endl << endl;

        cin >> Choix;

        while(Choix < 1 || Choix > 6)
        {
            cout << "Veuillez saisir un chiffre correct" << endl ;
            if(cin.fail())
            {

                cin.clear();
                cin.ignore();

            }
            cin >> Choix;
        }

        switch(Choix)
        {
        case 1:
            this->UtiliserObjet(Cible);
            break;
        case 2 :
            this->UtiliserTechnique(Cible);
            break;
        case 3 :
            this->ChoixArme(Cible);
            break;
        case 4 :
            this->changerPosture("Attaque");
            break;
        case 5:
            this->ObtenirObjet();
            break;
        case 6:
            break;
        default :
            break;
        }

    }
    else if (this->getPosture() == "Attaque")
    {
        cout << "1) Attaquer " << endl;
        cout << "2) Lancer un sort" << endl;
        cout << "3) Utiliser une technique" << endl;
        cout << "4) Utiliser un objet du sac " <<  endl;
        cout << "5) Changer d'arme" << endl;
        cout << "6) Passer en posture defensive " << endl;
        cout << "7) Ne rien faire " << endl << endl;
        cin >> Choix;

        while((Choix < 1 || Choix > 6) || (Desarme && Choix == 1))
        {
            if (Desarme && Choix == 1)
                cout << "Vous etes desarme, vous ne pouvez pas attaquer. " << endl;
            cout << "Veuillez saisir un chiffre correct" << endl ;
            if(cin.fail())
            {

                cin.clear();
                cin.ignore();

            }
            cin >> Choix;
        }

        switch(Choix)
        {
        case 1 :
            this->attaquer((*Cible));
            this->checkArme();
            break;
        case 2 :
            this->UtiliserSort(Cible);
            break;
        case 3 :
            this->UtiliserTechnique(Cible);
            break;
        case 4 :
            this->UtiliserObjet(Cible);
            break;
        case 5 :
            this->ChoixArme(Cible);
            break;
        case 6 :
            this->changerPosture("Defense");
            break;
        case 7 :
            break;
        default :
            break;

        }


    }
    this->appliquerBonus();
    this->appliquerMalus();

} //ChoixActions

 void Personnage::UtiliserObjet(Personnage* Cible)
{

    //Inventaire Inv(Player->getInventaire());
    vector<Objet*> ObjetsP(m_inventaire.getContenu());
    vector<Objet> ObjSansArmes;
    unsigned Choix;
    /*for (unsigned i(0); i < Inv.getType().size(); ++i)
        if(Inv.getType()[i] == "Arme")
            ObjetsP.erase(ObjetsP.begin() + i); */
    unsigned ObjetsRestants(0);
    for(unsigned i(0); i < m_inventaire.getContenu().size()  ; ++i)
        {
            Objet Ob = *(ObjetsP[i]);
            if (Ob.getType() != ARME)
            {

                ObjetsRestants++;
                Objet O (Ob.getNom(), Ob.getType(), Ob.getDescription());
                ObjSansArmes.resize(ObjSansArmes.size() + 1);
                ObjSansArmes[ObjSansArmes.size() - 1] = O;
                cout << ObjetsRestants << ") " << Ob.getNom() << " (" << m_inventaire.getExemplaires()[i] << ")"
                    << string (30 - Ob.getNom().size(), ' ')
                    << Ob.getDescription() << endl ;
            }
        }


    cout << ObjetsRestants + 1 << ") Retour" <<endl;
    cout << endl << "Entrez le numero de l'objet : ";

    cin >> Choix;

    while(Choix < 1 || Choix > ObjetsRestants + 1)
    {
        cout << "Veuillez saisir un chiffre correct " << endl ;
        if(cin.fail())
        {

            cin.clear();
            cin.ignore();

        }
        cin >> Choix;
    }
    if (Choix == ObjetsRestants + 1)
    {
        system("cls");
        this->afficherEtat();
        this->ChoixActions(Cible);
    }
    else if (ObjSansArmes[Choix - 1].getType() == POTION)
    {

        this->UtiliserPotion(ObjSansArmes[Choix - 1].getNom(), Cible);
    }

} //UitliserObjet

void Personnage::ObtenirObjet()
{
    unsigned Indice = rand() % ObjetsExistants.size();
    //Inventaire Inv = Player->getInventaire();
    Objet* Ob (ObjetsExistants[Indice]);
    m_inventaire.ajouterObjet(Ob, 1);
    //this->setInventaire(m_inventaire.getContenu(), m_inventaire.getExemplaires());
    cout << "Vous avez obtenu "
        << ((Ob->getType() == ARME) ? "une arme : " : "un objet : ")
         << Ob->getNom() << endl;
    system("PAUSE");

} //ObtenirObjet

void Personnage::UtiliserSort(Personnage* Cible)
{
    unsigned Choix;

    cout << "1) Sort de bouclier (10 mana) : Donne 10 points de bouclier" << endl;
    cout << "2) Boule de feu (20 mana) : Inflige 15 points de degats" <<endl;
    cout << "3) Meteore (60 mana) : Inflige 40 degats apres un tour de canalisation" << endl;
    cout << "4) Retour" << endl;

    cout << "Entrez le numero du sort" << endl;
    cin >> Choix;

    while(Choix < 1 || Choix > 4)
    {
        cout << "Veuillez saisir un chiffre correct " << endl ;
        if(cin.fail())
        {

            cin.clear();
            cin.ignore();

        }
        cin >> Choix;
    }

    switch(Choix)
    {
    case 1 :
        if(this->getMana() < 10)
        {
            cout << "Pas assez de Mana !" << endl << endl;
            this->ChoixActions(Cible);
        }
        else
        {
            this->setMana(this->getMana() - 10);
            this->setBouclier(this->getBouclier() + 10);
        }
        break;
    case 2 :
        if(this->getMana() < 20)
        {
            cout << "Pas assez de Mana !" << endl << endl;
            this->ChoixActions(Cible);
        }
        else
        {
            this->setMana(this->getMana() - 20);
            Cible->recevoirDegats(15);
        }
        break;
    case 3 :
        if(this->getMana() < 60)
        {
            cout << "Pas assez de Mana !" << endl << endl;
            this->ChoixActions(Cible);
        }
        else
        {
            this->setMana(this->getMana() - 60);
            this->ajouterMalus({CHARGE, 2, 40});
        }
        break;
    case 4 :
        system("cls");
        this->afficherEtat();
        this->ChoixActions(Cible);
        break;
    }
} //UtiliserSort

void Personnage::InitialiserPersonnage()
{

    vector<unsigned> PoidsInventaireDeBase = {1,1,1,3,1,1,1,2};
    vector<Objet*> InventaireDeBase = {&A1, &A2, &A3, &O1, &O2, &O3, &O4, &O5};

    string Nom;
    cin >> Nom;
    cout << endl;
    this->setNom(Nom);
    this->setInventaire(InventaireDeBase, PoidsInventaireDeBase);
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



