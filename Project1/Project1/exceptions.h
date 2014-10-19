/**************************************************************
 * File:    exceptions.h
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Austin Pagano
 * Date   : 10/15/14
 * Section: 02
 * E-mail:  apagano1@umbc.edu
 *
 * exceptions class header file
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