#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include "Menu.h"
#include "BaseOrder.h"
#include "DineInOrder.h"
#include "TakeOutOrder.h"
#include "User.h"
#include "Admin.h"

using namespace std;

// 从 menu.txt 加载菜单
void loadMenuFromFile(vector<Menu>& menuList) {
    menuList.clear();
    ifstream fin("menu.txt");
    string number, name;
    double price, discount;
    while (fin >> number >> name >> price >> discount) {
        Menu m;
        m.number = number;
        m.name = name;
        m.price = price;
        m.discount = discount;
        menuList.push_back(m);
    }
    fin.close();
}

int main() {
    vector<Menu> menuList;
    loadMenuFromFile(menuList); // 初始加载菜单文件

    while (true) {
        cout << "\n======= 欢迎使用自助点餐系统 =======" << endl;
        cout << "1. 管理员登录" << endl;
        cout << "2. 顾客点餐" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请选择身份: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            Admin admin;
            if (admin.login()) {
                bool admin_running = true;
                while (admin_running) {
                    cout << "\n=== 管理员功能菜单 ===" << endl;
                    cout << "1. 添加菜品" << endl;
                    cout << "2. 修改菜品" << endl;
                    cout << "3. 删除菜品" << endl;
                    cout << "4. 查询菜品" << endl;
                    cout << "5. 保存菜单到文件" << endl;
                    cout << "6. 查看订单文件" << endl;
                    cout << "7. 删除订单文件" << endl;
                    cout << "8. 销售统计" << endl;
                    cout << "9. 热销菜品排行" << endl;
                    cout << "10. 修改订单文件" << endl;
                    cout << "0. 返回主菜单" << endl;
                    cout << "请输入操作编号: ";
                    int op;
                    cin >> op;

                    switch (op) {
                    case 1: admin.addDish(menuList); break;
                    case 2: admin.modifyDish(menuList); break;
                    case 3: admin.deleteDish(menuList); break;
                    case 4: admin.searchDish(menuList); break;
                    case 5: admin.saveMenuToFile(menuList); break;
                    case 6: {
                        string filename;
                        cout << "请输入订单文件名（如 20250429001_dinein.txt）: ";
                        cin >> filename;
                        admin.viewOrder(filename);
                        break;
                    }
                    case 7: {
                        string filename;
                        cout << "请输入订单文件名: ";
                        cin >> filename;
                        admin.deleteOrder(filename);
                        break;
                    }
                    case 8: {
                        int n;
                        cout << "请输入要统计的订单文件个数: ";
                        cin >> n;
                        vector<string> files(n);
                        for (int i = 0; i < n; ++i) {
                            cout << "输入文件名[" << i + 1 << "]: ";
                            cin >> files[i];
                        }
                        admin.salesStatistics(files);
                        break;
                    }
                    case 9: {
                        int n;
                        cout << "请输入要分析的订单文件个数: ";
                        cin >> n;
                        vector<string> files(n);
                        for (int i = 0; i < n; ++i) {
                            cout << "输入文件名[" << i + 1 << "]: ";
                            cin >> files[i];
                        }
                        admin.topSellingDishes(files);
                        break;
                    }
                    case 10: {
                        string filename;
                        cout << "请输入要修改的订单文件名: ";
                        cin >> filename;
                        admin.modifyOrder(filename);
                        break;
                    }

                    case 0: admin_running = false; break;
                    default: cout << "无效操作！" << endl;
                    }
                }
            }

        }
        else if (choice == 2) {
            User user;
            loadMenuFromFile(menuList);
            user.placeOrder(menuList);

        }
        else if (choice == 0) {
            cout << "感谢使用，再见！" << endl;
            break;

        }
        else {
            cout << "无效输入，请重新选择。" << endl;
        }
    }

    return 0;
}
