// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// TileException.h
// TileException is an exception that is thrown when there's a problem with
// the configuration of a tile.
//
// Author: Sytten
// Creation date: 09/03/2013
// Last modification date: 09/03/2013
// ---------------------------------------------------------------------------

#ifndef TILEEXCEPTION_H
#define TILEEXCEPTION_H

#include <exception>
#include <sstream>

class TileException : public std::exception
{
    public:
        // In the constructor we create the message
            TileException(int tileID)
            {
                std::ostringstream oss;
                oss << "A problem occurred with the tile number " << tileID << ". Check in the configuration file to correct the error.";
                this->m_msg = oss.str();

            }
        // Virtual destructor
            virtual ~TileException() throw()
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

#endif // TILEEXCEPTION_H
