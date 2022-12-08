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
    import ParseUtil

    #FIXME: Here we assume that the file will open successfully.
    #       Maybe it would be a nice idea to handle the opposite case.

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
        objtable = ParseUtil.ParseObjectTable(loadfile)
        newlevel.objects = objtable
            
        print("number of objects :", len(newlevel.objects))

        #layers
        layercount : int = FileUtil.ReadUShort(loadfile)

        for i in range(0, layercount):
            newlevel.layers.append(ParseUtil.ParseLayer(loadfile, newlevel))

        
        loadfile.close()
        return newlevel

    # This is to supposed to be reached
    loadfile.close()
    return object()