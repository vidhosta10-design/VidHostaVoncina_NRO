#include <iostream>
#include <iomanip>
#include <cmath>
const double PI = 3.14159265358979323846;

using namespace std;

double calctan(double* x, int* N_steps)
{
    double xv = *x;
    int N = *N_steps;

    if (N <= 0) return 0.0;

    double term = xv;       
    double sum = term;

    for (int n = 1; n < N; ++n)
    {
        term *= (-xv * xv) * (2.0 * n - 1.0) / (2.0 * n + 1.0);
        sum += term;
    }

    return sum;
}

double f(double x, int N_steps)
{
    double arg = x / 2.0;          
    return exp(3.0 * x) * calctan(&arg, &N_steps);
}

int main()
{
    int n;        
    int N_steps;  

    cout << "Vnesi stevilo trapezov n: ";
    cin >> n;
    cout << "Vnesi stevilo clenov Taylorjeve vrste N_steps: ";
    cin >> N_steps;

    if (n <= 0 || N_steps <= 0)
    {
        cout << "Napaka: n in N_steps morata biti pozitivna.\n";
        return 1;
    }

    const double a = 0.0;
    const double b = PI / 4.0;
    const double dx = (b - a) / n;

    double sum_mid = 0.0;
    for (int i = 1; i <= n - 1; ++i)
    {
        double x = a + i * dx;
        sum_mid += f(x, N_steps);
    }

    double I = (dx / 2.0) * (f(a, N_steps) + 2.0 * sum_mid + f(b, N_steps));

    cout << fixed << setprecision(12);
    cout << "\nPriblizek integrala = " << I << "\n";

    return 0;
}
