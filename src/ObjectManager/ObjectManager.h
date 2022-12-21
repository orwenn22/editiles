#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>
#include <string>

class Level;
class ObjectTemplate;

class ObjectManager {
    public:
    ObjectManager();
    ~ObjectManager();

    int Add(ObjectTemplate* newobject);         //Add an object to m_objects
    ObjectTemplate* Get(int objectindex);       //return the pointer at index objectindex in m_objects
    int GetIndex(ObjectTemplate* objectptr);    //return the index of objectptr in m_objects
    void Delete(ObjectTemplate* objectptr);     //Delete objectptr of m_objects (will free memory)

    int RenameObject(std::string oldname, std::string newname);     //return 0 if the object was renamed correctly

    void Save(FILE* fileptr);
    void SaveStandalone();


    //object templates have unique names
    std::vector<ObjectTemplate*> m_objects;
    int m_objectcount;
};

#endif