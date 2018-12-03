#include <stdio.h>
#include <stdlib.h>
#include <time.h> // inclusion de la librairie time.h pour le random
#define NBTOURS 10 // Constante nbtours =10
#define NBJETONS 4 // il faut 4 jetons qui compose une combinaison

struct Mastermind //  creation de la structure mastermind
{
    int combinaison[NBJETONS];
    int nbEssai;
    int nbVictoire;
    int nbDefaite;
    int essaiCombinaison[NBJETONS];  // ajout de l'essai du joueur
};

struct Resultat // creation de la structure resultat
{
int nbEnPlace;
int nbDesordre;
};

struct Resultat TestCombi(struct Mastermind partie) // fonction qui appelle la structure de la partie et qui renvoi les resultat sous forme d'un nombre pour les bien placé
{
    // et un nombre pourles mal placé

    struct Resultat combi;
    combi.nbEnPlace=0;                             // initialisation des bien placé a 0
    combi.nbDesordre=0;                            // initialisation des mal  placé a 0
    int i;                                         // declaration des compteurs de boucles
    int j;
    int comptjdansreponse=0;                       // compte combien de fois j est present dans la reponse
    int comptjdansessai=0;                         // compte combien de fois j est dans la tentative d'essai
    int comptjbienplace=0;                         // compte combien de fois j est bien placé

    for (i=0; i<NBJETONS; i++)                             // on test les bien placé
    {
        if (partie.essaiCombinaison[i]==partie.combinaison[i])
        {
            combi.nbEnPlace++;                     // si bien placé on incremente le compteur de la structure resultat

        }
    }

    for (j=0; j<10; j++)                        // on teste toutes les valeurs entre 0 et 9
    {
        for (i=0; i<NBJETONS; i++)
        {
            if (j==partie.combinaison[i]) // on teste toutes les valeurs entre 0 et 9 dans la reponse
            {
                comptjdansreponse++;     // on incremente le compteur le cas echeant
            }
            if (j==partie.essaiCombinaison[i]) // on teste toutes les valeurs entre 0 et 9 dans l'essai du joueur
            {
                comptjdansessai++; // on incremente le compteur le cas echeant
            }
            if (partie.essaiCombinaison[i]==partie.combinaison[i] && j==partie.essaiCombinaison[i]) // on teste toutes les valeurs entre 0 et 9 qui sont bien placé
            {
                comptjbienplace++; // on incremente le compteur le cas echeant
            }
        }
        if (comptjdansessai>=comptjdansreponse) //si le nombre se trouve plus souvent dans l'essai du joueur
        {
            combi.nbDesordre+=comptjdansreponse-comptjbienplace; // alors on calcule la difference entre le nombre de fois ou cette valeur est presente dans la reponse et le nombre de fois ou cette valeur est bien placé et on ajoute cette difference a celui des autres valeur
        }                                                        // ( ex si le nombre 9 se trouve 2 fois dans la reponse et qu'il est une fois bien placé alors il y a un 9 mal placé si le joueur a au moins deux 9 dans sa reponse)
        comptjdansreponse=0; //reinitialisation pour le prochain passage dans la boucle
        comptjdansessai=0; //reinitialisation pour le prochain passage dans la boucle
        comptjbienplace=0; //reinitialisation pour le prochain passage dans la boucle
    }


    return combi; // retourn la structure combi
};



