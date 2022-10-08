#ifndef OBJECT_TEMPLATE_H
#define OBJECT_TEMPLATE_H

#include <string>
#include <vector>

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

    void Save(FILE* fileptr);

    std::string m_name;

    //Properties have unique names.
    std::vector<ObjectProperty*> m_properties;
    int m_propertycount;

    //make it so an object have a texture.
    bool m_havetexture;
    TextureObject* m_textureobj;
};

#endif