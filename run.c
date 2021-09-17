/*
run.c
指定されたパスのプログラムを実行する。
プログラムに標準入力が必要な場合は、入力する。
プログラムの実行が完了したあと、次のパス名を入力できる。

コンパイル：gcc -Wall -Wextra run.c
実行例：
$ ./a.out
commnand> /usr/bin/git add -A
commnand> /usr/bin/git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	modified:   README.md
	modified:   run.c

commnand> /usr/bin/date
Fri Sep 17 20:34:20 JST 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define MAX_ARGS 1024
void exec_execve(char *exargv[]){
    char    *exenvp[] = {NULL};
    int pid;
    pid=fork();

    if(pid==-1){
        printf("forkできないため、プログラムを実行できません。\n");
        perror("error in fork: ");
    }else if(pid==0){
        if (execve(exargv[0], exargv, exenvp) == -1) {
            printf("%sコマンドが実行できません\n", exargv[0]);
            perror("error in execve: ");
            exit(0);
        }
    }else if(pid>0){
        wait(NULL);
    }else{
        fprintf(stderr, "something wrong: E0001\n");
    }
    
}

/*
split: 文字列strを区切り文字sepで区切り、argsに各文字列の先頭のポインタを格納
区切る回数は最大でmax-2回
argsの要素数はmax個あればよい。
改行文字が入るとargsの配列の最後にNULLを格納して終了する。
max-2以上に区切り文字がある場合など以上がある場合、0、それ以外の場合1を返す。
返り値が1の場合、最後の要素にNULLが格納される。
*/
int split(char *str, char *args[], char sep, int max){
    int length; /*strの長さを格納*/
    int i; /*loop variable*/
    int arg_num=1;/*現在のargsの要素数*/

    if(max<1)return 0;/*maxが1以下のとき*/
    length = strlen(str);
    args[0]=str;
    for(i=0;i<length;i++){
        if(str[i]==sep){
            if(max<=arg_num) return 0;
            str[i]='\0';
            args[arg_num]=&str[i+1];
            arg_num++;
        }else if(str[i]=='\n'){
            if(max<=arg_num) return 0;
            str[i]='\0';
            args[arg_num]=NULL;
            arg_num++;
            return 1;
        }else if(str[i]=='\0'){
            if(max<=arg_num) return 0;
            args[arg_num]=NULL;
            arg_num++;
            return 1;
        }
    }
    return 0;
}

int main()
{
    char input[BUFSIZE];
    char *args[MAX_ARGS];
    while(1){
        printf("commnand> ");
        if(fgets(input, BUFSIZE,stdin)==NULL){
            return 0;
        }
        if((strlen(input) == BUFSIZE-1) && input[BUFSIZE-2]!='\n'){
            fprintf(stderr, "このプログラムは1行に%d文字以上入力できません。本プログラムを再起動してください。",BUFSIZE-2);
            return 1;
        }
        if(split(input, args, ' ', MAX_ARGS)){
            exec_execve(args);
        }else{
            fprintf(stderr, "引数が多すぎます。このプログラムはプログラム名を含めて引数を%d個まで受け付けます。\n", MAX_ARGS-1);
        }
    }
    return 0;
}