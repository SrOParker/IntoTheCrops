
#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../../man/utils/types.hpp"
#include "../../engine/teosinteEngine.hpp"

struct Node;
struct CustomDeleter{
	void operator()(Node *n);
};

//Clase para el destructor de Node. 
//Evita el acceso a memoria eliminada

struct DecisionTree{
	//aqui falta decir que en uniqueptr tenga el deleter
	using NodeStorage = std::vector<std::unique_ptr<Node, CustomDeleter>>;
	using MemoryStorage = std::unique_ptr<std::byte[]>;

	DecisionTree(std::size_t bytes = 400);
	//template <typename Mantype, typename E>
	//void run(Mantype& EM , E& ent) noexcept{
	//	if(tree.size() > 0)
	//		tree.back()->run(EM, ent);
	//}
	void run(Manentity_type& EM, Entity& e, EngineGL& GL) noexcept;

	//To add a Node to the tree
	//     createNodeType

	// PARAMETERS FOR THE TEMPLATE
	//
	//	NodeType: specifies the type of the Node
	//  PTs 	: parameters given to the node being created (children and needed)
	//  Returns : reference to the Node created. Adds the node to the tree auto

    template<typename NodeType, typename... PTs>
    NodeType& createNodeType(PTs&&... params);

	//Variable de clase
	std::size_t mem_size{100};
	MemoryStorage mem{std::make_unique<std::byte[]>(mem_size)};

	std::byte* ptr_mem{ mem.get() + mem_size };
	NodeStorage tree{};

};

