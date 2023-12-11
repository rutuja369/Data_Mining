#include<bits/stdc++.h>
using namespace std;

//Method 1: Equifreq
vector<vector<int>> equifreq(vector<int> data, int bins)
{
    int bin_freq=0;
    if( data.size() % bins == 0)
    {
        bin_freq= (data.size()/(bins));
    }
    else
    {
        bin_freq= (data.size()/(bins)) + 1;
    }

    vector<vector<int>> bins_vect;
    for(int i=0; i<bins; i++)
    {
        vector<int> bin ;
        for(int j=(i*bin_freq); j<(i+1)*bin_freq; j++)
        {
            if( j>=data.size())
            break;
            bin.push_back(data[j]);
        }
        if( bin.size()!= 0)
        bins_vect.push_back(bin);
        else
        bins_vect.push_back({-1}); //-1 -> indicates empty bins
    }
    return bins_vect;
}

//Method 2: Equiwidth
vector<vector<int>> equiwidth(vector<int> data, int bins)
{
    int max_val =INT_MIN, min_val= INT_MAX;
    vector<vector<int>> bins_vect;

    for(int i=0; i<data.size(); i++)
    {
        max_val = max(max_val, data[i]);
        min_val = min(min_val , data[i]);
    }
    int width = (max_val - min_val)/bins;
    cout<<min_val<<endl;
    //creating a vector to store the threshold of very bin
    vector<int>bin_threshold;

    for(int i=0;i<=bins; i++)
    {
        bin_threshold.push_back(min_val + (i*width));
    }

    //now create bins
    for(int i=0; i<bins; i++)
    {
        vector<int> bin;
        for(int j=0; j<data.size(); j++)
        {
            if( data[j]>= bin_threshold[i] && data[j]<bin_threshold[i+1])
            bin.push_back(data[j]);
            
        }
        bins_vect.push_back(bin);
    }
        bins_vect[bins-1].push_back(data[data.size()-1]);

    return bins_vect;
    
}

void writeCSV(string filename, vector<vector<int>> bins_vect)
{
    ofstream outputfile(filename);
    for(int i=0; i<bins_vect.size(); i++)
    {
        outputfile<<" Bin "<<(i+1)<<endl;
        vector<int> bin = bins_vect[i];
        for(int num: bin)
        {
            outputfile<<num<<" , ";
        }
        outputfile<<endl;
    }
    outputfile.close();
}

int main()
{
    //taking input from file
    ifstream inputfile("exp_3_inputfile.csv");
    vector<int> data;
    int value=0;
    while(inputfile>>value)
    {
        data.push_back(value);
    } 
    sort(data.begin(), data.end());

    int method=0;
    cout<<"Select method for binning"<<endl;
    cout<<"1. Equifrequency Binning"<<endl;
    cout<<"2. Equiwidth Binning"<<endl;

    cout<<"Enter the method"<<endl;
    cin>>method;

    int bins=0;
    cout<<"Enter no. of bins"<<endl;
    cin>>bins;

    if( method == 1)
    {
        vector<vector<int>> freqbins = equifreq(data, bins);
        writeCSV("output_equifreq.csv", freqbins);
    }
    else if(method==2)
    {
        vector<vector<int>> widthbins= equiwidth(data, bins);
        writeCSV("output_equiwidth.csv", widthbins);
    }
    else 
    cout<<"Invalid method"<<endl;


    return 0;
}