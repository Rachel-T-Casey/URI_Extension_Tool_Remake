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

    // Test case 4: SD calculation with two values
    requestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 0));
    this->testCase(funct, false, 5, "foobar");

    // Test case 5: SD calculation with more values
    requestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 0));
    requestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 0));
    requestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 0));
    this->testCase(funct, false, 4, "foobar");

    return this->getTestResults();
}

std::vector<bool> RequestExtenderTester::testCanBuildHistogram() {
    std::vector<bool> testCaseResults;
    this->clearTestCases();
    auto RequestExtenderPtr = std::make_shared<RequestExtender>(3);
    std::function<bool (std::string)> funct = 
        std::bind(&RequestExtender::canBuildHistogram, RequestExtenderPtr, std::placeholders::_1);

    // Test case: 0
    // Testing result on unprocessed data
    this->testCase(funct, false, false, "Foo");

    // Test case: 1
    // Testing result on data with one processing time
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 10));
    this->testCase(funct, false, false, "foobar");

    // Test case: 2
    // Testing result on data with multiple identical processing times
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 10));
    this->testCase(funct, false, false, "foobar");

    // Test case: 3
    // Testing result on data with multiple identical processing times,
    // and two unique processing times

    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("foobar", 3));
    this->testCase(funct, false, true, "foobar");
    
    // Test case: 4
    // Testing result on data with two unique processing times and no
    // identical times 

    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("bar", 3));
    RequestExtenderPtr->m_responseTimes.insert(std::make_pair("bar", 0));
    this->testCase(funct, false, true, "foobar");

    // Test case: 5
    // Testing result on data with one unique processing value, after
    // multiple unique values for other URIs have been processed 
    this->testCase(funct, false, false, "foo");
    return this->getTestResults();
}

