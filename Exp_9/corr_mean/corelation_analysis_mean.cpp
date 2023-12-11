#include <bits/stdc++.h>
using namespace std;

// Function to calculate mean
double mean(vector<double> data, int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; ++i)
    {
        sum += data[i];
    }
    return sum / n;
}

// Function to calculate standard deviation
double standardDeviation(vector<double> data, int n, int mean)
{
    double variance = 0.0;
    for (int i = 0; i < n; ++i)
    {
        variance += (data[i] - mean) * (data[i] - mean);
    }
    return sqrt(variance / (n));
}

// Function to calculate correlation using formula
double calculateCorrelation(vector<double> x, vector<double> y, int n)
{
    double meanX = mean(x, n);
    double meanY = mean(y, n);
    double sdX = standardDeviation(x, n, meanX);
    double sdY = standardDeviation(y, n, meanY);

    double covariance = 0.0;
    for (int i = 0; i < n; ++i)
    {
        covariance += (x[i] - meanX) * (y[i] - meanY);
    }

    return  (covariance / ((n - 1) * sdX * sdY) );
}

int main()
{
    vector<double> x;
    vector<double> y;

    ifstream input("corr_anal_mean.csv");
    string line;
    int line_no=0;
    while (getline(input, line))
    {
        if( line_no==0)
        {
            line_no++;
            continue;
        }

        //skip first line then extract the input lines
        stringstream str(line);

        string x_val, y_val;
        getline(str, x_val, ',');
        getline(str, y_val);

        x.push_back(stoi(x_val));
        y.push_back(stoi(y_val));


    }

    int dataSize = x.size();

    // Calculate the correlation coefficient
    double correlation = calculateCorrelation(x, y, dataSize);

    // Output the correlation coefficient
    cout << "Correlation Coefficient: " << correlation << std::endl;

    return 0;
}
