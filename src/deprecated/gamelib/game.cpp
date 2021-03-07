#include <base/game/game.h>
#include <base/glewhelper/glewhelper.h>

#include <gl\glew.h>
//#include <SDL_opengl.h>
#include <gl\glu.h>

#include <iostream>
#include <cassert>

namespace ngs {

UnitTestGame* UnitTestGame::_singleton = NULL;

Game::Game(int width, int height)
    : _width(width),
      _height(height),
      _window(NULL),
      _context(NULL),
      _quit(false) {
  assert(init());
}

Game::~Game() {
  deinit();
}

void Game::swap_buffers() {
  // Swap buffers.
  SDL_GL_SwapWindow(_window);
}

void Game::deinit() {
  // Finish using glew.
  finish_glew();

  // Destroy the window.
  SDL_DestroyWindow(_window);
  _window = NULL;

  // Quit SDL systems.
  SDL_Quit();
}

bool Game::init() {
  // Initialize SDL.
  if (SDL_Init( SDL_INIT_VIDEO) < 0) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << "\n";
    return false;
  }

  // Set the desired OpenGL version.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Create the window.
  _window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (_window == NULL) {
    std::cerr << "Unable to create SDL window: " << SDL_GetError() << "\n";
    return false;
  }

  // Create the OpenGL context.
  _context = SDL_GL_CreateContext(_window);
  if (_context == NULL) {
    std::cerr << "Unable to create OpenGL context: " << SDL_GetError() << "\n";
    return false;
  }

  // Start glew.
  start_glew();

  // Attempt to use VSync.
  if (SDL_GL_SetSwapInterval(1) < 0) {
    std::cerr << "Unable to setup VSync: " << SDL_GetError() << "\n";
  }

  return true;
}

void Game::run() {
  SDL_Event e;

  // Enable text input.
  SDL_StartTextInput();

  while (!_quit) {
    while (SDL_PollEvent(&e) != 0) {
      // User has quit game.
      if (e.type == SDL_QUIT) {
        _quit = true;
      }
      // Handle keypress and mouse input.
      else if (e.type == SDL_TEXTINPUT) {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        handleKeys(e.text.text[0], x, y);
      }
    }

    // Render.
    render();

    // Swap buffers.
    SDL_GL_SwapWindow(_window);
  }

  // Disable text input
  SDL_StopTextInput();
}

}
