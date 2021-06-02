#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_SIZE 255

int insert(FILE *fp, FILE* fp2 ,int i ,char*buf){

	int count=0;

	for(int j=i; j<strlen(buf)-1;j++){
             fprintf(fp2,"%c",buf[j]);
             count++;
           }
	return count;
}


void ReadnWrite(FILE * fp ,FILE * fp2){
	char buf[MAX_SIZE];
	int count ; // 길이 구하는 칭구
	int start =0;	
	int length =0; 
	while(fgets(buf,sizeof(buf),fp)!=NULL){
		count =0; //줄마다 검사 후 다시 초기화
		

		if(strncmp(buf,"ID:",3)==0){ // id 저장
 			printf("ID 발견\n");
			length=insert(fp,fp2,4,buf);
			fprintf(fp2,"@%d/",length);
			continue;
      }
		if(strncmp(buf,"NAME:",5)==0){ // 이름 저장
      printf("이름 발견\n");
			length=insert(fp,fp2,6,buf);
      fprintf(fp2,"@%d/",length);
      continue;
      }

		if(strncmp(buf,"GENDER:",7)==0){ // 성별 저장
      printf("성별 발견\n");
			if(buf[8]='F'){
			 fprintf(fp2,"F/");
			}else
			 fprintf(fp2,"M/");
      continue;
    }

		if(strncmp(buf,"AGE:",4)==0){ // 나이 저장
			printf("나이 발견\n");
			length=insert(fp,fp2,5,buf);
			fprintf(fp2,"/");
			continue;
		}
		if(strncmp(buf,"HP:",3)==0){ // HP 저장
      printf("HP 발견\n");
			insert(fp,fp2,4,buf);
			fprintf(fp2,"/");
      continue;
    }

		if(strncmp(buf,"MP:",3)==0){ // MP 저장
			printf("MP 발견\n");
      insert(fp,fp2,4,buf);
      fprintf(fp2,"/");
      continue;
		}
		if(strncmp(buf,"COIN:",5)==0){ // COIN 저장
      printf("COIN 발견\n");
      insert(fp,fp2,6,buf);
      fprintf(fp2,"/");
      continue;
     }
		if(strncmp(buf,"*DESCRIPTION*",13)==0){ // 자기소개 저장
			printf("같아요!\n");
			start++;
			continue;
		}
		if(start>0){
		for(int k=0;k<strlen(buf)-1;k++){
				fprintf(fp2,"%c",buf[k]);
				count++;
		}
		fprintf(fp2,"@%d/",count);
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
