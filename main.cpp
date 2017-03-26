#include <iostream>
#include <stdlib.h>
#include <Personnage.h>

using namespace std;



Personnage P1, P2;
bool PlayTurn(true);
Personnage* Player = PlayTurn ? &P1 : &P2;
Personnage* Cible = PlayTurn ? &P2 : &P1;

void ChoixActions();

unsigned CheckNbObjet(string Obj)
{
    Inventaire Inv = (*Player).getInventaire();
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
    Inventaire Inv = (*Player).getInventaire();
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
                (*Player).ajouterBonus({SOIN, 1, 10});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de poison" )
            {
                (*Cible).ajouterMalus({POISON, 5, 5});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de gel")
            {
                (*Cible).ajouterMalus({GEL, 2, 0});
                --Exemplaires[i];
            }
            else if (O.getNom() == nomPotion && nomPotion == "Potion de rage")
            {
                (*Player).ajouterBonus({RAGE, 3, 2});
                --Exemplaires[i];
            }

        }
    }

    (*Player).setInventaire(Objs, Exemplaires);
    (*Player).refreshInventaire();

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
    Inventaire Inv = (*Player).getInventaire();
    vector<Objet*> ObjetsP(Inv.getContenu());
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

                cout << ArmesRestantes << ") " << O.getNom() << O.getDescription() << endl;
                ArmesP.resize(ArmesP.size() + 1);

                //Arme A = *(ObjetsP[i]);
                 Arme A (O.getNom(),
                         stoi(O.getDescription().substr((30 - O.getNom().size()) + 1 + 9, 2)),
                         stoi(O.getDescription().substr((30 - O.getNom().size()) + 1 + 26, 1)));
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
        if(!((*Player).estArme())) cout << "Vous n'avez aucune arme equipee" << endl;
        cout << "Veuillez saisir un chiffre correct " << endl ;
        if(cin.fail())
        {

            cin.clear();
            cin.ignore();

        }
        cin >> Choix;
    }
    cout << endl << endl;

    if(Choix == ArmesRestantes + 1 && ((*Player).estArme()))
        ChoixActions();
    else
    {
        for(Arme & A : ArmesP)
        if(A.getNom() == ArmesP[Choix - 1].getNom())
        (*Player).changerArme(A);
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
    Inventaire Inv((*Player).getInventaire());
    vector<Objet*> ObjetsP(Inv.getContenu());
    vector<Objet> ObjSansArmes;
    unsigned Choix;
    /*for (unsigned i(0); i < Inv.getType().size(); ++i)
        if(Inv.getType()[i] == "Arme")
            ObjetsP.erase(ObjetsP.begin() + i); */


    unsigned ObjetsRestants(0);
    for(unsigned i(0); i < Inv.getType().size()  ; ++i)
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
        ChoixActions();
    }
    else if (ObjSansArmes[Choix - 1].getType() == POTION)
    {

        UtiliserPotion(ObjSansArmes[Choix - 1].getNom());
    }

} //UitliserObjet

void ChoixActions()
{
    unsigned Choix(0);

    if (!((*Player).checkInventaire()))
    {

        cout << "L'inventaire a rencontre un probleme"<< endl << endl;
        system("PAUSE");
        (*Player).recevoirDegats(1000);
        return;
    }

    bool Block(false);
    for(unsigned i(0); i < (*Player).getMalus().size(); ++i)
        if((*Player).getMalus()[i][0] == GEL)
            Block = true;


    if(Block)
    {
        cout << "Vous ne pouvez pas jouer ce tour." << endl << endl;
        system("PAUSE");
    }
    else if((*Player).getPosture() == "Defense")
    {
        cout << "1) Passer en posture offensive " << endl;
        cout << "2) Utiliser un objet du sac"  <<  endl;
        cout << "3) Changer d'arme" << endl;
        cout << "4) Ne rien faire " << endl << endl;

        cin >> Choix;

        while(Choix < 1 || Choix > 4)
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
            (*Player).changerPosture("Attaque");
            break;
        case 2 :
            UtiliserObjet();
            break;
        case 3 :
            ChoixArme();
            break;
        case 4 :
            break;
        default :
            break;
        }
    }
    else if ((*Player).getPosture() == "Attaque")
    {
        cout << "1) Attaquer " << endl;
        cout << "2) Passer en posture defensive " << endl;
        cout << "3) Utiliser un objet du sac " <<  endl;
        cout << "4) Changer d'arme" << endl;
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
        case 1 :
            (*Player).attaquer((*Cible));
            (*Player).checkArme();
            break;
        case 2 :
            (*Player).changerPosture("Defense");
            break;
        case 3 :
            UtiliserObjet();
            break;
        case 4 :
            ChoixArme();
            break;
        case 5 :
            break;
        default :
            break;

        }


    }
    (*Player).appliquerBonus();
    (*Player).appliquerMalus();

} //ChoixActions



int main()
{

    string Nom;

    vector<unsigned> PoidsInventaireDeBase;
    PoidsInventaireDeBase = {1,1,1,3,1,1,1};
    vector<Objet*> InventaireDeBase;

    Arme A1("Grosse epee rouillee", 10, 8);
    Arme A2("Fine epee aiguisee", 20, 3);
    Arme A3("Enorme massue a usage unique", 50, 1);
    Objet O4("Potion de vie", POTION, "Regenere 10 points de vie");
    Objet O5("Potion de poison", POTION, "Inflige 5 points de degats par tour a l'ennemi pendant 5 tours");
    Objet O6("Potion de gel", POTION, "Empeche l'ennemi d'agir pendant 2 tours");
    Objet O7("Potion de rage", POTION, "Double vos degats pendant les 2 prochains tours");

    InventaireDeBase = {&A1, &A2, &A3, &O4, &O5, &O6, &O7};
    //vector<string> TypeInventaireDeBase;
    //TypeInventaireDeBase = {"Arme", "Arme", "Arme", "Potion", "Potion"};

    Player = &P1;

    cout << "Joueur 1, choisissez votre nom : ";
    cin >> Nom;
    cout << endl;
    (*Player).setNom(Nom);

    (*Player).setInventaire(InventaireDeBase, PoidsInventaireDeBase);

    ChoixArme();


    Player = &P2;
    cout << "Joueur 2, choisissez votre nom : ";
    cin >> Nom;
    cout << endl;
    (*Player).setNom(Nom);

    (*Player).setInventaire(InventaireDeBase, PoidsInventaireDeBase);

    ChoixArme();



    do
    {
        Player = PlayTurn ? &P1 : &P2;
        Cible = PlayTurn ? &P2 : &P1;


        system("cls");

        cout << (*Player).getNom() << ", que voulez vous faire ?" << endl << endl;
        (*Player).afficherEtat();



        if (!((*Player).estArme()))
        {
            cout << "Vous n'avez plus d'arme " << endl;
            ChoixArme();
        }

        ChoixActions();



        PlayTurn = !(PlayTurn);


    }while ((P1.estVivant()) && (P2.estVivant()));

    system("cls");

    P1.afficherEtat();
    P2.afficherEtat();

    cout << (*Player).getNom() << " a gagne !" << endl;
    return 0;
}
