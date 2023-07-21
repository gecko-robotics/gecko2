/**************************************************\
* The MIT License (MIT)
* Copyright (c) 2014 Kevin Walchko
* see LICENSE for full details
\**************************************************/
#pragma once

#include <array>

template<typename T, const size_t BB_SIZE>
class Blackbox {
 public:
  Blackbox() : head_(0), tail_(0), size_(0) {}

  // Add a message to the ring buffer.
  void push_back(const T &message) {
    // If the ring buffer is full, wrap the head around.
    if (size_ == BB_SIZE) head_ = increment(head_);
    else size_++;
    if (size_ > 1) tail_ = increment(tail_);
    data_[tail_] = message;
    // if (size_ > 1) tail_ = increment(tail_);
  }

  T& operator[](const size_t i) { return data_[(head_ + i) % BB_SIZE]; }
  T& front() { return data_[head_]; }
  T& back() { return data_[tail_]; }

  // I don't think this works, because it can wrap
  // const T* begin() { return &data_[0]; }
  // const T* end() { return &data_[size_]; }
  // T* data() { return &data_[0]; } // value?
  T* data() { return data_.data(); } // value?

  const size_t head() const { return head_; }
  const size_t tail() const { return tail_; }

  // const T& get(const size_t i) {
  //   const size_t j = (head_ + i) % BB_SIZE;
  //   return data_[j];
  // }

  // Get the number of messages in the ring buffer.
  inline const size_t size() const { return size_; }
  inline const size_t len() const { return size(); }
  inline const size_t max_size() { return BB_SIZE; }
  inline const size_t capacity() { return BB_SIZE; }
  bool full() const { return size_ == BB_SIZE ? true : false; }
  bool empty() const { return size_ == 0 ? true : false; }

 protected:
  size_t size_;
  size_t head_;
  size_t tail_;
  std::array<T, BB_SIZE> data_;

  inline size_t increment(const size_t s) { return (s + 1) % BB_SIZE; }
};

// #include <vector>

// #if defined(__APPLE__) || defined(linux)
// typedef std::string string;
// #else
// typedef String string;
// #endif

// class Blackbox {
// public:
//   Blackbox() {}

//   bool init() { return true; }

//   void buffer_msg(string s) { buffer.push_back(s); }

//   void send_msgs(Stream *s) {
//     // for (auto msg: buffer) {
//     //   s->write(msg);
//     // }
//   }

//   std::vector<string> buffer;
//   // vector<string> sent;
// };