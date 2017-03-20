#ifndef COINS_H
#define COINS_H

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class coins
{
    public:
        coins();
        coins(vector<pair<int,string>> &PassCoinClass);
        virtual ~coins();

        double Getvalue();
        void Setvalue(double val);

    protected:

    private:
        double value;
        vector<pair<int,string>> CoinValues;
};

#endif // COINS_H
