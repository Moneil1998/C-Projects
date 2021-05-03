#include <stdio.h>
#include <stdlib.h>
float min(float dataSet[],int dataSetSize);
float max(float dataSet[],int dataSetSize);
float sum(float dataSet[],int dataSetSize);
float avg(float dataSet[],int dataSetSize);
void print(float dataSet[],int dataSetSize);
int getData (float *dataSet, int dataSetSize);
int  menu(float dataSet[], int dataSetSize);

int main() 
{
  float dataSet[10];
  int dataSetSize = 10;
  
  getData(dataSet, dataSetSize);
  
  menu(dataSet, dataSetSize);
  
}

/*
Menu function


This function is for selecting which calculation wants to be done on the dataset
by calling the respective function(s).
*/
int  menu(float dataSet[], int dataSetSize)
{
  int selection = 0;
  do
  {
    printf("\n");
    printf("1. Find the minimum value\n");
    printf("2. Find the maximum value\n");
    printf("3. Calculate the sum of all values\n");
    printf("4. Calculate the average of all the values\n");
    printf("5. Print the values in the data set\n");
    printf("6. Exit the program\n");
  
    printf("\n");
    printf("Enter a number from the menu:");
    scanf("%d",&selection);
    while (selection<0 || selection>6){
      printf("Not an option! Please enter a number from the menu:");
      scanf("%d",&selection);
    }
  
    switch (selection)
      {
      case 1:
	printf("\n");
	printf("The minimum value in data is: %0.2f\n",min(dataSet,dataSetSize));
	printf("\n");
	break;
      case 2:
	printf("\n");
        printf("The maximum value in data is: %0.2f\n", max(dataSet, dataSetSize));
	printf("\n");
	break;
      case 3:
	printf("\n");
	printf("The sum of all the value in data is: %0.2f\n",sum(dataSet, dataSetSize));
	printf("\n");
	break;
      case 4:
	printf("\n");
	printf("The average of all the value in data is: %0.2f\n",avg(dataSet, dataSetSize));
	printf("\n");
	break;
      case 5:
	printf("\n");
	print(dataSet, dataSetSize);
	printf("\n");
	break;
      default:
	break;
       


      }
  }while (selection != 6);
}

/*
Calculation functions



This function will print the given chosen dataset array.
*/
void print (float dataSet[], int dataSetSize)
{
  
  int i = 0;
  printf("\n");
  printf("Data Set:\n");
  for(i=0; i<dataSetSize;i++)
  {
    printf("%0.2f\n",dataSet[i]);
  }
  

/*
This function will calculate and return the average of the array.
*/
}
float avg (float dataSet[], int dataSetSize)
{
  float total = sum(dataSet,  dataSetSize);
  float avg = total/dataSetSize;
  return avg;
}

/*
This function will calculate and return the sum of the array.
*/
float sum (float dataSet[], int dataSetSize)
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
float min (float dataSet[], int dataSetSize)
{
  int i = 0;
  float temp = dataSet[0];
  
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
float max (float dataSet[], int dataSetSize)
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
int getData (float *dataSet, int dataSetSize)
{
  int i = 0;
  printf("Enter 10 floats\n");
  for(i;i<dataSetSize; i++)
  {
    scanf("%f",&dataSet[i]);
  }
}




