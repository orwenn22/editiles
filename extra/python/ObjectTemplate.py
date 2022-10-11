import TemplateProperty

class ObjectTemplate(object):
    def __init__(self, name: str) -> None:
        self.name : str = name

        self.properties : list[TemplateProperty.TemplateProperty] = []
        self.properties.append(TemplateProperty.TemplateProperty("x", 0))
        self.properties.append(TemplateProperty.TemplateProperty("y", 0))
        self.properties.append(TemplateProperty.TemplateProperty("width", 8))
        self.properties.append(TemplateProperty.TemplateProperty("height", 8))

        import Instance
        self.children : list[Instance.Instance] = []
    
    def SetProperty(self, propname: str, value: int | str):
        for prop in self.properties:
            if prop.name == propname:
                prop.SetValue(value)
                return
        
        print("porperty", propname, "don't exist, adding to template of", self.name)
        self.properties.append(TemplateProperty.TemplateProperty(propname, value))