#include <iostream>
#include <set>
#include <unordered_map>
#include <format>
#include <memory>

enum class Side{
    Buy,
    Sell
};

using ll = long long;

class Order
{
public:
    Order(Side side, int price, int quantity,ll time, ll orderId)
    : side_{side}
    , price_{price}
    , initialQuantity_{quantity}
    , remainingQuantity_{quantity}
    , time_{time}
    , orderId_{orderId}
    {   }

    ll GetOrderId() const { return orderId_; }
    Side GetSide() const { return side_; }
    int GetPrice() const { return price_; }
    ll GetTime() const { return time_;}
    int GetInitialQuantity() const { return initialQuantity_; }
    int GetRemainingQuantity() const { return remainingQuantity_; }
    int GetFilledQuantity() const {return initialQuantity_-remainingQuantity_;}

    bool isFilled(){ return GetRemainingQuantity()==0; }

    void Fill(int quantity){
        if(quantity> GetRemainingQuantity())
            throw std::logic_error(std::format("Order ({}) cannot be filled for more than ", GetOrderId()) );

        remainingQuantity_-=quantity;
    }

    bool operator<(const Order& other) const{
        bool isSell = (GetSide() == Side::Sell);

        if(GetPrice()>other.GetPrice())return true^isSell;
        else if(GetPrice()<other.GetPrice())return false^isSell;

        return GetTime()<other.GetTime();
    }

private:
    Side side_;
    int price_;
    int initialQuantity_;
    int remainingQuantity_;
    ll time_;
    ll orderId_;

};

struct CompareOrder{
    bool operator()(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) const{
        bool isSell = (a->GetSide() == Side::Sell);

        if(a->GetPrice()>b->GetPrice())return true^isSell;
        else if(a->GetPrice()<b->GetPrice())return false^isSell;

        return a->GetTime()<b->GetTime();
    }
};

class Orderbook
{
private:

    std::set<std::shared_ptr<Order>, CompareOrder> ask_;
    std::set<std::shared_ptr<Order>, CompareOrder> buy_;
    std::unordered_map<ll, std::shared_ptr<Order>> order_;
    static ll time_;

    void MatchOrders(){

        while(true){
            if(ask_.size()==0 || buy_.size()==0) break;

            auto bestBuy = *buy_.begin(); //copies share pointer
            auto bestAsk = *ask_.begin();
            if(bestBuy->GetPrice() < bestAsk->GetPrice())break;

            int quantity = std::min(bestBuy->GetRemainingQuantity(), bestAsk->GetRemainingQuantity());

            bestBuy->Fill(quantity);
            bestAsk->Fill(quantity);
            std::cout<<"Traded "<<quantity<<" units at "<<(bestBuy->GetPrice()+bestAsk->GetPrice())/2.0<<" euros!\n";

            buy_.erase(buy_.begin());
            if(bestBuy->isFilled())order_.erase(bestBuy->GetOrderId());
            else buy_.insert(bestBuy);

            ask_.erase(ask_.begin());
            if(bestAsk->isFilled())order_.erase(bestAsk->GetOrderId());
            else ask_.insert(bestAsk);

        }

    }


public:

    void AddOrder(Side side, int price, int quantity, ll orderId){
        if(quantity<=0)
            throw std::logic_error("Only orders of positive ammounts!");
        
        std::shared_ptr<Order> newOrder = std::make_shared<Order>(side, price, quantity, time_++, orderId);
        if(side==Side::Buy){
            buy_.insert(newOrder);
        }else{
            ask_.insert(newOrder);
        }

        order_.emplace(orderId,newOrder);
        MatchOrders();
    }


    void CancelOrder(ll orderId){
        auto currentOrder = order_.find(orderId);
        if(currentOrder==order_.end())return;

        if((currentOrder->second)->GetSide()==Side::Buy){
            buy_.erase(currentOrder->second);//cant erase
        }else{
            ask_.erase(currentOrder->second);
        }
        order_.erase(currentOrder);
    }

    void PrintMarket(){
        std::cout<<"Buy:\n";
        std::cout<<"Price | Quantity \n";
        for(auto& u:buy_){
            std::cout<<u->GetPrice()<<" "<<u->GetRemainingQuantity()<<'\n';
        }
        std::cout<<"Ask:\n";
        std::cout<<"Price | Quantity \n";
        for(auto& u:ask_){
            std::cout<<u->GetPrice()<<" "<<u->GetRemainingQuantity()<<'\n';
        }
        std::cout<<'\n';
    }
//AddOrder(Side, price, quantity, OrderId)
//CancelOrder(OrderId)
};

ll Orderbook::time_ =0;