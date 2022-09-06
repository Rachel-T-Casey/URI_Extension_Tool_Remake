#include "HistogramTester.hpp"
#include "RequestExtender.hpp"
std::vector<bool> HistogramTester::testNormalize() {

    this->clearTestCases();
    //make_shared can't be used because Histogram() is a private class constructor
    RequestExtender::Histogram* histogramPtr = new RequestExtender::Histogram;
    std::function<double (double, double, double)> func = 
        std::bind(&RequestExtender::Histogram::normalize, histogramPtr, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    
    this->testCase(func, true, 0, 0, 0, 0);
    //Test case 1:
    //Minimum greater than maximum
    this->testCase(func, true, 0, 3, 10, 1);
    //Test case 2:
    //Data less than minimum
    this->testCase(func, true, 0, 2, 3, 10);
    //Test case 3:
    //Data greater than maximum
    this->testCase(func, true, 0, 10, 3, 5);
    //Test case 4:
    //Positive data equal to max value
    this->testCase(func, false, 1, 3, 2, 3);
    //Test case 5:
    //Postive data equal to min value
    this->testCase(func, false, 0, 1, 1, 10);
    //Test case 6:
    //Positve data between max and min
    this->testCase(func, false, 0.5, 2, 1, 3);

    delete histogramPtr;
    return this->getTestResults();  
}
std::vector<bool> HistogramTester::testNormalizeDataset() {
    this->clearTestCases();
    //make_shared can't be used because Histogram() is a private class constructor
    RequestExtender::Histogram* histogramPtr = new RequestExtender::Histogram;
     std::function<std::vector<double> (const std::vector<double>)> func = 
        std::bind(&RequestExtender::Histogram::normalizeDataset, histogramPtr, std::placeholders::_1);

    std::vector<double> testInputs;
    std::vector<double> expectedOutputs;
    // Test case 0: Verify exception on empty dataset
    this->testCase(func, true, expectedOutputs, testInputs);
    // Test case 1: Verify exception on dataset with one entry
    testInputs = { 1 };
    this->testCase(func, true, expectedOutputs, testInputs);
    // Test case 2: Two inputs with first greater
    testInputs = { 10, 0 };
    expectedOutputs = { 1, 0 };
    this->testCase(func, false, expectedOutputs, testInputs);
    // Test case 3: Two inputs with first smaller
    testInputs = { 1, 3 };
    expectedOutputs = { 0, 1};
    this->testCase(func, false, expectedOutputs, testInputs);
    // Test case 4: Recurrent minimum, with one larger value
    testInputs = { 1, 1, 10, 1, 1, 1, 1 };
    expectedOutputs = {0, 0, 1, 0, 0, 0, 0};
    this->testCase(func, false, expectedOutputs, testInputs);
    // Test case 5: Recurrent minimum, recurrent maximum, single mid value
    testInputs = { 1, 1, 1, 1, 3, 1, 3, 3, 2};
    expectedOutputs = {0, 0, 0, 0, 1, 0, 1, 1, 0.5 };
    this->testCase(func, false, expectedOutputs, testInputs);

    delete histogramPtr;
    return this->getTestResults();
}
std::vector<bool> HistogramTester::testFillBins() {
     this->clearTestCases();
    //make_shared can't be used because Histogram() is a private class constructor
    RequestExtender::Histogram* histogramPtr = new RequestExtender::Histogram;

    std::function<std::vector<double> (const std::vector<double>&)> func = 
    std::bind(&RequestExtender::Histogram::fillBins, histogramPtr, std::placeholders::_1);

    histogramPtr->m_bins.push_back(0);
    histogramPtr->m_bins.push_back(0);
    std::vector<double> testInputs;
    std::vector<double> expectedOutputs;

    // Test case 0, exception if first value not zero
    testInputs = { 0.1, 0.2, 0.5, 1 };
    this->testCase(func, true, expectedOutputs, testInputs);
    // Test case 1, exception if last value is not zero
    testInputs = { 0, 0.2, 0.4, 0.5 };
    this->testCase(func, true, expectedOutputs, testInputs);
    // Test case 2, two bins with one element each
    histogramPtr->m_bins = {0, 0};
    testInputs = { 0, 1};
    expectedOutputs = {1, 1};
    this->testCase(func, false, expectedOutputs, testInputs);
    // Test case 3, two bins with 5 elements in first, 2 elements in last
    histogramPtr->m_bins = {0, 0};
    testInputs = { 0, 0.1, 0.15, 0.2, 0.49, 0.5, 1};
    expectedOutputs = { 5, 2 };
    this->testCase(func, false, expectedOutputs, testInputs);
    // test case 4, 5 bins with 1 element in first bin, 1 element in last bin
    // and all others in bin 3
    histogramPtr->m_bins = {0, 0, 0, 0, 0};
    testInputs = {0, 0.2, 0.22, 0.25, 0.3, 0.7999, 1};
    expectedOutputs = {1, 4, 0, 1, 1};
    this->testCase(func, false, expectedOutputs, testInputs);
    return this->getTestResults();
}
