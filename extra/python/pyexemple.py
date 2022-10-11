import sys

import BaseLayer
import GridLayer
import InstanceLayer
import Level
import ObjectTemplate

g_level : Level.Level
g_havelevel : bool
g_isrunning : bool

def create(args: list[str]):
    global g_level
    global g_havelevel
    if len(args) == 5:
        g_level = Level.Level(int(args[1]), int(args[2]), int(args[3]), int(args[4]))
        g_havelevel = True
        print("empty level created.")

def load(args: list[str]):
    global g_level
    global g_havelevel
    if len(args) == 2:
        g_level = Level.LoadlevelFromFile(args[1])
        g_havelevel = True;

def addlayer(args: list[str]):
    global g_level
    if len(args) == 3:
        if g_havelevel:
            if args[1] == "1":
                g_level.layers.append(GridLayer.GridLayer(args[2], g_level.width, g_level.height))
            elif args[2] == "2":
                g_level.layers.append(InstanceLayer.InstanceLayer(args[2]))
    else:
        print("addlayer <type> <name>")

def lslayer(args: list[str]):
    global g_level
    if g_havelevel:
        print("layer count :", len(g_level.layers))
        for i in range(0, len(g_level.layers)):
            print(str(i) + " : name = " + g_level.layers[i].name + " type = " + str(g_level.layers[i].type))


useraction : dict = {
    "addlayer" : addlayer,
    "create"   : create,
    "lslayer"  : lslayer,
    "load"     : load,
}

def main(argc: int, argv: list[str]) -> int:
    global g_level
    global g_havelevel
    global g_isrunning

    g_havelevel = False
    g_isrunning = True

    while g_isrunning:
        print(">", end="")
        userin : str = input()

        args = userin.split(" ")
        if args[0] in useraction.keys():
            useraction[args[0]](args)
    return 0

if __name__ == "__main__":
    main(len(sys.argv), sys.argv)