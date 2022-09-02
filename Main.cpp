#include <iostream>
#include <vector>
#include "RequestExtenderTester.hpp"
void requestExtenderTestDriver();
int main(int argc, char const *argv[]){
    requestExtenderTestDriver();
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
            std::cout << "testMean() failed test case: " << i << std::endl;
        }
        else {
            std::cout << "testMean() passed test case: " << i << std::endl;
        }
    }

    std::cout << "Beginning tests on sd()" << std::endl;
    testResults = R.testSD();
    for(unsigned int i = 0; i < testResults.size(); i++){
        if(!testResults[i]) {
            std::cout << "testSD() failed test case: " << i << std::endl;
        }
        else {
            std::cout << "testSD() passed test case: " << i << std::endl;
        }
    }


}