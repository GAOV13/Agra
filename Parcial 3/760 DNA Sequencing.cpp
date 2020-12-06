#include <bits/stdc++.h>
 
using namespace std;

string sigma, s;
set<string> info;
int sigmaSize = 256;
int size, size1;

struct Node{
  int depth, begin, end, suffixIndex;
  int children[256];
  int parent, suffixLink;

  Node(){}

  Node(int begin, int end, int depth, int parent){
    for(int i = 0; i < sigmaSize; ++i)
      children[i] = -1;
    this->begin = begin;
    this->end = end;
    this->parent = parent;
    this->depth = depth;
    suffixLink = -1;
    suffixIndex = -1;
  }

  bool contains(int d){
    return depth <= d && d < depth + (end - begin);
  }

  int length(){
    return end - begin;
  }
};

Node tree[3000];

string get(int l, int r){
  int i;
  string cad(s.begin() + l, s.begin() + r);
  return cad;
}

void suffixIndexDFS(int n, int h){
  int i;
  bool leaf = true;

  for(i = 0; i < sigmaSize; i++){
    if(tree[n].children[i] != -1){
      leaf = false;
      suffixIndexDFS(tree[n].children[i], h + tree[tree[n].children[i]].length());
    }
  }

  if (leaf){ 
    for(i = tree[n].begin; i < tree[n].end; i++){ 
      if(s[i] == '#'){ 
        tree[n].end = i; 
        break;
      } 
    }
    tree[n].suffixIndex = size - h;  
  } 
}

void buildSuffixTree(){
  int n = s.length(), i, cur, curDepth, k, end, lastRule, remSuffix;
  int *a = new int[n];
  int curr, pos = 0, activeNode = -1;

  for(i = 0; i < n; i++)
    a[i] = sigma.find(s[i]);

  curr = pos;
  tree[pos++] = Node(0, 0, 0, 0); 
  tree[0].suffixLink = 0;
  lastRule = remSuffix = 0;

  for(i = 0; i < n; ++i){
    cur = a[i];

    while(remSuffix <= i){
      curDepth = i - remSuffix;

      if(lastRule != 3){
	if(tree[curr].suffixLink != -1)
	  curr = tree[curr].suffixLink;
	else
	  curr = tree[tree[curr].parent].suffixLink;

	k = remSuffix + tree[curr].depth;
	while(curDepth > 0 && !tree[curr].contains(curDepth - 1)){
	  k += tree[curr].end - tree[curr].begin;
	  curr = tree[curr].children[a[k]];
	}
      }

      if(!tree[curr].contains(curDepth)){
	if(activeNode != -1){
	  tree[activeNode].suffixLink = curr;
	  activeNode = -1;
	}

	if(tree[curr].children[cur] == -1){
	  tree[pos++] = Node(i, n, curDepth, curr);
	  tree[curr].children[cur] = pos - 1;
	  lastRule = 2;
	}
	else{
	  curr = tree[curr].children[cur];
	  lastRule = 3;
	  break;
	}
      }
      else{
	end = tree[curr].begin + curDepth - tree[curr].depth;

	if(a[end] != cur){
	  tree[pos++] = Node(tree[curr].begin, end, tree[curr].depth, tree[curr].parent);
	  int newn = pos - 1;
	  tree[pos++] = Node(i, n, curDepth, newn);
	  tree[newn].children[cur] = pos - 1;
	  tree[newn].children[a[end]] = curr;
	  tree[tree[curr].parent].children[a[tree[curr].begin]] = newn;

	  if(activeNode != -1)
	    tree[activeNode].suffixLink = newn;
	  tree[curr].begin = end;
	  tree[curr].depth = curDepth;
	  tree[curr].parent = newn;
	  curr = activeNode = newn;
	  lastRule = 2;
	}
	else if(tree[curr].end != n || (tree[curr].begin - tree[curr].depth) < remSuffix){
	  lastRule = 3;
	  break;
	}
	else
	  lastRule = 1;
      }

      remSuffix += 1;
    }
  }
  
  tree[0].suffixLink = -1;
  suffixIndexDFS(0, 0);
}

int doTraversal(int n, int h, int &maxHeight, int &substringStartIndex){
  int i=0; 
  int ret = -1; 
  if(tree[n].suffixIndex < 0 || n == 0){ 
    for (i = 0; i < sigmaSize; i++){ 
      if(tree[n].children[i] != -1){ 
        ret = doTraversal(tree[n].children[i], h + tree[tree[n].children[i]].length(), maxHeight, substringStartIndex); 
        if(tree[n].suffixIndex == -1) 
          tree[n].suffixIndex = ret; 
        else if((tree[n].suffixIndex == -2 && ret == -3) || (tree[n].suffixIndex == -3 && ret == -2) ||  tree[n].suffixIndex == -4){ 
          tree[n].suffixIndex = -4;
          if(maxHeight < h){ 
            maxHeight = h; 
            substringStartIndex = tree[n].end - h + 1;
            string temp = get(substringStartIndex - 1, substringStartIndex - 1 + maxHeight);
            info.clear();
            info.insert(temp);
          }

          else if(maxHeight == h){
            maxHeight = h; 
            substringStartIndex = tree[n].end - h + 1;
            string temp = get(substringStartIndex - 1, substringStartIndex - 1 + maxHeight);
            if(temp.size()) info.insert(temp);
          }
        } 
      } 
    } 
  } 
  else if(tree[n].suffixIndex > -1 && tree[n].suffixIndex < size1) 
    return -2; 
  else if(tree[n].suffixIndex >= size1) 
    return -3; 
  return tree[n].suffixIndex; 
} 
  
void getLongestCommonSubstring(){ 
    int maxHeight = 0, substringStartIndex = 0;
    info.clear();
    doTraversal(0, 0, maxHeight, substringStartIndex); 

    if(!info.size()) cout << "No common sequence." << endl;

    else for(set<string>::iterator i = info.begin(); i != info.end(); ++i) cout << *i << endl;
} 

int main(){
  sigma = "abcdefghijklmnopqrstuvwxyz#$";
  sigmaSize = sigma.length();
  string s1, s2;
  bool ver = false;
  while(cin >> s1 >> s2){
    if(ver) cout << endl;

    ver = true;
    s1 += '#';
    s2 += '$';
    size1 = s1.size();
    s = s1 + s2;
    size = s.size();
    buildSuffixTree(); 
    getLongestCommonSubstring(); 
  }
  return 0;
}
