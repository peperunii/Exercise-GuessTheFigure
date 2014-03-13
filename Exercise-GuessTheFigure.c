#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
void izchertavane(int *arr_coord, int *figura_coord, int FigureOrLine);
int IsParallelogram(int *arr_coord, int *figura_type, int *figura_coord, int *NumberOfRecognizedFigures, int *figura_types);

int NUMBER_OF_INPUT_POINTS;

int main()
{
        //1 2, 2 3, 4 7, 7 11, 0 -3, 0 -5, -5 4, -5 8, 4 6, 1 11, -9 6, -8 4, -1 -4, 12 9, 3 -2  -Lying on a same line
        int i, j, k, z, t,check;
        int figura_type = 0;
        int shift_x = 0, shift_y = 0;
        int LyingOnSameLine = 0, Parallelogram = 0;
        float otnoshenie = 0, Ratio_abs = 0;
        float Ratio_3rdCoord = 0;
        int *coord;
        int *input_coord;
        int FigureNumber = 0;
        int figura_coord[100];
        int figura_types[25];
        int fig_coord[4];
        char unUsedString[255];
        int FigureOrLine = 0;
        int NumberOfRecognizedFigures = 0;

        printf("Enter Number of points: ");
        scanf("%d",&NUMBER_OF_INPUT_POINTS);

        input_coord = (int *)malloc(NUMBER_OF_INPUT_POINTS * sizeof(int));
        coord		= (int *)malloc(NUMBER_OF_INPUT_POINTS * sizeof(int));
        for (i = 0; i < 4; i++) figura_coord[i] = -1;
        for (i = 0; i < 5; i++) figura_types[i] = 0;
        /* Check input data */
        do{
                t = 0;
                check = 0;
                system("cls");
                fflush(stdin);
				printf("Enter coordinates for %d points in the following format:\n", NUMBER_OF_INPUT_POINTS);
                for (i = 0; i < NUMBER_OF_INPUT_POINTS; i++)
                {
                        printf(" x y");
                        if (i != NUMBER_OF_INPUT_POINTS - 1) printf(",");
                }
                printf("\n");
                for (i = 0; i < NUMBER_OF_INPUT_POINTS; i++)
                {
                        check = scanf_s("%d", &input_coord[2 * i]);
                        if (check != 0) t++;
                        check = scanf_s("%d", &input_coord[2 * i + 1]);
                        if (check != 0) t++;
                        if (i != NUMBER_OF_INPUT_POINTS - 1) check = scanf_s("%s", unUsedString);
                }
                
        } while (t != (2 * NUMBER_OF_INPUT_POINTS));

        // Izmestvane na coordinatnata sistema do pyrvi kvadrant - Samo za izchislenie.
        /*
                        |							|		
                        |							|		
                        |							|		
                      *	|   *						|	  *	      *
                ________|_________________  ---->   | 
                      *	|							|	  *	
                *		|							| *		
                        |                  			|_______________________		                  
        
        
        */
        for (i = 0; i < NUMBER_OF_INPUT_POINTS; i++)
        {
                if (input_coord[2 * i] < 1)
                {
                        //shift X
                        if ((shift_x + input_coord[2 * i]) < 1) shift_x = 1 - input_coord[2 * i];
                }
                if (input_coord[2 * i + 1] < 1)
                {
                        //shift Y
                        if ((shift_y + input_coord[2 * i + 1]) < 1) shift_y = 1 - input_coord[2 * i + 1];
                }
        }
        for (i = 0; i < NUMBER_OF_INPUT_POINTS; i++)
        {
                coord[2 * i] = input_coord[2 * i] + shift_x;
                coord[2 * i + 1] = input_coord[2 * i + 1] + shift_y;
        }

        // Presmqtane na teorema na Tales za vsqka tochka po zadadeni drugi dve
        /*                   Z
        y3					+								|  A, B - zadadeni tochki obrazuvashti prava ( i, j)
        |			B		.								|  +  Z tochka koqto shte byde proverena dali se namira na pravata AB
        y2		    *		.								|
        |           .		.								|  Proverqva se otnoshenieto ((B_x - A_x)/ ( Z_x - A_x)) == ((B_y -A_y)/ (Z_y - A_y))
        |    A      .		.								|
        y1   * . . ...	.  ..								|
        |          		     								|
        |____X1_____x2______X3______________________________|
        */
        for (i = 0; i < NUMBER_OF_INPUT_POINTS; i++)
        {
                for (j = 0; j < NUMBER_OF_INPUT_POINTS; j++)
                {
                        if (j == i) continue;

                        if ((coord[2 * i + 1] - coord[2 * j + 1]) == 0) otnoshenie = 0;
                        else otnoshenie = (float)(coord[2 * i] - coord[2 * j]) / (coord[2 * i + 1] - coord[2 * j + 1]);
                        Ratio_abs = otnoshenie;

                        for (z = 0; z < NUMBER_OF_INPUT_POINTS; z++)
                        {
                                if (z == i || z == j) continue;

                                if ((coord[2 * i + 1] - coord[2 * z + 1]) == 0) Ratio_3rdCoord = 0;
                                else Ratio_3rdCoord = (float)(coord[2 * i] - coord[2 * z]) / (coord[2 * i + 1] - coord[2 * z + 1]);

                                if (((coord[2 * z] == coord[2 * i]) && (coord[2 * z] == coord[2 * j])) ||
                                        ((coord[2 * z + 1] == coord[2 * i + 1]) && (coord[2 * z + 1] == coord[2 * j + 1]))
                                        )
                                {
                                        LyingOnSameLine = 1;
                                        break;
                                }
                                if (Ratio_3rdCoord == Ratio_abs && Ratio_3rdCoord != 0)
                                {
                                        LyingOnSameLine = 1;
                                        break;
                                }
                        }
                        if (LyingOnSameLine) break;
                }
                if (LyingOnSameLine) break;
        }
        if (LyingOnSameLine)
        {
                printf("There are at least 3 points lying on a same line.\n");
                printf("[%d, %d], [%d, %d], [%d,%d]\n", input_coord[2 * i], input_coord[2 * i + 1], input_coord[2 * j], input_coord[2 * j + 1], input_coord[2 * z], input_coord[2 * z + 1]);
                
                FigureOrLine = 1;
                
                figura_coord[0] = i;
                figura_coord[1] = j;
                figura_coord[2] = z;
        }
        else
        {
                printf("There aren't 3 point lying on a same line\n");
                // check if there 4 points are forming recognizable shape.
                Parallelogram = IsParallelogram(coord, &figura_type, figura_coord, &NumberOfRecognizedFigures, figura_types);

                  printf("There are %d figuri formed from the given points\n", NumberOfRecognizedFigures);
                  do{
PrintTUK:			      // Don't blame for using goto in a cycle. It is completely secure :)
                          fflush(stdin);
                          printf("If you want to visualize graphic and information for a specific figure, Enter its number ( 26 for Exit)\nFigure Number: ");
						  scanf_s("%d", &FigureNumber);
                          if(( ((FigureNumber < 0) || (FigureNumber > NumberOfRecognizedFigures-1))) && (FigureNumber != 26)) goto PrintTUK;
                          figura_type = figura_types[FigureNumber];
                          if(FigureNumber == 26) goto EX_IT;
                          switch (figura_type)
                          {
                                 case 0: printf("The points does not form a recognizable shape (square, rect. or trapets..\n");
					             	break;
					             case 1: printf("The figure is Square\n");
					             	break;
					             case 2: printf("The figure is Rectangle \n");
					             	break;
					             case 3: printf("The figure is Trapezoid\n");
					             	break;
					             case 4: printf("The figure is Parallelogram \n");
					             	break;
                          }
                          if (figura_type != 0)
                          {
                                  fig_coord[0] = figura_coord[4 * FigureNumber + 0];
                                  fig_coord[1] = figura_coord[4 * FigureNumber + 1];
                                  fig_coord[2] = figura_coord[4 * FigureNumber + 2];
                                  fig_coord[3] = figura_coord[4 * FigureNumber + 3];

                                  printf("The points forming the figure are: [%d, %d], [%d, %d], [%d, %d], [%d, %d]\n",
                                          input_coord[2 * fig_coord[0]], input_coord[2 * fig_coord[0] + 1],
                                          input_coord[2 * fig_coord[1]], input_coord[2 * fig_coord[1] + 1],
                                          input_coord[2 * fig_coord[2]], input_coord[2 * fig_coord[2] + 1],
                                          input_coord[2 * fig_coord[3]], input_coord[2 * fig_coord[3] + 1]
                                          );
                                  FigureOrLine = 2;

                                  izchertavane(input_coord, fig_coord, FigureOrLine);
                          }
                          if (FigureNumber == 26) break;
                  } while (1);
        }
		//Original array as parameter
        if (LyingOnSameLine || (FigureOrLine == 0)) izchertavane(input_coord, figura_coord, FigureOrLine);
EX_IT:
        _getch();
        return 0;
}

