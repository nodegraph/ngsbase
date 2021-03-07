#pragma once
#include <base/game/game_export.h>
#include <SDL.h>


namespace ngs {

class GAMEEXPORT_EXPORT Game {
 public:
  Game(int width, int height);
  virtual ~Game();

  // Game Loop.
  virtual void run();
  virtual void swap_buffers();

 protected:
  // Quit run loop.
  bool _quit;

 private:
  // Initialization and Deinitialization.
  virtual bool init();
  virtual void deinit();

  // Handle Key Input.
  virtual void handleKeys( unsigned char key, int x, int y ) {}

  // Per Frame Update.
  virtual void update() {}

  // Render.
  virtual void render() {}

  // Window dimensions.
  const int _width;
  const int _height;

  // SDL Objects.
  SDL_Window* _window;
  SDL_GLContext _context;
};

class GAMEEXPORT_EXPORT UnitTestGame: public Game {
 public:
  static UnitTestGame* get_instance() {
    if (!_singleton) {
      _singleton = new UnitTestGame();
    }
    return _singleton;
  }
  ~UnitTestGame() {}
  void (*test)();
  virtual void render() { test(); _quit = true;}
 private:
  static UnitTestGame* _singleton;
  UnitTestGame(): Game(512, 512), test(NULL) {}
};

}
