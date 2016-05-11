#pragma once

#define PHOENIX_SINGLETON(Class)	\
private:							\
static Class* m_pSingleton;			\
Class();							\
~Class();							\
public:								\
static Class* GetSingleton(){		\
	if(m_pSingleton == 0x00){		\
		m_pSingleton = new Class;	\
	}								\
	return m_pSingleton;			\
}									\
static void Destroy(){				\
	if(m_pSingleton != 0x00){		\
		delete m_pSingleton;		\
		m_pSingleton = 0x00;		\
	}								\
}