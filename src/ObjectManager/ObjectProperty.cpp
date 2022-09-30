#include "ObjectProperty.h"

ObjectProperty::ObjectProperty(std::string pname) {
    name = pname;
    type = OPT_INT;

    obligatory = false;

    havedefaultvalue = true;
    defaultvalue.as_int = 0;
}

void ObjectProperty::SetValue(int nval) {
    if(havedefaultvalue) {
        if(obligatory) {
            if(type == OPT_INT) {
                defaultvalue.as_int = nval;
                havedefaultvalue = true;
            }
        } else {
            type = OPT_INT;
            defaultvalue.as_int = nval;
            havedefaultvalue = true;
        }
    }
}

void ObjectProperty::SetValue(std::string nval) {
    if(havedefaultvalue) {
        if(obligatory) {
            if(type == OPT_STR) {
                int i;
                for(i = 0; i < nval.length() && i < 255; i++) {
                    defaultvalue.as_str[i] = nval[i];
                }
                defaultvalue.as_str[i] = 0;
                havedefaultvalue = true;
            }
        } else {
            type = OPT_STR;
            int i;
            for(i = 0; i < nval.length() && i < 255; i++) {
                defaultvalue.as_str[i] = nval[i];
            }
            defaultvalue.as_str[i] = 0;
            havedefaultvalue = true;
        }
    }
}