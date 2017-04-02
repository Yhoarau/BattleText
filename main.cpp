#include <iostream>
#include <stdlib.h>
#include <Personnage.h>
#include <time.h>

using namespace std;



Personnage P1, P2;
bool PlayTurn(true);
Personnage* Player = PlayTurn ? &P1 : &P2;
Personnage* Cible = PlayTurn ? &P2 : &P1;

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

vector<Objet*> ObjetsExistants = {&A1, &A2, &A3, &A4, &A5, &O1, &O2, &O3, &O4, &O5, &O6};


void ChoixActions();

unsigned CheckNbObjet(string Obj)
{
    Inventaire Inv = Player->getInventaire();
    vector<string> Contenu = Inv.getNomsObj();
    vector<unsigned> Exemplaires = Inv.getExemplaires();

    //for(unsigned i(0); i< Contenu.size(); ++i)
      //  if(Contenu[i] == Obj) return Exemplaires[i];

    vector<string>::iterator it = find(Contenu.begin(), Contenu.end(), Obj);
    unsigned i = distance(Contenu.begin(), it);
    if (it != Contenu.end()) return Exemplaires[i];
    return 0;

}

void UtiliserPotion(string nomPotion)
{
    Inventaire Inv = Player->getInventaire();
    vector<string> Contenu = Inv.getNomsObj();
    vector<unsigned> Exemplaires = Inv.getExemplaires();
    vector<string> Types = Inv.getType();
    vector<Objet*> Objs = Inv.getContenu();

    for(unsigned i (0); i < Objs.size() ; ++i )
    {
         Objet O = *(Objs[i] );
        //cout << O.getType(); system("PAUSE");
        if(O.getType() == POTION)
        {
            if(O.getNom() == nomPotion && nomPotion == "Potion de vie")
            {
                Player->ajouterBonus({SOIN, 1, 10});
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
                Player->ajouterBonus({RAGE, 3, 2});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de mana")
            {
                Player->setMana((*Player).getMana() + 20);
                if(Player->getMana() > 100) (*Player).setMana(100);
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion d'invincibilite")
            {
                Player->ajouterBonus({INVINCIBILITE, 4, 0});
                --Exemplaires[i];
            }

        }
    }

    Player->setInventaire(Objs, Exemplaires);
    Player->refreshInventaire();

    /*vector<string>::iterator it = find(Types.begin(), Types.end(), "Potion" );
    unsigned i = distance(Types.begin(), it);
    if (it != Types.end())
        if(Contenu[i] == "Potion de vie")
            {
                Player.boirePotionDeVie(10);
                --Exemplaires[i];
                Player.setInventaire(Contenu, Exemplaires, Types);
                Player.checkInventaire();
            }*/

} //UtiliserPotion

void ChoixArme()
{
    Inventaire Inv = Player->getInventaire();
    vector<Objet*> ObjetsP(Inv.getContenu());
    vector<unsigned> NbObjetsP(Inv.getExemplaires());
    vector<Arme> ArmesP;
    //vector<string> Types(Inv.getType());
    unsigned Choix(0);

    //vector<Arme> Armes;
    //Armes.resize(0);
    /*Arme A1("Grosse epee rouillee", 10, 8);
    Arme A2("Fine epee aiguisee", 20, 3);
    Arme A3("Enorme massue a usage unique", 50, 1);
    vector<Arme> Armes {A1, A2, A3};*/


    /*
    Armes[0] = A1;
    Armes[1] = A2;
    Armes[2] = A3; */

    cout << "Veuillez choisir une arme parmi celles qui vous reste :" << endl << endl;
    /*for (unsigned i(0); i < Inv.getType().size(); ++i)
            if(Inv.getType()[i] != "Arme") ArmesP.erase(ArmesP.begin() + i); */
    unsigned ArmesRestantes(0);
    for (unsigned i(0); i < ObjetsP.size() ; ++i)
        {
            Objet O = *(ObjetsP[i]);
            if(O.getType() == ARME)
            {
                ++ArmesRestantes;

                cout << ArmesRestantes << ") " << O.getNom() << " (" << NbObjetsP[i] << ")" << O.getDescription() << endl;
                ArmesP.resize(ArmesP.size() + 1);

                //Arme A = *(ObjetsP[i]);
                 Arme A (O.getNom(),
                         stoi(O.getDescription().substr((30 - O.getNom().size()) + 1 + 9, 4)),
                         stoi(O.getDescription().substr((30 - O.getNom().size()) + 1 + 28, 3)));
                ArmesP[ArmesP.size() - 1] = A;

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

    while(Choix < 1 || Choix > ArmesRestantes + 1 || (Choix == ArmesRestantes + 1 && !((*Player).estArme())))
    {
        if(!(Player->estArme())) cout << "Vous n'avez aucune arme equipee" << endl;
        cout << "Veuillez saisir un chiffre correct " << endl ;
        if(cin.fail())
        {

            cin.clear();
            cin.ignore();

        }
        cin >> Choix;
    }
    cout << endl << endl;

    if(Choix == ArmesRestantes + 1 && (Player->estArme()))
        {
            system("cls");
            Player->afficherEtat();
            ChoixActions();
        }
    else
    {
        for(Arme & A : ArmesP)
        if(A.getNom() == ArmesP[Choix - 1].getNom())
        Player->changerArme(A);
    }

   //Objet A = ArmesP[Choix-1];
    //Player.changerArme((ArmesP[Choix-1]));

    /*vector<string>::iterator it = find(ArmesP.begin(), ArmesP.end(), ArmesP[Choix - 1]);
    unsigned i = distance(Inv.getContenu().begin(), it);
    Arme A (Inv.getContenu()[i], Inv.getExemplaires()[i], Inv.getType()[i], Inv.getDescription()[i]);
    Player.changerArme(A); */
} // ChoixArme

 void UtiliserObjet()
{

    Inventaire Inv(Player->getInventaire());
    vector<Objet*> ObjetsP(Inv.getContenu());
    vector<Objet> ObjSansArmes;
    unsigned Choix;
    /*for (unsigned i(0); i < Inv.getType().size(); ++i)
        if(Inv.getType()[i] == "Arme")
            ObjetsP.erase(ObjetsP.begin() + i); */
    unsigned ObjetsRestants(0);
    for(unsigned i(0); i < Inv.getContenu().size()  ; ++i)
        {
            Objet Ob = *(ObjetsP[i]);
            if (Ob.getType() != ARME)
            {

                ObjetsRestants++;
                Objet O (Ob.getNom(), Ob.getType(), Ob.getDescription());
                ObjSansArmes.resize(ObjSansArmes.size() + 1);
                ObjSansArmes[ObjSansArmes.size() - 1] = O;
                cout << ObjetsRestants << ") " << Ob.getNom() << " (" << Inv.getExemplaires()[i] << ")"
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
        Player->afficherEtat();
        ChoixActions();
    }
    else if (ObjSansArmes[Choix - 1].getType() == POTION)
    {

        UtiliserPotion(ObjSansArmes[Choix - 1].getNom());
    }

} //UitliserObjet

void UtiliserSort()
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
        if(Player->getMana() < 10)
        {
            cout << "Pas assez de Mana !" << endl << endl;
            ChoixActions();
        }
        else
        {
            Player->setMana((*Player).getMana() - 10);
            Player->setBouclier((*Player).getBouclier() + 10);
        }
        break;
    case 2 :
        if(Player->getMana() < 20)
        {
            cout << "Pas assez de Mana !" << endl << endl;
            ChoixActions();
        }
        else
        {
            Player->setMana((*Player).getMana() - 20);
            Cible->recevoirDegats(15);
        }
        break;
    case 3 :
        if(Player->getMana() < 60)
        {
            cout << "Pas assez de Mana !" << endl << endl;
            ChoixActions();
        }
        else
        {
            Player->setMana((*Player).getMana() - 60);
            Player->ajouterMalus({CHARGE, 2, 40});
        }
        break;
    case 4 :
        system("cls");
        Player->afficherEtat();
        ChoixActions();
        break;
    }


} //UtiliserSort

void ObtenirObjet()
{
    unsigned Indice = rand() % ObjetsExistants.size();
    Inventaire Inv = Player->getInventaire();
    Objet* Ob (ObjetsExistants[4]);
    Inv.ajouterObjet(Ob, 1);
    Player->setInventaire(Inv.getContenu(), Inv.getExemplaires());


} //ObtenirObjet

void ChoixActions()
{
    unsigned Choix(0);

    if (!(Player->checkInventaire()))
    {

        cout << "L'inventaire a rencontre un probleme"<< endl << endl;
        system("PAUSE");
        Player->recevoirDegats(1000);
        return;
    }

    bool Block(false);
    for(unsigned i(0); i < Player->getMalus().size(); ++i)
    {
        if((Player->getMalus()[i][0] == GEL) ||
           ((Player->getMalus()[i][0] == CHARGE) && ((*Player).getMalus()[i][1] >= 1)))
            Block = true;
    }

    for(unsigned i(0); i < Player->getMalus().size(); ++i)
    {
        if((Player->getMalus()[i][0] == CHARGE))
            {
                if (Player->getMalus()[i][1] == 1)
                    Cible->ajouterMalus({MARQUE, 1, (*Player).getMalus()[i][2]});
            }
    }

    if(Block)
    {
        cout << "Vous ne pouvez pas jouer ce tour." << endl << endl;
        system("PAUSE");
    }
    else if(Player->getPosture() == "Defense")
    {
        cout << "1) Utiliser un objet du sac"  <<  endl;
        cout << "2) Changer d'arme" << endl;
        cout << "3) Passer en posture offensive " << endl;
        cout << "4) Obtenir un objet au hasard" << endl;
        cout << "5) Ne rien faire " << endl << endl;

        cin >> Choix;

        while(Choix < 1 || Choix > 5)
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
            UtiliserObjet();
            break;
        case 2 :
            ChoixArme();
            break;
        case 3 :
            Player->changerPosture("Attaque");
            break;
        case 4 :
            ObtenirObjet();
            break;
        case 5:
            break;
        default :
            break;
        }

    }
    else if (Player->getPosture() == "Attaque")
    {
        cout << "1) Attaquer " << endl;
        cout << "2) Lancer un sort" << endl;
        cout << "3) Utiliser un objet du sac " <<  endl;
        cout << "4) Changer d'arme" << endl;
        cout << "5) Passer en posture defensive " << endl;
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
        case 1 :
            Player->attaquer((*Cible));
            Player->checkArme();
            break;
        case 2 :
            UtiliserSort();
            break;
        case 3 :
            UtiliserObjet();
            break;
        case 4 :
            ChoixArme();
            break;
        case 5 :
            Player->changerPosture("Defense");
            break;
        case 6 :
            break;
        default :
            break;

        }


    }
    Player->appliquerBonus();
    Player->appliquerMalus();

} //ChoixActions



int main()
{

    string Nom;

    vector<unsigned> PoidsInventaireDeBase;
    PoidsInventaireDeBase = {1,1,1,3,1,1,1,2};
    //vector<Objet*> InventaireDeBase;

    vector<Objet*> InventaireDeBase = {&A1, &A2, &A3, &O1, &O2, &O3, &O4, &O5};
    //vector<string> TypeInventaireDeBase;
    //TypeInventaireDeBase = {"Arme", "Arme", "Arme", "Potion", "Potion"};

    Player = &P1;

    cout << "Joueur 1, choisissez votre nom : ";
    cin >> Nom;
    cout << endl;
    Player->setNom(Nom);

    Player->setInventaire(InventaireDeBase, PoidsInventaireDeBase);

    ChoixArme();


    Player = &P2;

    cout << "Joueur 2, choisissez votre nom : ";
    cin >> Nom;
    cout << endl;
    Player->setNom(Nom);

    Player->setInventaire(InventaireDeBase, PoidsInventaireDeBase);

    ChoixArme();



    do
    {

        Player = PlayTurn ? &P1 : &P2;
        Cible = PlayTurn ? &P2 : &P1;


        system("cls");

        cout << Player->getNom() << ", que voulez vous faire ?" << endl << endl;
        Player->afficherEtat();



        if (!((*Player).estArme()))
        {
            cout << "Vous n'avez plus d'arme " << endl;
            ChoixArme();
        }

        ChoixActions();



        PlayTurn = !(PlayTurn);


    }while ((Player->estVivant()) && (Cible->estVivant()));

    system("cls");

    Player->afficherEtat();
    Cible->afficherEtat();

    if(!(Player->estVivant()) && !(Cible->estVivant()))
    {
        cout << "Il ne reste plus personne sur le champ de bataille, " << Player->getNom() << " a tout fait peter." << endl;
        cout << "Il ne reste aucun survivant pour declarer un vainqueur. Vous avez perdu." << endl;
        return 0;
    }
    cout << Player->getNom() << " a gagne !" << endl;

    return 0;
}
