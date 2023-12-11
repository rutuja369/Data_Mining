/*
Data mining assignment 2
- Rutuja khilare
*/

#include <bits/stdc++.h>
using namespace std;

// Function to perform min-max normalization using the specified formula
vector<double> minMaxNormalization(const vector<double>& data, double min_new, double max_new) {
    double min_old = *min_element(data.begin(), data.end());
    double max_old = *max_element(data.begin(), data.end());
    
    vector<double> normalized_data;
    for (double val : data) {
        double normalized_val = (val - min_old) / (max_old - min_old) * (max_new - min_new) + min_new;
        normalized_data.push_back(normalized_val);
    }
    
    return normalized_data;
}

// Function to perform z-score normalization
vector<double> zScoreNormalization(const vector<double>& data) {
    double mean = 0;
    for (double val : data) {
        mean += val;
    }
    mean /= data.size();
    
    double variance = 0;
    for (double val : data) {
        variance += (val - mean) * (val - mean);
    }
    variance /= data.size();
    
    double std_deviation = sqrt(variance);
    
    vector<double> normalized_data;
    for (double val : data) {
        double z_score = (val - mean) / std_deviation;
        normalized_data.push_back(z_score);
    }
    
    return normalized_data;
}

int main() {
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    
    vector<double> data;
    double value;
    
    while (input_file >> value) {
        data.push_back(value);
    }
    
    double min_new, max_new;
    cout << "Enter the new range for min-max normalization (min new max): ";
    cin >> min_new >> max_new;
    
    vector<double> min_max_normalized = minMaxNormalization(data, min_new, max_new);
    vector<double> z_score_normalized = zScoreNormalization(data);
    
    output_file << "Min-Max Normalized Data:\n";
    for (double val : min_max_normalized) {
        output_file << val << "\n";
    }
    
    output_file << "\nZ-Score Normalized Data:\n";
    for (double val : z_score_normalized) {
        output_file << val << "\n";
    }
    
    input_file.close();
    output_file.close();
    
    return 0;
}