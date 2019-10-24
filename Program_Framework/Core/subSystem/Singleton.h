#pragma once

template<class T>
class Singleton
{
protected:
	Singleton(void) {};
	virtual ~Singleton(void) {};

public:
	static T* GetInstance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T;
		return m_pInstance;
	};

	static void DestroyInstance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	};

private:
	static T* m_pInstance;
};

template <typename T>
T* Singleton<T>::m_pInstance = nullptr;