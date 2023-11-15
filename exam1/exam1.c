#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
	DIR *directory;
	struct dirent *entry;

	directory = opendir(".");
	
	if (directory == NULL) {
		perror("디렉토리 열기 실패");
		return EXIT_FAILURE;
	}
		    
	// 디렉토리 내의 파일 목록 읽기
	printf("현재 디렉토리의 파일 목록:\n");
	
	while ((entry = readdir(directory)) != NULL) {
		printf("%s\n", entry->d_name);
	}
		    
	// 디렉토리 닫기
	closedir(directory);
	
	return EXIT_SUCCESS;
}
