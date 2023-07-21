
#pragma once

#include <array>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

namespace gecko {

// https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp

template<typename T, const uint16_t MAX_VECTOR_SIZE=64>
class vector {
  public:
  vector() { clear(); }
  ~vector() {}
  vector(vector&& other) = delete; // moveable
  vector& operator=(vector&& other) = delete; // moveable
  vector(const vector&) = delete; // copyable
  vector& operator=(const vector&) = delete; // copyable

  // struct Iterator {
  //   using iterator_category = std::forward_iterator_tag;
  //   using difference_type = std::ptrdiff_t; // ??
  //   using value_type = T;
  //   using pointer = T*;
  //   using reference = T&;

  //   Iterator(pointer ptr): m_ptr(ptr) {}

  //   reference operator*() const { return *m_ptr; }
  //   pointer operator->() { return m_ptr; }

  //   // Prefix increment
  //   Iterator& operator++() { m_ptr++; return *this; }

  //   // Postfix increment
  //   Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

  //   friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
  //   friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

  //   private:
  //   pointer m_ptr;
  // };

  inline void push_back(T value) { buffer[bsize++] = value; }

  T back() { return buffer[bsize]; }

  void clear() {
    bsize = 0;
    memset(buffer.data(), 0 , MAX_VECTOR_SIZE);
  }

  const T& operator[](const size_t i) const {
    if (i >= bsize) i = bsize - 1;
    return buffer[i];
  }

  T& operator[](const size_t i) {
    if (i >= bsize && bsize == MAX_VECTOR_SIZE) return buffer[bsize - 1];
    else if ( i < bsize && bsize == MAX_VECTOR_SIZE) return buffer[i];
    bsize += 1;
    return buffer[i];
  }

  uint16_t max_size() { return MAX_VECTOR_SIZE; }
  uint16_t size() { return bsize; }
  uint16_t len() { return bsize; }

  // T* begin() { return buffer.data(); }
  // T* end() { return &buffer[bsize]; }
  // Iterator begin() { return Iterator(&buffer[0]); }
  // Iterator end() { return Iterator(&buffer[bsize]); }

  typedef typename std::array<T,MAX_VECTOR_SIZE>::iterator it;
  it begin() { return buffer.begin(); }
  it end() { return buffer.end(); }
  T* data() { return buffer.data(); } // FIXME: this goes beyond bsize

  protected:
  // T buffer[MAX_VECTOR_SIZE];
  std::array<T,MAX_VECTOR_SIZE> buffer;
  uint16_t bsize;
};

// template<typename T, uint16_t MAX_VECTOR_SIZE=64> using deque = vector<T,MAX_VECTOR_SIZE>;
// template<typename T, uint16_t MAX_VECTOR_SIZE=64> using array = vector<T,MAX_VECTOR_SIZE>;

} // end namespace gecko