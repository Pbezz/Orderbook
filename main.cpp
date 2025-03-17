#include <bits/stdc++.h>
#include <format>
#include <iostream>
#include "orderbook.h"

int main(){

    Orderbook orderbook;


    orderbook.PrintMarket();
    orderbook.AddOrder(Side::Buy, 10, 1, 0);
    orderbook.AddOrder(Side::Buy, 11, 4, 1);
    orderbook.AddOrder(Side::Buy, 12, 2, 2);

    orderbook.AddOrder(Side::Sell, 20, 2, 3);
    orderbook.AddOrder(Side::Sell, 18, 13, 4);
    orderbook.PrintMarket();
    orderbook.AddOrder(Side::Sell, 10, 70, 5);
    orderbook.PrintMarket();

    orderbook.CancelOrder(4);
    orderbook.CancelOrder(3);
    orderbook.CancelOrder(5);
    orderbook.PrintMarket();

    int testSize =0;
    std::cout<<"Final number of orders to test the orderbook:\n";
    std::cin>>testSize;

    for(int i=1;i<=testSize;i++) orderbook.AddOrder(Side::Buy, 10, i, i+10);

    for(int i=1;i<=testSize;i++) orderbook.AddOrder(Side::Sell, 10, i, i+testSize+10);

    orderbook.PrintMarket();
    return 0;
}