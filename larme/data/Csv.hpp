#pragma once

#include "ValueVectorMap.hpp"
#include "cocos2d.h"

USING_NS_CC;

namespace larme {
namespace data {
    
class Csv
{
public:
    static ValueVectorMap* toValueVectorMap(const std::string &stringCsv);
private:
    static void stringToVector(std::vector<std::string>* vectorStrings, const std::string &stringCsv, const std::string &delimiter);
    static void stringToValueMap(ValueMap* valueMap, const std::string &stringCsv, const std::vector<std::string> &vectorKeys);
};

}
}
