#ifndef RUDIMENTALHASHMAP_HPP
#define RUDIMENTALHASHMAP_HPP

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
    
    hashmap(size_type bucket_count);
    ~hashmap();

    // Capacity
    bool empty() const noexcept { }
    size_type bucket_count() const noexcept { return bucket_count_; }
    size_type element_count() const noexcept { return element_count; }
    size_type max_size() const noexcept { }

    // Modifiers
    void clear() { }
    void insert(const value_type& elem) { }
    void erase(const key_type& key) { }

    // Access
    mapped_type& at(const key_type& key) { }
    size_type count(const key_type& key) { }

  private:
    size_type elem_count_;
    size_type bucket_count_;

    std::vector<std::pair<key_type, std::list<value_type>>> bucket_list_;
}; // hashmap

} // ::tgl

#endif // RUDIMENTALHASHMAP_HPP
