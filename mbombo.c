#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// Fonction pour afficher le menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. creerCompteBancaire\n");
    printf("2. Effectuer un depot\n");
    printf("3. Retirer de l'argent\n");
    printf("4. Quitter\n");
    printf("Veuillez choisir une option: ");
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
