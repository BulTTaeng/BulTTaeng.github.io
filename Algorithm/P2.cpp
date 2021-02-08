#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int buildN=0;
  int walk=0;
  long mostfarB=0;
  long mostS=0;
  long maxN =0;
  scanf("%d %d",&buildN,&walk);

  int * humanN = (int*)malloc(sizeof(int) *buildN);
  long *location = (long*)malloc(sizeof(long) *buildN);
  
  int i=0;
  long j=0;
  for(i =0; i<buildN; i++){
    scanf("%d %ld",&humanN[i],&location[i]);

    if(i==0) mostS = location[0];

    if(mostfarB < location[i]) mostfarB = location[i];
    
    if(mostS >location[i]) mostS = location[i];
    
  }
  
  if(walk*2 >= mostfarB-mostS){
    
    for(int i=0; i<buildN; i++){
      maxN+=humanN[i];
    }
    printf("%ld",maxN);
    return 0;
  }
  
  
  long *count = (long*)malloc(sizeof(long) * mostfarB+1);
  
  
  for(i=0; i< buildN; i++){
    
    long start = location[i]-walk;
    long end = location[i] + walk;

    if(start <mostS){
        start=mostS;
    }

    if(end >mostfarB){
      end = mostfarB;
    }
    
    for(j = start; j<=end;j++){
      count[j] += humanN[i];
      
      if(maxN <count[j] ) maxN = count[j];
    }

  }
  
  printf("%ld",maxN);
  
  return 0;
}
