/*
  * Check: a unit test framework for C
  * Copyright (C) 2001, 2002 Arien Malec
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the
  * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
  * MA 02110-1301, USA.
  */

#include <stdlib.h>
#include <check.h>
#include "../linked_list.h"
#include "../process.h"

START_TEST(test_ln)
{
    LinkedList *ll = initLinkedList();
    listNode *ln = malloc(sizeof(listNode));
    process *p = initProcess(NULL, 0, 0);

    ln = initListNode(p);

    ck_assert_ptr_eq(ln->p, p);
    //  ck_assert_str_eq(money_currency(m), "USD");
    //  money_free(m);
}
END_TEST

START_TEST(test_ll_add)
{
    LinkedList *ll = initLinkedList();

    process *p1 = initProcess(NULL, 0, 0);
    process *p2 = initProcess(NULL, 0, 0);

    listNode *ln1 = initListNode(p1);
    listNode *ln2 = initListNode(p2);

    pushToHead(ll, ln1);
    ck_assert_ptr_eq(ll->head->p, p1);
    ck_assert_int_eq(ll->size, 1);

    pushToHead(ll, ln2);
    ck_assert_ptr_eq(ll->tail->p, p1);
    ck_assert_int_eq(ll->size, 2);

    //  money_free(m);
}
END_TEST

START_TEST(test_ll_remove)
{
    LinkedList *ll = initLinkedList();

    process *p1 = initProcess(NULL, 0, 0);
    process *p2 = initProcess(NULL, 0, 0);
    process *p3 = initProcess(NULL, 0, 0);

    listNode *ln1 = initListNode(p1);
    listNode *ln2 = initListNode(p2);
    listNode *ln3 = initListNode(p3);

    pushToHead(ll, ln1);
    pushToHead(ll, ln2);
    pushToHead(ll, ln3);
    ck_assert_int_eq(ll->size, 3);

    listNode *temp = removeNode(ll, ln2);
    ck_assert_ptr_eq(ln2, temp);
    ck_assert_ptr_eq(ll->tail, ln1);
    ck_assert_ptr_eq(ll->head, ln3);
    ck_assert_int_eq(ll->size, 2);

    //  money_free(m);
}
END_TEST

Suite *ll_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Linked List");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_ln);
    tcase_add_test(tc_core, test_ll_add);
    tcase_add_test(tc_core, test_ll_remove);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = ll_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}