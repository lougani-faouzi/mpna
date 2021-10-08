#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrice.h"


void desaloc_mat(matrice *mat)
{
  free(mat->valeur);
  free(mat);
}

void AfficheMatrice(matrice *matrix)
{
  
    for (int i = 0; i < matrix->nb_lignes; i++)
    {
      for (int j = 0; j < matrix->nb_colonnes; j++)
      {
              printf("%f ", matrix->valeur[i*matrix->nb_lignes + j]);
      }
      printf("\n");
    }
      printf("\n");
}

matrice *lire_matrice_fixe(char *fichier)
{
  int i=0,n=0;
  char temp[256];
  int lecture=0;
  int taille;
  
  FILE *f = fopen(fichier, "r");
  matrice *mat = aligned_alloc(64,sizeof(matrice));
  
  while (fgets(temp,256,f))
  {
   if ((lecture==0)&&(temp[0]!='%'))
   {       
    sscanf(temp,"%d %d %d\n",&(mat->nb_lignes),&(mat->nb_colonnes),&n);             
    taille= mat->nb_lignes * mat->nb_colonnes;
    mat->valeur = aligned_alloc(64,taille*sizeof(mat));
    while(i<taille)
    {
    mat->valeur[i] = 0;
    i++;
    lecture = 1;
    }
              
   }
   else  if ((lecture==1)&&(temp[0] !='%'))
   {
    double val;
    int ligne;
    int colonne;
    sscanf(temp, "%d %d %lf\n", &ligne, &colonne,&val);
    int ecart=ligne-1;
    mat->valeur[ecart*mat->nb_lignes+ecart]=val;
   }
  }
  fclose(f);
  return mat;
}







