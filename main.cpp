#include <iostream>
#include <stdlib.h>
#include <Personnage.h>

using namespace std;

unsigned CheckNbObjet(Personnage & Player, string Obj)
{
    Inventaire Inv = Player.getInventaire();
    vector<string> Contenu = Inv.getNomsObj();
    vector<unsigned> Exemplaires = Inv.getExemplaires();

    //for(unsigned i(0); i< Contenu.size(); ++i)
      //  if(Contenu[i] == Obj) return Exemplaires[i];

    vector<string>::iterator it = find(Contenu.begin(), Contenu.end(), Obj);
    unsigned i = distance(Contenu.begin(), it);
    if (it != Contenu.end()) return Exemplaires[i];
    return 0;

}

void BoirePotion(Personnage & Player, string nomPotion)
{
    Inventaire Inv = Player.getInventaire();
    vector<string> Contenu = Inv.getNomsObj();
    vector<unsigned> Exemplaires = Inv.getExemplaires();
    vector<string> Types = Inv.getType();
    vector<Objet> Objs = Inv.getContenu();

    for(unsigned i (0); i < Contenu.size() ; ++i )
        if(Types[i] == "Potion")
        {
            if(Contenu[i] == "Potion de vie")
            {
                Player.boirePotionDeVie(10);
                --Exemplaires[i];
                Player.setInventaire(Objs, Exemplaires);
                Player.checkInventaire();
            }

        }

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

}

void ChoixArme(Personnage & Player)
{
    Inventaire Inv = Player.getInventaire();
    vector<Objet> ArmesP(Inv.getContenu());
    //vector<string> Types(Inv.getType());
    unsigned Choix(0);

    //vector<Arme> Armes;
    //Armes.resize(0);
    Arme A1("Grosse epee rouillee", 10, 8);
    Arme A2("Fine epee aiguisee", 20, 3);
    Arme A3("Enorme massue a usage unique", 50, 1);
    vector<Arme> Armes {A1, A2, A3};


    /*
    Armes[0] = A1;
    Armes[1] = A2;
    Armes[2] = A3; */

    cout << "Veuillez choisir une arme parmi celles qui vous reste :" << endl << endl;
    for (unsigned i(0); i < Inv.getType().size(); ++i)
            if(Inv.getType()[i] != "Arme") ArmesP.erase(ArmesP.begin() + i);
    for (unsigned i(1); i < ArmesP.size() +1; ++i)
        {
            cout << i << ") " << ArmesP[i-1].getNom() << "     " << ArmesP[i-1].getDescription() << endl;
        }
    if (ArmesP.size() == 0)
    {
        cout << "Vous n'avez plus d'arme a disposition, vous ne pouvez plus attaquer" << endl << endl;
        return;
    }
    cout << endl << "Entrez le numero de l'arme : ";
    cin >> Choix;

    while(Choix < 1 || Choix > ArmesP.size() + 1)
    {
        cout << "Veuillez saisir un chiffre correct" << endl ;
        if(cin.fail())
        {

            cin.clear();
            cin.ignore();

        }
        cin >> Choix;
    }
    cout << endl << endl;
     for(Arme & A : Armes)
        if(A.getNom() == ArmesP[Choix - 1].getNom())
            Player.changerArme(A);
   // Objet A = ArmesP[Choix-1];
   // Player.changerArme((ArmesP[Choix-1]));

    /* vector<string>::iterator it = find(Armes.begin(), Armes.end(), Contenu[Choix - 1]);
    unsigned i = distance(Inv.getContenu().begin(), it);
    Arme A (Inv.getContenu()[i], Inv.getExemplaires()[i], Inv.getType()[i], Inv.getDescription()[i]);
    Player.changerArme(A); */
} // ChoixArme

void ChoixActions(Personnage & Player, Personnage & Cible)
{
    unsigned Choix(0);

    if (!(Player.checkInventaire()))
    {

        cout << "L'inventaire a rencontre un probleme"<< endl << endl;
        system("PAUSE");
        Player.recevoirDegats(1000);
        return;
    }

    if(Player.getPosture() == "Defense")
    {
        cout << "1) Passer en posture offensive " << endl;
        cout << "2) Boire une potion de soin (+10 pv) (reste " << CheckNbObjet(Player, "Potion de vie") << ")" <<  endl;
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
            Player.changerPosture("Attaque");
            break;
        case 2 :
            BoirePotion(Player, "Potion de vie");
            break;
        case 3 :
            ChoixArme(Player);
            break;
        case 4 :
            break;
        default :
            break;
        }
    }
    else if (Player.getPosture() == "Attaque")
    {
        cout << "1) Attaquer " << endl;
        cout << "2) Passer en posture defensive " << endl;
        cout << "3) Boire une potion de soin (+10 pv) (reste " << CheckNbObjet(Player, "Potion de vie") << ")" <<  endl;
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
            Player.attaquer(Cible);
            Player.checkArme();
            break;
        case 2 :
            Player.changerPosture("Defense");
            break;
        case 3 :
            BoirePotion(Player, "Potion de vie");
            break;
        case 4 :
            ChoixArme(Player);
            break;
        case 5 :
            break;
        default :
            break;

        }


    }
}



int main()
{
    Personnage P1, P2;
    string Nom;
    bool PlayTurn(true);
    vector<unsigned> PoidsInventaireDeBase;
    PoidsInventaireDeBase = {1,1,1,3,1};
    vector<Objet> InventaireDeBase;
    Arme A1("Grosse epee rouillee", 10, 8);
    Objet O1("Grosse epee rouillee", "Arme", "Degats : 10, Durabilite : 8");
    Objet O2("Fine epee aiguisee", "Arme", "Degats : 20, Durabilite : 3");
    Objet O3("Enorme massue a usage unique", "Arme", "Degats : 50, Durabilite : 1");
    Objet O4("Potion de vie", "Potion", "Régénère 10 points de vie");
    Objet O5("Potion de poison", "Potion", "Inflige 5 points de dégats par tour à l'ennemi pendant 3 tours");

    InventaireDeBase = {O1, O2, O3, O4, O5};
    //vector<string> TypeInventaireDeBase;
    //TypeInventaireDeBase = {"Arme", "Arme", "Arme", "Potion", "Potion"};



    cout << "Joueur 1, choisissez votre nom : ";
    cin >> Nom;
    cout << endl;
    P1.setNom(Nom);

    P1.setInventaire(InventaireDeBase, PoidsInventaireDeBase);
    ChoixArme(P1);

    cout << "Joueur 2, choisissez votre nom : ";
    cin >> Nom;
    cout << endl;
    P2.setNom(Nom);

    P2.setInventaire(InventaireDeBase, PoidsInventaireDeBase);
    ChoixArme(P2);

    do
    {
        system("cls");

        cout << (PlayTurn ? P1.getNom() : P2.getNom()) << ", que voulez vous faire ?" << endl << endl;
        (PlayTurn ? P1.afficherEtat() : P2.afficherEtat());



        if (PlayTurn ? !(P1.estArme()) : !(P2.estArme()))
        {
            cout << "Vous n'avez plus d'arme " << endl;
            PlayTurn ? ChoixArme(P1) : ChoixArme(P2);
        }

        ChoixActions((PlayTurn ? P1 : P2), (PlayTurn ? P2 : P1) );

        PlayTurn = !(PlayTurn);
    }while ((P1.estVivant()) && (P2.estVivant()));

    system("cls");

    P1.afficherEtat();
    P2.afficherEtat();

    cout << (PlayTurn ? P2.getNom() : P1.getNom()) << " a gagne !" << endl;
    return 0;
}
