// User.h
#ifndef USER_H
#define USER_H

#include <vector>
#include "Menu.h"
#include "DineInOrder.h"
#include "TakeOutOrder.h"

class User {
public:
    User();
    ~User();

    void browseMenu(const vector<Menu>& menuList) const; // 展示菜单
    void placeOrder(const vector<Menu>& menuList);       // 下单
};

#endif
#pragma once
