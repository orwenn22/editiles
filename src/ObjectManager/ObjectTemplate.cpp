#include "ObjectTemplate.h"

#include "../Editor.h"
#include "../Layer/Instance.h"
#include "../Layer/InstanceLayer.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerIDs.h"
#include "../Level.h"
#include "ObjectProperty.h"

extern Editor* g_editor;

ObjectTemplate::ObjectTemplate(std::string name) {
    m_propertycount = 0;
    m_name = name;

    m_havetexture = false;

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

    //Add the property to the object template
    m_properties.push_back(newproperty);
    m_propertycount++;

    ////////////////////
    //Add the property to all the instances

    Level* level = g_editor->m_level;

    //loop throught all the layers
    for(int i = 0; i < level->m_layercount; i++) {
        if(level->GetLayer(i)->m_type == LAYERID_INSTANCE) {    //instance layer
            //get the layer
            InstanceLayer* layer = (InstanceLayer*)(level->GetLayer(i));

            layer->AddPropertyToAllInstances(this, newproperty);
        }
    }

    //printf("SUCCESS\n");
    return 0;
}

ObjectProperty* ObjectTemplate::GetProperty(int index) {
    if(index >= 0 && index < m_propertycount) {
        return m_properties[index];
    }
    return NULL;
}

int ObjectTemplate::GetPropertyIndex(std::string name) {
    for(int i = 0; i < m_propertycount; i++) {
        if(m_properties[i]->name == name) {
            return i;
        }
    }
    return -1;
}

int ObjectTemplate::GetPropertyIndex(ObjectProperty* propertyptr) {
    for(int i = 0; i < m_propertycount; i++) {
        if(m_properties[i] == propertyptr) {
            return i;
        }
    }
    return -1;
}

void ObjectTemplate::SetPropertyValue(std::string name, int value) {
    //get the index of the property in m_properties
    int propindex = GetPropertyIndex(name);

    //save informations before the change
    int previouspropertytype = m_properties[propindex]->type;
    int previousdefaultvalue = 0;
    if(previouspropertytype == OPT_INT) {
        previousdefaultvalue =m_properties[propindex]->defaultvalue.as_int;
    }


    int changeresult = m_properties[propindex]->SetValue(value);

    if(changeresult == 0) {     //change successful
        //get a pointer to the level
        Level* level = g_editor->m_level;

        
        //loop throught all the layers
        for(int i = 0; i < level->m_layercount; i++) {
            if(level->GetLayer(i)->m_type == LAYERID_INSTANCE) {    //instance layer
                //get the layer
                InstanceLayer* layer = (InstanceLayer*)(level->GetLayer(i));

                //apply the change to all the instances
                layer->ChangePropertyToAllInstances(this, propindex, previouspropertytype, previousdefaultvalue, value);
            }
        }
    }
}

void ObjectTemplate::SetPropertyValue(std::string name, std::string value) {
    int propindex = GetPropertyIndex(name);

    //save informations before the change
    int previouspropertytype = m_properties[propindex]->type;
    std::string previousdefaultvalue = "[{|}]";
    if(previouspropertytype == OPT_STR) {
        previousdefaultvalue = m_properties[propindex]->defaultvalue.as_str;
    }

    int changeresult = m_properties[propindex]->SetValue(value);

    if(changeresult == 0) {
        //get a pointer to the level
        Level* level = g_editor->m_level;

        
        //loop throught all the layers
        for(int i = 0; i < level->m_layercount; i++) {
            if(level->GetLayer(i)->m_type == LAYERID_INSTANCE) {    //instance layer
                //get the layer
                InstanceLayer* layer = (InstanceLayer*)(level->GetLayer(i));

                layer->ChangePropertyToAllInstances(this, propindex, previouspropertytype, previousdefaultvalue, value);
                
            }   //if(layertype == LAYERID_INSTANCE)
        }   //loop throught layers
    }
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
    int indexofremovedprop = -1;

    for(int i = 0; i < m_propertycount; i++) {
        if(m_properties[i]->name == name) {                     //found correct property
            if(m_properties[i]->obligatory == false) {          //check if it is removable
                delete m_properties[i];
                m_properties.erase(m_properties.begin() + i);   //removes
                m_propertycount--;
                indexofremovedprop = i;
            }
            break;
        }
    }

    //check if a property was removed
    if(indexofremovedprop != -1) {
        Level* level = g_editor->m_level;

        //loop throught all the layers
        for(int i = 0; i < level->m_layercount; i++) {
            if(level->GetLayer(i)->m_type == LAYERID_INSTANCE) {    //instance layer
                //get the layer
                InstanceLayer* layer = (InstanceLayer*)(level->GetLayer(i));
                //remove properties from instances
                layer->RemovePropertyFromInstances(this, indexofremovedprop);
            }
        }
    }
}