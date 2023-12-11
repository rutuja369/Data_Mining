#include<bits/stdc++.h>
using namespace std;
int k;

struct Point
{
    double x,y;
    int cluster;
};

double distance(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) +(a.y-b.y)*(a.y-b.y) );
}

void clustering(vector<Point> &arr, vector<Point> &clust_center){
  for(int i=0;i<arr.size();i++)
  {
    double dis=distance(arr[i],clust_center[0]);
    int location=0;
    for(int j=0;j<clust_center.size();j++)
    {
        int d=distance(arr[i],clust_center[j]);
        if(d<dis)
        {
            dis=d;
            location=j;
        }
    }
     arr[i].cluster=location;
  }
}

void Updatecenter(vector<Point> &arr,vector<Point> &clut_center)
{
    map<int, int> clust;
    vector<Point> centroidSum(k, {0.0, 0.0, 0});

    for(int i=0;i<arr.size();i++)
    {
        int c=arr[i].cluster;
        clust[c]++;
        centroidSum[c].x += arr[i].x;
        centroidSum[c].y += arr[i].y;
    }
    
    for(int i=0;i<k;i++)
    {
        if(clust.find(i)!=clust.end())
        {
            clut_center[i].x = centroidSum[i].x / clust[i];
            clut_center[i].y = centroidSum[i].y / clust[i];
        }
    }

}

int main()
{
    vector<Point> arr;
    ifstream f1("exp_10_inputfile.csv");
    string point,line,x,y;
    int val;
    cout<<"Enter number of clusters:";
    cin>>k;
    getline(f1,line);
    while (getline(f1,line))
    {
        stringstream str(line);
        getline(str,point,',');
        getline(str,x,',');
        getline(str,y,',');
        Point p;
        p.x=stod(x);
        p.y=stod(y);
        arr.push_back(p);
    }
    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<>dis(1, arr.size());

    vector<Point> cluster_center(k);
    for(int i=0;i<k;i++)
    {
        int r= dis(gen);
        cluster_center[i]=arr[r];
    }
    for(int i=0;i<k;i++)
    {
        cout<<cluster_center[i].x<<cluster_center[i].y<<endl;
    }
    for(int i=0;i<10;i++)
    {
        clustering(arr,cluster_center);
        Updatecenter(arr,cluster_center);
        cout<<endl<<"Output After "<<i+1<<" iteration"<<endl;
    }
    ofstream f2("out.csv");
    f2<<"x"<<","<<"y"<<","<<"Cluster"<<endl;
    for(auto it:arr)
    {
        f2<<it.x<<","<<it.y<<","<<it.cluster<<endl;
    }
    return 0;
}