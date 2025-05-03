// TakeOutOrder.h
#ifndef TAKEOUTORDER_H
#define TAKEOUTORDER_H

#include "BaseOrder.h"

class TakeOutOrder : public BaseOrder {
private:
    string delivery_time;
    string delivery_address;
    string delivery_phone;
    double delivery_fee;

public:
    TakeOutOrder();
    TakeOutOrder(string orderNo, string dishNo, string dishName, double price, double discount, int amt,
        string time, string address, string phone, double fee);

    ~TakeOutOrder();

    void display() const override;          // ��д��ʾ����
    void outputToFile(ofstream& out) const override; // ��д������ļ�
};

#endif
#pragma once
