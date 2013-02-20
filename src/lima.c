#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "odesys.h"

#define MAX_CONFIG_FILE_SIZE (64 * 1024) /* 64 kB */

int
main(int argc, char *argv[])
{
  odesys_t *odesys = NULL;
  struct stat file_status;

  if (argc < 3)
    {
      fprintf (stderr, "Useage: %s <parameter file> <output file>.\n",
               argv[0]);
      exit (1);
    }
  
  if (stat(argv[2], &file_status) == 0)
    {
      fprintf (stderr, "Output filename already exists. Exiting.\n");
      exit (1);
    }

  odesys = odesys_parse_cfg_from_file_ctor (argv[1], MAX_CONFIG_FILE_SIZE);
  if (odesys == NULL)
    {
      fprintf(stderr, "Failed to initialize. Exiting.\n");
      return -1;
    }

  //  odesys_tdse_propagate_simple (odesys);
  odesys_tdse_propagate_threaded(odesys, 4);
  odesys_expval_fwrite(odesys, argv[2]);

  odesys_dtor(odesys);

  return 0;
}

#undef MAX_CONFIG_FILE_SIZE
