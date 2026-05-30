#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>

using namespace std;

struct Settlement {
    string from;
    string to;
    long long amount;
};

vector<Settlement> minimizeCashFlow(
    vector<tuple<string, string, long long>>& transactions)
{
    unordered_map<string, long long> balance;

    // Calculate net balances
    for (auto& t : transactions)
    {
        string from, to;
        long long amount;

        tie(from, to, amount) = t;

        balance[from] -= amount;
        balance[to] += amount;
    }

    // Separate debtors and creditors
    vector<pair<string, long long>> debtors;
    vector<pair<string, long long>> creditors;

    for (auto& person : balance)
    {
        if (person.second < 0)
        {
            debtors.push_back(
                {person.first, -person.second});
        }
        else if (person.second > 0)
        {
            creditors.push_back(
                {person.first, person.second});
        }
    }

    vector<Settlement> result;

    int i = 0;
    int j = 0;

    while (i < debtors.size() && j < creditors.size())
    {
        long long amount =
            min(debtors[i].second, creditors[j].second);

        result.push_back({
            debtors[i].first,
            creditors[j].first,
            amount
        });

        debtors[i].second -= amount;
        creditors[j].second -= amount;

        if (debtors[i].second == 0)
            i++;

        if (creditors[j].second == 0)
            j++;
    }

    return result;
}

int main()
{
    vector<tuple<string, string, long long>> transactions = {
        {"Tom", "Jerry", 1000},
        {"Jerry", "Spike", 1000},
        {"Spike", "Tom", 500}
    };

    vector<Settlement> optimized =
        minimizeCashFlow(transactions);

    cout << "Optimized Transactions:\n\n";

    for (auto& t : optimized)
    {
        cout << t.from
             << " pays "
             << t.to
             << " ₹"
             << t.amount
             << endl;
    }

    return 0;
}