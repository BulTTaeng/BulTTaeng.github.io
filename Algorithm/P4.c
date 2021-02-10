#include <stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void) {
  int n,k;

  int ** tower =(int**)malloc(sizeof(int*) * 4);
  for(int i=0; i< 4; i++){
    tower[i] = (int*)malloc(sizeof(int) * (n+1));
  }

  scanf("%d %d",&n,&k);

  int * loc = (int *)malloc(sizeof(int) * (n+1));

  scanf("%d",&tower[1][0]);
  for(int i=1; i<=tower[1][0]; i++){
    scanf("%d",&tower[1][i]);
    loc[tower[1][i]] = 1;
  }

  scanf("%d",&tower[2][0]);
  for(int i=1; i<=tower[2][0]; i++){
    scanf("%d",&tower[2][i]);
    loc[tower[2][i]] = 2;
  }

  scanf("%d",&tower[3][0]);
  for(int i=1; i<=tower[3][0]; i++){
    scanf("%d",&tower[3][i]);
    loc[tower[3][i]] = 3;
  }

  int ans =0;
  
  for(int i=n;i>0;i--){
    if(loc[i] == k){
      continue;
    }
    else{
      ans+=pow(2,i-1);
    }

    if(k==1){
      if(loc[i] ==2) k=3;
      else k =2;
    }
    else if(k==2){
      if(loc[i] ==1) k =3;
      else k=1;

    }
    else if(k ==3){
      if(loc[i] ==1) k=2;
      else k=1;
    }
  }
  
  
  printf("%d",ans);
  for(int i=0; i<4; i++){
  	free(tower[i]);
  }
  free(tower);
  free(loc);
  return 0;
}
