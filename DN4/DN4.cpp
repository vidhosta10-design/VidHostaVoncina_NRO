#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

// Funkcija za izračun povprečne vrednosti vektorja
double mean(const vector<double>& v)
{
    double sum = 0.0;
    for (double x : v)
        sum += x;
    return sum / v.size();
}

int main()
{
    // Branje matrike A in vektorja b

    vector<vector<double>> A;
    vector<double> b;

    string filename = "datoteka_A_b.txt";
    ifstream infile(filename);

    // Prva vrstica: "A: n=256"
    string first_line;
    getline(infile, first_line);
    replace(first_line.begin(), first_line.end(), '=', ' ');

    istringstream iss(first_line);
    string tmp1, tmp2;
    int n;
    iss >> tmp1 >> tmp2 >> n;

    cout << "Velikost matrike A: " << n << " x " << n << endl;

    // Branje matrike A
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(infile, line);
        replace(line.begin(), line.end(), ';', ' ');

        istringstream iss_row(line);
        vector<double> row(n);

        for (int j = 0; j < n; j++)
            iss_row >> row[j];

        A.push_back(row);
    }

    // Preskočimo prazno vrstico
    string empty_line;
    getline(infile, empty_line);

    // Vrstica: "b: n->256"
    string line_b;
    getline(infile, line_b);
    replace(line_b.begin(), line_b.end(), '>', ' ');

    istringstream iss_b(line_b);
    int n_b;
    iss_b >> tmp1 >> tmp2 >> n_b;

    cout << "Velikost vektorja b: " << n_b << endl;

    // Branje vektorja b
    for (int i = 0; i < n_b; i++)
    {
        string val;
        getline(infile, val);
        b.push_back(stod(val));
    }

    infile.close();

    // Gauss–Seidel iterativna metoda

    // Začetni približek
    vector<double> T(n_b, 100.0);

    auto start_time = chrono::high_resolution_clock::now();

    for (int iitt = 0; iitt < 2000; iitt++)
    {
        for (int jj = 0; jj < n_b; jj++)
        {
            double d = b[jj];

            for (int ii = 0; ii < n_b; ii++)
            {
                if (ii != jj)
                {

                    // uporabljamo sproti posodobljen vektor T
                    d -= A[jj][ii] * T[ii];
                }
            }

            T[jj] = d / A[jj][jj];
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_duration = end_time - start_time;

    cout << "Cas izvajanja Gauss-Seidel metode: "
        << time_duration.count() << " s" << endl;

    // Izpis rezultatov

    double max_T = T[0];
    for (double x : T)
        if (x > max_T)
            max_T = x;

    cout << "Maksimalna temperatura: " << max_T << " °C" << endl;


    // Gauss–Seidelova metoda ni primerna za paralelizacijo z OpenMP, saj se pri izračunu posameznega elementa T[jj] uporabljajo že posodobljene vrednosti T[0 … jj−1] iz iste iteracije. 
    // Če bi se računanje izvajalo vzporedno, bi se porušil predpisani zaporedni vrstni red posodabljanja, kar bi vodilo do nepravilnih oziroma netočnih rezultatov.

    return 0;
}