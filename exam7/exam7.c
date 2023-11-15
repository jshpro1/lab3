#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main() {
	int pipe_fd[2]; // 0: 읽기용, 1: 쓰기용
	char message_out[BUFFER_SIZE] = "Hello, Child!";
	char message_in[BUFFER_SIZE];

	if (pipe(pipe_fd) == -1) {
		perror("파이프 생성 실패");
		exit(EXIT_FAILURE);
	}

	pid_t child_pid = fork();

	if (child_pid == -1) {
		perror("fork 실패");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0) {
		// 자식 프로세스: 파이프를 통해 메시지 수신
		close(pipe_fd[1]); // 쓰기용 파이프 닫기

		read(pipe_fd[0], message_in, sizeof(message_in));
		printf("자식 프로세스에서 받은 메시지: %s\n", message_in);

		close(pipe_fd[0]); // 읽기용 파이프 닫기
	} else {
		 // 부모 프로세스: 파이프를 통해 메시지 송신		
		close(pipe_fd[0]); // 읽기용 파이프 닫기

		write(pipe_fd[1], message_out, sizeof(message_out));

		close(pipe_fd[1]); // 쓰기용 파이프 닫기

		    }
	 return EXIT_SUCCESS;
}
