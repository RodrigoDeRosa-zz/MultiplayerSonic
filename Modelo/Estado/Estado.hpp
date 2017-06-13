#ifndef ESTADO_HPP
#define ESTADO_HPP

#include "../../message.hpp"

class Estado{
	state_type estado;
	int frame, frameSum;
public:
	Estado();
	state_type get();
	void setInvencible();
	void set(state_type estado);
	void updateFrame();
	int getFrame();
	bool recibirGolpe();
};

#endif /*ESTADO_HPP*/
