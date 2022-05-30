
#include "dt.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "Node.hpp"
#include "Node_Attack.hpp"
#include "Node_Chase.hpp"
#include "Node_StandBy.hpp"
#include "Node_InRange.hpp"
#include "Node_Candil.hpp"
#include "Node_See.hpp"
#include "Node_Wander.hpp"

void CustomDeleter::operator()(Node *n){ n->~Node(); }

DecisionTree::DecisionTree(std::size_t bytes)
		: mem_size{bytes}
	{ 

		auto& attack   = createNodeType<Node_Attack>();  //Leaf
		auto& chase    = createNodeType<Node_Chase>();   //Leaf
		auto& range    = createNodeType<Node_InRange>(attack, chase); 
		auto& standby  = createNodeType<Node_StandBy>(); //Leaf
		auto& candil   = createNodeType<Node_Candil>(standby, range); 
		auto& wander   = createNodeType<Node_Wander>();  //Leaf
		
		//Root node
		createNodeType<Node_See>(candil, wander); 
	}

void DecisionTree::run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept{
	if(tree.size() > 0)
		tree.back()->run(EM, e, GL);
}

template<typename NodeType, typename... PTs>
NodeType& DecisionTree::createNodeType(PTs&&... params) {
	auto* ptr_node = ptr_mem - sizeof(NodeType);
	NodeType* node = new (ptr_node) NodeType(std::forward<PTs>(params)...); 
	tree.emplace_back( node ); 
	ptr_mem = ptr_node; 
	return *node;
}