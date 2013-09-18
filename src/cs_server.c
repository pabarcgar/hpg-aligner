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

int apply_cs_postprocessing(cs_server_input_t* input, batch_t *batch) {
//	LOG_DEBUG("Reading basespace genome...");
//	genome_t* basespace_genome = genome_new("dna_compression_nt.bin", "/data/test/hpg-aligner/colorspace/alineamientosCS/nuevasPruebas/referencia_cs/");
//	LOG_DEBUG("Done !!");
	// mensajes del genoma de referencia
//	printf("Numero de cromosomas: %d\n", basespace_genome->num_chromosomes);
//	printf("length: %d\n", basespace_genome->genome_length);
//	for (int i=0; i<basespace_genome->num_chromosomes; i++) {
//		printf("Chr name: %s\n", basespace_genome->chr_name[i]);
//		printf("Chr size: %d\n", basespace_genome->chr_size[i]);
//		printf("Chr offset: %d\n", basespace_genome->chr_offset[i]);
//	}

//	printf("\t\tread_match =\t\t%s\n", read_match);

	// TODO: Prueba, vamos a coger el trocito de la referencia sobre el que mapea la read
	mapping_batch_t* mapping_batch = batch->mapping_batch;

//	printf("NUMERO DE TARGETS EN EL MAPPING BATCH: %d\n", mapping_batch->num_targets);
//	printf("NUMERO DE EXTRA TARGETS EN EL MAPPING BATCH: %d\n", mapping_batch->num_extra_targets);
//	printf("NUMERO DE ALLOCATED TARGETS: %d\n", mapping_batch->num_allocated_targets);
//	printf("NUM TO DO: %d\n", mapping_batch->num_to_do);
//
//	array_list_t *fq_batch = mapping_batch->fq_batch;
//	printf("TAMANO DEL fq_batch: %d\n", fq_batch->size);

//	size_t* targets = mapping_batch->targets;
//	for (int i=0; i<mapping_batch->num_allocated_targets; i++) {
//		printf("Target %d: %d\n", i, targets[i]);
//	    //read_index = batch->targets[i];
//	}

//	printf("Action: %d\n", mapping_batch->action);
//	printf("Num Targets: %d\n", mapping_batch->num_targets);
//	printf("Num allocated Targets: %d\n", mapping_batch->num_allocated_targets);
//	printf("fastq batch size: %d\n", array_list_size(mapping_batch->fq_batch));

    size_t num_reads = array_list_size(mapping_batch->fq_batch);
    size_t num_mapped_reads = 0;
    size_t total_mappings = 0;
    size_t num_items;
    fastq_read_t *fq_read;
    array_list_t* read_mappings_list;
    alignment_t* alignment;
    adapter_t adapter;
    for (size_t i = 0; i < num_reads; i++) {
    	 num_items = array_list_size(mapping_batch->mapping_lists[i]);
    	 total_mappings += num_items;
    	 fq_read = (fastq_read_t *) array_list_get(i, mapping_batch->fq_batch);
    	 adapter = mapping_batch->adapters[i];
    	   // mapped or not mapped ?
    	 if (num_items == 0) {
    	   total_mappings++;
//    	   write_unmapped_read(fq_read, bam_file);
    	 } else {
    	   num_mapped_reads++;
    	   read_mappings_list = mapping_batch->mapping_lists[i];
    	   size_t num_mappings = array_list_size(read_mappings_list);
    	   for (size_t j = 0; j < num_mappings; j++) {
    		   alignment = (alignment_t *) array_list_get(j, read_mappings_list);
    		   // TODO: descomentar la siguiente linea para hacer el postprocessing
    		   // colorspace_alignment_postprocess(alignment, adapter, basespace_genome);
    	   }
    	 }
    }
//    printf ("\n\nNumero de reads mapeadas: %d\n", num_mapped_reads);
//    printf ("\n\nNumero total de mappings: %d\n", total_mappings);

//	adapter_t adaptador = mapping_batch->adapters[j];
//	//      printf("ADAPTADOR: %c%c\n", adaptador.base, adaptador.first_color);
//	//      printf("PRIMER NUCLEOTIDO: %c\n", adapter_to_nucleotide(adaptador.base, adaptador.first_color));
//	//      printf("MAPPED LEN: %d\n", mapped_len);
//	//      printf("C: %d\n", c);
//	//      printf("POS: %d\n", pos);
//	char* trocito = calloc(1, mapped_len);
//	size_t start, end;
//	start = pos + 1;
//	end = start + c;
//	//      printf("START: %d\n", pos);
//	//      printf("END: %d\n", end);
//	// genome parameters
//
//	char* trocito_basespace = calloc(1, mapped_len);
//	genome_read_sequence_by_chr_index(trocito, sw_output->strand,
//	                                 sw_output->chromosome - 1, &start, &end, input->genome_p);
//	genome_read_sequence_by_chr_index(trocito_basespace, sw_output->strand,
//	                             sw_output->chromosome - 1, &start, &end, basespace_genome);
//	//     genome_read_sequence_by_chr_index(r[sw_count], cal->strand,
//	//                                       cal->chromosome_id - 1, &start, &end, genome);
//	printf("\tTrocito colorspace:\t\t%s\n", trocito);
//
//	char* trocito_basespace_cs;
//	trocito_basespace_cs = (char *) calloc(strlen(trocito_basespace), sizeof(char));
//	nucleotide_sequence_to_color_space(NULL, trocito_basespace, trocito_basespace_cs);
//	printf("\tTrocito basespace en cs:\t%s\n", trocito_basespace_cs);
//	printf("\tTrocito basespace:\t\t%s\n", trocito_basespace);
//	printf("PRIMER NUCLEOTIDO:\t\t%c\n", adapter_to_nucleotide(adaptador.base, adaptador.first_color));
//	free(trocito);
//	free(trocito_basespace);
//	free(trocito_basespace_cs);

	// TODO: fin pruebacip
	return CONSUMER_STAGE;
}

void colorspace_alignment_postprocess (alignment_t* alignment, adapter_t adapter, genome_t* basespace_genome) {
	// obtain the basespace sequence from the reference genome
	size_t mapped_len = strlen(alignment->sequence);
	printf("Alignment sequence: %s\n", alignment->sequence);
	// TODO: ojo con los nombres de variables
	printf("Mapped Length:%d\n", mapped_len);
	// TODO: ¿malloc en lugar de calloc?
	char* basespace_read = calloc(1, mapped_len);

	size_t start, end;
	start = alignment->position + 1;
	end = start + mapped_len;
//	printf("Parametros: trocito_basespace: %s\nalignment->seq_strand: %d\nalignment->chromosome: %d,&start,
//									  &end,
//									  basespace_genome");
	genome_read_sequence_by_chr_index(basespace_read,
									  alignment->seq_strand,
									  alignment->chromosome,
									  &start,
									  &end,
									  basespace_genome);
	printf("Trocito extraido:   %s\n", basespace_read);

	// obtenemos el adaptador para compararlo
	char first_nucleotide = cs_adapter_to_nucleotide(adapter.base, adapter.first_color);
	printf("Adaptador: %c\n", first_nucleotide);

	free(basespace_read);
	// compare the adapter

}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

