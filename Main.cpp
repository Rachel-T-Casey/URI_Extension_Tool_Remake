#include <iostream>
#include <vector>
#include "RequestExtenderTester.hpp"
#include "HistogramTester.hpp"
void requestExtenderTestDriver();
void histogramTestDriver();
void printTestCases(std::vector<bool> testResults);
int main(int argc, char const *argv[]){
    requestExtenderTestDriver();
    histogramTestDriver();
    return 0;
}

void requestExtenderTestDriver() {
    
    std::cout << "Beginning tests on request extender" << std::endl;
    RequestExtenderTester R;
    std::vector<bool> testResults;
    
    std::cout << "Beginning tests on mean()" << std::endl;
    testResults = R.testMean();
    printTestCases(testResults);
    
    std::cout << "Beginning tests on sd()" << std::endl;
    testResults = R.testSD();
    printTestCases(testResults);
   
    std::cout << "Beginning tests on canBuildHistogram()" << std::endl;
    testResults = R.testCanBuildHistogram();
    printTestCases(testResults);
}


void histogramTestDriver() {
    
    std::cout << "Starting tests on histogram" << std::endl;
    
    HistogramTester H;
    std::vector<bool> testResults;
    
    std::cout << "Starting test on normalize()" << std::endl;
    testResults = H.testNormalize();
    printTestCases(testResults);

    std::cout << "Starting test on normalizeDataset()" << std::endl;
    testResults = H.testNormalizeDataset();
    printTestCases(testResults);
    /*
    H.testNormalizeDataset();
    H.testFillBins();
    H.testBins();
    H.testBinSize();
    H.testHistogram();
    */
}
void printTestCases(std::vector<bool> testResults) {
    for(unsigned int i = 0; i < testResults.size(); i++) {
        if(testResults[i]) {
            std::cout << "Passed test case: " << i << std::endl;
        } else {
            std::cout << "Failed test case: " << i << std::endl;
        }
    }
}
