#include "ObjectProperty.h"

ObjectProperty::ObjectProperty(std::string pname) {
    name = pname;
    type = OPT_INT;

    obligatory = false;

    havedefaultvalue = true;
    defaultvalue.as_int = 0;
}

int ObjectProperty::SetValue(int nval) {
    if(havedefaultvalue) {
        if(obligatory) {        //type can't be changed if obligatory
            if(type == OPT_INT) {   //check if the type is correct
                defaultvalue.as_int = nval;     //change the value
                havedefaultvalue = true;
            }
            else {      //wrong type
                return 1;   //failure
            }
        }
        else {              //property added by user, so type can be changed
            type = OPT_INT;                 //change type
            defaultvalue.as_int = nval;     //change value
        }
    }
    else {          //property can't have a default value
        return 1;   //failure
    }
    return 0;       //success
}

int ObjectProperty::SetValue(std::string nval) {
    if(havedefaultvalue) {
        if(obligatory) {        //type can't be changed if obligatory
            if(type == OPT_STR) {   //check if the type is correct
                //change the value
                size_t i;
                for(i = 0; i < nval.length() && i < 255; i++) {
                    defaultvalue.as_str[i] = nval[i];
                }
                defaultvalue.as_str[i] = 0;
                havedefaultvalue = true;
            } else {        //wrong type
                return 1;   //failure
            }
        } else {         //property added by user, so type can be changed
            type = OPT_STR;     //change type
            //change value
            size_t i;
            for(i = 0; i < nval.length() && i < 255; i++) {
                defaultvalue.as_str[i] = nval[i];
            }
            defaultvalue.as_str[i] = 0;
            havedefaultvalue = true;
        }
    } 
    else {          //property can't have a default value
        return 1;   //failure
    }
    return 0;   //success
}