#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INF 99999

void printHouseNumbers(int* riskedHouses, int length){ //function to print house numbers
	
	int i=0;
	
	for(; i<length; i++){
		
		printf("H%d ", riskedHouses[i]);
		
	}
	
}

void printMatrix(int** a, int N){ //function to print a matrix
	
	int i=0, j=0;
	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			
			printf("%5d ", a[i][j]);
			
		}
		printf("\n");
	}
	
}

void floydWarshall(int** a, int N){ //Floyd Warshall Algorithm
	
	int i=0, j=0, k=0;
	
	for(k=0; k<N; k++){
		
		for(i=0; i<N; i++){
			
			for(j=0; j<N; j++){
				
				if(a[i][k] + a[k][j] < a[i][j]){
					a[i][j] = a[i][k] + a[k][j];
				}
				
			}
		}
	}
	
	printMatrix(a, N);
	printf("\n");
	
}


bool isAlreadyPatient(int houseNumber, int* houseNumbersOfPatients, int numberOfPatients){  //returns true if a house is that of an already infected person
	
	int i=0;
	
	for(i=0; i<numberOfPatients; i++){
		
		if(houseNumbersOfPatients[i] == houseNumber){
			return true;
		}
		
	}
	return false;
	
}


int removeDuplicates(int* a, int length){ //removes duplicate elements from an array and returns the length of array after removing them
	
	int i=0;
	int j=0;
	int k=0;
	
	for(i = 0; i < length; i++)
    {
        for(j = i+1; j < length; )
        {
        	
            if(a[j] == a[i])
            {
                for(k = j; k < length; k++)
                {
                    a[k] = a[k+1];
                }
                length--;
            }
            else
            {
                j++;
            }
        }
    }
    
    return length;
	
}

void housesInRisk(int** graph, int numberOfHouses, int thresholdDistance, int* houseNumbersOfPatients, int numberOfPatients){
// prints the house numbers of houses whose residents should to be tested	

	printf("Shortest distances between every pair of houses:\n\n");
	
	floydWarshall(graph, numberOfHouses);
	
	int i=0;
	int itr=0;
	int riskedHousesLength = 0;  //length of the dynamic array named as riskedHouses
	int* riskedHouses = (int*) calloc(numberOfHouses, sizeof(int));
	
	for(itr=0; itr<numberOfPatients; itr++){
	
		int houseNumberOfPatient = houseNumbersOfPatients[itr];
	
		for(i=0; i<numberOfHouses; i++){
			
			if(graph[houseNumberOfPatient][i] <= thresholdDistance 
			&& graph[houseNumberOfPatient][i] != 0 
			&& isAlreadyPatient(i, houseNumbersOfPatients, numberOfPatients) == false){
				
				riskedHouses[riskedHousesLength++] = i;
				
			}
			
		}
	}
	
	riskedHousesLength = removeDuplicates(riskedHouses, riskedHousesLength);
	printf("\nHouse numbers of residents who should get tested are:\n");
	printf("\n");
	printHouseNumbers(riskedHouses, riskedHousesLength);
	
}


int main(){
	
	int numberOfHouses = 12;
	int numberOfPatients = 5;
	int thresholdDistance = 20;
	
	int houseNumbersOfPatients[] = {1, 3, 6, 8, 11};	//can be only 0 to 11
	
	int i=0, j=0;
	
//	int input[][] = {					//number of columns should be MAX not N
//						{0, 5, 999, 10},
//						{5, 0, 3, 999},
//						{999, 3, 0, 1},
//						{10, 999, 1, 0}
//					};
	
	
	int** graph = (int**) malloc(numberOfHouses * sizeof(int*)); //allocating number of rows equal to the numberOfHouses
	
	// allocating number of cells equal to numberOfHouses to every row
	for(i=0; i<numberOfHouses; i++){
		
		graph[i] = (int*) malloc(numberOfHouses * sizeof(int)); 
		
	}
	
	for(i=0; i<numberOfHouses; i++){
		
		graph[i][i] = 0;
		
	}
	
//	graph[0][1] = 5;
//	graph[0][2] = INF;
//	graph[0][3] = 13;
//	graph[0][4] = INF;
//	
//	graph[1][0] = 5;
//	graph[1][2] = 8;
//	graph[1][3] = 14;
//	graph[1][4] = 10;
//	
//	graph[2][0] = INF;
//	graph[2][1] = 8;
//	graph[2][3] = INF;
//	graph[2][4] = 11;
//	
//	graph[3][0] = 13;
//	graph[3][1] = 14;
//	graph[3][2] = INF;
//	graph[3][4] = 13;
//	
//	graph[4][0] = INF;
//	graph[4][1] = 10;
//	graph[4][2] = 11;
//	graph[4][3] = 13;
	
	
	for(i=0; i<numberOfHouses; i++){
		for(j=0; j<numberOfHouses; j++){
			scanf("%d", &graph[i][j]);
		}
	}
	
	
	housesInRisk(graph, numberOfHouses, thresholdDistance, houseNumbersOfPatients, numberOfPatients);
	
	return 0;
	
}
