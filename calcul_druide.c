#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// Fonctions d'opérations utilisées dans calcule
float add(float a, float b) { 
    return a + b; 
}
float sub(float a, float b) { 
    return a - b; 
}
float mul(float a, float b) { 
    return a * b; 
}
float div_op(float a, float b) { 
    return a / b;
}

// Fonction utilisée dans calcule : Obtenir la fonction d'opération
float (*get_operation(char op))(float, float) {
    switch(op) {
        case '+': return add;
        case '-': return sub;
        case '*': return mul;
        case '/': return div_op;
        default: return NULL;
    }
}

// Fonction utilisée dans verifier_le_nombre_operateurs : Traiter espaces et nombres
void traiter_espaces_et_nombres(const char *chaine, int *i, int *compteur_nombres) {
    // Ignorer les espaces
    if (isspace(chaine[*i])) {
        (*i)++;
    }
    
    // Compter un nombre (peut avoir plusieurs chiffres)
    if (isdigit(chaine[*i])) {
        (*compteur_nombres)++;
        // Sauter tous les chiffres du même nombre
        while (isdigit(chaine[*i])) {
            (*i)++;
        }
    }
}

// Fonction utilisée dans verifier_le_nombre_operateurs : Traiter opérateurs et invalides
int traiter_operateurs_et_invalides(const char *chaine, int *i, int *compteur_operateurs) {
    // Compter un opérateur
    if (chaine[*i] == '+' || chaine[*i] == '-' || 
        chaine[*i] == '*' || chaine[*i] == '/') {
        (*compteur_operateurs)++;
        (*i)++;
    }
    
    // Caractère invalide (lettre, ponctuation, etc.)
    if (isalpha(chaine[*i]) || ispunct(chaine[*i])) {
        printf("Erreur : caractere invalide '%c'\n", chaine[*i]);
        return -1;  // Erreur
    }
    
    return 0;  // Succès
}

//Fonction utilisée dans verifier_la_valeur : Vérifier le nombre d'opérateurs
bool verifier_le_nombre_operateurs(char* nombre_utilisateur){
    int compteur_operateurs = 0;
    int compteur_nombres = 0;
    int i = 0;
    
    while (nombre_utilisateur[i] != '\0') {
    
    // Fonction 1
    traiter_espaces_et_nombres(nombre_utilisateur, &i, &compteur_nombres);
    
    // Fonction 2
    if (traiter_operateurs_et_invalides(nombre_utilisateur, &i, &compteur_operateurs) == -1) {
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

// Fonction utilisée dans verifier_la_valeur : Vérifier l'espacement entre chiffres et opérateurs
int verifier_espacement(char actuel, char suivant) {
    // Chiffre suivi directement d'un opérateur (sans espace)
    if (isdigit(actuel) && 
        (suivant == '+' || suivant == '-' || suivant == '*' || suivant == '/')) {
        printf("Erreur : ne pas coller chiffre et operateur\n");
        return -1;
    }
    
    // Opérateur suivi directement d'un chiffre (sans espace)
    if ((actuel == '+' || actuel == '-' || actuel == '*' || actuel == '/') && 
        isdigit(suivant)) {
        printf("Erreur : ne pas coller operateur et chiffre\n");
        return -1;
    }
    
    return 0;  // Pas d'erreur
}

// Fonction utilisée dans verifier_la_valeur : Compter le nombre de nombres dans la chaîne
int compter_nombres(const char *chaine) {
    int compteur = 0;
    
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (isdigit(chaine[i])) {
            compteur++;
            // Sauter les autres chiffres du même nombre
            while(isdigit(chaine[i + 1])) {
                i++;
            }
        }
    }
    
    return compteur;
}

//Fonction utilisée dans obtenir : Vérifier la validité de la saisie utilisateur
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
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++) {
    char suivant = nombre_utilisateur[i+1];
    
    if (verifier_espacement(nombre_utilisateur[i], suivant) == -1) {
        return -1;
    }
}
    
    // Vérifier qu'il y a au moins 2 nombres dans l'expression
    int compteur_nombres = compter_nombres(nombre_utilisateur);
    
    if (compteur_nombres < 2 && !verifier_le_nombre_operateurs(nombre_utilisateur)){
        printf("Erreur : deux nombres sont necessaires au minimum\n");
        return -1;
    }
    
    return 0;
}

//Fonction utilisé dans main : Obtenir la saisie utilisateur
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

// Fonction 1 utilisé dans trier_les_elements : Extraire un nombre
float extraire_nombre(const char *chaine, int *position, float *nombres, int *nb_count) {
    float nombre = 0;
    
    // Tant qu'on a des chiffres, on continue
    while (isdigit(chaine[*position])) {
        nombre = nombre * 10 + (chaine[*position] - '0');
        (*position)++;
    }
    (*position)--;  // On recule car la boucle appelante va incrémenter
    
    nombres[*nb_count] = nombre;
    (*nb_count)++;
    
    return nombre;
}

// Fonction 2 utilisé dans trier_les_elements : Traiter une opération
void traiter_operation(char operateur, float *nombres, int *nb_count) {
    // Obtenir la fonction d'opération
    float (*operation)(float, float) = get_operation(operateur);
    
    if (operation != NULL) {
        // Vérification division par zéro
        if (operateur == '/' && nombres[*nb_count - 1] == 0) {
            printf("Erreur: Division par zero\n");
            exit(1);
        }
        
        float resultat = operation(nombres[*nb_count - 2], nombres[*nb_count - 1]);
        nombres[*nb_count - 2] = resultat;
        (*nb_count)--;
    }
}

//Fonction utilisée dans calcule : Trier les éléments
float trier_les_elements(char* nombre_utilisateur) {
    float nombres[50];  // Tableau pour stocker les nombres
    int nb_count = 0;   // Compteur de nombres
    int i = 0;
    
    while(nombre_utilisateur[i] != '\0') {
        if (isdigit(nombre_utilisateur[i])) {
            // Fonction 1
            extraire_nombre(nombre_utilisateur, &i, nombres, &nb_count);
        }
        else if (nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || 
                 nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') {
            // Fonction 2
            traiter_operation(nombre_utilisateur[i], nombres, &nb_count);
        }
        i++;
    }
    
    return nombres[0];
}

//Fonction utilisée dans main : Calculer le résultat
float calcule(char* nombre_utilisateur){
    float res = trier_les_elements(nombre_utilisateur);
    return res;
}

//Fonction principale
int main(){
    char* nombre_utilisateur = obtenir();

    if (nombre_utilisateur != NULL) {
        
        float res = calcule(nombre_utilisateur);
        printf("Le resultat est : %.2f\n", res);
        free(nombre_utilisateur);
    }
    else {
        return 1;
    }
    return 0;
}