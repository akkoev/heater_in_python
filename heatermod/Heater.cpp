/**********************************************************
 * This file is generated by the 20-sim C++ Code Generator
 *
 *  file:  Heater.cpp
 *  subm:  Heater
 *  model: heater
 *  expmt: heater
 *  date:  November 1, 2018
 *  time:  5:48:32 PM
 *  user:  Johannes Burger
 *  from:  Cooll Sustainable Energy Solutions BV, 20-sim 4.7 Professional Single
 *  build: 4.7.1.8902
 **********************************************************/

/* Standard include files */
#include <stdio.h>
#include <math.h>
/* Include the header for memcpy and memset
 * You may need to change this into <memory.h> for older compilers
 */
#include <string.h>

/* 20-sim include files */
#include "Heater.h"

/* Delta margin used for end time checking */
const XXDouble c_delta = 1.0e-7;

/* this PRIVATE function sets the input variables from the input vector */
void Heater::CopyInputsToVariables (XXDouble *u)
{
	/* copy the input vector to the input variables */
	m_V[210] = u[0];		/* dm_water {kg/s} */
	m_V[221] = u[1];		/* P_natural_gas {W} */
	m_V[223] = u[2];		/* Tin */

}

/* this PRIVATE function uses the output variables to fill the output vector */
void Heater::CopyVariablesToOutputs (XXDouble *y)
{
	/* copy the output variables to the output vector */
	y[0] = 	m_V[222];		/* P_actual {W} */
	y[1] = 	m_V[211];		/* TSteel1 {K} */
	y[2] = 	m_V[213];		/* TSteel2 {K} */
	y[3] = 	m_V[215];		/* TSteel3 {K} */
	y[4] = 	m_V[217];		/* TSteel4 {K} */
	y[5] = 	m_V[219];		/* TSteel5 {K} */
	y[6] = 	m_V[212];		/* TWater1 {K} */
	y[7] = 	m_V[214];		/* TWater2 {K} */
	y[8] = 	m_V[216];		/* TWater3 {K} */
	y[9] = 	m_V[218];		/* TWater4 {K} */
	y[10] = 	m_V[220];		/* TWater5 {K} */

}

Heater::Heater(void)
{
	m_number_constants = 2;
	m_number_parameters = 41;
	m_number_initialvalues = 22;
	m_number_variables = 224;
	m_number_states = 22;
	m_number_rates = 22;
	m_number_matrices = 22;
	m_number_unnamed = 0;

	/* the variable arrays */
	m_C = new XXDouble[2 + 1];		/* constants */
	m_P = new XXDouble[41 + 1];		/* parameters */
	m_I = new XXDouble[22 + 1];		/* initial values */
	m_V = new XXDouble[224 + 1];		/* variables */
	m_s = new XXDouble[22 + 1];		/* states */
	m_R = new XXDouble[22 + 1];		/* rates (or new states) */
	m_M = new XXMatrix[22 + 1];		/* matrices */
	m_U = new XXDouble[0 + 1];		/* unnamed */
	m_workarray = new XXDouble[0 + 1];

	Reset(0.0);
	m_finish_time = 1000.0;
}

void Heater::Reset(XXDouble starttime)
{
	m_start_time = starttime;
	m_step_size = 0.002;
	m_time = starttime;
	m_major = true;
	m_stop_run = false;

	/* Clear the allocated variable memory */
	memset(m_C, 0, (2 + 1) * sizeof(XXDouble));
	memset(m_P, 0, (41 + 1) * sizeof(XXDouble));
	memset(m_I, 0, (22 + 1) * sizeof(XXDouble));
	memset(m_V, 0, (224 + 1) * sizeof(XXDouble));
	memset(m_s, 0, (22 + 1) * sizeof(XXDouble));
	memset(m_R, 0, (22 + 1) * sizeof(XXDouble));
	memset(m_M, 0, (22 + 1) * sizeof(XXDouble));
	memset(m_U, 0, (0 + 1) * sizeof(XXDouble));
	memset(m_workarray, 0, (0 + 1) * sizeof(XXDouble));


	state = initialrun;
}

bool Heater::IsFinished(void)
{
	return (state == finished);
}

Heater::~Heater(void)
{
	/* free memory */
	delete[] m_C;
	delete[] m_P;
	delete[] m_I;
	delete[] m_V;
	delete[] m_s;
	delete[] m_R;
	delete[] m_M;
	delete[] m_U;
	delete[] m_workarray;
}

