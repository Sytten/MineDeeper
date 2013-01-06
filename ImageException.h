#ifndef IMAGEEXCEPTION_H
#define IMAGEEXCEPTION_H

#include <exception>
#include <sstream>

class ImageException : public std::exception
{
    public:
        ImageException(std::string imageName)
        {
            std::ostringstream oss;
            oss << "The image " << imageName << " cannot be loaded! Make sure it's in the same directory as Minedeeper.exe";
            this->m_msg = oss.str();

        }

        virtual ~ImageException() throw()
        {

        }

        virtual const char * what() const throw()
        {
            return this->m_msg.c_str();
        }

    private:
        std::string m_msg;
};

#endif // IMAGEEXCEPTION_H
