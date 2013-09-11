#ifndef CS_SERVER_H
#define CS_SERVER_H

#include "commons/commons.h"
#include "containers/array_list.h"
#include "aligners/bwt/colorspace.h"

#include "buffers.h"

//====================================================================================
//  structures and prototypes
//====================================================================================

/**
 * @brief Structure for store all parameters needed for run @a bwt_server_cpu.
 *
 * Structure for store some configuration values and data structures like lists
 * to insert and read data batches.
 */
struct cs_server_input {
  int colorspace;        /** colorspace*/
};

//------------------------------------------------------------------------------------

/**
 * @brief  Initializer for the @a cs_server_input_t structure.
 * @param  colorspace input reads are in colorspace
 *
 * Initialize all @a cs_server_input_t fields with the input parameters.
 */
void cs_server_input_init(int colorspace, cs_server_input_t* input_p);

//====================================================================================
// apply_cs_preprocessing
//====================================================================================
int apply_cs_preprocessing(cs_server_input_t* input, batch_t *batch);

//------------------------------------------------------------------------------------

int apply_cs_postprocessing(cs_server_input_t* input, batch_t *batch);

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

#endif  // CS_SERVER_H

