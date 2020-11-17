//
// Created by Lone Kriss on 2020/11/17.
//
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <cstdio>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <memory>

#define MAXBUF 1024
using std::cout;
using std::cin;;
using std::endl;

void error_handle(const std::string& message){
    cout<<message<<endl;
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc != 3){
        cout<<"using "<<argv[0]<<"<IP> "<<"<PORT> "<<endl;
    }


    int sock;
    struct sockaddr_in serv_addr;
    char buf[MAXBUF];

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handle("sock error!");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
        error_handle("connect error!");

    while(1){
        fputs("Input your choose:(Q to quit)",stdout);
        fgets(buf, MAXBUF, stdin);
        send(sock, buf, strlen(buf),0);

    }
    close(sock);
    return 0;
}