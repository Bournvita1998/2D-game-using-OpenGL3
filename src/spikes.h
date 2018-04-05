#include "main.h"

#ifndef SPIKES_H
#define SPIKES_H


class spikes {
public:
    spikes() {}
    spikes(float x, float y,float v, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void set_speed(float v);
    double speed;
    double acc;
    double speedy;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // spikes_H
