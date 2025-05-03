// Menu.cpp
#include "Menu.h"

int Menu::current_id = 1001;

Menu::Menu() {
    number = to_string(current_id++);
    name = "";
    price = 0.0;
    discount = 1.0;
}

Menu::Menu(string n, double p, double d) {
    number = to_string(current_id++);
    name = n;
    price = p;
    discount = d;
}

Menu::~Menu() {
    cout << "Menu class destructor called." << endl;
}

void Menu::outputToFile(ofstream& out) const { // ✅ 要与头文件匹配加 const
    out << number << " " << name << " " << price << " " << discount << endl;
}

void Menu::display() const {
    cout << "编号: " << number
        << " | 名称: " << name
        << " | 价格: " << price
        << " | 折扣: " << discount << endl;
}

bool Menu::operator < (const Menu& other) const {
    return number < other.number;
}
