#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//Fp1.2.3 : Verifier le nombre d'operateurs
bool verifier_le_nombre_operateurs(char* nombre_utilisateur){
    int compteur_operateurs = 0;
    int compteur_chiffres = 0;
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
        if (isdigit(nombre_utilisateur[i])) {
            compteur_chiffres++;
        }
        else if (nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || 
                 nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') {
            compteur_operateurs++;
        }
        else {
            continue;
        }
    }
    if (compteur_operateurs != compteur_chiffres -1) {
        printf("Erreur : il doit y avoir plus de chiffres que d'operateurs\n");
        return false;
    }
    else {
        return true;
    }
}

//Fp1.2 : Verifier la saisie utilisateur
int verifier_la_valeur(char* nombre_utilisateur){
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
        if (!isdigit(nombre_utilisateur[i]) && nombre_utilisateur[i] != '+' 
            && nombre_utilisateur[i] != '-' && nombre_utilisateur[i] != '/' 
            && nombre_utilisateur[i] != '*' && nombre_utilisateur[i] != '\n' 
            && nombre_utilisateur[i] != ' '){
            // if the character is not numeric or an operator
            printf("Erreur : entree invalide '%c'\n", nombre_utilisateur[i]);
            return -1;
        }

        char suivant = nombre_utilisateur[i+1];
    if (isdigit(nombre_utilisateur[i]) && !isdigit(suivant) && suivant != ' ' && suivant != '\n' && suivant != '\0'){
        printf("Erreur : ne pas coller chiffre et operateur\n");
        return -1;
    }
    if ((nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') && isdigit(suivant)){
        printf("Erreur : ne pas coller operateur et chiffre\n");
        return -1;
    }

            if(i == 1 && !isdigit(nombre_utilisateur[0]) && !isdigit(nombre_utilisateur[1])){
                // Si les deux premiers caracteres ne sont pas des chiffres
                printf("Erreur : deux chiffres sont necessaire au debut\n");
                return -1;

            }
        
        }
    if (!verifier_le_nombre_operateurs(nombre_utilisateur)){
        return -1;
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
    if (verifier_la_valeur(nombre_utilisateur) == -1) {
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
        printf("Vous avez entrez : %s\n", nombre_utilisateur);
        
        int res = calcule(nombre_utilisateur);
        
        free(nombre_utilisateur);
    }
    
    return 0;
}