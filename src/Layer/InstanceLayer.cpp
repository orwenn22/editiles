#include "InstanceLayer.h"

#include "../FileUtil/FileUtil.h"
#include "../Level.h"
#include "../ObjectManager/ObjectProperty.h"
#include "Instance.h"
#include "LayerIDs.h"

InstanceLayer::InstanceLayer(Level* level, std::string name) : Layer(level, name) {
    m_type = LAYERID_INSTANCE;
    m_instancecount = 0;
}

InstanceLayer::~InstanceLayer() {
    for(int i = 0; i < m_instancecount; i++) {
        delete m_instances[i];
    }
    m_instances.clear();
    m_instancecount = 0;
}

void InstanceLayer::Add(Instance* newinstance) {
    m_instances.push_back(newinstance);
    m_instancecount++;
}

Instance* InstanceLayer::Get(int index) {
    if(index >= 0 && index < m_instancecount) {
        return m_instances[index];
    }
    return NULL;
}

void InstanceLayer::Save(FILE* fileptr) {
    Layer::Save(fileptr);

    //number of instance
    WriteInt(fileptr, m_instancecount);

    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->Save(fileptr);
    }
}

void InstanceLayer::RemoveWithIndex(int index) {
    if(index >= 0 && index < m_instancecount) {
        delete m_instances[index];
        m_instances.erase(m_instances.begin() + index);
        m_instancecount--;
    }
}

void InstanceLayer::RemoveWithPtr(Instance* instanceptr) {
    for(int i = 0; i < m_instancecount; i++) {
        if(m_instances[i] == instanceptr) {
            RemoveWithIndex(i);
            return;
        }
    }
}

void InstanceLayer::Update(int x, int y) {
    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->Update(x, y, m_parrent->m_zoom);
    }
}

void InstanceLayer::CheckMouseInput() {
    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->CheckMouseInput();
    }
}

void InstanceLayer::Draw(int x, int y) {
    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->Draw();
    }
}

void InstanceLayer::AddPropertyToAllInstances(ObjectTemplate* instancestype, ObjectProperty* newproperty) {
    //loop throught the instances of the layer
    for(int i = 0; i < m_instancecount; i++) {
        Instance* instance = m_instances[i];

        //check if the instance correspond to the object
        if(instance->m_objtemplateptr == instancestype) {
            //add the property to the instance with the default value
            InstancePropertyValue newvalue;
            if(newproperty->type == OPT_INT) {
                newvalue.as_int = newproperty->defaultvalue.as_int;
            }
            else if(newproperty->type == OPT_STR) {
                for(int k = 0; k < 255; k++) {
                    char c = newproperty->defaultvalue.as_str[k];
                    newvalue.as_str[k] = c;
                    if(c == 0) break;
                }
            }
            instance->m_properties.push_back(newvalue);
        }
    }
}

void InstanceLayer::ChangePropertyToAllInstances(ObjectTemplate* instancestype, int propertyindex, int oldpropertytype, int oldpropertyvalue, int newpropertyvalue) {
    //loop throught the instances of the layer
    for(int i = 0; i < m_instancecount; i++) {
        Instance* instance = m_instances[i];

        //check if the instance correspond to the object
        if(instance->m_objtemplateptr == instancestype) {
            if(oldpropertytype == OPT_INT) {   //previous prop type was the same as the new
                //check if the value of the instance is the old default value...
                if(instance->m_properties[propertyindex].as_int == oldpropertyvalue) {
                    instance->m_properties[propertyindex].as_int = newpropertyvalue;   //...if so replace it by the new one.
                    printf("instance value updated\n");
                }
            }
            else {      //old default value type is different as the new one so replace default value
                instance->m_properties[propertyindex].as_int = newpropertyvalue;
                printf("instance value updated\n");
            }
        }
    }
}

void InstanceLayer::ChangePropertyToAllInstances(ObjectTemplate* instancestype, int propertyindex, int oldpropertytype, std::string oldpropertyvalue, std::string newpropertyvalue) {
    //loop throught the instances of the layer
    for(int i = 0; i < m_instancecount; i++) {
        Instance* instance = m_instances[i];

        //check if the instance correspond to the object
        if(instance->m_objtemplateptr == instancestype) {
            if(oldpropertytype == OPT_STR) {   //previous prop type was the same as the new
                //check if the value of the instance is the old default value...
                if(oldpropertyvalue == std::string(instance->m_properties[propertyindex].as_str)) {
                    //...if so replace it by the new one.
                    for(int k = 0; k < 255; k++) {
                        char c = newpropertyvalue[k];
                        instance->m_properties[propertyindex].as_str[k] = c;
                        if(c == 0) break;    //end of string
                    }
                    printf("instance value updated\n");
                }
            }
            else {      //old default value type is different as the new one so replace default value
                for(int k = 0; k < 255; k++) {
                    char c = newpropertyvalue[k];
                    instance->m_properties[propertyindex].as_str[k] = c;
                    if(c == 0) break;    //end of string
                }
                printf("instance value updated\n");
            }
        }
    }
}

void InstanceLayer::RemovePropertyFromInstances(ObjectTemplate* instancestype, int indextoremove) {
    //loop throught the instances of the layer
    for(int i = 0; i < m_instancecount; i++) {
        Instance* instance = m_instances[i];

        //check if the instance correspond to the object
        if(instance->m_objtemplateptr == instancestype) {
            //remove the property
            instance->m_properties.erase(instance->m_properties.begin() + indextoremove);
        }
    }
}