#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void swap(int *a, int *b) {
  int c = *a; 
  *a = *b; 
  *b = c; 
  
}

void heapify(int arr[], int n, int i) {

  int big = i; 
  int left = 2 * i + 1; 
  int right = 2 * i + 2; 

  if (left < n && arr[left] > arr[big]){
    big = left; 
  }
  if (right < n && arr[right] > arr[big]) {
    big = right; 
  }
  if (big != i) {
    swap(&arr[big], &arr[i]);
      heapify(arr, n, big); 

  }

}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n) {

  for (int i = n/2 - 1; i > -1; i--){
    heapify(arr, n, i); 
  }
  for (int i = n-1; i > -1; i--) {
    swap(&arr[0], &arr[i]); 
    heapify(arr, i, 0); 
  }
  extraMemoryAllocated += sizeof(int) * n; 
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int mid, int r) {

  int size1 = mid - l + 1; 
  int size2 = r - mid; 
  
  int data1[size1]; 
  int data2[size2]; 

  int i, j, k; 

  for (i = 0; i < size1; i++) {
    data1[i] = pData[l + i]; 
  }
  for (j = 0; j < size2; j++) {
    data2[j] = pData[mid + j + 1]; 
  }

  i = 0; 
  j = 0; 
  k = l; 

  while (i < size1 && j < size2) {
    if (data1[i] <= data2[j]) {
      pData[k] = data1[i]; 
      i++; 
    }
    else { 
      pData[k] = data2[j]; 
      j++; 
    }
    k++; 
  }
  while (i < size1) {
    pData[k] = data1[i]; 
    i++; 
    k++; 
  }
  while (j < size2) {
    pData[k] = data2[j]; 
    j++; 
    k++; 
  }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {

  int mid; 
  
  if (l < r) {
    
    mid = (l + r)/2; 

    mergeSort(pData, l, mid);

    mergeSort(pData, mid+1, r);  

    merge(pData, l, mid, r);

    extraMemoryAllocated += sizeof(int) * (r); 

  }
  
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	// for (i=sz;i<dataSz;++i)
	// {
	// 	printf("%d ",pData[i]);
	// }
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}