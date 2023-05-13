#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

#define SIZE 1024
#define NAME "TEST"
#define PROJ 'f'

int main() {

  int shmid;
  char *shm_ptr;
  char message[SIZE];
  key_t k = ftok(NAME, PROJ);
  
  shmid = shmget(k, SIZE, IPC_CREAT | 0666);
  if (shmid == -1) {
    perror("shmget");
    exit(1);
  }
  
  shm_ptr = shmat(shmid, NULL, 0);
  if (shm_ptr == (char *) -1) {
    perror("shmat");
    exit(1);
  }
  
  printf("Message received: %s", shm_ptr);
  
  shmdt(shm_ptr);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}
