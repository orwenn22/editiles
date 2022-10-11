import ObjectTemplate

class Instance(object):
    def __init__(self, obj: ObjectTemplate.ObjectTemplate) -> None:
        self.object : ObjectTemplate.ObjectTemplate = obj
        self.object.children.append(self)

        self.properties : list[int | str] = []

        #copy default properties in object
        for prop in self.object.properties:
            self.properties.append(prop.value)
    
    def __del__(self):
        self.object.children.remove(self)
    
    def SetPropValue(self, propname: str, value: int | str):
        for i in range(len(self.object.properties)):
            prop = self.object.properties[i]
            if prop.name == propname:
                self.properties[i] = value
                return
        
        print("property", propname, "not fount on Instance of object", self.object.name)