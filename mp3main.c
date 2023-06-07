#include <stdio.h>
#include <string.h>
#include "view.h"
#include "edit.h"
#include "types.h"

int main(int argc,char *argv[])
{
    mp3Details tagReader;
    editmp3Details editReader;

    if(argc>1)
    {

	if(strcmp(argv[1],"--help")==0)
	{
	    printf("-----------------------------------------------HELP MENU-------------------------------------------------------\n");
	    printf("1. -v -> to view mp3 file contents\n");
	    printf("2. -e -> to edit mp3 file contents\n");
	    printf("         2.1 -t -> to edit song title\n");
	    printf("         2.2 -a -> to edit artist name\n");
	    printf("         2.3 -A -> to edit Album name\n");
	    printf("         2.4 -m -> to edit content\n");
	    printf("         2.5 -y -> to edit year\n");
	    printf("         2.6 -c -> to edit comment\n");
            printf("---------------------------------------------------------------------------------------------------------------\n");
	}
	else if(strcmp(argv[1],"-v")==0)
	{
          if( view_validation(argv,&tagReader)==e_failure)
	  {
	      printf("Validation for viewing tag reader is failure\n");
	  } 
	  else
	  {
	      if(view(&tagReader)==e_failure)
	      {
		  printf("Viewing mp3 tag details is unsuccessful\n");
	      }
	  }
	}
	else if(strcmp(argv[1],"-e")==0)
	{
             if(edit_validation(argc,argv,&editReader)==e_failure)
             {
		 printf("Validation for editing mp3 is unsuccessful\n");
	     }
	     else
	     {
		 if(edit(argv,&editReader)==e_failure)
		 {
		     printf("Editing mp3 tag details is unsuccessful\n");
		 }
	     }
	}
	else
	{
   	    
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("Error : INVALID ARGUMENTS\n");
	printf("USAGE:\n");
	printf("To view plz pass like : ./a.out -v mp3filename \n");
	printf("To edit plz pass like : ./a.out -e -t/-a/-A/-y/-m/-c changing_text mp3filename \n");
	printf("To get help pass like : ./a.out --help \n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	
	} 

    }
    else
    {
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("Error : ./.aout : INVALID ARGUMENTS\n");
	printf("USAGE:\n");
	printf("To view plz pass like : ./a.out -v mp3filename \n");
	printf("To edit plz pass like : ./a.out -e -t/-a/-A/-y/-m/-c changing_text mp3filename \n");
	printf("To get help pass like : ./a.out --help \n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
    }
}
