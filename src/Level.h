#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

class Layer;
class ObjectManager;
class Level {
    public:
    Level();
    Level(int width, int height, int boxwidth, int boxheight);
    ~Level();

    void Update();
    void Draw();

    //void AddLayer(std::string name);
    void AddLayer(Layer* newlayer);
    Layer* GetLayer(int index);
    void RemoveLayer(Layer* layerptr);

    void SwapLayers(int index1, int index2);

    void Save(std::string filename);

    //private:
    int m_x;
    int m_y;

    //Levels info
    unsigned short m_boxwidth;      //width of a box in pixel
    unsigned short m_boxheight;     //height of a box in pixel

    unsigned short m_width;         //number of box horizontally
    unsigned short m_height;        //number of box vertically
    ////////////

    unsigned char m_zoom;

    //Layer 0 is on top
    //Layer 1 is behind
    //etc
    std::vector<Layer*> m_layers;
    int m_layercount;
    /////////////////

    //Object templates
    ObjectManager* m_objectmanager;

    //user selection
    int m_selectedlayer;

    bool m_ispainting;      //if set to true, change the values of the tiles below the mouse.
    int m_selectednumber;
    /////////////

    //DRAG & DROP to move the grid around
    bool m_followmouse;

    int m_xmouseoffset;
    int m_ymouseoffset;
    ////////////

    //overring
    int m_relativemouseposx;    //X and Y relative position of the mouse from the origin of the grid (dont't take m_zoom into account)
    int m_relativemouseposy;

    int m_overredboxx;  //X and Y index of the overred box
    int m_overredboxy;
    /////////////



};

#endif