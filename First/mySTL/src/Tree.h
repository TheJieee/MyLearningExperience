#pragma once
#include <vector>
#include <iostream>

typedef int T;
namespace my {

	class Tree
	{
	public:
		
		Tree() 
		{
			node* p = new node; 
			m_root = p;
		}

		void in_order_traverse(void (*visit)(T));

		void in_order_threading();

		Tree* build_Huffman_tree(std::vector<float> weight);

		void print()
		{
			std::cout << "print" << std::endl;
		}

		void post_order_traverse(void (*visit)(const T&)) { post_order_traverse(m_head, visit); }

		float root_weight()const { return m_root->weight; }

		Tree* link_tree(Tree* other);

		~Tree() { post_order_traverse(m_root, [](const T& t) { delete (node*)&t; } ); }
	private:
		struct node {
			T data;
			float weight;
			bool rightT = false;
			bool leftT = false;
			node* right = nullptr;
			node* left = nullptr;
		};
		node* m_head = nullptr;
		node* m_root = nullptr;

		int m_depth = 1;

		void in_threading(node* p, node& pre);

		void post_order_traverse(node* p, void (*visit)(const T&));

		node* node_cpy(node* nd) { return new node(*nd); }
	};
}