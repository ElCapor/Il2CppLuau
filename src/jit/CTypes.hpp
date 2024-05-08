#ifndef CTypes_HPP
#define CTypes_HPP

// Base class for all types
class CType {
public:
    virtual std::string getName() const = 0;
    virtual int getAsmJitTypeId() const = 0;
    virtual const CType* getCType() const = 0;
};

// Derived class for int type
class IntCType : public CType {
public:
    std::string getName() const override { return "int"; }
    int getAsmJitTypeId() const override { return 0; } // Dummy implementation
    const CType* getCType() const override { return this; }
};

// Derived class for void type
class VoidCType : public CType {
public:
    std::string getName() const override { return "void"; }
    int getAsmJitTypeId() const override { return 0; } // Dummy implementation
    const CType* getCType() const override { return this; }
};

// Derived class for string type
class StringCType : public CType {
public:
    std::string getName() const override { return "string"; }
    int getAsmJitTypeId() const override { return 0; } // Dummy implementation
    const CType* getCType() const override { return this; }
};


#endif