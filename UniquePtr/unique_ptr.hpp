#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <utility>

namespace tgl 
{

template<class T>
class unique_ptr 
{
  using value_type  = T;
  using pointer     = T*;

  public:
    constexpr unique_ptr() noexcept
      : internal_ptr_{ nullptr }
    { }

    constexpr unique_ptr( pointer ptr ) noexcept
      : internal_ptr_{ ptr }
    { }
   
    // Copy/Move semantics

    constexpr unique_ptr( const unique_ptr& ) = delete;
    constexpr unique_ptr& operator=( const unique_ptr& ) = delete;

    constexpr unique_ptr( unique_ptr&& u_ptr ) noexcept { 
      internal_ptr_ = u_ptr.release(); 
    }

    constexpr unique_ptr& operator=( unique_ptr&& u_ptr ) {
      internal_ptr_ = u_ptr.release();
    }

    ~unique_ptr() {
      if (get() == nullptr)
        return;
      delete get();
      internal_ptr_ = nullptr;
    }

    // Modifiers
  
    pointer release() noexcept {
      pointer old_ptr = get();
      if (internal_ptr_)
        internal_ptr_ = nullptr;
      return old_ptr;
    }

    void reset( pointer ptr = pointer() ) noexcept {
      pointer old_ptr = get();
      internal_ptr_ = ptr;
      if (old_ptr)
        delete old_ptr;
    }

    void swap( unique_ptr& u_ptr ) noexcept {
      std::swap(internal_ptr_, u_ptr.internal_ptr_);
    }

    // Observers

    pointer get() noexcept {
      return internal_ptr_;
    }

    operator bool() const noexcept {
      return ( get() != nullptr );
    }
    
    // Access

    value_type operator*() noexcept {
      return *get();
    }

    pointer operator->() const noexcept {
      return get();
    }

  private:
    value_type* internal_ptr_;

}; // unique_ptr

template<class T> 
unique_ptr<T> make_unique( T&& arg ) {
  return unique_ptr<T>(new T(arg));
}

}  // ::tgl
#endif // UNIQUE_PTR_HPP

