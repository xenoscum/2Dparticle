#define LowerDens 4.0
#define UpperDens 6.0

double densInit1(double x, double y) {
    double f = -(x - 5) * (x - 5) + UpperDens;
    return f > LowerDens ? f : LowerDens;
}

double densInitParaboloid(double x, double y) {
    double x0 = 6;
    double y0 = 6;
    double f = -0.1 * ((x - x0) * (x - x0) + (y - y0) * (y - y0)) + UpperDens;
    return f > LowerDens ? f : LowerDens;
}
