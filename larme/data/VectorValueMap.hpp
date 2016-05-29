#pragma once

#include "cocos2d.h"
#include <vector>

USING_NS_CC;


namespace larme {
namespace data {
    
class VectorValueMap
{
private:
    std::vector<const cocos2d::ValueMap*> values;
public:
    VectorValueMap();
    ~VectorValueMap();
    int size();
    const std::vector<const cocos2d::ValueMap*>* getValue();
    std::string getStringAt(int number, const std::string &name);
    std::string getStringAt(int number, const std::string &name, const std::string &defaultValue);
    int getIntegerAt(int number, const std::string &name);
    int getIntegerAt(int number, const std::string &name, const int defaultValue);
    float getFloatAt(int number, const std::string &name);
    float getFloatAt(int number, const std::string &name, const float defaultValue);
    void push(const cocos2d::ValueMap* valueMap);
    
    static VectorValueMap* createFromCsvFile(const std::string &filepath);
};

}}