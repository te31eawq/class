#include <unistd.h> 	/* 유닉스 표준(UNIX Standard) 시스템 콜을 위한 헤더 파일 */
#include <fcntl.h>
#include <stdio.h> 	/* perror() 함수 */
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

//int main(int argc, char* argv[])
int main(int argc, char** argv)
{
    int n, in, out;
	int i,j;
    char buf[1024];
/*
	printf("argc : %d\n",argc);
	for(i=0;i<argc;i++)
	{
		printf("i:%d, argv[%d]: %s\n",i,i,argv[i]);
		for(j=0;j<strlen(argv[i]);j++)
			printf("i:%d,j:%d argv[%d][%d]:%c\n",i,j,i,j,argv[i][j]);
	}


	i=0;
	for(i=0;i<argc;i++)
	{
		printf("%s\n",argv[i]);
		for(j=0;j<strlen(argv[i]);j++)
		{
			printf("%c\n",*(*(argv+i)+j));
		}
	}
*/
    /* 명령행 인수로 복사할 파일명이 없는 경우에 에러를 출력하고 종료한다. */
    if (argc < 3) {
		printf("Usage : %s file1 file2\n",argv[0]);        
        return -1;
    }
	if(argc == 4 && argv[1][0] == '-')
	{
		if(argv[1][1] == 'l')
			printf("option : -l\n");
		else if(argv[1][1] == 'a')
			printf("option : -a\n");
		else
			printf("잘못된 옵션\n");
	}
	else
		printf("옶션 없는 명령 \n");


    /* 복사의 원본이 되는 파일을 읽기 모드로 연다. */
    if ((in = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);

        return -1;
    }

    /* 복사할 결과 파일을 쓰기 모드(새로운 파일 생성 | 기존에 파일 내용 지움)로 연다. */
//    if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) {
//    if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH)) < 0) {
    if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0) {
        perror(argv[2]);
        return -1;
    }

    /* 원본 파일의 내용을 읽어서 복사할 파일에 쓴다. */
    while ((n = read(in, buf, sizeof(buf))) > 0)
        write(out, buf, n);

    /* 열린 파일들을 닫는다. */
    close(out);
    close(in);

    /* 프로그램의 정상 종료 시 0을 반환한다. */
    return 0;
}