#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 256


// 메시지 구조체 정의
struct message {
	long mtype;  // 메시지 타입 (1: 클라이언트1, 2: 클라이언트2)
	char mtext[MAX_MESSAGE_SIZE];  // 메시지 텍스트
};

int main() {
	key_t key;
	int msgid;
	struct message msg;

	// 메시지 큐 키 생성
	key = ftok(".", 'C');
	if (key == -1) {
		perror("ftok 실패");
		exit(EXIT_FAILURE);
	}

	 // 자식 프로세스 생성
	 pid_t child_pid = fork();
	
   	 if (child_pid == -1) {
		 perror("fork 실패");
		 exit(EXIT_FAILURE);
	 }
	
	 if (child_pid == 0) {
		 // 자식 프로세스 (클라이언트1)
		 msg.mtype = 1;

		 while (1) {
			 printf("클라이언트1: ");
			 fgets(msg.mtext, sizeof(msg.mtext), stdin);
			 
			 // 메시지 큐에 메시지 전송
			 if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
				 perror("msgsnd 실패");
				 exit(EXIT_FAILURE);
			 }
		 }
	 } else {
	// 부모 프로세스 (클라이언트2)
	 msg.mtype = 2;
        
	 while (1) {
		 // 메시지 큐에서 메시지 수신
	
		 if (msgrcv(msgid, &msg, sizeof(msg.mtext), 2, 0) == -1) {
			 perror("msgrcv 실패");
			 exit(EXIT_FAILURE);
		 }
		 printf("클라이언트2: %s", msg.mtext);
	 }

	 }

	 // 메시지 큐 제거
	 msgctl(msgid, IPC_RMID, NULL);
	 
     	 return EXIT_SUCCESS;
}

