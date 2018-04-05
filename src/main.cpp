#include "main.h"
#include "timer.h"
#include "ball.h"
#include "Ground1.h"
#include "Ground2.h"
#include "trap.h"
#include "semi_circle.h"
#include "spikes.h"
#include "score.h"
#include "line.h"
#include "digit.h"
#include "Rectangle.h"


using namespace std;

int flag =0;
int flag2 = 0;
int tim=0;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Score score,level;
int score1=0;
Ball ball1 , Villans[100];
Ground1 ground1;
Ground2 ground2;
trap TRAP1 , TRAP2;
semi_circle SEMI1,SEMI2, MC1 ,MC11;
spikes SPI1 , SPI2;
Rectangle rec1,rec2;
Rectangle rec3,rec4;
extern double drag_oldx, drag_oldy;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground1.draw(VP);
    ground2.draw(VP);
    TRAP1.draw(VP);
    TRAP2.draw(VP);
    SEMI1.draw(VP);
    SEMI2.draw(VP);
    score.draw(VP);
    level.draw(VP);
    SPI1.draw(VP);
    SPI2.draw(VP);


    if(((score1 % 1000 == 0 && score1 ) || ( tim>0 &&tim <10000  )) && ( score1 > 2000 ))
    {
        tim+=30;
        MC1.draw(VP);
        MC11.draw(VP);
        rec1.draw(VP);
        rec2.draw(VP);
        rec3.draw(VP);
        rec4.draw(VP);
        ball1.position.x-=0.03;

        level.update(3);


        // if(ball1.position.x >- 4 && ball1.position.x < 4) 
        // {
        // ball1.rotation +=5;
        // }
    }
    else
    {
        tim=0;
    }


    if(((score1 % 1000 == 0 && score1 ) || ( tim>0 &&tim <10000  )) && ( score1 > 1000 ))
    {
        tim+=30;
        MC1.draw(VP);
        MC11.draw(VP);
        rec1.draw(VP);
        rec2.draw(VP);
        rec3.draw(VP);
        rec4.draw(VP);
        ball1.position.x-=0.03;
        if(score1 < 2000){
        level.update(2);
        }
        // if(ball1.position.x >- 4 && ball1.position.x < 4) 
        // {
        // ball1.rotation +=5;
        // }
    }
    else
    {
        tim=0;
    }

    // if((score1%1000 == 0 || score1%1000 == 100) && score1 != 0 && score1 != 100)
    // {
        // MC1.draw(VP);
        // MC11.draw(VP);
        // rec1.draw(VP);
        // rec2.draw(VP);
        // rec3.draw(VP);
        // rec4.draw(VP);
    // }

    ball1.draw(VP);

    int j=0;
    for(j=0;j<10;j++)
    {
        Villans[j].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int a_arrow = glfwGetKey(window, GLFW_KEY_A);
    int s_arrow = glfwGetKey(window, GLFW_KEY_S);
    int d_arrow = glfwGetKey(window, GLFW_KEY_D);
    int w_arrow = glfwGetKey(window, GLFW_KEY_W);
	int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	 if (mouse_clicked) {
        if (drag_oldx == -1 && drag_oldy == -1) {
            glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
        }
        else {
            int w, h;
            double new_x, new_y;
            glfwGetCursorPos(window, &new_x, &new_y);
            glfwGetWindowSize(window, &w, &h);
            float pos_x, pos_y;
            pos_x = 8 * (new_x - drag_oldx) / (w * screen_zoom);
            ball1.position.x = pos_x;
            // drag_oldx = new_x;
            // drag_oldy = new_y;
        }
    }

    if (screen_center_x - 4/screen_zoom > -6 && a_arrow) {
            screen_center_x -= 0.06;
            reset_screen();
        }

    if (screen_center_y - 4/screen_zoom > -8 && s_arrow) {
        screen_center_y -= 0.06;
        reset_screen();
    }

    if (screen_center_x + 4/screen_zoom < 6 && d_arrow) {
        screen_center_x += 0.06;
        reset_screen();
    }

    if (screen_center_y + 4/screen_zoom < 10 && w_arrow) {
        screen_center_y += 0.06;
        reset_screen();
    }



    if (left) {
        // Do something
        ball1.position.x -= 0.06;
        // ball1.rotation+=10;
    }
    if (right) {
        // Do something
        ball1.position.x += 0.06;
        // ball1.rotation-=10;
    }
    if (space && flag == 0) {
    // if (space) {
        // Do something
        // ball1.position.y += 0.01;
        ball1.speedy = -0.25;
        ball1.acc = -0.01;
        flag =-1;
    }

    if(ball1.position.x <= 1 && ball1.position.x >= -1 && ball1.position.y <= -1.7 ){
        if(ball1.position.x*ball1.position.x > 0.75*0.75){
            ball1.position.y=-1.85;
            return;
        }
        // ball1.position.x-=0.01;
        ball1.position.y = -sqrt(0.75 * 0.75 - ball1.position.x * ball1.position.x)-2;
        // ball1.acc = -3;
        // if(space){
        //     ball1.speedy = -0.5;
        //     ball1.acc = -0.01;
        // }

        if(flag2 == 0 && space){
            ball1.speedy = -0.3;
            ball1.acc = -0.01;
            flag2 = -1;
        }
        // if(ball1.position.x >=1 && ball1.position.x <=-1 && ball1.position.y >= -2.2 ){
        //     flag2 = 0;
        // }
    }

    if(ball1.position.x <=1 && ball1.position.x >=0 && ball1.position.y < -1.7){
        ball1.position.x -=0.02;
    }

    if(ball1.position.x >=-1 && ball1.position.x <=0 && ball1.position.y < -1.7){
        ball1.position.x +=0.02;
    }

    if(ball1.position.x >= 1 && ball1.position.x <= -1 && ball1.position.y <= 1.8){
        ball1.position.y = -1.8;
    }

    // if(ball1.position.y < -1.6 ){
    //     flag = 0;
    //     ball1.position.y = -1.8;
    // }

    if(ball1.position.y >= -1 && ball1.position.y <= -0.7 && ball1.position.x <=3 && ball1.position.x >= 2){
        ball1.speedy = -0.3;
        ball1.acc = -0.01;
    }
}
float cmp(float a,float b,float ep=0.005){
    return (fabs(a-b)<ep);
}
void tick_elements() {
    ball1.tick();
    SPI1.tick();
    SPI2.tick();
    if(cmp(ball1.position.x,0.0) and ball1.position.y<=-2.75){
        // printf("hi\n");
        // ball1.speedy = -0.3;
        // ball1.acc = -0.01;
        // ball1.position.y=-2.75;
        flag=0;
    }
    for(int i=0;i<10;i++){
        Villans[i].position.x+=Villans[i].speed;
    }
    // if (detect_collision(ball1.bounding_box(), ball2.bounding_box())) {
    //     ball1.speed = -ball1.speed;
    //     ball2.speed = -ball2.speed;
    // }

    if(flag = -1){
        ball1.speedy -= ball1.acc;
        // ball1.position.y = 
    }

    // if(flag == -1){
    //     ball1.speedy -= ball1.acc;
    // }

    if(ball1.position.y <= -1.75 ){
        ball1.position.y=-1.75;
        flag = 0;
        // ball1.position.y = -1.8;
        ball1.speedy = 0;
        ball1.acc = 0;
    }

    for(int j=0;j<10;j++){
        if(Villans[j].position.x > 5){
            Villans[j].position.x = -5;
        }
    }
}

