#ifndef _MATRICE_H_
#define _MATRICE_H_

struct matrice_
{
  double *valeur;
  int nb_lignes;
  int nb_colonnes;
  
};
typedef struct matrice_ matrice;

double norme(matrice* x,int taille);

matrice *lire_vector(int);
matrice *lire_matrice(int, double, double);
matrice *lire_vector_fixe(char *fichier);
matrice *lire_matrice_fixe(char *fichier);


void AfficheMatrice(matrice *matrix);
void desaloc_mat(matrice *matrix);
void desaloc_vec(matrice *vec);
void AfficheVecteur(matrice* vec);
double dotprod_simple(matrice* x, matrice* y,int);

#endif 
