#include <stdio.h>
#include "get_next_line_bonus.h"
int main(void)
{
    int fd;
    fd = open("test",O_RDONLY);
    int fd1;
    fd1 = open("test2",O_RDONLY);
    char *st1 = get_next_line(fd1);
    char *st = get_next_line(fd);
    int i = 1;
   while (st || st1)
    {
       
        printf("line [%d] fd[%d]:%s",i,fd,st);
        
       printf("line [%d] fd[%d]:%s",i,fd1,st1);
        free(st);
         
        free(st1);
        st = get_next_line(fd);
        st1 = get_next_line(fd1);
        i++;
    }
    /*st = get_next_line(fd);
    printf("line [%d]:%s",i,st);*/
    close(fd);
   
   
    close(fd1);
   // system("leaks a.out");

}
