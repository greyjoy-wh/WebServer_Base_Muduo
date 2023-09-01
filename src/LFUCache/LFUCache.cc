 #include "LFUCache.h"
 LFUCache& getCache(){
    static LFUCache cache(10);
    return cache;
}