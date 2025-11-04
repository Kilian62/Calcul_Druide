#include <stdio.h>
#include <stdlib.h>

//Fp1 : Obtenir une saisie utilisateur
int obtenir(){
    // Allocation pour la saisie utilisateur
    int taille = 100;
    char *num = malloc(taille * sizeof(char));
    if (num == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return 1;
    }  
    // Demande de saisie utilisateur et obtention
    printf("Bienvenu druide master !!\n");
    printf("Entrer des chiffres suivis d'operateur : \n");
    fgets(num, taille, stdin);
        
    return num;
}


int main(){
 char* num = obtenir();
printf("%s\n", num);
    free(num);
return 0;
}