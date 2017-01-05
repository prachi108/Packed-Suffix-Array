/* -*- mode:c; c-file-style:"k&r"; c-basic-offset: 4; tab-width:4; indent-tabs-mode:nil; mode:auto-fill; fill-column:78; -*- */
/* vim: set ts=4 sw=4 et tw=78 fo=cqt wm=0: */


#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <memory.h>
# include <stddef.h>
# include <strings.h>
#include <assert.h>
# include <sys/types.h>
#include <divsufsort.h>
#include "lfs.h"
#include "bit_array.h"

typedef struct _TestCase
{
    sauchar_t * text;
    saidx_t text_len;
    sauchar_t * pattern;
    saidx_t pattern_len;
    BIT_ARRAY * Ba;

    saidx_t expected_num_matches;
    saidx_t expected_index;
} TestCase;

#define MAX_TEST_CASES 255

void get_test_cases(TestCase **tc, saidx_t *num_testcases)
{
    *tc = NULL;
    *num_testcases = 0;
    size_t alloc_size = MAX_TEST_CASES * sizeof(TestCase);
    *tc = malloc(alloc_size);
    memset(*tc, 0, alloc_size);
    //check for null

    TestCase * current_tc = *tc;

    //Create bit array 001001001
    BIT_ARRAY * ba = NULL;
    ba = bit_array_create(9);
    bit_array_set_bit(ba, 2);
    bit_array_set_bit(ba, 5);
    bit_array_set_bit(ba, 8);


    //Test case #1
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "AC";
    current_tc->pattern_len = 2;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 0;

    current_tc++;
    (*num_testcases)++;


    //Test case #2...
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CG";
    current_tc->pattern_len = 2;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 3;

    current_tc++;
    (*num_testcases)++;


    //Test case #3
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "TA";
    current_tc->pattern_len = 2;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 8;

    current_tc++;
    (*num_testcases)++;


    //Test case #4
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "AG";
    current_tc->pattern_len = 2;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 1;

    current_tc++;
    (*num_testcases)++;


    //Test case #5
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CC";
    current_tc->pattern_len = 2;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 2;

    current_tc++;
    (*num_testcases)++;


    //Test case #6
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CT";
    current_tc->pattern_len = 2;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 4;

    current_tc++;
    (*num_testcases)++;


    //Test case #7
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "ACG";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 0;

    current_tc++;
    (*num_testcases)++;


    //Test case #8
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "TAG";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 8;

    current_tc++;
    (*num_testcases)++;


    //Test case #9
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CCT";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 2;

    current_tc++;
    (*num_testcases)++;


    //Test case #10
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CGT";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #11
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "AGC";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #12
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CTT";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #13
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "AAC";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #14
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "GTA";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #15
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "GCC";
    current_tc->pattern_len = 3;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #16
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "ACGTAGCCT";
    current_tc->pattern_len = 9;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #17
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CGTA";
    current_tc->pattern_len = 4;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #18
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "CGTAGCC";
    current_tc->pattern_len = 7;
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 0;
    current_tc->expected_index = 9;

    current_tc++;
    (*num_testcases)++;


    //Test case #19
    current_tc->text = "ACGTAGCCT";
    current_tc->text_len = 9;
    current_tc->pattern = "ACGTAGCCT";
    current_tc->pattern_len = 9;
    ba = bit_array_create(9);
    bit_array_set_bit(ba, 8);
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 1;
    current_tc->expected_index = 0;

    current_tc++;
    (*num_testcases)++;



    //Test case #20
    current_tc->text = "ACTGACTACTTACT";
    current_tc->text_len = 14;
    current_tc->pattern = "ACT";
    current_tc->pattern_len = 3;
    ba = bit_array_create(14);
    bit_array_set_bit(ba, 6);
    bit_array_set_bit(ba, 13);
    current_tc->Ba = ba;

    current_tc->expected_num_matches = 4;
    current_tc->expected_index = 0;

    current_tc++;
    (*num_testcases)++;



    //##############################
    return;
}

int
main(int argc, const char *argv[]) {
    saidx_t *SA;
    saidx_t i, j, size, left;

    TestCase *test = NULL;
    saidx_t num_testcases = 0;

    get_test_cases(&test, &num_testcases);

    for (i=0; i<num_testcases; i++, test++) {
        printf("Test case (%d).\n", i+1);
        printf("===================\n");

        SA = (saidx_t *)malloc((size_t)test->text_len * sizeof(saidx_t));
        //Todo, check for null

        if(divsufsort(test->text, SA, test->text_len) != 0) {
            fprintf(stderr, "Cannot create SA.\n");
            exit(EXIT_FAILURE);
        }

        /* Search and print */
        size = sa_search(test->text, test->text_len,
                test->pattern, test->pattern_len,
                SA, test->text_len, test->Ba, &left);
        for(j = 0; j < size; ++j) {
            fprintf(stdout, "%" PRIdSAIDX_T "\n", SA[left + j]);
        }

        //fprintf(stdout, "%" PRIdSAIDX_T "\n", size);
        //fprintf(stdout, "%" PRIdSAIDX_T "\n", left);
        assert(test->expected_num_matches == size);
        if (size > 0)
        	assert(test->expected_index == left);


        /* Deallocate memory. */
        free(SA);
    }


    //ToDO: put test case

    return 0;
}
