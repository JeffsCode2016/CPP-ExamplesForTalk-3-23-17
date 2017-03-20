#include "coins.h"
#include <iomanip>

coins::coins()
{
    cout << "Made it to the constructor" << endl;
    value = 0.0;
}

coins::coins(vector<pair<int,string>> &PassCoinClass): CoinValues(PassCoinClass)
{
    cout << "Made it to this new constructor" << endl;
    value = 0.0;
    for (auto i: CoinValues)
    {
        cout << "A " << i.second << " has a value of $" <<  fixed << setprecision(2) << static_cast<double>(i.first)/100 << endl;
    }
}

coins::~coins()
{
    cout << "Made it to the destructor" << endl;
}

double coins::Getvalue()
{
    return value;
}

void coins::Setvalue(double val)
{
    value = val;
}
