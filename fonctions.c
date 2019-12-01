#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fonctions.h"

// Fonctions
void afficherListeMed(Medecin *first)
{
    int n = 1;
    Medecin *current;

    current = first;
    while (current != NULL)
    {
        printf("Médecin %d --> %-14s %-20s %-20s\n",
               n, current->numInami, current->nom, current->prenom);

        n++;
        current = current->next;
    }
}

void afficherListePat(Patient *first)
{
    int n = 1;
    Patient *current;

    current = first;
    while (current != NULL)
    {   
        printf("Patient %d --> %-15s %-20s %-20s %-14s %02d/%02d/%4d %-40s %003d %-4s %-20s\n",
               n, current->regNat, current->nom, current->prenom, current->numTel, current->dateN.jour,
               current->dateN.mois, current->dateN.annee, current->adresse.rue, current->adresse.num,
               current->adresse.cp, current->adresse.ville);

        n++;
        current = current->next;
    }
}

void ajouterMed(Medecin **current, Medecin **first, Medecin **last, int *nb)
{
    Medecin *new;

    new = malloc(sizeof(Medecin));

    printf("Numéro inami : ");
    lire(new->numInami, 14);

    printf("\nNom : ");
    // fgets(new->nom, 20, stdin);
    lire(new->nom, 20);
    majuscule(&new->nom);

    printf("\nPrénom : ");
    lire(new->prenom, 20);
    majuscule(&new->prenom);

    printf("\n");
    *nb++;

    // Tri
    for (*current = *first; *current != NULL; *current = (*current)->next)
    {
        if (strcmp(new->nom, (*first)->nom) < 0)
        {
            new->next = *current;
            *first = new;
            break;
        }
        else if (strcmp(new->nom, (*current)->nom) < 0)
        {
            (*last)->next = new;
            new->next = *current;
            break;
        }
        else if ((*current)->next == NULL && strcmp(new->nom, (*current)->nom) > 0)
        {
            new->next = (*current)->next;
            (*current)->next = new;
            break;
        }
        *last = *current;
    }

    //Adresse du dernier
    for (*current = *first; *current != NULL; *current = (*current)->next)
        *last = *current;
}

void ajouterPat(Patient **current, Patient **first, Patient **last, int *nb)
{
    Patient *new;
    new = malloc(sizeof(Patient));

    printf("Nom : ");
    lire(new->nom, 20);
    majuscule(&new->nom);

    printf("\nPrénom : ");
    lire(new->prenom, 20);
    majuscule(&new->prenom);

    printf("\nNuméro de registre national : ");
    lire(new->regNat, 15);

    printf("\nNuméro de téléphone : ");
    lire(new->numTel, 13);

    printf("\nDate de naissance :\n");
    // lire(new->dateN, 8);
    printf("\tJour : ");
    new->dateN.jour = lireInt(&new->dateN.jour, 2);
    printf("\tMois : ");
    new->dateN.mois = lireInt(&new->dateN.mois, 2);
    printf("\tAnnée : ");
    new->dateN.annee = lireInt(&new->dateN.annee, 4); 

    printf("\nAdresse :\n");
    printf("\tRue : ");
    lire(new->adresse.rue, 40);
    majuscule(&new->adresse.rue);

    printf("\tNuméro : ");
    new->adresse.num = lireInt(&new->adresse.num, 3);

    printf("\tCode postal : ");
    // new->adresse.cp = lireInt(&new->adresse.cp, 4);
    lire(new->adresse.cp, 4);

    printf("\tLocalité : ");
    lire(new->adresse.ville, 20);
    majuscule(&new->adresse.ville);

    printf("\n");
    *nb++;

    // Tri
    for (*current = *first; *current != NULL; *current = (*current)->next)
    {
        if (strcmp(new->nom, (*first)->nom) < 0)
        {
            new->next = *current;
            *first = new;
            break;
        }
        else if (strcmp(new->nom, (*current)->nom) < 0)
        {
            (*last)->next = new;
            new->next = *current;
            break;
        }
        else if ((*current)->next == NULL && strcmp(new->nom, (*current)->nom) > 0)
        {
            new->next = (*current)->next;
            (*current)->next = new;
            break;
        }
        *last = *current;
    }

    //Adresse du dernier
    for (*current = *first; *current != NULL; *current = (*current)->next)
        *last = *current;
}

