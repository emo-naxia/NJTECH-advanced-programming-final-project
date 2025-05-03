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

    BaseOrder(); // 默认构造
    BaseOrder(string orderNo, string dishNo, string dishName, double price, double discount, int amount);
    virtual ~BaseOrder(); // 虚析构

    virtual void outputToFile(ofstream& out) const; // 输出到文件
    virtual void display() const; // 显示到屏幕
};

#endif

