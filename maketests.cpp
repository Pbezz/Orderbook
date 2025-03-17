#include <iostream>
#include <fstream>
#include <format>

int main(){

    int i,buy,price,quantity;
    long long id;
    std::cin>>i;


    std::ofstream write(std::format("test/in{}.txt", i));


    for(int x=1;x<=100;x++){
        write<<"1 10 "<<x<<" "<<x<<'\n';
    }    
    for(int x=1;x<=100;x++){
        write<<"0 10 "<<101-x<<" "<<x+100<<'\n';
    }

    return 0;
}