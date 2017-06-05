#ifndef ESTADO_HPP
#define ESTADO_HPP

#include "../../message.hpp"

class Estado{
	state_type estado;
	int frame;
public:
	Estado();
	state_type get();
	void setInvencible();
	void set(state_type estado);
	void updateFrame();
	int getFrame();
};

#endif /*ESTADO_HPP*/