#include "main.h"

#ifndef semi_circle_H
#define semi_circle_H


class semi_circle {
public:
    semi_circle() {}
    semi_circle(float r, float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double acc;
    double speedy;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // semi_circle_H