float random(float a,float b){
    float r= ((float)rand()/(float)(RAND_MAX));
    float diff = b-a;
    r*=diff;
    return a+r;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    
    ball1       = Ball(1.5, -1.75,0.25, COLOR_RED,0);
    // ball2       = Ball(-2, 0, COLOR_RED);
    // ball2.speed = -ball2.speed;
    // SPI1.speed  = -SPI2.speed;
    ground1     = Ground1(-4,-4, COLOR_GROUND1);
    ground2     = Ground2(-4,-4, COLOR_GROUND2);
    SEMI1       = semi_circle(1,0,-2,COLOR_semi_circle);
    SEMI2       = semi_circle(0.5,2.55,-1,COLOR_trap);
    TRAP1       = trap(3,-2, COLOR_trap);
    TRAP2       = trap(2,-2, COLOR_trap);
    SPI1        = spikes(-2,-2,-0.01,COLOR_spikes);
    SPI2        = spikes(1.2,-2,0.01,COLOR_spikes);
    rec1        = Rectangle(-1.6,3.2,0.8,0.2,COLOR_RED);
    rec2        = Rectangle(-1.6,1.8,0.8,0.2,COLOR_RED);
    rec3        = Rectangle(-0.8,3.2,0.2,0.2,COLOR_GREY);
    rec4        = Rectangle(-0.8,1.8,0.2,0.2,COLOR_GREY);


    if(SPI2.position.x >= 2){
        SPI2.set_speed(-0.01);
    }
    if(SPI2.position.x <= 1.2){
        SPI2.set_speed(0.01);
    }


    MC1         = semi_circle(0.8,-1,2,COLOR_RED);
    MC1.rotation = -90;
    MC11         = semi_circle(0.6,-1,2,COLOR_BACKGROUND);
    MC11.rotation = -90;
    level = Score();
    level.update(1);
    level.x=0;
    color_t colored[7]={COLOR_VIOLET,COLOR_INDIGO,COLOR_BLUE,COLOR_GREEN,COLOR_YELLOW,COLOR_ORANGE,COLOR_RED};
    for(int j =0; j<10;j++){
        float x1=random(-5,-3);
        float y1=random(0,3);
        float r1=random(0.3,0.6);
        float sp=random(0.01,0.09);
        int color = rand()%7;
        Villans[j] = Ball(x1,y1,r1,colored[color],1);
        Villans[j].speed = sp;
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    score.x=4;
    
    // level.update(1);
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            for(int i=0;i<10;i++){
                if(detect_collision(ball1.bounding_box(),Villans[i].bounding_box()) and ball1.speedy>0){
                    flag=0;
                    ball1.speedy=-0.25;
                    Villans[i].position.x = -5.0;
                    score1+=100;
                    score.add(100);
                }
            }
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
