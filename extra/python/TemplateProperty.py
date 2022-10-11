class TemplateProperty(object):
    def __init__(self, name : str) -> None:
        self.name : str = name
        self.type : int = 0
        self.value : int | str = 0
    
    def __init__(self, name : str, value : int | str) -> None:
        self.name : str = name
        self.SetValue(value)

    def SetValue(self, value: int | str):
        if type(value) == int:
            self.type = 0
        elif type(value) == str:
            self.type = 1
        self.value = value
