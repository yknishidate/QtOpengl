#ifndef SPHEREMODEL_H
#define SPHEREMODEL_H
#include "model.h"

class SphereModel :public Model
{
public:
    SphereModel(float r, int st, int sl);
    void change(float r, int st, int sl);

    void setRadius(float r){rad = r;}
    void setStacks(int s){stacks = s;}
    void setSlices(int s){slices = s;}

    float getRadius(){return rad;}
    int getStacks(){return stacks;}
    int getSlices(){return slices;}

private:
    float rad = 2.0;
    int stacks = 32;
    int slices = 64;
};

#endif // SPHEREMODEL_H
