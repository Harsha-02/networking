#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SIZE 4 
#define MAX_FRAME_SIZE 20
int main()
{
    printf("server\n");
    int sfd,lfd,i,j,status;
    socklen_t len;
    char str[MAX_FRAME_SIZE],frame[MAX_FRAME_SIZE],temp[MAX_FRAME_SIZE],ack[MAX_FRAME_SIZE];
    struct sockaddr_in saddr,caddr;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd<0)
    {
        perror("Socket creation error");
        exit(1);
    }
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=htonl(INADDR_ANY);
    saddr.sin_port=htons(5000);
    if(bind(sfd,(struct sockaddr*)&saddr,sizeof(saddr))<0)
    {
        perror("BIND ERROR");
        exit(1);
    }
    if(listen(sfd,5)<0)
    {
        perror("Listen error");
        exit(1);
    }
    len=sizeof(caddr);
    lfd=accept(sfd,(struct sockaddr*)&caddr,&len);
    printf("enter the text to send ");
    scanf("%s",str);
    i=0;
    printf("\n\n");
    while(i<strlen(str))
    {
        memset(frame,0,MAX_FRAME_SIZE);
        strncpy(frame,str+i,SIZE);
        len=strlen(frame);
        for(j=0;j<len;j++)
        {
            sprintf(temp,"%d",i+j);
            strcat(frame,temp);
        }
        printf("Frame transmitted : %s\n ",frame);
        write(lfd,frame,sizeof(frame));
        read(lfd,ack,MAX_FRAME_SIZE);
        sscanf(ack,"%d",&status);
        if(status==-1)
        {
            printf("transmission is successful.\n");
            i+=SIZE;
        }
        else
        {
            printf("Received error in %d \n",status);
            i=status;
        }
        printf("\n");
        
    }
    write(lfd,"exit",sizeof("exit"));
    printf("Exiting\n");
    sleep(2);
    close(lfd);
    close(sfd);
    return 0;

}
