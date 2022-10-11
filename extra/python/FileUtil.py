from io import BufferedReader

def ReadUShort(file: BufferedReader) -> int:
    return int.from_bytes(file.read(2), byteorder="big", signed=False)

def ReadShort(file: BufferedReader) -> int:
    return int.from_bytes(file.read(2), byteorder="big", signed=True)

def ReadUInt(file: BufferedReader) -> int:
    return int.from_bytes(file.read(4), byteorder="big", signed=False)

def ReadInt(file: BufferedReader) -> int:
    return int.from_bytes(file.read(4), byteorder="big", signed=True)

def ReadString(file: BufferedReader) -> str:
    r : str = ''
    c : bytes = file.read(1)
    while c != b'\x00':
        r += c.decode()
        c = file.read(1)
    return r