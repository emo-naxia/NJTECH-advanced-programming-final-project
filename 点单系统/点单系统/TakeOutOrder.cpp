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
    total_price += delivery_fee; // �ܼ� = ��ƷС�� + ���������
}

TakeOutOrder::~TakeOutOrder() {
    cout << "TakeOutOrder class destructor called." << endl;
}

void TakeOutOrder::display() const {
    BaseOrder::display(); // ��ʾ������Ϣ
    cout << "�Ͳ�ʱ��: " << delivery_time
        << " | �Ͳ͵�ַ: " << delivery_address
        << " | ��ϵ�绰: " << delivery_phone
        << " | ������: " << delivery_fee
        << " | �����ܼ�: " << total_price << endl;
}

void TakeOutOrder::outputToFile(ofstream& out) const {
    BaseOrder::outputToFile(out);
    out << "�Ͳ�ʱ��: " << delivery_time
        << " �Ͳ͵�ַ: " << delivery_address
        << " ��ϵ�绰: " << delivery_phone
        << " ������: " << delivery_fee
        << " �����ܼ�: " << total_price << endl;
}
