#ifndef TIME_H_
#define TIME_H_

#include <GLFW/glfw3.h>

namespace VDEngine
{

class Time
{
  public:
    static void Update();

    static double GetTime();
    static double GetDeltaTime();

  private:
    Time();
    ~Time();

    static double m_last_updated_time;
    static double m_delta_time;
};

} // namespace VDEngine

#endif /* TIME_H_ */