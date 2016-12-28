#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//struct of book
typedef struct s_book {
        int count;
        char name[40];
        char auther[40];
        char type[40];
} s_book;


//delete useless 'n' in the last of strings
void rm_n (char *string) {
        if (string[strlen(string)-1] == '\n')
                string[strlen(string)-1] = 0;
}


//how to use:file_functions("file pointer","struct")
void file_read(FILE *fp,s_book *book) {
        char buf[130];
        int type1,type2;
        int count = 0;
        int i;
        //狗屎！C不允许初始化以外字符串赋值给数组
        //并且不知道为什么结构体成员指针莫名爆炸
        //只能这样了
        char *name = (char*)malloc(sizeof(char) * 40);
        char *auther = (char*)malloc(sizeof(char) * 40);
        char *type = (char*)malloc(sizeof(char) * 40);

        while (fgets (buf,130,fp) && buf[0] != EOF) {
                rm_n (buf);

                book[count].count = count + 1;
                name = strtok(buf,"-");
                auther = strtok(NULL,"-");
                type = strtok(NULL,"-");

                strcpy(book[count].name,name);
                strcpy(book[count].auther,auther);
                strcpy(book[count].type,type);

                count ++;
        }
        printf ("Read %u books\n",count);

        for (i = 0;i < count;i++)
                printf ("%d. <%s> by %s , Type:%s\n"
                ,i+1,book[i].name,book[i].auther,book[i].type);
}


//main function
int main (int argc,char *argv[]) {
        s_book book[100];
        FILE *fp;
        char newarg;

        if (argc != 2) {
                puts ("Error!No or too much arguments");
                return 1;
        }
        if ((fp = fopen(argv[1],"r+")) == NULL) {
                printf ("Fail to open the file %s\n",argv[1]);
                return 1;
        }

        printf ("######The Books Manager#######\n"
                "r:read a:add d:delete q:quit\n"
                "##############################\n"
                ">");
        scanf ("%c",&newarg);

        //
        switch (newarg) {
                case 'r': file_read(fp,book); break;
                /*
                case 'a': file_add(); break;
                case 'd': file_delete; break;
                */
                case 'q': return 0;
                default: puts("Error!Arguments Exception!");
        }

        fclose (fp);
        return 0;
}
