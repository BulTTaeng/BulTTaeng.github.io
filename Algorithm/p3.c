#include <stdio.h>
#include <stdlib.h>

int packcrr(int * bags, int m,int i,int m_i,int bnum,int min){
int crr=0;


  if(bags[i] == 0 && (i > m/2) ){ 
    crr+=packcrr(bags,m,i-1,m_i+1,bnum,min);
  }
  else if(i> m/2){ //오른쪽 숫자들

    for(int j=m_i; j>=min; j--){
      if(bags[i] >= bags[j]){
        bags[i] -= bags[j];
        bnum -= (bags[j]*2);
        crr += bags[j];
        bags[j] = 0;
      }

      else{//clear , good to go
        bags[j] -= bags[i];
        bnum -= (bags[i]*2);
        crr += bags[i];
        bags[i] = 0;
        break;
      }
    }

    if(bags[i] != 0){//still left
      crr+= bags[i];
      bnum -= bags[i];
      bags[i] = 0;
    }

    crr+=packcrr(bags,m,i-1,m_i+1,bnum,min);
  }
  else if(i <= m/2){//왼쪽 숫자들, 그냥 나누기 2하면됨
    crr += (bnum/2 +bnum%2);
    return crr;
  }
  return crr;
}

int main(void){
  int m;
  int w;
  int bnum=0;
  int crr=0;
  int max = 0;
  int min = 100001;
  scanf("%d",&m);
  
  int * bags = (int*)malloc(sizeof(int) * m+1);
  
  while(scanf("%d",&w) != EOF){
    if(w > max) max = w;
    if(w<min) min = w;
    bags[w]++;
    bnum++;
  }


  crr += bags[m];
  bnum -= bags[m];
  bags[m] = 0;
  

  if(m == max && m == min) {
    printf("%d",crr);
    return 0;
  }
  else if(m == max){
    crr += packcrr(bags,m,m-1,m-m+1,bnum,min);
  }
  else{
    crr += packcrr(bags,m,max,m-max,bnum,min);
  }

  printf("%d",crr);

  free(bags);
  return 0;
}
