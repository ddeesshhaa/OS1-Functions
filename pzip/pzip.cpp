#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <pthread.h>
#include <signal.h>
using namespace std;
struct str_struct{
    FILE *file;
    int index;
}y[100];
pthread_mutex_t lockk=PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_lock(pthread_mutex_t*mutex);
int pthread_mutex_unlock(pthread_mutex_t*mutex);
pthread_t p[100];
vector<pair<int,char> >ans[50];
char c;
string s;

void *zip(void *file){
  str_struct cur = *(str_struct*)file;
  int idx = cur.index;
  FILE *cur_file = cur.file;
  pthread_mutex_lock(&lockk);
    s.clear();
    while((c = fgetc(cur_file)) != EOF)
        s += c;
  int count = 1;
  for(int i = 1; i<(int)s.size(); i++){

    if(s[i] == s[i-1]) count++;
    else{
      ans[idx].push_back({count,s[i-1]});
      count = 1;
    }
  }
  ans[idx].push_back({count,s[s.size()-1]});
  pthread_mutex_unlock(&lockk);
  fclose(cur_file);
  return NULL ;
}

int main(int argc , char** argv){

  if(argc==1){
    cout << "pzip: file1 [file2 ...]\n";
    return 1;
  }
  for(int i = 1;i < argc;i++){
        x[i].file = fopen(argv[i],"r");
        x[i].index = i;
    }
    for(int i=1;i<argc;i++){
        pthread_create(&p[i],NULL,zip,&y[i]);
    }

    for(int i=1;i<argc;i++){
        pthread_join(p[i],NULL);
    }
    for(int i=2; i<argc; i++)
    {
        int sz1=ans[i-1].size()-1;
        if(ans[i-1][sz1].second==ans[i][0].second)
        {
            ans[i][0].first+=ans[i-1][sz1].first;
            ans[i-1].pop_back();
        }
    }
    for(int i = 1;i < argc ;i++){
        for(auto it:ans[i])
        {
        	 fwrite(&it.first,1,sizeof(it.first),stdout);
        	 fwrite(&it.second,1,sizeof(it.second),stdout);
        }
    }
	 
  return 0;
}







