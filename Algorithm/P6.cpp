#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include <algorithm>

using namespace std;

typedef struct loc{
  int i;
  int j;
  int now;
} L;

vector <int> h , w;
vector < vector<int> > poly[5];
stack<L> st;

bool possible(int **board, int nowp, int i, int j, int nowh, int noww,int ssize){
  

  int hh=0, ww = 0;
  for(int k = i; k <i+nowh; k++){
    if( k == ssize){
      return false;
    }

    for(int q = j; q<j+noww; q++){
      if(q == ssize){
        return false;
      }
      else if(board[k][q] != 0 && poly[nowp][hh][ww] == 1){
        return false;
      }
      ww++;
    }
    hh++;
    ww =0;
  }

  return true;
}

bool success(int ** board, int ssize){
  for(int i=0; i<ssize; i++){
    for(int j=0; j< ssize; j++){
      if(board[i][j] == 0){
        return false;
      }
    }
  }

  return true;
}

int erase( int** board , int nowp, int i, int j ,int nowh, int noww){
  int hh=0, ww = 0;
  int count = 0;

  for(int k = i; k <i+nowh; k++){
    for(int q = j; q<j+noww; q++){
      if(board[k][q]== nowp+1 ){
        board[k][q] =  0;
        count++;
      }
      ww++;  
    }

    hh++;
    ww = 0;
  }
  return count;
}

int put(int**board, int nowp,int i, int j, int nowh, int noww){
  int hh=0, ww = 0;
  int count =0;

  for(int k = i; k <i+nowh; k++){
    for(int q = j; q<j+noww; q++){
      if(poly[nowp][hh][ww] == 1){
        board[k][q] =  nowp +1;
        count++;
      }
      ww++;  
    }

    hh++;
    ww = 0;
  }
  return count;
}

void pushst(int x, int y, int z){
  L nw;
  nw.i = x;
  nw.j = y;
  nw.now = z;
  st.push(nw);
}

void resolve(int **board , int ssize, int index, int n, int s, int loci, int locj, int restart, int c){
  c++;
  cout << c <<"!!!!";
  int i, j, stop =0;

  if(restart ==0){
    locj++;
  }

  for(i =loci ; i< ssize; i++){
    for(j =locj; j< ssize; j++){
      if(possible(board,index,i,j,h[index],w[index],ssize) == true){
        
        s -= put(board, index,i,j,h[index],w[index]);
        pushst(i,j,index);
        stop = 1;
        break;
        
      }
    }
    locj = 0;
    if(stop == 1){
      break;
    }
  }

  if(stop == 0){ //적절한 지점을 찾지 못했으면
    
    if(st.empty()){ // 처음블락을 끝까지 갔는데도? -> 실패
      return;
    }
    else{
      L again = st.top();
      st.pop();
      s += erase(board, again.now, again.i,again.j,h[again.now],w[again.now]);
      resolve(board, ssize,again.now,n,s,again.i,again.j,0,c);
    }
    
  }

  else{ 
    if(s == 0){
      return;
    }

    else{
      resolve(board, ssize,index+1,n,s,0,0,1,c);
    }
  }

}



void solve(int ** board, int ssize, int index, int n ,int s, int c){
  int stop =0;
  c++;
  if(index == n){
  
    return;
  }
  
  for(int i =0 ; i< ssize; i++){

    for(int j =0; j< ssize; j++){
      if(possible(board,index,i,j,h[index],w[index],ssize) == true){
        s -= put(board, index,i,j,h[index],w[index]);
        pushst(i,j,index);
        stop = 1;
        break;
      }
    }

    if(stop == 1){
      break;
    }

  }
  
  if(stop == 0){
    L again = st.top();
    st.pop();
    s += erase(board, again.now, again.i,again.j,h[again.now],w[again.now]);
    
    resolve(board, ssize,again.now,n,s,again.i,again.j,0,c);
  }

  else{
    if(s == 0){
      return;
    }
    
    solve(board,ssize,index+1,n,s,c);
  }
  
}



int main() {
  int n ; 
  int tmph, tmpw;
  int input;
  int count1 = 0 , max = 0 , check =0, ssize =0;
  
  cin >> n;
  
  for(int i =0; i<n; i++){
    cin >> tmph >> tmpw;
    
    if(max < tmph){
      max = tmph;
    }
    if(max < tmpw){
      max = tmpw;
    }

    h.push_back(tmph);
    w.push_back(tmpw);
    
    for(int j =0; j< tmph; j++){
      vector<int> v;
      for(int k =0; k< tmpw; k++){
        cin >> input;
        
        if(input == 1){
          count1++;
        }
        v.push_back(input);
      }
      
      poly[i].push_back(v) ;
    }

  }
  
  for(ssize =max; ssize<=8; ssize++){
    
    if((int) pow(ssize,2) == count1){
      check =1;
      break;
    }

  }
  
  if(check == 0){
    cout << "No solution possible";
    return 0;
  }

  else{
    int ** board = (int**)malloc(sizeof(int *) * ssize);
    for(int i =0; i<ssize ; i++){
      board[i] = (int *) malloc(sizeof(int ) * ssize);
    }

    for(int i =0; i<ssize; i++){
      for(int j=0; j<ssize; j++){
        board[i][j] = 0;
      }
    }
    
    solve(board,ssize,0,n, (ssize *ssize),0 );
    
    
    bool re = success(board,ssize);
    if(re == true){
      for(int i =0; i<ssize; i++){
        for(int j=0; j<ssize; j++){
          printf("%d ", board[i][j] );
        }
        cout <<endl;
      }
    }

    else{
      cout << "No solution possible";
    }
    

  }
  
  return 0;
}