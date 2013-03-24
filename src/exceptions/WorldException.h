// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// WorldException.h
// WorldException is an exception that is thrown when there's a problem with
// world's configuration file.
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef WORLDEXCEPTION_H
#define WORLDEXCEPTION_H

#include <exception>
#include <sstream>

class WorldException : public std::exception
{
    public:
        // In the constructor we create the message
            WorldException(int line)
            {
                std::ostringstream oss;
                oss << "A problem occurred at line " << line << " in the world configuration file's. Check if it's more than 100%.";
                this->m_msg = oss.str();

            }
        // Virtual destructor
            virtual ~WorldException() throw()
            {
            }

        // Return the message so we can display it
            virtual const char * what() const throw()
            {
                return this->m_msg.c_str();
            }

    private:
        std::string m_msg;
};

#endif // WORLDEXCEPTION_H
