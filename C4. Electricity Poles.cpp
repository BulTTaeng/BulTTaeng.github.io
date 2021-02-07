#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>

using namespace std;

priority_queue<long, vector<long>,greater<long> > sgap;


void swap(int a, int b, long arr[]){
  long  temp = arr[a];
  arr[a] = arr[b];
  arr[b] =  temp;
}

void heapify(long arr[], long n, long i) 
{ 
    long largest = i; 
    long l = 2*i + 1; 
    long r = 2*i + 2; 
   
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
     
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    if (largest != i) 
    { 
        swap(i,largest, arr);   
        heapify(arr, n, largest); 
    } 
} 

void heapSort(long arr[], long n) 
{  
    for (long i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
     
    for (long i=n-1; i>0; i--) 
    {  
        swap(0, i,arr);  
        heapify(arr, i, 0); 
    } 
}

struct Node {
	long gap;
	Node * next;
};
void push(struct Node** head_ref, long new_data) 
{ 
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    new_node->gap  = new_data; 
    new_node->next = (*head_ref); 
    (*head_ref)    = new_node; 
} 
  
/* Given a reference (pointer to pointer) to the head of a list 
   and a key, deletes the first occurrence of key in linked list */
bool deleteNode(struct Node **head_ref, long key) 
{ 
  
    // Store head node 
    struct Node* temp = *head_ref, *prev; 
  
    // If head node itself holds the key to be deleted 
    if (temp != NULL && temp->gap == key) 
    { 
        temp->next->gap += temp->gap;
        sgap.push(temp->next->gap);      
      
        *head_ref = temp->next;   // Changed head 
        free(temp);               // free old head 
        return true; 
    } 
  
     
    while (temp != NULL && temp->gap != key) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    
    if (temp == NULL) return false; 

    else{ // if there is temp 
      
      if(temp->next == NULL){
        prev->gap += temp->gap; 
        sgap.push(prev->gap);
      }
      else if(temp->next->gap > prev ->gap){//next is large
        prev->gap += temp->gap;
        sgap.push(prev->gap);
      }
      else if(temp->next->gap <= prev ->gap){
        temp->next->gap += temp->gap;
        sgap.push(temp->next->gap);
      }
      prev->next = temp->next; 
      free(temp);
      return true;
    }
    
} 




int main() {
  int n,k,epn=0;
  long min = 1000000001;
  cin >> n >>k;
  epn = (n-1);
  long * eploc = (long*) malloc(sizeof(long) * n);


  for(int i=0; i<n; i++){
    cin >> eploc[i];
  }
  
  
  
  heapSort(eploc, n);
  

  struct Node* head = NULL;
    
  for(int i=0 ; i< n-1; i++){
    push(&head, (eploc[i+1] - eploc[i]));
    sgap.push( (eploc[i+1] - eploc[i]) );
  }
  /*while(!sgap.empty() ){
    cout << sgap.top()<<" ";
    sgap.pop();
  }*/
  /*Node * a = head;
  while( a !=NULL ){
    cout <<a->gap <<" ";
    
    a = a->next;
  }
  printf("\n");
  */
  if( n == k){
    cout  << sgap.top();
    return 0;
  }
  
  
  long small;

  while(!sgap.empty()){
      
    small = sgap.top();
    sgap.pop();
    //printf("small is %ld \n",small);
    bool re = deleteNode(&head,small);
    if(re == true){
      epn--;
      //printf("epn is %d\n",epn);
      if(epn == (k-1)){
        break;
      }
    }

  /*Node * a1 = head;
  while( a1 !=NULL ){
    cout <<a1->gap <<" ";
    
    a1 = a1->next;
  }
  printf("\n");
    */
     
  }

  Node * check = head;

  while( check !=NULL ){
    //cout <<check->gap <<" ";
    if(min >= check->gap ){
      min = check->gap;
    }
    check = check->next;
  }
  
  

  cout <<min;


  return 0;

  
}