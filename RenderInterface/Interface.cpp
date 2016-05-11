#include "Interface.h"

#include "OpenGL.h"

_CInterface* _CInterface::m_pSingleton = 0x00;

_CInterface* _CInterface::GetSingleton(){
	if(m_pSingleton == 0x00){
		m_pSingleton = new _CInterface;
	}
	return m_pSingleton;
}

void _CInterface::Destroy(){
	if(m_pSingleton != 0x00){
		delete m_pSingleton;
		m_pSingleton = 0x00;
	}
}

void _CInterface::SetType(RENDER_TYPE::RENDER_TYPE type){
	if(GetSingleton()->GetType() == type){return;}
	Destroy();
	switch(type){
	case RENDER_TYPE::NONE:
		m_pSingleton = 0x00;
		break;
	case RENDER_TYPE::OpenGL:
		m_pSingleton = new _COpenGLRenderer;
		break;
	default:
		m_pSingleton = 0x00;
		break;
	}
}

RENDER_TYPE::RENDER_TYPE _CInterface::GetType(){
	return RENDER_TYPE::NONE;
}