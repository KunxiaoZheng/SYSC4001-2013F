#include <stdio.h>	
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg);
void *thread_function2(void *arg);
void *thread_function3(void *arg);
void *thread_function4(void *arg);
double val(void);
int randMaxMin(int, int);

sem_t bin_sem;
sem_t ful_sem;
sem_t syn_sem;

int golden_buffer[6];
int silver_buffer[11];
int bronze_buffer[11];
int golden_time_buffer[6]
int silver_time_buffer[11];
int bronze_buffer[11];

#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int currentPostion=0;


int main() {
  int res;
  pthread_t a_thread;
  pthread_t a_thread2;
  pthread_t a_thread3;
  pthread_t a_thread4;
  void *thread_result;

  int count =0;//create 40 processes
  int GoldenNextPosition=0;
  int SilverNextPosition=0;
  int BronzeNextPosition=0;

  //information about the fake process
  int fakePID;
  int fakePriority;
  int fakeTime;

  //initial semaphores
  res = sem_init(&bin_sem, 0, 1);
  if (res != 0) {
    perror("Semaphore initialization failed");
    exit(EXIT_FAILURE);
  }
  res = sem_init(&ful_sem, 0, 5);
  if (res != 0) {
    perror("Semaphore initialization failed");
    exit(EXIT_FAILURE);
  }
  res = sem_init(&syn_sem, 0, 0);
  if (res != 0) {
    perror("Semaphore initialization failed");
    exit(EXIT_FAILURE);
  }

  //creating threads
  res = pthread_create(&a_thread, NULL, thread_function, NULL);
  if (res != 0) {
    perror("Thread1 creation failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_create(&a_thread2, NULL, thread_function2, NULL);
  if (res != 0) {
    perror("Thread1 creation failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_create(&a_thread3, NULL, thread_function3, NULL);
  if (res != 0) {
    perror("Thread1 creation failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_create(&a_thread4, NULL, thread_function4, NULL);
  if (res != 0) {
    perror("Thread1 creation failed");
    exit(EXIT_FAILURE);
  }


  //semaphores and producing the processes
  while(count<40){

    //randint for the infomations
    golden_buffer[GoldenNextPosition]=count;
    fakePID=randMaxMin(1000,9999);
    fakePriority=val();
    fakeTime=randMaxMin(0,10);
    sem_wait(&ful_sem);  
    sem_wait(&bin_sem);
    
   
    
      if(fakePriority<0.2){
         printf("Main Thread golden-%d:%d\n",GoldenNextPosition ,golden_buffer[GoldenNextPosition]);
            golden_buffer[GoldenNextPosition]=fakePID;
            golden_time_buffer[GoldenNextPosition]=fakeTime;
            if(GoldenNextPosition==4){
              GoldenNextPosition=0;
             }else{
              GoldenNextPosition++;
             }
      //put process into the gold queue
      }else if(fakePriority>=0.2&&fakePriority<0.6){
         printf("Main Thread silver-%d:%d\n",SilverNextPosition ,silver_buffer[SilverNextPosition]);
            silver_buffer[SilverNextPosition]=fakePID;
            silver_time_buffer[SilverNextPosition]=fakeTime;
            if(SilverNextPosition==9){
              SilverNextPosition=0;
             }else{
              SilverNextPosition++;
             }
        
      //put process into the silver queue
      }else{
         printf("Main Thread bronze-%d:%d\n",BronzeNextPosition ,bronze_buffer[BronzeNextPosition]);
            bronze_buffer[BronzeNextPosition]=fakePID;
            bronze_time_buffer[BronzeNextPosition]=fakeTime;
            if(BronzeNextPosition==9){
              BronzeNextPosition=0;
             }else{
              BronzeNextPosition++;
             }
        
      //put process into the bronze queue
      }
    
    sem_post(&bin_sem);
    sem_post(&syn_sem);
    count++;
  }



  printf("\nWaiting for thread to finish...\n");
  res = pthread_join(a_thread, &thread_result);
  if (res != 0) {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_join(a_thread2, &thread_result);
  if (res != 0) {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_join(a_thread3, &thread_result);
  if (res != 0) {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }

  res = pthread_join(a_thread4, &thread_result);
  if (res != 0) {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }

  printf("\nThread joined\n");
  sem_destroy(&bin_sem);
  exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
  int count=10;
  while(count > 0) {
    sem_wait(&syn_sem);
    sem_wait(&bin_sem);  
    printf("S thread-%d:%d\n",currentPostion,golden_buffer[currentPostion]);
    if(currentPostion==4){
      currentPostion=0;
    }else{
      currentPostion++;
    }    
    //get the process
    sem_post(&bin_sem);
    sem_post(&ful_sem);
    count--;
  }
  pthread_exit(NULL);
}

void *thread_function2(void *arg) {
  int count=10;
  while(count > 0) {
    sem_wait(&syn_sem);
    sem_wait(&bin_sem);  
    printf("S2 thread-%d:%d\n",currentPostion,golden_buffer[currentPostion]);
    if(currentPostion==4){
      currentPostion=0;
    }else{
      currentPostion++;
    }    
    //get the process
    sem_post(&bin_sem);
    sem_post(&ful_sem);
    count--;
  }
  pthread_exit(NULL);
}


void *thread_function3(void *arg) {
  int count=10;
  while(count > 0) {
    sem_wait(&syn_sem);
    sem_wait(&bin_sem);  
    printf("S3 thread-%d:%d\n",currentPostion,golden_buffer[currentPostion]);
    if(currentPostion==4){
      currentPostion=0;
    }else{
      currentPostion++;
    }    
    //get the process
    sem_post(&bin_sem);
    sem_post(&ful_sem);
    count--;
  }
  pthread_exit(NULL);
}

void *thread_function4(void *arg) {
  int count=10;
  while(count > 0) {
    sem_wait(&syn_sem);
    sem_wait(&bin_sem);  
    printf("S4 thread-%d:%d\n",currentPostion,golden_buffer[currentPostion]);
    if(currentPostion==4){
      currentPostion=0;
    }else{
      currentPostion++;
    }    
    //get the process
    sem_post(&bin_sem);
    sem_post(&ful_sem);
    count--;
  }
  pthread_exit(NULL);
}


double val(){
  return (double)rand() / (double)RAND_MAX;
}

int randMaxMin(int max, int min){
  int r = (rand() % (max-min)+min;
  return r;
}
