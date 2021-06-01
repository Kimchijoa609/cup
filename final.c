#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_SIZE 255

void ReadnWrite(FILE * fp ,FILE * fp2){
	char buf[MAX_SIZE];
	int count ; // 길이 구하는 칭구
	int start =0;	
	while(fgets(buf,sizeof(buf),fp)!=NULL){
		count =0; //줄마다 검사 후 다시 초기화
		for(int i = 0; i< strlen(buf)+1;i++){

			if(buf[i]==':'){
				  i++;	
					for(int j = i+1 ; j < strlen(buf)-1; j++){		
						fprintf(fp2,"%c",buf[j]);
						count++;
					}
					fprintf(fp2,"/%d/",count);
					break;
			}
		}
		if(strncmp(buf,"*DESCRIPTION*",13)==0){
				printf("같아요!\n");
				start++;
				continue;
		}
		if(start>0){
		for(int k=0;k<strlen(buf)-1;k++){
				fprintf(fp2,"%c",buf[k]);
				count++;
		}
		fprintf(fp2,"/%d/",count);
		}

	}
	
}


int main(int argc, char* argv[]){


	FILE * fp = fopen(argv[1],"rt");  //읽기모드로 파일 열기
	FILE * fp2 = fopen(argv[2], "wt"); // 쓰기모드로 파일 열기

	if(argc!= 3){  
		fprintf(stderr,"usage) %s source_file target_file!\n",argv[0]);
		exit(-1);
	}

	if(fp == NULL){ // 파일 열기 실패 시
     fprintf(stderr,"Cannot open file %s \n",argv[1]);
     exit(-1);
   }

	ReadnWrite(fp,fp2);

	fclose(fp);
	fclose(fp2);

	return 0;
}
