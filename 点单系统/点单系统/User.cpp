// User.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <iostream>
#include <fstream>
#include <ctime>

User::User() {}

User::~User() {
    cout << "User class destructor called." << endl;
}

void User::browseMenu(const vector<Menu>& menuList) const {
    cout << "========== ��ǰ�˵� ==========" << endl;
    for (const auto& menu : menuList) {
        menu.display();
    }
    cout << "==============================" << endl;
}

void User::placeOrder(const vector<Menu>& menuList) {
    browseMenu(menuList);

    vector<BaseOrder*> orders;
    string order_number;

    // ���ɶ������
    time_t now = time(0);
    tm* ltm = localtime(&now);
    order_number = to_string(1900 + ltm->tm_year)
        + (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(ltm->tm_mon + 1)
        + (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday)
        + "001"; // ��������001��������Զ�̬����

    cout << "��ѡ���òͷ�ʽ��1. ��ʳ 2. ������: ";
    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "�����������������: ";
        cin >> choice;
    }

    vector<Menu> selectedDishes;

    while (true) {
        cout << "�������Ʒ��ţ�����0������ͣ�: ";
        string dishNo;
        cin >> dishNo;
        if (dishNo == "0") break;

        cout << "���������: ";
        int amount;
        cin >> amount;
        if (amount <= 0) {
            cout << "�����������0�����������롣" << endl;
            continue;
        }

        // ���Ҳ˵�
        bool found = false;
        for (const auto& item : menuList) {
            if (item.number == dishNo) {
                selectedDishes.push_back(item);

                BaseOrder* order = new BaseOrder(order_number, item.number, item.name,
                    item.price, item.discount, amount);
                orders.push_back(order);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "û���ҵ��ò�Ʒ�����������롣" << endl;
        }
    }

    if (orders.empty()) {
        cout << "δ���κβ�Ʒ��ȡ��������" << endl;
        return;
    }

    double all_total = 0;
    for (const auto& o : orders) {
        all_total += o->total_price;
    }

    if (choice == 1) { // ��ʳ
        int tableNo;
        double boxFee;
        cout << "�����������: ";
        cin >> tableNo;
        cout << "�Ƿ���Ҫ���᣿(�������ѽ��, û��������0): ";
        cin >> boxFee;

        all_total += boxFee;

        // ������ʳ������Ϣ
        ofstream fout(order_number + "_dinein.txt");
        for (const auto& o : orders) {
            o->outputToFile(fout);
        }
        fout << "������: " << tableNo << " �����: " << boxFee << " �ܼ�: " << all_total << endl;
        fout.close();

        cout << "��ʳ���������ɣ��ļ�����" << order_number + "_dinein.txt" << endl;

    }
    else if (choice == 2) { // ����
        string time, address, phone;
        double deliveryFee;
        cout << "�������Ͳ�ʱ�䣨��18:00��: ";
        cin >> time;
        cout << "�������Ͳ͵�ַ: ";
        cin.ignore();
        getline(cin, address);
        cout << "��������ϵ�绰: ";
        getline(cin, phone);
        cout << "������������: ";
        cin >> deliveryFee;

        all_total += deliveryFee;

        ofstream fout(order_number + "_takeout.txt");
        for (const auto& o : orders) {
            o->outputToFile(fout);
        }
        fout << "�Ͳ�ʱ��: " << time
            << " �Ͳ͵�ַ: " << address
            << " ��ϵ�绰: " << phone
            << " ������: " << deliveryFee
            << " �ܼ�: " << all_total << endl;
        fout.close();

        cout << "�������������ɣ��ļ�����" << order_number + "_takeout.txt" << endl;
    }

    for (auto& o : orders) {
        delete o;
    }
}
