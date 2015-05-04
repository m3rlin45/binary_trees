#ifndef binary_search_tree_h
#define binary_search_tree_h
#include "tree_common.h"
#include <memory>

namespace trees {
	template <typename T>
	class binary_search_tree {
	private:
		std::unique_ptr<binary_node<T>> root;

		void my_insert(binary_node<T> &root, T value) {
			if (root.value > value) {
				if (root.left) {
					my_insert(*root.left, value);
				}
				else {
					root.left = std::make_unique<binary_node<T>>(value, &root);
				}
			}
			else if(root.value < value){
				if (root.right) {
					my_insert(*root.right, value);
				}
				else {
					root.right = std::make_unique<binary_node<T>>(value, &root);
				}
			}
		}

		binary_node<T> * my_find(T value) {
			auto cursor = root.get();
			while (cursor) {
				if (cursor->value == value) {
					return cursor;
				}
				else if (cursor->value > value) {
					cursor = cursor->left.get();
				}
				else {
					cursor = cursor->right.get();
				}
			}
			return nullptr;
		}

		void my_delete_node(binary_node<T> *&node) {
			//check if root
			if (node && node == root.get()) {
				root = nullptr;
				node == nullptr;
			}
			else if (node && node->parent) {//find the owner and kill it
				auto parent = node->parent;
				if (parent->left && parent->left.get() == node) {
					parent->left = nullptr;
					node = nullptr;
				}
				else if (parent->right && parent->right.get() == node) {
					parent->right = nullptr;
					node = nullptr;
				}
			}
		}

		void my_remove(binary_node<T> *node) {
			//if it's got no children, just delete it
			if (!node->left && !node->right) {
				my_delete_node(node);
			}
			else if (node->left && !node->right) { // if it only has left child, copy the value and remove it
				node->value = node->left->value;
				my_remove(node->left.get());
			}
			else if (node->right && !node->left) {  //if it only has a right child, copy the val and remove it
				node->value = node->right->value;
				my_remove(node->right.get());
			}
			else { //it has two children

			}
		}

	public:
		binary_search_tree &insert(T value) {
			if (root) {
				my_insert(*root, value);
			}
			else {
				root = std::make_unique<binary_node<T>>(value, nullptr);
			}
			return *this;
		}

		bool contains(T value) {
			return my_find(value);
		}

		binary_search_tree &remove(T value) {
			auto node = my_find(value);
			if (node) {
				my_remove(node);
			}
			return *this;
		}

		template<typename Tv>
		void applyTraverser(Tv &traverser)
		{
			if (root)
			{
				traverser.visit(*root);
			}
		}
	};


}



#endif
