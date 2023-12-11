/*
Data Mining Assignment 5:
    - Rutuja Khilare
*/

#include <bits/stdc++.h>
using namespace std;

// A struct to represent a cell's data in the CSV file: -> it corresponds to a single class attribute -> ex: europe , north_america
struct CellData
{
    int count;
    int tWeight;
    int dWeight;
};

// Function to read data from the input CSV file into the provided data structures
void readData(const string &filename, map<string, map<string, CellData>> &cellData, map<string, int> &columnTotal, map<string, int> &rowTotal)
{
    //read file 
    fstream file(filename, ios::in);
    if (!file.is_open())
    {
        cout << "Couldn't open file: " << filename << endl;
        return;
    }

    string line, row, col, count;
    int val;
    int lineNumber = 0;

    while (getline(file, line))
    {
        //stores each line of file as a str
        stringstream str(line);

        if (lineNumber == 0)
        {
            lineNumber++;
            continue; //Skip the header line
        }
        
        //gets each individual attribute from the line
        getline(str, row, ',');
        getline(str, col, ',');
        getline(str, count, ',');

        val = stoi(count);

        //store data in specific datastructures carefully
        cellData[row][col].count += val;
        columnTotal[col] += val;
        rowTotal[row] += val;
        
    }
}

// Function to write the result to an output CSV file
void writeResult(const string &filename, const map<string, map<string, CellData>> &cellData, const map<string, int> &columnTotal, const map<string, int> &rowTotal)
{
    //writes into a file
    ofstream fw(filename, ios::out);

    //Class Attribute : Computer  : T.V : Both
    fw << "Column\\Row, Count, T-Weight, D-Weight, Count, T-Weight, D-Weight, Count, T-Weight, D-Weight" << endl;

    int totalRowValue=0;
    for(auto rowEntry: rowTotal)
    {
        totalRowValue += rowEntry.second;
    }

    for (const auto &rowEntry : rowTotal)
    { 
        const string &row = rowEntry.first;
        fw << row << ",";

        for (const auto &colEntry : columnTotal)
        {
            const string &col = colEntry.first;
            //whether t.v or computer
            const CellData &cell = cellData.at(row).at(col);
          
         
            fw << cell.count << ",";
            //t-wgt calculated
            fw << ((float)cell.count / rowTotal.at(row)) * 100 << "%,";

            //d-wgt calculated
            fw << ((float)cell.count / colEntry.second) * 100 << "%,";
        }

        //this is for last col: total of both
        fw << rowTotal.at(row) << ","
           << "100%, " << ((float)rowTotal.at(row) / totalRowValue) * 100 << "%" << endl;
    }


    fw << "Total,";

    int totalColValue =0;
    for(auto &colEntry: columnTotal)
    {
        totalColValue += colEntry.second;
    }
    
    for (const auto &colEntry : columnTotal)
    {
        fw << colEntry.second << ",";
        //this is for last row-> total of both
        fw << ((float)colEntry.second / totalColValue) * 100 << "%,";
        fw << "100%,";
    }

    fw << totalRowValue << "100%, 100%" << endl;
}

int main()
{
    //this celldata stores data about each class attribute: europe
    map<string, map<string, CellData>> cellData;

    //this columntotal map -> to cal d wgt-> string -> computer/tv
    map<string, int> columnTotal;
    //this rowtotal map-> to cal t wgt -> string ==europe/america
    map<string, int> rowTotal;

    readData("exp5_inputfile.csv", cellData, columnTotal, rowTotal);
    writeResult("exp5_outputfile.csv", cellData, columnTotal, rowTotal);

    cout << "Processing complete. Results saved to 'exp5_outputfile.csv'." << endl;

    return 0;
}