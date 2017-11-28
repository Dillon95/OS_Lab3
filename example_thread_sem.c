#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int shared= 0;
void race(void);
sem_t *mutex;

int main(){
  pthread_t player1, player2, player3;
  mutex = sem_open("/mutex", O_CREAT, 0644, 1);

  sem_wait(mutex);
  pthread_create(&player1, NULL, (void *)race, NULL);
  sem_wait(mutex);
  pthread_create(&player2, NULL, (void *)race, NULL);
  sem_wait(mutex);
  pthread_create(&player3, NULL, (void *)race, NULL);
  //sem_wait(mutex);

  pthread_join(player1, NULL);
  pthread_join(player2, NULL);
  pthread_join(player3, NULL);

  printf("Total Number = %d\n", shared);
  sem_close(mutex);
  sem_unlink("/mutex");

  return 0;

}

void race(void) {
  long i,tmp;
  for(i=1; i<=200000; i++) {
    tmp = shared;
    tmp = tmp + 1;
    shared = tmp;
  }
  //sem_post(mutex);
}
