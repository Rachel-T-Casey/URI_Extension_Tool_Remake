#include "RequestExtenderTester.hpp"

#include <stdexcept>  

std::vector<bool> RequestExtenderTester::testMean() {
    RequestExtender r(3);
    std::vector<bool> testCaseResults;

    // Test case: 0
    // Test proper exception handling for unprocessed data
    try {
        r.mean("foo");
        testCaseResults.push_back(false);
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(true);
    };

    // Test case: 1
    // Test exception is not thrown for processed data
    r.process("bar");
    try {
        r.mean("bar");
        testCaseResults.push_back(true);
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    };

    // Test case: 2
    // Test exception is not thrown for unprocessed data after other data is processed
    try {
        r.mean("foo");
        testCaseResults.push_back(false);
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(true);
    };
    // Test case: 3
    // Test mean calculation with single value
    r.m_responseTimes.insert(std::make_pair("foobar", 0));
    try {
        double meanTime = r.mean("foobar");
        if(meanTime == 0){
            testCaseResults.push_back(true);
        } else {
            testCaseResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    }
    // Test case: 4
    // Test mean calculation with multiple values
    r.m_responseTimes.insert(std::make_pair("foobar", 1));
    try {
        double meanTime = r.mean("foobar");
        if(meanTime == 0.5){
            testCaseResults.push_back(true);
        } else {
            testCaseResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    }
    // Test case: 5
    // Test mean calculation with more values
    r.m_responseTimes.insert(std::make_pair("foobar", 2.5));
    r.m_responseTimes.insert(std::make_pair("foobar", 1));
    r.m_responseTimes.insert(std::make_pair("foobar", 1));
    try {
        double meanTime = r.mean("foobar");
        if(meanTime == 1.1){
            testCaseResults.push_back(true);
        } else {
            testCaseResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    }

    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testSD() {
    std::vector<bool> testCaseResults;
    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testBuildHistogram() {
    std::vector<bool> testCaseResults;
    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testCanBuildHistogram() {
    std::vector<bool> testCaseResults;
    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testFetchHistogram() {
    std::vector<bool> testCaseResults;
    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testGraphHistogram() {
    std::vector<bool> testCaseResults;
    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testRequestExtender() {
    std::vector<bool> testCaseResults;
    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testAll() {
    std::vector<bool> testCaseResults;
    return testCaseResults;
}