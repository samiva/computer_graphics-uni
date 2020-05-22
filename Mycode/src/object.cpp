#include "../include/object.h"
#include "GL/glew.h"

GLuint Object::idCounter = 0;

Object::Object() {
    m_id = idCounter;
    idCounter++;    
}

 Object::~Object() {}


