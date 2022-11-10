#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <stdio.h>

class InstanceLayer;
class ObjectTemplate;

union InstancePropertyValue {
    int as_int;
    char as_str[255];
};

class Instance {
    public:
    Instance(ObjectTemplate* objtemplate, int x, int y);
    ~Instance();

    void Update(int levelx, int levely, int zoom);
    void CheckMouseInput();
    void Draw();

    void Save(FILE* fileptr);

    void MoveTo(int x, int y);

    ObjectTemplate* m_objtemplateptr;

    std::vector<InstancePropertyValue> m_properties;

    InstanceLayer* m_parrent;
    bool m_isinlayer;

    int m_x;
    int m_y;
    int m_width;
    int m_height;

    bool m_drawonscreen;
};

#endif