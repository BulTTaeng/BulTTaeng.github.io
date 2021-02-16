#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

struct x_fx{
  long x;
  long y;
};

struct comp{
  bool operator()(struct x_fx &fa, struct x_fx &ga){
    if(fa.x == ga.x){
      return fa.y < ga.y;
    }
    else{
      return fa.x > ga.x;
    }
  }
};


priority_queue<struct x_fx, vector<struct x_fx>, comp> sfunc;

void func_push(long loc, long val){  
  struct x_fx tmp;
  tmp.x = loc;
  tmp.y = val;
  sfunc.push(tmp);
}

long findmax(priority_queue<struct x_fx, vector<struct x_fx>, comp> sfunc, long start, long end){
  long max =0;
  long nowl,nextl;
  long nowv=0,nextv=0;
  int count =0;
  int breakp=0;
  long gap;

  if(sfunc.top().x > start){
    gap = abs(end - sfunc.top().x) +1;
  }
  else{
    gap = abs(end - start) +1;
  }

  while(true){
    
    nowl = sfunc.top().x;
    nowv = sfunc.top().y;
    sfunc.pop();
    
    if(sfunc.empty()){
      break;
    }

    while(nowv >= sfunc.top().y){
        if(sfunc.empty()){
          breakp =1;
          break;
        }
        sfunc.pop();
    }

    if(breakp ==1){
      break;
    }

    nextl = sfunc.top().x;
    nextv = sfunc.top().y;
        
    if(nextl < start){
      continue;
    }

    else if(nextl == end){
      max += (1 * nextv);
      gap -= 1;
      break;
    }

    else if(nextl >= start && nextl < end){
      if(count ==0){
        count =1;  
        if(start >= nowl){
          max += ((nextl-start) * nowv);
          gap -= (nextl-start);
        }

        else{ 
          max += ((nextl-nowl) * nowv);
          gap -= (nextl-nowl);
        }
          
      }

      else{
        max += ((nextl-nowl) * nowv);
        gap -= (nextl-nowl);
      }

    }

    else{
      max += ((end -nowl+1) *nowv);
      gap -= (end -nowl+1);
      break;
    }

    if(sfunc.empty()){
      break;
    }
      
  }


  if(gap != 0){
    max += nowv *gap;
  }
  return max;
}



int main() {
  
  long loc,val;
  long fn, gn, start, end;
  long max=0;

  cin >> fn;

  for(int i =0; i<fn; i++){
      
      cin >> loc >> val;
      func_push(loc,val);
  }

  cin >> gn;
  
  for(int i =0; i<gn; i++){
      
      cin >> loc >> val;
      func_push(loc,val);
  }

  cin >>start>> end;
  
  if(end < sfunc.top().x){
    cout <<max;
    return 0;
  }
  max =findmax(sfunc,start,end);
  max = max %10007;
  cout<<"\n" <<max;

  return 0;
}
