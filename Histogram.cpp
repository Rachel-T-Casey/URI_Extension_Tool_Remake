#include "RequestExtender.hpp"

RequestExtender::Histogram::Histogram(const std::vector<double>& dataSet, unsigned int binCount) {
    if(binCount < 2) {
        throw std::invalid_argument("Histogram requires at least two bins");
    }
    if(dataSet.size() < 2) {
        throw std::invalid_argument("Passed dataset contains too few unique values");
    }
    std::vector<double> normalizedData = normalizeDataset(dataSet);
    fillBins(normalizedData);
}

std::vector<double> RequestExtender::Histogram::bins() const {

}

double RequestExtender::Histogram::binSize() const {

}

double RequestExtender::Histogram::normalize(double data, double min, double max) const {
    if(min > max) {
        throw std::invalid_argument("Minimum value greater than maximum value");
    }
    if(data < min) {
        throw std::invalid_argument("Data value is less than minimum value");
    }
    if(data > max) {
        throw std::invalid_argument("Data value is greater than maximum value");
    }
    if(min == max) {
        throw std::invalid_argument("Normalize requires at least two unique values"); 
    }
    return (data - min) / (max - min);
}

std::vector<double> RequestExtender::Histogram::normalizeDataset(const std::vector<double>& data) const {
    if(data.size() < 2) {
        throw std::invalid_argument("Passed dataset contains too few unique values");
    }
    double min = data[0];
    double max = data[0];
    std::vector<double> normalizedData; 
    for(unsigned int i = 1; i < data.size(); i++) {
        if(min > data[i]) {
            min = data[i];
        } 
        if(max < data[i]) {
            max = data[i];
        }
    }
    if(min == max) {
       throw std::invalid_argument("Passed dataset contains too few unique values");
    }
    for(unsigned int i = 0; i < data.size(); i++) {
        double result = this->normalize(data[i], min, max);
        normalizedData.push_back(result);
    }
    return normalizedData;
}
void RequestExtender::Histogram::fillBins(std::vector<double>& normalizedData) {

}
