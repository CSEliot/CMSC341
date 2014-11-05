#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/classification.hpp>

const bool DEBUG = true;
const char GENERIC_FILTER_LIST[] = "\t \n \r '.!#$%&()*+,./0123456789:;<=>?@[]^_`~{|}\";";

static void printDebug(std::string message){
    if(DEBUG){
        std::cout << message << std::endl;
    }
}

class Util{

public:
    /*Lowers caps of simple strings using boost library.
     * Pre: str using basic ASCII characters, no special chars.
     * Post: all things in lower case.
     */
    static std::string Lower(std::string inString){
        boost::algorithm::to_lower(inString);
        return inString;
    }

    /*Iterates a string through itself and removes any matching cases based on filter list.
     * Pre: Any string of any format.
     * Post: A string that does not contain any of the generic filter list.
     */
    static std::string Strip(std::string inString){
        while(inString.size() != 0 && inString.find('-', 0) == 0){
            inString.erase(0, 1);
        }
        while(inString.size() != 0 && inString.find('-', inString.size()-1) == inString.size()-1){
            inString.erase(inString.size()-1, 1);
        }
        inString.erase(boost::remove_if(inString,
                                        boost::is_any_of(GENERIC_FILTER_LIST)), inString.end());
        return inString;
    }

    /*Checks to make sure file can be read in based on fileName
     * Pre: fileName must contain the name of a file in the working directory
     * Post: True if file can be read, false if not
     */
    static bool FileExists(char* fileName){
        std::ifstream infile;
        infile.open(fileName, std::ios_base::in);

        if(infile.fail()) {
            return false;
        }else {
            infile.close();
            return true;
        }
    }


};

#endif // UTIL_H
