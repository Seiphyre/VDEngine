

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

#ifndef VDENGINE_TIME_H_
#define VDENGINE_TIME_H_

// External libs
#include <GLFW/glfw3.h>

namespace VDEngine
{

class Time
{
    friend auto meta::registerMembers<VDEngine::Time>();
    
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

#endif /* VDENGINE_TIME_H_ */

#ifndef META_REGISTER_VDENGINE_TIME
#define META_REGISTER_VDENGINE_TIME

template <>
inline auto meta::registerMembers< VDEngine::Time >() 
{
    return meta::members( 
 
    );
}

#endif /* META_REGISTER_VDENGINE_TIME */

