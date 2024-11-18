#include "datebox.h"

DateBox::DateBox(Shader &shader, vec2 pos, vec2 size, Date day) : Rect(shader, pos, size, color(1, 1, 1, 1))
{
    this->day = day;
}

Date DateBox::getDay()
{
    return day;
}
