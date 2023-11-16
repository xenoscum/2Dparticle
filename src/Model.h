#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstddef>
#include <cmath>
#include <fstream>
#include <string>

class Model{
public:
    using cellID_type = uint32_t;

    enum dimension { oneDimensional, twoDimensional };

    Model(int N_, double tau_, double (*densityInit_) (double, double), dimension dim, double rad);

    ~Model();

private:
    class Particle;
    std::vector<Particle> particles;

    size_t N;
    static double tau;
    static double gridSize;
    double (*densityInit) (double, double);

    std::ofstream outStream;
    std::string outFileName = "..\\..\\data.txt";

    const double VELMULT = 0.1;

    static cellID_type cellHash(double, double);

    double velocityAbs(double dens) { return VELMULT * dens; }

public:
    void runFor(int iterations);
    
    void setTau(double tau_) { tau = tau_; }
    void setDensityInit(double (* const densityInit_) (double, double)) { densityInit = densityInit_; }
};