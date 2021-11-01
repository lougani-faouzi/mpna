#include <stdio.h>
#include <math.h>
#include "matrice.h"

int main()
{
          matrice *mat =lire_matrice(5, 2, 1);
          AfficheMatrice(mat);
          //desaloc_vec(mat);
          
          printf("\n");
          matrice *vec =lire_vector(4);
          AfficheVecteur(vec);
          //desaloc_mat(vec);  
          
          //simple dot prod 
          printf("\n");
          printf("%lf",dotprod_simple(vec,vec,4));
          
          //norme d un vecteur
          printf("\n");
          printf("%lf",norme(vec,4));
      	  
      	  // AfficheVecteur(vec);
                
       //   case 3:
          
          
       //   break;

       //  default : printf("\n neant");

       // } 
        
        //double dotp=dotprod_simple(vec,vec,int taille);
        
       
  return 0;
}
