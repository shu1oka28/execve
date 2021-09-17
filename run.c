#include <stdio.h>
#include <unistd.h>

int main()
{
    char    command[] = "/usr/bin/date";
    char    *exargv[] = {"date",  NULL};
    char    *exenvp[] = {NULL};
    int     return_code = 0;

    if (execve(command, exargv, exenvp) == -1) {
        printf("%sコマンドが実行できませんでした\n", command);
        perror("peeor:error");
        return_code = 1;
    }
    return return_code;
}