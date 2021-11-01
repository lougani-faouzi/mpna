#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrice.h"


double norme(matrice* x,int taille)
{

 double a=dotprod_simple(x,x,taille);
 return sqrt(a);

}




double dotprod_simple(matrice* x, matrice* y,int taille)
{
  double s=0.0;
  
  for (int i=0; i<taille; i++)
  {
    s= s+x->valeur[i]*y->valeur[i];
  }
  
  return s;
}

matrice *lire_vector_fixe(char *fichier)
{
  char buffer[256];
  int  lecture=0;
  FILE *f = fopen(fichier, "r");
  matrice *vec = aligned_alloc(64,sizeof(matrice));
  
  while (fgets(buffer,256,f))
  {
      
  
  if ((lecture==1)&&(buffer[0]!='%'))
  {
   int taille;
   sscanf(buffer,"%d %d %d\n",&(vec->nb_lignes),&(vec->nb_colonnes),&taille);  
   if (vec->nb_colonnes == 1)
   {
     for(int i=0; i<vec->nb_lignes; i++)
     {     
            double v = 0.0;
            sscanf(buffer, "%lf\n", &v);
            vec->valeur[i]=v;
            lecture=1;
     }  
    
   }

  }
  
 }
  fclose(f);
  return vec;
}



matrice *lire_matrice(int n, double x, double y) {

  matrice *mat = aligned_alloc(64,sizeof(matrice));
  mat->nb_lignes=n;
  mat->nb_colonnes=n;
  mat->valeur= (double *)aligned_alloc(64,sizeof(double)*(mat->nb_lignes*mat->nb_colonnes));
  
  int j=n;
  for(int i = 1; i < n - 1; i++)
  {
	mat->valeur[j+i]=x;
  	mat->valeur[j+i+1]=y;
  	mat->valeur[j+i-1]=y;
  	j=j+n;
  }
  mat->valeur[0]=x;
  mat->valeur[n*n-1]=x;
  mat->valeur[1]=y;
  mat->valeur[n*n-2]=y;
  
  return mat;
}


matrice *lire_vector(int n) {
  // a renvoir car return a vec avec 1 comme val

  matrice *vec = aligned_alloc(64,sizeof(matrice));
  vec->nb_lignes=n;
  vec->nb_colonnes=1;
  vec->valeur= (double *)aligned_alloc(64,sizeof(double)*(vec->nb_lignes*vec->nb_colonnes));
  
  
  for (int i = 0; i < n; i++) {
    vec->valeur[i] = 1.0;
  }
 
  return vec;

}

void AfficheVecteur(matrice* vec)
{
	for (int i=0; i<vec->nb_lignes ; i++)
	printf("%lf\n",vec->valeur[i]);

}


void desaloc_mat(matrice *mat)
{
  free(mat->valeur);
  free(mat);
}

void desaloc_vec(matrice *vec)
{
  free(vec->valeur);
  free(vec);
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











