#pragma once
#include "include.h"

class Person {
public:
    QString username;
    QString pwd;
    QString nickname;
    int level;
    int exp;
    int count;
public:
    Person() {
        level = 0;
        exp = 0;
    }
    Person(QString _username,
           QString _pwd,
           QString _nickname,
           int _level,
           int _exp,
           int _count) {
        this->username = _username;
        this->pwd = _pwd;
        this->nickname = _nickname;
        this->level = _level;
        this->exp = _exp;
        this->count = _count;
    }
    Person(const Person &rhs) {
        username = rhs.username;
        pwd = rhs.pwd;
        nickname = rhs.nickname;
        level = rhs.level;
        exp = rhs.exp;
    }

    int get_level(QString s) {
        if(s.length() <= 3)
            return 1;
        else if(s.length() <= 6)
            return 2;
        else if(s.length() <= 9)
            return 3;
        else if(s.length() <= 12)
            return 4;
        else
            return 5;
    }
};
