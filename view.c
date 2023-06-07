#include<stdio.h>
#include<string.h>
#include"view.h"
#include "types.h"

Status read_validate_argu(char *argv[],mp3Details *tagReader)
{
    if(argv[2]==NULL)
    {
	return e_failure;
    }

    if(strstr(argv[2],".mp3")==NULL)
    {
        return e_failure;
    }
    strcpy(tagReader->mp3fname,argv[2]);
//    printf("%s",tagReader->mp3fname);
}

Status f_open(mp3Details *tagReader)
{
	tagReader->fptr_mp3=fopen(tagReader->mp3fname,"r" );

	if (tagReader->fptr_mp3 == NULL)
	{
		perror("fopen");
		fprintf(stderr,"ERROR: unable to open the file %s\n",tagReader->mp3fname);
		return e_failure;
	}
	return e_success;
}

Status check_id3(mp3Details *tagReader)
{
    char buffer[4];
    fseek(tagReader->fptr_mp3,0,SEEK_SET);
    fread(buffer,3,1,tagReader->fptr_mp3);
    buffer[3]='\0';
    if(strcmp(buffer,"ID3")!=0)
	return e_failure;

    char ch;
    fread(&ch,1,1,tagReader->fptr_mp3);
    if(ch!=0x03)
    {
    return e_failure;
    }

}

Status view_validation(char *argv[],mp3Details *tagReader)
{

    if(read_validate_argu(argv,tagReader)==e_failure)
    {
	printf("Validation of CML arguments is unsuccessful\n");
	return e_failure;
    }
    
    if(f_open(tagReader)==e_failure)
    {
          printf("Opening a mp3failure is unsuccessful\n");	
	  return e_failure;
    }
    
    if(check_id3(tagReader)==e_failure)
    { 
          printf("ID3 tag or version is not matching\n");	
	  return e_failure;
    }
}


char read_size(mp3Details *tagReader,int *num)
{
    fseek(tagReader->fptr_mp3,3,SEEK_CUR);
     
    unsigned char ch;
    fread(&ch,1,1,tagReader->fptr_mp3);
    
 /*   int base=1;
    for(int i=0;i<8;i++)
    {
       *num = *num+(ch&(1<<i));
    }
   */

    fseek(tagReader->fptr_mp3,2,SEEK_CUR);
    return ch;
    
}


Status tag_reader(mp3Details *tagReader)
{
    
    int num=0;
    char info[258];
    char arr[6][5]={"TPE1","TIT2","TALB","TYER","TCON","COMM"};
    char buffer[5];
    fread(buffer,4,1,tagReader->fptr_mp3);
    buffer[4]='\0';
   // printf("%s\n",buffer);
    for(int i=0;i<6;i++)
    {
	if(strcmp(buffer,arr[i])==0)
        {
	    switch (i)
	    {
		case 0:
		   num=read_size(tagReader,&num);
		   fread(info,num,1,tagReader->fptr_mp3);
                   printf("Artist Name    : ");
		   for(int i=0;i<num;i++)
		   printf("%c",info[i]);
		   printf("\n"); 
		   printf("\n"); 

		    break;
		case 1:
		   num=read_size(tagReader,&num);
		   fread(info,num,1,tagReader->fptr_mp3);
                   printf("Song Title     : ");
		   for(int i=0;i<num;i++)
		   printf("%c",info[i]); 
		   printf("\n"); 
		   printf("\n"); 
		    break;
		case 2:
		  num= read_size(tagReader,&num);
		   fread(info,num,1,tagReader->fptr_mp3);
                   printf("Album          : ");
		   for(int i=0;i<num;i++)
		   printf("%c",info[i]); 
		   printf("\n"); 
		   printf("\n"); 
		    break;
		case 3:
		  num= read_size(tagReader,&num);
		   fread(info,num,1,tagReader->fptr_mp3);
                   printf("Year           : ");
		   for(int i=0;i<num;i++)
		   printf("%c",info[i]); 
		   printf("\n"); 
		   printf("\n"); 
		    break;
		case 4:
		  num= read_size(tagReader,&num);
		   fread(info,num,1,tagReader->fptr_mp3);
                   printf("Content type   : ");
		   for(int i=0;i<num;i++)
		   printf("%c",info[i]); 
		   printf("\n"); 
		   printf("\n"); 
		    break;
		case 5:
		  num= read_size(tagReader,&num);
		   fread(info,num,1,tagReader->fptr_mp3);
                   printf("Comments       : ");
		   for(int i=0;i<num;i++)
		   printf("%c",info[i]); 
		   printf("\n"); 
		   printf("\n"); 
		   break;
	    }
    	  break;  
        }
    }
    
}

Status view(mp3Details *tagReader)
{
    
    fseek(tagReader->fptr_mp3,10,SEEK_SET);
    printf("---------------------------------------------===========--------------------------------------------------\n");
    printf("---------------------------------------------MP3 DETAILS--------------------------------------------------\n");
    printf("---------------------------------------------===========--------------------------------------------------\n");
    printf("\n");
    printf("-----------------------------------\n");
    printf("MP3 TAG READER AND EDITOR FOR ID3V2  \n");
    printf("-----------------------------------\n");
    printf("\n");
    for(int i=0;i<6;i++)
    tag_reader(tagReader);

    printf("--------------------------------------==============================--------------------------------------\n");
    printf("--------------------------------------Details Displayed Successfully--------------------------------------\n");
    printf("--------------------------------------==============================--------------------------------------\n");

    

}

