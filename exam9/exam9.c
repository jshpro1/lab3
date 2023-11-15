#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define SHM_KEY 1234
#define SEM_KEY 5678
#define BUFFER_SIZE 4096

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

void P(int semid) {
	struct sembuf p = {0, -1, SEM_UNDO};
	semop(semid, &p, 1);
}

void V(int semid) {
	struct sembuf v = {0, 1, SEM_UNDO};
	semop(semid, &v, 1);
}

int main() {
	key_t shm_key = SHM_KEY;
	key_t sem_key = SEM_KEY;
	int shm_id, sem_id;
	void *shared_memory;
	union semun arg;
	struct stat st;

	 // 공유 메모리 생성 또는 연결
	 shm_id = shmget(shm_key, BUFFER_SIZE, IPC_CREAT | 0666);
	 if (shm_id == -1) {
		 perror("shmget 실패");
		 exit(EXIT_FAILURE);
	 }

	 shared_memory = shmat(shm_id, NULL, 0);
	 if (shared_memory == (void *)-1) {
		 perror("shmat 실패");
		 exit(EXIT_FAILURE);
	 }

	 // 세마포어 생성 또는 연결
	 
      	 sem_id = semget(sem_key, 1, IPC_CREAT | 0666);
	 if (sem_id == -1) {
		 perror("semget 실패");
		 exit(EXIT_FAILURE);
	 }

	 // 세마포어 초기화
	 arg.val = 1;
	 if (semctl(sem_id, 0, SETVAL, arg) == -1) {
		 perror("semctl 실패");
		 exit(EXIT_FAILURE);
	 }
	
	 pid_t child_pid = fork();

	 if (child_pid == -1) {
		 perror("fork 실패");
		 exit(EXIT_FAILURE);
	 }

	 if (child_pid == 0) {
		 // 자식 프로세스 (쓰기)
		 FILE *source_file = fopen("source.txt", "r");
		 if (source_file == NULL) {
			 perror("소스 파일 열기 실패");
			 exit(EXIT_FAILURE);
		 }

		 P(sem_id); // 세마포어 P 연산

		 size_t bytesRead;
		 while ((bytesRead = fread(shared_memory, 1, BUFFER_SIZE, source_file)) > 0) {
			 // 파일 내용을 공유 메모리로 복사
		 }

      		 V(sem_id); // 세마포어 V 연산

		 fclose(source_file);
	 } else {
		 // 부모 프로세스 (읽기)
		 wait(NULL); // 자식 프로세스의 종료를 기다림

		
		 P(sem_id); // 세마포어 P 연산

		 FILE *destination_file = fopen("destination.txt", "w");
		 if (destination_file == NULL) {
			 perror("대상 파일 열기 실패");
			 exit(EXIT_FAILURE);
		 }

		 fwrite(shared_memory, 1, BUFFER_SIZE, destination_file);
	
		 V(sem_id); // 세마포어 V 연산						         
	
		 fclose( destination_file);
	 }

	 // 공유 메모리 및 세마포어 삭제
	 shmdt(shared_memory);
	 shmctl(shm_id, IPC_RMID, NULL);
	 semctl(sem_id, 0, IPC_RMID, arg);

	 return EXIT_SUCCESS;
}

	
