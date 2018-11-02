#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <ctime>
#include <stdio.h>
#include <iostream>


/* 20-sim submodel class include file */
#include "Heater.h"



namespace py = pybind11;

// wrapper to expose methods of Heater to Python such that it accepts numpy.ndarray as input and output
class HeaterWrapper : public Heater {
public:

	/* Initialize wrapper */
	void init(py::array_t<double> u)
	{
		/* read input arrays buffer_info */
		py::buffer_info bufu = u.request();
		if (bufu.size != 3)
			throw std::runtime_error("Input shape must be 3");

		/* pointer to buffer */
		double *ptru = (double *)bufu.ptr;

		XXDouble y[11 + 1] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		XXDouble t = 0.0;

		Heater::Initialize(ptru, y, t);
	}


	/* getTime wrapper */
	double getTime(void) {
		return Heater::m_time;
	}


	/* wrapper to calculate large time step */
	py::array_t<double> calc(py::array_t<double> u, py::array_t<double> dt)
	{
		/* read input arrays buffer_info */
		py::buffer_info bufu = u.request();    // 3 element intput vector
		if (bufu.size != 3)
			throw std::runtime_error("Input shape for u must be 3");

		py::buffer_info bufdt = dt.request();    // 1 element intput vector
		if (bufdt.size != 1)
			throw std::runtime_error("Input shape for dt must be 1");

		/* allocate the output buffer */
		py::array_t<double> y = py::array_t<double>(11);  //11 element output vector
		py::buffer_info bufy = y.request();

		/* pointer to buffers */
		double *ptru = (double *)bufu.ptr;
		double *ptrdt = (double *)bufdt.ptr;
		double *ptry = (double *)bufy.ptr;


		/* Variable used as input for Heater::Calculate() 		*/
		XXDouble uu[3 + 1];
		XXDouble yy[11 + 1];

		/* Copy numpy input vector to input vector for Heater::Calculate */
		uu[0] = ptru[2]; /* dm_water {kg/s} */
		uu[1] = ptru[0]; /* P_natural_gas {W} */
		uu[2] = ptru[1]; /* Tin */


		if (state == Heater::finished)
		{
			state = Heater::mainrun;
		}

		m_finish_time = m_time + ptrdt[0]; // set finish time

		while (state != Heater::finished)
		{
			Calculate(uu, yy);
		}

		/* Copy output yy to vector which will be returned to python */
		/* Note that the order of variables can change when updating the 20-sim model*/
		ptry[10] = yy[0];  // P_actual {W}
		ptry[5] = yy[1];   // TSteel1 {K}
		ptry[6] = yy[2];   // TSteel2 {K}
		ptry[7] = yy[3];   // TSteel3 {K}
		ptry[8] = yy[4];   // TSteel4 {K}
		ptry[9] = yy[5];   // TSteel5 {K}
		ptry[0] = yy[6];   // TWater1 {K}
		ptry[1] = yy[7];   // TWater2 {K}
		ptry[2] = yy[8];   // TWater3 {K}
		ptry[3] = yy[9];   // TWater4 {K}
		ptry[4] = yy[10];  // TWater5 {K}

		return y;
	}




};


PYBIND11_MODULE(heatermod, m) {

	py::class_<HeaterWrapper>(m, "Heater")
		.def(py::init([]() { return new HeaterWrapper(); }))
		.def("init", &HeaterWrapper::init)
		.def("calc", &HeaterWrapper::calc)
		.def("getTime", &HeaterWrapper::getTime);

#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}