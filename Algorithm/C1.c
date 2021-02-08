#include <stdio.h>
#include <stdlib.h>

void func(int friends , int marine, int * numf, int **Darr,int snum);

int main(void) {
  int marine;
  int friends;
  int edge;
  scanf("%d %d %d",&marine, &friends, &edge);

  int edges[edge*2];

  int * numf = (int*)malloc(sizeof(int) *(marine+1));
  for(int i=0; i<marine+1; i++){
    numf[i] =0;
  }
  int **Darr = malloc(sizeof(int*) * (marine+1));
  for(int i=0; i<marine+1; i++){
    Darr[i] = malloc(sizeof(int) *(marine+1));
  }
  for(int i=0; i<marine+1; i++){
    for(int j =0; j<marine+1; j++){
      Darr[i][j] = 0;
    }
  }

  for(int i=1; i< edge*2; i= i+2){
    scanf("%d %d",&edges[i],&edges[i+1]);
    Darr[edges[i]][edges[i+1]] = 1;
    Darr[edges[i+1]][edges[i]] = 1;
    numf[edges[i]]++;
    numf[edges[i+1]]++;
  }

  



  for(int i=1; i<marine+1; i++){
    
    if(numf[i] < friends){
      for (int j =1; j<marine+1; j++){
        if(Darr[i][j] == 1){
          numf[i]--;
          numf[j]--;
          Darr[i][j] = 0;
          Darr[j][i] = 0;
          if(numf[j] <friends){
            
            func(friends,marine,numf,Darr,j);
          }
          
        }
      }
      
    }

  }

  int count=0;
  
  for(int i =1; i<marine+1; i++){
    
    if(numf[i] >= friends){
      count ++;
    }
  }

  printf("%d",count);
  return 0;
}

void func(int friends , int marine, int * numf, int **Darr,int snum){
    
      for (int j =1; j<marine+1; j++){
        if(Darr[snum][j] == 1){
          numf[snum]--;
          numf[j]--;
          Darr[snum][j] = 0;
          Darr[j][snum] = 0;
          if(numf[j]<friends){
            func(friends,marine,numf,Darr,j);
          }
          
        }
      }    

}
