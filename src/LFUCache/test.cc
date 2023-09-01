#include "LFUCache.h"
#include "../Buffer.h"

int main()
{
    LFUCache* obj = new LFUCache(2);
    // obj->put(1,1);
    // obj->put(2,2);
    // int n1 = obj->get(1);
    // obj->put(3,3);
    // int n2 = obj->get(2);
    // int n3 = obj->get(3);
    // obj->put(4,4);
    // int n4 = obj->get(1);
    // int n5 = obj->get(3);
    // int n6 = obj->get(4);
    Buffer buf1;
    Buffer buf2;
    Buffer buf3;
    obj->put("file1", "nihao1");
    obj->put("file2", "nihao2");
    obj->put("file3", "nihao3");
    // string s1 = "";
    // string s2 = "";
    // string s3 = "";
    int ret = obj->get("file1", buf1);
    if(!ret){
        std::cout<<buf1.retrieveAllAsString()<<std::endl;
    }
    ret = obj->get("file2", buf2);
    if(!ret){
        std::cout<<buf2.retrieveAllAsString()<<std::endl;
    }    
    ret =obj->get("file3", buf3);
    if(!ret){
        std::cout<<buf3.retrieveAllAsString()<<std::endl;
    }    


    return 0;

}