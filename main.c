#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPTES_PAR_JOUR 100
// Structures pour stocker les informations de l'utilisateur
typedef struct {
    char operatorName[20];
    char nom[50];
    char postnom[50];
    char prenom[50];
    char dateDeNaissance[11];  // Format: YYYY-MM-DD
    char lieuDeNaissance[50];  // Pays
    char adresseActuelle[100]; // Exemple: "Pays, Ville, Commune, Avenue, Numéro de la parcelle"
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
    static int compteIndex = 10000000000000; // Index de départ pour les numéros de compte
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

// Fonction pour afficher le menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. creerCompteBancaire\n");
    printf("2. Effectuer un depot\n");
    printf("3. Retirer de l'argent\n");
    printf("4. Quitter\n");
    printf("Veuillez choisir une option: ");
}


// Fonction pour effectuer un dépôt
void deposit(MobileMoneyAccount *account) {
    char currency;
    float amount;
    long int NumeroDeCompte;
    printf("\nEntrez le numero de compte : ");
    scanf("%ld", &NumeroDeCompte);
    printf("\nChoisissez la devise (F pour FC, U pour USD): ");
    getchar(); // Pour consommer le '\n' restant
    scanf("%c", &currency);



    if (currency == 'F' || currency == 'f') {
        printf("Entrez le montant en FC: ");
        scanf("%f", &amount);
        if (amount >= 5000) {
            account->balanceFC += amount;
            printf("Depot reussi! Nouveau solde en FC: %.2f\n", account->balanceFC);
        } else {
            printf("Le montant doit etre supérieur ou égal à 5000 FC.\n");
        }
    } else if (currency == 'U' || currency == 'u') {
        printf("Entrez le montant en USD: ");
        scanf("%f", &amount);
        if (amount >= 5) {
            account->balanceUSD += amount;
            printf("Depot reussi! Nouveau solde en USD: %.2f\n", account->balanceUSD);
        } else {
            printf("Le montant doit être supérieur ou égal à 5 USD.\n");
        }
    } else {
        printf("Devise invalide.\n");
    }
}

// Fonction pour retirer de l'argent
void withdraw(MobileMoneyAccount *account) {
    char currency;
    float amount;
    printf("\nChoisissez la devise (F pour FC, U pour USD): ");
    getchar(); // Pour consommer le '\n' restant
    scanf("%c", &currency);

    if (currency == 'F' || currency == 'f') {
        printf("Entrez le montant en FC: ");
        scanf("%f", &amount);
        if (amount <= account->balanceFC) {
            account->balanceFC -= amount;
            printf("Retrait reussi! Nouveau solde en FC: %.2f\n", account->balanceFC);
        } else {
            printf("Solde insuffisant.\n");
        }
    } else if (currency == 'U' || currency == 'u') {
        printf("Entrez le montant en USD: ");
        scanf("%f", &amount);
        if (amount <= account->balanceUSD) {
            account->balanceUSD -= amount;
            printf("Retrait réussi! Nouveau solde en USD: %.2f\n", account->balanceUSD);
        } else {
            printf("Solde insuffisant.\n");
        }
    } else {
        printf("Devise invalide.\n");
    }
}

int main() {
    MobileMoneyAccount account;
    int choice;

    // Initialisation du compte
    printf("Choisissez votre banque (Rawbank, Illicocash, Equity_bank, Ecobank): ");
    scanf("%s", account.operatorName);
    account.balanceFC = 0.0;
    account.balanceUSD = 0.0;

    printf("\nBienvenue sur %s\n", account.operatorName);

    // Boucle principale du programme
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                creerCompteBancaire(account);
                break;
            case 2:
                deposit(&account);
                break;
            case 3:
                withdraw(&account);
                break;
            case 4:
                printf("Merci d'avoir utilise nos services !\n");
                break;
            default:
                printf("Option invalide, veuillez réessayer.\n");
        }
    } while (choice != 4);

    return 0;
}
