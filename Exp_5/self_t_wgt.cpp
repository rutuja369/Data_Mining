#include<bits/stdc++.h>
using namespace std;

//Data structure to store the values associated with each item: tv/computer
struct CellData
{
    int count;
    int t_wgt;
    int d_wgt;
};

void readData(string filename, map<string, map<string, CellData>> cellData, map<string, int> rowTotal, map<string, int> columnTotal  )
{
    ifstream inputfile(filename, ios::in);

    if(!inputfile.is_open())
    {
        cout<<"Error in opening the file"<<filename<<endl;
    }
    
    string line, location, item, count;
    int value=0, line_number=0;

    while( getline(inputfile, line))
    {
        //this stringstream object stores each line of inputfile as string
        stringstream str(line);

        
        //this is to ignore the headings of inputfile
        if( line_number == 0)
        {
            line_number++;
            continue;
        }    
        getline(str, location, ',');
        getline(str, item, ',');
        getline(str, count, ',');

        //converting extracted count in string to -> count in int
        value = stoi(count);

        cellData[location][item].count += value;
        columnTotal[item] += value;
        rowTotal[location] += value;
    }
}

void writeData(string filename, map<string, map<string, CellData>> cellData , map<string, int>columnTotal, map<string, int> rowTotal)
{
    fstream outputfile(filename, ios::out);

    //Write down the column
    outputfile<<"Column/Row, Item1 , Item2 "<<endl;
    outputfile<<"Column/Row, count, t_wgt, d_wgt, count, t_wgt, d_wgt, total_count, tt_wgt, td_wgt"<<endl;

    int totalRowValue =0;
    for(auto rowEntry: rowTotal)
    {
       //it stores the vertical sum  
       totalRowValue += rowEntry.second;
    }

    //Displaying results in expected format

    //Displaying each row
    for(auto rowEntry: rowTotal)
    {
        string location = rowEntry.first;
        outputfile<<location<<",";

        //traversing the columntotal -> to get all the items
        for(auto colEntry: columnTotal)
        {
            string item= colEntry.first;

            CellData cell = cellData.at(location).at(item);

            //print the curr_item count
            outputfile<<cell.count<<",";

            //print t_wgt of curr_item;
            outputfile<< ( double(cell.count)/rowTotal.at(location) )* 100 <<"," ;

            //print d_wgt of curr_item;
            outputfile<< (double(cell.count)/colEntry.second) * 100<<", "; //since colEntry.second stores the value 

        }
        
        //for last column :
        outputfile<<"Total ,";
       
        outputfile<<rowTotal.at(location)<<", 100% , "<<double(rowTotal.at(location)) /totalRowValue  * 100 <<endl;
    }

    //After completing this part -> last final row remains
    outputfile<<"Total, ";
    
    int totalColValue=0;
    for(auto colEntry: columnTotal)
    {
        totalColValue+= colEntry.second;
    }

    // prints total for each item
    for(auto colEntry: columnTotal)
    {
        outputfile<<colEntry.second<<",";
        outputfile<<(double(colEntry.second)/totalColValue)*100 <<", ";
        outputfile<<"100%,";
    }

    outputfile<<totalRowValue<<", 100% , 100%, "<<endl;

}


int main()
{
    //First make the data structures:
    //to store location -> ke item ka value
    map<string, map<string, CellData>> cellData;

    //to store the values for each unique location
    map<string, int> rowTotal; //string -> location

    //to store the values for each unique item
    map<string, int> columnTotal; //string -> tv/computer

    readData("exp5_inputfile.csv", cellData, rowTotal, columnTotal);
    writeData("exp5_outputfile.csv", cellData, rowTotal, columnTotal);

    return 0;
}