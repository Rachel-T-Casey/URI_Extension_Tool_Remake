#include <iostream>
#include <vector>
#include "RequestExtenderTester.hpp"
#include "HistogramTester.hpp"
void requestExtenderTestDriver();
void histogramTestDriver();
int main(int argc, char const *argv[]){
    requestExtenderTestDriver();
    histogramTestDriver();
    return 0;
}

void requestExtenderTestDriver() {
    std::cout << "Beginning tests on request extender" << std::endl;
    RequestExtenderTester R;
    std::vector<bool> testResults;
    testResults = R.testMean();
    std::cout << "Beginning tests on mean()" << std::endl;
    for(unsigned int i = 0; i < testResults.size(); i++){
        if(!testResults[i]) {
            std::cout << "Failed test case: " << i << std::endl;
        }
        else {
            std::cout << "Passed test case: " << i << std::endl;
        }
    }

    std::cout << "Beginning tests on sd()" << std::endl;
    testResults = R.testSD();
    for(unsigned int i = 0; i < testResults.size(); i++){
        if(!testResults[i]) {
            std::cout << "Failed test case: " << i << std::endl;
        }
        else {
            std::cout << "Passed test case: " << i << std::endl;
        }
    }
    std::cout << "Beginning tests on canBuildHistogram()" << std::endl;
    testResults = R.testCanBuildHistogram();
    for(unsigned int i = 0; i < testResults.size(); i++){
        if(!testResults[i]) {
            std::cout << "Failed test case: " << i << std::endl;
        }
        else {
            std::cout << "Passed test case: " << i << std::endl;
        }
    }
}


void histogramTestDriver() {
    std::cout << "Starting tests on histogram" << std::endl;
    HistogramTester H;
    std::vector<bool> testResults;
    std::cout << "Starting test on normalize()" << std::endl;
    testResults = H.testNormalize();
    for(unsigned int i = 0; i < testResults.size(); i++) {
        if(testResults[i]) {
            std::cout << "Passed test case: " << i << std::endl;
        } else {
            std::cout << "Failed test case: " << i << std::endl;
        }
    }
    /*
    H.testNormalizeDataset();
    H.testFillBins();
    H.testBins();
    H.testBinSize();
    H.testHistogram();
    */
}

