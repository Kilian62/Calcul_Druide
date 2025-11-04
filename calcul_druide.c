#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Fp1.2 : Verifier la saisie utilisateur
int verifier(char* nombre_utilisateur){
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
        if (!isdigit(nombre_utilisateur[i]) && nombre_utilisateur[i] != '+' 
            && nombre_utilisateur[i] != '-' && nombre_utilisateur[i] != '/' 
            && nombre_utilisateur[i] != '*' && nombre_utilisateur[i] != '\n' 
            && nombre_utilisateur[i] != ' '){
            // if the character is not numeric or an operator
            printf("Erreur : entree invalide '%c'\n", nombre_utilisateur[i]);
            return -1;
        }
       /* if(i < 1 && !isdigit(nombre_utilisateur[i])){
            printf("Erreur : l'expression doit commencer par 2 chiffres\n");
            return -1;
        }*/
    }
    return 0;
}

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
    printf("Entrer des chiffres suivis d'operateurs : \n");
    fgets(nombre_utilisateur, taille, stdin);
    
    // Verification de la saisie utilisateur
    if (verifier(nombre_utilisateur) == -1) {
        free(nombre_utilisateur);
        return NULL;
    }
    
    return nombre_utilisateur;
}

//Fp2.2 : Trier les elements
int trier_les_elements(char* nombre_utilisateur){
    int nombres[50];  // Tableau pour stocker les nombres
    int nb_count = 0;  // Compteur de nombres
    
    for(int i = 0; nombre_utilisateur[i] != '\0'; i++){
        if (isdigit(nombre_utilisateur[i])) {
            //fusion des chiffres en nombres entiers
            int nombre = 0;
            
            // Tant qu'on a des chiffres, on continue
            while (isdigit(nombre_utilisateur[i])) {
                nombre = nombre * 10 + (nombre_utilisateur[i] - '0');
                i++;
            }
            i--;  // On recule car la boucle for va faire i++

            nombres[nb_count] = nombre;
            nb_count++;
            
            printf("Nombre trouve: %d\n", nombre);
        }
        else if (nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || 
                 nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') {
            // On peut traiter les operateurs ici si besoin
            printf("Operateur trouve: %c\n", nombre_utilisateur[i]);
        }
    }
    
    return 0;
}

//Fp2 : Calculer le resultat
int calcule(char* nombre_utilisateur){
    // Fonction de calcul à implémenter
    trier_les_elements(nombre_utilisateur);
    return 0;
}

int main(){
    char* nombre_utilisateur = obtenir();
    int res;

    if (nombre_utilisateur != NULL) {
        printf("Vous avez entre : %s\n", nombre_utilisateur);
        
        int res = calcule(nombre_utilisateur);
        
        free(nombre_utilisateur);
    }
    
    return 0;
}