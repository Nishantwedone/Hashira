#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

long long parseBase(const string &s, int b) {
    long long res = 0;
    for (char c : s) {
        int digit = 0;
        if      (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'a' && c <= 'f') digit = 10 + (c - 'a');
        else if (c >= 'A' && c <= 'F') digit = 10 + (c - 'A');
        res = res * b + digit;
    }
    return res;
}

long long lagrangeConstant(const vector<pair<long long,long long>>& pts) {
    int k = pts.size();
    long double C = 0.0L;
    for (int i = 0; i < k; ++i) {
        long double yi = pts[i].second;
        long double Li = 1.0L;
        for (int j = 0; j < k; ++j) {
            if (j == i) continue;
            Li *= (0 - pts[j].first) / (long double)(pts[i].first - pts[j].first);
        }
        C += yi * Li;
    }
    return llround(C);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    json j;
    cin >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<pair<long long,long long>> pts;
    for (auto &it : j.items()) {
        if (it.key() == "keys") continue;
        long long x = stoll(it.key());
        int base = stoi(it.value()["base"].get<string>());
        string val = it.value()["value"].get<string>();
        long long y = parseBase(val, base);
        pts.emplace_back(x, y);
        if (pts.size() == k) break;
    }

    long long c = lagrangeConstant(pts);
    cout << c << "\n";
    return 0;
}


