#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

void* pzip(int argc, char** argv){
	FILE* open_file(char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("wzip: cannot open file\n");
    exit(1);
  }

  return fp;
}
  if (argc <= 1) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  FILE* fp;
  int c = 0;
  int last = -1;
  int counter = 0;
  for (int i = 1; i < argc; i++) {
    fp = open_file(argv[i]);

    pthread_mutex_lock(&lock1);
    while ((c = fgetc(fp)) != EOF) { //ASCII CODE		AAAA	4A1B	64
      if (last == -1) {
        last = c;
        counter++;
      } else if (c != last) {

        fwrite(&counter, sizeof(int), 1, stdout);
        fputc(last, stdout);
        counter = 1;
      } else {
        counter++;
      }

      last = c;
    }
    pthread_mutex_unlock(&lock1);

    fclose(fp);
  }

  if (counter > 0) {
    fwrite(&counter, sizeof(int), 1, stdout);
    fputc(last, stdout);
  }

}

pthread_mutex_t lock1=PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
pthread_t th[20];

int main(int argc, char** argv) {
    pzip(argc,argv);

  return 0;
}
