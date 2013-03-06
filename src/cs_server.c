#include "cs_server.h"

//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------

char cs2nt(char cs) {
}

//------------------------------------------------------------------------------------

void apply_cs_preprocessing(mapping_batch_t *batch) {
  
  int num_reads = array_list_size(batch->fq_batch);

  batch->adapters = (adapter_t *) calloc(num_reads, sizeof(adapter_t));

  printf("pre processing CS...\n");

  fastq_read_t *read;
  adapter_t *adapter;
  for (int i = 0; i < num_reads; i++) {
    read = array_list_get(i, batch->fq_batch);
    adapter = &batch->apdapters[i];

    adapter_init(read->sequence[0], cs2nt(read->sequence[1]), 
		 read->quality[1], adapter);
    
    
    printf("read %i of %i: %s\n", i, num_reads, read->sequence);
  }

  printf("pre processing CS...done !!\n");
}

//------------------------------------------------------------------------------------

void apply_cs_postprocessing(mapping_batch_t *batch) {
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

