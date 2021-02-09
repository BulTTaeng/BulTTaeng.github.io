#include <stdio.h>
#include <stdlib.h>

void travel(int ** input, int ** Diff, int ** visit,int row , int col,int ans,int n,int i){
	
  if(Diff[row][col] < ans) Diff[row][col] = ans;

  else if(Diff[row][col] > ans){
    return;
  }

  if(visit[row][col] == 0 ||visit[row][col]!= i ){//not visited

    
    visit[row][col] = i;
    if(row !=0){//상,1
      if(input[row-1][col] > input[row][col]){    
        ans =ans +(input[row-1][col] - input[row][col]);
        
        travel(input,Diff,visit,row-1 ,col,ans,n,i);
        ans = ans -(input[row-1][col] - input[row][col]);
      }
    }

    if(col != (n-1)){//우,2
      if(input[row][col+1] > input[row][col]){
        ans =ans+(input[row][col+1] - input[row][col]);
        
        travel(input,Diff,visit,row ,col+1,ans,n,i);
        ans = ans-(input[row][col+1] - input[row][col]);
      }
    }
    if(row != (n-1)){//하,3
      if(input[row+1][col] > input[row][col]){
        ans =ans+(input[row+1][col] - input[row][col]);
        
        travel(input,Diff,visit,row+1 ,col,ans,n,i);
        ans =ans-(input[row+1][col] - input[row][col]);
      }
    }
    if(col != 0){//좌,4
      if(input[row][col-1] > input[row][col]){
        ans =ans+(input[row][col-1] - input[row][col]);
       
        travel(input,Diff,visit,row ,col-1,ans,n,i);
        ans =ans-(input[row][col-1] - input[row][col]);
      }
    }
    

  }
  

}


int main(void) {
  int n;
  int i,j;
  
  int ans =0;
  int min=100000000;
  int max=0;
  int maxN=0;
  scanf("%d",&n);

  int ** input = (int**)malloc(sizeof(int*) * n);
  for(i=0; i<n; i++){
    input[i] = (int*)malloc(sizeof(int) * n);
  }

  int ** Diff = (int**)malloc(sizeof(int*) * n);
  for(i=0; i<n; i++){
    Diff[i] = (int*)malloc(sizeof(int) * n);
  }

  int ** visit = (int**)malloc(sizeof(int*) * n);
  for(i=0; i<n; i++){
    visit[i] = (int*)malloc(sizeof(int) * n);
  }

  //입력값 받기
  for(i =0; i<n; i++){
    for(j=0;j<n;j++){
      scanf("%d",&input[i][j]);
      if(input[i][j] > max) {
        max = input[i][j];
      }
      if(input[i][j] < min){
        min = input[i][j];
       
      }
    }
  }

  int x = 1;
  for(i=0; i<n; i++){
    for(j=0;j<n;j++){
      travel(input,Diff,visit,i,j,ans,n,x);
      x++;
    }
  }
  
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(Diff[i][j] > maxN) maxN = Diff[i][j];
    }
  }
  printf("%d",maxN);
}
