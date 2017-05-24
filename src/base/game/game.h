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

}
