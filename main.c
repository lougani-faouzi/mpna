#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrice.h"

int main()
{        /*
          printf("\nlecture matrice\n" );
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
      	  printf("%lf",norme_frobenius(mat));
      	  */
      	  
      	  // arnoldi 
      	  
      	  printf("\n arnoldi \n");
      	  double A[] = {1, 0, 1, 1, 1, 1, -1, -1, 0};
      	  double *H = malloc(sizeof(double) * 12);
          double *V = malloc(sizeof(double) * 12);
          double b[] = {0, 1, 1};
          arnoldi(3, 3, A, b, H, V);
      	  printf("\n arnoldi \n");
      	  
      	  // AfficheVecteur(vec);
                
       //   case 3:
          
          
       //   break;

       //  default : printf("\n neant");

       // } 
        
        //double dotp=dotprod_simple(vec,vec,int taille);
        
       
  return 0;
}
