#ifndef widget_hpp
#define widget_hpp
#include <string>

class Widget {
    public:
    virtual void Init() = 0;
    virtual void Render() = 0;

    void setName(std::string name) {this->name = name;}
    std::string& getName() {return name;}

    void setId(int id) {this->id = id;}
    int& getId() {return id;}

    private:
    std::string name;
    int id;
};

#endif