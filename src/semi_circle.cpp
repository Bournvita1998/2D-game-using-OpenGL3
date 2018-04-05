#include "semi_circle.h"
#include "main.h"

semi_circle::semi_circle(float r ,float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    GLfloat g_vertex_buffer_data[720*9];

    int i;

    for(i=0;i<360;i++)
    {
        g_vertex_buffer_data[9*i] = 0.0f;
        g_vertex_buffer_data[9*i+1] = 0.0f;
        g_vertex_buffer_data[9*i+2] = 0.0f;
        g_vertex_buffer_data[9*i+3] = r * cos(-i*M_PI/360);
        g_vertex_buffer_data[9*i+4] = r * sin(-i*M_PI/360);
        g_vertex_buffer_data[9*i+5] = 0.0f;
        g_vertex_buffer_data[9*i+6] = r * cos(-(i+1)*M_PI/360);
        g_vertex_buffer_data[9*i+7] = r * sin(-(i+1)*M_PI/360);
        g_vertex_buffer_data[9*i+8] = 0.0f;
    }

    // glDrawArrays(GL_TRIANGLES, 0, 720*9); // 3 indices starting at 0 -> 1 triangle

    // static const GLfloat vertex_buffer_data[] = {
    //     0, 0, 0, // vertex 1
    //     0.1, 0, 0, // vertex 2
    //     0, 1, 0, // vertex 3

    //     0.1, 0, 0, // vertex 3
    //     0, 1, 0, // vertex 4
    //     0.1, 1, 0 // vertex 1
    // };

    this->object = create3DObject(GL_TRIANGLES, 360*3, g_vertex_buffer_data, color, GL_FILL);
}

void semi_circle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void semi_circle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void semi_circle::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}