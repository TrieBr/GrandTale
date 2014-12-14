// ----------------------------------------------------------------------
// customAllegroInterface.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Implements the custom allegro file I/O interface that works with the data files for Grand Tale.
*/
// ------------------------------------------------------------------------
#include <allegro5/allegro.h>


void*			cAI_fopen(const char *path, const char *mode);
bool			cAI_fclose(ALLEGRO_FILE *f);
size_t			cAI_fread(ALLEGRO_FILE *f, void *ptr, size_t size);
size_t			cAI_fwrite(ALLEGRO_FILE *f, const void *ptr, size_t size);
bool			cAI_fflush(ALLEGRO_FILE *f);
int64_t			cAI_ftell(ALLEGRO_FILE *f);
bool			cAI_fseek(ALLEGRO_FILE *f, int64_t offset, int whence);
bool			cAI_feof(ALLEGRO_FILE *f);
int			cAI_ferror(ALLEGRO_FILE *f);
void			cAI_fclearerr(ALLEGRO_FILE *f);
int				cAI_fungetc(ALLEGRO_FILE *f, int c);
off_t			cAI_fsize(ALLEGRO_FILE *f);