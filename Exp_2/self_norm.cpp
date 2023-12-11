/*
Normalization of Data:
*/
#include<bits/stdc++.h>
using namespace std;

vector<double> min_max_normalization(const vector<double> &data, double new_min, double new_max)
{
    vector<double> res;
    double min_old=DBL_MAX, max_old= DBL_MIN;
    for(int i=0; i< data.size(); i++)
    {
        min_old= min(min_old, data[i]);
        max_old= max(max_old, data[i]);
    }

    for(int i=0; i<data.size(); i++)
    {
        double normalized_val = ( ( (data[i] - min_old)*(new_max-new_min) ) / (max_old - min_old)) + (new_min); 
        res.push_back(normalized_val);
    }

    return res;
}

vector<double> z_score_normalization(const vector<double> &data)
{
    // z_score=  (x-x_bar) /standard_deviation
    double mean=0,variance=0, standard_deviation=0;
    vector<double> res;
    for(int i=0; i<data.size(); i++)
    {
        mean+= data[i];
    }
    mean = (mean)/data.size();

    for(int i=0; i<data.size(); i++)
    {
        variance += (data[i] - mean)*(data[i]-mean);
    }
    variance/= data.size();

    standard_deviation = sqrt(variance);
    for(int i=0; i<data.size(); i++)
    {
        double normalized_val = (data[i] - mean) /standard_deviation;
        res.push_back(normalized_val);
    }    
    return res;
}

vector<double> decimal_scaling_norm(const vector<double> &data)
{
    vector<double> res;
    double max_no=0;
    for(int i=0; i<data.size(); i++)
    {
        max_no = max(max_no, data[i]);
    }
    int j = log10(max_no) + 1;
    for(int i=0; i<data.size(); i++)
    {
        double normalized_val = data[i] / (pow(10, j));
        res.push_back(normalized_val);
    }


    return res;

}


int main()
{
    //object of class ifstream to read input from inputfile
    ifstream inputfile("input.txt");
    //object of class ofstream to write res in outputfile
    ofstream outputfile("output.txt");

    vector<double> data;
    double value;

    while( inputfile>> value)
    {
        data.push_back(value);
    }
    cout<<"Performing Min-Max Normalization"<<endl;
    cout<<"Enter the values of new_min and new_max of new range to which the data is to be normalized"<<endl;
    double new_min=0, new_max=0;
    cin>>new_min>>new_max;
    vector<double> min_max_norm = min_max_normalization(data, new_min, new_max);
    outputfile<<"Min-Max Normalization"<<endl;
    for(double it: min_max_norm)
    {
        outputfile<<it<<endl;
    }

    
    cout<<"Performing Z-Score Normalization"<<endl;
    vector<double> z_score_norm = z_score_normalization(data);
    outputfile<<"Z-Score Normalization"<<endl;
    for(double it: z_score_norm)
    {
        outputfile<<it<<endl;
    }

    cout<<"Performing Normalization by decimal scaling"<<endl;
    vector<double> decimal_scaling = decimal_scaling_norm(data);
    outputfile<<"Decimal- Scaling Normalization"<<endl;
    for(double it: decimal_scaling)
    {
        outputfile<<it<<endl;
    }

    return 0;
}