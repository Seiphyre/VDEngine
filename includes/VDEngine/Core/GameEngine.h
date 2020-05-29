#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Singleton.h"

namespace VDEngine
{

class GameEngine : public Singleton<GameEngine>
{
    friend class Singleton<GameEngine>;

  public:
    bool Init();

    // void SetWindowSize();
    // void SetWindowTitle();

  private:
    GameEngine();
};

extern const GameEngine * g_GameEngine;

} // namespace VDEngine

#endif /* GAME_ENGINE_H_ */