#include "InstancePropertiesList.h"

#include "../Layer/Instance.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"

#include <raylib.h>

InstancePropertiesList::InstancePropertiesList(WidgetManager* widgetmanager, Instance* instanceptr, int x, int y, int w, int h)
: ElementList(widgetmanager, x, y, w, h) {
    m_instanceptr = instanceptr;
    m_elementheight = 15;
    m_canselectelement = false;
}

int InstancePropertiesList::GetElementCount() {
    return m_instanceptr->m_objtemplateptr->m_propertycount;
}

void InstancePropertiesList::DrawElement(int painterx, int paintery, int elementindex) {
    int xcenter = m_width / 2;
    ObjectProperty* propintemplate = m_instanceptr->m_objtemplateptr->GetProperty(elementindex);
    
    DrawText(propintemplate->name.c_str() ,painterx + 2, paintery + 2, 10, WHITE);

    DrawLine(painterx + xcenter, paintery, painterx + xcenter, paintery + m_elementheight, GRAY);

    DrawText(TextFormat("%i", m_instanceptr->m_properties[elementindex].as_int), painterx + xcenter + 2, paintery + 2, 10, WHITE);
}