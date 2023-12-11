#include<bits/stdc++.h>
using namespace std;


double distance(double x1, double y1, int x2, int y2)
{
    return sqrt(((float)x2 - x1) * ((float)x2 - x1) + ((float)y2 - y1) * ((float)y2 - y1));
}


int main()
{
    vector<pair<int, int>> dataset;
    string line, point, x, y;
    int line_no=0, x_coor=0, y_coor=0;

    ifstream inputfile("exp_10_inputfile.csv", ios::in);

    if( !inputfile.is_open())
    {
        cout<<"Error in opening the file"<<endl;
        return -1;
    }

    while(getline(inputfile, line))
    {
        stringstream str(line);

        if(line_no==0)
        {
            line_no++;
            continue;
        }

        getline(str, point, ',');
        getline(str, x, ',');
        getline(str, y, ',');

        //get the points added to the dataset
        x_coor= stoi(x);
        y_coor= stoi(y);

        dataset.push_back({x_coor, y_coor});
    }

    //calculate the cluster center using the mid point method
    int n= dataset.size();
    double mid_x=0, mid_y=0;

    int sum_x=0, sum_y=0;

    for(auto pair: dataset)
    {
        int x_coor = pair.first;
        int y_coor= pair.second;

        sum_x+= x_coor;
        sum_y+= y_coor;
    }

    mid_x = (sum_x)/dataset.size();
    mid_y = (sum_y)/dataset.size();


    //Now calculate the distance of all points with all other points and also with given cluster center and display the results in lower triangular format

    //creating an outputfile
    ofstream outputfile("exp_10_outputfile.csv");

    outputfile<<"  ,p1, p2, p3, p4, p5, CC"<<endl;

    // cout<<"Dataset size is "<<dataset.size()<<endl;

    //calculating the distance of all the points with each other -> printing row-wise distances
    for(int i=0; i<dataset.size(); i++)
    {
        if( i<dataset.size())
        outputfile<<"p"<<i+1<<",";

        for(int j=0; j<=i; j++)
        {
            cout<<"This is distance between "<<i<<j<<endl;
            int x1=dataset[i].first;
            int y1=dataset[i].second;

            int x2=dataset[j].first;
            int y2=dataset[j].second;

            
            //if both points are same-> dist 0
            if( i==j )
            {
                outputfile<<"0";
                break;
            }

            double dist=distance(x1, y1, x2, y2);

            outputfile<<dist<<",";
        }

        outputfile<<endl;
    }

    //for last line -> print the distance of points from Cluster Center CC;
    outputfile<<"C ,";

    //computing the distances of all points from CC
    for(int i=0; i<dataset.size();i++)
    {
        double x=dataset[i].first;
        double y= dataset[i].second;

        double dist = distance(x, y, mid_x, mid_y);

        outputfile<<dist<<",";

        if( i==dataset.size()-1)
        outputfile<<"0"<<endl;
    }

    outputfile<<endl;
    return 0;
}