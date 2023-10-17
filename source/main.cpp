#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Firefly
{
public:
    int n;
    vector<double> x;
    double B; // attractiveness of fifirefly
    double I; // intensity of fifirefly
    Firefly()
    {
    }
    ~Firefly()
    {
    }
};

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

int main()
{
    int m = 10; // number of fireflies
    int n = 10; // dimension of the problem
    double x_l = -40.0;
    double x_r = 40.0;
    Firefly firefly[m];
    for (size_t i = 0; i < m; i++)
    {
        firefly[i].B = 1.0;
        double temp;
        for (size_t j = 0; j < n; j++)
        {
            temp = (rand() / (double)RAND_MAX) * (x_r - x_l) + x_l;
            firefly[i].x.push_back(temp);
        }
        // cout<<endl;

        firefly[i].I = 1 / f_x(firefly[i].x);
    }
        for (size_t i = 0; i < m; i++)
    {
        cout << "Firefly " << i << endl;
        cout << "attractiveness B=" << firefly[i].B << endl;
        cout << "intensity I=" << firefly[i].B << endl;
        for (double x : firefly[i].x)
        {
            cout << "x"
                 << "=" << x << endl;
        }
        cout << endl;
    }

    return 0;
}
