#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <GL/glew.h>
class Object {
public:
	Object();
private:
	GLuint m_vaoCube, m_vboCube, m_eboCube;
};
#endif // !__OBJECT_H__