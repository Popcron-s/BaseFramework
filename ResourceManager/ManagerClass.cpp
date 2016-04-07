#include "ManagerClass.h"
#include "Decoder.h"

_ResourceManager* _ResourceManager::m_pSingleton = 0x0;

_ResourceManager* _ResourceManager::GetSingleton(){
	if(m_pSingleton == 0x0){
		m_pSingleton = new _ResourceManager;
	}
	return m_pSingleton;
}
void _ResourceManager::Destroy(){
	if(m_pSingleton != 0x0){
		m_pSingleton->RemoveAll();
		delete m_pSingleton;
		m_pSingleton = 0x0;
	}
}

_ResourceManager::_ResourceManager(){
	m_Count = 0;
	m_Head = 0x00;
}
_ResourceManager::~_ResourceManager(){
	RemoveAll();
}

void _ResourceManager::TextNormalize(char* text){
	for(int i = 0 ; text[i] != 0x00 ; ++i){
		if('a' <= text[i] && text[i] <= 'z'){
			text[i] -= 32;
		}
	}
}

bool _ResourceManager::Insert(const char* text){
	TEXT nor_text = text;
	TextNormalize(nor_text);

	_BaseType* data = 0x00;

	if(!Decode(nor_text, &data)){return false;} 

	_Node** t_node = &m_Head;

	while((*t_node) != 0x00){
		if(nor_text < (*t_node)->name){t_node = &((*t_node)->LNode);}
		else if(nor_text > (*t_node)->name){t_node = &((*t_node)->RNode);}
		else{
			if(data != 0x00){
				delete data;
				data = 0x00;
			}
			return false;
		}
	}

	(*t_node) = new _Node;
	(*t_node)->name = (char*)nor_text;
	(*t_node)->data = data; 
	(*t_node)->LNode = 0x00;
	(*t_node)->RNode = 0x00;

	++m_Count;

	return true;
}

bool _ResourceManager::Remove(const char* text){
	TEXT nor_text = text;
	TextNormalize(nor_text);

	_Node** t_node = &m_Head;
	while((*t_node) != 0x00){
		if(nor_text < (*t_node)->name){t_node = &((*t_node)->LNode);}
		else if(nor_text > (*t_node)->name){t_node = &((*t_node)->RNode);}
		else{
			if(((*t_node)->LNode != 0x00) && ((*t_node)->RNode != 0x00)){
				_Node** t_node2 = t_node;
				t_node2 = &((*t_node2)->RNode);
				if((*t_node2)->LNode != 0x00){
					while((*t_node2)->LNode != 0x00 || (*t_node2)->RNode != 0x00){
						if((*t_node2)->LNode != 0x00){t_node2 = &((*t_node2)->LNode);}
						else{t_node2 = &((*t_node2)->RNode);}
					}
					(*t_node2)->RNode = (*t_node)->RNode;
				}
				(*t_node2)->LNode = (*t_node)->LNode;
				_Node* t_node3 = (*t_node2);
				(*t_node2) = 0x00;
				delete (*t_node);
				(*t_node) = t_node3;
			}
			else if((*t_node)->LNode != 0x00){
				_Node* t_node2 = (*t_node);
				(*t_node) = (*t_node)->LNode;
				delete t_node2;
				t_node2 = 0x00;
			}
			else if((*t_node)->RNode != 0x00){
				_Node* t_node2 = (*t_node);
				(*t_node) = (*t_node)->RNode;
				delete t_node2;
				t_node2 = 0x00;
			}
			else{
				delete (*t_node);
				(*t_node) = 0x00;
			}

			--m_Count;
			return true;
		}
	}

	return false;
}

bool _ResourceManager::RemoveAll(){
	while(m_Count > 0){
		Remove(m_Head->name);
	}
	return true;
}

bool _ResourceManager::GetData(const char* text, _BaseType** data){
	TEXT nor_text = text;
	TextNormalize(nor_text);

	_Node* t_node = m_Head;

	while(t_node != 0x00){
		if(nor_text < t_node->name){t_node = t_node->LNode;}
		else if(nor_text > t_node->name){t_node = t_node->RNode;}
		else{break;}
	}

	if(t_node == 0x00){return false;}

	(*data) = t_node->data;
	return true;
}

_BaseType* _ResourceManager::GetData(const char* text){
	_BaseType* data = 0x00;
	TEXT nor_text = text;
	TextNormalize(nor_text);

	_Node* t_node = m_Head;

	while(t_node != 0x00){
		if(nor_text < t_node->name){t_node = t_node->LNode;}
		else if(nor_text > t_node->name){t_node = t_node->RNode;}
		else{break;}
	}

	if(t_node == 0x00){return 0x00;}

	data = t_node->data;
	return data;
}

void _ResourceManager::Sort(){

}