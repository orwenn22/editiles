from io import BufferedReader

import BaseLayer
import GridLayer
import FileUtil
import Instance
import InstanceLayer
import Level
import ObjectTemplate

#############################################
# Everything related to Objects and ObjectProperties

def ParseObjectProperty(loadfile : BufferedReader) -> tuple[str, int | str]:
    #infos about property
    propname : str = FileUtil.ReadString(loadfile)
    proptype : str = FileUtil.ReadUShort(loadfile)
    propvalue : int | str

    if proptype == 0:   #int
        propvalue = FileUtil.ReadInt(loadfile)
    elif proptype == 1: #str
        propvalue = FileUtil.ReadString(loadfile)

    return (propname, propvalue)


def ParseObjectTemplate(loadfile : BufferedReader) -> ObjectTemplate.ObjectTemplate:
    #infos about object
    objname : str = FileUtil.ReadString(loadfile)
    objtemplate = ObjectTemplate.ObjectTemplate(objname)
    propcount : int = FileUtil.ReadUShort(loadfile)
    
    # Properties in the object template
    for j in range(0, propcount):
        prop = ParseObjectProperty(loadfile)        
        #add property to object
        objtemplate.SetProperty(prop[0], prop[1])   # [0] : name  |  [1] : value
    
    return objtemplate


def ParseObjectTable(loadfile : BufferedReader) -> list[ObjectTemplate.ObjectTemplate]:
    objlist = []
    objcount : int = FileUtil.ReadUShort(loadfile)

    for i in range(0, objcount):
        objlist.append(ParseObjectTemplate(loadfile))
    
    return objlist



########################
# Parse a GridLayer

def ParseGridLayer(loadfile : BufferedReader, gridwidth : int, gridheight : int) -> GridLayer.GridLayer:
    layername : str = FileUtil.ReadString(loadfile)
    layer = GridLayer.GridLayer(layername, gridwidth, gridheight)
    layer.tilemapname : str = FileUtil.ReadString(loadfile)
                
    boxcount : int = layer.width * layer.height
    for j in range(0, boxcount):
        layer.griddata[j] = FileUtil.ReadUShort(loadfile)
                
    return layer


#########################################################
# Everything related to Instances and InstanceLayers


def ParseInstance(loadfile : BufferedReader, lvl : Level.Level) -> Instance.Instance:
    objtemplateindex : int = FileUtil.ReadUShort(loadfile)
    objtemplate = lvl.objects[objtemplateindex]

    newinst = Instance.Instance(objtemplate)
    newinst.properties.clear()

    for prop in objtemplate.properties:
        value : int | str
        if prop.type == 0:
            value = FileUtil.ReadInt(loadfile)
        elif prop.type == 1:
            value = FileUtil.ReadString(loadfile)
            #print(value)
        else:
            print("unknown property type")

        newinst.properties.append(value)
    
    return newinst


def ParseInstanceLayer(loadfile : BufferedReader, lvl : Level.Level) -> InstanceLayer.InstanceLayer:
    layername : str = FileUtil.ReadString(loadfile)
    layer = InstanceLayer.InstanceLayer(layername)
    instancecount : int = FileUtil.ReadInt(loadfile)

    #Instances
    for j in range(0, instancecount):
        layer.instances.append(ParseInstance(loadfile, lvl))
    
    return layer



###############################################



def ParseLayer(loadfile : BufferedReader, lvl : Level.Level) -> BaseLayer.Layer:
    #get the type of the layer
    layertype : int = FileUtil.ReadUShort(loadfile)
    layer = BaseLayer.Layer("[no layer]")

    if layertype == 1:
        layer = ParseGridLayer(loadfile, lvl.width, lvl.height)
    elif layertype == 2:
        layer = ParseInstanceLayer(loadfile, lvl)
    else:
        print("unknown layer type :(")
    
    return layer