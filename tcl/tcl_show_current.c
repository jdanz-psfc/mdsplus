#include        "tclsysdef.h"
#include        <mdsshr.h>
#include <string.h>

/**********************************************************************
* TCL_SHOW_CURRENT.C --
*
* TclShowCurrent:  Display current shotid.
*
* History:
*  27-Apr-1998  TRG  Create.  Ported from original mds code.
*
************************************************************************/

	/***************************************************************
	 * TclShowCurrent:
	 ***************************************************************/
int TclShowCurrent(void *ctx, char **error, char **output)
{
  int shot;
  char text[80];
  char *experiment = 0;

  cli_get_value(ctx, "EXPERIMENT", &experiment);
  shot = TreeGetCurrentShotId(experiment);
  if (shot) {
    *output = malloc(100);
    sprintf(*output, "Current shot is %d\n", shot);
  } else {
    *error = strdup("Failed to get shotid.\n");
  }
  if (experiment)
    free(experiment);
  return 1;
}