int main()
{
    struct Mastermind partie; // creation d'une structure Mastermind appelé partie
    int i;
    int pastrouve;           // declaration de la variable le jouer n'a pas trouve
    int testVictoire;        // variable qui tester si le joueur a gagné
    int rejouer=0;           // variable qui test si le joueur veut rejouer
    srand(time(NULL));       // initialisation du seed du random en fonction de temps
    struct Resultat affichageCombi;  // creation d'une structure Resultat appelé affichage combi
    partie.nbDefaite=0;             // pour une nouvelle sceance on s'assure que les variable soit a 0
    partie.nbVictoire=0;            // pour une nouvelle sceance on s'assure que les variable soit a 0
    do                              // debut de la boucle do while pour rejouer
    {
        for (i=0; i<NBJETONS; i++)         // creation de la combinaison gagnante dans le tableau de taille 4
        {
            partie.combinaison[i]=rand()%10;  // on cree la combinaisons gagnante qui doit etre trouvé par le joueur
        }
        partie.nbEssai=NBTOURS; // le nombre maximal de tours est inserer dans la structure mastermind nommé partie
        pastrouve=1;            // on remet pas trouve a 1
        while (partie.nbEssai>0 && pastrouve) // boucle qui permet de jouer tant que le joueur n'a pas trouvé et qu'il lui reste des essais
        {
            if (partie.nbEssai==1)  // on traites les cas du pluriel et du singulier
            {
                printf("Attention, c'est votre derniere tentative \n");
            }
            else
            {
                printf("Il vous reste %d tentatives\n",partie.nbEssai);
            }
            for (i=0; i<NBJETONS; i++) // boucle pour remplir le tableau d'essai de combinaison du joueur de la structure mastermind partie
            {
                do
                {
                    if (i==0) //cas partilier du 1 er
                    {
                        printf("Entrez votre %der chiffre compris entre 0 et 9\n",i+1); //on demande la saisie du premier au 4eme chiffre
                        fseek(stdin,0,SEEK_END); // on s'assure qu'il ne puisse rentrer qu'une valeur a la fois
                        scanf("%d",&partie.essaiCombinaison[i]); // on insere les valeur entrer par le joueur dans le tableau d'essai de combinaison du joueur de la structure mastermind partie
                    }
                    else // cas du xeme
                    {
                        printf("Entrez votre %deme chiffre compris entre 0 et 9\n",i+1); //on demande la saisie du premier au 4eme chiffre
                        fseek(stdin,0,SEEK_END); // on s'assure qu'il ne puisse rentrer qu'une valeur a la fois
                        scanf("%d",&partie.essaiCombinaison[i]); // on insere les valeur entrer par le joueur dans le tableau d'essai de combinaison du joueur de la structure mastermind partie
                    }

                }
                while (partie.essaiCombinaison[i]<0 || partie.essaiCombinaison[i]>9); // boucle qui tester si le joueur a bien inserer un nombre entre 0 et 9

            }
            testVictoire=0; //on reinitialise le test victoire pour les parties apres la 1ere
            for (i=0; i<NBJETONS; i++) // on test si le joueur a trouvé
            {
                if (partie.essaiCombinaison[i]==partie.combinaison[i])
                {
                    testVictoire++; // si oui on incremente
                }
            }
            if (testVictoire==NBJETONS) // on teste si les 4 valeurs de la combinaison sont juste
            {
                pastrouve=0; // on indique que le jouer a trouve pour sortir de la boucle
                partie.nbVictoire++; // on incremente la victoire pour son historique
            }
            else
            {
                affichageCombi=TestCombi(partie); // on appel la fonction test combi pour tester les nb bien placé et les nb dans le desordre

                if (affichageCombi.nbEnPlace<=1) // on traites les cas du pluriel et du singulier
                {
                    printf("Il y a %d chiffre a la bonne place\n",affichageCombi.nbEnPlace);
                }
                else
                {
                    printf("Il y a %d chiffres a la bonne place\n",affichageCombi.nbEnPlace);
                }
                if (affichageCombi.nbDesordre<=1) // on traites les cas du pluriel et du singulier
                {
                    printf("Il y a %d bon chiffre dans le mauvais ordre\n",affichageCombi.nbDesordre);
                }
                else
                {
                    printf("Il y a %d bons chiffres dans le mauvais ordre\n",affichageCombi.nbDesordre);
                }
                partie.nbEssai--; // on enleve un essai car le jouer n'a aps trouvé
                if (partie.nbEssai==0) // si le joueur n'a pas trouvé apres 10 essai on lui donne al reponse
                {
                    partie.nbDefaite++; // on incremente son nombre de defaite
                    printf("la combinaison gagnante etait:\n");
                    for (i=0; i<NBJETONS; i++) // une boucle pour ecrire la combinaison en entier
                    {
                        printf("%d",partie.combinaison[i]);
                    }
                }
            }

        }

        if (partie.nbVictoire<=1) // on traites les cas du pluriel et du singulier
        {
            printf("\nVous avez %d victoire\n",partie.nbVictoire);
        }
        else
        {
            printf("\nVous avez %d victoires\n",partie.nbVictoire);
        }
        if (partie.nbDefaite<=1) // on traites les cas du pluriel et du singulier
        {
            printf("Vous avez %d defaite\n",partie.nbDefaite);
        }
        else
        {
            printf("Vous avez %d defaites\n",partie.nbDefaite);
        }
        do //debut de la boucle do while pour savoir si le joueur veut rejouer ou non et si il rentre bien une valeur accepté
        {
            printf("Voulez vous rejouer ?\n0 pour non 1 pour oui\n");
            fseek(stdin,0,SEEK_END);
            scanf("%d",&rejouer);
        }
        while (rejouer<0 || rejouer>1);

    }
    while (rejouer); // condition de la boucle pour rejouer
    return 0;
}
