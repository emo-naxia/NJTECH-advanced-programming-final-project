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
    cout << "========== 当前菜单 ==========" << endl;
    for (const auto& menu : menuList) {
        menu.display();
    }
    cout << "==============================" << endl;
}

void User::placeOrder(const vector<Menu>& menuList) {
    browseMenu(menuList);

    vector<BaseOrder*> orders;
    string order_number;

    // 生成订单编号
    time_t now = time(0);
    tm* ltm = localtime(&now);
    order_number = to_string(1900 + ltm->tm_year)
        + (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(ltm->tm_mon + 1)
        + (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday)
        + "001"; // 这里简单设成001，后面可以动态调整

    cout << "请选择用餐方式（1. 堂食 2. 外卖）: ";
    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "输入错误，请重新输入: ";
        cin >> choice;
    }

    vector<Menu> selectedDishes;

    while (true) {
        cout << "请输入菜品编号（输入0结束点餐）: ";
        string dishNo;
        cin >> dishNo;
        if (dishNo == "0") break;

        cout << "请输入份数: ";
        int amount;
        cin >> amount;
        if (amount <= 0) {
            cout << "份数必须大于0，请重新输入。" << endl;
            continue;
        }

        // 查找菜单
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
            cout << "没有找到该菜品，请重新输入。" << endl;
        }
    }

    if (orders.empty()) {
        cout << "未点任何菜品，取消订单。" << endl;
        return;
    }

    double all_total = 0;
    for (const auto& o : orders) {
        all_total += o->total_price;
    }

    if (choice == 1) { // 堂食
        int tableNo;
        double boxFee;
        cout << "请输入餐桌号: ";
        cin >> tableNo;
        cout << "是否需要包厢？(输入包厢费金额, 没有则输入0): ";
        cin >> boxFee;

        all_total += boxFee;

        // 保存堂食订单信息
        ofstream fout(order_number + "_dinein.txt");
        for (const auto& o : orders) {
            o->outputToFile(fout);
        }
        fout << "餐桌号: " << tableNo << " 包厢费: " << boxFee << " 总价: " << all_total << endl;
        fout.close();

        cout << "堂食订单已生成，文件名：" << order_number + "_dinein.txt" << endl;

    }
    else if (choice == 2) { // 外卖
        string time, address, phone;
        double deliveryFee;
        cout << "请输入送餐时间（如18:00）: ";
        cin >> time;
        cout << "请输入送餐地址: ";
        cin.ignore();
        getline(cin, address);
        cout << "请输入联系电话: ";
        getline(cin, phone);
        cout << "请输入外卖费: ";
        cin >> deliveryFee;

        all_total += deliveryFee;

        ofstream fout(order_number + "_takeout.txt");
        for (const auto& o : orders) {
            o->outputToFile(fout);
        }
        fout << "送餐时间: " << time
            << " 送餐地址: " << address
            << " 联系电话: " << phone
            << " 外卖费: " << deliveryFee
            << " 总价: " << all_total << endl;
        fout.close();

        cout << "外卖订单已生成，文件名：" << order_number + "_takeout.txt" << endl;
    }

    for (auto& o : orders) {
        delete o;
    }
}
