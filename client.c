#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#define MAXCHAR 1000

int main(int argc, char* argv[]) {
    int so;

    struct sockaddr_in ad;
    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;
    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    // init address
    hep = gethostbyname(argv[1]);
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(12331);
    // connect to server
    connect(serv, (struct sockaddr *)&ad, ad_length);
    while (1) {
        // after connected, it's client turn to chat
        FILE *fp;
        char s[MAXCHAR];
        char *filename;
        int i=0;
        // send some data to server
        printf("client>");
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
        send(serv,&s,sizeof(s),0);



        // then it's server turn
        fp = fopen("clientReceive.txt","w");
        if (fp == NULL){
            printf("Could not open file");
        }
        recv(serv, s, sizeof(s), 0);
        fprintf(fp,"%s\n",s);
        fclose(fp);
        printf("server says: %s\n", s);
        memset(s,0,MAXCHAR);
    }
}
