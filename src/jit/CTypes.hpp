#ifndef CTypes_HPP
#define CTypes_HPP
#include <string>
#include <cstdint>

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
    CType_Void,
    CType_Int,
    CType_MAX
};

int CType2AsmTypeId(CType type);

// abstract CContainer exposed to lua
class CContainer 
{
public:
    SETTYPE(None); // type of the container
    virtual std::string GetName() const = 0;
};

class VoidContainer : public CContainer
{
public:
    SETTYPE(Void);
    SETNAME(void);
    void* self; // value
    void* GetValue() {return self;}
    void SetValue(void* value) {self = value;}
};

}
#endif