#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

struct Rule
{
    string substr;
    string type;
    string str;
};

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

vector<Rule> parse_csv(string filename)
{
    vector<Rule> rules;
    ifstream in;
    in.open(filename);

    string s;
    while (getline(in, s))
    {
        vector<string> v = split(s, ",");
        rules.push_back(Rule{v[0], v[1], v[2]});
    }
    in.close();
    return rules;
}

vector<int> Z_func(const string &s)
{
    vector<int> Z(s.size());
    // Z[0] = s.size();
    int left = 0, right = 0;
    for (int i = 0; i < Z.size(); ++i)
    {
        // cout<<left<<' '<<right<<endl;
        Z[i] = max(0, min(right - i, Z[i - left]));
        while (i + Z[i] < s.size() && s[Z[i]] == s[i + Z[i]])
        {
            Z[i]++;
            if (i + Z[i] > right)
            {
                left = i;
                right = i + Z[i];
            }
        }
    }
    return Z;
}

int main(int argc, char *argv[])
{
    string mode = argv[1];
    string filename = argv[2];

    string input;
    cin >> input;

    vector<Rule> a = parse_csv(filename);

    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i].substr << " " << a[i].type << " " << a[i].str << endl;
    }

    int input_size = input.size();
    for (int i = 0; i < a.size(); i++)
    {
        vector<int> ans = Z_func(a[i].substr + "#" + input);
        if (mode == "--step")
            cout << a[i].substr + "#" + input << endl;
        for (int o = 0; o < ans.size(); o++)
        {
            if (mode == "--step")
                cout << ans[o];
        }
        if (mode == "--step")
            cout << endl;
        int tmp = 0;
        for (int j = 0; j < ans.size(); j++)
        {
            tmp++;
            if (a[i].substr.size() == ans[j] || ans.size() == 1)
            {
                if (ans.size() == 1)
                {
                    input.replace(j - a[i].substr.size(), a[i].substr.size() + 1,
                                  a[i].str);
                }
                else
                    input.replace(j - a[i].substr.size() - 1, a[i].substr.size(),
                                  a[i].str);
                if (a[i].type == "|->")
                    goto endlop;
                i = -1;
                break;
            }
        }
        if (mode == "--step")
            cout << endl;
    }

endlop:
    cout << input;
}
