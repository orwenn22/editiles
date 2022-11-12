#ifndef INTFIELD_H
#define INTFIELD_H

#include "Widget.h"

//IntField is a widget where the user can input a number
//and it will update a value stored at the destination of a pointer.
//It is also possible to specify a minimum and maximum value.
//The value stored at the pointer itself is overwritten when the
//user press enter or desselect the IntField by clicking anywhere else.
class IntField : public Widget {
    public:
    IntField(int x, int y, int w, int* variableptr);

    void Update() override;
    void Draw() override;

    void SetTargetVariable(int* variableptr);
    void AllowNegative(bool allow);
    void AllowNull(bool allow);

    void SetMinMax(int min, int max);

    private:
    bool m_isselected;      //If this is set to true, the IntField will read and react to keyboard input.
    bool m_allownegative;   //If this is set to false, the IntField won't allow negative value. (default : true)
    int m_allownull;        //is this is set to false, the intField won't allow 0 as a value. (default : true)
    int* m_varriableptr;    //Pointer to the int value that the IntField will update.

    //this value is stored in the IntField. 
    //When the user input something, this value is the thing that actually get changed and displayed.
    int m_tempvariable;

    int m_minvalue; //Minimum value that the IntField accept. (default : -10000)
    int m_maxvalue; //Maximum value that the IntField accept. (default : 10000)
};

#endif