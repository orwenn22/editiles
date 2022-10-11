import BaseLayer

class InstanceLayer(BaseLayer.Layer):
    def __init__(self, name: str) -> None:
        super().__init__(name)
        self.type = 2

        import Instance
        self.instances : list[Instance.Instance] = []