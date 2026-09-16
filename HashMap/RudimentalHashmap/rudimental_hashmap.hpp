#ifndef RUDIMENTALHASHMAP_HPP
#define RUDIMENTALHASHMAP_HPP

#include <algorithm>
#include <cmath>
#include <functional>
#include <utility>
#include <list>
#include <vector>

namespace tgl {

template<
  class Key, 
  class T, 
  class Hash=std::hash<Key>
> class hashmap {
  public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using hash_function = Hash;
    using size_type = size_t;

    const float MAX_LOAD_FACTOR{ 0.7 };
    
    hashmap( size_type bucket_count = 16 )
      : elem_count_{ 0 }
      , bucket_count_{ bucket_count }
      , load_factor_{ update_load_factor() }
    { }

    ~hashmap();

    // Capacity
    bool empty() const noexcept { return elem_count_ == 0;  }
    size_type bucket_count() const noexcept { return bucket_count_; }
    size_type element_count() const noexcept { return element_count; }
    size_type max_size() const noexcept { }

    // Modifiers
    void clear() { }

    void insert( const value_type& elem ) {
      if ( load_factor_ > MAX_LOAD_FACTOR ) {
        bucket_list_.resize( 2 * bucket_list_.size() );
        bucket_count_ = bucket_list_.size();
      }

      size_type seed = hash_key( &elem.first );
      size_type index = seed % bucket_count_; 
      bucket_list_.at( index ).insert( elem );
      elem_count_++;

      update_load_factor();
    }

    void erase( const key_type& key ) {
      size_type seed = hash_key( &key );
      size_type index = seed % bucket_count_;
      auto& bucket = bucket_list_.at( index );
      
      for ( auto& elem : bucket ) {
        if ( elem.first == key ) {
          bucket.erase( elem );
          elem_count_--;
        }       
      }

      update_load_factor();
    }

    // Access
    mapped_type& at( const key_type& key ) { 
      size_type seed = hash_key( key );
      size_type index = seed % bucket_count_;
      auto& bucket = bucket_list_.at( index );
      
      for ( auto& elem : bucket ) {
        if ( elem.first == key ) {
          return elem;
        }
      }

      return;
    }

  private:
    size_type hash_key( const key_type &key ) {
      return hash_function( key );
    }

    void update_load_factor() {
      load_factor_ = float(elem_count_) / float(bucket_count_);
    }

    size_type elem_count_;
    size_type bucket_count_;
    float load_factor_;

    std::vector<std::list<value_type>> bucket_list_;
}; // hashmap

} // ::tgl

#endif // RUDIMENTALHASHMAP_HPP
