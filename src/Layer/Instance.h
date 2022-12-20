#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <vector>
#include <stdio.h>

class InstanceLayer;
class ObjectTemplate;

struct ObjectProperty;

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

    //Called when the Instance is saved to a file.
    void Save(FILE* fileptr);

    //Move the Instance to the positions x and y.
    void MoveTo(int x, int y);

    //Get the index of a property from the ObjectTemplate of the instance with a name.
    int GetPropertyIndex(std::string propertyname);
    //Get a ptr to a property of the ObjectTemplate with the index (returns null if the index is invalid).
    ObjectProperty* GetProperty(int index);

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