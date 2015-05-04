#ifndef binary_tree_builder_h
#define binary_tree_builder_h
#include "tree_common.h"
#include <memory>

namespace trees {
	template <typename T>
	class binary_tree_builder {		
	private:
		std::unique_ptr<binary_node<T>> root;
		binary_node<T> *cursor;

		void put_child(std::unique_ptr<binary_node<T>> &child, T value){
			if (child) {
				child->value = value;
			} else {
				child = std::make_unique<binary_node<T>>();
				child->parent = cursor;
				child->value = value;
			}
		}
	public:
		binary_tree_builder(T rootVal)
		{
			root = std::make_unique<binary_node<T>>();
			root->value = rootVal;
			cursor = root.get();
		}
		binary_tree_builder<T>& put_left(T value) {
			put_child(cursor->left, value);
			return *this;
		}

		binary_tree_builder<T> & put_right(T value) {
			put_child(cursor->right, value);
			return *this;
		}

		binary_tree_builder<T>& move_left() {
			if (cursor->left) {
				cursor = cursor->left.get();
			} else {
				throw std::runtime_error("No Node left");
			}
			return *this;
		}
		binary_tree_builder<T> & move_right() {
			if (cursor->right) {
				cursor = cursor->right.get();
			}
			else {
				throw std::runtime_error("No Node Right");
			}
			return *this;
		}
		binary_tree_builder<T>& move_up() {
			if (cursor != root.get()){
				cursor = cursor->parent;
			} else {
				throw std::runtime_error("Already at top");
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
