#ifndef NAVIGATOR_SRC_LIB_S21_QUEUE_H_
#define NAVIGATOR_SRC_LIB_S21_QUEUE_H_

#include <initializer_list>
#include <list>
#include <utility>

namespace s21 {
template <class T, class Container = std::list<T>> class Queue {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue() : cont_(Container()) {}
  explicit Queue(std::initializer_list<value_type> const &items)
      : cont_(Container(items)) {}
  Queue(const Queue &src) : cont_(src.cont_) {}
  Queue(Queue &&src) { cont_ = std::move(src.cont_); }
  auto operator=(Queue &&src) {
    cont_ = std::move(src.cont_);
    return *this;
  }
  Queue &operator=(const Queue &src) {
    if (this != &src) {
      cont_ = src.cont_;
    }
    return *this;
  }
  ~Queue() { cont_.clear(); }

  const_reference back() const { return cont_.back(); }
  const_reference front() const { return cont_.front(); }
  bool empty() const { return cont_.empty(); }
  size_type size() const { return cont_.size(); }
  
  void push(const_reference value) { cont_.push_back(value); }
  void pop() { cont_.pop_front(); }
  void swap(Queue &other) { cont_.swap(other.cont_); }

  template <class... Args> void emplace_back(Args &&...args) {
    cont_.emplace_back(args...);
  }

private:
  Container cont_;
};

} // namespace s21

#endif // NAVIGATOR_SRC_LIB_S21_QUEUE_H_
