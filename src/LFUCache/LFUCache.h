#pragma once
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include "../Buffer.h"
#include <mutex>
using  std::string;


struct Node {
    string key_;
    string value_;
    int freq_;
    Node* next;
    Node* pre;
    Node(string key, string value):key_(key), value_(std::move(value)), freq_(1)
    {
    }
    Node(): key_(""), value_(""), freq_(1){
    }
};

class MyList{
public:
    Node* head;
    Node* tail;

    MyList(): head(new Node), tail(new Node) {
        head->next = tail;
        tail->pre = head;
    }
    bool empty(){
        return head->next == tail && tail->pre == head;
    }
    void deleteNode(Node* node){
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void addNode(Node* node){ //头插
        node->pre = head;
        node->next = head->next;
        node->pre->next = node;
        node->next->pre = node;
    }
};

class LFUCache {
private:
    int cap_;
    int size_;
    int minfreq_;
    std::unordered_map<string, Node*> map1;
    std::unordered_map<int, MyList*> map2;
    std::mutex mutex_;
public:
    LFUCache(int capacity) {
        cap_ = capacity;
        size_ = 0;
    }
    //返回-1 表示没有命中  返回0 表示命中了
    int get(const string& key, string & value) {
        std::unique_lock<std::mutex> lock(mutex_);
        //没找到
        if(map1.find(key) == map1.end()){
            return -1; 
        }
        Node* node = map1[key];
        // buf.append(node->value_);
        value = node->value_;
        map2[node->freq_]->deleteNode(node);
        if(map2[node->freq_]->empty() && node->freq_ == minfreq_){
            minfreq_ ++;
        }
        node->freq_++;
        if(map2.find(node->freq_) == map2.end()){
            map2[node->freq_] = new MyList();
        }
        map2[node->freq_]->addNode(node);
        return 0;
    }
    
    void put(const string& key, const string& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        if(map1.find(key) != map1.end()){
            map1[key]->value_ = value;
            string tmp;
            get(key,tmp);
        }else{
            if(size_ == cap_){
                MyList *l = map2[minfreq_];
                Node* node = l->tail->pre;
                l->deleteNode(node);
                map1.erase(node->key_);
                size_--;
            }
            size_++;
            Node* node = new Node(key, value);
            if(map2.find(1) == map2.end()){
                map2[1] = new MyList();
            }
            map2[1]->addNode(node);
            map1[key] = node;
            minfreq_ = 1;
        }
    }
};

 LFUCache& getCache();