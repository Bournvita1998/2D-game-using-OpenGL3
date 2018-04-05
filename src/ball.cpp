#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float r,color_t color, int fl) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    speedy = 0;
    acc = 0;

    GLfloat vertex_buffer_data[720*9];

    int i;

    for(i=0;i<720;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i+1] = 0.0f;
        vertex_buffer_data[9*i+2] = 0.0f;
        vertex_buffer_data[9*i+3] = r * cos(i*M_PI/360);
        vertex_buffer_data[9*i+4] = r * sin(i*M_PI/360);
        vertex_buffer_data[9*i+5] = 0.0f;
        vertex_buffer_data[9*i+6] = r * cos((i+1)*M_PI/360);
        vertex_buffer_data[9*i+7] = r * sin((i+1)*M_PI/360);
        vertex_buffer_data[9*i+8] = 0.0f;
    };

    // static const GLfloat vertex_buffer_data[] = {
    //     -0.2, -0.2, 0, // vertex 1
    //     0.2,  -0.2, 0, // vertex 2
    //     0.2,  0.2, 0, // vertex 3

    //     0.2,  0.2, 0, // vertex 3
    //     -0.2, 0.2, 0, // vertex 4
    //     -0.2, -0.2, 0 // vertex 1
    // };
    if(fl==0){
        color_t colored[7]={COLOR_VIOLET,COLOR_INDIGO,COLOR_BLUE,COLOR_GREEN,COLOR_YELLOW,COLOR_ORANGE,COLOR_RED};
        this->object = create3DObject(GL_TRIANGLES, 720*3, vertex_buffer_data, colored, GL_FILL,7);
    }
    else
        this->object = create3DObject(GL_TRIANGLES, 720*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->position.x -= this->speed;
    this->position.y -= this->speedy;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
