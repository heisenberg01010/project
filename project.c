#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int ch;

char fn[20],e,c,name[20];

FILE *fp1,*fp2,*fp;

void Modify();
void NewFile();
void SaveAs();
void Copy();
void Delete();
void View();
void comparison();
void Edit();
void Find();

#define esc 27

int main()
{
	do 
	{
		do
		{
			printf("\n-----------------------------------------TEXT EDITOR--------------------------------------------------");
			printf("\n\n\tMENU:\n\t\n");
			printf("\n\t1.NEWFILE\n\t2.VIEW\n\t3.COPY\n\t4.DELETE\n\t5.COMPARISON\n\t6.EDIT\n\t7.SAVEAS\n\t8.FIND\n\t9.EXIT\n");
			printf("\n\tEnter your choice: ");
			
			scanf(" %d",&ch);
			getchar();
			
		}
		while (ch < 1 || ch > 9);

		switch(ch)
		{
			case 1:
			{
				NewFile();
				break;
			}
			case 2:
			{
				View();
				break;
			}
			case 3:
			{
				Copy();
				break;
			}	
			case 4:
			{
				Delete();
				break;
			}	
			case 5:
			{
				comparison();
				break;
			}	
			case 6:
			{
				Edit();
				break;
			}
			case 7:
			{
				SaveAs();
				break;
			}
			case 8:
			{
				Find();
				break;	
			}
			case 9:
			exit(0);
			
			default:
			{
				printf("Incorrect Input\n");
				break;
			}
		}
		
	
	}
	while(1);

return 0;
}

void NewFile()
{
	printf("\n\tEnter the name of the file to be created: ");
	scanf("%s", name);
	fp1=fopen(name,"w");
	printf("\n\tPress Esc and then Enter to save.\n\t");
	printf("Press Tab key and then Enter to quit without saving.\n\n\t");

	char temp;
	scanf("%c", &temp);

	while(1)
	{
		c=getchar();
		fputc(c,fp1);

		if(c == esc )
		{
			fclose(fp1);
			break;
		}

		else if(c == '\t')
		{
			remove(name);
			break;
		}	

	}
}

void comparison()
{
	int line = 1, col = 0;
	  

	printf("\n\tEnter the first file: ");
		scanf("%s", name);
		fp1 = fopen(name,"r");
	printf("\n\tEnter the second file: ");
		scanf("%s", fn);
		fp2 = fopen(fn,"r");

	

    if (fp1 == NULL || fp2 == NULL) 
    { 
       printf("\tError : Files not open\n"); 
       return; 
    } 
	char ch1 = getc(fp1); 
    char ch2 = getc(fp2);

	while (ch1 != EOF && ch2 != EOF) 
    { 
        col++; 
  
        if (ch1 == '\n' && ch2 == '\n') 
        { 
            line++; 
            col = 0; 
        } 
  

        if (ch1 != ch2) 
        { 
            printf("Files not equal\n"); 
            printf("Line Number : %d \t""Position : %d \n", line, col); 
        } 
  
        ch1 = getc(fp1); 
        ch2 = getc(fp2); 
    } 
    printf("\n\tFiles are identical\n");
	fclose(fp1); 
    fclose(fp2); 
}

void View()
{
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		return;
	}
	printf("\t");
	while( c != EOF )
	{
		c=getc(fp1);
		printf("%c",c);
	}

}

void Copy()
{
	printf("\n\tEnter the new filename to copy:  ");
	scanf("%s",fn);
	printf("\n\tEnter the filename from which to copy: ");
	scanf("%s", name);
	fp1=fopen(name,"r");
	fp2=fopen(fn,"w");

	if(fp1 == NULL)
	{
		printf("\n\tFile not found!");
		return;

	}

	while(!feof(fp1))
	{
		c=getc(fp1);
		putc(c,fp2);
	}

printf("\n\tFile has been copied successfully");
fclose(fp2);
}

void Delete()
{
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");

	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		return;
	}
	fclose(fp1);

	if(remove(fn)==0)
	{
		printf("\n\n\tFile has been deleted successfully!");
	}
	else
		printf("\n\tError!\n"); 
}

void Edit()
{
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r+");

	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		return;
	}
	while(!feof(fp1))
	{
		c=getc(fp1);
		printf("%c",c);

	}
	printf("\n\tPress Esc and then enter key to save.\n\n\t");

	while(1)
		{
			c=getchar();
			fputc(c,fp1);

		if(c == esc )
			{
				fclose(fp1);
				break;
			}

		}
}

void SaveAs()
{
	printf("\n\tEnter the name of the file to be changed: ");
	scanf("%s", name);
	printf("\n\tEnter the new file name: ");
	scanf("%s", fn);

	fp1 = fopen(name, "r");
	
	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		return;
	}
	
	ch = rename(name, fn);

	remove(name);	


	printf("\n\tpress '.' to save\n\n\t");

	while(1)
		{
			c=getchar();

			if(c == '.')
				{
					fclose(fp1);
					break;
				}

		}
}

void Find()
{
	printf("\n\tEnter the file name: ");
	scanf("%s",fn);
	fp1=fopen(fn,"r");


	if(fp1==NULL)
	{
		printf("\n\tFile not found!");
		fclose(fp1);
	}


	char temp[100000];
	int line = 1;
	int match_no = 0;
	char str[100];

	printf("\tEnter the phrase to search: ");
	scanf("%s", str);

	while(fgets(temp, 100000, fp1) != NULL) 
	{
		if((strstr(temp, str)) != NULL) 
		{
			printf("\tA match found on line: %d\n", line);
			printf("\n\t%s\n", temp);
			match_no++;
		}
		line++;
	}
	if(match_no == 0)
	{
		printf("\tNo match found");
	}
	fclose(fp1);
	printf("Hello!");
}



