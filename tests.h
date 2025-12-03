#ifndef TESTS_H
#define TESTS_H

void hashT_auto_resize_test();
void hashT_all_collisions_test();
void hashT_delete_chain_middle_test();
void hashT_reinsert_after_delete_test();
void hashT_null_value_test();
void hashT_big_stress_test();
void hashT_foreach_after_delete_test();
void hashT_search_not_found_full_table_test();
void hashT_update_value_test();
void hashT_empty_destroy_test();
void hashT_reinsert_into_deleted_slot_test();
void hashT_resize_ignores_deleted_test();
void hashT_mass_delete_chain_test();
void runAllTests();


#endif