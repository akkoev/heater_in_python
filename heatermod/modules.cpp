#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <ctime>
#include <stdio.h>
#include <iostream>


/* 20-sim submodel class include file */
#include "Heater.h"



namespace py = pybind11;


class HeaterCustom : public Heater {
public:

	/* Initialize wrapper */
	void init(double u)
	{
		u = u + 1;
	}


	/* getTime wrapper */
	double getTime(void) {
		return 1.0;
	}


};

PYBIND11_MODULE(heatermod, m) {

	py::class_<HeaterCustom>(m, "HeaterCustom")
		.def(py::init([]() { return new  HeaterCustom(); }))
		.def("init", &HeaterCustom::Initialize)
		.def("getTime", &HeaterCustom::GetTime);

#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}