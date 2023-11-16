#include "Model.h"
#include "Particle.h"

Model::Model(int N_, double tau_, double (*densityInit_) (double, double), dimension dim, double rad):
        N(N_), densityInit(densityInit_){

    outStream.open(outFileName);
    outStream << N << '\n';
    
    tau = tau_;
    particles.reserve(N);

    gridSize = 2 * rad;

    double dist = rad * M_SQRTPI;
    if (dim == oneDimensional) {
        for (size_t i = 0; i < N; ++i) {
            double x = dist * i;
            double dens = densityInit(x, 0);
            
            particles.push_back(Particle(x, 0, rad, dens, std::pair<double, double>(velocityAbs(dens), 0)));
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
                        std::pair<double, double>(velocityAbs(dens) * M_SQRT2 / 2, velocityAbs(dens) * M_SQRT2 / 2)));
            }
        }
    }

    for (size_t i = 0; i < N; ++i) {
        particles[i].writeDrawingData(outStream);
    }
}


Model::~Model() {
    outStream.close();
}


Model::cellID_type Model::cellHash(double normalizedX, double normalizedY) {
    uint16_t cellX = static_cast<uint16_t>(normalizedX);
    uint16_t cellY = static_cast<uint16_t>(normalizedX);

    return (static_cast<cellID_type>(cellX) << 16) | cellY;
}

void Model::runFor(int iterations) {
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < N; ++i) {
            particles[i].predictor(tau);
        }

        for (size_t i = 0; i < N; ++i) {
            particles[i].corrector();
        }

        for (size_t i = 0; i < N; ++i) {
            particles[i].writeDrawingData(outStream);
        }
    }
}
