// BaseOrder.cpp
#include "BaseOrder.h"

BaseOrder::BaseOrder() {
    order_number = "";
    dish_number = "";
    dish_name = "";
    dish_price = 0.0;
    dish_discount = 1.0;
    amount = 0;
    total_price = 0.0;
}

BaseOrder::BaseOrder(string orderNo, string dishNo, string dishName, double price, double discount, int amt) {
    order_number = orderNo;
    dish_number = dishNo;
    dish_name = dishName;
    dish_price = price;
    dish_discount = discount;
    amount = amt;
    total_price = price * discount * amt;
}

BaseOrder::~BaseOrder() {
    cout << "BaseOrder class destructor called." << endl;
}

void BaseOrder::outputToFile(ofstream& out) const {
    out << order_number << " " << dish_number << " " << dish_name << " "
        << dish_price << " " << dish_discount << " "
        << amount << " " << total_price << endl;
}

void BaseOrder::display() const {
    cout << "订单号: " << order_number
        << " | 菜品编号: " << dish_number
        << " | 菜名: " << dish_name
        << " | 单价: " << dish_price
        << " | 折扣: " << dish_discount
        << " | 份数: " << amount
        << " | 小计: " << total_price << endl;
}
