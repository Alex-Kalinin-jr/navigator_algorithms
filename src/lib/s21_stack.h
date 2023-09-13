#ifndef SRC_LIB_S21_STACK_H_
#define SRC_LIB_S21_STACK_H_

#include <initializer_list>
#include <list>
#include <utility>

namespace s21 {

template <class T, class Container = std::list<T>> class Stack {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack() : cont_(Container()) {}
  explicit Stack(std::initializer_list<value_type> const &items)
      : cont_(Container(items)) {}

  Stack(const Stack &src) : cont_(src.cont_) {}
  Stack(Stack &&src) { cont_ = std::move(src.cont_); }
  Stack &operator=(Stack &&src) {
    cont_ = std::move(src.cont_);
    return *this;
  }
  Stack &operator=(const Stack &src) {
    if (this != &src) {
      cont_ = src.cont_;
    }
    return *this;
  }
  ~Stack() {}

  const_reference top() const { return cont_.back(); }
  bool empty() const { return cont_.empty(); }
  size_type size() const { return cont_.size(); }
  void push(const_reference value) { cont_.push_back(value); }
  void pop() { cont_.pop_back(); }
  void swap(Stack &other) { cont_.swap(other.cont_); }

  // is not tested
  template <class... Args> void emplace_front(Args &&...args) {
    cont_.emplace_back(args...);
  }

private:
  Container cont_;
};

} // namespace s21

#endif // SRC_LIB_S21_STACK_H_