int IsParallelogram(int *arr_coord, int *figura_type, int *figura_coord, int *NumberOfRecognizedFigures, int *figura_types)
{
        int Parallelogram = 0;
        int flag_passed = 0;
        int i, j, k, z, m, ch1, ch2,ch3;
        int skipCheck = 0;
        int X_preneseno;
        float Ratio_1, Ratio_2;
        float new_Y;
        int MaxY_forCalcs = 0;
        int X_forCalcs = 0;
        int tyrsenY, tyrsenX;
        int maxY_side1 = 0, maxY_side2 = 0;
        int m_x, m_y, p_x, p_y;
        float diagonal_ij, diagonal_z;
        int Distance_z_x, Distance_z_y, Distance_ij_x, Distance_ij_y;
        int CountFigureTypes = 0;
        int check_coordinatesForDuplicates[50][4];
        int duplicate = 0;
        int MatchNumber = 0;
        int checkBits[4] = {0, 0, 0, 0 } ;
        for (i = 0; i < 25; i++)
        {
                for (j = 0; j < 4; j++)
                {
                        check_coordinatesForDuplicates[i][j] = 1000;
                }
        }

        for (i = 0; i < NUMBER_OF_INPUT_POINTS; i++)
        {
                for (j = 0; j < NUMBER_OF_INPUT_POINTS; j++)
                {
                        flag_passed = 0;
                        if (j == i) continue;
                        Distance_ij_x = abs(arr_coord[2 * i] - arr_coord[2 * j]);
                        Distance_ij_y = abs(arr_coord[2 * i + 1] - arr_coord[2 * j + 1]);
                        diagonal_ij = sqrt(pow((float)Distance_ij_x, 2) + pow((float)Distance_ij_y, 2));
                        for (z = 0; z < NUMBER_OF_INPUT_POINTS; z++)
                        {
                                if (z == i || z == j)continue;
                                
                                p_x = arr_coord[2 * z];
                                p_y = arr_coord[2 * z + 1];
                                
                                for (m = 0; m < NUMBER_OF_INPUT_POINTS; m++)
                                {
                                        if (m == i || m == j || m == z) continue;
                                        /*
                                        Check coordinates for duplicate entries
                                        */
                                        duplicate = 0;
                                        for (ch1 = 0; ch1 < *NumberOfRecognizedFigures; ch1++)
                                        {
                                                checkBits[0] = 0;
                                                checkBits[1] = 0;
                                                checkBits[2] = 0;
                                                checkBits[3] = 0;
                                                MatchNumber = 0;
                                                for (ch2 = 0; ch2 < 4; ch2++)
                                                {
                                                        if(check_coordinatesForDuplicates[ch1][ch2] == i) checkBits[0] = 1;
                                                        if(check_coordinatesForDuplicates[ch1][ch2] == j) checkBits[1] = 1;
                                                        if(check_coordinatesForDuplicates[ch1][ch2] == z) checkBits[2] = 1;
                                                        if(check_coordinatesForDuplicates[ch1][ch2] == m) checkBits[3] = 1;		
                                                }
                                                for(ch2 = 0; ch2 < 4; ch2++)
                                                {
                                                        if(checkBits[ch2] == 1) MatchNumber++;
                                                }
                                                if (MatchNumber == 4) duplicate = 1;
                                                if(duplicate) break;
                                        }
                                        if (duplicate) continue;
                                        Parallelogram = 0;
                                        m_x = arr_coord[2 * m];
                                        m_y = arr_coord[2 * m + 1];

                                        Distance_z_x = abs(m_x - p_x);
                                        Distance_z_y = abs(m_y - p_y);
                                        diagonal_z = sqrt(pow((float)Distance_z_x, 2) + pow((float)Distance_z_y, 2));
                                        if (Distance_ij_x / diagonal_ij == Distance_z_x / diagonal_z)
                                        {
                                                if ((arr_coord[2 * i] == arr_coord[2 * j]) && (m_x == p_x)) Parallelogram = 1;

                                                //Ako po-golqmoto Y e kym po-golqmoto X - vdigame flag maxY_side1. Povtarqme syshtoto i za vtorata strana i sravnqvame flagovete
                                                MaxY_forCalcs = MAX(arr_coord[2 * i + 1], arr_coord[2 * j + 1]);

                                                if (arr_coord[2 * i + 1] == arr_coord[2 * j + 1]) skipCheck = 1;

                                                if (!skipCheck)
                                                {
                                                        for (k = 0; k < NUMBER_OF_INPUT_POINTS; k++)
                                                        {
                                                                if (k != i && k != j) continue;
                                                                if ((arr_coord[2 * k + 1]) == MaxY_forCalcs)
                                                                        X_forCalcs = arr_coord[2 * k];
                                                        }
                                                        if (X_forCalcs == MAX(arr_coord[2 * i], arr_coord[2 * j])) maxY_side1 = 1;
                                                        else maxY_side1 = 0;

                                                        MaxY_forCalcs = MAX(m_y, p_y);
                                                        for (k = 0; k < NUMBER_OF_INPUT_POINTS; k++)
                                                        {
                                                                if (k == i || k == j) continue;
                                                                if ((arr_coord[2 * k + 1]) == MaxY_forCalcs) X_forCalcs = arr_coord[2 * k];
                                                        }
                                                        if (X_forCalcs == MAX(p_x, m_x)) maxY_side2 = 1;
                                                        else maxY_side2 = 0;
                                                }
                                                if (((maxY_side1 == maxY_side2) && !skipCheck) || skipCheck)
                                                {
                                                        Parallelogram = 1;
                                                        if (diagonal_ij == diagonal_z)
                                                        {
                                                                if (abs(MAX(p_x, m_x) - MAX(arr_coord[2 * i], arr_coord[2 * j])) == abs(MIN(p_x, m_x) - MIN(arr_coord[2 * i], arr_coord[2 * j])))
                                                                {
                                                                        tyrsenY = sqrt(pow((float)MAX(p_x, m_x) - MAX(arr_coord[2 * i], arr_coord[2 * j]), 2) + pow((float)MAX(p_y, m_y) - MAX(arr_coord[2 * i + 1], arr_coord[2 * j + 1]), 2));
                                                                        if (diagonal_ij == tyrsenY)
                                                                        {
                                                                                //kvadrat
                                                                                *figura_type = 1;
                                                                                figura_types[CountFigureTypes++] = 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                if (sqrt(pow((float)p_x - m_x, 2) + pow((float)p_y - m_y, 2))
                                                                                        ==
                                                                                        (sqrt(pow((float)MAX(p_y, m_y) - MAX(arr_coord[2 * j + 1], arr_coord[2 * i + 1]), 2) + pow((float)MAX(p_x, m_x) - MAX(arr_coord[2 * j], arr_coord[2 * i]), 2)
                                                                                        )))
                                                                                {
                                                                                        *figura_type = 1;
                                                                                        figura_types[CountFigureTypes++] = 1;
                                                                                }
                                                                                else
                                                                                {
                                                                                        X_forCalcs = MAX(arr_coord[2 * j], arr_coord[2 * i]);
                                                                                        for (k = 0; k < NUMBER_OF_INPUT_POINTS; k++)
                                                                                        {
                                                                                                if (k != i && k != j) continue;
                                                                                                if ((arr_coord[2 * k]) == X_forCalcs)
                                                                                                        MaxY_forCalcs = arr_coord[2 * k + 1];
                                                                                        }

                                                                                        tyrsenX = MIN(p_x, m_x);

                                                                                        for (k = 0; k < NUMBER_OF_INPUT_POINTS; k++)
                                                                                        {
                                                                                                if (k == i || k == j) continue;
                                                                                                if ((arr_coord[2 * k]) == tyrsenX)
                                                                                                        tyrsenY = arr_coord[2 * k + 1];
                                                                                        }
                                                                                        // Do tuk imame X,Y na 2te tochka v ediniqt diagonal na usporednika.
                                                                                        // Trqbva da namerim drugite 2 tochki, da se izchisli razstoqnieto mejdu tqh i ako sa ravni, to usporednika e pravoygylnik

                                                                                        diagonal_z = sqrt(pow((float)(MaxY_forCalcs - tyrsenY), 2) + pow((float)(X_forCalcs - tyrsenX), 2));

                                                                                        // syshtite izchisleniq i za 2riat diagonal
                                                                                        X_forCalcs = MIN(arr_coord[2 * j], arr_coord[2 * i]);
                                                                                        for (k = 0; k < NUMBER_OF_INPUT_POINTS; k++)
                                                                                        {
                                                                                                if (k != i && k != j) continue;
                                                                                                if ((arr_coord[2 * k]) == X_forCalcs)
                                                                                                        MaxY_forCalcs = arr_coord[2 * k + 1];
                                                                                        }

                                                                                        tyrsenX = MAX(p_x, m_x);
                                                                                        //MaxY_forCalcs = MaxY_forCalcs - tyrsenY;

                                                                                        for (k = 0; k < NUMBER_OF_INPUT_POINTS; k++)
                                                                                        {
                                                                                                if (k == i || k == j) continue;
                                                                                                if ((arr_coord[2 * k]) == tyrsenX)
                                                                                                        tyrsenY = arr_coord[2 * k + 1];
                                                                                        }
                                                                                        // Do tuk imame X,Y na 2te tochka v ediniqt diagonal na usporednika.
                                                                                        // Trqbva da namerim drugite 2 tochki, da se izchisli razstoqnieto mejdu tqh i ako sa ravni, to usporednika e pravoygylnik

                                                                                        diagonal_ij = sqrt(pow((float)(MaxY_forCalcs - tyrsenY), 2) + pow((float)(X_forCalcs - tyrsenX), 2));

                                                                                        if (diagonal_z == diagonal_ij)
                                                                                        {
                                                                                                *figura_type = 2;
                                                                                                figura_types[CountFigureTypes++] = 2;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                *figura_type = 4;
                                                                                                figura_types[CountFigureTypes++] = 4;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                                else                                
                                                                {
                                                                        *figura_type = 3;
                                                                        figura_types[CountFigureTypes++] = 3;
                                                                }
                                                        }
                                                        else
                                                        {
                                                                *figura_type = 3;
                                                                figura_types[CountFigureTypes++] = 3;
                                                        }
                                                        figura_coord[4 * (*NumberOfRecognizedFigures) + 0] = i;
                                                        figura_coord[4 * (*NumberOfRecognizedFigures) + 1] = j;
                                                        figura_coord[4 * (*NumberOfRecognizedFigures) + 2] = z;
                                                        figura_coord[4 * (*NumberOfRecognizedFigures) + 3] = m;
                                                        //return Parallelogram;
                                                        check_coordinatesForDuplicates[*NumberOfRecognizedFigures][0] = i;
                                                        check_coordinatesForDuplicates[*NumberOfRecognizedFigures][1] = j;
                                                        check_coordinatesForDuplicates[*NumberOfRecognizedFigures][2] = z;
                                                        check_coordinatesForDuplicates[*NumberOfRecognizedFigures][3] = m;
                                                        (*NumberOfRecognizedFigures)++;
                                                        if(*NumberOfRecognizedFigures == 25) return Parallelogram;
                                                }
                                        }
                                }
                        }
                }
        }
        return Parallelogram;
}



void izchertavane(int *arr_coords, int *figura_coord, int FigureOrLine)
{
        int i, j, z;
        int NumberOfDigits_forX_min = 1; //Minimum 1 digit is needed
        int NumberOfDigits_forX_max = 1;
        int NumberOfDigits_forY_min = 1;
        int NumberOfDigits_forY_max = 1;
        int CurrentNumberOfDigits = 1;
        int NumberForCalculations = 0;
        int min_x = 1000, max_x = 0, min_y = 1000, max_y = 0, min_Y_forPRint = 0;
        int printirai = 0;

        for (i = 0; i < NUMBER_OF_INPUT_POINTS - 1; i++)
        {
                min_x = MIN(MIN(arr_coords[2 * i], arr_coords[2 * i + 2]), min_x);
                max_x = MAX(MAX(arr_coords[2 * i], arr_coords[2 * i + 2]), max_x);
                min_y = MIN(MIN(arr_coords[2 * i + 1], arr_coords[2 * i + 3]), min_y);
                max_y = MAX(MAX(arr_coords[2 * i + 1], arr_coords[2 * i + 3]), max_y);
        }

        if (min_y - 10 > 0) min_Y_forPRint = min_y - 1;
        else if (min_y > 0) min_Y_forPRint = 0;
        if (min_y == 0) min_Y_forPRint = min_y;
        if (min_y < 0) min_Y_forPRint = min_y - 1;

        /* Opredelqne na max broi simvoli neobhodimi za vizualizirane na stoinostite po grafikata */
        //NumberOfDigits_forX_min
        NumberForCalculations = min_x - 1;
        for (; abs(NumberForCalculations) > 0;)
        {
                NumberForCalculations /= 10;
                if (NumberForCalculations) NumberOfDigits_forX_min++;
        }
        if (min_x < 0)NumberOfDigits_forX_min++;

        //NumberOfDigits_forX_max
        NumberForCalculations = max_x + 1;
        for (; abs(NumberForCalculations) > 0;)
        {
                NumberForCalculations /= 10;
                if (NumberForCalculations) NumberOfDigits_forX_max++;
        }
        if (max_x < 0)NumberOfDigits_forX_max++;

        //NumberOfDigits_forY_min
        NumberForCalculations = min_y - 1;
        for (; abs(NumberForCalculations) > 0;)
        {
                NumberForCalculations /= 10;
                if (NumberForCalculations) NumberOfDigits_forY_min++;
        }
        if (min_y < 0)NumberOfDigits_forY_min++;

        //NumberOfDigits_forY_max
        NumberForCalculations = max_y + 1;
        for (; abs(NumberForCalculations) > 0;)
        {
                NumberForCalculations /= 10;
                if (NumberForCalculations) NumberOfDigits_forY_max++;
        }
        if (max_y < 0)NumberOfDigits_forY_max++;
        /*  */

        for (z = 0; z < MAX(NumberOfDigits_forY_max, NumberOfDigits_forY_min) + 1; z++)
        {
                printf(" ");
        }

        for (j = min_x - 1; j <= max_x + 1; j++)
        {
                printf("-");
                for (z = 0; z < MAX(NumberOfDigits_forX_max, NumberOfDigits_forX_min) + 1; z++)
                {
                        printf(" ");
                }
        }
        printf("\n");

        for (i = max_y + 1; i >= min_Y_forPRint; i--)
        {
                CurrentNumberOfDigits = 1;
                NumberForCalculations = i;
                for (; abs(NumberForCalculations) > 0;)
                {
                        NumberForCalculations /= 10;
                        if (NumberForCalculations) CurrentNumberOfDigits++;
                }
                if (i < 0)CurrentNumberOfDigits++;

                for (z = 0; z < MAX(NumberOfDigits_forY_max, NumberOfDigits_forY_min) - CurrentNumberOfDigits; z++)
                {
                        printf(" ");
                }
                printf("%d", i);

                printf("|");
                for (j = min_x - 1; j <= max_x + 1; j++)
                {
                        printirai = 0;
                        for (z = 0; z < NUMBER_OF_INPUT_POINTS; z++)
                        {
                                if (arr_coords[2 * z] == j && arr_coords[2 * z + 1] == i)
                                {
                                        printirai = 1;
                                        break;
                                }
                        }
                        if (printirai)
                        {
                                if (figura_coord[0] != -1)
                                {
                                        if (FigureOrLine == 2)
                                        {
                                                if ((arr_coords[2 * figura_coord[0]] == j && arr_coords[2 * figura_coord[0] + 1] == i) ||
                                                        (arr_coords[2 * figura_coord[1]] == j && arr_coords[2 * figura_coord[1] + 1] == i) ||
                                                        (arr_coords[2 * figura_coord[2]] == j && arr_coords[2 * figura_coord[2] + 1] == i) ||
                                                        (arr_coords[2 * figura_coord[3]] == j && arr_coords[2 * figura_coord[3] + 1] == i))
                                                        printf("*");

                                                else printf(".");
                                        }
                                        if (FigureOrLine == 1)
                                        {
                                                if ((arr_coords[2 * figura_coord[0]] == j && arr_coords[2 * figura_coord[0] + 1] == i) ||
                                                        (arr_coords[2 * figura_coord[1]] == j && arr_coords[2 * figura_coord[1] + 1] == i) ||
                                                        (arr_coords[2 * figura_coord[2]] == j && arr_coords[2 * figura_coord[2] + 1] == i))
                                                        printf("*");

                                                else printf(".");
                                        }
                                }
                                else printf(".");

                                for (z = 0; z < MAX(NumberOfDigits_forX_max, NumberOfDigits_forX_min) + 1; z++)
                                {
                                        printf(" ");
                                }
                        }
                        else
                        {
                                for (z = 0; z < MAX(NumberOfDigits_forX_max, NumberOfDigits_forX_min) + 2; z++)
                                {
                                        printf(" ");
                                }
                        }
                }
                printf("\n");
        }

        for (z = 0; z < MAX(NumberOfDigits_forY_max, NumberOfDigits_forY_min) + 1; z++)
        {
                printf(" ");
        }

        for (j = min_x - 1; j <= max_x + 1; j++)
        {
                printf("-");
                for (z = 0; z < MAX(NumberOfDigits_forX_max, NumberOfDigits_forX_min) + 1; z++)
                {
                        printf(" ");
                }
        }
        printf("\n");
        for (z = 0; z < MAX(NumberOfDigits_forY_max, NumberOfDigits_forY_min) + 1; z++)
        {
                printf(" ");
        }
        for (j = min_x - 1; j <= max_x + 1; j++)
        {
                printf("%d", j);
                CurrentNumberOfDigits = 1;
                NumberForCalculations = j;
                for (; abs(NumberForCalculations) > 0;)
                {
                        NumberForCalculations /= 10;
                        if (NumberForCalculations) CurrentNumberOfDigits++;
                }
                if (j < 0)CurrentNumberOfDigits++;

                for (z = 0; z < MAX(NumberOfDigits_forX_max, NumberOfDigits_forX_min) - CurrentNumberOfDigits + 2; z++)
                {
                        printf(" ");
                }
        }
}