/* the initialization function for submodel */
void Heater::Initialize (XXDouble *u, XXDouble *y, XXDouble t)
{
	/* initialization phase (allocating memory) */
	m_initialize = true;
	m_stop_run = false;

	/* set the constants */
	m_C[0] = 8.31451;		/* R {J/mol.K} */
	m_C[1] = 6.28318530717959;		/* twopi {} */


	/* set the parameters */
	m_P[0] = 7.0;		/* situationInput */
	m_P[1] = 1.0e6;		/* timeMax {s} */
	m_P[2] = 2.0;		/* mWater {kg} */
	m_P[3] = 8.0;		/* mSteel {kg} */
	m_P[4] = 5.0;		/* nLayer */
	m_P[5] = 4180.0;		/* cpWater {J/kg} */
	m_P[6] = 500.0;		/* cpSteel {J/kg} */
	m_P[7] = 453.0;		/* TInit {K} */
	m_P[8] = 0.01;		/* RSteel {K/W} */
	m_P[9] = 3360.0;		/* cDiode {W/K} */
	m_P[10] = 1.0;		/* cDiodeMin {W/K} */
	m_P[11] = 101325.0;		/* p_init {Pa} */
	m_P[12] = 0.0;		/* p_exit {Pa} */
	m_P[13] = 0.001;		/* heater_volume {m3} */
	m_P[14] = 0.028;		/* M */
	m_P[15] = 1150.0;		/* cp_gas {J/kg.K} */
	m_P[16] = 2000.0;		/* Tburner {K} */
	m_P[17] = 500.0;		/* Texit {K} */
	m_P[18] = 1.0e-6;		/* flowConductance */
	m_P[19] = 0.1;		/* RHX {K/W} */
	m_P[20] = 800.0;		/* Layer1\CSteel\C {J/K} */
	m_P[21] = 1672.0;		/* Layer1\CWater4\C {J/K} */
	m_P[22] = 2.0e-4;		/* Layer1\C_gas_1\v_gas {m3} */
	m_P[23] = 2.0e-7;		/* Layer1\R_gas\flowConductanceLayer */
	m_P[24] = 800.0;		/* Layer2\CSteel\C {J/K} */
	m_P[25] = 1672.0;		/* Layer2\CWater4\C {J/K} */
	m_P[26] = 2.0e-4;		/* Layer2\C_gas_1\v_gas {m3} */
	m_P[27] = 2.0e-7;		/* Layer2\R_gas\flowConductanceLayer */
	m_P[28] = 800.0;		/* Layer3\CSteel\C {J/K} */
	m_P[29] = 1672.0;		/* Layer3\CWater4\C {J/K} */
	m_P[30] = 2.0e-4;		/* Layer3\C_gas_1\v_gas {m3} */
	m_P[31] = 2.0e-7;		/* Layer3\R_gas\flowConductanceLayer */
	m_P[32] = 800.0;		/* Layer4\CSteel\C {J/K} */
	m_P[33] = 1672.0;		/* Layer4\CWater4\C {J/K} */
	m_P[34] = 2.0e-4;		/* Layer4\C_gas_1\v_gas {m3} */
	m_P[35] = 2.0e-7;		/* Layer4\R_gas\flowConductanceLayer */
	m_P[36] = 800.0;		/* Layer5\CSteel\C {J/K} */
	m_P[37] = 1672.0;		/* Layer5\CWater4\C {J/K} */
	m_P[38] = 2.0e-4;		/* Layer5\C_gas_1\v_gas {m3} */
	m_P[39] = 2.0e-7;		/* Layer5\R_gas\flowConductanceLayer */
	m_P[40] = 0.1;		/* LowPassFilter1\BW */


	/* set the initial values */
	m_I[2] = 362400.0;		/* Layer1\CSteel\Q_init {J} */
	m_I[3] = 757416.0;		/* Layer1\CWater4\Q_init {J} */
	m_I[4] = 1.50650222497412e-4;		/* Layer1\C_gas_1\m_gas_init {kg} */
	m_I[5] = 58.2162334100266;		/* Layer1\C_gas_1\U_gas_init {J} */
	m_I[6] = 362400.0;		/* Layer2\CSteel\Q_init {J} */
	m_I[7] = 757416.0;		/* Layer2\CWater4\Q_init {J} */
	m_I[8] = 1.50650222497412e-4;		/* Layer2\C_gas_1\m_gas_init {kg} */
	m_I[9] = 58.2162334100266;		/* Layer2\C_gas_1\U_gas_init {J} */
	m_I[10] = 362400.0;		/* Layer3\CSteel\Q_init {J} */
	m_I[11] = 757416.0;		/* Layer3\CWater4\Q_init {J} */
	m_I[12] = 1.50650222497412e-4;		/* Layer3\C_gas_1\m_gas_init {kg} */
	m_I[13] = 58.2162334100266;		/* Layer3\C_gas_1\U_gas_init {J} */
	m_I[14] = 362400.0;		/* Layer4\CSteel\Q_init {J} */
	m_I[15] = 757416.0;		/* Layer4\CWater4\Q_init {J} */
	m_I[16] = 1.50650222497412e-4;		/* Layer4\C_gas_1\m_gas_init {kg} */
	m_I[17] = 58.2162334100266;		/* Layer4\C_gas_1\U_gas_init {J} */
	m_I[18] = 362400.0;		/* Layer5\CSteel\Q_init {J} */
	m_I[19] = 757416.0;		/* Layer5\CWater4\Q_init {J} */
	m_I[20] = 1.50650222497412e-4;		/* Layer5\C_gas_1\m_gas_init {kg} */
	m_I[21] = 58.2162334100266;		/* Layer5\C_gas_1\U_gas_init {J} */
	m_I[0] = 0.0;		/* LowPassFilter1\s1y_initial */
	m_I[1] = 0.0;		/* LowPassFilter1\y_initial */


	/* set the states */
	m_s[2] = m_I[2];		/* Layer1\CSteel\state {J} */
	m_s[3] = m_I[3];		/* Layer1\CWater4\state {J} */
	m_s[4] = m_I[4];		/* Layer1\C_gas_1\m_gas {kg} */
	m_s[5] = m_I[5];		/* Layer1\C_gas_1\U_gas {J} */
	m_s[6] = m_I[6];		/* Layer2\CSteel\state {J} */
	m_s[7] = m_I[7];		/* Layer2\CWater4\state {J} */
	m_s[8] = m_I[8];		/* Layer2\C_gas_1\m_gas {kg} */
	m_s[9] = m_I[9];		/* Layer2\C_gas_1\U_gas {J} */
	m_s[10] = m_I[10];		/* Layer3\CSteel\state {J} */
	m_s[11] = m_I[11];		/* Layer3\CWater4\state {J} */
	m_s[12] = m_I[12];		/* Layer3\C_gas_1\m_gas {kg} */
	m_s[13] = m_I[13];		/* Layer3\C_gas_1\U_gas {J} */
	m_s[14] = m_I[14];		/* Layer4\CSteel\state {J} */
	m_s[15] = m_I[15];		/* Layer4\CWater4\state {J} */
	m_s[16] = m_I[16];		/* Layer4\C_gas_1\m_gas {kg} */
	m_s[17] = m_I[17];		/* Layer4\C_gas_1\U_gas {J} */
	m_s[18] = m_I[18];		/* Layer5\CSteel\state {J} */
	m_s[19] = m_I[19];		/* Layer5\CWater4\state {J} */
	m_s[20] = m_I[20];		/* Layer5\C_gas_1\m_gas {kg} */
	m_s[21] = m_I[21];		/* Layer5\C_gas_1\U_gas {J} */
	m_s[0] = m_I[0];		/* LowPassFilter1\s1y */
	m_s[1] = m_I[1];		/* LowPassFilter1\y */


	/* set the matrices */
	m_M[0].mat = &m_V[8];		/* Layer1\C_gas_1\pIn.e */
	m_M[0].rows = 2;
	m_M[0].columns = 1;
	m_M[1].mat = &m_V[10];		/* Layer1\C_gas_1\pOut.e */
	m_M[1].rows = 2;
	m_M[1].columns = 1;
	m_M[2].mat = &m_V[33];		/* Layer1\R_gas\pIn.f */
	m_M[2].rows = 2;
	m_M[2].columns = 1;
	m_M[3].mat = &m_V[35];		/* Layer1\R_gas\pOut.f */
	m_M[3].rows = 2;
	m_M[3].columns = 1;
	m_M[4].mat = &m_V[47];		/* Layer2\C_gas_1\pIn.e */
	m_M[4].rows = 2;
	m_M[4].columns = 1;
	m_M[5].mat = &m_V[49];		/* Layer2\C_gas_1\pOut.e */
	m_M[5].rows = 2;
	m_M[5].columns = 1;
	m_M[6].mat = &m_V[72];		/* Layer2\R_gas\pIn.f */
	m_M[6].rows = 2;
	m_M[6].columns = 1;
	m_M[7].mat = &m_V[74];		/* Layer2\R_gas\pOut.f */
	m_M[7].rows = 2;
	m_M[7].columns = 1;
	m_M[8].mat = &m_V[86];		/* Layer3\C_gas_1\pIn.e */
	m_M[8].rows = 2;
	m_M[8].columns = 1;
	m_M[9].mat = &m_V[88];		/* Layer3\C_gas_1\pOut.e */
	m_M[9].rows = 2;
	m_M[9].columns = 1;
	m_M[10].mat = &m_V[111];		/* Layer3\R_gas\pIn.f */
	m_M[10].rows = 2;
	m_M[10].columns = 1;
	m_M[11].mat = &m_V[113];		/* Layer3\R_gas\pOut.f */
	m_M[11].rows = 2;
	m_M[11].columns = 1;
	m_M[12].mat = &m_V[125];		/* Layer4\C_gas_1\pIn.e */
	m_M[12].rows = 2;
	m_M[12].columns = 1;
	m_M[13].mat = &m_V[127];		/* Layer4\C_gas_1\pOut.e */
	m_M[13].rows = 2;
	m_M[13].columns = 1;
	m_M[14].mat = &m_V[150];		/* Layer4\R_gas\pIn.f */
	m_M[14].rows = 2;
	m_M[14].columns = 1;
	m_M[15].mat = &m_V[152];		/* Layer4\R_gas\pOut.f */
	m_M[15].rows = 2;
	m_M[15].columns = 1;
	m_M[16].mat = &m_V[164];		/* Layer5\C_gas_1\pIn.e */
	m_M[16].rows = 2;
	m_M[16].columns = 1;
	m_M[17].mat = &m_V[166];		/* Layer5\C_gas_1\pOut.e */
	m_M[17].rows = 2;
	m_M[17].columns = 1;
	m_M[18].mat = &m_V[184];		/* Layer5\R_gas\pIn.f */
	m_M[18].rows = 2;
	m_M[18].columns = 1;
	m_M[19].mat = &m_V[186];		/* Layer5\R_gas\pOut.f */
	m_M[19].rows = 2;
	m_M[19].columns = 1;
	m_M[20].mat = &m_V[201];		/* Se\p.e */
	m_M[20].rows = 2;
	m_M[20].columns = 1;
	m_M[21].mat = &m_V[204];		/* Sf\p.f */
	m_M[21].rows = 2;
	m_M[21].columns = 1;


	/* (re-)initialize the integration method */
	myintegmethod.Initialize(this);
	
	/* copy the inputs */
	m_time = t;
	CopyInputsToVariables (u);

	/* calculate initial and static equations */
	CalculateInitial ();
	CalculateStatic ();
	CalculateInput ();
	CalculateDynamic ();
	CalculateOutput ();

	/* Set the outputs */
	CopyVariablesToOutputs (y);

	/* end of initialization phase */
	m_initialize = false;

	state = mainrun;
}

