#ifndef LIGHT_H
#define LIGHT_H

#include "rect.h"
#include "../shader/shader.h"
#include <iostream>
#include "../Date.h"
using glm::vec2, glm::vec3;

class DateBox : public Rect
{
private:
    Date day;

public:
    /// @brief Construct a new Square object
    /// @details This constructor will call the InitRenderData function.
    /// @param shader The shader to use
    /// @param pos The position of the square
    /// @param size The size of the square
    /// @param day The Date the DateBox holds
    DateBox(Shader &shader, vec2 pos, vec2 size, Date day);


    Date getDay();

};

#endif
