#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    char s0[100], s1[100], ip0[]="192.168.1.142", ip1[]="192.168.0.105";
    struct sockaddr_in ad0, ad1;
    int serv0 = socket(AF_INET, SOCK_STREAM, 0);
    int serv1 = socket(AF_INET, SOCK_STREAM, 0);

    //sv1
    memset(&ad0, 0, sizeof(ad0));
    ad0.sin_family = AF_INET;
    ad0.sin_port = htons(55555);
    if(inet_pton(AF_INET,ip0, &ad0.sin_addr) <= 0){
        printf("Failed to connect to server 1, incorrect IP");
        return -1;
    }else{
        connect(serv0, (struct sockaddr *)&ad0, sizeof(ad0));
        write(serv0, "Hello from client", 18);
        read(serv0, s0, sizeof(s0));
        printf("client connected to server: %s\n", s0);
    }


    //sv2
    memset(&ad1, 0, sizeof(ad1));
    ad1.sin_family = AF_INET;
    ad1.sin_port = htons(55551);
    if(inet_pton(AF_INET,ip1, &ad1.sin_addr) <= 0){
        printf("Failed to connect to server 2, incorrect IP");
        return -1;
    }else{
        connect(serv1, (struct sockaddr *)&ad1, sizeof(ad1));
        write(serv1, "Hello from client", 18);
        read(serv1, s1, sizeof(s1));
        printf("Client connected to server: %s\n", s1);
    }

    while (1) {
        FILE *fp;
        int user, choice;
        uint32_t xd;
        char test[100], fileName[100], fileContent[1000];
        printf("What u wanna do: 1.GET/ 2.SET/ 3.DELETE/ 4.LIST/ 5.EXIT\n");
        scanf("%d", &user);
        if(user == 1){
            printf("User chosen 1.GET...\n");
            printf("From which server do you wanna take from? 1/2: ");
            scanf("%d", &choice);
            if(choice == 1){
                write(serv0, &user, sizeof(user));
            }
            if(choice == 2){
                write(serv1, &user, sizeof(user));
                user = 6;
            }
        }else if(user != 6){
            write(serv0, &user, sizeof(user));
            write(serv1, &user, sizeof(user));
        }
        switch(user){
            case 1:

                //LIST ALL FILES HERE!!

                printf("Type in file's name: ");
                scanf("%s", fileName);
                write(serv0, fileName, sizeof(fileName));
                read(serv0, &fileContent, sizeof(fileContent));
                fp = fopen(fileName,"w");
                fprintf(fp,"%s",fileContent);
                printf("Client received the file: %s", fileName);
                fclose(fp);

                printf("\n\n");
                break;
            case 2:
                printf("User chosen 2.SET...\n");
                printf("Please enters the file's name: ");
                scanf("%s", fileName);
                write(serv0, fileName, sizeof(fileName));
                write(serv1, fileName, sizeof(fileName));
                printf("Write the file's contents: ");
                scanf("%s", fileContent);
                write(serv0, fileContent, sizeof(fileContent));
                write(serv1, fileContent, sizeof(fileContent));
                printf("\n");
                break;
            case 3:
                printf("User chosen 3.DELETE...\n");
                printf("Please enters the file's name: ");
                scanf("%s", fileName);
                write(serv0, fileName, sizeof(fileName));
                read(serv0, &test, sizeof(test));
                write(serv1, fileName, sizeof(fileName));
                read(serv1, &test, sizeof(test));
                printf("%s\n",test);
                printf("\n");
                break;
            case 4:
                printf("User chosen 4.LIST...\n");
                printf("User's currently connected to: %s and %s\n", s0, s1);
                printf("Server 1 IP: %s\n", ip0);
                printf("Server 2 IP: %s\n", ip1);
                printf("\n");
                break;
            case 5:
                printf("User chosen 5.EXIT...\n");
                printf("\n");
                return 0;
            case 6:
                printf("Type in file's name2: ");
                scanf("%s", fileName);
                write(serv1, fileName, sizeof(fileName));
                read(serv1, &fileContent, sizeof(fileContent));
                fp = fopen(fileName,"w");
                fprintf(fp,"%s",fileContent);
                printf("Client received the file: %s", fileName);
                fclose(fp);

                printf("\n");
                break;
            default:
                printf("What?\n");
                printf("\n");
                break;
        }
    }
}