/* the function that calculates the submodel */
void Heater::Calculate (XXDouble *u, XXDouble *y /*, XXDouble t*/)
{
	switch (state)
	{
		case initialrun:	/* calculate the model for the first time */
			Initialize(u, y, 0.0);
			break;
		case mainrun:	/* calculate the model */
			if ( ( m_time <= (m_finish_time - m_step_size  + c_delta )) || ( m_finish_time == 0.0 ) )
			{
				/* another precessor submodel could determine the parameters of this submodel
				   and therefore the static parameter calculations need to be performed. */
				CalculateStatic ();
				CopyInputsToVariables (u);
				CalculateInput ();
				myintegmethod.Step();
				CalculateOutput ();
				CopyVariablesToOutputs (y);
			}
			else
			{
				state = finished;
			}

			if ( ( m_stop_run == true ) || (( m_finish_time != 0.0 ) && ( m_time + c_delta >= m_finish_time)) )
			{
				state = finished;
			}
			break;
		case finished:
			break;
		default:
			break;
	}
}

/* the termination function for submodel */
void Heater::Terminate (XXDouble *u, XXDouble *y /*, XXDouble t */)
{
	/* copy the inputs */
	CopyInputsToVariables (u);

	/* calculate the final model equations */
	CalculateFinal ();

	/* set the outputs */
	CopyVariablesToOutputs (y);
}


/* This function calculates the initial equations of the model.
 * These equations are calculated before anything else
 */
