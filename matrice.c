#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lapacke.h>
#include "matrice.h"

void affiche_matrice_ligne(int n, int m, double *mat) {
  int temp;
  for (int i = 0; i < n; i++) {
    temp = 0;
    for (int j = 0; j < m; j++) {
      printf("%lf ", mat[temp+i]);
      temp=temp+n;
    }
    printf("\n");
  }
}



void scal_fois_vect(int n, double scal, double *vect) {
  for (int i = 0; i < n; i++) {
    vect[i]= scal * vect[i];
  }
}

void copier_vect_vect(int n, double *vect_a, double *vect_b) {
  for (int i = 0; i < n; i++) {
    vect_b[i]=vect_a[i];
  }
}

void scal_fois_vect_plus_vect(int n, double scal, double *vect_a, double *vect_b) {
  for (int i = 0; i < n; i++) {
    vect_b[i] = scal * vect_a[i] + vect_b[i];
  }
}

double somme_mul_vect_vect(int n, double *vect_a, double *vect_b) {
  
  double somme = 0.0;
  for (int i = 0; i < n; i++) {
    somme = somme + vect_a[i] * vect_b[i];
  }
  return somme;
}


double *Modified_gs(int n, double *A) {
  
  int cpt = 0;
  double *coef,*vect_w;
  coef= malloc(sizeof(double)*n);
  vect_w= malloc(sizeof(double)*n*n);
  for (int k = 0; k < n; k++) {
    
    // ici on calcul w = ak dans la formule du cours 
    copier_vect_vect(n,&A[cpt],&vect_w[cpt]);
    
    // for j=1:k-1, rjk= qtjw ,w = w −rjkq end 
    for (int j = 0; j < k; j++) {
      coef[j] = somme_mul_vect_vect(n,&vect_w[cpt],&vect_w[j*n]);
      scal_fois_vect_plus_vect(n,-coef[j],&vect_w[j * n], &vect_w[cpt]);
    }

    // ici on normalise notre vecteur 
    double val = (double)(1/norme(&vect_w[cpt],n));
    scal_fois_vect(n,val,&vect_w[cpt]);
    
    cpt=cpt+n;
  }

  return vect_w;
}

double *Classical_gs(int n, double *A) {

  int cpt = 0;
  double *coef,*vect_w;
  coef= malloc(sizeof(double)*n);
  vect_w= malloc(sizeof(double)*n*n);
  
  for (int k = 0; k < n; k++) {
  
    // ici on calcul w = ak dans la formule du cours 
    copier_vect_vect(n,&A[cpt],&vect_w[cpt]);

    // for j = 1:k-1, rjk= qtjw end
    for (int j = 0; j < k; j++)
      coef[j] = somme_mul_vect_vect(n,&vect_w[cpt],&vect_w[j * n]);

    // for j = 1:k-1,  w = w −rjkqj end 
    for (int j = 0; j < k; j++)
      scal_fois_vect_plus_vect(n,-coef[j],&vect_w[j * n],&vect_w[cpt]);

    // ici on normalise notre vecteur 
    double val = (double)(1/norme(&vect_w[cpt],n));
    scal_fois_vect(n,val,&vect_w[cpt]);
    
    cpt=cpt+n;
  }
    
  return vect_w;
}



void matrice_carre(double **A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = i*j+1;
		}
	}
}

double scal(double **V, int j, int i, int m)
{
	double S = 0;
	for (int k = 0; k < m; ++k)
	{
		S = S + V[j][k]*V[i][k]; 
	}
	return S;
}




void dotprod_2(double **A, double **V, int j, int n, int m)
{
	
	for (int i = 0; i < n; ++i)
	{
		for (int k = 0; k < m; ++k)
		{
			V[j+1][k] = V[j+1][k] + A[i][k] * V[k][j+1];
		}
	}

}

/*
  A la matrice 
  H la matrice hessenberg  
  v le vecteur initial
  n la taille de la matrice A
  m la taille du sous espace de projection
  V la matrice unitaire 

*/

void arnoldi(double **A, double *v, int n, int m, double **H, double **V)
{

	// Initialisation de V1
	double nb = norme(v, m);
	for (int i = 0; i < m; ++i)
	{
		V[0][i] = v[i] / nb;
	}


	// boucle de calcul global
	for (int j = 0; j < m-1; ++j)
	{
		dotprod_2(A, V, j, n, m);
		for (int i = 0; i < j; ++i)
		{
			H[i][j] = scal(V, j+1, i, m);
			//ici on doit calculer calcul de Vj+1
			for (int k = 0; k < m; ++k)
			{
				V[j+1][k] = V[j+1][k] - V[i][k]*H[i][j];
			}
		}

		H[j+1][j] = norme(V[j+1], m);
		if (H[j+1][j] == 0)
		{
			return ;
		}
		//ici on doit calculer de H[j+1][j]
		for (int k = 0; k < m; ++k)
		{
			V[j+1][k] = V[j+1][k]/H[j+1][j];
		}
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

void affiche_matrice_carree(double **A, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%lf\t", A[i][j]);
		}
		printf("\n");
	}
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
              printf("%lf ", matrix->valeur[i*matrix->nb_lignes + j]);
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











