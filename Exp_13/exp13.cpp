#include <bits/stdc++.h>
using namespace std;

vector<string>attributes;
map<string,int>class_attri_cnt;
map<string,map<string,map<string,int>>>attribute_yn_cnt;
 
double calculateProbability(string Outlook,string Temp,string Humidity,string Wind,string playgame){
 
     double yes_cnt = class_attri_cnt["Yes"];
     double no_cnt = class_attri_cnt["No"];
     double total = yes_cnt + no_cnt;

     double ans = class_attri_cnt[playgame]/total * (attribute_yn_cnt[attributes[0]][Outlook][playgame])/(class_attri_cnt[playgame]) *(attribute_yn_cnt[attributes[1]][Temp][playgame])/(class_attri_cnt[playgame])*(attribute_yn_cnt[attributes[2]][Humidity][playgame])/(class_attri_cnt[playgame])* (attribute_yn_cnt[attributes[3]][Wind][playgame])/(class_attri_cnt[playgame]);
     return ans;

 };

int main(){
    ifstream input("exp13_inputfile.csv");
  
    string line, day, outlook, temp, humidity, wind, playGame;
      int j = 0;
    while(getline(input,line)){
      
        stringstream str(line);

        getline(str,day,',');
        getline(str,outlook,',');
        getline(str,temp,',');
        getline(str,humidity,',');
        getline(str,wind,',');
        getline(str,playGame,',');

        if(j==0){
        j++;
        attributes.push_back(outlook);
        attributes.push_back(temp);
        attributes.push_back(humidity);
        attributes.push_back(wind);
        continue;
        }
       
       class_attri_cnt[playGame]++;

       attribute_yn_cnt[attributes[0]][outlook][playGame]++;
       attribute_yn_cnt[attributes[1]][temp][playGame]++;
       attribute_yn_cnt[attributes[2]][humidity][playGame]++;
       attribute_yn_cnt[attributes[3]][wind][playGame]++;

    }


    double yes_cnt = class_attri_cnt["Yes"];
    double no_cnt = class_attri_cnt["No"];
    double total = yes_cnt + no_cnt;

     cout << "Enter the unknown case" << endl;
     string Outlook, Temp, Humidity, Wind;
     cin >> Outlook >> Temp >> Humidity >> Wind;

     double p_yes = calculateProbability(Outlook, Temp, Humidity, Wind,"Yes");
     double p_no = calculateProbability(Outlook, Temp, Humidity, Wind,"No");

     cout << "Probability of yes is "<<p_yes <<endl;
     cout<<"Probability of no is "<< p_no << endl;

     if(p_yes > p_no ) {
        cout << "The unknown case is classified as Yes" ;
     }
     else cout<< "The unknown case is classified as No";
}