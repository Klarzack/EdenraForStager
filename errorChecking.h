#include <iostream>
#include <GL/glew.h> // Adjust your include based on your environment

#define CHECK_GL_ERROR() \
    do { \
        GLenum err = glGetError(); \
        while (err != GL_NO_ERROR) { \
            std::cerr << "OpenGL error in " << __FILE__ << ":" << __LINE__ << ": " << err << std::endl; \
            err = glGetError(); \
        } \
    } while (false)


//		CHECK_GL_ERROR();  will tell u on which line the error is, simply call this function after each OpenGL call that u suspect is wrong