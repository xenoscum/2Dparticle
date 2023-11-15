#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstddef>
#include <cmath>
#include <fstream>
#include <string>


class Model{
    std::ofstream out;
    std::string outFileName = "data.txt";

    size_t N;
    double tau;
    double (* const densityInit) (double, double);

    const double velMult = 0.1;

    class Particle{
        inline static int idCounter = 0;

        double x;
        double y;
        double radius;
        double density;
        std::pair<double, double> velocity;
        int cell;
        size_t id;

    public:
        Particle(): id(idCounter++) {};

        Particle(double x_, double y_, double radius_, double density_,
                std::pair<double, double> velocity_): id(idCounter++) {
            x = x_;
            y = y_;
            radius = radius_;
            density = density_;
            velocity = velocity_;
        }

        void writeDrawingData(std::ofstream& out) {
            out << x << ' ' << y << ' ' << radius << ' ' << density << ' ';
        }
    };

    std::vector<Particle> particles;
    std::unordered_map<int, std::unordered_set<size_t>> cells;

    double velocity(double dens) {
        return velMult * dens;
    }

public:
    enum dimension { oneDimensional, twoDimensional };
    
    Model(): N(), densityInit() {};

    Model(int N_, double tau_, double (*densityInit_) (double, double), dimension dim, double rad):
            N(N_), densityInit(densityInit_){

        out.open(outFileName);
        
        tau = tau_;
        particles.reserve(N);

        double dist = rad * M_SQRTPI;
        if (dim == oneDimensional) {
            for (size_t i = 0; i < N; ++i) {
                double x = dist * i;
                double dens = densityInit(x, 0);
                
                particles.push_back(Particle(x, 0, rad, dens, std::pair<double, double>(velocity(dens), 0)));
            }
        }
        else if (dim == twoDimensional){
            size_t n = static_cast<int>(std::sqrt(N));
            N = n * n;

            for (size_t i = 0; i < n; ++i) {
                for(size_t j = 0; j < n; ++j) {
                    double x = dist * i;
                    double y = dist * j;
                    double dens = densityInit(x, y);

                    particles.push_back(Particle(x, y, rad, dens,
                            std::pair<double, double>(velocity(dens) * M_SQRT2 / 2, velocity(dens) * M_SQRT2 / 2)));
                }
            }
        }

        for (size_t i = 0; i < N; ++i) {
            particles[i].writeDrawingData(out);
        }
        out << '\n';

    }

    ~Model() {
        out.close();
    }
};