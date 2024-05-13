#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
void addBook(void);
void del(void);
void booksList(void);
void issueBook(void);
void issueList(void);
void searchbooks(void);
void updatebooks(void);
void close(void);



struct books{
    int ID;
    char bookName[50];
    char authorName[50];
    char Quantity;
    char Price;
    char rackno;
    char date[12];
}b;

struct student{
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
}s;

FILE *fp;

int main(){

    int ch;


    while(1)
	{
        system("cls");
        printf("\n");	
		printf("\n");
		printf("\n               ****************************** MAIN MENU ******************************");
		printf("\n               ***********************************************************************");

    		
		printf("\n");
		printf("\n               ====== [1]. Add Books   ");
		
		printf("\n");
		printf("\n               ====== [2]. View Book list");
		
		printf("\n");
		printf("\n               ====== [3]. Delete Books");
		
		printf("\n");
		printf("\n               ====== [4]. Issue Books");
		            
		printf("\n");
		printf("\n               ====== [5]. Issue List");
		
		printf("\n");
		printf("\n               ====== [6]. Search Books");
		
		printf("\n");
		printf("\n               ====== [7]. Update Books");
	
		printf("\n");
		printf("\n               ====== [8]. Close ");
		
		printf("\n");
		printf("\n               ***********************************************************************");
		printf("\n               ***********************************************************************");
		
		printf("\n");
		printf("\n               Enter your choice:");
        scanf("%d", &ch);

    switch(ch)
		{

	        case 1:
	            addBook();
	            break;
	
	        case 2:
	            booksList();
	            break;
	
	        case 3:
	            del();
	            break;
	
	        case 4:
	            issueBook();
	            break;
	
	        case 5:
	            issueList();
	            break;
	        case 6:
	        	searchbooks();
	        	break;
	        case 7:
	        	updatebooks();
	        	break;
	        case 8:
	        {
					
		        	system("cls");
				
				printf("\n          Library Management System");
				printf("\n          Project in C");
				printf("\n");
				printf("\n     ******************************************");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n     *******************************************");
				printf("\n");
				printf("     *******************************************");
				printf("\n");
				printf("     ********************************************");
				printf("\n");
				printf("Exiting in 3 second...........>");
				//flushall();
			
				exit(0);
			}	
	        default:
	            printf("\n      Wrong Entry!!Please re-entered correct option");

        }
        printf("\n            - Press Any Key To Continue........");
        getch();
    }

    return 0;
}


void addBook()
{
    system("cls");
    fp = fopen("Filebooks.txt", "ab+");
	
	printf("\n                          Enter the Information Below");
	printf("\n                ************************************************");
	printf("\n                ************************************************");
	printf("\n                         Book ID: ");
	scanf("%d",&b.ID);
	printf("                         Book Name: ");
	scanf("%s",&b.bookName);
	printf("                         Author: ");
	scanf("%s",&b.authorName);
	printf("                         Quantity: ");
	scanf("%d",&b.Quantity);
	printf("                         Rack No: ");
	scanf("%d",&b.rackno);
	
	fwrite(&b,sizeof(b),1,fp);
	fclose(fp);
        printf("\n               The record is sucessfully saved");
		printf("\n               Save any more?(Y / N)");
	    
		if(getch()=='n')
	    	 main();
	    else
		    system("cls");
		    addBook();
		

}

void booksList()
{
	int i=0;
    system("cls");
    printf("\n*********************************Book List*****************************\n");
	printf("%-10s %-30s %-20s %-30s %s", "ID", "Book Name", "Author", "Quantity", "Rackno");
    fp = fopen("Filebooks.txt", "rb");
    while(fread(&b,sizeof(b),1,fp))
	{
        printf("\n%-10d %-30s %-20s %-30d %d", b.ID, b.bookName, b.authorName, b.Quantity, b.rackno);
		i=i+b.Quantity;
    }
    printf("\n");   
    printf("\n");
    printf("\n");
	printf("\n                  Total Books =%d",i);
    fclose(fp);
}

