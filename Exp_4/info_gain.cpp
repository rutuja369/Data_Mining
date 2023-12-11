/*
Data Mining Assignment 4: Info gain calculation
- Rutuja Khilare
*/

#include <bits/stdc++.h>
using namespace std;


// Function to calculate entropy
double calculateEntropy(int positive, int negative)
{
    double total = positive + negative;
    double entropy = 0.0;

    if (total > 0)
    {
        double positiveProbability = positive / total;
        double negativeProbability = negative / total;

        /*
        Entropy = E- p*log2(p) (where p is the probability)
        */
        if (positiveProbability > 0)
        {
            entropy -= positiveProbability * log2(positiveProbability);
        }

        if (negativeProbability > 0)
        {
            entropy -= negativeProbability * log2(negativeProbability);
        }
    }

    return entropy;
}

// Function to compute information gain
double computeInformationGain(map<string, int> &parentCounts, map<string, map<string, int>> &childCounts)
{

    double positiveParent = parentCounts["Yes"];
    double negativeParent = parentCounts["No"];
    double totalParent = positiveParent + negativeParent;

    // need probability count for entropy -> pass on the count of yes and no func
    double parentEntropy = calculateEntropy(positiveParent, negativeParent);
    cout << "Parent Entropy: " << parentEntropy << "\n";

    // Similarly get the child entropy from map
    double childEntropy = 0;

    for (auto it = childCounts.begin(); it != childCounts.end(); ++it)
    {
        string childName = it->first;
        double positiveChild = it->second["Yes"];
        double negativeChild = it->second["No"];
        double totalChild = positiveChild + negativeChild;

        double childEntropyPart = calculateEntropy(positiveChild, negativeChild);

        /*
        child Entropy= (totalchild_count/totalparent_count) * childEntropyPart
        */
        childEntropy += (totalChild / totalParent) * childEntropyPart;
    }

    cout << "Weighted Child Entropy: " << childEntropy << "\n";

    double informationGain = parentEntropy - childEntropy;
    cout << "Information Gain: " << informationGain << "\n";

    return informationGain;
}

int main()
{

    // get the input data set
    ifstream file("exp4_inputfile.csv");

    // variables to store attribute data and the categorical class: playtennis
    string line, day, outlook, temp, humidity, wind, playtennis;

    // parentCount-> to calculate main entropy for the categorical class: playtennis
    map<string, int> parentCounts;

    /*
    childCounts-> to calculate the attribute table of selected attribute
    if-> childName = column 3 (temp)
    so, for attribute = temp -> generate a matrix of play and no-play (storing it as a map)
    */
    
    map<string, map<string, int>> childCounts;


    if (!file.is_open())
    {
        cerr << "Error opening input file." << endl;
        return -1;
    }


    int i = 0;
    string childName;
    int choice;

    // reads data for a
    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, day, ',');
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, wind, ',');
        getline(str, playtennis, ',');
        // file reads playtennis and checks for a "ending character" so append the csv file with some dummy char after the playtennis col value

        if (i == 0)
        {
            i++;
            cout << "Enter Child Column Number: ";
            cin >> choice;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Sorry this is not a valid attribute-> choose some other attribute" << endl;
            return -1;

        case 2:
            childName = outlook;
            break;

        case 3:
            childName = temp;
            break;

        case 4:
            childName = humidity;
            break;

        case 5:
            childName = wind;
            break;

        default:
            childName = playtennis;
            break;
        }

        // now calculate the freq of categorical class and the freq of values of categorical class for the chosen attribute
        parentCounts[playtennis]++;
        childCounts[childName][playtennis]++;
    }

    double informationGain = computeInformationGain(parentCounts, childCounts);

    cout << "Overall Information Gain: " << informationGain << "\n";

    file.close();

    return 0;
}