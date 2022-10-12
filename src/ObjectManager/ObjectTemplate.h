#ifndef OBJECT_TEMPLATE_H
#define OBJECT_TEMPLATE_H

#include <string>
#include <vector>

class Instance;
class TextureObject;
struct ObjectProperty;

class ObjectTemplate {
    public:
    ObjectTemplate(std::string name);
    ~ObjectTemplate();

    ObjectProperty* GetProperty(int index);
    int GetPropertyIndex(std::string name);
    int GetPropertyIndex(ObjectProperty* propertyptr);

    int AddProperty(ObjectProperty* newproperty);

    int RenameProperty(std::string oldname, std::string newname);

    void SetPropertyValue(std::string name, int value);
    void SetPropertyValue(std::string name, std::string value);

    void RemoveProperty(std::string name);

    void AddChildren(Instance* inst);
    void RemoveChildren(Instance* inst);

    void Save(FILE* fileptr);

    std::string m_name;

    //Properties have unique names.
    std::vector<ObjectProperty*> m_properties;
    int m_propertycount;

    //Contain all the instances created from the object
    std::vector<Instance*> m_children;
    int m_childrencount;

    //make it so an object have a texture.
    bool m_havetexture;
    TextureObject* m_textureobj;
};

#endif