void supprimerMed(Medecin **first, int *nbTot)
{
    Medecin *current, *tmp;
    int n = 0, i, found = 0;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du médecin : ");
    lire(nom, 20);
    majuscule(nom);

    printf("\nEntrez le prénom du médecin : ");
    lire(prenom, 20);
    majuscule(prenom);

    // On recherche dans la liste
    current = *first;
    while (current != NULL)
    {
        n++;
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            found = 1;
            break;
        }

        current = current->next;
    }

    // Suppression
    if (n == 1 && found)
    {
        tmp = *first;
        *first = (*first)->next;
        free(tmp);
        *nbTot--;
    }
    else if (found)
    {
        n--;
        current = *first;

        // On se déplace jusqu'à l'élément précédent celui qu'on veut supprimer
        for (i = 0; i < n - 1; i++)
            current = current->next;

        if (n != *nbTot)
        {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp);
        }
        else
        {
            tmp = current->next;
            current->next = NULL;
            free(tmp);
        }

        *nbTot--;
    }
    else
        printf("\nPersonne non trouvée\n");
}

void supprimerPat(Patient **first, int *nbTot)
{
    Patient *current, *tmp;
    int n = 0, i, found = 0;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du patient : ");
    lire(nom, 20);
    majuscule(nom);

    printf("\nEntrez le prénom du patient : ");
    lire(prenom, 20);
    printf("\n");
    majuscule(prenom);

    // On recherche dans la liste
    current = *first;
    while (current != NULL)
    {
        n++;
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            found = 1;
            break;
        }

        current = current->next;
    }

    // Suppression
    if (n == 1 && found)
    {
        tmp = *first;
        *first = (*first)->next;
        free(tmp);
        *nbTot--;
    }
    else if (found)
    {
        n--;
        current = *first;

        // On se déplace jusqu'à l'élément précédent celui qu'on veut supprimer
        for (i = 0; i < n - 1; i++)
            current = current->next;

        if (n != *nbTot)
        {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp);
        }
        else
        {
            tmp = current->next;
            current->next = NULL;
            free(tmp);
        }

        *nbTot--;
    }
    else
        printf("Personne non trouvée\n");
}

void rechercherMed(Medecin *first)
{
    Medecin *current;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du médecin : ");
    lire(nom, 20);
    majuscule(&nom);

    printf("\nEntrez le prénom du médecin : ");
    lire(prenom, 20);
    printf("\n");
    majuscule(&prenom);

    printf("\n");

    // On recherche dans la liste
    current = first;
    while (current != NULL)
    {
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            printf("%-14s %-20s %-20s\n",
                   current->numInami, current->nom, current->prenom);
            return;
        }

        current = current->next;
    }

    printf("Erreur : Personne non trouvée\n");
}

void rechercherPat(Patient *first)
{
    Patient *current;
    char nom[21], prenom[21];
    char tmpNom[21], tmpPren[21];

    // On demande le nom et le prénom du médecin recherché
    printf("Entrez le nom du patient : ");
    lire(nom, 20);
    majuscule(&nom);

    printf("\nEntrez le prénom du patient : ");
    lire(prenom, 20);
    printf("\n");
    majuscule(&prenom);

    // On recherche dans la liste
    current = first;
    while (current != NULL)
    {
        strcpy(tmpNom, current->nom);
        strcpy(tmpPren, current->prenom);

        if (formatAndCompare(nom, tmpNom) == 0 && formatAndCompare(prenom, tmpPren) == 0)
        {
            printf("%-15s %-20s %-20s %-14s %02d/%02d/%4d %-40s %003d %-4s %-20s\n",
               current->regNat, current->nom, current->prenom, current->numTel, current->dateN.jour,
               current->dateN.mois, current->dateN.annee, current->adresse.rue, current->adresse.num,
               current->adresse.cp, current->adresse.ville);
            return;
        }

        current = current->next;
    }

    printf("Erreur : Personne non trouvée\n");
}

void modifierMed(Medecin *first)
{
    // TODO
}

void modifierPat(Patient *first)
{
    // TODO
}

int menuPrincipal()
{
    int choix;

    printf("\nMenu principal\n"
           "**************\n"
           "1. Médecins\n"
           "2. Patients\n"
           "3. Sauvegarder\n"
           "4. Quitter\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");

    return choix;
}

