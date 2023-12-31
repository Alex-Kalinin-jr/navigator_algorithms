#include "controller/controller.h"
#include "lib/s21_graph.h"
#include "lib/s21_graph_algorithms.h"
#include "view/console_view.h"

int main() {
  s21::Controller controller;
  s21::ConsoleView view(&controller);
  controller.SetView(&view);
  view.StartEventLoop();
  return 1;
}
