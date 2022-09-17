#ifndef INTFIELD_H
#define INTFIELD_H

#include "Widget.h"

class IntField : public Widget {
    public:
    IntField(WidgetManager* wm, int x, int y, int w, int* variableptr);

    void Update() override;
    void Draw() override;

    void SetTargetVariable(int* variableptr);
    void AllowNegative(bool allow);
    void AllowNull(bool allow);

    void SetMinMax(int min, int max);

    private:
    bool m_isselected;
    bool m_allownegative;
    int m_allownull;
    int* m_varriableptr;

    int m_tempvariable;

    int m_minvalue;
    int m_maxvalue;
};

#endif