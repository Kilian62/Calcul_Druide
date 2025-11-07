# 🧙‍♂️ Le Calcul le Plus Magique ✨

Bienvenue druide master ! Cette calculatrice magique effectue des calculs séquentiels de gauche à droite, comme un véritable sortilège mathématique !

## 📜 Description

Ce programme en C permet d'effectuer des calculs en chaîne avec les opérations de base (+, -, \*, /). Contrairement aux calculatrices classiques, celle-ci évalue les opérations **de gauche à droite** sans priorité des opérateurs.

## ✨ Fonctionnalités

- ✅ Addition, soustraction, multiplication et division
- ✅ Validation automatique de la saisie utilisateur
- ✅ Détection des erreurs (division par zéro, format invalide)
- ✅ Calcul séquentiel de gauche à droite
- ✅ Support des espaces dans la saisie
- ✅ Affichage du résultat avec 2 décimales

## 🛠️ Compilation

```bash
gcc -o calculatrice calculatrice.c -Wall -Wextra
```

## 🚀 Utilisation

Lancez le programme :

```bash
./calculatrice
```

Entrez votre calcul en respectant le format : **nombre opérateur nombre opérateur nombre...**

### Exemples valides :

```
Entrer des chiffres suivis d'operateurs : 10 + 5 * 2
Le resultat est : 30.00

Entrer des chiffres suivis d'operateurs : 100 / 2 - 25
Le resultat est : 25.00
```

### ⚠️ Format requis :

- Au moins **2 nombres** au début
- **1 opérateur de moins** que le nombre de chiffres
- **Espaces obligatoires** entre les nombres et les opérateurs
- Opérateurs supportés : `+`, `-`, `*`, `/`

## 📐 Règles de calcul

Le calcul s'effectue **séquentiellement de gauche à droite** :

```
10 + 5 * 2
→ (10 + 5) * 2
→ 15 * 2
→ 30
```

## ❌ Erreurs gérées

Le programme détecte et affiche des messages pour :

- Caractères invalides
- Format incorrect (opérateur collé au chiffre)
- Nombre d'opérateurs incorrect
- Division par zéro
- Moins de 2 nombres au début

## 🧩 Structure du code

### Fonctions principales :

| Fonction                          | Description                                |
| --------------------------------- | ------------------------------------------ |
| `obtenir()`                       | Récupère et valide la saisie utilisateur   |
| `verifier_la_valeur()`            | Vérifie le format de la saisie             |
| `verifier_le_nombre_operateurs()` | Valide le nombre d'opérateurs              |
| `calcule()`                       | Orchestre le calcul                        |
| `trier_les_elements()`            | Parse et effectue les calculs séquentiels  |
| `get_operation()`                 | Retourne le pointeur de fonction approprié |

### Opérations :

- `add()` : Addition
- `sub()` : Soustraction
- `mul()` : Multiplication
- `div_op()` : Division

## 🐛 Corrections à apporter

Pour supprimer les warnings de compilation :

1. Ajouter `#include <string.h>` en haut du fichier
2. Changer le type de retour de `trier_les_elements()` et `calcule()` de `int` à `float`

## 📝 Exemple d'exécution

```
Bienvenu druide master !!
Entrer des chiffres suivis d'operateurs : 15 + 10 / 5
Le resultat est : 5.00
```

**Explication :** (15 + 10) / 5 = 25 / 5 = 5

## 🔮 Magie des pointeurs de fonctions

Ce programme utilise des **pointeurs de fonctions** pour sélectionner dynamiquement l'opération à effectuer, rendant le code élégant et extensible !

---

_Que la magie des mathématiques soit avec vous, druide master !_ 🌟
