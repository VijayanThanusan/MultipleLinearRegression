#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include <ctypes/ctypes.h>

int LIGNE,COLONNE;
int LIGNEY,COLONNEY;

void affichermatrice(double ** matrice,int lignes, int colonnes)
{
  int i,j;
  printf("\n");
  for(i = 0; i < lignes; i++)
  {
    for(j = 0; j < colonnes; j++)
    {
      printf("%f ", matrice[i][j]);
    }
    printf("\n");
  }
}

double ** creermatrice (int lignes, int colonnes,double valeur)
{
  int i,j;
  double** matrice = malloc (lignes * sizeof(double *));
  for (i = 0; i < lignes; i++)
  {
    matrice[i]= malloc (colonnes * sizeof(double));
  }
  for (i = 0; i < lignes ;i++)
  {
    for(j = 0; j < colonnes ;j++)
    {
      matrice[i][j]=valeur;
    }
  }
  return matrice;
}


void desallocmatrice(double ** matrice,int lignes)
{
  int i;
  for (i = 0; i < lignes; i++)
  {
    free((double *)matrice[i]);
  }
}

double ** transposematrice(double ** matrice, int lignes, int colonnes)
{
  int i, j;
  double ** transpose = creermatrice(colonnes,lignes,0);
  for(i = 0; i < lignes; i++)
  {
    for(j = 0; j < colonnes; j++)
    {
      transpose[j][i] = matrice[i][j];
    }
  }
  return transpose;
}

double ** multipliermatrices(double **matrice1, int ligneM1, int colonneM1, double **matrice2, int ligneM2, int colonneM2)
{

    int i, j, jtmp;
    double somme;
    double ** resultat = creermatrice ( ligneM1, colonneM2 , 0);

    for(i = 0; i < ligneM1; i++)
    {
      for( j = 0 ; j < colonneM2; j++)
      {
        somme = 0;
        for( jtmp = 0; jtmp < colonneM1; jtmp++)
        {
          somme += matrice1[i][jtmp] * matrice2[jtmp][j];
        }
        resultat[i][j] = somme;
      }
    }

    return resultat;
}

double **copiermatrice(double **matrice, int ligneM, int colonneM)
{
  int i,j;
  double **matricecopier = creermatrice(ligneM,colonneM,0);
  for(i = 0; i < ligneM; i++)
  {
    for(j = 0; j < colonneM; j++)
    {
      matricecopier[i][j] = matrice[i][j];
    }
  }
  return matricecopier;
}

double  determinant(double **matrix, int tailleM )
{
  double ** matrix1= creermatrice(tailleM-1,tailleM-1,0);
  int  clean,h,i,j,matrix1I ,matrix1J;
  double somme, res = 0;
  if(tailleM == 2)
  {
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];

  }

  else
  {
    for( h = 0 ; h < tailleM;h++)
    {


    for(matrix1I = 0, i = 0; i < tailleM; )
    {
      if(i != 0)
      {
        for(matrix1J = 0, j = 0; j < tailleM ; )
        {
          if(j != h)
          {
            matrix1[matrix1I][matrix1J] = matrix[i][j];
            j++;
            matrix1J++;
          }
          else j++;
        }
        i++;
        matrix1I++;
      }
      else i++;
    }
    /*
    printf("\n\n%f\n",matrix[0][h]);
    affichermatrice(matrix1,tailleM-1,tailleM-1);
    printf("");
    */
    if(h % 2 == 0)
    {
     res += matrix[0][h] *  determinant(matrix1, tailleM-1);
    }
    else
    {
      res = res + (-1 * matrix[0][h]) * determinant(matrix1,tailleM-1);
    }

   }
  return res;
  }

 }



double ** cofacteur(double ** matrix, int tailleM)
{
  int ligne,colonne;
  double ** matrix1= creermatrice(tailleM-1,tailleM-1,0);
  double ** resultat = creermatrice(tailleM,tailleM,0);
  int i,j,matrix1I,matrix1J;

  for( ligne = 0; ligne < tailleM; ligne++)
  {
    for(colonne = 0; colonne < tailleM ; colonne ++)
    {
      for(matrix1I = 0, i = 0; i < tailleM; )
      {
        if(i != ligne)
        {
          for(matrix1J = 0, j = 0; j < tailleM ; )
          {
            if(j != colonne)
            {
              matrix1[matrix1I][matrix1J] = matrix[i][j];
              j++;
              matrix1J++;
            }
            else j++;
          }
          i++;
          matrix1I++;
        }
        else i++;

      }
      if(((ligne %2 == 0) && (colonne %2 == 0)) || ((ligne %2 != 0) && (colonne %2 != 0)) )
      resultat[ligne][colonne] = determinant(matrix1,tailleM-1);
      else
      {
      resultat[ligne][colonne] = -1 * determinant(matrix1,tailleM-1);
      }
   }
 }
  return resultat;
}

