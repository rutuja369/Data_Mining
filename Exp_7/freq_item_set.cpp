/*
Data Mining Assignment 7
 - Rutuja Khilare
*/

#include <bits/stdc++.h>
using namespace std;

/*
Note:
If min support count is given as 2-> then to find:
min support(%) = (min support count) / n  ...(where n = no. of transactions ) *100
and the input file can have real life transactions like {bread, milk, butter}-> so string splitting is req
*/

double min_supp_freq;                 // Minimum frequency for itemsets to be considered frequent.-> here support count is given in %
vector<set<string>> transac_table; // A vector to store transaction data.
set<string> item_sets;          // Set to store unique item_sets/items in the transactions.
map<string, int> freq;          // A map to store the frequency of each product/item.

// Function to split a string into words based on alphanumeric characters.
vector<string> wordsof(string str)
{
    vector<string> tmpset;
    string tmp = "";
    int i = 0;
    while (str[i])
    {
        //this func is to check if str[i] is alphanumeric
        if (isalnum(str[i]))
            tmp += str[i];
        else
        {
            if (tmp.size() > 0)
                tmpset.push_back(tmp);
            tmp = "";
        }
        i++;
    }

    if (tmp.size() > 0)
        tmpset.push_back(tmp);

    return tmpset;
}

// Function to combine elements in a vector into a string, excluding the one at 'miss' index.
string combine(vector<string> &arr, int miss)
{
    string str;
    for (int i = 0; i < arr.size(); i++)
    {
        if (i != miss )
            str += arr[i] + " ";
    }
    str = str.substr(0, str.size() - 1);
    return str;
}

// Function to clone a set and return a copy.
set<string> cloneit(set<string> &arr)
{
    set<string> dup;
    for (set<string>::iterator it = arr.begin(); it != arr.end(); it++)
        dup.insert(*it);
    return dup;
}

// Function to generate frequent itemsets of size k based on candidate itemsets of size k-1.
set<string> apriori_gen(set<string> &sets, int k)
{
    set<string> set2;
    for (set<string>::iterator it1 = sets.begin(); it1 != sets.end(); it1++)
    {
        set<string>::iterator it2 = it1;
        it2++;
        for (; it2 != sets.end(); it2++)
        {
            vector<string> v1 = wordsof(*it1);
            vector<string> v2 = wordsof(*it2);

            /*
            This is bigggg logic of generating latice: A, B, C: use karne kitne new candidate item sets bana sakte
            AB, AC, BC
            */

            bool alleq = true;
            for (int i = 0; i < k - 1 && alleq; i++)
            {
                if (v1[i] != v2[i])
                    alleq = false;
            }

            v1.push_back(v2[k - 1]);
            if (v1[v1.size() - 1] < v1[v1.size() - 2])
                swap(v1[v1.size() - 1], v1[v1.size() - 2]);

            for (int i = 0; i < v1.size() && alleq; i++)
            {
                string tmp = combine(v1, i);
                if (sets.find(tmp) == sets.end())
                    alleq = false;
            }

            if (alleq)
                set2.insert(combine(v1, -1));
        }
    }
    return set2;
}


int main()
{

    // Input file stream for reading data from a file.
    ifstream fin("exp_7_inputfile.csv", ios::in); // Open the input file for reading.

    if (!fin.is_open())
    {
        perror("Error in opening file : "); // Print an error message if the file cannot be opened.
    }
    cout << "Frequency % :";
    cin >> min_supp_freq; //Read the minimum frequency from the user.


    string str;
    while (!fin.eof())
    {
        getline(fin, str);

        vector<string> arr = wordsof(str);

        set<string> tmpset;
        for (int i = 0; i < arr.size(); i++)
            tmpset.insert(arr[i]);

        transac_table.push_back(tmpset); // Store the transaction data in the 'transac_table' vector.

        for (set<string>::iterator it = tmpset.begin(); it != tmpset.end(); it++)
        {
            item_sets.insert(*it); // Store unique item_sets in the 'item_sets' set.
            freq[*it]++;          // Increment the frequency of each product in the 'freq' map.
        }
    }
    fin.close(); // Close the input file.

    cout << "No of transactions: " << transac_table.size() << endl;
    min_supp_freq = min_supp_freq * transac_table.size() / 100; // Calculate the minimum frequency threshold.
    cout << "Min support count: " << min_supp_freq << endl;

    //to avoid duplicacy : since {bread, milk} {milk, bread} should not be pushed
    queue<set<string>::iterator> q;

    for (set<string>::iterator it = item_sets.begin(); it != item_sets.end(); it++)
    {
        if (freq[*it] < min_supp_freq)
            q.push(it);
    }

    while (q.size() > 0)
    {
        // Remove infrequent item_sets from the 'item_sets' set.
        item_sets.erase(*q.front()); 
        q.pop();
    }

    int pass = 1;
    cout << "\nFrequent " << pass++ << " -item set : \n";
    for (set<string>::iterator it = item_sets.begin(); it != item_sets.end(); it++)
        cout << "{" << *it << "} " << freq[*it] << endl; // Display frequent 1-itemsets.

    //this generates the freq item sets with items 2
    int i = 2;
    //we are cloning curr item_sets table -> coz if in this itr all the generated item_sets have freq<(min_supp_count) -> then product becomes empty so we need to revert back to prev item_sets table
    set<string> prev = cloneit(item_sets);

    //This loop keeps generating freq_itemsets until we stop getting candidate_item_sets with freq>min_supp_count
    while(i)
    {
        set<string> cur = apriori_gen(prev, i - 1); // Generate candidate itemsets of size 'i'.

        //here we check -> if the curr itemsets gen have become empty-> break and use prev item_sets as final freq_itemsets
        if (cur.size() < 1)
        {
            break;
        }

        for (set<string>::iterator it = cur.begin(); it != cur.end(); it++)
        {
            vector<string> arr = wordsof(*it);

            int tot = 0;
            for (int j = 0; j < transac_table.size(); j++)
            {
                bool pres = true;
                for (int k = 0; k < arr.size() && pres; k++)
                {
                    if (transac_table[j].find(arr[k]) == transac_table[j].end())
                    {
                        pres = false;
                        break;
                    }
                }
                if (pres)
                    tot++;
            }

            if (tot >= min_supp_freq)
                freq[*it] += tot;
            else
                q.push(it);
        }

        while (q.size() > 0)
        {
            cur.erase(*q.front());
            q.pop();
        }

      
      

        if (cur.size() == 0)
            break;

        cout << "\n\nFrequent " << pass++ << " -item set : \n";
        for (set<string>::iterator it = cur.begin(); it != cur.end(); it++)
            cout << "{" << *it << "} " << freq[*it] << endl; // Display frequent k-itemsets.

        prev = cloneit(cur);
        i++;
    }

    ofstream fw("item_set_output.csv", ios::out); // Open an output file for writing.
    for (auto it = prev.begin(); it != prev.end(); it++)
    {
        fw << "{" << *it << "}" << endl; // Write frequent itemsets to the output file.
    }

    return 1;
}