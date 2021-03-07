#include <base/glewhelper/glewhelper.h>
#include <base/game/game.h>

#include <iostream>
#include <string>


class TestGame: public ngs::Game {
 public:
  TestGame(): Game(680, 480) {}
  ~TestGame() {}
};


int main(int argc, char* args[]) {
  TestGame g;
  g.run();
  return 0;
}
