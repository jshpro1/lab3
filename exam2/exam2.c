#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void listFilesRecursively(char *basePath) {
	   
      	DIR *dir;
	struct dirent *entry;
	struct stat fileStat;
	  
	dir = opendir(basePath);
			
	if (dir == NULL) {	
		perror("디렉토리 열기 실패");
		return;
	}
		

       	// 디렉토리 내의 파일 및 디렉토리 나열
 
      	while ((entry = readdir(dir)) != NULL) {
		char path[1024];
		snprintf(path, sizeof(path), "%s/%s", basePath, entry->d_name);
			         
	      	stat(path, &fileStat);
		
		if (S_ISDIR(fileStat.st_mode)) {
			// 디렉토리인 경우 재귀적으로 방문
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				printf("디렉토리: %s\n", path);
				listFilesRecursively(path);
			}
		} else{
			printf("파일: %s\n", path);
		}
	}
	closedir(dir);
} 

int main() {
	    char basePath[1024];

	// 현재 디렉토리를 기준으로 시작
	    if (getcwd(basePath, sizeof(basePath)) == NULL) {
		    perror("현재 디렉토리 가져오기 실패");
		    return EXIT_FAILURE;
	    }

	    printf("디렉토리 내의 파일 및 디렉토리:\n");
	    listFilesRecursively(basePath);

	    return EXIT_SUCCESS;
}
