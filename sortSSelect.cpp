//
// Created by Lone Kriss on 2020/11/17.
//

//
// Created by Lone Kriss on 2020/11/17.
//
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/select.h>


#define MAXBUF 1024
using std::cout;
using std::cin;;
using std::endl;

void error_handle(const std::string& message){
    cout<<message<<endl;
    exit(1);
}

int main(int argc,char* argv[]){
    if(argc != 2){
        cout<<"using "<<argv[0]<< " <PORT>"<<endl;
        exit(1);
    }

    struct sockaddr_in serv_addr,clnt_addr;
    char buf[MAXBUF];
    int serv_sock,clnt_sock;
    socklen_t clnt_size;
    char ack[] ="message get!";

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handle("sock error!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //SELECT相关
    fd_set rset,copy_rset;  //设置select监视读集
    struct timeval time;
    int fd_max; //记录最大
    int fd_num;//记录select返回的套接字

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handle("bind error!");

    if(listen(serv_sock,5) == -1){
        error_handle("listen error!");
    }

    int str_len = -1;

    FD_ZERO(&rset);
    FD_SET(serv_sock,&rset);

    fd_max =serv_sock;
    while(1){
        time.tv_sec =5;
        time.tv_usec =500;
        copy_rset = rset;

        if((fd_num = select(fd_max+1, &copy_rset,NULL,NULL,&time))== -1){
            cout<<"select error!"<<endl;
            break;
        }

        if(fd_num <= 0){
            cout<<"no event happened"<<endl;
            continue;
        }

        for(int i = 0;i<fd_max+1;i++){
            if(FD_ISSET(i,&copy_rset)){
                if(i == serv_sock){
                    clnt_size = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_size);
                    if(clnt_sock == -1)
                        error_handle("accept_error");
                    FD_SET(clnt_sock,&rset);
                    if(fd_max<clnt_sock){
                        fd_max = clnt_sock;
                    }
                    cout<<"client connect: "<<clnt_sock<<endl;
                }
                else{

                    str_len = recv(i,buf,MAXBUF,0);
                    if(str_len == 0||str_len == -1){
                        FD_CLR(i,&rset);
                        close(i);
                        cout<<"close client: "<<i<<endl;
                    }else{
                        buf[str_len] = 0;
                        fputs(buf,stdout);
                        send(i,ack, sizeof(ack),0);
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}