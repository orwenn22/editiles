#ifndef PARSE_FUNCTIONS_H
#define PARSE_FUNCTIONS_H

#include <stdio.h>
#include <string>

class GridLayer;
class InstanceLayer;
class Instance;
class Layer;
class Level;
class ObjectManager;
class ObjectTemplate;

struct ObjectProperty;

Level* ParseLVLFile(std::string filename);
GridLayer* ParseTLMPFile(std::string filename);
ObjectManager* ParseOBJTBFile(std::string filename);    //OBJTB = OBJect TaBle

ObjectManager* ParseObjectTable(FILE* fileptr);
ObjectTemplate* ParseObjectTemplate(FILE* fileptr);
ObjectProperty* ParseObjectProperty(FILE* fileptr);


Layer* ParseLayer(FILE* fileptr, Level* lvlptr);

GridLayer* ParseGridLayer(FILE* fileptr, Level* lvlptr);
GridLayer* ParseGridLayer(FILE* fileptr, int w, int h);     //w and h are the number of tiles horizontally and vertically

InstanceLayer* ParseInstanceLayer(FILE* fileptr, Level* lvlptr);
Instance* ParseInstance(FILE* fileptr, Level* lvlptr);


#endif