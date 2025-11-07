#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
// Fonctions d'opérations
float add(float a, float b) { return a + b; }
float sub(float a, float b) { return a - b; }
float mul(float a, float b) { return a * b; }
float div_op(float a, float b) { return a / b; }

// Fonction qui retourne le pointeur vers l'opération appropriée
float (*get_operation(char op))(float, float) {
    switch(op) {
        case '+': return add;
        case '-': return sub;
        case '*': return mul;
        case '/': return div_op;
        default: return NULL;
    }
}


//Fp1.2.3 : Verifier le nombre d'operateurs
bool verifier_le_nombre_operateurs(char* nombre_utilisateur){
    int compteur_operateurs = 0;
    int compteur_nombres = 0;  // Nom plus clair
    int i = 0;
    
    while (nombre_utilisateur[i] != '\0'){
        
        // Ignorer les espaces
        if (isspace(nombre_utilisateur[i])){
            i++;
        }
        
        // Compter un nombre (peut avoir plusieurs chiffres)
        if (isdigit(nombre_utilisateur[i])){
            compteur_nombres++;
            // Sauter tous les chiffres du même nombre
            while (isdigit(nombre_utilisateur[i])){
                i++;
            }
        }
        
        // Compter un opérateur
        if (nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || 
            nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/'){
            compteur_operateurs++;
            i++;
        }
        
        // Caractère invalide (lettre, ponctuation, etc.)
        if (isalpha(nombre_utilisateur[i]) || ispunct(nombre_utilisateur[i])){
            printf("Erreur : caractere invalide '%c'\n", nombre_utilisateur[i]);
            return false;
        }
        
        i++;
    }
    
    // Vérifier la relation : nb_operateurs = nb_nombres - 1
    if (compteur_operateurs != compteur_nombres - 1){
        printf("Erreur : il doit y avoir 1 operateur de moins que le nombre de chiffres\n");
        return false;
    }
    
    return true;
}

//Fp1.2 : Verifier la saisie utilisateur
int verifier_la_valeur(char* nombre_utilisateur){
    // Vérifier les caractères invalides
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
        if (!isdigit(nombre_utilisateur[i]) && nombre_utilisateur[i] != '+' 
            && nombre_utilisateur[i] != '-' && nombre_utilisateur[i] != '/' 
            && nombre_utilisateur[i] != '*' && nombre_utilisateur[i] != '\n' 
            && nombre_utilisateur[i] != ' ' && nombre_utilisateur[i] != '.'){
            printf("Erreur : entree invalide '%c'\n", nombre_utilisateur[i]);
            return -1;
        }
    }
    
    // Vérifier qu'on ne colle pas chiffres et opérateurs
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
        char suivant = nombre_utilisateur[i+1];

        // Chiffre suivi directement d'un opérateur (sans espace)
        if (isdigit(nombre_utilisateur[i]) && 
            (suivant == '+' || suivant == '-' || suivant == '*' || suivant == '/')){
            printf("Erreur : ne pas coller chiffre et operateur\n");
            return -1;
        }
        
        // Opérateur suivi directement d'un chiffre (sans espace)
        if ((nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || 
             nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') && 
            isdigit(suivant)){
            printf("Erreur : ne pas coller operateur et chiffre\n");
            return -1;
        }
    }
    
    // Vérifier qu'il y a au moins 2 nombres dans l'expression
    int compteur_nombres = 0;
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
        if (isdigit(nombre_utilisateur[i])) {
            compteur_nombres++;
            // Sauter les autres chiffres du même nombre
            while(isdigit(nombre_utilisateur[i + 1])) {
                i++;
            }
        }
    }
    
    if (compteur_nombres < 2){
        printf("Erreur : deux nombres sont necessaires au minimum\n");
        return -1;
    }
    
    // Vérifier le nombre d'opérateurs
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
    printf("Entrer des chiffres suivis d'operateurs : ");
    fgets(nombre_utilisateur, taille, stdin);
    
    // Verification de la saisie utilisateur
    if (verifier_la_valeur(nombre_utilisateur) == -1) {
        free(nombre_utilisateur);
        return NULL;
    }
    
    return nombre_utilisateur;
}

//Fp2.2 : Trier les elements
float trier_les_elements(char* nombre_utilisateur){
    float nombres[50];  // Tableau pour stocker les nombres
    int nb_count = 0;  // Compteur de nombres
    float resultat = 0;
    int i =0;
    while(nombre_utilisateur[i] != '\0'){
        if (isdigit(nombre_utilisateur[i])) {
            //fusion des chiffres en nombres entiers
            float nombre = 0;
            
            // Tant qu'on a des chiffres, on continue
            while (isdigit(nombre_utilisateur[i])) {
                nombre = nombre * 10 + (nombre_utilisateur[i] - '0');
                i++;
            }
            i--;  // On recule car la boucle for va faire i++

            nombres[nb_count] = nombre;
            nb_count++;
            
        }
        else if (nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || 
                 nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') {
            
            // Obtenir la fonction d'opération
            float (*operation)(float, float) = get_operation(nombre_utilisateur[i]);
            
            if (operation != NULL) {
                // Vérification division par zéro
                if (nombre_utilisateur[i] == '/' && nombres[nb_count - 1] == 0) {
                    printf("Erreur: Division par zero\n");
                    return -1;
                }
                
                resultat = operation(nombres[nb_count - 2], nombres[nb_count - 1]);
                nombres[nb_count - 2] = resultat;
                nb_count--;
            }
        }
        i++;
    }
    
    return nombres[0];
}

//Fp2 : Calculer le resultat
float calcule(char* nombre_utilisateur){
    // Fonction de calcul à implémenter
    float res = trier_les_elements(nombre_utilisateur);
    return res;
}

int main(){
    char* nombre_utilisateur = obtenir();

    if (nombre_utilisateur != NULL) {
        
        float res = calcule(nombre_utilisateur);
        printf("Le resultat est : %.2f\n", res);
        
        free(nombre_utilisateur);
    }
    
    return 0;
}