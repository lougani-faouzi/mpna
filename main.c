#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <lapacke.h>
#include <time.h>
#include "matrice.h"

int main()
{         
      
         
          printf("\n ***TP01 ***** \n");
          printf("\nlecture matrice normale\n" );
          matrice *mat =lire_matrice(5, 2, 1);
          AfficheMatrice(mat);
          //desaloc_vec(mat);
          
          printf("\nlecture vecteur\n" );
          matrice *vec =lire_vector(4);
          AfficheVecteur(vec);
          //desaloc_mat(vec);  
          
          //simple dot prod 
          printf("\n simple dot prod de vecteur\n");
          printf("%lf",dotprod_simple(vec,vec,4));
          
          //norme d un vecteur
          printf("\n norme d un vecteur\n");
          printf("%lf",norme(vec,4));
      	  
      	  //norme frobenieus d'une matrice
      	  printf("\n norme frobenieus\n");
      	  printf("%lf",norme_frobenius(5,5,mat));
      	  
      	  printf("\n\n");
      	  
      	   printf("lecture et affchage d'une matrice format mtx  \n");
          matrice *mtx=lire_matrice_fixe("cage3.mtx");
          AfficheMatrice(mtx);
         
      	  printf("\n ***TP01 ***** \n");
      	  
      	 
      	  printf("\n ***TP02 arnoldi ***** \n");
      	  
      	  int n = 4, m = 3;
	  clock_t before, after;
	  
	  //allocation 
	  double **A = (double**) malloc(sizeof(double*)*n);
	  for (int i = 0; i < n; ++i)
	  {
		A[i] = (double*) malloc(sizeof(double)*n);
	  }
	  
	  //allocation 
	  double  **H = (double**) malloc(sizeof(double*)*n);
	  for (int i = 0; i < n; ++i)
	  {
		H[i] = (double*) malloc(sizeof(double)*n);
	  }
	  
	  double  *v = malloc(sizeof(double)*m);
	  double  **V = (double**) malloc(sizeof(double*)*m);
	  for (int i = 0; i < m; ++i)
	  {
		V[i] = (double*) malloc(sizeof(double)*n);
		v[i] = i+1;
	  }
	  
          printf("La matrice A :\n");
          matrice_carre(A, n);
          affiche_matrice_carree(A, n);
          printf("\n");
          printf("Le vecteur v :\n");
          for(int i=0;i<m;i++)
          {
            printf("%lf\t",v[i]); 
          }
          printf("\n\n");
	  
	  // appel a arnoldi+mesure perf
	  before = clock();
	  arnoldi(A, v, n, m, H, V);	
	  after = clock();
	  // fin appel a arnoldi+mesure perf
         
	  printf("Si n = %d et m = %d\n",n, m);
	  printf("\n");
	  printf("La matrice resultante H :\n");
	  affiche_matrice_carree(H, m);
	  printf("\n\n");
	  printf("La matrice des vecteurs propres :\n");
	  affiche_matrice_carree(V, m);
	  printf("\n");
	  fprintf(stderr, "le temps d'execution est = %ld ms\n", after-before);
	   	 
      
      	  printf("\n ***TP02 arnoldi ***** \n");
      	  
         
         printf("\n ***TP03 gramshmid ***** \n");
         
         clock_t before_cgs, after_cgs;        
         double m1[] = {1, 0, 1, 1, 1, 1, -1, -1, 0};//3*3
         //double m2[] = {1,0,-1,0};//2*2
         //double m3[] = {1};//1*1
         
         before_cgs = clock();
         double *cgs = Classical_gs(3, m1);
         after_cgs = clock();
         
         printf("La matrice en entree m1 :\n");
         affiche_matrice_ligne(3, 3, m1);
         printf("\n");
         printf("La matrice resultante en classical gs :\n");
         affiche_matrice_ligne(3, 3, cgs);  
         
         printf("\n");
	 fprintf(stderr, "le temps d'execution classical gs est = %ld ms\n", after_cgs-before_cgs);
	 
	 printf("\n");
	 clock_t before_mgs, after_mgs;        
     
         before_mgs = clock();
         double *mgs = Modified_gs(3, m1);
         after_mgs = clock();
         
         printf("La matrice resultante en Modified gs :\n");
         affiche_matrice_ligne(3, 3, mgs);  
         
         printf("\n");
	 fprintf(stderr, "le temps d'execution Modified gs est = %ld ms\n", after_mgs-before_mgs);
	
       
         
       
  return 0;
}
