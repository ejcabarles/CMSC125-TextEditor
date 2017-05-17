#include "../vfs/vfs_core.h"
#include "../stdlib/stdlib.h"
#include "dex_DDL.h"
// #include <stdlib.h>

void clear(){
    char editxt_prompt[256]="<editxt>";

    clrscr();
    textcolor(GREEN);
    textbackground(BLACK);
    printf("%s\n", editxt_prompt);
    textcolor(WHITE);
    textbackground(BLACK);
}

int editxt_execute(const char *str){
    char temp[512];
    char filebuffer[1024];
    char dest[1024];
    char *u;
    int command_length = 0;
    file_PCB *fp;

    //make a copy so that strtok wouldn't ruin str
    strcpy(temp,str);
    u=strtok(temp," ");

    if (u==0) return;
    command_length = strlen(u);

    if(strcmp(u, ":q")==0){
        return 0;
    }
    else if(strcmp(u, ":h")==0){
        printf("\n");
        console_execute("type /icsos/edtxthlp.txt");
    }
    else if(strcmp(u, ":c")==0){
        u=strtok(0," ");
        char c[2] = "";
        char temp[2] = "";

        fp = openfilex(u,FILE_WRITE);
        strcpy(filebuffer, "");
        fclose(fp);
        do{
            // strcpy(temp, "");
            c[0] = getch();
            printf("%c", c[0]);
          
            if (c[0] == ':'){
                strcpy(temp, c);
            }
            else if (c[0] == 'x' && temp[0] == ':'){
                fp = openfilex(u,FILE_WRITE);
                fwrite(filebuffer, strlen(filebuffer), 1, fp);
                fclose(fp);
                break;
            }
            else if (c[0] == 'u' && temp[0] == ':'){
                clear();

                if (filebuffer[strlen(filebuffer)-1] == '\n')
                    filebuffer[strlen(filebuffer)-2] = '\0';
                else
                    filebuffer[strlen(filebuffer)-1] = '\0';
                
                printf("%s", filebuffer);
                continue;
            }
            else if (c[0] == 's' && temp[0] == ':'){
                strcpy(temp, "");
                fp = openfilex(u,FILE_WRITE);
                fwrite(filebuffer, strlen(filebuffer), 1, fp);
                fclose(fp);
                clear();
                printf("File successfully saved!\n");
                filebuffer[strlen(filebuffer)-1] = '\0';
                printf("%s", filebuffer);
                continue;
            }
            else if (c[0] == 'q' && temp[0] == ':'){
                return 0;
            }
            else if (c[0] == 8){
                if (temp[0] == ':')
                    temp[0] = ' ';    
                else
                    filebuffer[strlen(filebuffer)-1] = '\0';   
            }
            else if (temp[0] == ':' && c[0] == 8){
                temp[0] = "";
                continue;
            }
            else{
                strcat(filebuffer, temp);
                strcpy(temp, "");
                strcat(filebuffer, c);
                // temp[0] = "";
            }
        }while(strcmp(temp, ":x") != 0);

        printf("\nNew file created\n");

    }
    else if(strcmp(u, ":r")==0){
        u=strtok(0," ");
        //temporary
        // if (u!=0) printf("%s\n",u);
        strcpy(filebuffer, "");
        fp = openfilex(u,FILE_READ);
        fread(filebuffer, 1024, 1, fp);
        fclose(fp);
        printf("%s", filebuffer );
    }
    else if(strcmp(u, ":e")==0){
        u=strtok(0," ");
        char c[2] = "";
        char temp[2] = "";

        fp = openfilex(u,FILE_WRITE);
        fread(filebuffer, 1024, 1, fp);
        fclose(fp);
        printf("%s", filebuffer );

        do{
            // strcpy(temp, "");
            c[0] = getch();
            printf("%c", c[0]);
          
            if (c[0] == ':'){
                strcpy(temp, c);
            }
            else if (c[0] == 'x' && temp[0] == ':'){
                fp = openfilex(u,FILE_WRITE);
                fwrite(filebuffer, strlen(filebuffer), 1, fp);
                fclose(fp);
                break;
            }
            else if (c[0] == 'u' && temp[0] == ':'){
                clear();

                if (filebuffer[strlen(filebuffer)-1] == '\n')
                    filebuffer[strlen(filebuffer)-2] = '\0';
                else
                    filebuffer[strlen(filebuffer)-1] = '\0';
                
                printf("%s", filebuffer);
                continue;
            }
            else if (c[0] == 's' && temp[0] == ':'){
                strcpy(temp, "");
                fp = openfilex(u,FILE_WRITE);
                fwrite(filebuffer, strlen(filebuffer), 1, fp);
                fclose(fp);
                clear();
                printf("File successfully saved!\n");
                filebuffer[strlen(filebuffer)-1] = '\0';
                printf("%s", filebuffer);
                continue;
            }
            else if (c[0] == 'q' && temp[0] == ':'){
                return 0;
            }
            else if (c[0] == 8){
                if (temp[0] == ':')
                    temp[0] = ' ';    
                else
                    filebuffer[strlen(filebuffer)-1] = '\0';   
            }
            else if (temp[0] == ':' && c[0] == 8){
                temp[0] = "";
                continue;
            }
            else{
                strcat(filebuffer, temp);
                strcpy(temp, "");
                strcat(filebuffer, c);
                // temp[0] = "";
            }
        }while(strcmp(temp, ":x") != 0);

        printf("\nFile successfully edited!\n");
    }

    else if(strcmp(u, ":d")==0){
        u=strtok(0," ");
        if (u!=0){
            // printf("%s\n", u);
            char *u2=strtok(0," ");
                if (u2==0)
                {
                    fp = openfilex(u,FILE_WRITE);
                    fdelete(fp);
                    printf("File deleted.\n");
                }
                else printf("Invalid parameter.\n");
        }
    }
    else if (strcmp(u,"ls")==0||strcmp(u,"dir")==0){
        int style=0, ordering = 0;
       
        u=strtok(0," ");
       
        if (u!=0)
        {
            do {           
                if (strcmp(u,"-l")==0) style=1;
                if (strcmp(u,"-oname")==0) ordering  = 0;
                if (strcmp(u,"-osize")==0) ordering  = 1;
                u=strtok(0," ");
            } while (u!=0);
        };
       
        console_ls(style, ordering);
    }
    else if(strcmp(u, "clear")==0){
        clear();
        clrscr();
    }


    return 1;
}


void editxt(){
    DEX32_DDL_INFO *myddl=0;
    fg_processinfo *myfg;
    char s[256]="";
    char c[256]="";
    char temp[256]="";
    char last[256]="";
    char editxt_prompt[256]="<editxt>";
    int flag;

    DWORD ptr;

    myddl =Dex32CreateDDL();    


    Dex32SetProcessDDL(myddl,getprocessid());
    myfg = fg_register(myddl,getprocessid());
    fg_setforeground( myfg->id );
    strcpy(last,"");

    textcolor(GREEN);
    textbackground(BLACK);
    printf("Welcome to EDITEXT\n");
    do{
        textcolor(GREEN);
        textbackground(BLACK);
        printf("%s", editxt_prompt);
        textcolor(WHITE);
        textbackground(BLACK);


        getstring(c,myddl);

        flag = editxt_execute(c);
    
        if(flag == 0) break;   
      
    }while(1);

    return;
}
