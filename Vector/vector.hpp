#ifndef VECTOR_HPP
#define VECTOR_HPP 

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <limits>

namespace tgl {
template <class T>
class vector 
{
  private:
    T* elem_;
    size_t size_;
    size_t capacity_;

    class iterator
    { };

  public:
    vector(std::size_t capacity = 10) 
      : size_{ 0 }
      , capacity_{ capacity_ }
      , elem_{ new T[capacity_] } 
      { }

    vector(std::initializer_list<T> init)
      : size_{ int(init.size()) }
      , capacity_{ size_ }
      , elem_{ new T[capacity_] } 
    { 
      std::copy(init.begin(), init.end(), elem_); 
    }

    vector(const vector& vec) 
      : size_{ vec.size_ }
      , capacity_{ vec.capacity_ }
      , elem_{ new T[capacity_] }
    {
      std::copy(vec.elem_, vec.elem_+vec.size_, this->elem_);
    }

    vector(vector&& vec) 
      : size_{ vec.size_ }
      , capacity_{ vec.capacity_ }
      , elem_{ new T[capacity_]}
    {
      std::copy(vec.elem_, vec.elem_+vec.size_, this->elem_);
      vec.elem_ = nullptr;
    }

    vector& operator=(const vector& vec)
    {
      T *new_elem = new T[vec.size_];
      std::copy(vec.elem_, vec.elem_+vec.size_, new_elem);
      
      delete[] this->elem_;
      this->size_ = vec.size_;
      this->capacity_ = vec.capacity_;
      this->elem_ = new_elem;
      return *this;
    }
    
    vector& operator=(vector&& vec)
    { 
      delete[] this->elem_;
      this->size_ = std::exchange(vec.size_, 0);
      this->capacity_ = std::exchange(vec.capacity_, 0);
      this->elem_ = std::exchange(vec.elem_, nullptr);
      return *this;
    }

    ~vector()
    {
      delete[] elem_;
    }

    T& at(size_t pos)
    {
      if (pos < size_)
        return elem_[pos];
      throw std::out_of_range("Index out of range");
    }

    T& operator[](size_t pos) noexcept
    {
      return elem_[pos];
    }
    
    // Iterators
    iterator begin();
    iterator end();

    // Capacity
    bool empty() const noexcept {
      return size_ == 0;
    }

    size_t size() const noexcept {
      return size_;
    }
    
    size_t capacity() const noexcept {
      return capacity_;
    }

    size_t max_size() const noexcept
    {
      return std::numeric_limits<size_t>::max();
    }
    
    void reserve(size_t new_capacity) {
      if (new_capacity > max_size())
       throw std::length_error("Requested size larger than std::numeric_limits<size_t>");
      if (new_capacity >= capacity_)
      {
        T *new_elem = new T[new_capacity];
        std::copy(elem_, elem_+size_, new_elem);
        delete[] elem_;
        elem_ = new_elem;
        capacity_ = new_capacity;
      }
    }

    // Modifiers 
    void push_back(T& elem) {
      if (size_ == capacity_)
        reserve(2*capacity_);
      elem_[size_++] = elem;
    }

    T& pop_back() {
      if (size_ == 0) return nullptr;
      return elem_[size_--];
    }

};
} // tgl::

template<class T>
std::ostream& operator<<(std::ostream& os, const tgl::vector<T>& vec) {
  return os;
}

#endif // VECTOR_HPP
