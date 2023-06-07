#include<stdio.h>
#include <string.h>
#include "edit.h"
#include "types.h"

Status edit_read_validate_argu(int argc,char *argv[],editmp3Details *tagReader)
{

    if(argc!=5)
    {
	return e_failure;
    }
    if(strstr(argv[4],".mp3")==NULL)
    {
	return e_failure;
    }
    strcpy(tagReader->mp3fname,argv[4]);
    return e_success;
}

Status edit_f_open(editmp3Details *tagReader)
{
    tagReader->fptr_mp3=fopen(tagReader->mp3fname,"r+" );

    if (tagReader->fptr_mp3 == NULL)
    {
	perror("fopen");
	fprintf(stderr,"ERROR: unable to open the file %s\n",tagReader->mp3fname);
	return e_failure;
    }
    return e_success;
}

Status edit_check_id3(editmp3Details *tagReader)
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
    return e_success;

}

Status edit_check_modifier(char *argv[],editmp3Details *tagReader)
{
    char arr[6][3]={"-t","-A","-a","-y","-m","-c"};
    for(int i=0;i<6;i++)
    {
	if(strcmp(argv[2],arr[i])==0)
	{
	    return e_success;
	}
    }
    return e_failure;
}

Status edit_validation(int argc,char * argv[],editmp3Details *tagReader)
{

    if(edit_read_validate_argu(argc,argv,tagReader)==e_failure)
    {
	printf("Validation of CML arguments is unsuccessful\n");
	return e_failure;
    }

    if(edit_f_open(tagReader)==e_failure)
    {
	printf("Opening a mp3failure is unsuccessful\n");	
	return e_failure;
    }

    if(edit_check_id3(tagReader)==e_failure)
    { 
	printf("ID3 tag or version is not matching\n");	
	return e_failure;
    }
    if(edit_check_modifier(argv,tagReader)==e_failure)
    {
	printf("Did not passsed proper input arguments pass like (-t/-A/-a/-m/-y/-c )\n");
	return e_failure; 
    }
    return e_success;
}

Status duplicateMp3(editmp3Details *tagReader)
{
    tagReader->duplicate_fname="temp.mp3";
    tagReader->duplicate_fptr_mp3=fopen(tagReader->duplicate_fname,"w+");
    char ch;
    fseek(tagReader->fptr_mp3,0,SEEK_SET);
    fseek(tagReader->duplicate_fptr_mp3,0,SEEK_SET);

    while(fread(&ch,1,1,tagReader->fptr_mp3)!=0)
    {
	fwrite(&ch,1,1,tagReader->duplicate_fptr_mp3);
    }
    return e_success;

}
Status check(editmp3Details *tagReader)
{
    unsigned char size;

    char buffer_tag[5];
    char buffer_edit[tagReader->eStringSize];

    fread(buffer_tag,4,1,tagReader->fptr_mp3);
    buffer_tag[4]='\0';
   
    while(strcmp(buffer_tag,tagReader->tags)!=0)
    {
	fseek(tagReader->fptr_mp3,3,SEEK_CUR);
	fread(&size,1,1,tagReader->fptr_mp3);
	fseek(tagReader->fptr_mp3,2,SEEK_CUR);
	fseek(tagReader->fptr_mp3,size,SEEK_CUR);
	fread(buffer_tag,4,1,tagReader->fptr_mp3);
	buffer_tag[4]='\0';
    }

    fseek(tagReader->fptr_mp3,3,SEEK_CUR);
    fread(&size,1,1,tagReader->fptr_mp3);

    tagReader->temp2Size=ftell(tagReader->fptr_mp3);

    tagReader->temp1Size=size;
  
    if(buffer_tag!="TYER"){
	fseek(tagReader->fptr_mp3,-1,SEEK_CUR);
	fwrite(&tagReader->eStringSize,1,1,tagReader->fptr_mp3);
    }
    fseek(tagReader->fptr_mp3,3,SEEK_CUR);
    int i=0;
    while(tagReader->eString[i]!='\0')
	fwrite(&tagReader->eString[i++],1,1,tagReader->fptr_mp3);

    int ptr;
  
    ptr=tagReader->temp2Size+tagReader->temp1Size+2;
   
    fseek(tagReader->duplicate_fptr_mp3,0,SEEK_SET);
    fseek(tagReader->duplicate_fptr_mp3,ptr,SEEK_CUR);
    
    char ch;
    while(fread(&ch,1,1,tagReader->duplicate_fptr_mp3)!=0)
    {
	fwrite(&ch,1,1,tagReader->fptr_mp3);
    } 
}


Status edit(char *argv[],editmp3Details *tagReader)
{
    duplicateMp3(tagReader);

    char buffer[5];
    char arr[6][5]={"-t","-a","-A","-y","-m","-c"};
    fseek(tagReader->fptr_mp3,0,SEEK_SET);
    fseek(tagReader->fptr_mp3,10,SEEK_CUR);
    strcpy(tagReader->eString,argv[3]);
    tagReader->eStringSize=strlen(argv[3])+1;
    printf("----------------------------------------===================------------------------------------------\n");
    printf("----------------------------------------Editing mp3 Details------------------------------------------\n");
    printf("----------------------------------------===================------------------------------------------\n");
    printf("\n");
    for(int i=0;i<6;i++)
    {
	if(strcmp(argv[2],arr[i])==0)
	{	
	    switch (i)
	    {
		case 0:
		    printf("Editing Title Name\n");
		    printf("\n");
		    strcpy(tagReader->tags,"TIT2");
		    check(tagReader);	   
		    break; 
		case 1:
		    printf("Editing Artist Name\n");
		    printf("\n");
		    strcpy(tagReader->tags,"TPE1");
		    check(tagReader);
		    break;
		case 2:
		    printf("Editing Album Name\n");
		    printf("\n");
		    strcpy(tagReader->tags,"TALB");
		    check(tagReader);
		    break;
		case 3:
		    printf("Editing Year\n");
		    printf("\n");
		    strcpy(tagReader->tags,"TYER");
		    check(tagReader);
		    break;
		case 4:
		    printf("Editing Content\n");
		    printf("\n");
		    strcpy(tagReader->tags,"TCON");
		    check(tagReader);
		    break;
		case 5:
		    printf("Editing Comments\n");
		    printf("\n");
		    strcpy(tagReader->tags,"COMM");
		    check(tagReader);
		    break;
		default:
		    printf("Pass correct arguments\n");
		    return e_failure;

	    }
	    printf("Editing %s tag is Successful\n",tagReader->tags);
	    printf("\n");
	}
    }
    printf("------------------------------------------===================----------------------------------------\n");
    printf("-----------------------------------Updating mp3 Details is Successful--------------------------------\n");
    printf("------------------------------------------===================----------------------------------------\n");
    remove("temp.mp3");
    return e_success;
}
