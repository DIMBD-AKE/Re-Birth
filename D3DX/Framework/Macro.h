#pragma once

#define SINGLETONE(class_name) \
private: \
	class_name(); \
	~class_name(); \
public: \
	static class_name* GetInstance() \
	{ \
		static class_name instance; \
		return &instance; \
	}
	
#define SYNTHESIZE(varType, varName, funcName)\
protected: varType varName;\
public: varType Get##funcName(void) { return varName; }\
public: void Set##funcName(varType var) { varName = var; }

#define SYNTHESIZE_REF(varType, varName, funName)\
protected: varType varName;\
public: varType& Get##funName(void) { return varName; }\
public: void Set##funName(varType& var) { varName = var; }

#define SYNTHESIZE_PT(varType, varName, funName)\
protected: varType varName;\
public: varType* Get##funName(void) { return &varName; }\
public: void Set##funName(varType var) { varName = var; }

#define GET(varType, varName, funcName)\
protected: varType varName;\
public: varType Get##funcName(void) { return varName; }

#define SET(varType, varName, funcName)\
protected: varType varName;\
public: void Set##funcName(varType var) { varName = var; }

#define SAFE_DELETE(p) { if(p) delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) { if(p) delete[] p; p = nullptr; }
#define SAFE_RELEASE(p) { if(p) p->Release(); p = nullptr; }