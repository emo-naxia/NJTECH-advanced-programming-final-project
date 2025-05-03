// DineInOrder.h
#ifndef DINEINORDER_H
#define DINEINORDER_H

#include "BaseOrder.h"

class DineInOrder : public BaseOrder {
private:
    int table_number;
    double box_fee;

public:
    DineInOrder();
    DineInOrder(string orderNo, string dishNo, string dishName, double price, double discount, int amt,
        int tableNo, double boxFee);

    ~DineInOrder();

    void display() const override;          // ��д��ʾ����
    void outputToFile(ofstream& out) const override; // ��д������ļ�
};

#endif
#pragma once
