import BaseLayer


class GridLayer(BaseLayer.Layer):
    def __init__(self, name: str, width: int, height: int) -> None:
        super().__init__(name)
        self.type = 1
        self.width = width
        self.height = height
        
        self.tilemapname : str = ""
        self.griddata : list[int] = [0] * width * height
    
    def GetBox(self, x: int, y: int) -> int:
        if 0 <= x < self.width and 0 <= y < self.height:
            return self.griddata[x + y*self.width]
        return -1
    
    def SetBox(self, x: int, y: int, value: int):
        if 0 <= value <= 65535:
            if 0 <= x < self.width and 0 <= y < self.height:
                self.griddata[x + y*self.width] = value