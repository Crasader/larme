#pragma once

/*
 平均値っぽい値に近似させるクラス
 */



namespace larme {
namespace util {
        
class Approximate
{
private:
    float average;
    int sampleAmount;
public:
    AverageRecent()
    :average(0), sampleAmount(1) {
    };
    
    void setSampleAmount(int sampleAmount) {
        this->sampleAmount = sampleAmount;
    }
    
    void setAverage(float total) {
        this->average = total;
    }
    
    float getAverage() {
        return this->average;
    }
    
    bool isAverageUnderThan(float compare) {
        return this->average < compare;
    }
    
    bool isAverageMoreThan(float compare) {
        return this->average >= compare;
    }
    
    void push(float sample) {
        float diff = (sample - average);
        average += diff / sampleAmount;
    }
};

}}