#ifndef widget_hpp
#define widget_hpp


class Widget {
    public:
    virtual void Init() = 0;
    virtual void Render() = 0;
};

#endif