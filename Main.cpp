#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string> 

#include "RequestExtenderTester.hpp"
#include "HistogramTester.hpp"
#include "Tester.hpp"

void printTestCases(std::vector<bool> testResults, bool loud, std::string functionName);
void testCaseDriver(bool loud);
int main(int argc, char **argv) {
        
        bool loud = false;
        bool testMode = false;

        for(int i = 1; i < argc; ++i) {
            if(argv[i] == std::string("-t")) {
                testMode = true;
                continue;
            }
            if(argv[i] == std::string("-l")) {
                loud = true;
                continue;
            }
        }
        if(testMode){
            testCaseDriver(loud);
        } else {
            
        }
    return 0;
}
void testCaseDriver(bool loud) {    
        RequestExtenderTester r;
        std::vector<std::string> functionNames;
        functionNames.push_back("RequestExtender::mean(const std::string&)");
        functionNames.push_back("RequestExtender::sd(const std::string&)");
        functionNames.push_back("RequestExtender::canBuildHistogram(const std::string&)");
        functionNames.push_back("Histogram::normalize(double, double, double)");
        functionNames.push_back("Histogram::normalizeDataset(const std::vector<double>&)");
        functionNames.push_back("Histogram::fillBins(const std::vector<double>&)");
        if(loud) {
            std::cout << "Beginning tests: " << std::endl;
        }
        std::cout << std::endl << "Testing: " << functionNames[0] << std::endl;
        printTestCases(r.testMean(), loud, functionNames[0]);
        std::cout << std::endl << "Testing: " << functionNames[1] << std::endl;
        printTestCases(r.testSD(), loud, functionNames[1]);
        std::cout << std::endl << "Testing: " << functionNames[2] << std::endl;
        printTestCases(r.testCanBuildHistogram(), loud, functionNames[2]);
        HistogramTester h;
        std::cout << std::endl << "Testing: " << functionNames[3] << std::endl;
        printTestCases(h.testNormalize(), loud, functionNames[3]);
        std::cout << std::endl << "Testing: " << functionNames[4] << std::endl;
        printTestCases(h.testNormalizeDataset(), loud, functionNames[4]);
        std::cout << std::endl << "Testing: " << functionNames[5] << std::endl;
        printTestCases(h.testFillBins(), loud, functionNames[5]);
 
}

void printTestCases(std::vector<bool> testResults, bool loud, std::string functionName) {
    for(unsigned int i = 0; i < testResults.size(); i++) {
        if(!testResults[i]) {
            std::cout << functionName << " Failed test case: " << i << std::endl;
        } else if(loud) {
            std::cout << functionName << " Passed test case: " << i << std::endl;
        }
    }
}
