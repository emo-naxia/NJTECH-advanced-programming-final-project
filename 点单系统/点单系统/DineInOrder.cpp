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
    total_price += box_fee; // �ܼ� = ��Ʒ�ϼ� + �����
}

DineInOrder::~DineInOrder() {
    cout << "DineInOrder class destructor called." << endl;
}

void DineInOrder::display() const {
    BaseOrder::display(); // ��ʾ���ඩ����Ϣ
    cout << "������: " << table_number
        << " | �����: " << box_fee
        << " | �����ܼ�: " << total_price << endl;
}

void DineInOrder::outputToFile(ofstream& out) const {
    BaseOrder::outputToFile(out);
    out << "������: " << table_number << " �����: " << box_fee
        << " �����ܼ�: " << total_price << endl;
}
