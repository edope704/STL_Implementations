#ifndef VECTOR_HPP
#define VECTOR_HPP 

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <limits>
#include <stdexcept>
#include <algorithm>

namespace tgl {

/**
 * @brief A dynamic array implementation.
 * 
 * @tparam T The type of elements stored in the vector.
 */
template <class T>
class vector 
{
  public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = std::ptrdiff_t;
    using pointer         = T*;
    using reference       = T&;
    using const_reference = const T&;
    
    using iterator        = pointer;
    using const_iterator  = const pointer;

    /**
     * @brief Initializes an empty vector.
     */
    vector() 
      : size_{ 0 }
      , capacity_{ 0 }
      , elem_{ new T[capacity_] } 
      { }

    /**
     * @brief Initializes a vecor with specified initial capacity.
     * @param capacity the initial capacity of the vector.
     */
    vector(size_type capacity)
      : size_{ 0 }
      , capacity_{ capacity }
      , elem_{ new T[capacity_] }
      { } 

    /**
     * @brief Allows initialization using initializer_list.
     * @param init The initializer list used to populate the vector.
     */
    vector(std::initializer_list<T> init)
      : size_{ init.size() }
      , capacity_{ size_ }
      , elem_{ new T[capacity_] } 
    { 
      std::copy(init.begin(), init.end(), elem_); 
    }

    /**
     * @brief Copy constructor.
     * @param vec The vector to copy from.
     */
    vector(const vector& vec) 
      : size_{ vec.size_ }
      , capacity_{ vec.capacity_ }
      , elem_{ new T[capacity_] }
    {
      std::copy(vec.elem_, vec.elem_+vec.size_, this->elem_);
    }

    /**
     * @brief Move constructor.
     * @param vec The vector to move from.
     */
    vector(vector&& vec) 
      : size_{ vec.size_ }
      , capacity_{ vec.capacity_ }
      , elem_{ new T[capacity_]}
    {
      std::copy(vec.elem_, vec.elem_+vec.size_, this->elem_);
      vec.elem_ = nullptr;
    }

    /**
     * @brief Copy assignment operator.
     * @param vec The vector to copy from.
     * @return A reference to the current vector.
     */
    vector& operator=(const vector& vec) {
      if (this == &vec) 
        return *this; // self-assignment check

      T *new_elem = new T[vec.size_];
      std::copy(vec.elem_, vec.elem_+vec.size_, new_elem);
      
      delete[] this->elem_;
      this->size_ = vec.size_;
      this->capacity_ = vec.capacity_;
      this->elem_ = new_elem;
      return *this;
    }
    
    /**
     * @brief Move assignment operator.
     * @param vec The vector to move from.
     * @return A reference to the current vector.
     */
    vector& operator=(vector&& vec) { 
      if (this == &vec) 
        return *this; // self-assignment check
      
      delete[] this->elem_;
      this->size_ = std::exchange(vec.size_, 0);
      this->capacity_ = std::exchange(vec.capacity_, 0);
      this->elem_ = std::exchange(vec.elem_, nullptr);
      return *this;
    }

    ~vector() {
      delete[] elem_;
    }

    /**
     * @brief Accesses the specified element with bounds checking.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     * @throws std::out_of_range if pos is not within the range of the container.
     */
    reference at(size_type pos) {
      if (pos < size_)
        return elem_[pos];
      throw std::out_of_range("Index out of range");
    }

    /**
     * @brief Accesses the specified element without bounds checking.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    reference operator[](size_type pos) noexcept {
      return elem_[pos];
    }
    
    // Iterators

    /**
     * @brief Returns an iterator to the beginning of the vector.
     */
    iterator begin() noexcept {
      return iterator(elem_);
    }

    /**
     * @brief Returns an iterator to the end of the vector.
     */
    iterator end() noexcept {
      return iterator(elem_ + size_);
    }

    // Capacity

    bool is_empty() const noexcept {
      return size_ == 0;
    }

    size_type size() const noexcept {
      return size_;
    }
    
    size_type capacity() const noexcept {
      return capacity_;
    }

    size_type max_size() const noexcept {
      return std::numeric_limits<size_type>::max();
    }

    bool is_full() const noexcept {
      return size_ == capacity_;
    }
    
    /**
     * @brief Requests that the vector capacity be at least enough to contain new_capacity elements.
     * @param new_capacity New capacity of the vector.
     * @throws std::length_error if new_capacity exceeds max_size().
     */
    void reserve(size_type new_capacity) {
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

    /**
     * @brief Adds an element to the end of the vector.
     * Calls reserve() if current size() == capacity()
     * @param elem The element to be appended.
     */
    void push_back(const_reference elem) {
      if (is_full())
        reserve(capacity_ == 0 ? 1 : 2*capacity_);
      elem_[size_++] = elem;
    }

    /**
     * @brief Removes the last element of the vector and returns it.
     * @throws std::out_of_range if the vector is empty.
     */
    void pop_back() {
      if (size_ == 0) throw std::out_of_range("Vector is empty");
      --size_;
    }
    
    /**
     * @brief Inserts elem at position pos
     * @param pos The position to insert elem
     * @param elem The element to be inserted
     */
    void insert(iterator pos, value_type elem) {
      if (pos == end())
        push_back(elem);
      else {
        // Saving the offset is necessary in case of reserve() as it 
        // invalidates pos
        auto offset = pos - begin();
        if (is_full()) {
          reserve(capacity_ == 0 ? 1 : 2*capacity_);
          // Recalculate pos with new base pointer
          pos = begin() + offset;
        }
        size_++;
        std::move_backward(pos, end()-1, end());
        *pos = elem;
      }
    }
    
    /**
     * @brief Erases an element from the vector
     * @param pos the position of the element to be removed
     * @return iterator end()
     */
    iterator erase(iterator pos) {
      std::move(pos+1, end(), pos);
      size_--;
      return end();
    }

  private:
    size_type size_;
    size_type capacity_;
    T* elem_;
    
}; // vector
}  // tgl

#endif // VECTOR_HPP
