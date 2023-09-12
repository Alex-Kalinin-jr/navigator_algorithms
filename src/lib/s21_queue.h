#ifndef SRC_LIB_S21_QUEUE_H_
#define SRC_LIB_S21_QUEUE_H_

#include <initializer_list>
#include <list>
#include <utility>

namespace s21 {
template <class T, class Container = std::list<T>>
class Queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Queue() : cont_(Container()) {}
  explicit Queue(std::initializer_list<value_type> const& items)
      : cont_(Container(items)) {}
  Queue(const Queue& src) : cont_(src.cont_) {}
  Queue(Queue&& src) { MoveHelper(src); }
  ~Queue() { cont_.clear(); }
  auto operator=(Queue&& q) {
    MoveHelper(q);
    return *this;
  }

  const_reference front() { return cont_.front(); }
  const_reference back() { return cont_.back(); }
  bool empty() { return cont_.empty(); }
  size_type size() { return cont_.size(); }
  void push(const_reference value) { cont_.push_back(value); }
  void pop() { cont_.pop_front(); }
  void swap(Queue& other) { cont_.swap(other.cont_); }

  template <class... Args>
  void emplace_back(Args&&... args) {
    cont_.emplace_back(args...);
  }

 private:
  Container cont_;

  void MoveHelper(Queue& src) {
    if (&cont_ != &(src.cont_)) {
      cont_ = src.cont_;
      src.cont_.clear();
    }
  }
};

}  // namespace s21

#endif  // SRC_LIB_S21_QUEUE_H_
