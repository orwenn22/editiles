#include "ObjectManager.h"

#include "ObjectTemplate.h"

ObjectManager::ObjectManager(Level* lvl) {
    m_parrent = lvl;
    m_objectcount = 0;
}

ObjectManager::~ObjectManager() {
    for(int i = 0; i < m_objectcount; i++) {
        delete m_objects[i];    //unload memory
    }
    m_objects.clear();          //clear vector
    printf("deleted objectmanager\n");
}

int ObjectManager::Add(ObjectTemplate* newobject) {
    for(int i = 0; i < m_objectcount; i++) {
        if(m_objects[i]->m_name == newobject->m_name) {
            return 1;     //don't add the object because it have the same name as another.
        }
    }
    m_objects.push_back(newobject);
    m_objectcount++;
    printf("Added object, count: %i\n", m_objectcount);
    return 0;
}

void ObjectManager::Delete(ObjectTemplate* objectptr) {
    for(int i = 0; i < m_objectcount; i++) {
        if(m_objects[i] == objectptr) {
            delete m_objects[i];
            m_objects.erase(m_objects.begin() + i);
            m_objectcount--;
            return;
        }
    }
}

ObjectTemplate* ObjectManager::Get(int index) {
    if(index >= 0 && index < m_objectcount) {
        return m_objects[index];
    }
    return nullptr;
}

int ObjectManager::GetIndex(ObjectTemplate* objectptr) {
    for(int i = 0; i < m_objectcount; i++) {
        if(m_objects[i] == objectptr) {
            return i;
        }
    }
    return -1;      //object don't exist :(
}

int ObjectManager::RenameObject(std::string oldname, std::string newname) {
    //check if an object already have the new name
    for(int i = 0; i < m_objectcount; i++) {
        if(m_objects[i]->m_name == newname) {
            return 2;  //an object already have this name :(
        }
    }

    for(int i = 0; i < m_objectcount; i++) {
        if(m_objects[i]->m_name == oldname) {
            m_objects[i]->m_name = newname;
            return 0;   //object renamed successfully
        }
    }
    return 1;  //object with the old name not found
}