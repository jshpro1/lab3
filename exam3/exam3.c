#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SENTENCES 5
#define MAX_LENGTH 100


const char *sentences[MAX_SENTENCES] = {
    "동의대학교",
    "소프트웨어공학과",
    "리눅스",
    "시스템프로그래밍",
    "팀프로젝트"
};


void delay(int milliseconds) {
	clock_t start_time = clock();
	while (clock() < start_time + milliseconds);
}

int main() {
	srand(time(NULL));

	printf("타자 연습을 시작합니다. 준비되면 엔터 키를 눌러주세요.\n");
	getchar();  // 사용자가 엔터 키를 누를 때까지 대기

	int totalMistakes = 0;
	int totalTime = 0;

	for (int i = 0; i < MAX_SENTENCES; ++i) {
		// 랜덤 문장 선택		
      		const char *sentence = sentences[rand() % MAX_SENTENCES];
		               
		printf("타이핑할 문장: %s\n", sentence);

		// 사용자 입력 받기
		char input[MAX_LENGTH];	    
		clock_t start_time = clock();	     
		fgets(input, MAX_LENGTH, stdin);		        
		clock_t end_time = clock();

		// 타이핑 시간 계산
		int typingTime = (int)((end_time - start_time) * 1000 / CLOCKS_PER_SEC);

		
	      	// 정확도 계산	   
	 	int mistakes = 0;	             
	     	for (int j = 0; sentence[j] != '\0' && input[j] != '\0'; ++j) {		                 
		if (sentence[j] != input[j]) {                                       
			mistakes++;                             
			}
		}

		// 결과 출력
		printf("오타 횟수: %d\n", mistakes);
		printf("소요 시간: %d 밀리초\n", typingTime);

		// 전체 통계 업데이트 
       		totalMistakes += mistakes;
		totalTime += typingTime;

		delay(1000);
		}

	       // 평균 분당 타자수 계산
	        double averageTypingSpeed = ((double)totalMistakes / totalTime) * 60000;

	         printf("\n타자 연습이 종료되었습니다.\n");		     
		 printf("전체 오타 횟수: %d\n", totalMistakes);		 
	 	 printf("전체 소요 시간: %d 밀리초\n", totalTime);	
		 printf("평균 분당 타자수: %.2f\n", averageTypingSpeed);
		
		 return EXIT_SUCCESS;
}
