#pragma once
#include<fstream>
#include<iostream>
#include"BPtree.hpp"
#include<vector>//#include"vector.hpp"
#include"lib/algorithm.hpp"
#include"lib/utility.hpp"
namespace sjtu
{
class ticket_key
{
private:
    string _Loc1;
    string _Loc2;
    string _Catalog;
public:
    ticket_key(const char* a, const char* b, const char* c): _Loc1(a), _Loc2(b), _Catalog(c) {}
    ticket_key(const ticket_key& o): _Loc1(o._Loc1), _Loc2(o._Loc2), _Catalog(o._Catalog) {}
    bool operator<(ticket_key o)
    {
        if(_Loc1 < o._Loc1) return true;
        if(_Loc1 > o._Loc1) return false;
        if(_Loc2 < o._Loc2) return true;
        if(_Loc2 > o._Loc2) return false;
        if(_Catalog < o._Catalog) return true;
        return false;
    }
};

class ticket_data
{
private:
    time _Time_From;
    time _Time_To;
    int _Price_Num;
    pair<string, double> _Price[7];
public:
    ticket_data(time a, time c, int d, pair<string, double>* e):_Time_From(a), _Time_To(c), _Price_Num(d)
    {
        for(int i = 0;i < d;i++) _Price[i] = e[i];
    }
    ticket_data(const ticket_data &o):_Time_From(o._Time_From),_Time_To(o.Time_To),_Price_Num(o._Price_Num)
    {
        for(int i = 0;i < _Price_Num;i++) _Price[i] = o._Price[i];
    }
};

class ticket_map
{
private:
    BPtree<string, ticket_data> _Sub_Root;
    static int _Num_Of_File;
public:
    ticket_map()
    {
        char* str;
        sprintf(str, _Num_Of_File);
        const char* cstr(str);
        fstream _Iofile;
        _Iofile.open(cstr);
        _Sub_Root = BPtree<string, ticket_data> (cstr);
        _Num_Of_File++;
    }
    void insert(string a, ticket_data b)
    {
        _Sub_Root.insert(a, b);
    }
};

class ticket
{
private:
    BPtree<ticket_key, ticket_map> _Root;
public:
    ticket()
    {
        fstream _Iofile;
        _Iofile.open("_Ticket_Data")
        _Root = BPtree<ticket_data, ticket_map> ("_Ticket_Data");
    }
    std::vector<pair<string, ticket_data>> query_ticket(ticket_key _Key)
    {
        ticket_map m = _Root.query(_Key).first;
        return m._Sub_Root.traverse();
    }
    void add_ticket(ticket_key k, string id, ticket_data d)
    {
        bool b = _Root.query(k).second;
        if(b)
        {
            ticket_map m = _Root.query(k).first;
            m.insert(id, d);
        }
        else
        {
            ticket_map m;
            m.insert(id, d);
            _Root.insert(k, m);
        }
    }
};
}