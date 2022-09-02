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
    RequestExtender r(3);
    // Test case: 0
    // Test proper exception handling for unprocessed data
    try {
        r.sd("foo");
        testCaseResults.push_back(false);
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(true);
    };

    // Test case: 1
    // Test exception is not thrown for processed data
    r.process("bar");
    try {
        r.sd("bar");
        testCaseResults.push_back(true);
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    };

    // Test case: 2
    // Test exception is not thrown for unprocessed data after other data is processed
    try {
        r.sd("foo");
        testCaseResults.push_back(false);
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(true);
    };
    
    // Test case: 3
    // Test sd calculation with single value
    r.m_responseTimes.insert(std::make_pair("foobar", 10));
    try {
        double meanTime = r.sd("foobar");
        if(meanTime == 0){
            testCaseResults.push_back(true);
        } else {
            testCaseResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    }
    // Test case: 4
    // Test sd calculation with two values
    r.m_responseTimes.insert(std::make_pair("foobar", 0));
    try {
        double meanTime = r.sd("foobar");
        if(meanTime == 5){
            testCaseResults.push_back(true);
        } else {
            testCaseResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    }
    // Test case: 5
    // Test sd calculation with more values
     r.m_responseTimes.insert(std::make_pair("foobar", 0));
     r.m_responseTimes.insert(std::make_pair("foobar", 0));
     r.m_responseTimes.insert(std::make_pair("foobar", 0));

    try {
        double meanTime = r.sd("foobar");
        if(meanTime == 4){
            testCaseResults.push_back(true);
        } else {
            testCaseResults.push_back(false);
        }
    } catch(std::invalid_argument const&) {
        testCaseResults.push_back(false);
    }



    return testCaseResults;
}

std::vector<bool> RequestExtenderTester::testBuildHistogram() {
    RequestExtender r(3);
    std::vector<bool> testCaseResults;
    return testCaseResults;
}
std::vector<bool> RequestExtenderTester::testCanBuildHistogram() {
    RequestExtender r(3);
    std::vector<bool> testCaseResults;

    // Test case: 0
    // Testing result on unprocessed data
    bool result = r.canBuildHistogram("Foo");
    testCaseResults.push_back(!result);

    // Test case: 1
    // Testing result on data with one processing times 
    r.m_responseTimes.insert(std::make_pair("foobar", 10));
    result = r.canBuildHistogram("foobar");
    testCaseResults.push_back(!result);

    // Test case: 2
    // Testing result on data with multiple identical processing times
    r.m_responseTimes.insert(std::make_pair("foobar", 10));
    result = r.canBuildHistogram("foobar");
    testCaseResults.push_back(!result);

    // Test case: 3
    // Testing result on data with multiple identical processing times,
    // and two unique processing times

    r.m_responseTimes.insert(std::make_pair("foobar", 3));
    result = r.canBuildHistogram("foobar");
    testCaseResults.push_back(result);
    
    // Test case: 4
    // Testing result on data with two unique processing times and no
    // identical times 

    r.m_responseTimes.insert(std::make_pair("bar", 3));
    r.m_responseTimes.insert(std::make_pair("bar", 0));
    result = r.canBuildHistogram("bar");
    testCaseResults.push_back(result);

    // Testing result on data with one unique processing value, after
    // multiple unique values for other URIs have been processed 

    result = r.canBuildHistogram("foo");
    testCaseResults.push_back(!result);

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