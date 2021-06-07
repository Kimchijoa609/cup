#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_SIZE 255

void insert(FILE *fp, FILE* fp2 ,int i ,char*buf){ // fp2에 값 입력


	for(int j=i; j<strlen(buf)-1;j++){
             fprintf(fp2,"%c",buf[j]);
           }
}

int find_index(FILE* fp, FILE* fp2,char* buf){ // ':' 전까지의 i 값 반환 

	for(int i=0;i < strlen(buf)-1;i++){
		if(buf[i+1]==':')
			return i;
	}
}


void ReadnWrite(FILE * fp ,FILE * fp2){
	char buf[MAX_SIZE];
	int start =0;	 
	int index;

	while(fgets(buf,sizeof(buf),fp)!=NULL){  
		//줄마다 읽고 항목을 strncmp 함수를 통해 검사 및 저장

		if(strncmp(buf,"ID:",3)==0){ // id 저장
			insert(fp,fp2,4,buf);
			fprintf(fp2,"/");
			continue;
      }
		if(strncmp(buf,"NAME:",5)==0){ // 이름 저장
			insert(fp,fp2,6,buf);
      			fprintf(fp2,"/");
      			continue;
      }

		if(strncmp(buf,"GENDER:",7)==0){ // 성별 저장
			if(buf[8]='F'){
			 fprintf(fp2,"F/");
			}else
			 fprintf(fp2,"M/");
		         continue;
    }

		if(strncmp(buf,"AGE:",4)==0){ // 나이 저장
			insert(fp,fp2,5,buf);
			fprintf(fp2,"/");
			continue;
		}
		if(strncmp(buf,"HP:",3)==0){ // HP 저장
			insert(fp,fp2,4,buf);
			fprintf(fp2,"/");
      continue;
    }

		if(strncmp(buf,"MP:",3)==0){ // MP 저장
      insert(fp,fp2,4,buf);
      fprintf(fp2,"/");
      continue;
		}
		if(strncmp(buf,"COIN:",5)==0){ // COIN 저장
      insert(fp,fp2,6,buf);
      fprintf(fp2,"/");
      continue;
     }

		/*-----------item-----------*/


		if(strncmp(buf,"BOMB:",5)==0){ // COIN 저장
			fprintf(fp2,"BM/");
      insert(fp,fp2,6,buf);
      fprintf(fp2,"/");
        continue;
		}else if(strncmp(buf,"POTION:",7)==0){ // POTION 저장
      fprintf(fp2,"PN/");
      insert(fp,fp2,8,buf);
      fprintf(fp2,"/");
        continue;
		}else if(strncmp(buf,"CURE:",5)==0){ // CURE 저장
      fprintf(fp2,"CR/");
      insert(fp,fp2,6,buf);
      fprintf(fp2,"/");
        continue;
    }else if(strncmp(buf,"CANNON:",7)==0){ // CANNON 저장
      fprintf(fp2,"CN/");
      insert(fp,fp2,8,buf);
      fprintf(fp2,"/");
        continue;
    }else if(strncmp(buf,"BOOK:",5)==0){ // BOOK 저장
      fprintf(fp2,"BK/");
      insert(fp,fp2,6,buf);
      fprintf(fp2,"/");
        continue;
    }else if(strncmp(buf,"SHIELD:",7)==0){ // SHIELD 저장
      fprintf(fp2,"SD/");
      insert(fp,fp2,8,buf);
      fprintf(fp2,"/");
        continue;
    }

	  /*--------friends list------*/

		if(strncmp(buf,"*FRIENDS LIST*",7)==0){ //
      fprintf(fp2,"@/");	
			continue;
    }if(strncmp(buf,"FRIEND",6)==0){  
			index=find_index(fp,fp2,buf);   // find_index 함수를 통해 index 값 구하고switch문 실행 ex) friend1 id의 인덱스는 9
			switch(index){ // gender 부분을 제외하고는 동일하게 처리
				case 9: //id
				case 11: //name
				case 10: //age
					insert(fp,fp2,index+3,buf);
					fprintf(fp2,"/");
					break;
				case 13: //gender
					if(buf[16]=='F'){
						fprintf(fp2,"F/");
						break;	
					}else
						fprintf(fp2,"M/");
						break;
			}
			continue;
    }



		/*-------description---------*/

		if(strncmp(buf,"*DESCRIPTION*",13)==0){ // 
			fprintf(fp2,"@/");
			start++; // *DESCRIPTION* 부분을 만나면 start 1 증가 
			continue;
		}
		if(start>0){ // *DESCRIPTION* 부분을 만난 후라면 반복문을 통해 저장
		for(int k=0;k<strlen(buf)-1;k++){
				fprintf(fp2,"%c",buf[k]);
		}
		fprintf(fp2,"/");
		}
	}
	
}

void nonIntelligenceCopy(char* filename){
	
	// 파일을 끝까지 읽고 여섯 번 복사해서 저장

	FILE* fp = fopen(filename,"r");
	int i =0;
	int len;
	char buf[3000];
	while(!feof(fp)){
		buf[i] = fgetc(fp);
		i++;
	}
	fclose(fp);

	fopen(filename,"w");
	len = strlen(buf);
	for(int i = 0;i<6;i++)
	{	
		fwrite(buf,1,len-2,fp);	
		fputc('\n',fp);
	}
	fclose(fp);

	return;
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
	
	nonIntelligenceCopy(argv[2]);

	return 0;
}
