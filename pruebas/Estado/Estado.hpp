#ifndef ESTADO_HPP
#define ESTADO_HPP

#include "message.hpp"

class Estado{
	state_type estado;
public:
	Estado();
	state_type get();
	void set(state_type estado);
};

#endif /*ESTADO_HPP*/