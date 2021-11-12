#ifndef _MATRICE_H_
#define _MATRICE_H_

struct matrice_
{
  double *valeur;
  int nb_lignes;
  int nb_colonnes;
  
};
typedef struct matrice_ matrice;


void affiche_matrice_ligne(int , int , double *);
void scal_fois_vect(int, double, double *);
void copier_vect_vect(int , double *, double *);
void scal_fois_vect_plus_vect(int , double , double *, double *);
double somme_mul_vect_vect(int , double *, double *);

double *Classical_gs(int, double *);
double *Modified_gs(int , double *);

void affiche_matrice_carree(double **, int );
double scal(double **, int , int , int );
void matrice_carre(double **, int );
void dotprod_2(double **, double **, int , int , int );
void arnoldi(double **A, double *v, int n, int m, double **H, double **V);


double dotprod_simple(double *, double *,int);
double norme_frobenius(int , int ,double *);
double norme(double *,int );
matrice *lire_matrice(int, double, double);
void affiche_matrice(double *, int, int);

matrice *lire_vector(int);
matrice *lire_vector_fixe(char *fichier);
matrice *lire_matrice_fixe(char *fichier);


void AfficheMatrice(matrice *matrix);
void desaloc_mat(matrice *matrix);
void desaloc_vec(matrice *vec);
void AfficheVecteur(matrice* vec);


#endif 
