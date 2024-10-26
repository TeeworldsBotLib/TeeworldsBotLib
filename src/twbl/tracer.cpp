#include <twbl/teeworlds/base/system.h>

#include "tracer.h"

void twbl_default_log_tracer(const char *pLine, int Offset, void *pContext)
{
	// if you do not want to see a full path in the log
	// you can implement your own tracer
	// and print ``pLine + offset``
	// where offset is how ever long your base path is
	dbg_msg("twbl-trace", "%s", pLine);
}
