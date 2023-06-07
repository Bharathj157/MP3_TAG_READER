#ifndef VIEW_H
#define VIEW_H

#include "types.h"

typedef struct mp3Info
{
	FILE *fptr_mp3;
	char mp3fname[32];
	
	

}mp3Details;

Status view_validation(char*argv[],mp3Details *tagReader);

Status view(mp3Details *tagReader);

#endif
