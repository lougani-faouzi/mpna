#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lapacke.h>
#include "matrice.h"

void blas2_dgemv(char trans, int m, int n, double a, double *A, int lda, double *x,double b, double *y)
{

  int taille_x,taille_y;
  
  if (trans == 'N' )
  {
    taille_x = n;
    taille_y = m;
    
    int ky=0;
    int i=0,j=0;
    
    while(i<taille_x)
    {
    	while(j<taille_y)
    	{
    		y[j] = y[j]+ a * A[ky + j] * x[i];
    		j++;
    	}
    	i++;
    	ky=ky+lda;
    }
    
  }else {
  
    // y = a*A**T*x + y
    taille_x = m;
    taille_y = n;
    int kx = 0;
    int i=0,j=0,k=0;
    while(i<taille_x)
    {
    	while(j<taille_y)
    	{
    	  y[i]= y[i]+ a * A[kx + j] * x[j];
    	  j++;
    	}
    	  i++;
          kx=kx+lda;
          
    }	
  }

  // y = b*y
    if (b == 0)
    { 
       while(k<taille_y)
       {
        y[k] = 0;
        k++;
       }
    } 
    else
    { 
      k=0;
      while(k<taille_y)
      {
      y[k]=b*y[k];
      k++;
      }
      
    } 
   
  
    if (a == 0)
    return;

}
/*
  A la matrice 
  b le vecteur initial
  n la taille de la matrice A
  m la taille du sous espace de projection
  H la matrice hessenberg 
  V la matrice unitaire 

*/

void arnoldi(int n, int m, double *A, double *b, double *H, double *V) 
{
    // on copie le vecteur b dans V
    for(int i=0; i<n; i++)
    {
      V[i]=b[i];  
    }
    
    // 
    double e=1.0/norme(V,n);
    
    for(int i=0; i<n; i++)
    {
      V[i]=e*V[i];
    }
    
    int k= n;
    int h = 0;
    int j=1;
    
    while (j<m)
    {
      //dgemv_('n', n, n, 1, A, n, &V[k-n],0,&V[k]);
      
      for(int i=0; i<n; i++)
      {
      	
      	H[h+i] = dotprod_simple(&V[k],&V[i*n],n);
      	for (int r=0; r<n; r++)
      	{
      		V[k]=-(H[h+ i])*V[i*n]+V[k];
      	}
 
      }
      H[h+j] = norme(&V[k],n);
      for (int t=0; t<n; t++)
      {
              V[k]= (1.0/H[h+j]) * V[k];
      }

      k=k+n;
      h=h+m+1;
      
      j++;
    }
   

}


double norme_frobenius(int nb_lig, int nb_col,double *mat)
{

 double temp = 0.0;
 double norm = 0.0;

  for (int i = 0; i < nb_lig * nb_col; i++)
  {
	temp=temp + mat[i] * mat[i];
  }
   
   norm=sqrt(temp);
   
   return norm;
   
}


double norme(double *x,int taille)
{

 double a=dotprod_simple(x,x,taille);
 return sqrt(a);

}




double dotprod_simple(double *x, double *y,int taille)
{
  double s=0.0;
  
  for (int i=0; i<taille; i++)
  {
    s= s+x[i]*y[i];
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

/*

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

*/
/*
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

*/

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











