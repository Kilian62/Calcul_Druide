#include <stdio.h>
#include <stdlib.h>

//Fp1 : Obtenir une saisie utilisateur
char* obtenir(){
    // Allocation pour la saisie utilisateur
    int taille = 100;
    char *nombre_utilisateur = malloc(taille * sizeof(char));
    if (nombre_utilisateur == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }  
    // Demande de saisie utilisateur et obtention
    printf("Bienvenu druide master !!\n");
    printf("Entrer des chiffres suivis d'operateur : \n");
    fgets(nombre_utilisateur, taille, stdin);
        
    return nombre_utilisateur;
}

//Fp2 : Calculer le resultat
int calcule(char* nombre_utilisateur){
    // Fonction de calcul à implémenter
    trier_les_elements(nombre_utilisateur);
    return 0;
}

//Fp2.2 : Trier les elements
int trier_les_elements(char* nombre_utilisateur){
    for(int i = 0;nombre_utilisateur[i]; i++){
        // Implémentation du tri
        /*printf("Caractere %d : %c\n", i, nombre_utilisateur[i]);*/
        
    }
    return 0;
}

int main(){
    char* nombre_utilisateur = obtenir();

    if (nombre_utilisateur != NULL) {
        printf("%s\n", nombre_utilisateur);
        
        int res = calcule(nombre_utilisateur);
        
        free(nombre_utilisateur);
    }
    
    return 0;
}