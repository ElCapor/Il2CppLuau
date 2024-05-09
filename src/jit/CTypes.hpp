#ifndef CTypes_HPP
#define CTypes_HPP
#include <string>
#include <cstdint>
#include <polyhook/asmjit/src/asmjit/asmjit.h>

#define SETTYPE(tp) CType m_CType = CType::CType_##tp
#define SETNAME(name) std::string GetName() const override \
{ \
return #name;\
} \

/*
* Code
*/
namespace jit
{
// Base class for all types
enum class CType
{
    CType_None,
    CType_Void, // no value
    CType_VoidPtr, // void* ptr
    CType_Int, //int
    CType_Bool, // bool
    CType_MAX
};

asmjit::TypeId CType2AsmTypeId(CType type);

// abstract CContainer exposed to lua
class CContainer 
{
public:
    SETTYPE(None); // type of the container
    virtual std::string GetName() const = 0;
};

class VoidPtrContainer : public CContainer
{
public:
    SETTYPE(VoidPtr);
    SETNAME(voidptr);
    void* self; // value
    void* GetValue() {return self;}
    void SetValue(void* value) {self = value;}
};

}
#endif