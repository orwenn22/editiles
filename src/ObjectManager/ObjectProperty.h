#ifndef OBJECT_PROPERTY_H
#define OBJECT_PROPERTY_H

#include <string>

enum ObjectPropertyType {
    OPT_INT,
    OPT_STR,
};

struct ObjectProperty {
    std::string name;
    int type;

    //if this value is set to true, the property can't be ranamed, deleted
    //and its type can't be changed.
    bool obligatory;

    //if this value is set to false, the property can't have a default value
    bool havedefaultvalue;

    

    union {
        int as_int;                 //type 0
        char as_str[255];           //type 1
    } defaultvalue;

    ObjectProperty(std::string pname);

    void SetValue(int nval);
    void SetValue(std::string nval);
};

#endif