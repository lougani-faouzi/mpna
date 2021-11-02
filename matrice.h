#ifndef _MATRICE_H_
#define _MATRICE_H_

struct matrice_
{
  double *valeur;
  int nb_lignes;
  int nb_colonnes;
  
};
typedef struct matrice_ matrice;

double dotprod_simple(double *, double *,int);
double norme_frobenius(int , int ,double *);
double norme(double *,int );
double *lire_matrice(int, double, double);
void affiche_matrice(double *, int, int);

matrice *lire_vector(int);
matrice *lire_vector_fixe(char *fichier);
matrice *lire_matrice_fixe(char *fichier);


void AfficheMatrice(matrice *matrix);
void desaloc_mat(matrice *matrix);
void desaloc_vec(matrice *vec);
void AfficheVecteur(matrice* vec);


#endif 
