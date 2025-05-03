// TakeOutOrder.cpp
#include "TakeOutOrder.h"

TakeOutOrder::TakeOutOrder() : BaseOrder() {
    delivery_time = "";
    delivery_address = "";
    delivery_phone = "";
    delivery_fee = 0.0;
}

TakeOutOrder::TakeOutOrder(string orderNo, string dishNo, string dishName, double price, double discount, int amt,
    string time, string address, string phone, double fee)
    : BaseOrder(orderNo, dishNo, dishName, price, discount, amt) {
    delivery_time = time;
    delivery_address = address;
    delivery_phone = phone;
    delivery_fee = fee;
    total_price += delivery_fee; // 总价 = 菜品小计 + 外卖服务费
}

TakeOutOrder::~TakeOutOrder() {
    cout << "TakeOutOrder class destructor called." << endl;
}

void TakeOutOrder::display() const {
    BaseOrder::display(); // 显示父类信息
    cout << "送餐时间: " << delivery_time
        << " | 送餐地址: " << delivery_address
        << " | 联系电话: " << delivery_phone
        << " | 外卖费: " << delivery_fee
        << " | 最终总价: " << total_price << endl;
}

void TakeOutOrder::outputToFile(ofstream& out) const {
    BaseOrder::outputToFile(out);
    out << "送餐时间: " << delivery_time
        << " 送餐地址: " << delivery_address
        << " 联系电话: " << delivery_phone
        << " 外卖费: " << delivery_fee
        << " 最终总价: " << total_price << endl;
}
