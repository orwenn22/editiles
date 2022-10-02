#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>

class ObjectTemplate;

union InstancePropertyValue {
    int as_int;
    char as_str[255];
};

class Instance {
    public:
    Instance(ObjectTemplate* objtemplate, int x, int y);

    void Update(int levelx, int levely, int zoom);
    void CheckMouseInput();
    void Draw();

    void MoveTo(int x, int y);

    ObjectTemplate* m_objtemplateptr;

    std::vector<InstancePropertyValue> m_properties;


    int m_x;
    int m_y;
    int m_width;
    int m_height;

    bool m_drawonscreen;
};

#endif