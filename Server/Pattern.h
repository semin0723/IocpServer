#ifndef _PATTERN_
#define _PATTERN_

#define DeclSingleton(Name) \
private:\
Name(const Name&) = delete;\
Name& operator=(const Name&) = delete;\
public: \
static Name* _instance; \
static Name* GetInstance();\
static void DestroyInstance();

#define ImplSingleton(Name) \
Name* Name::_instance = nullptr;\
Name* Name::GetInstance() { \
	if(_instance == nullptr) { \
		_instance = new Name();\
	}\
	return _instance;\
}\
void Name::DestroyInstance() {\
	delete _instance;\
	_instance = nullptr;\
}

#endif