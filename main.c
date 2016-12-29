#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_METHOD 40
#define NUM_BUFFER 130
#define NUM_BOOK 100



//struct of book
typedef struct str_book {
        int count;
        char name[NUM_METHOD];
        char auther[NUM_METHOD];
        char type[NUM_METHOD];
} str_book;


//delete useless 'n' in the last of strings
void rm_n (char *string) {
        if (string[strlen(string)-1] == '\n')
                string[strlen(string)-1] = 0;
}


//function to read file. return the number of books.
int file_read(FILE *fp,str_book *book) {
        char buf[NUM_BUFFER];
        int type1,type2;
        int count = 0;
        int i;
        //狗屎！C不允许初始化以外的字符串赋值给数组
        //并且不知道为什么结构体成员指针莫名爆炸
        //只能这样了
        char *name = (char*)malloc(sizeof(char) * NUM_METHOD);
        char *auther = (char*)malloc(sizeof(char) * NUM_METHOD);
        char *type = (char*)malloc(sizeof(char) * NUM_METHOD);

        //count will equals number of books.
        while (fgets (buf,NUM_BUFFER,fp) && buf[0] != EOF) {
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

        return count;
}


//function to list books
void file_list (int count,str_book *book) {
        int i;
        printf ("Here's book's listi:\n");
        for (i = 0;i < count;i++)
                printf ("%d. <%s> by %s, Type:%s\n"
                        ,i+1,book[i].name,book[i].auther,book[i].type);
}


//function to add book
int file_add (FILE *fp,str_book *book,int count) {
        char buf[NUM_BUFFER];

        if (count >= NUM_BOOK) {
                puts("Error!List was full!");
                return count;
        }

        printf ("Here's No.%d book to add\nName:",count+1);
        fgets (book[count].name,NUM_METHOD,stdin);
        rm_n (book[count].name);
        printf ("Auther:");
        fgets (book[count].auther,NUM_METHOD,stdin);
        rm_n (book[count].auther);
        printf ("Type:");
        fgets (book[count].type,NUM_METHOD,stdin);
        rm_n (book[count].type);

        book[count].count = count + 1;
        
        sprintf (buf,"%s-%s-%s\n"
                 ,book[count].name,book[count].auther,book[count].type);
        fputs (buf,fp);

        return ++count;
}


//main function
int main (int argc,char *argv[]) {
        str_book book[NUM_BOOK];
        FILE *fp;
        char newarg;
        int count;

        if (argc != 2) {
                puts ("Error!No or too much arguments");
                return 1;
        }
        if ((fp = fopen(argv[1],"r+")) == NULL) {
                printf ("Fail to open the file %s\n",argv[1]);
                return 1;
        }

        printf ("#########The Books Manager#########\n"
                "r:read l:list a:add d:delete q:quit\n"
                "###################################\n");

        while (1) {
                printf(">");
                scanf ("%c",&newarg);
                getchar();

                switch (newarg) {
                        case 'r': 
                                count = file_read (fp,book);
                                break;
                        case 'l':
                                file_list (count,book);
                                break;
                        case 'a': 
                                count = file_add (fp,book,count);
                                break;
                        /*
                        case 'd': file_delete; break;
                        */
                        case 'q': return 0;
                        default: puts("Error!Arguments Exception!");
                }
        }

        return 0;
}
