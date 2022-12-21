#include "ObjectTemplate.h"

#include "../FileUtil/FileUtil.h"
#include "../Layer/Instance.h"
#include "../Layer/InstanceLayer.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerIDs.h"
#include "../Level.h"
#include "ObjectProperty.h"

ObjectTemplate::ObjectTemplate(std::string name) {
    m_propertycount = 0;
    m_childrencount = 0;
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

    m_manager = NULL;
    m_isinmanager = false;
}

ObjectTemplate::~ObjectTemplate() {
    for(int i = 0; i < m_propertycount; i++) {
        delete m_properties[i];
    }
    m_properties.clear();
    m_propertycount = 0;

    //delete all the instances in the level that uses this object
    while(m_childrencount != 0) {
        Instance* inst = m_children[0];
        inst->m_parrent->RemoveWithPtr(inst);   //this will also deallocate the instance and remove it from m_children
    }

    //Do this just in case
    m_children.clear();
    m_childrencount = 0;

    m_manager = NULL;
    m_isinmanager = false;
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

    for(int i = 0; i < m_childrencount; i++) {
        Instance* instance = m_children[i];
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
        //update all instances
        for(int i = 0; i < m_childrencount; i++) {
            Instance* instance = m_children[i];

            if(previouspropertytype == OPT_INT) {   //previous prop type was the same as the new
                //check if the value of the instance is the old default value...
                if(instance->m_properties[propindex].as_int == previousdefaultvalue) {
                    instance->m_properties[propindex].as_int = value;   //...if so replace it by the new one.
                    printf("instance value updated\n");
                }
            }
            else {      //old default value type is different as the new one so replace default value
                instance->m_properties[propindex].as_int = value;
                printf("instance value updated\n");
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
        //update all instances
        for(int i = 0; i < m_childrencount; i++) {
            Instance* instance = m_children[i];

            if(previouspropertytype == OPT_STR) {   //previous prop type was the same as the new
                //check if the value of the instance is the old default value...
                if(previousdefaultvalue == std::string(instance->m_properties[propindex].as_str)) {
                    //...if so replace it by the new one.
                    for(int k = 0; k < 255; k++) {
                        char c = value[k];
                        instance->m_properties[propindex].as_str[k] = c;
                        if(c == 0) break;    //end of string
                    }
                    printf("instance value updated\n");
                }
            }
            else {      //old default value type is different as the new one so replace default value
                for(int k = 0; k < 255; k++) {
                    char c = value[k];
                    instance->m_properties[propindex].as_str[k] = c;
                    if(c == 0) break;    //end of string
                }
                printf("instance value updated\n");
            }
        }
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
        //remove the property from all the instances
        for(int i = 0; i < m_childrencount; i++) {
            Instance* instance = m_children[i];
            instance->m_properties.erase(instance->m_properties.begin() + indexofremovedprop);
        }
    }
}

//this is called from the Instance constructor
void ObjectTemplate::AddChildren(Instance* inst) {
    m_children.push_back(inst);
    m_childrencount += 1;
}

//this is called from the Instance destructor
void ObjectTemplate::RemoveChildren(Instance* inst) {
    for(int i = 0; i < m_childrencount; i++) {
        if(m_children[i] == inst) {
            m_children.erase(m_children.begin() + i);
            m_childrencount--;
            return;
        }
    }
}

void ObjectTemplate::Save(FILE* fileptr) {
    //printf("TODO : implement saving object\n");

    //name of the object
    for(size_t i = 0; i < m_name.size(); i++) {
        putc(m_name[i], fileptr);
    }
    putc(0, fileptr);   //null-termination

    //number of properties on the object
    WriteShort(fileptr, (short) m_propertycount);

    //save all the properties
    for(int i = 0; i < m_propertycount; i++) {
        ObjectProperty* prop = m_properties[i];

        //name of the property
        for(size_t j = 0; j < prop->name.size(); j++) {
            putc(prop->name[j], fileptr);
        }
        putc(0, fileptr);   //null-termination

        //property type
        WriteShort(fileptr, (short) (prop->type));

        //property default value
        if(prop->type == OPT_INT) {     //int property
            WriteInt(fileptr, prop->defaultvalue.as_int);
        } 
        else if(prop->type == OPT_STR) {    //string property
            for(int j = 0; prop->defaultvalue.as_str[j] != 0 && j < 255; j++) {
                putc(prop->defaultvalue.as_str[j], fileptr);
            }
            putc(0, fileptr);   //null-termination
        }
    }
}

void ObjectTemplate::SaveStandalone(std::string filename) {
    FILE* exportfile = fopen(filename.c_str(), "w");
    fprintf(exportfile, "obj");

    Save(exportfile);

    fclose(exportfile);
}