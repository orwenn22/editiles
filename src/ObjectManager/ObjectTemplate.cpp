#include "ObjectTemplate.h"

#include "ObjectProperty.h"

ObjectTemplate::ObjectTemplate(std::string name) {
    m_propertycount = 0;
    m_name = name;

    //add some basic and required properties
    ObjectProperty* xpos = new ObjectProperty("x");
    xpos->obligatory = true;
    xpos->havedefaultvalue = false;
    AddProperty(xpos);

    ObjectProperty* ypos = new ObjectProperty("y");
    ypos->obligatory = true;
    ypos->havedefaultvalue = false;
    AddProperty(ypos);

    ObjectProperty* width = new ObjectProperty("width");
    width->obligatory = true;
    width->havedefaultvalue = true;
    width->SetValue(8);
    AddProperty(width);

    ObjectProperty* height = new ObjectProperty("height");
    height->obligatory = true;
    height->havedefaultvalue = true;
    height->SetValue(8);
    AddProperty(height);
}

ObjectTemplate::~ObjectTemplate() {
    for(int i = 0; i < m_propertycount; i++) {
        delete m_properties[i];
    }
    m_properties.clear();
    m_propertycount = 0;
}

int ObjectTemplate::AddProperty(ObjectProperty* newproperty) {
    printf("ADDING PROP (name : %s)\n", newproperty->name.c_str());

    if(newproperty->name.empty()) {
        return 1;
    }

    for(int i = 0; i < m_propertycount; i++) {
        if(newproperty->name == m_properties[i]->name) {
            return 1;   //found a property that already have the name. return error
        }
    }
    m_properties.push_back(newproperty);
    m_propertycount++;
    //printf("SUCCESS\n");
    return 0;
}

ObjectProperty* ObjectTemplate::GetProperty(int index) {
    if(index >= 0 && index < m_propertycount) {
        return m_properties[index];
    }
    return NULL;
}

int ObjectTemplate::RenameProperty(std::string oldname, std::string newname) {
    if(newname.empty()) {
        return 4;
    }

    //check if an existing property already have the new name
    for(int j = 0; j < m_propertycount; j++) {
        if(m_properties[j]->name == newname) {
            return 2; //an existing property already have the name, return error
        }
    }

    for(int i = 0; i < m_propertycount; i++) {
        if(m_properties[i]->name == oldname) {                  //found correct property
            if(m_properties[i]->obligatory == false) {          //check if it is renamable
                m_properties[i]->name = newname;               //rename
                return 0;   //success
            }
            return 3;   //object not renamable
        }
    }
    return 1; //property not found :(
}

void ObjectTemplate::RemoveProperty(std::string name) {
    for(int i = 0; i < m_propertycount; i++) {
        if(m_properties[i]->name == name) {                     //found correct property
            if(m_properties[i]->obligatory == false) {          //check if it is removable
                delete m_properties[i];
                m_properties.erase(m_properties.begin() + i);   //removes
                m_propertycount--;
            }
            return;
        }
    }
    //property not found :(
}