void del()   //function that delete items books from file
{
    int id, f=0;
    system("cls");
    printf("\n       ============ Delete Books ============");
    printf("\n       ======================================");
    printf("\n");
    printf("\n       Enter Book ID to delete: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("Filebooks.txt", "rb");
    ft = fopen("Newfile.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1)
	{
        if(b.ID==id)
		{
            f=1;
        } else
			{
            	fwrite(&b, sizeof(b), 1, ft);
        	}
    }

    if(f==1)
	{
        printf("\n   Deleted Successfully.");
    } else
		{
        	printf("\n  Record Not Found !");
    	}

    fclose(fp);
    fclose(ft);

    remove("Filebooks.txt");
    rename("Newfile.txt", "Filebooks.txt");

}


void issueBook(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
    printf("       =========== Issue Books ===========");
	printf("\n       ===================================");
	printf("\n");
    printf("\n     *Enter Book id to issue: ");
    scanf("%d", &s.id);

    //Check if we have book of given id
    fp = fopen("Filebooks.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.ID == s.id)
		{
            strcpy(s.bookName, b.bookName);
            f=1;
            break;
        }
    }

    if(f==0)
	{
        printf("\n    No book found with this id\n");
        printf("\n    Please try again...\n");
        return ;
    }

    fp = fopen("Issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList()
{
    system("cls");
    printf("\n                           =================== Book Issue List  ===================");
	printf("\n                           ========================================================");
	printf("\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("Issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1)
	{
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}
void searchbooks()
{
	system("cls");
	int d;
	printf("\n");
	printf("\n");
	printf("\n          ***************Search Books***************");
	
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n          ===== 1. Search by ID");
	
	printf("\n");
	printf("\n");
	printf("\n          ===== 2. Search by Name");
	
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n       Enter Your Choice: ");
	fp=fopen("Filebooks.txt","r+");//open file for reading propose
	rewind(fp);                   // move pointer at the begining of file
	switch(getch())
    	{
		case '1':
			{
				system("cls");
				printf("\n        ******Search Book by ID******");
				printf("\n");
				printf("\n");
				printf("\n     Enter the Book ID: ");
				scanf("%d", &d);
				printf("\n     Searching..............");
				while(fread(&b, sizeof(b),1,fp)==1)
				{
					if(b.ID==d)
					{
						
						printf("\n");
						printf("\n");
						printf("\n       The book is available");
						printf("\n       ****************************************************");
						printf("\n       ****************************************************");
						printf("\n                        ID      : %d                       ",b.ID);
						printf("\n                        Name    : %s                       ",b.bookName);
						printf("\n                        Author  : %s                       ",b.authorName);
						printf("\n                        Quantity: %d                       ",b.Quantity);
						printf("\n                        Rack no : %d                       ",b.rackno);
						printf("\n       ****************************************************");
						printf("\n       ****************************************************");
						
						
					}
				
					else
					{
						printf("\n");
						printf("\n");
						printf("\n       ************************************");
						printf("\n       ************************************");
						printf("\n       ******    No Record Found     ******");
						printf("\n       ************************************");
						printf("\n       ************************************");
					}	
						printf("\n");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("         Try another search? (Y / N): ");
						if(getch()=='y')
						searchbooks();
						else
						main();
						break;
				}
			}
	    case '2':
			{
				char s[20];
				system("cls");
				printf("\n         ******Search by Name******");
				printf("\n");
				printf("\n");
				printf("\n         Enter Your Name: ");
				scanf("%s",&s);
				int d=0;
				while(fread(&b, sizeof(b),1,fp)==1)
				{
					if(strcmp(b.bookName,(s))==0) //checks whether a.name is equal to s or not
					{
						printf("\n");
						printf("\n");
						printf("\n       The book is available");
						printf("\n       ****************************************************");
						printf("\n       ****************************************************");
						printf("\n                         Book ID: %d                       ",b.ID);
						printf("\n                         Name   : %s                       ",b.bookName);
						printf("\n                         Author : %s                       ",b.authorName);
						printf("\n                         Quantity: %d                      ",b.Quantity);
						printf("\n                         Rack no: %d                       ",b.rackno);
						printf("\n       ****************************************************");
						printf("\n       ****************************************************");
						d++;	
					}
				}
				if(d==0)
				{
					printf("\n");
					printf("\n");
					printf("\n       ************************************");
					printf("\n       ************************************");
					printf("\n       ******    No Record Found     ******");
					printf("\n       ************************************");
					printf("\n       ************************************");
				}
				    printf("\n");
					printf("\n");
					printf("\n");
					printf("\n");
					printf("         Try another search? (Y/N): ");
					if(getch()=='y')
					searchbooks();
					else
					main();
					break;		
			}	
			default:
			getch();
			searchbooks();
			
     	}
     	fclose(fp);
	}	
	
void updatebooks()
{
	system("cls");
	int d;
	printf("\n				********** Update Books Section **********");
	printf("\n              ******************************************");
	char another='y';
	while(another=='y')
	{
		system("cls");
		printf("\n           ==== Enter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("Filebooks.txt","rb+");
		while(fread(&b,sizeof(b),1,fp)==1)
		{
		if(b.ID==d)
		  {
			printf("\n         The book is availble!");
		
			printf("\n         The Book ID:%d",b.ID);
			
			printf("\n         Enter new name:");
			scanf("%s",b.bookName);
			
			printf("           Enter new Author:");
			scanf("%s",b.authorName);
			printf("           Enter new quantity:");
			scanf("%d",&b.Quantity);
			printf("           Enter new rackno:");
			scanf("%d",&b.rackno);
	
			printf("\n");
			printf("        The record is modified");
			fseek(fp,ftell(fp)-sizeof(b),0);
			fwrite(&b,sizeof(b),1,fp);
			fclose(fp);
		  }
	
		}
		if(b.ID!=d)
			{
				printf("\n        No record found");
			}
	
	printf("\n          Modify another Record?(Y/N)");
	fflush(stdin);
	another=getch() ;
	}
}


