#include <iostream>
#include <stdlib.h>

using namespace std;

void swap(int a, int b, long arr[]){
  long  temp = arr[a];
  arr[a] = arr[b];
  arr[b] =  temp;
}

void heapify(long arr[], long n, long i) { 
  long largest = i; 
  long l = 2*i + 1; 
  long r = 2*i + 2; 
   
  if (l < n && arr[l] > arr[largest]) 
    largest = l; 
  
     
  if (r < n && arr[r] > arr[largest]) 
    largest = r; 
  
  if (largest != i) { 
    swap(i,largest, arr);   
    heapify(arr, n, largest); 
  } 
} 

void heapSort(long arr[], long n) {  
  for (long i = n / 2 - 1; i >= 0; i--) 
    heapify(arr, n, i); 
  
     
  for (long i=n-1; i>0; i--) {  
    swap(0, i,arr);  
    heapify(arr, i, 0); 
  }

}

void findgap(long * eploc,long * epgap, int n){ 
  for(int i=0; i< n-1; i++){
    epgap[i] = eploc[i+1] - eploc[i];
    
  }
}

 long findmgap(long * eploc,long * epgap, int n, int k){
  long shortd = epgap[0]; 
  long larged = 0;
  long mingap = 0, dist = 0;

  for(int i =0; i<n-1;i++){
    if(epgap[i] <shortd ){
      shortd = epgap[i]; 
    }
     larged += epgap[i];
   }
 
  while (shortd <= larged) {
    long std = (shortd + larged) / 2;
    long start = eploc[0];
    int pole = 1;
 
        
    for (int i = 1; i < n; i++) {
      dist = eploc[i] - start;
      if (std <= dist) {
        pole++;
        start = eploc[i];
      }
    }
 
    if (pole >= k) {
      mingap = std;
      shortd = std+1;
    } 

    else {
      larged = std-1;
    }
  }

  return mingap;
}

int main() {
  int n ,k;
  cin >> n>>k;
  long ans;

  long * eploc = (long*)malloc(sizeof(long) * n);
  long * epgap = (long*)malloc(sizeof(long) * (n-1));

  for(int i =0; i<n ; i++){
    cin >> eploc[i];
  }

  heapSort(eploc,n);
  findgap(eploc,epgap,n);
  
  ans = findmgap(eploc,epgap,n,k);
  cout <<ans;

}