/*
 * Unit tests for internal insertion sort functions.
 * These functions are static in tables.c, so we include the source directly.
 */
#include "testlib.h"

/* Include tables.c to access static functions */
#include "../tskit/tables.c"

static void
test_insertion_sort_segments_empty(void)
{
    tsk_segment_t segments[1];
    /* n=0 should be a no-op */
    insertion_sort_segments(segments, 0);
}

static void
test_insertion_sort_segments_single(void)
{
    tsk_segment_t segments[1] = {{ .left = 1.0, .node = 5 }};
    insertion_sort_segments(segments, 1);
    CU_ASSERT_EQUAL(segments[0].left, 1.0);
    CU_ASSERT_EQUAL(segments[0].node, 5);
}

static void
test_insertion_sort_segments_sorted(void)
{
    tsk_segment_t segments[3] = {
        { .left = 1.0, .node = 0 },
        { .left = 2.0, .node = 1 },
        { .left = 3.0, .node = 2 }
    };
    insertion_sort_segments(segments, 3);
    CU_ASSERT_EQUAL(segments[0].left, 1.0);
    CU_ASSERT_EQUAL(segments[1].left, 2.0);
    CU_ASSERT_EQUAL(segments[2].left, 3.0);
}

static void
test_insertion_sort_segments_reverse(void)
{
    tsk_segment_t segments[3] = {
        { .left = 3.0, .node = 2 },
        { .left = 2.0, .node = 1 },
        { .left = 1.0, .node = 0 }
    };
    insertion_sort_segments(segments, 3);
    CU_ASSERT_EQUAL(segments[0].left, 1.0);
    CU_ASSERT_EQUAL(segments[1].left, 2.0);
    CU_ASSERT_EQUAL(segments[2].left, 3.0);
}

static void
test_insertion_sort_segments_same_left(void)
{
    /* Same left coordinate - should sort by node (secondary key) */
    tsk_segment_t segments[3] = {
        { .left = 1.0, .node = 5 },
        { .left = 1.0, .node = 2 },
        { .left = 1.0, .node = 8 }
    };
    insertion_sort_segments(segments, 3);
    CU_ASSERT_EQUAL(segments[0].node, 2);
    CU_ASSERT_EQUAL(segments[1].node, 5);
    CU_ASSERT_EQUAL(segments[2].node, 8);
}

static void
test_insertion_sort_node_ids_empty(void)
{
    tsk_id_t ids[1];
    insertion_sort_node_ids(ids, 0);
}

static void
test_insertion_sort_node_ids_single(void)
{
    tsk_id_t ids[1] = { 42 };
    insertion_sort_node_ids(ids, 1);
    CU_ASSERT_EQUAL(ids[0], 42);
}

static void
test_insertion_sort_node_ids_sorted(void)
{
    tsk_id_t ids[5] = { 1, 2, 3, 4, 5 };
    insertion_sort_node_ids(ids, 5);
    CU_ASSERT_EQUAL(ids[0], 1);
    CU_ASSERT_EQUAL(ids[4], 5);
}

static void
test_insertion_sort_node_ids_reverse(void)
{
    tsk_id_t ids[5] = { 5, 4, 3, 2, 1 };
    insertion_sort_node_ids(ids, 5);
    CU_ASSERT_EQUAL(ids[0], 1);
    CU_ASSERT_EQUAL(ids[1], 2);
    CU_ASSERT_EQUAL(ids[2], 3);
    CU_ASSERT_EQUAL(ids[3], 4);
    CU_ASSERT_EQUAL(ids[4], 5);
}

static void
test_insertion_sort_node_ids_random(void)
{
    tsk_id_t ids[6] = { 3, 1, 4, 1, 5, 9 };
    insertion_sort_node_ids(ids, 6);
    CU_ASSERT_EQUAL(ids[0], 1);
    CU_ASSERT_EQUAL(ids[1], 1);
    CU_ASSERT_EQUAL(ids[2], 3);
    CU_ASSERT_EQUAL(ids[3], 4);
    CU_ASSERT_EQUAL(ids[4], 5);
    CU_ASSERT_EQUAL(ids[5], 9);
}

int
main(int argc, char **argv)
{
    CU_TestInfo tests[] = {
        { "test_insertion_sort_segments_empty", test_insertion_sort_segments_empty },
        { "test_insertion_sort_segments_single", test_insertion_sort_segments_single },
        { "test_insertion_sort_segments_sorted", test_insertion_sort_segments_sorted },
        { "test_insertion_sort_segments_reverse", test_insertion_sort_segments_reverse },
        { "test_insertion_sort_segments_same_left", test_insertion_sort_segments_same_left },
        { "test_insertion_sort_node_ids_empty", test_insertion_sort_node_ids_empty },
        { "test_insertion_sort_node_ids_single", test_insertion_sort_node_ids_single },
        { "test_insertion_sort_node_ids_sorted", test_insertion_sort_node_ids_sorted },
        { "test_insertion_sort_node_ids_reverse", test_insertion_sort_node_ids_reverse },
        { "test_insertion_sort_node_ids_random", test_insertion_sort_node_ids_random },
        CU_TEST_INFO_NULL,
    };
    return test_main(tests, argc, argv);
}
