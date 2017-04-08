#include <iostream>
#include <stdlib.h>
#include "Personnage.h"
#include <time.h>

using namespace std;

Personnage P1, P2;
bool PlayTurn(true);
Personnage* Player = PlayTurn ? &P1 : &P2;
Personnage* Cible = PlayTurn ? &P2 : &P1;

void ChoixActions();

int main()
{
    Player = &P1;
    cout << "Joueur 1, choisissez votre nom : ";
    Player->InitialiserPersonnage();
    Player->ChoixArme(Cible);

    Player = &P2;
    cout << "Joueur 2, choisissez votre nom : ";
    Player->InitialiserPersonnage();
    Player->ChoixArme(Cible);

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
            Player->ChoixArme(Cible);
        }

        Player->ChoixActions(Cible);

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
