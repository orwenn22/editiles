from io import BufferedReader

import BaseLayer
import GridLayer
import FileUtil
import InstanceLayer
import Instance
import ObjectTemplate

class Level(object):
    def __init__(self, width: int, height: int, boxwidth: int, boxheight: int) -> None:
        self.width : int = width
        self.height : int = height
        self.boxwidth : int = boxwidth
        self.boxheight : int = boxheight

        self.objects : list[ObjectTemplate.ObjectTemplate] = []
        self.layers : list[BaseLayer.Layer] = []
    

    def AddObject(self, newobj: ObjectTemplate.ObjectTemplate) -> int:
        for obj in self.objects:
            if newobj.name == obj.name:
                return 1    #error : object already exist
        
        self.objects.append(newobj)
        return 0    #success


def LoadlevelFromFile(filename: str) -> Level:
    loadfile : BufferedReader = open(filename, "rb")
    if loadfile.read(3) == b'LVL':
        #Level size infos
        levwidth = FileUtil.ReadUShort(loadfile)
        levheight = FileUtil.ReadUShort(loadfile)
        boxwidth = FileUtil.ReadUShort(loadfile)
        boxheight = FileUtil.ReadUShort(loadfile)

        # Create level
        newlevel = Level(levwidth, levheight, boxwidth, boxheight)

        # Object templates
        objcount : int = FileUtil.ReadUShort(loadfile)
        for i in range(0, objcount):
            #infos about object
            objname : str = FileUtil.ReadString(loadfile)
            objtemplate = ObjectTemplate.ObjectTemplate(objname)
            propcount : int = FileUtil.ReadUShort(loadfile)

            # Properties in the object template
            for j in range(0, propcount):
                #infos about property
                propname : str = FileUtil.ReadString(loadfile)
                proptype : str = FileUtil.ReadUShort(loadfile)
                propvalue : int | str

                if proptype == 0:   #int
                    propvalue = FileUtil.ReadInt(loadfile)
                elif proptype == 1: #str
                    propvalue = FileUtil.ReadString(loadfile)
                    
                #add property to object
                objtemplate.SetProperty(propname, propvalue)
            newlevel.AddObject(objtemplate)
            
        print("number of objects :", len(newlevel.objects))

        #layers
        layercount : int = FileUtil.ReadUShort(loadfile)

        for i in range(0, layercount):
            #infos about layers
            layertype : int = FileUtil.ReadUShort(loadfile)
            layername : str = FileUtil.ReadString(loadfile)

            if layertype == 1:
                layer = GridLayer.GridLayer(layername, newlevel.width, newlevel.height)
                layer.tilemapname : str = FileUtil.ReadString(loadfile)
                
                boxcount : int = layer.width * layer.height
                for j in range(0, boxcount):
                    layer.griddata[j] = FileUtil.ReadUShort(loadfile)
                
                newlevel.layers.append(layer)
            
            elif layertype == 2:
                layer = InstanceLayer.InstanceLayer(layername)
                instancecount : int = FileUtil.ReadInt(loadfile)

                #Instances
                for j in range(0, instancecount):
                    objtemplateindex : int = FileUtil.ReadUShort(loadfile)
                    objtemplate = newlevel.objects[objtemplateindex]

                    newinst = Instance.Instance(objtemplate)
                    newinst.properties.clear()

                    for prop in objtemplate.properties:
                        value : int | str
                        if prop.type == 0:
                            value = FileUtil.ReadInt(loadfile)
                        elif prop.type == 1:
                            value = FileUtil.ReadString(loadfile)
                            print(value)
                        else:
                            print("something went wrong")

                        newinst.properties.append(value)
                    
                    layer.instances.append(newinst)
                    

                newlevel.layers.append(layer)
            else:
                print("oof")
        
        loadfile.close()
        return newlevel

    loadfile.close()
    return object()