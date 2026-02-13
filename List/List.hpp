#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iostream>

template<class T>
class List 
{
  struct Node 
  {
    Node(T elem, Node* next = nullptr, Node* prev = nullptr)
      : next_{ next }
      , prev_{ prev }
      , elem_{ elem }
      { }
    
    void insert_before(Node* next) {
      next->prev_ = this;
      this->next_ = next;
    }

    void insert_after(Node* prev) {
      prev->next_ = this;
      this->prev_ = prev;
    }

    void insert_between(Node* prev, Node* next) {
      insert_after(prev);
      insert_before(next);
    }
  
    Node* next_;
    Node* prev_;
    T elem_;
  }; 

  class iterator 
  {
    private:
      Node* p;

    public:
      iterator(Node* it) : p{ it } { }
      iterator& operator--() { p = p->prev_; return *this; }
      iterator& operator++() { p = p->next_; return *this; }
      iterator  operator++(int) { 
        Node* temp_p = p;
        p = p->next_;
        return p;
      }
      T& operator*() { return p->elem_; }
      Node* get_node() const { return p; }
      bool operator==(const iterator& it) const { return p == it.p; }
      bool operator!=(const iterator& it) const { return p != it.p; }
  };

  public: 
    List() 
      : head_{ nullptr }
      , tail_{ head_ }
      { }

    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(tail_->next_); }
    
    // Inserts elem before it
    //  TO DO
    iterator insert(iterator& it, const T& elem) {
      return begin();
    }

    // erase element before p
    //  TO DO
    iterator erase(iterator p) {
      return begin();
    }

    void push_back(const T& elem) {        
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

    void push_front(const T& elem) {
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
    
    void pop_back() {
      if (size_ >= 1) { 
        tail_ = tail_->prev_;
        if (tail_ != nullptr) tail_->next_ = nullptr;
        size_--;
      }
    }
    
    void pop_front() {
      if (size_ >= 1) { 
        head_ = head_->next_;
        if (head_ != nullptr) head_->prev_ = nullptr;
        size_--;
      }
    }

    T& front() { return head_->elem_; }
    T& back()  { return tail_->elem_; }   

    void print() {
      for(auto it{ begin()}; it != end(); it++) {
        std::cout << *it << ' ';
      }
    }
    
  private:
    Node* head_;
    Node* tail_;

    std::size_t size_{ 0 };
};

#endif // LIST_HPP

