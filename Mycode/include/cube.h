#ifndef __CUBE_H__
#define __CUBE_H__
#include "object.h"
class Cube : public Object 
{
public:

	// Inherited via Object
	virtual void create() override;
	virtual void bind() override;
	virtual void unbind() override;
	virtual void update(float dt) override;

protected:
	void updateModel();
};
#endif // !__CUBE_H__