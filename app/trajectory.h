#ifndef Trajectory_H
#define Trajectory_H

#include <GL/glu.h>

class Trajectory
{
private:
    float v0_;
    int axe_ = 180;
    GLuint trajectory_;

public:
    Trajectory();
    GLuint draw();
    void set_v0(float v);
    void set_axe(int a);
};

#endif // Trajectory_H
