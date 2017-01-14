#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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


//NOTE:"file_" FUNCTION TO CHANGE FILE, "book_" FUNCTION TO CHANGE STRUCT
//function to read file. return the number of books.
int file_read(FILE *fp,str_book *book) {
        char buf[NUM_BUFFER];
        int type1,type2;
        int count = 0;
        int i;
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

        return count;
}


//function to write file
void file_write (FILE *fp,str_book *book,int count,char flag) {
        int i;

        if (flag = 'r') {
                rewind (fp);
                ftruncate (fileno(fp),0);
                for (i = 0;i < count;i++) {
                        fprintf (fp,"%s-%s-%s\n"
                                 ,book[i].name,book[i].auther,book[i].type);
                }
                puts ("File written");
        } else if (flag = 'a') {
                fprintf (fp,"%s-%s-%s\n"
                         ,book[count].name,book[count].auther,book[count].type);
                puts ("File written");
        } else {
                puts ("Error:Exaccept flag!");
        }
}
                
        

//function to add book
int book_add (FILE *fp,str_book *book,int count) {
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

        book[count].count = count+1;
        count ++;

        file_write (fp,book,count,'a');

        return count;
}


//function to list books
void book_list (int count,str_book *book) {
        int i;

        printf ("Here's book's list:\n");
        for (i = 0;i < count;i++)
                printf ("%d. <%s> by %s, Type:%s\n"
                        ,i+1,book[i].name,book[i].auther,book[i].type);
}


//function to delete book
int book_delete (FILE *fp,str_book *book,int count) {
        int num_delete,i;
        str_book book_bak[NUM_BOOK];

        printf ("Which number of book do you want to delete?\n>");
        scanf ("%d",&num_delete);
        while (getchar() != '\n');
        
        if ( num_delete > count ) {
                printf ("Error:No such book\n");
                return count;
        }

        for (i = 0 ; i < count ; i++) {
                book_bak[i] = book[i];
        }
        for (i = num_delete-1 ; i < count ; i ++) {
                book[i].count --;
                book[i] = book_bak[i+1];
        }
        count --;
        
        file_write (fp,book,count,'r');

        return count;
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

        printf ("Book Manager\n");
        count = file_read (fp,book);
        printf ("%d books has read from %s.\n",count,argv[1]);

        while (1) {
                printf(">");
                newarg = getchar();
                while (getchar() != '\n');

                switch (newarg) {
                        case 'r': 
                                count = file_read (fp,book);
                                break;
                        case 'l':
                                book_list (count,book);
                                break;
                        case 'a': 
                                count = book_add (fp,book,count);
                                break;
                        case 'd':
                                count = book_delete (fp,book,count);
                                break;
  
                        case 'q': return 0;
                        default: puts("Error!Arguments Exception!");
                }
        }

        return 0;
}
