#include "CTypes.hpp"

asmjit::TypeId jit::CType2AsmTypeId(CType type)
{
    switch (type)
    {
        case CType::CType_Void:
            return asmjit::TypeId(asmjit::TypeUtils::TypeIdOfT<void>::kTypeId);
        case CType::CType_VoidPtr:
            return asmjit::TypeId(asmjit::TypeUtils::TypeIdOfT<void*>::kTypeId);
        case CType::CType_Int:
            return asmjit::TypeId(asmjit::TypeUtils::TypeIdOfT<int>::kTypeId);
        case CType::CType_Bool:
            return asmjit::TypeId(asmjit::TypeUtils::TypeIdOfT<bool>::kTypeId);
    }
    return asmjit::TypeId::kVoid;
}