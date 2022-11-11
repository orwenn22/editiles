#include "ParseFunctions.h"

#include "FileUtil/FileUtil.h"
#include "Layer/GridLayer.h"
#include "Layer/Instance.h"
#include "Layer/InstanceLayer.h"
#include "Layer/Layer.h"
#include "Layer/LayerIDs.h"
#include "Level.h"
#include "ObjectManager/ObjectManager.h"
#include "ObjectManager/ObjectProperty.h"
#include "ObjectManager/ObjectTemplate.h"

#include <string>

Level* ParseLVLFile(std::string filename) {
    FILE* infile = fopen(filename.c_str(), "r");

    if(infile == NULL) {
        printf("File don't exist :(\n");
        return NULL;
    }

    //check for signature
    if(!(getc(infile) == 'L' && getc(infile) == 'V' && getc(infile) == 'L')) {
        fclose(infile);
        return NULL;
    }

    ///////////////////////////////
    //size infos

    unsigned short lvlwidth = ReadShort(infile);
    unsigned short lvlheight = ReadShort(infile);
    unsigned short boxwidth = ReadShort(infile);
    unsigned short boxheight = ReadShort(infile);

    printf("Creating : %i %i %i %i\n", lvlwidth, lvlheight, boxwidth, boxheight);
    Level* newlevel = new Level(lvlwidth, lvlheight, boxwidth, boxheight);

    /////////////////////////
    //object templates

    unsigned short objecttempcount = ReadShort(infile);
    for(int i = 0; i < objecttempcount; i++) {
        ObjectTemplate* objtemplate = ParseObjectTemplate(infile);

        //Add object to level
        newlevel->m_objectmanager->Add(objtemplate);
    }


    ///////////////////////////////////
    //Layers

    unsigned short layercount = ReadShort(infile);
    for(int i = 0; i < layercount; i++) {
        Layer* newlayer = ParseLayer(infile, newlevel);
        newlevel->AddLayer(newlayer);
    }

    fclose(infile);
    return newlevel;
}

GridLayer* ParseTLMPFile(std::string filename) {
    FILE* infile = fopen(filename.c_str(), "r");
    if(infile == NULL) {
        return NULL;
    }

    if(!(getc(infile) == 't' && getc(infile) == 'l' && getc(infile) == 'm' && getc(infile) == 'p')) {
        fclose(infile);
        return NULL;
    }

    unsigned short width = ReadShort(infile);
    unsigned short height = ReadShort(infile);
    unsigned short type = ReadShort(infile);

    if(type != LAYERID_GRID) {
        fclose(infile);
        return NULL;
    }

    GridLayer* newgridlayer = ParseGridLayer(infile, width, height);

    fclose(infile);
    return newgridlayer;
}


ObjectTemplate* ParseObjectTemplate(FILE* fileptr) {
    //get name of the object
    std::string objectname = ReadString(fileptr);

        //create the object template
    ObjectTemplate* objtemplate = new ObjectTemplate(objectname);

    ////////////////////////////////////
    //obj template properties

    unsigned short propcount = ReadShort(fileptr);
    for(int j = 0; j < propcount; j++) {

        ObjectProperty* objprop = ParseObjectProperty(fileptr);
        std::string propname = objprop->name;

        //Add property to object
        if(propname == "x" || propname == "y" || propname == "width" || propname == "height") {     //obligatory property
            //set the value of property
            int propindex = objtemplate->GetPropertyIndex(propname);
            objtemplate->GetProperty(propindex)->SetValue(objprop->defaultvalue.as_int);

            //destroy previously created property
            delete objprop;
        } else {        //custom property
            //Add property to object
            objtemplate->AddProperty(objprop);
        }
    }

    return objtemplate;
}


ObjectProperty* ParseObjectProperty(FILE* fileptr) {
    //Get name of the property
    std::string propname = ReadString(fileptr);

    //create the property
    ObjectProperty* objprop = new ObjectProperty(propname);

    unsigned short proptype = ReadShort(fileptr);

    //Get the value
    if(proptype == OPT_INT) {       //int
        objprop->SetValue(ReadInt(fileptr));
    }
    else if(proptype == OPT_STR) {      //str
        std::string propvalue = ReadString(fileptr);
        objprop->SetValue(propvalue);
    }
    return objprop;
}

Layer* ParseLayer(FILE* fileptr, Level* lvlptr) {
    Layer* returnlayer;
    
    unsigned short layertype = ReadShort(fileptr);

    switch (layertype) {
        case LAYERID_GRID:
            {
                returnlayer = ParseGridLayer(fileptr, lvlptr);
            }
        break;
            
        case LAYERID_INSTANCE:
            {
                returnlayer = ParseInstanceLayer(fileptr, lvlptr);
            }
        break;

        default:
            printf("Unknown layer type : %i\n", layertype);
            returnlayer = NULL;
        break;
    }

    return returnlayer;
}

GridLayer* ParseGridLayer(FILE* fileptr, Level* lvlptr) {
    return ParseGridLayer(fileptr, lvlptr->m_width, lvlptr->m_height);
}

GridLayer* ParseGridLayer(FILE* fileptr, int w, int h) {
    std::string layername = ReadString(fileptr);
    GridLayer* newlayer = new GridLayer(w, h, layername);

    newlayer->m_tilemapname = ReadString(fileptr);

    int boxcount = newlayer->m_width * newlayer->m_height;
    for(int j = 0; j < boxcount; j++) {
        newlayer->m_griddata[j] = ReadShort(fileptr);
    }

    return newlayer;
}

InstanceLayer* ParseInstanceLayer(FILE* fileptr, Level* lvlptr) {
    std::string layername = ReadString(fileptr);

    InstanceLayer* newlayer = new InstanceLayer(layername);
                    
    int instancecount = ReadInt(fileptr);
    for(int j = 0; j < instancecount; j++) {
        

        //Add instance to layer
        newlayer->Add(ParseInstance(fileptr, lvlptr));
    }
    return newlayer;
}


Instance* ParseInstance(FILE* fileptr, Level* lvlptr) {
    //get the object template that correspond to the instance
    int objecttemplateindex = ReadShort(fileptr);
    ObjectTemplate* objecttemplate = lvlptr->m_objectmanager->Get(objecttemplateindex);

    //create the instance
    Instance* newinstance = new Instance(objecttemplate, 0, 0);

    //get all the properties of the instance
    for(int k = 0; k < objecttemplate->m_propertycount; k++) {
        int proptype = objecttemplate->GetProperty(k)->type;

        if(proptype == OPT_INT) {
            int propvalue = ReadInt(fileptr);
            printf("prop value for index %i : %i | ox%x\n", k, propvalue, propvalue);
            newinstance->m_properties[k].as_int = propvalue;
        }
        else if(proptype == OPT_STR) {
            std::string propvalue = ReadString(fileptr);
                    
            unsigned long l;
            for(l = 0; l < propvalue.size(); l++) {
                newinstance->m_properties[k].as_str[l] = propvalue[l];
            }
            newinstance->m_properties[k].as_str[l] = 0; //null terminator
        }
    }

    return newinstance;
}