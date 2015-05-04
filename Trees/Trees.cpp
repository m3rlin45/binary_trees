// Trees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define BOOST_TEST_MAIN
#include <boost\test\unit_test.hpp>
#include "binary_tree_builder.h"
#include "binary_search_tree.h"
#include <iostream>
#include <functional>

void build_test_tree(trees::binary_tree_builder<int> &tree) {
	tree.put_left(4).move_left().put_left(1).put_right(6);
	tree.move_up().put_right(12).move_right();
	tree.put_left(11).put_right(20);
	tree.move_left().put_left(11);
}

BOOST_AUTO_TEST_CASE( pre_order_Traversal_Check ){
	trees::binary_tree_builder<int> tree(10);
	build_test_tree(tree);
	std::vector<int> check{ 10,4,1,6,12,11,11,20 };
	auto pre_ordered = trees::pre_order<int>(tree);
	BOOST_CHECK(check == pre_ordered);
}

BOOST_AUTO_TEST_CASE(in_order_Traversal_Check){
	trees::binary_tree_builder<int> tree(10);
	build_test_tree(tree);
	std::vector<int> check{ 1,4,6,10,11,11,12,20 };
	auto in_ordered = trees::in_order<int>(tree);
	BOOST_CHECK(check == in_ordered);
}

BOOST_AUTO_TEST_CASE(post_order_Traversal_Check) {
	trees::binary_tree_builder<int> tree(10);
	build_test_tree(tree);
	std::vector<int> check{ 1,6,4,11,11,20,12,10 };
	auto post_ordered = trees::post_order<int>(tree);
	BOOST_CHECK(check == post_ordered);
}


BOOST_AUTO_TEST_CASE(binary_search_ordering_test) {
	trees::binary_search_tree<int> search_tree;
	search_tree.insert(10).insert(5).insert(15).insert(20).insert(21).insert(20);
	std::vector<int> check{ 5,10,15,20,21 };
	auto sorted = trees::in_order<int>(search_tree);
	BOOST_CHECK(check == sorted);
}

BOOST_AUTO_TEST_CASE(binary_search_tree_find_success) {
	trees::binary_search_tree<int> search_tree;
	search_tree.insert(10).insert(5).insert(15).insert(20).insert(21).insert(20);

	BOOST_CHECK(search_tree.contains(5));
}

BOOST_AUTO_TEST_CASE(binary_search_tree_find_failure) {
	trees::binary_search_tree<int> search_tree;
	search_tree.insert(10).insert(5).insert(15).insert(20).insert(21).insert(20);

	BOOST_CHECK(!search_tree.contains(1));
}

BOOST_AUTO_TEST_CASE(binary_search_tree_delete_root) {
	trees::binary_search_tree<int> search_tree;
	search_tree.insert(10).insert(5).insert(15).insert(20).insert(21).insert(20);
	search_tree.remove(10);
	std::vector<int> check{ 5,15,20,21 };
	auto sorted = trees::in_order<int>(search_tree);
	BOOST_CHECK(check == sorted);
}

BOOST_AUTO_TEST_CASE(binary_search_tree_delete_only_node) {
	trees::binary_search_tree<int> search_tree;
	search_tree.insert(10);
	search_tree.remove(10);
	auto sorted = trees::in_order<int>(search_tree);
	BOOST_CHECK_EQUAL(sorted.size(), 0);
}

BOOST_AUTO_TEST_CASE(binary_search_tree_delete_one_of_two) {
	trees::binary_search_tree<int> search_tree;
	search_tree.insert(10).insert(5);
	search_tree.remove(10);
	std::vector<int> check{ 5 };
	auto sorted = trees::in_order<int>(search_tree);
	BOOST_CHECK(check == sorted);
}
