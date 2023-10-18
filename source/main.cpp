#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <array>

using namespace std;

class Firefly
{
public:
    vector<double> x;
    double B; // attractiveness of fifirefly
    double I; // intensity of fifirefly
    double f_x;
    Firefly();
    ~Firefly();
};

double f_x(vector<double> x_);

void fireflyInit(int m, int n, Firefly firefly[], double x_r, double x_l);

void fireflyPrint(int m, Firefly firefly[]);

double uRandom(double a);

int main()
{
    int m = 50;         // number of fireflies
    int n = 2;          // dimension of the problem
    double x_l = -40.0; // lobwer bound
    double x_r = 40.0;  // uper bound
    Firefly firefly[m]; // fireflies
    double a = 0.6;     // alfa, parameter of algorithm
 
    // initialization population of fireflies
    fireflyInit(m, n, firefly, x_r, x_l);
    double r = 0.0;        // distance between firefly
    double B_0 = 1;      // Beta_0 parameter
    double Y = 6;        // Gammna parameter
    double u = uRandom(a); // generate random u with uniform distribution
    int t = 1;
    double print;
    int MaxGeneration = 10000;
    double best = 0.0;
    while (t < MaxGeneration)
    {
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < m; j++)
            {
                for (size_t k = 0; k < n; k++)
                {
                    r += (firefly[i].x[k] - firefly[j].x[k]) * (firefly[i].x[k] - firefly[j].x[k]);
                }
                r = sqrt(r);

                if (firefly[j].I > firefly[i].I)
                {
                    firefly[i].B = B_0 * exp(-Y * pow(r, 2));

                    for (size_t k = 0; k < n; k++)
                    {
                        u = uRandom(a);
                        firefly[i].x[k] = firefly[i].x[k] + firefly[i].B * (firefly[j].x[k] - firefly[i].x[k]) + u;
                    }
                }
            }
            
            // checking boundries
            for (size_t l = 0; l < n; l++)
            {
                if (firefly[i].x[l] < x_l)
                {
                    firefly[i].x[l] = x_l;
                }
                if (firefly[i].x[l] > x_r)
                {
                    firefly[i].x[l] = x_r;
                }
            }

            // new solutions and intensisty
            firefly[i].f_x = f_x(firefly[i].x);
            firefly[i].I = 1.0 / firefly[i].f_x;
        }

        // search for best
        int best_index = 0;

        for (size_t i = 0; i < m; i++)
        {
            if (best < firefly[i].f_x)
            {
                best = firefly[i].f_x;
                best_index = i;
            }
        }
        for (size_t i = 0; i < n; i++)
        {
            u = uRandom(a);
            firefly[best_index].x[i] = firefly[best_index].x[i]+u;
        }

        t++;
        cout << best << endl;
    }

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
        firefly[i].f_x = f_x(firefly[i].x);
        firefly[i].I = 1 / firefly[i].f_x;
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
