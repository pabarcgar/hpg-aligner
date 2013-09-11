#ifndef INDEX_BUILDER_H
#define INDEX_BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aligners/bwt/bwt.h"
#include "aligners/bwt/genome.h"
#include "aligners/bwt/colorspace.h"
#include "commons/file_utils.h"

void run_index_builder(char *genome_filename, char *bwt_dirname, int bwt_ratio, int colorspace);

#endif // INDEX_BUILDER_H
