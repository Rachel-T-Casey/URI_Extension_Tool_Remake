#ifndef REQUEST_EXTENSION_HPP
#define REQUEST_EXTENSION_HPP

#include "Request.hpp"

#include <string>       // std::string
#include <map>          // std::multimap
#include <chrono>       // std::chrono 
#include <stdexcept>    // std::invalid_argument 
#include <vector>       // std::vector
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
* Passing a URI to mean() will return the mean response time for the URI in ms provided
* the uri has been processed at least once. An exception is thrown for any invalid URIs
* 
* Passing a URI to sd() will return the standard deviation for the URI in ms provided 
* the uri has been processed at least once. An exception is thrown for any invalid URIs
* 
* Passing a URI to buildHistogram() will construct a local normalized histogram object
* which provides additional statistical information for the response times by normalizing 
* processing times for the respective URI, and mapping the normalized values across a specified
* number of bins. The passed URI must have been processed with at least two unique measurements, 
* otherwise an exception will be thrown
*  
* Passing a URI to canBuildHistogram() will return a boolean indicating whether a histogram
* can be constructed using the passed URI
* 
* Calling fetchHistogram() will return a copy of all the bins of the local histogram, provided
* that a histogram has been built with the buildHistogram() function. If no histogram has been
* built, an exception will be thrown. The bins are represented  by the indexes of a 
* std::vector<double>, with the value stored at each index representing the  number of data 
* points stored in the respective bin. 
* 
* Calling graphHistogram() will return a string which visually represents the contents of the
* local histogram, provided that a histogram has been built with the buildHistogram() function.
* If no histogram has been built an exception will be thrown.
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
         * Given a uri which has been processed previously, with at least two unique
         * response times, creates a local histogram object which is used for the 
         * graph() and getHistogram() functions
         *
         * @see Histogram
         * @param [in] uri A URI which has been previously passed to process(uri), with
         * at least two unique logged response times
         * @throws std::invalid_argument if there are not at least two unique response times
         * for the specified uri
        */
        //void buildHistogram(std::string& uri) const;

        /**
         * Returns whether a specified uri is a valid uri for histogram creation.
         * 
         * @param [in] Any uri
         * @returns a Boolean value representing whether the passed URI is currently a valid
         * uri for histogram creation. Valid URIs must have had at least two process time 
         * measurements from the process() function.
        */ 
        bool canBuildHistogram(std::string& uri) const;
        /**
         * Returns the bins of the last histogram constructed byt he buildHistogram()
         * function. This function must only be called after a histogram is successfully 
         * constructed using buildHistogram()
         * 
         * @see buildHistogram()
         * @throws std::logic_error() if the local histogram object has not been initalized from
         * calling the buildHistogram() function prior to function execution
         * @returns A normalized dataset with values between 0 and 1 stored in a vector of doubles
         * with indexes of the vector representing cells of the normalized histogram.
        */ 
        std::vector<double> fetchHistogram() const; 

        /** 
         * Returns a string which visually represents the last histogram constructed 
         * by the buildHistogram() function. This function must only be called after a histogram
         * is successfully constructed using buildHistogram
         *
         * @see buildHistogram()
         * @throws std::logic_error() if the local histogram has not been initalized from calling
         * the buildHistogram() function prior to function execution
         * @returns A string which visually represents the last normalized histogram constructed
         * This string uses Unix line feed terminations ('\n').
        */ 
        std::string graphHistogram() const;

    private:

     /**
        * A Histogram read-only datastructure class
        *
        * Instantiations of this class will normalize the provided dataset, and store the
        * normalized data in a vector with a number of cells equal to the provided bincount.
        * 
        * To use, instantiate an object passing an vector of data, as well as the number of bins
        * the data should be stored in. The number of bins must be at least two, and the number
        * of unique values in the dataset must be at least two. 
        * 
        * After instantiaton, the following read-only functions can be used to obtain information
        * about the stored data:
        *   bins() Will return a copy of the vector that the data is sorted in.
        *   binSize() Will return the size of the range of data each bin occupies.
        */    
    class Histogram {         
        public:
            /**
            * Takes in a dataset, normalizes the dataset, and stores the normalized dataset
            * in a vector amongst a number of indices equal to passed binCount in the form
            * of a normalized histogram
            * 
            * @param [in] dataSet Data from a dataset with at least two unique values.
            * @param [in] binCount The number of bins the outputted histogram should contain.
            * binCount must be at least two.
            * @throws std::invalid_arguement if the number of unique values in the dataset is
            * less than two
            * @throws std::invalid_argument if the number of bins is less than two
            */
            Histogram(const std::vector<double>& dataSet, unsigned int binCount);
            /**
            * Returns a copy of the bins vector
            * @return A copy of the vector of bins for the histogram. This vector will 
            * always contain at least two bins, and no more than UINT_MAX bins. 
            */
            std::vector<double> bins() const;
            /**
            * Returns the size of the range of each bin. For instance, if the histogram
            * contains ten bins, this will return 0.1, whereas if the histogram contains 4
            * bins this will return 0.25. The size of each bin will always be between 1/2 and
            * 1/UINT_MAX 
            *
            * @returns Returns a value between 1/2 and 1/UINT_MAX which is size of the range
            * of values each bin stores.
            */
            double binSize() const;
        private:
            /**
            * Given data from a dataset, as well as the minimum and maximum datapoints
            * from the same dataset, returns a normalized value for the passed data 
            * between 0 and 1. The dataset must contain at least two unique values.
            * 
            * @param [in] data A value from a dataset of doubles
            * @param [in] min The minimum value in the respective dataset
            * @param [in] max The maximum value in the respective dataset
            * @returns The normalized value for data between 0 and 1
            * @throws std::invalid_argument if min is >= than max
            * @throws std::invalid_argument if max is <= min
            * @throws std::invalid_argument if data < min
            * @throws std::invalid_argument if data > max
            */
            double normalize(double data, double min, double max) const;
            /**
            * Passes all values from a dataset to normalize(), and builds a vector 
            * containing the returned normalized data. Then, returns the vector 
            * containing the normalized dataset. This dataset must contain at least
            * two unique values.
            * 
            * @see normalize(double,double,double) const
            * @param [in] data A dataset with a minimum of two unique values.
            * @return A vector containing normalized values between 0 and 1 generated 
            * from the respective dataset.
            */
            std::vector<double> normalizeDataset(const std::vector<double>& data) const;
            /**
            * Given a normalized dataset with values between 0 and 1, constructs a 
            * normalized histogram with a number of cells equal the value binCount 
            * passed to this object during instantiation. Each index in m_bins will
            * be set equal to the number of datapoints located in the respective cell
            * of the histogram. 
            * 
            * @param [in] A sorted normalized dataset containing values between 0 and 1 
            * with the minimum value being 0 and the maximum value being 1.
            * @throws std::invalid_argument if the minimum value in the dataset is < 0
            * @throws std::invalid_argument if the maximum value in the dataset is > 1
             */
            void fillBins(std::vector<double>& normalizedData);
            std::vector<double> m_bins;
    };
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
        Histogram* m_histogramPtr;
       
};
#endif