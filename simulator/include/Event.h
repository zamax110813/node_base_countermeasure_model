#ifndef EVENT_H
#define EVENT_H

#include"Obj.h"

enum TRANSITION{
    infection1,//非対策脆弱状態から非対策感染状態
    removal1,//非対策脆弱状態から非対策保護状態
    recovery1,//非対策感染状態から非対策保護状態
    discovery1,//非対策保護状態から非対策脆弱状態
    infection2,//対策脆弱状態から対策感染状態
    removal2,//対策脆弱状態から対策保護状態
    recovery2,//対策感染状態から対策保護状態
    discovery2,//対策保護状態から対策脆弱状態
    change_strat,//戦略の変更
    measure//時間計測用
};

class Obj;

class Event{
public:
    int node_num;//イベントが起こるノード番号
	double time;
	Obj* handler;
	Event* next;
    TRANSITION type_of_event;
};

#endif
#pragma once
