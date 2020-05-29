#include "VDEngine/Core/Time.h"

double VDEngine::Time::m_last_updated_time = 0;
double VDEngine::Time::m_delta_time        = 0;

VDEngine::Time::Time()
{
    m_last_updated_time = glfwGetTime();
}

VDEngine::Time::~Time()
{
}

void VDEngine::Time::Update()
{
    m_delta_time        = VDEngine::Time::GetTime() - m_last_updated_time;
    m_last_updated_time = glfwGetTime();
}

double VDEngine::Time::GetTime()
{
    return (glfwGetTime());
}

double VDEngine::Time::GetDeltaTime()
{
    return (m_delta_time);
}