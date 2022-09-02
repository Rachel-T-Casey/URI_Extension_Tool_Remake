#include "RequestExtender.hpp"
#include <cmath>


RequestExtender::RequestExtender(unsigned int binCount)
{
    m_uriKey = "";
    m_binCount = binCount;
    m_histogramPtr = nullptr;
}
void RequestExtender::start(const std::string& uri) {
    this->m_startTime = std::chrono::steady_clock::now();
    this->m_uriKey = uri;
}

void RequestExtender::finish() {
    if(this->m_startTime == std::chrono::steady_clock::time_point()) {
        throw std::logic_error("Start time not initalized");
    }
    if(this->m_uriKey == "") {
        throw std::logic_error("URI empty or not initalized");
    }

    auto endTime = std::chrono::steady_clock::now();
    auto timePassed = (endTime - this->m_startTime) / 1E6;
    double timePassedDouble = timePassed.count();
    m_responseTimes.insert(std::make_pair(m_uriKey, timePassedDouble));
}

double RequestExtender::mean(const std::string& uri) const {

    auto range = m_responseTimes.equal_range(uri);
    int totalMatches = std::distance(range.first, range.second);
    
    if(totalMatches < 1) {
        throw std::invalid_argument("URI has not been previously processed");
    }

    double total = 0;
    for(auto it = range.first; it != range.second; it++){
        total += it->second;
    }
    return total / totalMatches;
}

double RequestExtender::sd(const std::string& uri) const {

    auto range = m_responseTimes.equal_range(uri);
    int totalMatches = std::distance(range.first, range.second);

    if(totalMatches < 1) {
        throw std::invalid_argument("URI has not been previously processed");
    }
    double meanValue = this->mean(uri);
    double sd = 0.0;
    for(auto it = range.first; it != range.second; it++) {
        sd += std::pow(it->second - meanValue, 2);
    }
    return std::sqrt(sd / totalMatches);
}


void RequestExtender::buildHistogram(const std::string& uri) { 

}
bool RequestExtender::canBuildHistogram(const std::string& uri) const {
    auto range = m_responseTimes.equal_range(uri);
    int totalMatches = std::distance(range.first, range.second);
    if(totalMatches < 2) {
        return false;
    }
    for(auto it = range.first; it != range.second; it++) {
        if(it->second != range.first->second){
            return true;
        }
    }
    return false;
}

std::vector<double> RequestExtender::fetchHistogram() const {

}


std::string RequestExtender::graphHistogram() const {

}