void Heater::CalculateInitial (void)
{
		/* GY\dm_water = 0.033; */
		m_V[4] = 0.033;

		/* Layer1\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[20] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer1\CSteel\Q_init = Layer1\CSteel\C * TInit; */
		m_I[2] = m_P[20] * m_P[7];

		/* Layer1\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[21] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer1\CWater4\Q_init = Layer1\CWater4\C * TInit; */
		m_I[3] = m_P[21] * m_P[7];

		/* Layer1\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[22] = m_P[13] / m_P[4];

		/* Layer1\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[21] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer1\C_gas_1\m_gas_init = Layer1\C_gas_1\rho_init * Layer1\C_gas_1\v_gas; */
		m_I[4] = m_V[21] * m_P[22];

		/* Layer1\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[19] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer1\C_gas_1\U_gas_init = Layer1\C_gas_1\u_init * Layer1\C_gas_1\m_gas_init; */
		m_I[5] = m_V[19] * m_I[4];

		/* Layer1\RSteel\R = RSteel / nLayer; */
		m_V[32] = m_P[8] / m_P[4];

		/* Layer1\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[23] = m_P[18] / m_P[4];

		/* Layer2\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[24] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer2\CSteel\Q_init = Layer2\CSteel\C * TInit; */
		m_I[6] = m_P[24] * m_P[7];

		/* Layer2\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[25] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer2\CWater4\Q_init = Layer2\CWater4\C * TInit; */
		m_I[7] = m_P[25] * m_P[7];

		/* Layer2\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[26] = m_P[13] / m_P[4];

		/* Layer2\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[60] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer2\C_gas_1\m_gas_init = Layer2\C_gas_1\rho_init * Layer2\C_gas_1\v_gas; */
		m_I[8] = m_V[60] * m_P[26];

		/* Layer2\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[58] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer2\C_gas_1\U_gas_init = Layer2\C_gas_1\u_init * Layer2\C_gas_1\m_gas_init; */
		m_I[9] = m_V[58] * m_I[8];

		/* Layer2\RSteel\R = RSteel / nLayer; */
		m_V[71] = m_P[8] / m_P[4];

		/* Layer2\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[27] = m_P[18] / m_P[4];

		/* Layer3\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[28] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer3\CSteel\Q_init = Layer3\CSteel\C * TInit; */
		m_I[10] = m_P[28] * m_P[7];

		/* Layer3\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[29] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer3\CWater4\Q_init = Layer3\CWater4\C * TInit; */
		m_I[11] = m_P[29] * m_P[7];

		/* Layer3\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[30] = m_P[13] / m_P[4];

		/* Layer3\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[99] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer3\C_gas_1\m_gas_init = Layer3\C_gas_1\rho_init * Layer3\C_gas_1\v_gas; */
		m_I[12] = m_V[99] * m_P[30];

		/* Layer3\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[97] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer3\C_gas_1\U_gas_init = Layer3\C_gas_1\u_init * Layer3\C_gas_1\m_gas_init; */
		m_I[13] = m_V[97] * m_I[12];

		/* Layer3\RSteel\R = RSteel / nLayer; */
		m_V[110] = m_P[8] / m_P[4];

		/* Layer3\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[31] = m_P[18] / m_P[4];

		/* Layer4\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[32] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer4\CSteel\Q_init = Layer4\CSteel\C * TInit; */
		m_I[14] = m_P[32] * m_P[7];

		/* Layer4\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[33] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer4\CWater4\Q_init = Layer4\CWater4\C * TInit; */
		m_I[15] = m_P[33] * m_P[7];

		/* Layer4\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[34] = m_P[13] / m_P[4];

		/* Layer4\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[138] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer4\C_gas_1\m_gas_init = Layer4\C_gas_1\rho_init * Layer4\C_gas_1\v_gas; */
		m_I[16] = m_V[138] * m_P[34];

		/* Layer4\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[136] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer4\C_gas_1\U_gas_init = Layer4\C_gas_1\u_init * Layer4\C_gas_1\m_gas_init; */
		m_I[17] = m_V[136] * m_I[16];

		/* Layer4\RSteel\R = RSteel / nLayer; */
		m_V[149] = m_P[8] / m_P[4];

		/* Layer4\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[35] = m_P[18] / m_P[4];

		/* Layer5\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[36] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer5\CSteel\Q_init = Layer5\CSteel\C * TInit; */
		m_I[18] = m_P[36] * m_P[7];

		/* Layer5\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[37] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer5\CWater4\Q_init = Layer5\CWater4\C * TInit; */
		m_I[19] = m_P[37] * m_P[7];

		/* Layer5\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[38] = m_P[13] / m_P[4];

		/* Layer5\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[177] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer5\C_gas_1\m_gas_init = Layer5\C_gas_1\rho_init * Layer5\C_gas_1\v_gas; */
		m_I[20] = m_V[177] * m_P[38];

		/* Layer5\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[175] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer5\C_gas_1\U_gas_init = Layer5\C_gas_1\u_init * Layer5\C_gas_1\m_gas_init; */
		m_I[21] = m_V[175] * m_I[20];

		/* Layer5\RSteel\R = RSteel / nLayer; */
		m_V[183] = m_P[8] / m_P[4];

		/* Layer5\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[39] = m_P[18] / m_P[4];

}

/* This function calculates the static equations of the model.
 * These equations are only dependent from parameters and constants
 */
void Heater::CalculateStatic (void)
{
	/* LowPassFilter1\BWrad = twopi * LowPassFilter1\BW; */
	m_V[196] = m_C[1] * m_P[40];

	/* Se\p.e = [p_init; 0]; */
	m_M[20].mat[0] = m_P[11];
	m_M[20].mat[1] = 0.0;

	/* [Layer5\R_gas\pressureOut; Layer5\R_gas\hOut] = Se\p.e; */
	m_V[191] = m_M[20].mat[0];
	m_V[194] = m_M[20].mat[1];

}

/* This function calculates the input equations of the model.
 * These equations are dynamic equations that must not change
 * in calls from the integration method (like random and delay).
 */
void Heater::CalculateInput (void)
{

}

/* This function calculates the dynamic equations of the model.
 * These equations are called from the integration method
 * to calculate the new model rates (that are then integrated).
 */
void Heater::CalculateDynamic (void)
{
	/* additional code for LowPassFilter1\s1y; */
	m_R[1] = m_s[0];

	/* if (time > timeMax) */
	if (m_time > m_P[1])
	{
		/* stopsimulation */
		XXStopSimulation ( "End of measurement", 0);

	}

	/* Layer1\CSteel\p.T = Layer1\CSteel\state / Layer1\CSteel\C; */
	m_V[6] = m_s[2] / m_P[20];

	/* Layer1\CWater4\p.T = Layer1\CWater4\state / Layer1\CWater4\C; */
	m_V[7] = m_s[3] / m_P[21];

	/* Layer1\C_gas_1\u = Layer1\C_gas_1\U_gas / Layer1\C_gas_1\m_gas; */
	m_V[18] = m_s[5] / m_s[4];

	/* Layer1\C_gas_1\rho = Layer1\C_gas_1\m_gas / Layer1\C_gas_1\v_gas; */
	m_V[20] = m_s[4] / m_P[22];

	/* Layer1\C_gas_1\T = Layer1\C_gas_1\u / (cp_gas - R / M); */
	m_V[12] = m_V[18] / (m_P[15] - m_C[0] / m_P[14]);

	/* Layer1\C_gas_1\p = (((Layer1\C_gas_1\rho * R) * Layer1\C_gas_1\T) / M); */
	m_V[13] = (((m_V[20] * m_C[0]) * m_V[12]) / m_P[14]);

	/* Layer1\C_gas_1\h = Layer1\C_gas_1\u + Layer1\C_gas_1\p / Layer1\C_gas_1\rho; */
	m_V[22] = m_V[18] + m_V[13] / m_V[20];

	/* Layer1\C_gas_1\pIn.e = [Layer1\C_gas_1\p; Layer1\C_gas_1\h]; */
	m_M[0].mat[0] = m_V[13];
	m_M[0].mat[1] = m_V[22];

	/* Layer1\C_gas_1\pOut.e = [Layer1\C_gas_1\p; Layer1\C_gas_1\h]; */
	m_M[1].mat[0] = m_V[13];
	m_M[1].mat[1] = m_V[22];

	/* Layer2\CSteel\p.T = Layer2\CSteel\state / Layer2\CSteel\C; */
	m_V[45] = m_s[6] / m_P[24];

	/* Layer2\CWater4\p.T = Layer2\CWater4\state / Layer2\CWater4\C; */
	m_V[46] = m_s[7] / m_P[25];

	/* Layer2\C_gas_1\u = Layer2\C_gas_1\U_gas / Layer2\C_gas_1\m_gas; */
	m_V[57] = m_s[9] / m_s[8];

	/* Layer2\C_gas_1\rho = Layer2\C_gas_1\m_gas / Layer2\C_gas_1\v_gas; */
	m_V[59] = m_s[8] / m_P[26];

	/* Layer2\C_gas_1\T = Layer2\C_gas_1\u / (cp_gas - R / M); */
	m_V[51] = m_V[57] / (m_P[15] - m_C[0] / m_P[14]);

	/* Layer2\C_gas_1\p = (((Layer2\C_gas_1\rho * R) * Layer2\C_gas_1\T) / M); */
	m_V[52] = (((m_V[59] * m_C[0]) * m_V[51]) / m_P[14]);

	/* Layer2\C_gas_1\h = Layer2\C_gas_1\u + Layer2\C_gas_1\p / Layer2\C_gas_1\rho; */
	m_V[61] = m_V[57] + m_V[52] / m_V[59];

	/* Layer2\C_gas_1\pIn.e = [Layer2\C_gas_1\p; Layer2\C_gas_1\h]; */
	m_M[4].mat[0] = m_V[52];
	m_M[4].mat[1] = m_V[61];

	/* Layer2\C_gas_1\pOut.e = [Layer2\C_gas_1\p; Layer2\C_gas_1\h]; */
	m_M[5].mat[0] = m_V[52];
	m_M[5].mat[1] = m_V[61];

	/* Layer3\CSteel\p.T = Layer3\CSteel\state / Layer3\CSteel\C; */
	m_V[84] = m_s[10] / m_P[28];

	/* Layer3\CWater4\p.T = Layer3\CWater4\state / Layer3\CWater4\C; */
	m_V[85] = m_s[11] / m_P[29];

	/* Layer3\C_gas_1\u = Layer3\C_gas_1\U_gas / Layer3\C_gas_1\m_gas; */
	m_V[96] = m_s[13] / m_s[12];

	/* Layer3\C_gas_1\rho = Layer3\C_gas_1\m_gas / Layer3\C_gas_1\v_gas; */
	m_V[98] = m_s[12] / m_P[30];

	/* Layer3\C_gas_1\T = Layer3\C_gas_1\u / (cp_gas - R / M); */
	m_V[90] = m_V[96] / (m_P[15] - m_C[0] / m_P[14]);

	/* Layer3\C_gas_1\p = (((Layer3\C_gas_1\rho * R) * Layer3\C_gas_1\T) / M); */
	m_V[91] = (((m_V[98] * m_C[0]) * m_V[90]) / m_P[14]);

	/* Layer3\C_gas_1\h = Layer3\C_gas_1\u + Layer3\C_gas_1\p / Layer3\C_gas_1\rho; */
	m_V[100] = m_V[96] + m_V[91] / m_V[98];

	/* Layer3\C_gas_1\pIn.e = [Layer3\C_gas_1\p; Layer3\C_gas_1\h]; */
	m_M[8].mat[0] = m_V[91];
	m_M[8].mat[1] = m_V[100];

	/* Layer3\C_gas_1\pOut.e = [Layer3\C_gas_1\p; Layer3\C_gas_1\h]; */
	m_M[9].mat[0] = m_V[91];
	m_M[9].mat[1] = m_V[100];

	/* Layer4\CSteel\p.T = Layer4\CSteel\state / Layer4\CSteel\C; */
	m_V[123] = m_s[14] / m_P[32];

	/* Layer4\CWater4\p.T = Layer4\CWater4\state / Layer4\CWater4\C; */
	m_V[124] = m_s[15] / m_P[33];

	/* Layer4\C_gas_1\u = Layer4\C_gas_1\U_gas / Layer4\C_gas_1\m_gas; */
	m_V[135] = m_s[17] / m_s[16];

	/* Layer4\C_gas_1\rho = Layer4\C_gas_1\m_gas / Layer4\C_gas_1\v_gas; */
	m_V[137] = m_s[16] / m_P[34];

	/* Layer4\C_gas_1\T = Layer4\C_gas_1\u / (cp_gas - R / M); */
	m_V[129] = m_V[135] / (m_P[15] - m_C[0] / m_P[14]);

	/* Layer4\C_gas_1\p = (((Layer4\C_gas_1\rho * R) * Layer4\C_gas_1\T) / M); */
	m_V[130] = (((m_V[137] * m_C[0]) * m_V[129]) / m_P[14]);

	/* Layer4\C_gas_1\h = Layer4\C_gas_1\u + Layer4\C_gas_1\p / Layer4\C_gas_1\rho; */
	m_V[139] = m_V[135] + m_V[130] / m_V[137];

	/* Layer4\C_gas_1\pIn.e = [Layer4\C_gas_1\p; Layer4\C_gas_1\h]; */
	m_M[12].mat[0] = m_V[130];
	m_M[12].mat[1] = m_V[139];

	/* Layer4\C_gas_1\pOut.e = [Layer4\C_gas_1\p; Layer4\C_gas_1\h]; */
	m_M[13].mat[0] = m_V[130];
	m_M[13].mat[1] = m_V[139];

	/* Layer5\CSteel\p.T = Layer5\CSteel\state / Layer5\CSteel\C; */
	m_V[162] = m_s[18] / m_P[36];

	/* Layer5\CWater4\p.T = Layer5\CWater4\state / Layer5\CWater4\C; */
	m_V[163] = m_s[19] / m_P[37];

	/* Layer5\C_gas_1\u = Layer5\C_gas_1\U_gas / Layer5\C_gas_1\m_gas; */
	m_V[174] = m_s[21] / m_s[20];

	/* Layer5\C_gas_1\rho = Layer5\C_gas_1\m_gas / Layer5\C_gas_1\v_gas; */
	m_V[176] = m_s[20] / m_P[38];

	/* Layer5\C_gas_1\T = Layer5\C_gas_1\u / (cp_gas - R / M); */
	m_V[168] = m_V[174] / (m_P[15] - m_C[0] / m_P[14]);

	/* Layer5\C_gas_1\p = (((Layer5\C_gas_1\rho * R) * Layer5\C_gas_1\T) / M); */
	m_V[169] = (((m_V[176] * m_C[0]) * m_V[168]) / m_P[14]);

	/* Layer5\C_gas_1\h = Layer5\C_gas_1\u + Layer5\C_gas_1\p / Layer5\C_gas_1\rho; */
	m_V[178] = m_V[174] + m_V[169] / m_V[176];

	/* Layer5\C_gas_1\pIn.e = [Layer5\C_gas_1\p; Layer5\C_gas_1\h]; */
	m_M[16].mat[0] = m_V[169];
	m_M[16].mat[1] = m_V[178];

	/* Layer5\C_gas_1\pOut.e = [Layer5\C_gas_1\p; Layer5\C_gas_1\h]; */
	m_M[17].mat[0] = m_V[169];
	m_M[17].mat[1] = m_V[178];

	/* GY\dm_water = dm_water; */
	m_V[4] = m_V[210];

	/* LowPassFilter1\u = P_natural_gas; */
	m_V[195] = m_V[221];

	/* Retour\effort = Tin; */
	m_V[200] = m_V[223];

	/* GY\r = GY\dm_water * cpWater; */
	m_V[5] = m_V[4] * m_P[5];

	/* Layer1\GY1\r = GY\dm_water * cpWater; */
	m_V[25] = m_V[4] * m_P[5];

	/* [Layer1\R_gas\pressureIn; Layer1\R_gas\hIn] = Layer1\C_gas_1\pOut.e; */
	m_V[39] = m_M[1].mat[0];
	m_V[42] = m_M[1].mat[1];

	/* Layer2\GY1\r = GY\dm_water * cpWater; */
	m_V[64] = m_V[4] * m_P[5];

	/* [Layer2\R_gas\pressureIn; Layer2\R_gas\hIn] = Layer2\C_gas_1\pOut.e; */
	m_V[78] = m_M[5].mat[0];
	m_V[81] = m_M[5].mat[1];

	/* Layer3\GY1\r = GY\dm_water * cpWater; */
	m_V[103] = m_V[4] * m_P[5];

	/* [Layer3\R_gas\pressureIn; Layer3\R_gas\hIn] = Layer3\C_gas_1\pOut.e; */
	m_V[117] = m_M[9].mat[0];
	m_V[120] = m_M[9].mat[1];

	/* Layer4\GY1\r = GY\dm_water * cpWater; */
	m_V[142] = m_V[4] * m_P[5];

	/* [Layer4\R_gas\pressureIn; Layer4\R_gas\hIn] = Layer4\C_gas_1\pOut.e; */
	m_V[156] = m_M[13].mat[0];
	m_V[159] = m_M[13].mat[1];

	/* [Layer5\R_gas\pressureIn; Layer5\R_gas\hIn] = Layer5\C_gas_1\pOut.e; */
	m_V[190] = m_M[17].mat[0];
	m_V[193] = m_M[17].mat[1];

	/* LowPassFilter1\s2y = LowPassFilter1\BWrad ^ 2.0 * (LowPassFilter1\u - LowPassFilter1\y) - (1.414213562373 * LowPassFilter1\BWrad) * LowPassFilter1\s1y; */
	m_R[0] = (m_V[196] * m_V[196]) * (m_V[195] - m_s[1]) - (1.414213562373 * m_V[196]) * m_s[0];

	/* Sf\dm = LowPassFilter1\y / (cp_gas * (Tburner - TInit)); */
	m_V[207] = m_s[1] / (m_P[15] * (m_P[16] - m_P[7]));

	/* Sf\dH = (Sf\dm * Tburner) * cp_gas; */
	m_V[206] = (m_V[207] * m_P[16]) * m_P[15];

	/* Sf\p.f = [Sf\dm; Sf\dH]; */
	m_M[21].mat[0] = m_V[207];
	m_M[21].mat[1] = m_V[206];

	/* Sf1\r = GY\dm_water * cpWater; */
	m_V[209] = m_V[4] * m_P[5];

	/* GY\p2.dQ = GY\r * Retour\effort; */
	m_V[3] = m_V[5] * m_V[200];

	/* GY\p1.dQ = GY\r * Retour\effort; */
	m_V[2] = m_V[5] * m_V[200];

	/* [Layer1\R_gas\pressureOut; Layer1\R_gas\hOut] = Layer2\C_gas_1\pIn.e; */
	m_V[40] = m_M[4].mat[0];
	m_V[43] = m_M[4].mat[1];

	/* if Layer1\R_gas\pressureIn > Layer1\R_gas\pressureOut */
	if (m_V[39] > m_V[40])
	{
		/* Layer1\R_gas\h = Layer1\R_gas\hIn; */
		m_V[41] = m_V[42];
	}
	else
	{
		/* Layer1\R_gas\h = Layer1\R_gas\hOut; */
		m_V[41] = m_V[43];
	}

	/* Layer1\R_gas\dm = Layer1\R_gas\flowConductanceLayer * (Layer1\R_gas\pressureIn - Layer1\R_gas\pressureOut); */
	m_V[37] = m_P[23] * (m_V[39] - m_V[40]);

	/* Layer1\R_gas\dH = Layer1\R_gas\dm * Layer1\R_gas\h; */
	m_V[38] = m_V[37] * m_V[41];

	/* Layer1\R_gas\pIn.f = [Layer1\R_gas\dm; Layer1\R_gas\dH]; */
	m_M[2].mat[0] = m_V[37];
	m_M[2].mat[1] = m_V[38];

	/* Layer1\R_gas\pOut.f = [Layer1\R_gas\dm; Layer1\R_gas\dH]; */
	m_M[3].mat[0] = m_V[37];
	m_M[3].mat[1] = m_V[38];

	/* [Layer2\R_gas\pressureOut; Layer2\R_gas\hOut] = Layer3\C_gas_1\pIn.e; */
	m_V[79] = m_M[8].mat[0];
	m_V[82] = m_M[8].mat[1];

	/* if Layer2\R_gas\pressureIn > Layer2\R_gas\pressureOut */
	if (m_V[78] > m_V[79])
	{
		/* Layer2\R_gas\h = Layer2\R_gas\hIn; */
		m_V[80] = m_V[81];
	}
	else
	{
		/* Layer2\R_gas\h = Layer2\R_gas\hOut; */
		m_V[80] = m_V[82];
	}

	/* Layer2\R_gas\dm = Layer2\R_gas\flowConductanceLayer * (Layer2\R_gas\pressureIn - Layer2\R_gas\pressureOut); */
	m_V[76] = m_P[27] * (m_V[78] - m_V[79]);

	/* Layer2\R_gas\dH = Layer2\R_gas\dm * Layer2\R_gas\h; */
	m_V[77] = m_V[76] * m_V[80];

	/* Layer2\R_gas\pIn.f = [Layer2\R_gas\dm; Layer2\R_gas\dH]; */
	m_M[6].mat[0] = m_V[76];
	m_M[6].mat[1] = m_V[77];

	/* Layer2\R_gas\pOut.f = [Layer2\R_gas\dm; Layer2\R_gas\dH]; */
	m_M[7].mat[0] = m_V[76];
	m_M[7].mat[1] = m_V[77];

	/* [Layer3\R_gas\pressureOut; Layer3\R_gas\hOut] = Layer4\C_gas_1\pIn.e; */
	m_V[118] = m_M[12].mat[0];
	m_V[121] = m_M[12].mat[1];

	/* if Layer3\R_gas\pressureIn > Layer3\R_gas\pressureOut */
	if (m_V[117] > m_V[118])
	{
		/* Layer3\R_gas\h = Layer3\R_gas\hIn; */
		m_V[119] = m_V[120];
	}
	else
	{
		/* Layer3\R_gas\h = Layer3\R_gas\hOut; */
		m_V[119] = m_V[121];
	}

	/* Layer3\R_gas\dm = Layer3\R_gas\flowConductanceLayer * (Layer3\R_gas\pressureIn - Layer3\R_gas\pressureOut); */
	m_V[115] = m_P[31] * (m_V[117] - m_V[118]);

	/* Layer3\R_gas\dH = Layer3\R_gas\dm * Layer3\R_gas\h; */
	m_V[116] = m_V[115] * m_V[119];

	/* Layer3\R_gas\pIn.f = [Layer3\R_gas\dm; Layer3\R_gas\dH]; */
	m_M[10].mat[0] = m_V[115];
	m_M[10].mat[1] = m_V[116];

	/* Layer3\R_gas\pOut.f = [Layer3\R_gas\dm; Layer3\R_gas\dH]; */
	m_M[11].mat[0] = m_V[115];
	m_M[11].mat[1] = m_V[116];

	/* [Layer4\R_gas\pressureOut; Layer4\R_gas\hOut] = Layer5\C_gas_1\pIn.e; */
	m_V[157] = m_M[16].mat[0];
	m_V[160] = m_M[16].mat[1];

	/* if Layer4\R_gas\pressureIn > Layer4\R_gas\pressureOut */
	if (m_V[156] > m_V[157])
	{
		/* Layer4\R_gas\h = Layer4\R_gas\hIn; */
		m_V[158] = m_V[159];
	}
	else
	{
		/* Layer4\R_gas\h = Layer4\R_gas\hOut; */
		m_V[158] = m_V[160];
	}

	/* Layer4\R_gas\dm = Layer4\R_gas\flowConductanceLayer * (Layer4\R_gas\pressureIn - Layer4\R_gas\pressureOut); */
	m_V[154] = m_P[35] * (m_V[156] - m_V[157]);

	/* Layer4\R_gas\dH = Layer4\R_gas\dm * Layer4\R_gas\h; */
	m_V[155] = m_V[154] * m_V[158];

	/* Layer4\R_gas\pIn.f = [Layer4\R_gas\dm; Layer4\R_gas\dH]; */
	m_M[14].mat[0] = m_V[154];
	m_M[14].mat[1] = m_V[155];

	/* Layer4\R_gas\pOut.f = [Layer4\R_gas\dm; Layer4\R_gas\dH]; */
	m_M[15].mat[0] = m_V[154];
	m_M[15].mat[1] = m_V[155];

	/* [Layer1\C_gas_1\dmOut; Layer1\C_gas_1\dHOut] = Layer1\R_gas\pIn.f; */
	m_V[16] = m_M[2].mat[0];
	m_V[17] = m_M[2].mat[1];

	/* Layer1\OneJunction4\p2.T = Layer1\CWater4\p.T - Layer1\CSteel\p.T; */
	m_V[27] = m_V[7] - m_V[6];

	/* [Layer2\C_gas_1\dmOut; Layer2\C_gas_1\dHOut] = Layer2\R_gas\pIn.f; */
	m_V[55] = m_M[6].mat[0];
	m_V[56] = m_M[6].mat[1];

	/* Layer2\OneJunction4\p2.T = Layer2\CWater4\p.T - Layer2\CSteel\p.T; */
	m_V[66] = m_V[46] - m_V[45];

	/* [Layer3\C_gas_1\dmOut; Layer3\C_gas_1\dHOut] = Layer3\R_gas\pIn.f; */
	m_V[94] = m_M[10].mat[0];
	m_V[95] = m_M[10].mat[1];

	/* Layer3\OneJunction4\p2.T = Layer3\CWater4\p.T - Layer3\CSteel\p.T; */
	m_V[105] = m_V[85] - m_V[84];

	/* [Layer4\C_gas_1\dmOut; Layer4\C_gas_1\dHOut] = Layer4\R_gas\pIn.f; */
	m_V[133] = m_M[14].mat[0];
	m_V[134] = m_M[14].mat[1];

	/* Layer4\OneJunction4\p2.T = Layer4\CWater4\p.T - Layer4\CSteel\p.T; */
	m_V[144] = m_V[124] - m_V[123];

	/* Layer5\OneJunction4\p2.T = Layer5\CWater4\p.T - Layer5\CSteel\p.T; */
	m_V[180] = m_V[163] - m_V[162];

	/* if Layer5\R_gas\pressureIn > Layer5\R_gas\pressureOut */
	if (m_V[190] > m_V[191])
	{
		/* Layer5\R_gas\h = Layer5\R_gas\hIn; */
		m_V[192] = m_V[193];
	}
	else
	{
		/* Layer5\R_gas\h = Layer5\R_gas\hOut; */
		m_V[192] = m_V[194];
	}

	/* Layer5\R_gas\dm = Layer5\R_gas\flowConductanceLayer * (Layer5\R_gas\pressureIn - Layer5\R_gas\pressureOut); */
	m_V[188] = m_P[39] * (m_V[190] - m_V[191]);

	/* Layer5\R_gas\dH = Layer5\R_gas\dm * Layer5\R_gas\h; */
	m_V[189] = m_V[188] * m_V[192];

	/* Layer5\R_gas\pIn.f = [Layer5\R_gas\dm; Layer5\R_gas\dH]; */
	m_M[18].mat[0] = m_V[188];
	m_M[18].mat[1] = m_V[189];

	/* Layer5\R_gas\pOut.f = [Layer5\R_gas\dm; Layer5\R_gas\dH]; */
	m_M[19].mat[0] = m_V[188];
	m_M[19].mat[1] = m_V[189];

	/* Sf1\p.f = Sf1\r * Layer1\CWater4\p.T; */
	m_V[208] = m_V[209] * m_V[7];

	/* [Layer1\C_gas_1\dmIn; Layer1\C_gas_1\dHIn] = Sf\p.f; */
	m_V[14] = m_M[21].mat[0];
	m_V[15] = m_M[21].mat[1];

	/* Layer1\C_gas_1\m_gas_dot = Layer1\C_gas_1\dmIn - Layer1\C_gas_1\dmOut; */
	m_R[4] = m_V[14] - m_V[16];

	/* Layer1\OneJunction1\p2.T = Layer1\C_gas_1\T - Layer1\CSteel\p.T; */
	m_V[26] = m_V[12] - m_V[6];

	/* [Layer2\C_gas_1\dmIn; Layer2\C_gas_1\dHIn] = Layer1\R_gas\pOut.f; */
	m_V[53] = m_M[3].mat[0];
	m_V[54] = m_M[3].mat[1];

	/* Layer2\C_gas_1\m_gas_dot = Layer2\C_gas_1\dmIn - Layer2\C_gas_1\dmOut; */
	m_R[8] = m_V[53] - m_V[55];

	/* Layer2\OneJunction1\p2.T = Layer2\C_gas_1\T - Layer2\CSteel\p.T; */
	m_V[65] = m_V[51] - m_V[45];

	/* [Layer3\C_gas_1\dmIn; Layer3\C_gas_1\dHIn] = Layer2\R_gas\pOut.f; */
	m_V[92] = m_M[7].mat[0];
	m_V[93] = m_M[7].mat[1];

	/* Layer3\C_gas_1\m_gas_dot = Layer3\C_gas_1\dmIn - Layer3\C_gas_1\dmOut; */
	m_R[12] = m_V[92] - m_V[94];

	/* Layer3\OneJunction1\p2.T = Layer3\C_gas_1\T - Layer3\CSteel\p.T; */
	m_V[104] = m_V[90] - m_V[84];

	/* [Layer4\C_gas_1\dmIn; Layer4\C_gas_1\dHIn] = Layer3\R_gas\pOut.f; */
	m_V[131] = m_M[11].mat[0];
	m_V[132] = m_M[11].mat[1];

	/* Layer4\C_gas_1\m_gas_dot = Layer4\C_gas_1\dmIn - Layer4\C_gas_1\dmOut; */
	m_R[16] = m_V[131] - m_V[133];

	/* Layer4\OneJunction1\p2.T = Layer4\C_gas_1\T - Layer4\CSteel\p.T; */
	m_V[143] = m_V[129] - m_V[123];

	/* [Layer5\C_gas_1\dmIn; Layer5\C_gas_1\dHIn] = Layer4\R_gas\pOut.f; */
	m_V[170] = m_M[15].mat[0];
	m_V[171] = m_M[15].mat[1];

	/* [Layer5\C_gas_1\dmOut; Layer5\C_gas_1\dHOut] = Layer5\R_gas\pIn.f; */
	m_V[172] = m_M[18].mat[0];
	m_V[173] = m_M[18].mat[1];

	/* Layer5\C_gas_1\m_gas_dot = Layer5\C_gas_1\dmIn - Layer5\C_gas_1\dmOut; */
	m_R[20] = m_V[170] - m_V[172];

	/* Layer5\OneJunction1\p2.T = Layer5\C_gas_1\T - Layer5\CSteel\p.T; */
	m_V[179] = m_V[168] - m_V[162];

	/* Layer1\GY1\p2.dQ = Layer1\GY1\r * Layer2\CWater4\p.T; */
	m_V[24] = m_V[25] * m_V[46];

	/* Layer1\GY1\p1.dQ = Layer1\GY1\r * Layer2\CWater4\p.T; */
	m_V[23] = m_V[25] * m_V[46];

	/* Layer1\R\p.f = Layer1\OneJunction1\p2.T / RHX; */
	m_V[28] = m_V[26] / m_P[19];

	/* if Layer2\CWater4\p.T > Layer1\CWater4\p.T */
	if (m_V[46] > m_V[7])
	{
		/* Layer1\R1\c = cDiode; */
		m_V[29] = m_P[9];
	}
	else
	{
		/* Layer1\R1\c = cDiodeMin; */
		m_V[29] = m_P[10];
	}

	/* Layer1\R1\flow = (Layer2\CWater4\p.T - Layer1\CWater4\p.T) * Layer1\R1\c; */
	m_V[30] = (m_V[46] - m_V[7]) * m_V[29];

	/* Layer2\GY1\p2.dQ = Layer2\GY1\r * Layer3\CWater4\p.T; */
	m_V[63] = m_V[64] * m_V[85];

	/* Layer2\GY1\p1.dQ = Layer2\GY1\r * Layer3\CWater4\p.T; */
	m_V[62] = m_V[64] * m_V[85];

	/* Layer2\R\p.f = Layer2\OneJunction1\p2.T / RHX; */
	m_V[67] = m_V[65] / m_P[19];

	/* if Layer3\CWater4\p.T > Layer2\CWater4\p.T */
	if (m_V[85] > m_V[46])
	{
		/* Layer2\R1\c = cDiode; */
		m_V[68] = m_P[9];
	}
	else
	{
		/* Layer2\R1\c = cDiodeMin; */
		m_V[68] = m_P[10];
	}

	/* Layer2\R1\flow = (Layer3\CWater4\p.T - Layer2\CWater4\p.T) * Layer2\R1\c; */
	m_V[69] = (m_V[85] - m_V[46]) * m_V[68];

	/* Layer3\GY1\p2.dQ = Layer3\GY1\r * Layer4\CWater4\p.T; */
	m_V[102] = m_V[103] * m_V[124];

	/* Layer3\GY1\p1.dQ = Layer3\GY1\r * Layer4\CWater4\p.T; */
	m_V[101] = m_V[103] * m_V[124];

	/* Layer3\R\p.f = Layer3\OneJunction1\p2.T / RHX; */
	m_V[106] = m_V[104] / m_P[19];

	/* if Layer4\CWater4\p.T > Layer3\CWater4\p.T */
	if (m_V[124] > m_V[85])
	{
		/* Layer3\R1\c = cDiode; */
		m_V[107] = m_P[9];
	}
	else
	{
		/* Layer3\R1\c = cDiodeMin; */
		m_V[107] = m_P[10];
	}

	/* Layer3\R1\flow = (Layer4\CWater4\p.T - Layer3\CWater4\p.T) * Layer3\R1\c; */
	m_V[108] = (m_V[124] - m_V[85]) * m_V[107];

	/* Layer4\GY1\p2.dQ = Layer4\GY1\r * Layer5\CWater4\p.T; */
	m_V[141] = m_V[142] * m_V[163];

	/* Layer4\GY1\p1.dQ = Layer4\GY1\r * Layer5\CWater4\p.T; */
	m_V[140] = m_V[142] * m_V[163];

	/* Layer4\R\p.f = Layer4\OneJunction1\p2.T / RHX; */
	m_V[145] = m_V[143] / m_P[19];

	/* if Layer5\CWater4\p.T > Layer4\CWater4\p.T */
	if (m_V[163] > m_V[124])
	{
		/* Layer4\R1\c = cDiode; */
		m_V[146] = m_P[9];
	}
	else
	{
		/* Layer4\R1\c = cDiodeMin; */
		m_V[146] = m_P[10];
	}

	/* Layer4\R1\flow = (Layer5\CWater4\p.T - Layer4\CWater4\p.T) * Layer4\R1\c; */
	m_V[147] = (m_V[163] - m_V[124]) * m_V[146];

	/* Layer5\R\p.f = Layer5\OneJunction1\p2.T / RHX; */
	m_V[181] = m_V[179] / m_P[19];

	/* PlusMinus\output = Sf\p.f[2] - Layer5\R_gas\pOut.f[2]; */
	m_V[197] = m_M[21].mat[1] - m_M[19].mat[1];

	/* Layer1\ZeroJunction14\p1.dQ = Layer1\R1\flow + Layer1\GY1\p1.dQ; */
	m_V[44] = m_V[30] + m_V[23];

	/* Layer2\ZeroJunction14\p1.dQ = Layer2\R1\flow + Layer2\GY1\p1.dQ; */
	m_V[83] = m_V[69] + m_V[62];

	/* Layer3\ZeroJunction14\p1.dQ = Layer3\R1\flow + Layer3\GY1\p1.dQ; */
	m_V[122] = m_V[108] + m_V[101];

	/* Layer4\ZeroJunction14\p1.dQ = Layer4\R1\flow + Layer4\GY1\p1.dQ; */
	m_V[161] = m_V[147] + m_V[140];

	/* Layer1\C_gas_1\U_gas_dot = (Layer1\C_gas_1\dHIn - Layer1\C_gas_1\dHOut) - Layer1\R\p.f; */
	m_R[5] = (m_V[15] - m_V[17]) - m_V[28];

	/* Layer2\C_gas_1\U_gas_dot = (Layer2\C_gas_1\dHIn - Layer2\C_gas_1\dHOut) - Layer2\R\p.f; */
	m_R[9] = (m_V[54] - m_V[56]) - m_V[67];

	/* Layer3\C_gas_1\U_gas_dot = (Layer3\C_gas_1\dHIn - Layer3\C_gas_1\dHOut) - Layer3\R\p.f; */
	m_R[13] = (m_V[93] - m_V[95]) - m_V[106];

	/* Layer4\C_gas_1\U_gas_dot = (Layer4\C_gas_1\dHIn - Layer4\C_gas_1\dHOut) - Layer4\R\p.f; */
	m_R[17] = (m_V[132] - m_V[134]) - m_V[145];

	/* Layer5\C_gas_1\U_gas_dot = (Layer5\C_gas_1\dHIn - Layer5\C_gas_1\dHOut) - Layer5\R\p.f; */
	m_R[21] = (m_V[171] - m_V[173]) - m_V[181];

	/* Layer1\RSteel\p.dQ = Layer1\OneJunction4\p2.T / Layer1\RSteel\R; */
	m_V[31] = m_V[27] / m_V[32];

	/* Layer2\RSteel\p.dQ = Layer2\OneJunction4\p2.T / Layer2\RSteel\R; */
	m_V[70] = m_V[66] / m_V[71];

	/* Layer3\RSteel\p.dQ = Layer3\OneJunction4\p2.T / Layer3\RSteel\R; */
	m_V[109] = m_V[105] / m_V[110];

	/* Layer4\RSteel\p.dQ = Layer4\OneJunction4\p2.T / Layer4\RSteel\R; */
	m_V[148] = m_V[144] / m_V[149];

	/* Layer5\RSteel\p.dQ = Layer5\OneJunction4\p2.T / Layer5\RSteel\R; */
	m_V[182] = m_V[180] / m_V[183];

	/* Layer1\CSteel\p.dQ = Layer1\RSteel\p.dQ + Layer1\R\p.f; */
	m_R[2] = m_V[31] + m_V[28];

	/* Layer1\CWater4\p.dQ = (Layer1\GY1\p2.dQ + Layer1\R1\flow) - (Sf1\p.f + Layer1\RSteel\p.dQ); */
	m_R[3] = (m_V[24] + m_V[30]) - (m_V[208] + m_V[31]);

	/* Layer2\CSteel\p.dQ = Layer2\RSteel\p.dQ + Layer2\R\p.f; */
	m_R[6] = m_V[70] + m_V[67];

	/* Layer2\CWater4\p.dQ = (Layer2\GY1\p2.dQ + Layer2\R1\flow) - (Layer1\ZeroJunction14\p1.dQ + Layer2\RSteel\p.dQ); */
	m_R[7] = (m_V[63] + m_V[69]) - (m_V[44] + m_V[70]);

	/* Layer3\CSteel\p.dQ = Layer3\RSteel\p.dQ + Layer3\R\p.f; */
	m_R[10] = m_V[109] + m_V[106];

	/* Layer3\CWater4\p.dQ = (Layer3\GY1\p2.dQ + Layer3\R1\flow) - (Layer2\ZeroJunction14\p1.dQ + Layer3\RSteel\p.dQ); */
	m_R[11] = (m_V[102] + m_V[108]) - (m_V[83] + m_V[109]);

	/* Layer4\CSteel\p.dQ = Layer4\RSteel\p.dQ + Layer4\R\p.f; */
	m_R[14] = m_V[148] + m_V[145];

	/* Layer4\CWater4\p.dQ = (Layer4\GY1\p2.dQ + Layer4\R1\flow) - (Layer3\ZeroJunction14\p1.dQ + Layer4\RSteel\p.dQ); */
	m_R[15] = (m_V[141] + m_V[147]) - (m_V[122] + m_V[148]);

	/* Layer5\CSteel\p.dQ = Layer5\RSteel\p.dQ + Layer5\R\p.f; */
	m_R[18] = m_V[182] + m_V[181];

	/* Layer5\CWater4\p.dQ = GY\p2.dQ - (Layer4\ZeroJunction14\p1.dQ + Layer5\RSteel\p.dQ); */
	m_R[19] = m_V[3] - (m_V[161] + m_V[182]);

}

/* This function calculates the output equations of the model.
 * These equations are not needed for calculation of the rates
 * and are kept separate to make the dynamic set of equations smaller.
 * These dynamic equations are called often more than one time for each
 * integration step that is taken. This makes model computation much faster.
 */
void Heater::CalculateOutput (void)
{
	/* TSteel1 = Layer1\CSteel\p.T; */
	m_V[211] = m_V[6];

	/* TWater1 = Layer1\CWater4\p.T; */
	m_V[212] = m_V[7];

	/* TSteel2 = Layer2\CSteel\p.T; */
	m_V[213] = m_V[45];

	/* TWater2 = Layer2\CWater4\p.T; */
	m_V[214] = m_V[46];

	/* TSteel3 = Layer3\CSteel\p.T; */
	m_V[215] = m_V[84];

	/* TWater3 = Layer3\CWater4\p.T; */
	m_V[216] = m_V[85];

	/* TSteel4 = Layer4\CSteel\p.T; */
	m_V[217] = m_V[123];

	/* TWater4 = Layer4\CWater4\p.T; */
	m_V[218] = m_V[124];

	/* TSteel5 = Layer5\CSteel\p.T; */
	m_V[219] = m_V[162];

	/* TWater5 = Layer5\CWater4\p.T; */
	m_V[220] = m_V[163];

	/* enthalpy_in\enthalpyFlow = Sf\p.f[2]; */
	m_V[0] = m_M[21].mat[1];

	/* PlusMinus\plus1 = Sf\p.f[2]; */
	m_V[198] = m_M[21].mat[1];

	/* enthalpy_out\enthalpyFlow = Layer5\R_gas\pOut.f[2]; */
	m_V[1] = m_M[19].mat[1];

	/* PlusMinus\minus1 = Layer5\R_gas\pOut.f[2]; */
	m_V[199] = m_M[19].mat[1];

	/* Se\powerOut = Layer5\R_gas\pOut.f[2]; */
	m_V[203] = m_M[19].mat[1];

	/* P_actual = PlusMinus\output; */
	m_V[222] = m_V[197];

}

/* This function calculates the final equations of the model.
 * These equations are calculated after all the calculations
 * are performed
 */
void Heater::CalculateFinal (void)
{

}


XXBoolean Heater::XXStopSimulation (XXString message, XXInteger id)
{
	m_stop_run = true;
	return 0;
}


bool Heater::SetFinishTime(XXDouble newtime)
{
	if ((newtime <= 0.0) || ( newtime > m_time))
	{
		m_finish_time = newtime;
		return true;
	}

	return false;
}

