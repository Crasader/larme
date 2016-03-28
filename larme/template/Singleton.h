#pragma once

// https://gist.github.com/DanDanBaker/2299755

namespace larme{
namespace templates{

template<typename T>
class Singleton
{
public:
    static T* getInstance();
    static void destroy();
    
private:
    
    Singleton(Singleton const&){};
    Singleton& operator=(Singleton const&){};
    
protected:
    static T* m_instance;
    
    Singleton(){ m_instance = static_cast <T*> (this); };
    ~Singleton(){  };
};

template<typename T> T* Singleton<T>::m_instance = nullptr;

template<typename T>
T* Singleton<T>::getInstance()
{
    if(!m_instance)
    {
        Singleton<T>::m_instance = new T();
    }
    
    return m_instance;
}

template<typename T>
void Singleton<T>::destroy()
{
    delete Singleton<T>::m_instance;
    Singleton<T>::m_instance = 0;
}

} // namespace templates
} // namespace larme