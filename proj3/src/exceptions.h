/**************************************************************
 * File:    exceptions.h
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Eliot Carney-Seim
 * Date  Due: 10/21/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * The Exceptions class heder file
 *
 *************************************************************/

#include <iostream>
#include <stdlib.h>

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <string>

class Exceptions {
public:
    /**********************************************************************
     * Name: MyExceptions (Constructor)
     * PreCondition: String containing error description.  
     * 
     * PostCondition:  Error object
     *********************************************************************/
    Exceptions(std::string message): m_message(message) {}

    /**********************************************************************
     * Name: GetMessage
     * PreCondition: None.  
     * 
     * PostCondition:  Returns error message.
     *********************************************************************/
    const std::string GetMessage() { return m_message; }
    
private:
    
    std::string m_message; //Error message.
};

#endif
