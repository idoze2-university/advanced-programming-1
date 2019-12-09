#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <functional>

using namespace std;

template <class T>
class CacheManager
{
    map<string, pair<T, list<string>::iterator>> unordered_map;
    list<string> keys;
    const int count;

public:
    void insert(string key, T obj)
    {
        if (unordered_map.size() == count)
        {
            auto last = keys.back();
            keys.pop_back();
            auto item = unordered_map.at(last);
            unordered_map.erase(last);
        }
        keys.push_front(key);
        auto iter = keys.begin();
        unordered_map.insert({key, pair<T, list<string>::iterator>(obj, iter)});
        string filename = T::class_name + "_" + key;
        ofstream out_file{filename, ios::out | ios::binary};
        if (out_file.is_open())
        {
            out_file.write((char *)&obj, sizeof(obj));
            out_file.close();
        }
    };
    T get(string key)
    {
        pair<T, list<string>::iterator> item;
        try
        {
            item = unordered_map.at(key);
            unordered_map.erase(key);
            keys.erase(item.second);
        }
        catch (const std::exception &e)
        {
            T obj;
            string filename = T::class_name + "_" + key;
            ifstream in_file{filename, ios::in | ios::binary};
            if (not in_file)
            {
                cerr << "Could not find object with key: \"" + key + "\"." << endl;
                return obj;
            }
            in_file.read((char *)&obj, sizeof(obj));
            in_file.close();
            item.first = obj;
        }
        insert(key, item.first);
        return item.first;
    };
    void foreach (function<void(T &)> func)
    {
        for (auto k : keys)
        {
            pair<T, list<string>::iterator> item = unordered_map.at(k);
            func(item.first);
        }
    };
    CacheManager(){};
    CacheManager(int count) : count(count){};
    ~CacheManager(){};
};