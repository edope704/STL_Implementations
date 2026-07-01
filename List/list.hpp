#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>

namespace tgl {

template<class T>
struct list_node 
{
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;

  /**
   * @brief Constructs a new node.
   * @param elem The element to store in the node.
   * @param next Pointer to the next node (default nullptr).
   * @param prev Pointer to the previous node (default nullptr).
   */
  list_node(const_reference elem, list_node* next = nullptr, list_node* prev = nullptr)
    : next_{ next }
    , prev_{ prev }
    , elem_{ elem }
    { }

  list_node* next_;
  list_node* prev_;
  value_type elem_;
}; // list_node

template<class T>
class list_iterator 
{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
    using node              = list_node<T>;

    /**
     * @brief Constructs an iterator from a node pointer.
     * @param it Pointer to the node.
     */
    list_iterator(node* it) : p{ it } { }

    list_iterator& operator--() { p = p->prev_; return *this; }
    list_iterator& operator++() { p = p->next_; return *this; }
    list_iterator operator++(int) { 
      node* temp_p = p;
      p = p->next_;
      return temp_p;
    }

    reference operator*() { return p->elem_; }

    /**
     * @brief Retrieves the underlying node pointer.
     */
    node* get_ptr() const { return p; }

    bool operator==(const list_iterator& it) const { return p == it.p; }
    bool operator!=(const list_iterator& it) const { return p != it.p; }

  private:
    node* p;
}; // list_iterator

/**
 * @brief A generic doubly-linked list implementation.
 * @tparam T The type of elements stored in the list.
 */
template<class T>
class list 
{
  public:
    
    using value_type      = T;
    using size_type       = size_t;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = list_iterator<T>;
    using node            = list_node<T>;

    /**
     * @brief Default constructor. Initializes an empty list.
     */
    list() 
      : head_{ nullptr }
      , tail_{ head_ }
      , size_{ 0 }
      { }
    
    /**
     * @brief Initializes a list containing size default constructed 
     * items of T
     */
    list(size_type size)
      : head_{ nullptr }
      , tail_{ head_ }
      , size_{ 0 }
    {
      for (int i{ 0 }; i<size; i++) 
        push_back( T() );
    }
    
    /**
     * @brief Initializes a list with size copies elem
     */
    list(size_type size, const_reference elem)
      : head_{ nullptr }
      , tail_{ head_ }
      , size_{ 0 }
    {
      for (int i{ 0 }; i<size; i++) 
        push_back( elem );
    }

    list(std::initializer_list<T> init) 
      : head_{ nullptr }
      , tail_{ head_ }
      , size_{ 0 }
      { 
        for (const_reference elem : init)
          push_back( elem );
      }

    iterator begin() { return iterator(head_); }

    iterator end() { return iterator(tail_->next_); }
    
    /**
     * @brief Inserts an element before the specified iterator position.
     * @param it Iterator indicating the position before which to insert.
     * @param elem The element to insert.
     * @return Iterator pointing to the newly inserted element.
     * @todo Implement the insertion logic.
     */
    iterator insert(iterator it, const_reference elem) {
      if (it == begin()) {
        push_front(elem);
        return begin();
      }
      else if (it == end()) {
        push_back(elem);
        return end();
      }
      else {
        node* pos = it.get_ptr();
        node* new_node = new node(elem);
        
        new_node->prev_ = pos->prev_;
        new_node->next_ = pos;
        
        pos->prev_->next_ = new_node;
        pos->prev_ = new_node;

        size_++;
        return iterator(new_node);
      }
    }

    /**
     * @brief Erases the element at the specified iterator position.
     * @param p Iterator pointing to the element to erase.
     * @return Iterator pointing to the element following the erased one.
     * @todo Implement the erase logic.
     */
    iterator erase(iterator it) {
      if (it == begin()) {
        pop_front();
        return begin();
      }
      else if (it == end()) {
        pop_back();
        return end();
      }
      else {
        node* to_erase = it.get_ptr();
        node* to_return = to_erase->next_;
        to_erase->next_->prev_ = to_erase->prev_;
        to_erase->prev_->next_ = to_erase->next_;
        delete to_erase;

        size_--;
        return to_return;
      }
    }

    /**
     * @brief Adds an element to the end of the list.
     * @param elem The element to append.
     */
    void push_back(const_reference elem) {        
      node* new_node{ new node(elem) };
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
      node* new_node{ new node(elem) };
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
        node* to_erase = tail_;
        tail_ = tail_->prev_;
        if (tail_ != nullptr) tail_->next_ = nullptr;
        size_--;
        delete to_erase;
      }
    }
    
    /**
     * @brief Removes the first element from the list.
     */
    void pop_front() {
      if (size_ >= 1) {
        node* to_erase = head_;
        head_ = head_->next_;
        if (head_ != nullptr) head_->prev_ = nullptr;
        size_--;
        delete to_erase;
      }
    }

    reference front() { return head_->elem_; }

    reference back()  { return tail_->elem_; }   

  private:
    node* head_;
    node* tail_;
    
    size_type size_;
   
}; // list
}  // tgl

#endif // LIST_HPP
