// Copyright 2021 Roger Peralta Aranibar
#ifndef SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
#define SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

#include <vector>
#include <utility>
#include "Directed.hpp"

namespace ADE {
namespace Persistence {

template <typename Type>
class PartialNode : public Node<Type>{
 public:
  typedef Type data_type;

  
 // PartialNode() {}

  PartialNode(data_type data, std::size_t const& out_ptrs_size,
              std::size_t const& in_ptrs_size) 
		: Node<Type>(data,out_ptrs_size),
		modificaciones(0),
		//backward_ = new PartialNode<Type>*[in_ptrs_size]()
		backward_ ( new PartialNode<Type>*[in_ptrs_size]())
  {
	version=std::vector<int>(in_ptrs_size*2,0);
	for(int i=0;i<in_ptrs_size*2;++i){
		Table.emplace_back(data,out_ptrs_size);
	}
	
    //backward_ = new PartialNode<Type>*[in_ptrs_size]();
  }
  
/////////////////////////////////////////////////////////////////////////////////
  //data_type get_data(unsigned int version) { return data_; }
  data_type get_data(unsigned int version) { return *Node<Type>::data_; }

  //bool set_data(data_type const& data) { return true; }
	bool set_data(data_type const data){
		*Node<Type>::data_=data;
		return true;
	}
/////////////////////////////////////////////////////////////////////////////////////
	
	bool set_ptr(PartialNode* ptr, unsigned int id){
		Node<Type>::forward_ = ptr;
		return true;
	}

///////////////////////////////////////////////////////////////////////////////////
/*
	PartialNode* insert_vertex(std::size_t const& position,
                             data_type const& data) {
    return nullptr;
  }*/
		
/////////////////////////////////////////////////////////////////////////////////////
  
	//bool update_edge(std::size_t const& position, PartialNode* v) { return true; }

/////////////////////////////////////////////////////////////////////////////////

  PartialNode& operator[](std::size_t id) const {
	  return *dynamic_cast<PartialNode*>(&(Node<Type>::operator[](id)));
  }
	
  PartialNode& operator[](
    //  std::pair<std::size_t, unsigned int> const& position_version) const {
	  std::pair<std::size_t, unsigned int> id_version) const {
	  int i=0;
	  while(i<modificaciones && version[i]<=id_version.second)i++;
	  i--;
	  return *dynamic_cast<PartialNode*>(Table[i].forward_[id_version.first]);
    //return 0;
  }
  
  
  ////////////////////////////////////////////////////////
  int modificaciones;
  std::vector<Node<data_type>> Table;
  std::vector<int> version;
  /////////////////////////////////////////////////////////////
  //data_type* data_;
  std::size_t out_ptrs_size_;
  PartialNode** forward_;

  std::size_t in_ptrs_size_;
  //std::size_t current_modifications_size_;
  //std::size_t current_back_pointer_size_;

  PartialNode** backward_;
  // TODO: Table mods, 2 * in_ptrs_size_
};

template <typename Type, typename Node = PartialNode<Type>>
class PartialDirectedGraph : public DirectedGraph<Type, Node> {
 public:
  typedef Type data_type;

  PartialDirectedGraph(data_type const data, std::size_t const& out_ptrs_size,
                       std::size_t const& in_ptrs_size) 
	  : DirectedGraph<Type, Node>(data, out_ptrs_size,in_ptrs_size),
	  in_ptrs_size_(in_ptrs_size),
	  current_version_(0) {}
  
///////////////////////////////////////////////////////////////////////////////////////////////
  //Node* get_root_ptr(unsigned int const& version) { return nullptr; }
  Node* get_root_ptr() {
	  return DirectedGraph<Type, Node>::get_root_ptr();
  }
  
  Node* get_root_ptr(unsigned int version) {
	  return DirectedGraph<Type, Node>::get_root_ptr();
  }
  //Node get_root(unsigned int const& version) { return; }
  
///////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  
  Node* insert_vertex(data_type const data, Node* u, std::size_t position){
	 // ++(*current_version_);
	  ++current_version_;
	  return insert_vertex(data, u, position, current_version_);
  }
	  
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
  
  void add_edge(Node* u, Node* v, std::size_t position) {
    //++(*current_version_);
	  ++current_version_;
    //return true;
	return add_edge(u, v, position, current_version_);
  }
  
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
  private:
  Node* insertarV(data_type const data, Node* u, std::size_t position, unsigned int version_)
  {
	  Node* new_node = new Node(data, DirectedGraph<Type, Node>::out_ptrs_size_,in_ptrs_size_);
	  u->version[u->modificaciones] = version_;
	  if(u->modificaciones>0)
		  u->Table[(u->modificaciones)] = u->Table[(u->modificaciones)-1];
	  new_node->backward_[position] = u;    
	  u->Table[(u->modificaciones)].forward_[position] = new_node;
	  (u->modificaciones)++; 
	  return dynamic_cast<Node*>(u->Table[u->modificaciones-1].forward_[position]);
	    
  } 

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
  
  Node* insert_vertex(data_type const data, Node* u, std::size_t position, unsigned int version_){
	  if(u->modificaciones < in_ptrs_size_*2)
	  {
		  return insertarV(data, u, position, version_);
	  } 
	  else
	  {
		  Node* new_u = new Node(*(u->data_), DirectedGraph<Type, Node>::out_ptrs_size_,in_ptrs_size_);
		  for(int i = 0;i<int(in_ptrs_size_);++i)
		  {
			  if(u->backward_[i]!=nullptr)
			  {
				  add_edge(u->backward_[i],new_u,i);
			  }
		  }
		  return insertarV(data,new_u, position,version_);
	  }         
  }
	  
///////////////////////////////////////////////////////////////////////////////////////////////////	  
///////////////////////////////////////////////////////////////////////////////////////////////
  
  void add_edge(Node* u, Node* v, std::size_t position, unsigned int version_) {
	  if( (u->modificaciones)< in_ptrs_size_*2)
	  {
		  u->version[u->modificaciones] = version_;
		  u->Table[u->modificaciones].forward_[position] = v;
		  v->backward_[position] = u;
		  (u->modificaciones)++; 
	  }
	  else
	  {
		  Node* new_u = new Node(*(u->data_), DirectedGraph<Type, Node>::out_ptrs_size_,in_ptrs_size_); 
		  for(int i = 0;i<int(in_ptrs_size_);++i)
		  {
			  if(u->backward_[i]!=nullptr)
			  {
				  add_edge(u->backward_[i],new_u,i);
			  }
		  }
		  new_u->version[u->modificaciones] = version_;
		  new_u->Table[u->modificaciones].forward_[position] = v;
		  v->backward_[version_] = new_u; 
		  (new_u->modificaciones)++;
	  }
	  // return DirectedGraph<Type, Node>::add_edge(u, v, position);
  }

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////	  
	  
  protected:
  unsigned int current_version_;
  std::size_t in_ptrs_size_;

  Node* root_ptr_;
  std::size_t out_ptrs_size_;
};

}  // namespace Persistence
}  // namespace ADE

#endif  // SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
