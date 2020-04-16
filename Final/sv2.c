#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <dirent.h>

char fileLists;

void getFiles(){
    int n=0, i=0;
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    while((dir=readdir(d))!=NULL){
        if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name, "..")){

        }else{
            n++;
        }
    }

    char *fileList[n];
    while((dir=readdir(d))!=NULL){
        if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name, "..")){

        }else{
            fileList[i]=(char*)malloc(strlen(dir->d_name)+1);
            strncpy(fileList[i],dir->d_name,strlen(dir->d_name));
            i++;
        }
    }
    rewinddir(d);

    for(int i=0;i<n;i++){
        printf("%s\t",fileList[i]);
    }
}

int main() {
    int cs, ss, cli, pid, new_socket;
    struct sockaddr_in sad, cad;
    char s[100];
    socklen_t cad_length = sizeof(cad);
    socklen_t sad_length = sizeof(sad);

    ss = socket(AF_INET, SOCK_STREAM, 0);
    cs = socket(AF_INET, SOCK_STREAM, 0);


    memset(&cad, 0, sizeof(cad));
    cad.sin_family = AF_INET;
    cad.sin_addr.s_addr = INADDR_ANY;
    cad.sin_port = htons(55551);
    bind(cs, (struct sockaddr *)&cad, cad_length);
    listen(cs, 0);

    while (1) {
        char text[100];
        cli = accept(cs, (struct sockaddr *)&cad, &cad_length);
        printf("Client connected\n");
        read(cli, &text, sizeof(text));
        write(cli, "server2", 8);
        printf("%s\n", text);

        pid = fork();
        if (pid == 0) {
            while(1){
                FILE *fp;
                int user, status;
                int i = 0;
                char fileName[100], fileContent[1000];
                printf("Waiting for client...\n");
                read(cli, &user, sizeof(user));
                switch(user){
                    case 1:
                        printf("Client request 1.GET service...\n");

                        read(cli, &fileName, sizeof(fileName));
                        fp = fopen(fileName,"r");
                        while (fgets(fileContent,1000,fp)!=NULL){
                            fscanf(fp,"%s",&fileContent[i]);
                            i++;
                        }
                        write(cli, fileContent, sizeof(fileContent));
                        printf("\n");
                        break;
                    case 2:
                        printf("Client request 2.SET service...\n");
                        read(cli,&fileName, sizeof(fileName));
                        fp = fopen(fileName,"w");
                        printf("Received file's name: %s\n", fileName);
                        read(cli,&fileContent, sizeof(fileContent));
                        fprintf(fp,"%s",fileContent);
                        fclose(fp);
                        printf("\n");
                        break;
                    case 3:
                        printf("Client request 3.DELETE service...\n");
                        read(cli,&fileName, sizeof(fileName));
                        status = remove(fileName);
                        if(status==0){
                            printf("Succesfully deleted file: %s\n", fileName);
                            write(cli,"File deletion successful!",26);
                        }else{
                            printf("Can't find file: %s... moving on\n", fileName);
                            write(cli,"No such file here!",19);
                        }
                        printf("\n");
                        break;
                    case 4:

                        break;
                    case 5:
                        printf("Client request 5.EXIT service...\n");
                        printf("\n");
                        return 0;
                    default:
                        break;
                }
            }
        }
        else {
            continue;
        }
    }
    // disconnect
    close(cli);

}
