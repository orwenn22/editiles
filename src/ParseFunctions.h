#ifndef PARSE_FUNCTIONS_H
#define PARSE_FUNCTIONS_H

#include <stdio.h>
#include <string>

class GridLayer;
class InstanceLayer;
class Instance;
class Layer;
class Level;
class ObjectTemplate;

struct ObjectProperty;


ObjectTemplate* ParseObjectTemplate(FILE* fileptr);
ObjectProperty* ParseObjectProperty(FILE* fileptr);

Layer* ParseLayer(FILE* fileptr, Level* lvlptr);
GridLayer* ParseGridLayer(FILE* fileptr, Level* lvlptr);
InstanceLayer* ParseInstanceLayer(FILE* fileptr, Level* lvlptr);

Instance* ParseInstance(FILE* fileptr, Level* lvlptr);


#endif