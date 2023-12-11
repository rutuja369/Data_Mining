#include<bits/stdc++.h>
using namespace std;

//-----------------------------------------------------------------------------------------------
//Initialize the datastructures:


//stores the list of attributes
vector<string> attributes;

//stores yes and no values freq for class attribute : playgame
map<string, int> class_attribute_count;

//stores the values in each attribute like: for outlook: sunny,rain,overcast
map<string, unordered_set<string>> values_in_attributes;

//stores freq of each value for all attributes: like for outlook : sunny ki freq, rain ki freq and so on
map<string, int> attribute_count;    

//stores freq of yes and no separately for each value for attribute: like sunny ki -> yes ki freq
                                                                                // -> no ki freq
map<string, map<string, int>> attribute_yn_count;
//-----------------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------------------------
double computeGain(string attribute_name, double parentEntropy)
{
    double gain=0;

    //Get the unique values of the curr attribute
    unordered_set<string> sets = values_in_attributes[attribute_name];

    //traverse through each unique value from the set
    for(auto values: sets)
    {
       //total no. of records
       double total_records= class_attribute_count["Yes"] + class_attribute_count["No"];
       //curr_val_freq-> ex: sunny chi freq
       double count_val_freq= attribute_count[values];

       //freq of yes and no of curr_val of attribute: Ex: sunny -> yes and no
       double count_val_yes= attribute_yn_count[values]["Yes"];
       double count_val_no= attribute_yn_count[values]["No"];

       if(count_val_yes!=0)
       {
          gain+= (count_val_freq/total_records)*(- (count_val_yes/count_val_freq)*log2(count_val_yes/count_val_freq) );
       }
       if(count_val_no!=0)
       {
          gain+= (count_val_freq/total_records)*(- (count_val_no/count_val_freq)*log2(count_val_no/count_val_freq) );
       }
    }

    gain = (parentEntropy -gain);
    return gain;
}
//-----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
double computeGini(string attribute_name)
{
    double gini=0;

    //Get the unique values of the curr attribute
    unordered_set<string> sets = values_in_attributes[attribute_name];

    //traverse through each unique value from the set
    for(auto values: sets)
    {
       //total no. of records
       double total_records= class_attribute_count["Yes"] + class_attribute_count["No"];
       //curr_val_freq-> ex: sunny chi freq
       double count_val_freq= attribute_count[values];

       //freq of yes and no of curr_val of attribute: Ex: sunny -> yes and no
       double count_val_yes= attribute_yn_count[values]["Yes"];
       double count_val_no= attribute_yn_count[values]["No"];

   
        gini+= (count_val_freq/total_records)*(1 - (count_val_yes/count_val_freq)*(count_val_yes/count_val_freq)- (count_val_no/count_val_freq)*(count_val_no/count_val_freq) );
     
    }

    return gini;
}

//----------------------------------------------------------------------------------------------



int main()
{


    //creating an inputfile to extract data
    ifstream inputfile("exp12_inputfile.csv");

    if( !inputfile.is_open())
    {
        cout<<"Error in opening file"<<endl;
    }

    string line, day, outlook, temp, hum, wind, playGame;
    int line_no=0;

    while( getline(inputfile, line))
    {
        stringstream str(line);


        //extract data from each row
        getline(str, day, ',' );
        getline(str, outlook, ',' );
        getline(str, temp, ',' );
        getline(str, hum, ',' );
        getline(str, wind, ',' );
        getline(str, playGame, ',' );

        //now fill out the datasets
        if( line_no == 0)
        {
            line_no++;
            attributes.push_back(outlook);
            attributes.push_back(temp);
            attributes.push_back(hum);
            attributes.push_back(wind);
            continue;
        }

        class_attribute_count[playGame]++;
        
        //hard coded -> fill out the values_int_attributes-> d.s
        values_in_attributes["Outlook"].insert(outlook);
        values_in_attributes["Temp"].insert(temp);
        values_in_attributes["Humidity"].insert(hum);
        values_in_attributes["Wind"].insert(wind);

        //fill out attribute count:->  sunny freq
        attribute_count[outlook]++;
        attribute_count[temp]++;
        attribute_count[hum]++;
        attribute_count[wind]++;

        attribute_yn_count[outlook][playGame]++;
        attribute_yn_count[temp][playGame]++;
        attribute_yn_count[hum][playGame]++;
        attribute_yn_count[wind][playGame]++;

    }


    //calculate the Parent Entropy;
    double yes_count = class_attribute_count["Yes"];
    double no_count= class_attribute_count["No"];
    double total_count = yes_count+no_count;

    double parentEntropy =0;

    parentEntropy -= (yes_count/total_count)*(log2(yes_count/total_count)) ;
    parentEntropy -= (no_count/total_count)*(log2(no_count/total_count)) ;

    cout<<"Entropy of class attribute or parent Entropy is: "<<parentEntropy<<endl;

    //Compute the gain and gini Index for each attribute and store the results in outputfile
    ofstream outputfile("exp12_outputfile.csv", ios::out);

    outputfile<<"Attribute"<<","<<"Gain"<<","<<"Gini Index"<<endl;

    //traverse through all the attributes one by one and cal gain and gini index for each of them

    //outlook, temp, hum, wind -> 4
    for(int i=0; i<4; i++)
    {
        //only list of attributes is required 
        double gain = computeGain(attributes[i], parentEntropy); //and here since parent entropy is req -> thus passed on
        double gini = computeGini(attributes[i]);

        //display the output
        outputfile<<attributes[i]<<","<<gain<<","<<gini<<endl;
    }





    return 0;
}