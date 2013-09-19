#include "index_builder.h"

//------------------------------------------------------------------------------------

void check_index_builder(char *genome_filename, char *bwt_dirname, int bwt_ratio) {

     if (!exists(genome_filename)) {
	  printf("Reference genome does not exist.\n\n");
	  help_index_builder();
     }

     if (!exists(bwt_dirname)) {
	  printf("BWT index directory does not exist.\n\n");
	  help_index_builder();
     }
	  
     if (bwt_ratio <= 0) {
	  printf("Invalid BWT index ratio. It must be greater than 0.\n\n");
	  help_index_builder();
     }
}

//------------------------------------------------------------------------------------

void help_index_builder() {
     printf("./hpg-aligner build-index -[i|--bwt-index=<directory>] [-g|--ref-genome=<file>] [--index-ratio=<int>]\n");
     printf("-i, --bwt-index=<directory>\t\tBWT directory name\n");
     printf("-g, --ref-genome=<file>\t\tReference genome\n");
     printf("-r, --index-ratio=<int>\t\tBWT index ratio of compression\n");
     printf("--colorspace\t\tBuild colorspace index\n");

     exit(0);
}

//------------------------------------------------------------------------------------

void run_index_builder(char *genome_filename, char *bwt_dirname, int bwt_ratio, int colorspace) {
     
     check_index_builder(genome_filename, bwt_dirname, bwt_ratio);

     char binary_filename[strlen(bwt_dirname) + 128];
     sprintf(binary_filename, "%s/dna_compression.bin", bwt_dirname);
     
     if (colorspace) {
    	 // create colorspace fasta file
		 LOG_DEBUG("Transforming fasta to nucleotide encoded colorspace...\n");
		 char colorspace_fasta_filename[strlen(bwt_dirname) + 128];
	     sprintf(colorspace_fasta_filename, "%s/reference_cs.fasta", bwt_dirname);
		 fasta_to_colorspace(genome_filename, colorspace_fasta_filename);
		 LOG_DEBUG("...done !\n");
		 // generate genome binary files (colorspace and basespace)
		 LOG_DEBUG("Compressing colorspace reference genome...\n");
		 generate_codes(binary_filename, colorspace_fasta_filename);
		 LOG_DEBUG("...done !\n");
	     char nt_binary_filename[strlen(bwt_dirname) + 128];
	     sprintf(nt_binary_filename, "%s/dna_compression_nt.bin", bwt_dirname);
		 LOG_DEBUG("Compressing nucleotide-space reference genome...\n");
		 generate_codes(nt_binary_filename, genome_filename);
		 LOG_DEBUG("...done !\n");
		 // build BWT
	     LOG_DEBUG("Building BWT index...\n");
	     printf("Fasta file: %s\n", colorspace_fasta_filename);
	     bwt_generate_index_files(colorspace_fasta_filename, bwt_dirname, bwt_ratio);
	     LOG_DEBUG("...done !\n");
	     // remove colorspace fasta file, only needed for BWT index generation
	     remove(colorspace_fasta_filename);

     } else {
    	 // generate genome binary file
		 LOG_DEBUG("Compressing reference genome...\n");
		 generate_codes(binary_filename, genome_filename);
		 LOG_DEBUG("...done !\n");
		 // build BWT
	     LOG_DEBUG("Building BWT index...\n");
	     bwt_generate_index_files(genome_filename, bwt_dirname, bwt_ratio);
	     LOG_DEBUG("...done !\n");
     }
     

}


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
