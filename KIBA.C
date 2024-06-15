#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPTES_PAR_JOUR 100
#define SOLDE_MINIMUM 5

// Structures pour stocker les informations de l'utilisateur
typedef struct {
    char operatorName[20];
    char nom[50];
    char postnom[50];
    char prenom[50];
    char dateDeNaissance[11];  // Format: YYYY-MM-DD
    char lieuDeNaissance[50];  // Pays
    char adresseActuelle[100]; // Exemple: "Pays, Ville, Commune, Avenue, Num�ro de la parcelle"
    char numeroDeTelephone[15];
    float balanceFC;
    float balanceUSD;
} MobileMoneyAccount;

typedef struct {
    char numeroDeCompte[15];   // 14 chiffres + '\0'
    MobileMoneyAccount titulaire;
    double solde;
    char dateDeCreation[11];   // Format: YYYY-MM-DD
} CompteBancaire;

void genererNumeroDeCompte(char *numeroDeCompte, int compteIndex) {
    sprintf(numeroDeCompte, "%014d", compteIndex);
}

void obtenirDateCourante(char *date) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(date, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}

void creerCompteBancaire(MobileMoneyAccount account) {
    CompteBancaire compte;
    static int compteIndex = 10000000000000; // Index de d�part pour les num�ros de compte
    genererNumeroDeCompte(compte.numeroDeCompte, compteIndex++);
    obtenirDateCourante(compte.dateDeCreation);
    compte.solde = 0.0;

    printf("Entrez le nom: ");
    scanf("%s", compte.titulaire.nom);
    printf("Entrez le postnom: ");
    scanf("%s", compte.titulaire.postnom);
    printf("Entrez le prenom: ");
    scanf("%s", compte.titulaire.prenom);
    printf("Entrez la date de naissance (YYYY-MM-DD): ");
    scanf("%s", compte.titulaire.dateDeNaissance);
    printf("Entrez le lieu de naissance (pays): ");
    scanf("%s", compte.titulaire.lieuDeNaissance);
    printf("Entrez l'adresse actuelle (pays, ville, commune, avenue, numero de la parcelle): ");
    scanf(" %[^\n]", compte.titulaire.adresseActuelle); // Utilisation de " %[^\n]" pour lire des espaces
    printf("Entrez le numero de telephone: ");
    scanf("%s", compte.titulaire.numeroDeTelephone);

    // Enregistrer les informations dans un fichier CSV
    FILE *file = fopen("comptes.csv", "a");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%.2f,%s\n",
        compte.numeroDeCompte,
        compte.titulaire.nom,
        compte.titulaire.postnom,
        compte.titulaire.prenom,
        compte.titulaire.dateDeNaissance,
        compte.titulaire.lieuDeNaissance,
        compte.titulaire.adresseActuelle,
        compte.titulaire.numeroDeTelephone,
        compte.dateDeCreation,
        compte.solde,
        compte.dateDeCreation);

    fclose(file);

    printf("Compte bancaire cree avec succes ! Numero de compte: %s\n", compte.numeroDeCompte);
}