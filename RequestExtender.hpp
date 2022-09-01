#ifndef REQUEST_EXTENSION_HPP
#define REQUEST_EXTENSION_HPP

#include "Request.hpp"

#include <string>       // std::string
#include <map>          // std::multimap
#include <chrono>       // std::chrono 
#include <stdexcept>    // std::invalid_argument 


/**
* Resource request processing extension class
*
* Instatiations of this class extends state based processing of resource requests
* by logging processing times, and providing statistical anaylsis on processing times.
* 
* To use, instantiate an object and call process() on a URI to get the response
* data. After processing a URI you can access a variety of statistical information
* by passing the URI to the respective statistical functions.
* 
* Passing a URI to mean() will return the mean response time for the URI in ms
* Passing a URI to sd() will return the standard deviation for the URI in ms
* Passing a URI to histogram() will return a histogram object which provides additional
* statistical information. 
* 
*/

class RequestExtender : public Request
{
    public:

        /** 
         * Given a uri which has been processed previously, returns the mean response
         * time for the respective uri
         * 
         * @param [in] uri A URI which has been previously passed to process(uri)
         * @throws std::invalid_argument if the uri has not been previously processed
         * @return The mean processing time for the provided URI in millisecond unit

        */
        double mean(const std::string& uri) const;
        /** 
         * Given a uri which has been processed previously, returns the standard deviation
         * between responses for the respective uri
         * 
         * @param [in] uri A URI which has been previously passed to process(uri)
         * @throws std::invalid_argument if the uri has not been previously processed
         * @return The standard deviation between processing times for the provided
         * uri in millisecond units
        */
        double sd(const std::string& uri) const;
        /** 
         * Given a uri which has been processed previously, returns a histogram object
         * which provides several methods for statistical analysis
         *
         * @see Histogram
         * @param [in] uri A URI which has been previously passed to process(uri)
         * @throws std::invalid_argument if the uri has not been previously processed 
         * @return A histogram object which provides a variety of statistical analysis
         * methods for the processing time on the specified uri
        */

        //Histogram histogram(std::string& uri) const;

    private:

        /**
        * Records the current time, and copies the passed uri to prepare the finish()
        * function.
        * 
        * @param [in] uri A URI which is being processed by the process() function
        */
        void start(const std::string& uri);
        /** 
        * Calculates the difference between the current time, and the recorded time 
        * from the start() function. This value is then stored in a multimap with 
        * the uri passed to the start() function as the key. 
        *
        * @throws std::logic_error if no startTime, or no uri name is recorded from
        * the start() function
        */
        void finish();

        std::chrono::time_point<std::chrono::steady_clock> m_startTime;
        std::multimap<std::string, double> m_responseTimes;
};

#endif