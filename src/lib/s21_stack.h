#ifndef SRC_LIB_S21_STACK_H_
#define SRC_LIB_S21_STACK_H_

#include <initializer_list>
#include <list>
#include <utility>

namespace s21 {

template <class T, class Container = std::list<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Stack() : cont_(Container()) {}
  explicit Stack(std::initializer_list<value_type> const& items)
      : cont_(Container(items)) {}
  Stack(const Stack& src) : cont_(src.cont_) {}
  Stack(Stack&& src) { MoveHelper(src); }
  ~Stack() { cont_.clear(); }
  auto operator=(Stack&& s) {
    MoveHelper(s);
    return *this;
  }

  const_reference top() { return cont_.back(); }
  bool empty() { return cont_.empty(); }
  size_type size() { return cont_.size(); }
  void push(const_reference value) { cont_.push_back(value); }
  void pop() { cont_.pop_back(); }
  void swap(Stack& other) { cont_.swap(other.cont_); }

  template <class... Args>
  void emplace_front(Args&&... args) {
    cont_.emplace_back(args...);
  }

 private:
  Container cont_;

  void MoveHelper(Stack& src) {
    if (&cont_ != &(src.cont_)) {
      cont_ = src.cont_;
      src.cont_.clear();
    }
  }
};
}  // namespace s21

#endif  // SRC_LIB_S21_STACK_H_