int menuMed()
{
    int choix;

    printf("\nMédecin(s)\n"
           "**********\n"
           "1. Afficher la liste\n"
           "2. Ajouter\n"
           "3. Supprimer\n"
           "4. Rechercher\n"
           "5. Modifier\n"
           "6. Retour au menu principal\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");

    return choix;
}

int menuPat()
{
    int choix;

    printf("\nPatient(s)\n"
           "**********\n"
           "1. Afficher la liste\n"
           "2. Ajouter\n"
           "3. Supprimer\n"
           "4. Rechercher\n"
           "5. Modifier\n"
           "6. Retour au menu principal\n: ");

    choix = lireInt(&choix, 1);
    printf("\n");

    return choix;
}

void sauvegarde(Medecin *firstM, Patient *firstP)
{
    Medecin *currentM;
    Patient *currentP;
    FILE *fMed, *fPat;
    fMed = fopen("medecins.dat", "w");
    fPat = fopen("patients.dat", "w");

    // Save médecins
    currentM = firstM;
    while (currentM != NULL)
    {
        fprintf(fMed, "%-14s%-20s%-20s\n",
                currentM->numInami, currentM->nom, currentM->prenom);
        currentM = currentM->next;
    }
    fclose(fMed);

    // Save patients
    currentP = firstP;
    while (currentP != NULL)
    {
        fprintf(fPat, "%-15s%-20s%-20s%-13s%02d/%02d/%4d%-40s%003d%-4s%-20s\n",
                currentP->regNat, currentP->nom, currentP->prenom, currentP->numTel, currentP->dateN.jour,
                currentP->dateN.mois, currentP->dateN.annee, currentP->adresse.rue, currentP->adresse.num,
                currentP->adresse.cp, currentP->adresse.ville);
        currentP = currentP->next;
    }
    fclose(fPat);

    printf("Sauvegarde effectuée\n");
}

void majuscule(char chaine[])
{
    int i;

    for (i = 0; chaine[i] != '\0'; i++)
    {
        chaine[i] = toupper(chaine[i]);
    }
}

void clearBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF) // Quand c = '\n' et EOF --> fin du buffer
        c = getchar();
}

int lire(char *chaine, int longueur)
{
    char *posReturn = NULL;
    longueur++; // Caractère de fin de chaîne

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        posReturn = strchr(chaine, '\n');
        if (posReturn != NULL)
        {
            *posReturn = '\0';
        }
        else
            clearBuffer();

        return 1;
    }
    else
    {
        clearBuffer();
        return 0;
    }
}

int lireInt(char *chaine, int longueur)
{
    if (lire(chaine, longueur))
        return (int)(strtol(chaine, NULL, 10));
    else
        return 0;
}

long lireLong(char *chaine, int longueur)
{
    if (lire(chaine, longueur))
        return strtol(chaine, NULL, 10);
    else
        return 0;
}

int formatAndCompare(char *chaine1, char *chaine2)
{
    // chaine 1 = nom, prenom
    // chaine 2 = current->nom, current->prenom

    int lenChaine1, lenChaine2 = 20, i = 0;
    lenChaine1 = strlen(chaine1);
    
    // printf("Longueur nom à vouloir supp : %d\n", lenChaine1);

    while (chaine2[lenChaine2] == 0 || chaine2[lenChaine2] == ' ')
        lenChaine2--;
    lenChaine2++;
    
    // printf("Longeur nom de liste chaînée = %d\n", lenChaine2);

    if (lenChaine1 == lenChaine2)
    {
        while (chaine1[i] != '\0')
        i++;

        chaine2[i] = '\0';

        return strcmp(chaine1, chaine2);
    }
    else
    {
        return 1;
    }
    
}

