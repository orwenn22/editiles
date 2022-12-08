#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

class GridLayer;
class Layer;
class ObjectManager;

class Level {
    public:
    Level();
    Level(int width, int height, int boxwidth, int boxheight);
    ~Level();

    void Update();
    void PenUpdate(GridLayer* curlayer);
    void RectUpdate(GridLayer* curlayer);

    void Draw();
    void PenDraw();
    void RectDraw();

    //void AddLayer(std::string name);
    void AddLayer(Layer* newlayer);
    Layer* GetLayer(int index);
    void RemoveLayer(Layer* layerptr);

    void SwapLayers(int index1, int index2);

    void Save(std::string filename);
    
    void Resize(int newwidth, int newheight);

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

    bool m_ispainting;      //if set to true, change the values of the tiles below the mouse. (m_selectedtool = 0)
    int m_selectednumber;   //correspond to the selected tile in the palette
    
    int m_selectedtool;     //selected tool. 0 = pen, 1 = rectangle

    int m_rectoriginx;      //for rectangle tool, correspond to the tile indexes of the start of the rectangle
    int m_rectoriginy;      //^^^
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