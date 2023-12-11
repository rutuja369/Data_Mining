#include<bits/stdc++.h>
using namespace std;

double computeMean(vector<double> vect, int n)
{
    double sum=0;
    for(int i=0; i<n; i++)
    {
        sum+= (vect[i]);
    }
    return (sum / n);
}

double computeSD(vector<double> vect, double mean , int n)
{
    double sd=0, variance=0;
    for(int i=0; i<n; i++)
    {
        variance += ( (vect[i] - mean)*(vect[i] - mean) );
    }

    sd = sqrt(variance/ (n-1) );

    return sd;
}

double computeCorrCoeff(vector<double> a_vals, vector<double> b_vals, int n)
{

    double mean_a = computeMean(a_vals, n);
    double mean_b = computeMean(b_vals, n);

    double sd_a = computeSD(a_vals, mean_a, n);
    double sd_b = computeSD(b_vals, mean_b, n);

    double covariance=0;
   
    for(int i=0; i<n; i++)
    {
        covariance += (a_vals[i] - mean_a)*(b_vals[i] - mean_b) ;
    }

    covariance/= ( double(n-1)*sd_a*sd_b );

    return covariance;

}
int main()
{
    ifstream inputfile("corr_anal_mean.csv");

    vector<double>a_vals;
    vector<double>b_vals;

    string line;

    int line_no=0;

    while( getline(inputfile, line))
    {
        if( line_no == 0)
        {
            line_no++;
            continue;
        }

        stringstream str(line);
        string a, b;
        getline(str, a, ',');
        getline(str, b , ',');

        a_vals.push_back(stoi(a));
        b_vals.push_back(stoi(b));
    }

    double corr_coeff=0;
    int n= a_vals.size();
    corr_coeff = computeCorrCoeff(a_vals, b_vals, n);

    cout<<"Correlation coefficient is "<<corr_coeff<<endl;

    return 0;
}
