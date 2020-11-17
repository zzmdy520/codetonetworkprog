
// Created by Lone Kriss on 2020/11/17.
//
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <memory.h>

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

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handle("sock error!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handle("bind error!");

    if(listen(serv_sock,5) == -1){
        error_handle("listen error!");
    }

    clnt_size = sizeof(clnt_addr);
    int str_len = -1;

        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_size);
        if(clnt_sock == -1)
            error_handle("accept_error");

        str_len = recv(clnt_sock,buf, MAXBUF,0);
        fputs(buf, stdout);
        close(clnt_sock);
        close(serv_sock);

    return 0;
}
