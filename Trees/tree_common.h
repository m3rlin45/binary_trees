#ifndef tree_common_h
#define tree_common_h
#include <memory>
#include <functional>
#include <list>
#include <iomanip>

namespace trees {

	template <typename T>
	struct binary_node {
		binary_node() {}
		binary_node(T value, binary_node<T> * parent)
			: parent(parent), value(value) {}
		std::unique_ptr<binary_node<T>> left;
		std::unique_ptr<binary_node<T>> right;
		binary_node * parent;
		T value;
	};


	template<typename T>
	class inOrderVisitorRecurse {
		std::function<void(T)> my_visit_func;
	public:
		inOrderVisitorRecurse(std::function<void(T)> visit_func)
		:my_visit_func(visit_func){}

		void visit(binary_node<T> &root) {
			if (root.left)
			{
				visit(*root.left); //visit our left side first
			}
			my_visit_func(root.value); //visit me
			if (root.right)
			{
				visit(*root.right); //visit my right
			}
		}
	};

	template<typename T>
	class preOrderVisitorRecurse {
		std::function<void(T)> my_visit_func;
	public:
		preOrderVisitorRecurse(std::function<void(T)> visit_func)
			:my_visit_func(visit_func) {}

		void visit(binary_node<T> &root) {
			my_visit_func(root.value); //visit me
			if (root.left)
			{
				visit(*root.left); //visit our left side first
			}
			if (root.right)
			{
				visit(*root.right); //visit my right
			}
		}
	};

	template<typename T>
	class post_order_visitor {
		std::function<void(T)> my_visit_func;
	public:
		post_order_visitor(std::function<void(T)> visit_func)
			:my_visit_func(visit_func) {}

		void visit(binary_node<T> &root) {
			if (root.left)
			{
				visit(*root.left); //visit our left side first
			}
			if (root.right)
			{
				visit(*root.right); //visit my right
			}
			my_visit_func(root.value); //visit me
		}
	};

	template<typename T>
	class levelOrderVisitor {
		std::function<void(T)> my_visit_func;
	public:
		levelOrderVisitor(std::function<void(T)> visit_func)
			:my_visit_func(visit_func) {}

		void visit(binary_node<T> &root) {
			std::list<binary_node<T>*> to_visit;
			to_visit.push_back(&root);
			while (!to_visit.empty()) {
				auto node = to_visit.front();
				to_visit.pop_front();
				my_visit_func(node->value);//visit
				//queue any other nodes
				if (node->left){
					to_visit.push_back(node->left.get());
				}
				if (node->right) {
					to_visit.push_back(node->right.get());
				}
			}
		}
	};

	template<typename Tval, typename Ttree>
	std::vector<Tval> in_order(Ttree &tree) {
		std::vector<Tval> ret;
		std::function<void(Tval)> recorder = [&ret](Tval val) { ret.push_back(val); };
		trees::inOrderVisitorRecurse<Tval> inOrder(recorder);
		tree.applyTraverser(inOrder);
		return ret;
	}

	template<typename Tval, typename Ttree>
	std::vector<Tval> pre_order(Ttree &tree) {
		std::vector<Tval> ret;
		std::function<void(Tval)> recorder = [&ret](Tval val) { ret.push_back(val); };
		trees::preOrderVisitorRecurse<Tval> preOrder(recorder);
		tree.applyTraverser(preOrder);
		return ret;
	}

	template<typename Tval, typename Ttree>
	std::vector<Tval> post_order(Ttree &tree) {
		std::vector<Tval> ret;
		std::function<void(Tval)> recorder = [&ret](Tval val) { ret.push_back(val); };
		trees::post_order_visitor<Tval> post_order(recorder);
		tree.applyTraverser(post_order);
		return ret;
	}

	int intPow(int base, int exp) {
		int ret = 1;
		for (int i = 0; i < exp; i++) {
			ret *= base;
		}
		return ret;
	}

	template<typename T>
	class treePrinter {
	public:
		void visit(binary_node<T> &root) {
			std::list<std::list<binary_node<T>*>> levels;

			levels.emplace_back();
			levels.back().push_back(&root);
			while (!levels.back().empty()) {
				std::list<binary_node<T>*> newLevel;
				for (auto node : levels.back()){
					if (!node) {
						continue;
					}
					if (node->left) {
						newLevel.push_back(node->left.get());
					}
					else {
						newLevel.push_back(nullptr);
					}
					if (node->right) {
						newLevel.push_back(node->right.get());
					}
					else {
						newLevel.push_back(nullptr);
					}
				}
				levels.emplace_back(std::move(newLevel));
			}

			levels.pop_back();
			levels.pop_back(); //get rid of empty and all null levels
			int offset = levels.size();
			int levelNum = 0;
			while (!levels.empty())
			{
				offset--;

				for (auto node : levels.front()) {
					if (node) {
						std::cout << std::setw(3 * intPow(2, offset)) << node->value;
					}
					else {
						std::cout << std::setw(3 * intPow(2, offset)) << " ";
					}
				}
				std::cout << std::endl;
				levels.pop_front();
			}
		}
	};
}

#endif
