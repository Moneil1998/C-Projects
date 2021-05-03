#include <stdio.h>
#include <stdlib.h>
float min(float *dataSet, int dataSetSize);
float max(float *dataSet,int dataSetSize);
float sum(float *dataSet,int dataSetSize);
float avg(float *dataSet,int dataSetSize);
void print(int set, float *dataSet,int dataSetSize);
void menu(float ***dataSetArrayPtr, int **dataSetSizePtr,int numSets);
int getData(float* dataSet, int dataSetSize);
int getNumOfData();
void allocate(float ***dataSetArrayPtr, int **dataSetSizePtr, int numSets);
void deallocate(float ***dataSetArrayPtr, int **dataSetSizePtr, int numSets);


int main() 
{
  float ** dataSetArrayPtr= NULL;
  int * dataSetSizePtr= NULL;
  int numSets = 0;

  numSets = getNumOfData();
  allocate(&dataSetArrayPtr, &dataSetSizePtr, numSets);
  menu(&dataSetArrayPtr, &dataSetSizePtr,numSets);
  deallocate(&dataSetArrayPtr, &dataSetSizePtr, numSets);
}

/*
Allocating and deallocating memory functions
*/


/*
This functions allocates space in memory given the number of datasets and the arrays within them.
*/
void allocate(float ***dataSetArrayPtr, int **dataSetSizePtr, int numSets)
{
  
  int i = 0,sizeOfArray = 0;
  float *temp=NULL;
  
  *dataSetArrayPtr = (float**)calloc(numSets, sizeof(float*));
  *dataSetSizePtr = (int*)calloc(numSets, sizeof(int));
  
  
    for(i = 0;i<numSets;i++)
    {
      printf("\nEnter dataset %d size: ",i);
      scanf("%d",&sizeOfArray);
      (*dataSetSizePtr)[i]=sizeOfArray;
      temp = (float*)calloc(sizeOfArray,sizeof(float));
      getData(temp,sizeOfArray);
      (*dataSetArrayPtr)[i]=temp;
    }
  
}
/*
This function will deallocate the space in memory for each call of calloc.
*/
void deallocate(float ***dataSetArrayPtr, int **dataSetSizePtr, int numSets)
{
  int i = 0;
  for(i=0;i<numSets;i++)
  {
    free((*dataSetArrayPtr)[i]);
  }
  free(*dataSetArrayPtr);
  free(*dataSetSizePtr);
 }

/*
Menu function


This function is for selecting which calculation wants to be done on the dataset
by calling the respective function(s).
*/
void  menu(float ***dataSetArrayPtr, int **dataSetSizePtr,int numSets)
{
  int selection = 0;
  int dataSet = 0;
  do
  {
    printf("\n");
    printf("Enter the number of the data set on which you wish to do calculations:");
    scanf("%d",&dataSet);
    while (dataSet>numSets){
      printf("Out of range dataset. Please enter the number on which you wish to do calculations:");
      scanf("%d",&dataSet);
    }
    printf("\n");
    printf("\n");
    printf("1. Find the minimum value\n");
    printf("2. Find the maximum value\n");
    printf("3. Calculate the sum of all values\n");
    printf("4. Calculate the average of all the values\n");
    printf("5. Print the values in the data set\n");
    printf("6. Exit the program\n");
    printf("\n");
    printf("Enter a number from the menu:");
    printf("\n");
    scanf("%d",&selection);
    while (selection<0 || selection>6){
      printf("Not an option! Please enter a number from the menu:");
      printf("\n");
      scanf("%d",&selection);
    }
  
    switch (selection)
      {
      case 1:
	printf("\n");
	printf("The minimum value in data %d is: %0.2f\n",dataSet, min((*dataSetArrayPtr)[dataSet-1],(*dataSetSizePtr)[dataSet-1]));
	printf("\n");
	break;
	
      case 2:
	printf("\n");
        printf("The maximum value in data %d is: %0.2f\n", dataSet, max((*dataSetArrayPtr)[dataSet-1],(*dataSetSizePtr)[dataSet-1]));
	printf("\n");
	break;
      case 3:
	printf("\n");
	printf("The sum of all the value in data %d is: %0.2f\n", dataSet, sum((*dataSetArrayPtr)[dataSet-1],(*dataSetSizePtr)[dataSet-1]));
	printf("\n");
	break;
      case 4:
	printf("\n");
	printf("The average of all the value in data %d is: %0.2f\n",dataSet, avg((*dataSetArrayPtr)[dataSet-1],(*dataSetSizePtr)[dataSet-1]));
	printf("\n");
	break;
      case 5:
	printf("\n");
	print(dataSet, (*dataSetArrayPtr)[dataSet-1],(*dataSetSizePtr)[dataSet-1]);
	printf("\n");
	break;
	
       


      }
  }while (selection != 6);
}

/*
Calculation functions



This function will print the given chosen dataset array.
*/
void print (int set,float* dataSet, int dataSetSize)
{
  int i = 0;
  printf("\n");
  printf("Data Set %d:\n",set);
  for(i=0; i<dataSetSize;i++)
  {
    printf("%0.2f\n",dataSet[i]);
  }
}

/*
This function will calculate and return the average of the array.
*/
float avg (float* dataSet, int dataSetSize)
{
  float total = sum(dataSet,  dataSetSize);
  float avg = total/dataSetSize;
  
  return avg;


}

/*
This function will calculate and return the sum of the array.
*/
float sum (float* dataSet, int dataSetSize)
{
  float sum = 0.0;
  int i = 0;
  for( i=0; i<dataSetSize; i++)
    {
      sum += dataSet[i];
      
    }
  return sum; 


}

/*
This function will return the minimum value of the array.
*/

float min (float *dataSet, int dataSetSize)
{
  
  float temp = dataSet[0];
  int i = 0;
  for(i = 0;i<dataSetSize;i++)
  {
    if (dataSet[i]< temp)
    {
      temp = dataSet[i];
    }
  }
  return temp;
}

/*
This function will return the maximum value of the array.
*/
float max (float* dataSet, int dataSetSize)
{
  int i = 0;
  float temp = dataSet[0];
  
  for(i = 0;i<dataSetSize;i++)
  {
    if (dataSet[i]> temp)
    {
      temp = dataSet[i];
    }
  }
  return temp;
}

/*
This function will store user input floats into array.
*/
int getData (float* dataSet, int dataSetSize)
{
  int i = 0;
  printf("\nEnter floats:");
  for(i=0;i<dataSetSize; i++)
  {
    scanf(" %f",&dataSet[i]);
  }
  return;
}

/*
This function will return the number of dataset user wants.
*/
int getNumOfData()
{
  int num;
  printf("\nEnter number of datasets:");
  scanf("%d",&num);
  while (num<1)
  {
    printf("\nPlease enter a number greater or equal to 1:");
    scanf("%d", &num);
  }
  return num;
}



