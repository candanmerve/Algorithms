/*
	MERVE CANDAN
	150160041
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>

int match,misMatch, indel, value;

using namespace std;

vector<string> alphabeticalOrder(vector<string> str)
{
    sort(str.begin(), str.end());
    return str;
}

int findMaxValue(int** matrix, int matchValue, int len1, int len2, int i, int k)
{
    int leftPoint;
    int upPoint;
    int dPoint;
    int maximum;
    leftPoint = matrix[i - 1][k] + indel;
    upPoint = matrix[i][k - 1] + indel;
    dPoint = matrix[i - 1][k - 1] + matchValue;
    maximum = max(leftPoint, max(upPoint, dPoint));
    return maximum > 0 ? maximum : 0;
}

vector<string> sweat(string str1, string str2)
{
    int maxValue = 0;
    int** matrix = new int*[str1.length()+1];
    for (int i = 0; i < (signed)str1.length() + 1; i++)
    {
        matrix[i] = new int[str2.length()+1];
        for (int k = 0; k < (signed)str2.length() + 1; k++)
            matrix[i][k] = 0;
    }
    
    for (int i = 1; i < (signed)str1.length() + 1; i++)
    {
        for (int k = 1; k < (signed)str2.length() + 1; k++)
        {
            if (str1[i - 1] == str2[k - 1])
                matrix[i][k] = findMaxValue(matrix, match, str1.length() + 1, str2.length() + 1, i, k);
            else
                matrix[i][k] = findMaxValue(matrix, misMatch, str1.length() + 1, str2.length() + 1, i, k);
        }
    }

    for (int i = 0; i < (signed)str1.length() + 1; i++)
    {
        for (int k = 0; k < (signed)str2.length() + 1; k++)
        {
            maxValue = matrix[i][k] > maxValue ? matrix[i][k] : maxValue;
        }
    }
    vector<char> word;
    vector<string> words;
    bool check;
    for (int i = 0; i < (signed)str1.length() + 1; i++)
    {
        for (int k = 0; k < (signed)str2.length() + 1; k++)
        {
            if (matrix[i][k] == maxValue)
            {
                check = false;
                /*for (int m = 0; m < maxValue; m++)
                {
                    word.insert(word.begin(),str1[i - m-1]);
                }*/
                int temp_i = i;
                int temp_k = k;
                int counter = 0;
                while (matrix[temp_i][temp_k] > 0)
                {
                    word.insert(word.begin(), str1[i - counter - 1]);
                    temp_i--;
                    temp_k--;
                    counter++;
                }
                string hold(word.begin(), word.end());
                word.clear();
                for (int j = 0; j < (signed)words.size(); j++)
                {
                    if (words[j] == hold)
                        check = true;
                }
                if (!check && hold != "")
                    words.push_back(hold);
            }
        }
    }
    value = maxValue;
    sort(words.begin(), words.end());
    return words;
}

int main(int argc,char **argv) {
    ifstream file;
    ofstream output(argv[2]);
    file.open(argv[1]);
    match = stoi(argv[3]);
    misMatch = stoi(argv[4]);
    indel = stoi(argv[5]);
    vector<string> str;
    vector<string> words;
    if (!file) {
        cerr << "File cannot be opened!";
        exit(1);
    }
    string line;
    while (!file.eof()) {
        getline(file, line);
        str.push_back(line);
    }
    str = alphabeticalOrder(str);

    for (int i = 0; i < (signed)str.size() - 1; i++)
    {
        for (int j = i+1; j < (signed)str.size(); j++)
        {
            words = sweat(str[i], str[j]);
            
            output << str[i] << " - " << str[j] << endl;
            output << "Score: " << value << " Sequence(s):";
            for (int i = 0; i < (signed)words.size(); i++)
                output << " \"" << words[i] << "\"";
            output << endl;
        }
    }
	file.close();
    output.close();
    return 0;
}