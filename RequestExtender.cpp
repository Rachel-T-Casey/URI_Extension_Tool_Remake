#include "RequestExtender.hpp"


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
    int timePassedInt = timePassed.count();
    m_responseTimes.insert({m_uriKey, timePassedInt});
}

double RequestExtender::mean(const std::string& uri) const {

}

double RequestExtender::sd(const std::string& uri) const {
}

void RequestExtender::buildHistogram(const std::string& uri) { 
}
bool RequestExtender::canBuildHistogram(const std::string& uri) const {

}

std::vector<double> RequestExtender::fetchHistogram() const {

}


std::string RequestExtender::graphHistogram() const {

}