double ** inverse(double ** matrice, int tailleM)
{
  printf("aaaaaaaa");
  double ** inv = creermatrice(tailleM,tailleM,0);
  double **res;

  double ** cof = cofacteur(matrice, tailleM);
  double det = determinant(matrice, tailleM);
  int i, j;

  for(i = 0; i< 5; i++)
  {
    for(j = 0; j < 5; j++)
    {
      inv[i][j] = cof[i][j]/det;
    }
  }
  return inv;
}


double ** lireunfichier(char *nomfichiertxt)
{
   FILE *fichier;
   double **matricelu;
   int nombredeligne;
   int nombredecolonne;
   int i,j;
   fichier = fopen(nomfichiertxt,"r");

   if( fichier == NULL )
   {
      perror("Erreur de la lecture du fichier\n");
      exit(EXIT_FAILURE);
   }

   fscanf(fichier,"%d %d" ,&nombredeligne,&nombredecolonne);
   matricelu = creermatrice(nombredeligne,nombredecolonne,0);
   for(i = 0; i < nombredeligne; i++)
   {
     for(j = 0; j < nombredecolonne; j++)
     {
       fscanf(fichier,"%lf", &matricelu[i][j] );
     }
   }


  fclose(fichier);
   LIGNE = nombredeligne;
   COLONNE = nombredecolonne;
   return matricelu;
}

double ** YouX(double ** matrice, int ligneM , int colonneM ,int test)  // test = 0 == Y, test = 1 == X
{
  int i,j;
  double** matrixXouY;
  if( test == 0)
  {
    matrixXouY= creermatrice(ligneM,1,0);
    for(i = 0; i < ligneM ;i++)
      {
        matrixXouY[i][0] = matrice[i][0];
      }
    LIGNEY = ligneM;
    COLONNEY = 1;
  }
  else
  {
    matrixXouY = creermatrice(ligneM,colonneM,0);
    for(i = 0; i < ligneM; i++)
    {
      for(j = 0; j < colonneM; j++)
      {
        if(j == 0)
        {
          matrixXouY[i][j] = 1;
        }
        else matrixXouY[i][j]= matrice[i][j];
      }
    }
  }
  return matrixXouY;
}

void programme(char * data) {

  int i,j;
  double **matrix = lireunfichier(data);
  double ** Y = YouX(matrix,LIGNE,COLONNE,0);
  double ** X = YouX(matrix,LIGNE,COLONNE,1);
  double ** transposedeX;
  double ** transMULx;
  double ** cofac; //cofac
  double determinanttransMULx;
  double ** tmpinv,**inverseM; //inverse
  double ** transMULy;
  double ** invMULtmy;

  transposedeX = transposematrice(X, LIGNE,COLONNE);

  transMULx = multipliermatrices(transposedeX,COLONNE,LIGNE,X,LIGNE,COLONNE);

  cofac = cofacteur(transMULx,COLONNE);
  determinanttransMULx = determinant(transMULx,COLONNE);

   tmpinv = creermatrice(COLONNE,COLONNE,0);
  for(i = 0; i< COLONNE; i++)
  {
    for(j = 0; j < COLONNE; j++)
    {
      tmpinv[i][j] = cofac[i][j]/determinanttransMULx;
    }
  }
  inverseM = transposematrice(tmpinv,COLONNE,COLONNE);
  transMULy = multipliermatrices(transposedeX,COLONNE,LIGNE,Y,LIGNE,COLONNEY);
  invMULtmy = multipliermatrices(inverseM,COLONNE,COLONNE,transMULy,COLONNE,COLONNE);
  affichermatrice(invMULtmy,COLONNE,COLONNEY);
  //printf("\n\n%d  %d",LIGNE,COLONNE);
}

int main()
{
  clock_t a = clock();

   programme("data.txt");

   clock_t b = clock();

   printf("temps: %f seconds\n", (double)(b - a) / CLOCKS_PER_SEC);

   return 0;
}
