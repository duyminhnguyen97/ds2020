#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define MAXCHAR 1000

int main() {
    int ss, cli, pid;
    int result;
    struct sockaddr_in ad;

    socklen_t ad_length = sizeof(ad);
    // create the socket
    ss = socket(AF_INET, SOCK_STREAM, 0);
    // bind the socket to port 12345
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = INADDR_ANY;
    ad.sin_port = htons(12331);
    bind(ss, (struct sockaddr *)&ad, ad_length);
    // then listen
    listen(ss, 0);
    while (1) {
        // an incoming connection
        cli = accept(ss, (struct sockaddr *)&ad, &ad_length);
        pid = fork();
        if (pid == 0) {
            // I'm the son, I'll serve this client
            printf("client connected\n");
            while (1) {
                FILE *fp;
                char s[MAXCHAR];
                fp = fopen("serverReceive.txt","w");
                if (fp == NULL){
                    printf("Could not open file");
                }
                // it's client turn to chat, I wait and read message from client
                recv(cli, s, sizeof(s), 0);
                printf("client says: %s\n",s);
                fprintf(fp,"%s\n",s);
                fclose(fp);


                // now it's my (server) turn

                char *filename;
                int i=0;
                printf("server>");
                scanf("%s", filename);
                fp = fopen(filename,"r");
                if (fp == NULL){
                    printf("Could not open file %s",filename);
                }
                while (fgets(s,MAXCHAR,fp)!=NULL){
                    fscanf(fp,"%s",&s[i]);
                    i++;
                }
                fclose(fp);
                send(cli,&s,sizeof(s),0);
            }
            return 0;
        }
        else {
            // I'm the father, continue the loop to accept more clients
            continue;
        }
    }
    // disconnect
    close(cli);

}
