#include "orderbook.h"
#include <fstream>

int main(){

    Orderbook orderbook;
    int i,buy,price,quantity;
    long long id;

    std::cout<<"Select which test case to use (1-3):\n";
    std::cin>>i;
    std::ifstream read(std::format("test/in{}.txt", i));


    while(read>>buy>>price>>quantity>>id){
        if(buy==-1){
            orderbook.CancelOrder(id);
            continue;
        }

        Side side = buy==1? Side::Buy : Side::Sell;
        orderbook.AddOrder(side, price, quantity, id);
    }

    read.close();

    orderbook.PrintMarket();

    return 0;
}