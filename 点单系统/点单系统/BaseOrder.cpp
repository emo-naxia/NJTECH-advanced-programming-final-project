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
    cout << "������: " << order_number
        << " | ��Ʒ���: " << dish_number
        << " | ����: " << dish_name
        << " | ����: " << dish_price
        << " | �ۿ�: " << dish_discount
        << " | ����: " << amount
        << " | С��: " << total_price << endl;
}
