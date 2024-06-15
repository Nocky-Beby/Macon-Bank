#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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