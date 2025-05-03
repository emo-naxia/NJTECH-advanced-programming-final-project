// DineInOrder.cpp
#include "DineInOrder.h"

DineInOrder::DineInOrder() : BaseOrder() {
    table_number = 0;
    box_fee = 0.0;
}

DineInOrder::DineInOrder(string orderNo, string dishNo, string dishName, double price, double discount, int amt,
    int tableNo, double boxFee)
    : BaseOrder(orderNo, dishNo, dishName, price, discount, amt) {
    table_number = tableNo;
    box_fee = boxFee;
    total_price += box_fee; // 总价 = 菜品合计 + 包厢费
}

DineInOrder::~DineInOrder() {
    cout << "DineInOrder class destructor called." << endl;
}

void DineInOrder::display() const {
    BaseOrder::display(); // 显示父类订单信息
    cout << "餐桌号: " << table_number
        << " | 包厢费: " << box_fee
        << " | 最终总价: " << total_price << endl;
}

void DineInOrder::outputToFile(ofstream& out) const {
    BaseOrder::outputToFile(out);
    out << "餐桌号: " << table_number << " 包厢费: " << box_fee
        << " 最终总价: " << total_price << endl;
}
