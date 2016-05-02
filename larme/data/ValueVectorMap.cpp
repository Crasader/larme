#include "ValueVectorMap.hpp"
#include "larme/data/Csv.hpp"

namespace larme {
namespace data {
    
    
ValueVectorMap* ValueVectorMap::createFromCsvFile(const std::string &filepath) {
    std::string stringCsv = FileUtils::getInstance()->getStringFromFile(filepath);
    return Csv::toValueVectorMap(stringCsv);
}

ValueVectorMap::ValueVectorMap() {
    
}

ValueVectorMap::~ValueVectorMap() {
    for (const cocos2d::ValueMap* map : this->values) {
        delete map;
    }
}

int ValueVectorMap::size() {
    return static_cast<int>(this->values.size());
}

const std::vector<const cocos2d::ValueMap*>* ValueVectorMap::getValue() {
    return &(this->values);
}

std::string ValueVectorMap::getStringAt(int number, const std::string &name) {
    return this->values.at(number)->at(name).asString();
}

std::string ValueVectorMap::getStringAt(int number, const std::string &name, const std::string &defaultValue) {
    if (0 < this->values.at(number)->count(name)) {
        return this->values.at(number)->at(name).asString();
    }
    return defaultValue;
}

int ValueVectorMap::getIntegerAt(int number, const std::string &name) {
    return this->values.at(number)->at(name).asInt();
}

int ValueVectorMap::getIntegerAt(int number, const std::string &name, const int defaultValue) {
    if (0 < this->values.at(number)->count(name)) {
        return this->values.at(number)->at(name).asInt();
    }
    return defaultValue;
}
    
float ValueVectorMap::getFloatAt(int number, const std::string &name) {
    return this->values.at(number)->at(name).asFloat();
}

float ValueVectorMap::getFloatAt(int number, const std::string &name, const float defaultValue) {
    if (0 < this->values.at(number)->count(name)) {
        return this->values.at(number)->at(name).asFloat();
    }
    return defaultValue;
}

void ValueVectorMap::push(const cocos2d::ValueMap* valueMap) {
    this->values.push_back(valueMap);
}

}}