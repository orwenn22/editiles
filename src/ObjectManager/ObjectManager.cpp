#include "ObjectManager.h"

#include "../FileUtil/FileUtil.h"
#include "../Layer/Instance.h"
#include "../Layer/InstanceLayer.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerIDs.h"
#include "../Level.h"
#include "ObjectTemplate.h"

ObjectManager::ObjectManager() {
    m_objectcount = 0;
}

ObjectManager::~ObjectManager() {
    for(int i = 0; i < m_objectcount; i++) {
        delete m_objects[i];    //unload memory
    }
    m_objects.clear();          //clear vector
    EmptyTrashcan();
    printf("deleted objectmanager\n");
}

int ObjectManager::Add(ObjectTemplate* newobject) {
    //TODO : handle the case where an ObjectTemplate is already in a manager.
    
    for(int i = 0; i < m_objectcount; i++) {
        if(m_objects[i]->m_name == newobject->m_name) {
            return 1;     //don't add the object because it have the same name as another.
        }
    }
    m_objects.push_back(newobject);
    m_objectcount++;
    newobject->m_manager = this;
    newobject->m_isinmanager = true;
    printf("Added object, count: %i\n", m_objectcount);
    return 0;   //success
}

void ObjectManager::Delete(ObjectTemplate* objectptr) {
    //delete object from manager
    for(int i = 0; i < m_objectcount; i++) {
        if(m_objects[i] == objectptr) {
            //delete m_objects[i];
            m_trashcan.push_back(m_objects[i]);
            m_objects.erase(m_objects.begin() + i);
            m_objectcount--;
            printf("Deleted object, count: %i\n", m_objectcount);
            return;
        }
    }
}

int ObjectManager::GetObjectTemplateCount() {
    return m_objectcount;
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

void ObjectManager::Save(FILE* fileptr) {
    // Even tho the type of m_objectcount is int, it is improbable
    // that the ObjectManager contain more than 65535(?) objects,
    // So we save it as a short.
    WriteShort(fileptr, (short)m_objectcount);
    for(int i = 0; i < m_objectcount; i++) {
        m_objects[i]->Save(fileptr);
    }
}

void ObjectManager::SaveStandalone() {
    FILE* exportfile = fopen("export.objtb", "w");

    fputs("objtb", exportfile);
    Save(exportfile);

    fclose(exportfile);
}

void ObjectManager::EmptyTrashcan() {
    for(ObjectTemplate *obj : m_trashcan) delete obj;
    m_trashcan.clear();
}
