
#ifndef EDIT_H
#define EDIT_H

#include "types.h"

typedef struct mp3details
{
        
	FILE *fptr_mp3;
	char mp3fname[32];

        FILE *duplicate_fptr_mp3;
        char *duplicate_fname;
        
        
        char tags[5];	
        uint eStringSize;
        char eString[258];
        
        uint temp1Size;
        long temp2Size;

}editmp3Details;

Status edit_read_validate_argu(int argc,char *argv[],editmp3Details *tagReader);

Status edit_f_open(editmp3Details *tagReader);

Status edit_check_id3(editmp3Details *tagReader);

Status edit_check_modifier(char *argv[],editmp3Details *tagReader);

Status edit_validation(int argc,char * argv[],editmp3Details *tagReader);

Status edit(char *argv[],editmp3Details *tagReader);

#endif
