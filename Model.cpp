#include <unordered_map>
#include <vector>


class Model{
    class Particle;
    
    const int N;
    const double tau;
    std::vector<Particle> particles;

public:
    Model(): N(0), tau(0) {};

    Model(int N_, double tau_): N(N_), tau(tau_) {
        particles.resize(N);
    }

    
};


class Model::Particle{
    double x;
    double y;
    double radius;
    double density;
    std::pair<double, double> velocity;
    int cell;
    int id;

    inline static int counter = 0;

public:
    Particle() {};

    Particle(double x_, double y_, double radius_, double density_, std::pair<double, double> velocity_): id(++counter) {
        x = x_;
        y = y_;
        radius = radius_;
        density = density_;
        velocity = velocity_;
    }

    void move() {
        x += 1;
    }
};