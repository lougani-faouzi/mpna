#include <stdio.h>
#include <math.h>
#include "matrice.h"

int main(int argc, char **argv)
{
        matrice *matrix = lire_matrice_fixe(argv[1]);
        switch (argc)
	{
          case 2: 
      		 AfficheMatrice(matrix);
      		 desaloc_mat(matrix); 
          break;

         default : printf("\n neant");

        } 
        
       
  return 0;
}
