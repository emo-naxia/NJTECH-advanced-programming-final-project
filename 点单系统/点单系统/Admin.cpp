// Admin.cpp
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstdio>
#include <sstream>

Admin::Admin() {
    username = "admin";
    password = "123456";
}

Admin::~Admin() {
    cout << "Admin class destructor called." << endl;
}

// 登录验证
bool Admin::login() {
    string user, pass;
    cout << "请输入管理员账号: ";
    cin >> user;
    cout << "请输入密码: ";
    cin >> pass;

    if (user == username && pass == password) {
        cout << "登录成功！" << endl;
        return true;
    }
    else {
        cout << "账号或密码错误！" << endl;
        return false;
    }
}

// 添加菜品
void Admin::addDish(vector<Menu>& menuList) {
    string name;
    double price, discount;

    cout << "请输入菜品名称: ";
    cin >> name;
    cout << "请输入菜品价格: ";
    cin >> price;
    cout << "请输入折扣（如无折扣请输入1.0）: ";
    cin >> discount;

    Menu newDish(name, price, discount);
    menuList.push_back(newDish);

    cout << "添加菜品成功！" << endl;
}

// 修改菜品
void Admin::modifyDish(vector<Menu>& menuList) {
    cout << "请输入要修改的菜品编号: ";
    string number;
    cin >> number;

    bool found = false;
    for (auto& item : menuList) {
        if (item.number == number) {
            cout << "找到菜品：" << item.name << endl;
            cout << "请输入新菜名: ";
            cin >> item.name;
            cout << "请输入新价格: ";
            cin >> item.price;
            cout << "请输入新折扣: ";
            cin >> item.discount;
            cout << "修改成功！" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "未找到该编号对应的菜品！" << endl;
    }
}

// 删除菜品
void Admin::deleteDish(vector<Menu>& menuList) {
    cout << "请输入要删除的菜品编号: ";
    string number;
    cin >> number;

    for (auto it = menuList.begin(); it != menuList.end(); ++it) {
        if (it->number == number) {
            cout << "删除菜品：" << it->name << endl;
            menuList.erase(it);
            cout << "删除成功！" << endl;
            return;
        }
    }

    cout << "未找到该编号对应的菜品！" << endl;
}

// 查询菜品
void Admin::searchDish(const vector<Menu>& menuList) const {
    cout << "请输入要查询的菜品编号或名称: ";
    string keyword;
    cin >> keyword;

    bool found = false;
    for (const auto& item : menuList) {
        if (item.number == keyword || item.name == keyword) {
            item.display();
            found = true;
        }
    }

    if (!found) {
        cout << "没有找到相关菜品。" << endl;
    }
}

// 保存菜单到文件
void Admin::saveMenuToFile(const vector<Menu>& menuList) {
    ofstream fout("menu.txt");
    for (const auto& item : menuList) {
        item.outputToFile(fout);
    }
    fout.close();
    cout << "菜单已保存到 menu.txt 文件。" << endl;
}

// 查看订单内容
void Admin::viewOrder(const string& filename) const {
    ifstream fin(filename);
    if (!fin) {
        cout << "订单文件不存在：" << filename << endl;
        return;
    }

    string line;
    cout << "========== 订单内容 ==========" << endl;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    cout << "==============================" << endl;

    fin.close();
}

// 删除订单文件
void Admin::deleteOrder(const string& filename) {
    if (remove(filename.c_str()) == 0) {
        cout << "成功删除订单文件：" << filename << endl;
    }
    else {
        cout << "删除失败，文件不存在或无法删除。" << endl;
    }
}

// 销售统计功能
void Admin::salesStatistics(const vector<string>& orderFiles) {
    double totalRevenue = 0;
    int orderCount = 0;

    for (const string& file : orderFiles) {
        ifstream fin(file);
        if (!fin) continue;

        string line;
        while (getline(fin, line)) {
            if (line.find("总价") != string::npos) {
                size_t pos = line.find("总价:");
                if (pos != string::npos) {
                    double value = stod(line.substr(pos + 6));
                    totalRevenue += value;
                    orderCount++;
                }
            }
        }
        fin.close();
    }

    cout << "共统计订单数: " << orderCount << endl;
    cout << "总销售额为: " << totalRevenue << " 元" << endl;
}

// 销量排行
void Admin::topSellingDishes(const vector<string>& orderFiles) {
    map<string, int> dishCount;

    for (const string& file : orderFiles) {
        ifstream fin(file);
        if (!fin) continue;

        string dishName;
        while (fin >> std::ws && fin.peek() != EOF) {
            string order_number, dish_number;
            double price, discount;
            int amount;
            fin >> order_number >> dish_number >> dishName >> price >> discount >> amount;
            dishCount[dishName] += amount;
            string dummy;
            getline(fin, dummy);
        }
        fin.close();
    }

    vector<pair<string, int>> sortedDishes(dishCount.begin(), dishCount.end());
    sort(sortedDishes.begin(), sortedDishes.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

    cout << "\n🍽️ 热销菜品前5：" << endl;
    int topN = min(5, (int)sortedDishes.size());
    for (int i = 0; i < topN; ++i) {
        cout << sortedDishes[i].first << " [" << sortedDishes[i].second << "份] ";
        cout << string(sortedDishes[i].second, '*') << endl;
    }
}
void Admin::modifyOrder(const std::string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "文件打开失败！" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // 读取菜品行（跳过标题、桌号、地址等）
    while (getline(in, line)) {
        if (line.find("订单编号") != string::npos ||
            line.find("堂食") != string::npos ||
            line.find("桌号") != string::npos ||
            line.find("外卖") != string::npos ||
            line.find("地址") != string::npos ||
            line.find("电话") != string::npos ||
            line.find("总价") != string::npos) {
            continue;
        }
        lines.push_back(line);
    }
    in.close();

    if (lines.empty()) {
        cout << "订单为空或格式不支持修改！" << endl;
        return;
    }

    cout << "订单菜品如下：\n";
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << i + 1 << ". " << lines[i] << endl;
    }

    cout << "请输入要删除的菜品序号（输入0表示不删除）: ";
    int delIndex;
    cin >> delIndex;

    if (delIndex > 0 && delIndex <= (int)lines.size()) {
        lines.erase(lines.begin() + delIndex - 1);
        cout << "已删除第 " << delIndex << " 项菜品。\n";
    }

    // 简单重算总价
    double total = 0;
    for (const string& l : lines) {
        stringstream ss(l);
        string number, name;
        double price, discount;
        int amount = 1;
        ss >> number >> name >> price >> discount >> amount;
        total += price * discount * amount;
    }

    // 重写文件
    ofstream out(filename);
    out << "【修改后的订单】\n";
    for (const string& l : lines) {
        out << l << endl;
    }
    out << "总价: " << total << endl;
    out.close();

    cout << "订单修改完成并保存。\n";
}
