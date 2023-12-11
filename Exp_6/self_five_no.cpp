/*
Data Mining Assignment 6:
- Rutuja Khilare
*/


#include<bits/stdc++.h>
using namespace std;

double calculate_median(vector<int> data)
{
    int n= data.size();
    if( n%2==0)
    {
        return (data[n/2 -1] + data[n/2 ]) / 2.0;
    }
    return data[n/2];
}

int calculate_quartile_1(vector<int> data)
{
    vector<int> part1;
    for(int i=0; i<(data.size()/2); i++)
    {
        part1.push_back(data[i]);
    }
    return calculate_median(part1);
}

int calculate_quartile_3(vector<int> data)
{
    int n= data.size();
    vector<int> part2;
    //dry run this you'll get it!!
    if( n%2 == 0)
    {
        for(int i=(n/2) ; i<n; i++)
        {
            part2.push_back(data[i]);
        }
    }
    else if( n%2 !=0 )
    {
        for(int i=(n/2 + 1); i<n ; i++)
        {
            part2.push_back(data[i]);
        }
    }
    return calculate_median(part2);
}



int main()
{
    ifstream inputfile("exp_6_inputfile.csv");
    ofstream outputfile("exp_6_outputfile.csv");

    if( !inputfile.is_open())
    {
        cerr<<"Error in getting data from file"<<endl;
        return -1;
    }

    vector<int> data;
    int value;
    while(inputfile >> value)
    {
        data.push_back(value);
    }

    int n= data.size();

    sort(data.begin(), data.end());

    
    //Getting the results displayed

    cout<<"Minimum value of the dataset"<<endl;
    cout<<data[0]<<endl;
    cout<<"First Quartile of the dataset: Q1"<<endl;
    cout<<calculate_quartile_1(data)<<endl;
    cout<<"Median value of the dataset: Q2"<<endl;
    cout<<calculate_median(data)<<endl;
    cout<<"Second Quartile of the dataset: Q3"<<endl;
    cout<<calculate_quartile_3(data)<<endl;
    cout<<"Maximum value of the dataset"<<endl;
    cout<<data[n-1]<<endl;

    //writing the results in outputfile
    outputfile<<"Minimum value of the dataset"<<endl;
    outputfile<<data[0]<<endl;
    outputfile<<"First Quartile of the dataset: Q1"<<endl;
    outputfile<<calculate_quartile_1(data)<<endl;
    outputfile<<"Median value of the dataset: Q2"<<endl;
    outputfile<<calculate_median(data)<<endl;
    outputfile<<"Second Quartile of the dataset: Q3"<<endl;
    outputfile<<calculate_quartile_3(data)<<endl;
    outputfile<<"Maximum value of the dataset"<<endl;
    outputfile<<data[n-1]<<endl;


    return  0;
}