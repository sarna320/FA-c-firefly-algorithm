#include <iostream>
#include <cmath>
#include <vector>
#include <random>

using namespace std;

class Firefly
{
public:
    vector<double> x;
    double B; // attractiveness of fifirefly
    double I; // intensity of fifirefly
    Firefly();
    ~Firefly();
};

double f_x(vector<double> x_);

void fireflyInit(int m, int n, Firefly firefly[], double x_r, double x_l);

void fireflyPrint(int m, Firefly firefly[]);

double uRandom(double a);

int main()
{
    int m = 20;         // number of fireflies
    int n = 2;          // dimension of the problem
    double x_l = -40.0; // lobwer bound
    double x_r = 40.0;  // uper bound
    Firefly firefly[m]; // fireflies
    double a = 0.7;     // alfa, parameter of algorithm
    double u=uRandom(a); //generate radom u with uniform distribution
    // initialization fireflies
    fireflyInit(m, n, firefly, x_r, x_l);

    // print all fireflies
    // fireflyPrint(m, firefly);

    return 0;
}

void fireflyPrint(int m, Firefly firefly[])
{
    for (size_t i = 0; i < m; i++)
    {
        cout << "Firefly " << i + 1 << endl;
        cout << "attractiveness B=" << firefly[i].B << endl;
        cout << "intensity I=" << firefly[i].B << endl;
        for (double x : firefly[i].x)
        {
            cout << "x"
                 << "=" << x << endl;
        }
        cout << endl;
    }
}

void fireflyInit(int m, int n, Firefly firefly[], double x_r, double x_l)
{
    // initialization fireflies
    for (size_t i = 0; i < m; i++)
    {
        firefly[i].B = 1.0;
        double temp;
        for (size_t j = 0; j < n; j++)
        {
            temp = (rand() / (double)RAND_MAX) * (x_r - x_l) + x_l;
            firefly[i].x.push_back(temp);
        }
        firefly[i].I = 1 / f_x(firefly[i].x);
    }
}

double f_x(vector<double> x_)
{
    double sum = 0.0;     // sum of f_x
    double product = 1.0; // product of f_x
    double f_x = 0.0;
    double counter = 1.0;
    for (double x : x_)
    {
        sum += pow(x, 2);
        product *= cos(x / counter);
        counter++;
    }
    return 1 / 40 * sum + 1 - product;
}

double uRandom(double a)
{
    std::default_random_engine generator;                          // generator
    std::uniform_real_distribution<double> distribution(0.0, 1.0); // number genereted with uniform_real_distribution
    double E = distribution(generator);                            // epsilon parameter
    return a * (E - 0.5);
}

Firefly::Firefly()
{
}

Firefly::~Firefly()
{
}
