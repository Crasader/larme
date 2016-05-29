#include "VectorValueMap.hpp"
#include "larme/data/Csv.hpp"

namespace larme {
namespace data {
    
    
VectorValueMap* VectorValueMap::createFromCsvFile(const std::string &filepath) {
    std::string stringCsv = FileUtils::getInstance()->getStringFromFile(filepath);
    return Csv::toVectorValueMap(stringCsv);
}

VectorValueMap::VectorValueMap() {
    
}

VectorValueMap::~VectorValueMap() {
    for (const cocos2d::ValueMap* map : this->values) {
        delete map;
    }
}

int VectorValueMap::size() {
    return static_cast<int>(this->values.size());
}

const std::vector<const cocos2d::ValueMap*>* VectorValueMap::getValue() {
    return &(this->values);
}

std::string VectorValueMap::getStringAt(int number, const std::string &name) {
    return this->values.at(number)->at(name).asString();
}

std::string VectorValueMap::getStringAt(int number, const std::string &name, const std::string &defaultValue) {
    if (0 < this->values.at(number)->count(name)) {
        return this->values.at(number)->at(name).asString();
    }
    return defaultValue;
}

int VectorValueMap::getIntegerAt(int number, const std::string &name) {
    return this->values.at(number)->at(name).asInt();
}

int VectorValueMap::getIntegerAt(int number, const std::string &name, const int defaultValue) {
    if (0 < this->values.at(number)->count(name)) {
        return this->values.at(number)->at(name).asInt();
    }
    return defaultValue;
}
    
float VectorValueMap::getFloatAt(int number, const std::string &name) {
    return this->values.at(number)->at(name).asFloat();
}

float VectorValueMap::getFloatAt(int number, const std::string &name, const float defaultValue) {
    if (0 < this->values.at(number)->count(name)) {
        return this->values.at(number)->at(name).asFloat();
    }
    return defaultValue;
}

void VectorValueMap::push(const cocos2d::ValueMap* valueMap) {
    this->values.push_back(valueMap);
}

}}