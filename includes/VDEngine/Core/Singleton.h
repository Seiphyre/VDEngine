#ifndef VDENGINE_SINGLETON_H_
#define VDENGINE_SINGLETON_H_

namespace VDEngine
{

template <typename T> class Singleton
{
  protected:
    static T * m_instance;

    Singleton()
    {
    }

  public:
    static T * getInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new T();
        }

        return m_instance;
    }
};

template <typename T> T * Singleton<T>::m_instance = nullptr;

} // namespace VDEngine

#endif /* VDENGINE_SINGLETON_H_ */