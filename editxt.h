#include "../vfs/vfs_core.h"
// #include <stdlib.h>

int editxt_execute(const char *str){
    char temp[512];
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
        //temporary
        // if (u!=0) printf("%s\n",u);
        fp = openfilex(u,FILE_APPEND);
        fclose(fp);
        printf("New file created\n");
    }
    else if(strcmp(u, ":r")==0){
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
                else
               printf("Invalid parameter.\n");
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


    return 1;
}



void editxt(){
    DEX32_DDL_INFO *myddl=0;
    fg_processinfo *myfg;
    char s[256]="";
    char c[256]="";
    char temp[256]="";
    char last[256]="";
    char editxt_prompt[256]="/editxt/";
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




