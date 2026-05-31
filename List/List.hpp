#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iterator>
// #include <iostream>

namespace tgl {

/**
 * @brief A generic doubly-linked list implementation.
 * @tparam T The type of elements stored in the list.
 */
template<class T>
class List 
{
  private:
    struct Node; 

  public:
    // Type definitions
    using value_type      = T;
    using size_type       = size_t;
    using reference       = T&;
    using const_reference = const T&;

    class iterator 
    {
      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

      private:
        Node* p;

      public:
        /**
         * @brief Constructs an iterator from a node pointer.
         * @param it Pointer to the node.
         */
        iterator(Node* it) : p{ it } { }

        iterator& operator--() { p = p->prev_; return *this; }
        iterator& operator++() { p = p->next_; return *this; }
        iterator operator++(int) { 
          Node* temp_p = p;
          p = p->next_;
          return temp_p;
        }

        reference operator*() { return p->elem_; }

        /**
         * @brief Retrieves the underlying node pointer.
         */
        Node* get_ptr() const { return p; }

        bool operator==(const iterator& it) const { return p == it.p; }
        bool operator!=(const iterator& it) const { return p != it.p; }
    };

    /**
     * @brief Default constructor. Initializes an empty list.
     */
    List() 
      : head_{ nullptr }
      , tail_{ head_ }
      { }

    /**
     * @brief Returns an iterator to the beginning of the list.
     */
    iterator begin() { return iterator(head_); }

    /**
     * @brief Returns an iterator to the end of the list.
     */
    iterator end() { return iterator(nullptr); }
    
    /**
     * @brief Inserts an element before the specified iterator position.
     * @param it Iterator indicating the position before which to insert.
     * @param elem The element to insert.
     * @return Iterator pointing to the newly inserted element.
     * @todo Implement the insertion logic.
     */
    iterator insert(iterator& it, const_reference elem) {
      return begin();
    }

    /**
     * @brief Erases the element at the specified iterator position.
     * @param p Iterator pointing to the element to erase.
     * @return Iterator pointing to the element following the erased one.
     * @todo Implement the erase logic.
     */
    iterator erase(iterator p) {
      return begin();
    }

    /**
     * @brief Adds an element to the end of the list.
     * @param elem The element to append.
     */
    void push_back(const_reference elem) {        
      Node* new_node{ new Node(elem) };
      if (size_ == 0) {
        head_ = new_node;
        tail_ = head_;
      } else {
        tail_->next_ = new_node;
        new_node->prev_ = tail_;
        tail_ = new_node;
      }
      size_++;
    }

    /**
     * @brief Adds an element to the beginning of the list.
     * @param elem The element to prepend.
     */
    void push_front(const_reference elem) {
      Node* new_node{ new Node(elem) };
      if (size_ == 0) {
        head_ = new_node;
        tail_ = head_;
      } else {
        head_->prev_ = new_node;
        new_node->next_ = head_;
        head_ = new_node;
      }
      size_++;
    }
    
    /**
     * @brief Removes the last element from the list.
     */
    void pop_back() {
      if (size_ >= 1) { 
        tail_ = tail_->prev_;
        if (tail_ != nullptr) tail_->next_ = nullptr;
        size_--;
      }
    }
    
    /**
     * @brief Removes the first element from the list.
     */
    void pop_front() {
      if (size_ >= 1) { 
        head_ = head_->next_;
        if (head_ != nullptr) head_->prev_ = nullptr;
        size_--;
      }
    }

    /**
     * @brief Accesses the first element of the list.
     * @return Reference to the first element.
     */
    reference front() { return head_->elem_; }

    /**
     * @brief Accesses the last element of the list.
     * @return Reference to the last element.
     */
    reference back()  { return tail_->elem_; }   

  private:

    struct Node 
    {
      /**
       * @brief Constructs a new Node.
       * @param elem The element to store in the node.
       * @param next Pointer to the next node (default nullptr).
       * @param prev Pointer to the previous node (default nullptr).
       */
      Node(const_reference elem, Node* next = nullptr, Node* prev = nullptr)
        : next_{ next }
        , prev_{ prev }
        , elem_{ elem }
        { }
  
      Node* next_;
      Node* prev_;
      value_type elem_;
    }; 

    Node* head_;
    Node* tail_;

    size_type size_{ 0 };

}; // List
}  // tgl

#endif // LIST_HPP
