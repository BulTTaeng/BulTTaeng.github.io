#include <iostream> 
#include <queue> 
#include <vector> 

using namespace std;

void bfs(int start,int *dst,int *visit,vector<int> cities[]){
  queue<int> nextcity; 
  nextcity.push(start); 
  visit[start] = true; 

  while(!nextcity.empty()){
    int now = nextcity.front();
    nextcity.pop();
    for(int i=0; i< cities[now].size(); i++){
       int adjcity = cities[now][i]; 
       if(!visit[adjcity]){
        nextcity.push(adjcity);
        visit[adjcity] = true; 
        dst[adjcity] =dst[now]+1;
       }
    }
    
  }

}

int main() {
  int p,q,r,N,M;
  int city1, city2;
  int sp=0;
  int distance;


  scanf("%d %d %d %d %d",&p,&q,&r,&N,&M);
   
  vector<int> cities[N+1];

  int * dst1 = (int*)malloc(sizeof(int) * N+1);
  int * dst2 = (int*)malloc(sizeof(int) * N+1);
  int * dstN = (int*)malloc(sizeof(int) * N+1);
  int * visit1 = (int*)malloc(sizeof(int) * N+1);
  int * visit2 = (int*)malloc(sizeof(int) * N+1);
  int * visitN = (int*)malloc(sizeof(int) * N+1);

  for(int i =0; i< M; i++){
    scanf("%d %d",&city1,&city2);
    cities[city1].push_back(city2);
    cities[city2].push_back(city1);
  }
  bfs(1,dst1,visit1,cities);
  bfs(2,dst2,visit2,cities);
  bfs(N,dstN,visitN,cities);

  for(int i=1; i<N+1; i++){
     distance = dst1[i] *p +dst2[i] *q + dstN[i]*r;
    
    if( sp==0 ) sp = distance;

    else{
      if(sp > distance && distance!=0){
        sp = distance;
      }
    }
  }

  cout << sp;

  free(visit1);
  free(visit2);
  free(visitN);
  free(dst1);
  free(dst2);
  free(dstN);
  
  return 0;
}
