// Copyright 2021 Roger Peralta Aranibar
#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <thread>

// TODO: Uncommend after implement the partial structure
#include "persistence/partial_directed_graph.hpp"
#include "persistence/Directed.hpp"
//#include "pointer_machine/directed_graph.hpp"
/*
void test_directed_graph() {
  std::cout << "Directed Graph"
            << "\n";
  // Create a DirectedGraph, a maximum of 5 edge for each node and the root with
  // the starting value of 1.
  ADE::PointerMachine::DirectedGraph<int, ADE::PointerMachine::Node<int>>
      my_graph(1, 5);//1 es el valor del root, y 5 es la cantidad de nodos que pueden apuntar

  // We can obtain the root and print their value.
  ADE::PointerMachine::Node<int>* root_ptr = my_graph.get_root_ptr();
  std::cout << "Root Value: " << root_ptr->get_data() << "\n";  //obtener el valor del root

  // Also, we can insert a new vertex passing the new Node value, and the index
  // of the pointer that will be used to point the inserted node.
  my_graph.get_root().insert_vertex(0, 2);  // 1[0] -> 2

  std::cout << "Inserted Value: " << my_graph.get_root()[0].get_data()//impime en la posiscion 0 imrimiria el 2
            << "\n";  // 2

  // Likewise, the method to insert a new vertex, returns a reference of the
  // new vertex inserted.
  ADE::PointerMachine::Node<int>* other_inserted_node_ptr =
      my_graph.get_root()[0].insert_vertex(1, 3);  // 1[0] -> 2[1] -> 3

  std::cout << "Inserted Value: " << my_graph.get_root()[0][1].get_data()
            << "\n";  // 3

  // To add an edge between two vertex, we call the function update edge from
  // the startin Node with the index id that will link both nodes.
  my_graph.get_root().update_edge(1,
                                  other_inserted_node_ptr);  // 5[0] -> 2[1] ->
                                                             // 3 5[1]   -> 3

  std::cout << "Following other Edge: " << my_graph.get_root()[1].get_data()
            << "\n";
}
*/
///*
void test_directed_graph() {

	ADE :: Persistence :: PartialDirectedGraph<int> my_graph(1,4,5);
	ADE :: Persistence :: PartialNode<int> *root_ptr =my_graph.get_root_ptr();
	
	std::cout<< "Dato de la RAIZ: "<< *root_ptr->data_ << std::endl;
	ADE:: Persistence :: PartialNode<int>* inserted_node_ptr = my_graph.insert_vertex(4, root_ptr, 0);
	//////////////////////////////////////////////////////////////////////////////
	std::cout<<"Next RAIZ: "<< *inserted_node_ptr->data_ << std::endl;
	ADE:: Persistence :: PartialNode<int>* Ptr_1 = my_graph.insert_vertex(5, root_ptr, 0);
	ADE:: Persistence :: PartialNode<int>* Ptr_2 = my_graph.insert_vertex(8, root_ptr, 0);
	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	
	std::cout<< "version: 1 posisicion[0] = " << *(*root_ptr)[{0,1}].data_<< std::endl;  
	std::cout<< "version: 2 posisicion[0] = " << *(*root_ptr)[{0,2}].data_<< std::endl;
	
}
//*/
int main() {
  test_directed_graph();

  return 0;
}