void lectureMedecins(Medecin **firstM, Medecin **currentM, Medecin **interM, Medecin **lastM, int *cpM)
{
    //Fichier
    FILE *fdatMed;
    fdatMed = fopen("medecins.dat", "r");
    // Premier client
    *firstM = malloc(sizeof(Medecin));

    *currentM = *firstM;

    // Lecture des clients présents dans le fichier
    fscanf(fdatMed, "%14s", (*currentM)->numInami);
    fgets((*currentM)->nom, 21, fdatMed);
    fgets((*currentM)->prenom, 21, fdatMed);
    while (!feof(fdatMed))
    {
        *interM = malloc(sizeof(Medecin));

        fscanf(fdatMed, "%14s", (*interM)->numInami);
        fgets((*interM)->nom, 21, fdatMed);
        fgets((*interM)->prenom, 21, fdatMed);

        for (*currentM = *firstM; *currentM != NULL; *currentM = (*currentM)->next)
        {
            if (strcmp((*interM)->nom, (*firstM)->nom) < 0)
            {
                (*interM)->next = *currentM;
                *firstM = *interM;
                break;
            }
            else if (strcmp((*interM)->nom, (*currentM)->nom) < 0)
            {
                (*lastM)->next = *interM;
                (*interM)->next = *currentM;
                break;
            }
            else if ((*currentM)->next == NULL && strcmp((*interM)->nom, (*currentM)->nom) > 0)
            {
                (*interM)->next = (*currentM)->next;
                (*currentM)->next = *interM;
                break;
            }
            *lastM = *currentM;
        }
        (*cpM)++;
    }
    *currentM = (*firstM)->next;
    free(*firstM);
    *firstM = *currentM;

    //Adresse du dernier
    for (*currentM = *firstM; *currentM != NULL; *currentM = (*currentM)->next)
        *lastM = *currentM;
}

void lecturePatients(Patient **firstP, Patient **currentP, Patient **interP, Patient **lastP, int *cpP)
{
    //Fichier
    FILE *fdatPat;
    fdatPat = fopen("patients.dat", "r");
    // Premier client
    *firstP = malloc(sizeof(Patient));

    *currentP = *firstP;

    // Lecture des clients présents dans le fichier
    fscanf(fdatPat, "%15s", (*currentP)->regNat);
    fgets((*currentP)->nom, 21, fdatPat);
    fgets((*currentP)->prenom, 21, fdatPat);
    fscanf(fdatPat, "%13s", (*currentP)->numTel);
    // fgets((*currentP)->numTel, 14, fdatPat);
    fscanf(fdatPat, "%2d%*c%2d%*c%4d", &(*currentP)->dateN.jour, &(*currentP)->dateN.mois, &(*currentP)->dateN.annee);
    fgets((*currentP)->adresse.rue, 41, fdatPat);
    fscanf(fdatPat, "%3d %4s", &(*currentP)->adresse.num, &(*currentP)->adresse.cp);
    fgets((*currentP)->adresse.ville, 21, fdatPat);
    while (!feof(fdatPat))
    {
        *interP = malloc(sizeof(Patient));

        fscanf(fdatPat, "%15s", (*interP)->regNat);
        fgets((*interP)->nom, 21, fdatPat);
        fgets((*interP)->prenom, 21, fdatPat);
        fscanf(fdatPat, "%13s", (*interP)->numTel);
        fscanf(fdatPat, "%2d%*c%2d%*c%4d", &(*interP)->dateN.jour, &(*interP)->dateN.mois, &(*interP)->dateN.annee);
        fgets((*interP)->adresse.rue, 41, fdatPat);
        fscanf(fdatPat, "%3d %4s", &(*interP)->adresse.num, &(*interP)->adresse.cp);
        fgets((*interP)->adresse.ville, 21, fdatPat);

        for (*currentP = *firstP; *currentP != NULL; *currentP = (*currentP)->next)
        {
            if (strcmp((*interP)->nom, (*firstP)->nom) < 0)
            {
                (*interP)->next = *currentP;
                *firstP = *interP;
                break;
            }
            else if (strcmp((*interP)->nom, (*currentP)->nom) < 0)
            {
                (*lastP)->next = *interP;
                (*interP)->next = *currentP;
                break;
            }
            else if ((*currentP)->next == NULL && strcmp((*interP)->nom, (*currentP)->nom) > 0)
            {
                (*interP)->next = (*currentP)->next;
                (*currentP)->next = *interP;
                break;
            }
            *lastP = *currentP;
        }
        (*cpP)++;
    }
    *currentP = (*firstP)->next;
    free(*firstP);
    *firstP = *currentP;

    //Adresse du dernier
    for (*currentP = *firstP; *currentP != NULL; *currentP = (*currentP)->next)
        *lastP = *currentP;
}
