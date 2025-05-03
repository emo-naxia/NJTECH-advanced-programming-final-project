// BaseOrder.h
#ifndef BASE_ORDER_H
#define BASE_ORDER_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class BaseOrder {
public:
    string order_number;
    string dish_number;
    string dish_name;
    double dish_price;
    double dish_discount;
    int amount;
    double total_price;

    BaseOrder(); // Ĭ�Ϲ���
    BaseOrder(string orderNo, string dishNo, string dishName, double price, double discount, int amount);
    virtual ~BaseOrder(); // ������

    virtual void outputToFile(ofstream& out) const; // ������ļ�
    virtual void display() const; // ��ʾ����Ļ
};

#endif

