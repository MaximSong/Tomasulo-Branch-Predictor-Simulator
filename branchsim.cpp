#include "branchsim.hpp"
#include <algorithm>
void yeh_patt_init_predictor(branchsim_conf_t *sim_conf) {
    // create history table of 2^H entries (all entries initialized to 0)

    // create pattern table of 2^P entries init to weakly not taken

#ifdef DEBUG
    printf("Yeh-Patt: Creating a history table of %" PRIu64 " entries of length %" PRIu64 "\n", 0ul, 0ul); // TODO: FIX ME
    printf("Yeh-Patt: Creating a pattern table of %" PRIu64 " 2-bit saturating counters\n", 0ul); // TODO: FIX ME
#endif
}

bool yeh_patt_predict(branch_t *br) {
#ifdef DEBUG
    printf("\tYeh-Patt: Predicting... \n"); // PROVIDED
#endif

    // add your code here


#ifdef DEBUG
    printf("\t\tHT index: 0x%" PRIx64 ", History: 0x%" PRIx64 ", PT index: 0x%" PRIx64 ", Prediction: %d\n", 0ul, 0ul, 0ul, 0); // TODO: FIX ME
#endif
    return false; // TODO: FIX ME
}

void yeh_patt_update_predictor(branch_t *br) {
#ifdef DEBUG
    printf("\tYeh-Patt: Updating based on actual behavior: %d\n", (int) br->is_taken); // PROVIDED
#endif

    // add your code here

#ifdef DEBUG
    printf("\t\tHT index: 0x%" PRIx64 ", History: 0x%" PRIx64 ", PT index: 0x%" PRIx64 ", New Counter: 0x%" PRIx64 ", New History: 0x%" PRIx64 "\n", 0ul, 0ul, 0ul, 0ul, 0ul); // TODO: FIX ME
#endif
}

void yeh_patt_cleanup_predictor() {
    // add your code here
}

unsigned long long ghr = 0;
unsigned long long pattern_table_size;
unsigned long long *pattern_table;
void gshare_init_predictor(branchsim_conf_t *sim_conf) {
    // create pattern table of 2^P entries init to weakly not taken
    unsigned int P = sim_conf->P;
    ghr = 0;
    unsigned long long pattern_table_size = 1 << P;
    unsigned long long *pattern_table = new unsigned long long[pattern_table_size];
    std::fill_n(pattern_table, pattern_table_size, 0b01); // initialize pattern table to weakly not taken

#ifdef DEBUG
    printf("Gshare: Creating a pattern table of %" PRIu64 " 2-bit saturating counters\n", 0ul); // TODO: FIX ME
#endif
}

bool gshare_predict(branch_t *br) {
#ifdef DEBUG
    printf("\tGshare: Predicting... \n"); // PROVIDED
#endif
    
    // add your code here
    unsigned long long index = (ghr ^ br->ip) & (pattern_table_size - 1);
    bool prediction = pattern_table[index] >= 0b10;

#ifdef DEBUG
    printf("\t\tHistory: 0x%" PRIx64 ", Counter index: 0x%" PRIx64 ", Prediction: %d\n", 0ul, 0ul, 0);
#endif
    return prediction; // TODO: FIX ME
}

void gshare_update_predictor(branch_t *br) {
#ifdef DEBUG
    printf("\tGshare: Updating based on actual behavior: %d\n", (int) br->is_taken); // PROVIDED
#endif

    // add your code here
    unsigned long long index = (ghr ^ br->ip) & (pattern_table_size - 1);
    if (br->is_taken) {
        if (pattern_table[index] < 0b11) {
            pattern_table[index]++;
        }
    } else {
        if (pattern_table[index] > 0b00) {
            pattern_table[index]--;
        }
    }
    ghr = (ghr << 1) | (br->is_taken ? 1 : 0) & (pattern_table_size - 1);

#ifdef DEBUG
    printf("\t\tHistory: 0x%" PRIx64 ", Counter index: 0x%" PRIx64 ", New Counter value: 0x%" PRIx64 ", New History: 0x%" PRIx64 "\n", 0ul, 0ul, 0ul, 0ul); // TODO: FIX ME
#endif
}

void gshare_cleanup_predictor() {
    // add your code here
    delete[] pattern_table;
    pattern_table = nullptr;
#ifdef DEBUG
    printf("Gshare: Cleaning up\n"); 
#endif
}

/**
 *  Function to update the branchsim stats per prediction
 *
 *  @param prediction The prediction returned from the predictor's predict function
 *  @param br Pointer to the branch_t that is being predicted -- contains actual behavior
 *  @param sim_stats Pointer to the simulation statistics -- update in this function
*/
void branchsim_update_stats(bool prediction, branch_t *br, branchsim_stats_t *sim_stats) {

}

/**
 *  Function to cleanup branchsim statistic computations such as prediction rate, etc.
 *
 *  @param sim_stats Pointer to the simulation statistics -- update in this function
*/
void branchsim_finish_stats(branchsim_stats_t *sim_stats) {

}


