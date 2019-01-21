#ifndef TSK_GENOTYPES_H
#define TSK_GENOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <tskit/trees.h>

#define TSK_16_BIT_GENOTYPES    1

typedef struct {
    size_t num_samples;
    double sequence_length;
    size_t num_sites;
    tsk_treeseq_t *tree_sequence;
    tsk_id_t *sample_index_map;
    char *output_haplotype;
    char *haplotype_matrix;
    tsk_tree_t tree;
} tsk_hapgen_t;

typedef struct {
    tsk_site_t *site;
    const char **alleles;
    tsk_size_t *allele_lengths;
    tsk_size_t num_alleles;
    tsk_size_t max_alleles;
    union {
        uint8_t *u8;
        uint16_t *u16;
    } genotypes;
} tsk_variant_t;

typedef struct {
    size_t num_samples;
    size_t num_sites;
    tsk_treeseq_t *tree_sequence;
    tsk_id_t *samples;
    tsk_id_t *sample_index_map;
    size_t tree_site_index;
    int finished;
    tsk_tree_t tree;
    tsk_flags_t options;
    tsk_variant_t variant;
} tsk_vargen_t;

int tsk_hapgen_init(tsk_hapgen_t *self, tsk_treeseq_t *tree_sequence);
/* FIXME this is inconsistent with the tables API which uses size_t for
 * IDs in functions. Not clear which is better */
int tsk_hapgen_get_haplotype(tsk_hapgen_t *self, tsk_id_t j, char **haplotype);
int tsk_hapgen_free(tsk_hapgen_t *self);
void tsk_hapgen_print_state(tsk_hapgen_t *self, FILE *out);

int tsk_vargen_init(tsk_vargen_t *self, tsk_treeseq_t *tree_sequence,
        tsk_id_t *samples, size_t num_samples, tsk_flags_t options);
int tsk_vargen_next(tsk_vargen_t *self, tsk_variant_t **variant);
int tsk_vargen_free(tsk_vargen_t *self);
void tsk_vargen_print_state(tsk_vargen_t *self, FILE *out);

#ifdef __cplusplus
}
#endif
#endif