#include <unordered_map>
#include <unordered_set>

#include "Particle.h"


std::unordered_map<Model::cellID_type, std::unordered_set<Model::Particle::particleID_type>> Model::Particle::cells; 


Model::Particle::Particle(double x_, double y_, double radius_, double density_,
            std::pair<double, double> velocity_):
            x(x_), y(y_), radius(radius_), density(density_), velocity(velocity_) {};


void Model::Particle::updateCell() {
    auto it = cells.find(cell);
    
    if (it != cells.end()) {
        it->second.erase(id);
    }

    cell = cellHash(x / gridSize, y / gridSize);

    cells[cell].insert(id);

    if (it != cells.end()) {
        if(it->second.empty()) {
            cells.erase(cell);
        }
    }
}

double Model::Particle::impactParameter(Model::Particle::particleID_type particle) {
    return 0;
}

void Model::Particle::writeDrawingData(std::ofstream& out) const {
    out << x << ' ' << y << ' ' << radius << ' ' << density << '\n';
}

void Model::Particle::predictor() {
    x += tau * velocity.first;
    y += tau * velocity.second;

    updateCell();
}

void Model::Particle::corrector() {

}