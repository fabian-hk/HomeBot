#include <boost/python.hpp>

#include "Scraper.h"



BOOST_PYTHON_MODULE(libwebscraper) {
    // Add regular functions to the module.
    using namespace boost::python;
    def("scraper", scraper);
}