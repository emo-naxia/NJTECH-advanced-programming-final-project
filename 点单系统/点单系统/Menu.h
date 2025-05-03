// Menu.h
#ifndef MENU_H
#define MENU_H
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Menu {
private:
    static int current_id;

public:
    string number;
    string name;
    double price;
    double discount;

    Menu(); // 默认构造
    Menu(string name, double price, double discount); // 有参构造
    ~Menu(); // 析构函数

    void outputToFile(ofstream& out) const; // ✅ 记得加 const
    void display() const;

    bool operator < (const Menu& other) const;
};

#endif
