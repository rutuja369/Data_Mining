#include <bits/stdc++.h>
using namespace std;

int op = 1;

ofstream fwtr("linkage_output.csv", ios::out);

// Function to perform agglomerative clustering and return the name of the resulting cluster
string agglomerative(string input)
{
    //creating the distance matrix
    map<string, map<string, int>> dm;


    fstream file(input, ios::in);

    string line;
    getline(file, line);

    int pt = 0;
    stringstream st(line);

    int i = 0;
    //now extracting the pts to store in a vector of string
    string point;
    vector<string> points;

    // Read the point names from the first line of the input file
    while (getline(st, point, ','))
    {
        if (i == 0)
        {
            i++;
            continue;
        }
        //storing the pts
        points.push_back(point);
    }

    //filling out out d.s -> dm
    // Populate the distance matrix from the input file
    while (getline(file, line))
    {
        stringstream str(line);
        //get the first pt from line string -> A
        getline(str, point, ',');

        string dist;
        int idx = 0;

        while (getline(str, dist, ','))
        {
            if (dist.length() != 0)
            {
                try
                {
                    // A-> A, B, C, D , E, F
                    //Calculating dist of each point with all other points
                    dm[point][points[idx]] = stoi(dist);
                }
                catch (const std::invalid_argument &e)
                {
                    cerr << "Invalid argument in distance data: " << e.what() << " for dist: " << dist << endl;
                    // Handle the error as needed (e.g., skip the value or set a default distance)
                    dm[point][points[idx]] = 0; // Set a default distance
                }
            }
            idx++;
        }
    }

    // The rest of your agglomerative clustering code remains the same.
    // ...
    string pt1, pt2;
    int min_dist = INT_MAX;

    // Find the two points with the minimum distance
    for (auto p : dm)
    {
        for (auto pp : p.second)
        {
            //p1=A   , p2=A 
            string p1 = p.first, p2 = pp.first;
            //get dist between these two pts
            int dist = pp.second;
            //Update the pt1 and pt2 if found that curr pts have min dist than previous ones
            if (p1 != p2 && dist < min_dist)
            {
                pt1 = p1;
                pt2 = p2;
                min_dist = dist;
            }
        }
    }

    //Got the min dist now -> form ckuster of these two pts -> by clubing their rows

    cout << "Clusters Chosen: " << pt1 << " & " << pt2 << endl;

    //-----------------------------------------------------------------------
    string up, down;
    // Determine the order of the two points based on their names
    if (pt1[0] > pt2[0])
    {
        down = pt1;
        up = pt2; //smaller is in up -> F
    }
    else
    {
        up = pt1; //smaller is in up -> E
        down = pt2;
    }

    //Big -> to small -> FE
    string newPt = down + up;


    // Update distances and remove old points from the matrix
    for (auto p : dm)
    {
        point = p.first;
        if (point[0] > newPt[0])
        {
            //updating the dist -> with min
            dm[point][newPt] = min(dm[point][up], dm[point][down]);
        }
    }
    //dm[down] -> map traversing in F ka d.s
    for (auto p : dm[down])
    {
        point = p.first;
        //f to a dist
        int d1 = p.second;

        if (up[0] > point[0])
            d1 = min(d1, dm[up][point]); //e to a dist
        else
            d1 = min(d1, dm[point][up]);

        //dist of FE to A -> d1
        dm[newPt][point] = d1;
    }

    //ig -> this is for traversing column wise
    for (auto p : dm)
    {
        point = p.first;
        auto mtemp = p.second;


        if (point[0] >= up[0])
        {
            int d1 = dm[point][up];

            if (down[0] > point[0])
                d1 = min(d1, dm[down][point]);
            else
                d1 = min(d1, dm[point][down]);

            dm[point][newPt] = d1;
            dm[point].erase(up);

            if (point[0] >= down[0])
                dm[point].erase(down);
        }
    }

    dm.erase(up);
    dm.erase(down);
    //-------------------------------------------------------------------


    // Create an output file with updated cluster data
    string output = "output" + to_string(op++) + ".csv";
    ofstream fw(output, ios::out);
    fw << ",";

    //Prints row and then col
    for (auto p : dm)
    {
        fw << p.first << ",";
    }
    fw << "\n";

    //Print dist matrix
    for (auto p : dm)
    {
        fw << p.first << ",";
        for (auto pp : p.second)
        {
            fw << pp.second << ",";
        }
        fw << "\n";
    }

    //fw -> closing phase wise outputfiles
    fw.close();

    //Getting results in main output file
    fwtr << down << " & " << up << "\n";

    return output;

}

int main()
{
    string input = "linkage_input.csv";

    fstream file1(input, ios::in);

    string line;
    getline(file1, line);

    int pt = 0;
    stringstream st(line);

    int j = 0, len = 0;
    string point;

    // Determine the number of points in the dataset
    while(getline(st, point, ','))
    {
        if (j == 0)
        {
            j++;
            continue;
        }
        len++;
    }
    cout<<len<<endl;
    // Repeatedly perform agglomerative clustering to create clusters
    for (int i = 1; i <= len - 2; i++)
    {
        string output = agglomerative(input);
        input = output;
    }
    return 0;
}
