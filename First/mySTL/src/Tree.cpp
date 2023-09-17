#include "Tree.h"
#include<list>


namespace my {
	
	void Tree::in_order_traverse(void (*visit)(T))
	{
		node* p = m_head->left;
		while (p == m_head) {
			while (!p->leftT)
				p = p->left;
			visit(p->data);
			while (p->rightT and p->right != m_head) {
				p = p->right;
				visit(p->data);
			}
			p = p->right;
		}
	}

	void Tree::in_order_threading()
	{
		m_head = new node;
		m_head->leftT = true;
		m_head->rightT = false;
		m_head->right = m_head;

		node* p = m_root;
		if (!p)
			m_head->left = m_head;
		else {
			m_head->right = m_root;
			node pre = *m_head;
			in_threading(p, pre);
			pre.rightT = true;
			pre.right = m_head;
			m_head->right = &pre;
		}
	}

	void Tree::in_threading(node* p, node& pre)
	{
		if (p) {
			in_threading(p->left, pre);

			if (p->left) {
				p->leftT = true;
				p->left = &pre;
			}
			if (pre.right) {
				pre.rightT = true;
				pre.right = p;
			}
			pre = *p;
			in_threading(p->right, pre);
		}
	}

	Tree* Tree::build_Huffman_tree(std::vector<float> weight)
	{
		std::list<Tree*> trees;
		for (float i : weight) {
			Tree* p = new Tree;
			p->m_root->weight = i;
			trees.push_back(p);
		}

		auto f = [&]() {
			Tree* ret = trees.front();
			for (Tree* a : trees) {
				ret = ret->root_weight() < a->root_weight() ? ret : a;
			}
			trees.remove(ret);
			return ret;
			};

		while (trees.size() > 1) {
			Tree* minfst = f(), * mincnd = f();
			Tree* newTree = minfst->link_tree(mincnd);
			delete minfst; delete mincnd;
			trees.push_back(newTree);
		}
		return trees.front();
	}
	void Tree::post_order_traverse(node* p, void(*visit)(const T&))
	{
		if (p) {
			post_order_traverse(p->left, visit);
			post_order_traverse(p->right, visit);
			visit(p->data);
		}
	}

	Tree* Tree::link_tree(Tree* other)
	{
		Tree* ret = new Tree;
		ret->m_root->left = node_cpy(this->m_root);
		ret->m_root->right = node_cpy(other->m_root);
		ret->m_root->weight = this->m_root->weight + other->m_root->weight;
		return ret;
	}

}