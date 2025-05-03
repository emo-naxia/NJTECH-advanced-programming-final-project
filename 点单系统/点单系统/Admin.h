// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "Menu.h"

using namespace std;

class Admin 
{
private:
    string username;
    string password;

public:
    Admin();
    ~Admin();

    // ��¼����
    bool login();

    // �˵�����
    void addDish(vector<Menu>& menuList);
    void modifyDish(vector<Menu>& menuList);
    void deleteDish(vector<Menu>& menuList);
    void searchDish(const vector<Menu>& menuList) const;
    void saveMenuToFile(const vector<Menu>& menuList);
    void modifyOrder(const std::string& filename);


    // ��������
    void viewOrder(const string& filename) const;
    void deleteOrder(const string& filename);

    // ����ͳ��
    void salesStatistics(const vector<string>& orderFiles);
    void topSellingDishes(const vector<string>& orderFiles);
};

#endif
