#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char* uniforme(char* nombre_utilisateur) {
    char* result = malloc(strlen(nombre_utilisateur) + 1);
    if (result == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
    int j = 0;
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++) {
        if (nombre_utilisateur[i] != ' ') {
            result[j++] = nombre_utilisateur[i];
        }
    }
    result[j] = '\0';
    return result;

}
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
    int compteur_chiffres = 0;

    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
        if(isspace(nombre_utilisateur[i])){
            continue;
        }
        if (isdigit(nombre_utilisateur[i])) {
                compteur_chiffres++;

                while(isdigit(nombre_utilisateur[i + 1])) {
                    i++;
                }
        }

        else if (nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || 
                 nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') {
            compteur_operateurs++;
        }
        else {
            printf("Erreur : caractere invalide '%c'\n", nombre_utilisateur[i]);
        }
    }
    if (compteur_operateurs != compteur_chiffres -1) {
        printf("Erreur : il doit y avoir 1 operateur de moins que le nombre de chiffres\n");
        return false;
    }
    return true;
    
}

//Fp1.2 : Verifier la saisie utilisateur
int verifier_la_valeur(char* nombre_utilisateur){
    int compteur = 0;
    for (int i = 0; nombre_utilisateur[i] != '\0'; i++){
       if (!isdigit(nombre_utilisateur[i]) && nombre_utilisateur[i] != '+' 
            && nombre_utilisateur[i] != '-' && nombre_utilisateur[i] != '/' 
            && nombre_utilisateur[i] != '*' && nombre_utilisateur[i] != '\n' 
            && nombre_utilisateur[i] != ' ' && nombre_utilisateur[i] != '.'){
            printf("Erreur : entree invalide '%c'\n", nombre_utilisateur[i]);
            return -1;
        }
    
        char suivant = nombre_utilisateur[i+1];

        if (isdigit(nombre_utilisateur[i]) && !isdigit(suivant) && suivant != ' ' && suivant != '\n' && suivant != '\0' && suivant != '.'){
            printf("Erreur : ne pas coller chiffre et operateur\n");
            return -1;
        }
        if ((nombre_utilisateur[i] == '+' || nombre_utilisateur[i] == '-' || nombre_utilisateur[i] == '*' || nombre_utilisateur[i] == '/') && isdigit(suivant)){
            printf("Erreur : ne pas coller operateur et chiffre\n");
            return -1;
        }
        // verfier qu'il y a au moins deux chiffres au debut
        while (isdigit(nombre_utilisateur[i + compteur]) ) {
                compteur++;
        }
        compteur++;
        if(i == 0 && !isdigit(nombre_utilisateur[compteur]) ){
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
int trier_les_elements(char* nombre_utilisateur){
    float nombres[50];  // Tableau pour stocker les nombres
    int nb_count = 0;  // Compteur de nombres
    float resultat = 0;
    
    for(int i = 0; nombre_utilisateur[i] != '\0'; i++){
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
    }
    
    return nombres[0];
}

//Fp2 : Calculer le resultat
int calcule(char* nombre_utilisateur){
    // Fonction de calcul à implémenter
    float res = trier_les_elements(nombre_utilisateur);
    return res;
}

int main(){
    char* nombre_utilisateur = obtenir();
    int res;

    if (nombre_utilisateur != NULL) {
        
        float res = calcule(nombre_utilisateur);
        printf("Le resultat est : %.2f\n", res);
        
        free(nombre_utilisateur);
    }
    
    return 0;
}