#ifndef CS_SERVER_H
#define CS_SERVER_H

#include "commons/commons.h"
#include "containers/array_list.h"

#include "buffers.h"

//====================================================================================
//  structures and prototypes
//====================================================================================

void apply_cs_preprocessing(mapping_batch_t *batch);

//------------------------------------------------------------------------------------

void apply_cs_postprocessing(mapping_batch_t *batch);

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

#endif  // CS_SERVER_H

