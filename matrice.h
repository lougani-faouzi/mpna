#ifndef _MATRICE_H_
#define _MATRICE_H_

struct matrice_
{
  double *valeur;
  int nb_lignes;
  int nb_colonnes;
  
};
typedef struct matrice_ matrice;

matrice *lire_matrice_fixe(char *fichier);
void AfficheMatrice(matrice *matrix);
void desaloc_mat(matrice *matrix);

#endif 
