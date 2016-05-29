#include "Csv.hpp"

namespace larme {
namespace data {
    
VectorValueMap* Csv::toVectorValueMap(const std::string &stringCsv) {
    VectorValueMap* vectorValueMap = new VectorValueMap();
    
    std::vector<std::string> rows, rowNames;
    Csv::stringToVector(&rows, stringCsv, "\n");
    Csv::stringToVector(&rowNames, rows.at(0), ",");
    for (int i = 1; i < (int)rows.size(); i ++) {
        ValueMap* valueMap = new ValueMap();
        Csv::stringToValueMap(valueMap, rows.at(i), rowNames);
        vectorValueMap->push(valueMap);
    }
    
    return vectorValueMap;
}

void Csv::stringToVector(std::vector<std::string>* vectorStrings, const std::string &stringCsv, const std::string &delimiter) {
    size_t current = 0, found;
    while((found = stringCsv.find_first_of(delimiter, current)) != std::string::npos){
        vectorStrings->push_back(std::string(stringCsv, current, found - current));
        current = found + 1;
    }
    std::string lastString = std::string(stringCsv, current, stringCsv.size() - current);
    // 最後の文字列はrtrimする
    std::string::size_type right = lastString.find_last_not_of("\r\n\t\v");
    lastString = lastString.substr(0, right + 1);
    vectorStrings->push_back(lastString);
}

void Csv::stringToValueMap(ValueMap* valueMap, const std::string &stringCsv, const std::vector<std::string> &vectorKeys) {
    std::vector<std::string> tempVector;
    Csv::stringToVector(&tempVector, stringCsv, ",");
    if (tempVector.size() != vectorKeys.size()) {
        log("csv data amount invalid");
        return;
    }
    int size = static_cast<int>(tempVector.size());
    for (int i = 0; i < size; ++i) {
        valueMap->insert(std::pair<std::string, Value>(
                                                       vectorKeys.at(i),
                                                       Value(tempVector.at(i))
                                                       ));
    }
}

}}
