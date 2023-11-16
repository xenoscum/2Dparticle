#pragma once

#include <utility>
#include "Model.h"

class Model::Particle{
public:
    using particleID_type = size_t;

private:
    static std::unordered_map<cellID_type, std::unordered_set<particleID_type>> cells;
    //cell number : set of partcle ids
    
    inline static int idCounter = 0;
    particleID_type id;
    cellID_type cell;

    double x;
    double y;
    double radius;
    double density;
    std::pair<double, double> velocity;

    void updateCell();

    double impactParameter(particleID_type);

    friend Model::Model(int, double, double (*) (double, double), dimension, double);

public:
    Particle(double, double, double, double, std::pair<double, double>);

    void writeDrawingData(std::ofstream&) const;

    void predictor();
    void corrector();
};
