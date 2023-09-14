#include "view/console_view.h"

int main() {
  s21::Controller controller;
  s21::ConsoleView view(&controller);
  view.StartEventLoop();
  return 1;
}
