#include "RequestExtenderTester.hpp"
#include <stdexcept>  

std::vector<bool> RequestExtenderTester::testMean() {
    this->clearTestCases();
    auto RequestExtenderPtr = std::make_shared<RequestExtender>(3);
    std::function<double (std::string)> funct = 
        std::bind(&RequestExtender::mean, RequestExtenderPtr, std::placeholders::_1);
 
    //Test case 0: Throwing exception for unparsed data
    this->testCase(funct, true, 0,"foo");
    
    //Test case 1: No exception thrown for parsed data
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("bar", 0));
    this->testCase(funct, false, 0,"bar");
   
    // Test case 2: Exceptions thrown for unprocessed data after other
    // data has been processed
    this->testCase(funct, true, 0, "foo");
   
    // Test case 3: Test mean calculation for single value
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 0));
    this->testCase(funct, false, 0, "foobar");
   
    // Test case 4: Test mean calculation with multiple values
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 1));
    this->testCase(funct, false, 0.5, "foobar");
    
    // Test case 5: Test mean calculation with more values
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 2.5));
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 1));
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 1));
    this->testCase(funct, false, 1.1, "foobar");

    return this->getTestResults();
}
std::vector<bool> RequestExtenderTester::testSD() {
    this->clearTestCases();
    auto requestExtenderPtr = std::make_shared<RequestExtender>(3);
    std::function<double (std::string)> funct = 
        std::bind(&RequestExtender::sd, requestExtenderPtr, std::placeholders::_1);

    // Test case: 0 Proper exception handling for unprocessed data
    this->testCase(funct, true, 0, "foo");
    // Test case 1: No exception thrown for processed data
    requestExtenderPtr->m_responseTimes.insert(std::make_pair("bar", 0));
    this->testCase(funct, false, 0, "bar");
    // Test case 2: Proper exception handlng after other data has been processed
    this->testCase(funct, true, 0, "foo");
    // Test case 3: SD calculation with single value
    requestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 10));
    this->testCase(funct, false, 0, "foobar");
    return this->getTestResults();
    /*

    
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


    */

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

    // Test case: 5
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