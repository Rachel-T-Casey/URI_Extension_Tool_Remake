#include "HistogramTester.hpp"
#include "RequestExtender.hpp"
std::vector<bool> HistogramTester::testNormalize() {
    std::vector<bool> testResults;
    //Test case: 0
    //Test min == max
    RequestExtender::Histogram h;
    try { 
        h.normalize(0, 0, 0);
        testResults.push_back(false);
    } catch(std::invalid_argument const&) {
        testResults.push_back(true);
    }
    //Test case 1:
    //Minimum greater than maximum
    try {
        h.normalize(3, 10, 1);
        testResults.push_back(false);
    } catch(std::invalid_argument const&) {
        testResults.push_back(true);
    }
    //Test case 2:
    //Data less than minimum
    try {
        h.normalize(2, 3, 10);
        testResults.push_back(false);
    }   catch(std::invalid_argument const&) {
        testResults.push_back(true);
    }
    //Test case 3:
    //Data greater than maximum
    try {
        h.normalize(10, 3, 5); 
        testResults.push_back(false);
    }   catch(std::invalid_argument const&) {
        testResults.push_back(true);
    }
    //Test case 4:
    //Positive data equal to max value
    try {
        double result = h.normalize(3, 2, 3);
        if(result == 1){
            testResults.push_back(true);
        }
        else {
            testResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testResults.push_back(false);
    }
    //Test case 5:
    //Postive data equal to min value
    try {
        double result = h.normalize(1, 1, 10);
        if(result == 0) {
            testResults.push_back(true);
        }
        else {
            testResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testResults.push_back(false);
    }
    //Test case 6:
    //Positve data between max and min
    try {
        double result = h.normalize(2, 1, 3);
        if(result == 0.5) {
            testResults.push_back(true);
        }
        else {
            testResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testResults.push_back(false);
    }
    // Possibly should expand test coverage to cover negative values. While negative
    // values should never be encountered in the scope of this program, negative values
    // would result in unexpected values
    return testResults;
}
std::vector<bool> HistogramTester::testNormalizeDataset() {
    std::vector<bool> testResults;
    return testResults;
}
std::vector<bool> HistogramTester::testFillBins() {
    std::vector<bool> testResults;
    return testResults;
}
std::vector<bool> HistogramTester::testBins() {
    std::vector<bool> testResults;
    return testResults;
}
std::vector<bool> HistogramTester::testBinSize() {
    std::vector<bool> testResults;
    return testResults;
}
std::vector<bool> HistogramTester::testHistogram() {
    std::vector<bool> testResults;
    return testResults;
}
std::vector<bool> HistogramTester::testAll() {
    std::vector<bool> testResults;
    return testResults;
}