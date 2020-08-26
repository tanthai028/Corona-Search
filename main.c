#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define COLS 2

int** readData(int **items);
int** filterData(int **items);
void merge(int **arr, int l, int m, int r);
void mergeSort(int **arr, int l, int r);
int binarySearch(int **list, int x, int y, int len);
void searchPhase(int **items);
int** allocateMem();
int getRows();

int main(void) {
	int **arr, **sortedArr;
	arr = allocateMem();
	sortedArr = allocateMem();
	sortedArr = readData(arr);
	sortedArr = filterData(sortedArr);
	printf("filtered and sorted data written to out.txt");

	searchPhase(sortedArr);
	
	free(sortedArr);
	free(arr);

  return 0;
}


int** allocateMem()
{
	int ROWS = getRows();

	int** newArr = (int**)malloc(sizeof(int*)*ROWS);
	for (int i=0; i<ROWS; i++)
		newArr[i] = (int*)malloc(sizeof(int)*COLS);
	
	return newArr;
}

void searchPhase(int **items){
	int input;
	int x,y;
	int rows = sizeof(items) + 1;

	do{
		printf("\nSearch input (x y): ");
		scanf("%d %d", &x, &y);
		binarySearch(items, x, y, rows);
	} while( x != -999 && y != -999);

	printf("Output: exit\n");

}

int** readData(int **items)
{ 
	FILE *input, *output;
	int cx, cy, cr, n;

	input = fopen("in.txt", "r");

	fscanf(input,"%d %d %d %d", &cx ,&cy, &cr, &n);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < 2; j++){
			fscanf(input, "%d", &items[i][j]);
		}
	}
	
	fclose(input);    
	return items;
}

int** filterData(int **items){
	int ROWS = getRows();
	int x2, y2, i, j, cx, cy, cr, n;
	int x = 0;

	mergeSort(items, 0, 13);
	FILE *input, *output;	
	input = fopen("in.txt", "r");
	output = fopen("out.txt", "w");
	fscanf(input,"%d %d %d %d", &cx ,&cy, &cr, &n);	
	int x1 = cx;
  int y1 = cy;

	// allocate mem for temp 2d array
	int** temp = allocateMem();
	

	for(i = 0; i < ROWS; i++){     
		for(j = 0; j < COLS; j++){

      if (j == 0) 
        x2 = items[i][j];

      else if (j == 1){
        y2 = items[i][j];

				if(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) < cr*cr){
					temp[x][0] = x2;
					temp[x][1] = y2;
					x++;
				}
			}
		}
	}
	
	int rows = sizeof(temp);

	for(int i = 0; i < rows + 1; i++){
		for(int j = 0; j < COLS; j++){
			if(temp[i][i] != 0 || temp[j][j] != 0){
				// printf("%d ", temp[i][j]);
				fprintf(output, "%d ", temp[i][j]);
			}
		}
		fprintf(output, "\n");
		// printf("\n");
	}

	fclose(input);
	fclose(output);

	return temp;
}
      
void mergeSort(int **arr, int l, int r)
{
	if (l < r){
		int m = (l+r)/2;
		mergeSort(arr, l, m);   // left side
		mergeSort(arr, m+1, r); // right side
		merge(arr, l, m, r);
	}
}

void merge(int **arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	int Lx[n1], Rx[n2]; 
	int Ly[n1], Ry[n2]; 

	for (i = 0; i < n1; i++){
		Lx[i] = arr[l + i][0];
		Ly[i] = arr[l + i][1];
	}
	for (j = 0; j < n2; j++){
		Rx[j] = arr[m + 1 + j][0];
		Ry[j] = arr[m + 1 + j][1];
	}
		
	i = 0; 
	j = 0; 
	k = l; 

	while (i < n1 && j < n2){
		if (Lx[i] < Rx[j]){
			arr[k][0] = Lx[i];
			arr[k][1] = Ly[i];
			i++;
		}
		else{
			arr[k][0] = Rx[j];
			arr[k][1] = Ry[j];
			j++;
		}
		k++;
	}
	while (i < n1){
		arr[k][0] = Lx[i];
		arr[k][1] = Ly[i];
		i++;
		k++;
	}
	while (j < n2){
		arr[k][0] = Rx[j];
		arr[k][1] = Ry[j];
		j++;
		k++;
	}
}

int binarySearch(int **list, int x, int y, int len)
{
	int mid;
	int l = 0, h = len - 1;

	while (l <= h){
		mid = (h + l)/2;

		// printf("l: %d\n", l);
		// printf("h: %d\n", h);
		// printf("mid: %d\n", mid);

		if (x == -999 || y == -999)
			return -1;
		
		if (list[mid][0] == x && list[mid][1] == y){ 
			printf("Output: Found at record %d", mid + 1);
			return 1;
		}
		// If item greater, ignore left half
		if (x > list[mid][0] || (x >= list[mid][0] && y > list[mid][1]))
			l = mid + 1;

		// If item is smaller, ignore right half
		else if (x < list[mid][0]  || (x <= list[mid][0] && y < list[mid][1]))
			h = mid - 1;
	}

	// if we reach here, then element was not present
	printf("Output: Not Found");
	return 0;
}

int getRows(){
	int cx, cy, cr, n;
	FILE *input = fopen("in.txt", "r");
	fscanf(input,"%d %d %d %d", &cx ,&cy, &cr, &n);	

	return n;
}


/*
	-4 -2  	[0]
	-4 2 		[1]
	-2 4		[2]
	-1 3 		[3]
	0 -2 		[4]
	2 -2 		[5]
	2 2 		[6]
	2 4 		[7]
	3 1 		[8]
*/

