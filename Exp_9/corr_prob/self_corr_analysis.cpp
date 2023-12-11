#include<bits/stdc++.h>
using namespace std;

double correlation(vector<int> d1, vector<int> d2)
{
    double pos1=0, pos2=0, pos1_and_pos2=0, ans=0;

    int n= d1.size();
    for(int i=0; i<n; i++)
    {
        if( d1[i]==1 && d2[i]==1)
        pos1_and_pos2++;
        if( d1[i]==1)
        pos1++;
        if(d2[i]==1)
        pos2++;
    }

    pos1_and_pos2 /= n;
    pos1/=n;
    pos2/=n;

    ans= (pos1_and_pos2/(pos1*pos2) );

    return ans;
}


int main()
{   

    ifstream inputfile("exp_9_inputfile.csv", ios::in);
    
    int line_number=0;
    string line, count;
    vector<vector<int>>dataset;

    while(getline(inputfile, line))
    {
        vector<int> v;
        if(line_number==0)
        {
            line_number++;
            continue;
        }
        stringstream str(line);
        string s="";
        while(getline(str, s, ','))
        {
            v.push_back(stoi(s)) ;
        }
        dataset.push_back(v);
    }

    for(auto vect: dataset)
    {
        for(int i=0; i<vect.size(); i++)
        {
            cout<<vect[i]<<" ";
        }
        cout<<endl;
    }
    
    
    ofstream outputfile("exp_9_outputfile.csv", ios::out);


    for(int i=0; i<dataset.size()-1; i++)
    {
        double val=0;
        for(int j=i+1; j<dataset.size(); j++)
        {
            val= correlation(dataset[i], dataset[j]) ;
            if( val>1)
            outputfile<<"vector "<<i+1<<" and vector "<<j+1<<" are positively correlated: "<<val<<endl;
            else if( val<1)
            outputfile<<"vector "<<i+1<<" and vector "<<j+1<<" are negatively correlated: "<<val<<endl;
            else if( val==1)
            outputfile<<"vector "<<i+1<<" and vector "<<j+1<<" are independent of each other: "<<val<<endl;
        }
    }
    
    
    return 0;
}