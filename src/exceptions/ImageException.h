// ---------------------------------------------------------------------------
// This software is in the public domain, furnished "as is", without technical
// support, and with no warranty, express or implied, as to its usefulness for
// any purpose.
//
// ImageException.h
// ImageException is an exception that is thrown when image can't be loaded.
//
// Author: Sytten
// Creation date: 05/01/2013
// Last modification date: 26/01/2013
// ---------------------------------------------------------------------------

#ifndef IMAGEEXCEPTION_H
#define IMAGEEXCEPTION_H

#include <exception>
#include <sstream>

class ImageException : public std::exception
{
    public:
        // In the constructor we create the message
            ImageException(std::string imageName)
            {
                std::ostringstream oss;
                oss << "The image " << imageName << " cannot be loaded. Make sure it's in the data folder.";
                this->m_msg = oss.str();

            }
        // Virtual destructor
            virtual ~ImageException() throw()
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

#endif // IMAGEEXCEPTION_H
