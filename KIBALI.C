#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
        if (amount > account->balanceFC-sold_min) {
            printf("Solde insuffisant.\n");
        } else {
            account->balanceFC -= amount;
            printf("Retrait reussi! Nouveau solde en FC: %.2f\n", account->balanceFC);
        }
    } else if (currency == 'U' || currency == 'u') {
        printf("Entrez le montant en USD: ");
        scanf("%f", &amount);
        if (amount > account->balanceUSD-SOLDE_MINIMUM) {
            printf("Solde insuffisant.\n");
        } else {
            account->balanceUSD -= amount;
            printf("Retrait réussi! Nouveau solde en USD: %.2f\n", account->balanceUSD);
        }
    } else {
        printf("Devise invalide.\n");
    }
}