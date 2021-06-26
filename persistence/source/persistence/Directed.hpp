// Copyright 2021 Roger Peralta Aranibar
#ifndef SOURCE_POINTER_MACHINE_DIRECTED_GRAPH_HPP_
#define SOURCE_POINTER_MACHINE_DIRECTED_GRAPH_HPP_

#include <cstddef>
#include <iostream>

namespace ADE {
//namespace PointerMachine {
//template <typename Type, typename Node>
//class DirectedGraph;
		
	template <typename Type>
	class Node {
	public:
		typedef Type data_type;
		
		//Node() : data_(nullptr), forward_(nullptr), out_ptrs_size_(0) {}
		
		Node(data_type data, std::size_t const& out_ptrs_size)
			: data_(new data_type(data)),
			out_ptrs_size_(out_ptrs_size){
			forward_=new Node<Type>*[out_ptrs_size](); }
		virtual ~Node() {}	
		//data_type get_data() { return *data_; }
		
		/*bool set_data(data_type const& data) {
		data(new data_type(data_));
		return true;
		}*/
		
		/**
		*
		*  \brief Insert element
		*  Inserts an element at the location id and returns the vertex pointer for
		* the new vertex.
		*
		*/
		/*Node* insert_vertex(std::size_t const& position, data_type const& data) {
		if (out_ptrs_size_ < position) {
		throw std::out_of_range("Insert position is out of edges range.");
		}
		Node* next_node_ptr = forward_[position];
		Node* new_node = new Node(data, out_ptrs_size_);
		
		new_node->forward_[position] = next_node_ptr;
		
		forward_[position] = new_node;
		return forward_[position];
		}*/
		
		
		/**
		*  \brief Attachs two nodes
		*
		*  Adds an edge to v and throws and exception of type std::out_of_range
		* if position is not within the range of u nodes.
		*
		*/
		/*bool update_edge(std::size_t const& position, Node* v) {
		if (out_ptrs_size_ < position) {
		throw std::out_of_range("Position out of first argument node.");
			}
		forward_[position] = v;
		return true;
		}*/
			
		/**
		*  \brief Access specified element
		*
		*  Returns a reference to the element at specified location position. If id
		* is not within the range of the container an exception of type
		* std::out_of_range is thrown. If no node exist at the location
		* std::logic_error is thrown.
		*
		*/
		Node& operator[](std::size_t const& id) const {
			if (out_ptrs_size_ < id) {
				throw std::out_of_range("Index out of node edges range.");
			}
			if (!forward_[id]) {
				throw std::logic_error("Access to null reference.");
			}
			return *forward_[id];
		}
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		void operator =(Node<data_type> &a)
		{
			data_ = a.data_;
			for(int i = 0 ;i<out_ptrs_size_;++i){
				forward_[i] = a.forward_[i];  
			}
			//forward_ = a.forward_;
			out_ptrs_size_ = a.out_ptrs_size_;     
		}
		
		///////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		
			data_type* data_;
			std::size_t out_ptrs_size_;
			Node** forward_;
			
			//friend class DirectedGraph<Type, Node>;
	};
		
	template <typename Type, typename Node>
	class DirectedGraph {
	public:
		typedef Type data_type;
		
		DirectedGraph(data_type const data, std::size_t const& out_ptrs_size, std::size_t const& in_ptrs_size)
			: root_ptr_(new Node(data, out_ptrs_size, in_ptrs_size)),
			out_ptrs_size_(out_ptrs_size) {}
		
		virtual ~DirectedGraph() {}
		
		Node* get_root_ptr() { return root_ptr_; }//retorna el la raiz
		
		//////////////////////////////////////////////////////////////////////////////////////////			
		/////////////////////////////////////////////////////////////////////////////////////////
			
			
		Node* insert_vertex(data_type const data, Node* u, std::size_t position) {
			if (u->out_ptrs_size_ != out_ptrs_size_) {
				throw std::logic_error("Node with different number of out pointers.");
			}
			if (out_ptrs_size_ < position) {
				throw std::out_of_range("Insert position out of node edges range.");
			}
			Node* next_node_ptr = dynamic_cast<Node*>(u->forward_[position]);
			Node* new_node = new Node(data, out_ptrs_size_);
			new_node->forward_[position] = next_node_ptr;
			u->forward_[position] = new_node;
			return dynamic_cast<Node*>(u->forward_[position]);
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Node get_root() { return *root_ptr_; }//retorna el valor de la raiz
		
		/**
		*  \brief Attachs two nodes
		*
		*  Adds edge from u to v and throws and exception of type std::out_of_range
		* if position is not within the range of u nodes,
		*
		*/
		void add_edge(Node* u, Node* v, std::size_t const& position) {
			if (u->out_ptrs_size_ < position) {
				throw std::out_of_range("Position out of first argument node.");
			}
			u->forward_[position] = v;
		}
		
		protected:
			Node* root_ptr_;
			std::size_t out_ptrs_size_;
	};
		
//}  // namespace PointerMachine
}  // namespace ADE
#endif  // SOURCE_POINTER_MACHINE_DIRECTED_GRAPH_HPP_
