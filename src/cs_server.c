#include "cs_server.h"

//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------

char cs2nt(char cs) {
	// TODO: implementar esto
	printf("funcion cs2nt de cs_server.c no implementada");
}

//------------------------------------------------------------------------------------
void cs_server_input_init(int colorspace, cs_server_input_t* input_p) {
  input_p->colorspace = colorspace;
}

int apply_cs_preprocessing(cs_server_input_t* input, batch_t *batch) {
  if (input->colorspace) {
	  mapping_batch_t *mapping_batch = batch->mapping_batch;
	  int num_reads = array_list_size(mapping_batch->fq_batch);

	  mapping_batch->adapters = (adapter_t *) calloc(num_reads, sizeof(adapter_t));

	  fastq_read_t *read;
	  adapter_t *adapter;
	  for (int i = 0; i < num_reads; i++) {
			read = array_list_get(i, mapping_batch->fq_batch);
			adapter = &mapping_batch->adapters[i];

			// save the adapter (adapter + first color and first quality)
			adapter_init(read->sequence[0], read->sequence[1],
				 read->quality[1], adapter);
			// remove the adapter and the first color from the sequence, the first quality value,
			// and enconde the colors in nucleotide-space
			read->sequence = read->sequence + 2;
			read->quality++;
			read->length = read->length - 2;
			cs_sequence_to_base_space_encoding(read->sequence);
	  }
	  read = array_list_get(2, mapping_batch->fq_batch);
  }

  return BWT_STAGE;
}

//------------------------------------------------------------------------------------

void apply_cs_postprocessing(mapping_batch_t *batch) {
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

