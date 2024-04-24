#include "matrices.h"

#ifdef AD_CHK
	#include <stdlib.h> // exit
	#include "../utils/log.h"
#endif

inline union Matrix4x4 m4x4_translation(union Tuple _t) {
#ifdef AD_CHK
	LOG_W("Not implemented yet.");
	exit(0);
#endif	
}
