/**********************************************************
 * This file is generated by the 20-sim C++ Code Generator
 *
 *  file:  Heater.cpp
 *  subm:  Heater
 *  model: heater
 *  expmt: heater
 *  date:  October 26, 2018
 *  time:  3:48:46 PM
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
	m_V[211] = u[1];		/* P_natural_gas {W} */
	m_V[212] = u[2];		/* Tin */

}

/* this PRIVATE function uses the output variables to fill the output vector */
void Heater::CopyVariablesToOutputs (XXDouble *y)
{
	/* copy the output variables to the output vector */
	y[0] = 	m_V[209];		/* Tout */

}

Heater::Heater(void)
{
	m_number_constants = 1;
	m_number_parameters = 40;
	m_number_initialvalues = 20;
	m_number_variables = 213;
	m_number_states = 20;
	m_number_rates = 20;
	m_number_matrices = 22;
	m_number_unnamed = 0;

	/* the variable arrays */
	m_C = new XXDouble[1 + 1];		/* constants */
	m_P = new XXDouble[40 + 1];		/* parameters */
	m_I = new XXDouble[20 + 1];		/* initial values */
	m_V = new XXDouble[213 + 1];		/* variables */
	m_s = new XXDouble[20 + 1];		/* states */
	m_R = new XXDouble[20 + 1];		/* rates (or new states) */
	m_M = new XXMatrix[22 + 1];		/* matrices */
	m_U = new XXDouble[0 + 1];		/* unnamed */
	m_workarray = new XXDouble[0 + 1];

	Reset(0.0);
	m_finish_time = 100.0;
}

void Heater::Reset(XXDouble starttime)
{
	m_start_time = starttime;
	m_step_size = 0.0025;
	m_time = starttime;
	m_major = true;
	m_stop_run = false;

	/* Clear the allocated variable memory */
	memset(m_C, 0, (1 + 1) * sizeof(XXDouble));
	memset(m_P, 0, (40 + 1) * sizeof(XXDouble));
	memset(m_I, 0, (20 + 1) * sizeof(XXDouble));
	memset(m_V, 0, (213 + 1) * sizeof(XXDouble));
	memset(m_s, 0, (20 + 1) * sizeof(XXDouble));
	memset(m_R, 0, (20 + 1) * sizeof(XXDouble));
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


	/* set the parameters */
	m_P[0] = 7.0;		/* situationInput */
	m_P[1] = 1.0e6;		/* timeMax {s} */
	m_P[2] = 2.0;		/* mWater {kg} */
	m_P[3] = 8.0;		/* mSteel {kg} */
	m_P[4] = 5.0;		/* nLayer */
	m_P[5] = 4180.0;		/* cpWater {J/kg} */
	m_P[6] = 500.0;		/* cpSteel {J/kg} */
	m_P[7] = 298.0;		/* TInit {K} */
	m_P[8] = 0.001;		/* RSteel {K/W} */
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
	m_P[36] = 800.0;		/* LayerLast\CSteel\C {J/K} */
	m_P[37] = 1672.0;		/* LayerLast\CWater4\C {J/K} */
	m_P[38] = 2.0e-4;		/* LayerLast\C_gas_1\v_gas {m3} */
	m_P[39] = 2.0e-7;		/* LayerLast\R_gas\flowConductanceLayer */


	/* set the initial values */
	m_I[0] = 238400.0;		/* Layer1\CSteel\Q_init {J} */
	m_I[1] = 498256.0;		/* Layer1\CWater4\Q_init {J} */
	m_I[2] = 2.29008559702441e-4;		/* Layer1\C_gas_1\m_gas_init {kg} */
	m_I[3] = 58.2162334100266;		/* Layer1\C_gas_1\U_gas_init {J} */
	m_I[4] = 238400.0;		/* Layer2\CSteel\Q_init {J} */
	m_I[5] = 498256.0;		/* Layer2\CWater4\Q_init {J} */
	m_I[6] = 2.29008559702441e-4;		/* Layer2\C_gas_1\m_gas_init {kg} */
	m_I[7] = 58.2162334100266;		/* Layer2\C_gas_1\U_gas_init {J} */
	m_I[8] = 238400.0;		/* Layer3\CSteel\Q_init {J} */
	m_I[9] = 498256.0;		/* Layer3\CWater4\Q_init {J} */
	m_I[10] = 2.29008559702441e-4;		/* Layer3\C_gas_1\m_gas_init {kg} */
	m_I[11] = 58.2162334100266;		/* Layer3\C_gas_1\U_gas_init {J} */
	m_I[12] = 238400.0;		/* Layer4\CSteel\Q_init {J} */
	m_I[13] = 498256.0;		/* Layer4\CWater4\Q_init {J} */
	m_I[14] = 2.29008559702441e-4;		/* Layer4\C_gas_1\m_gas_init {kg} */
	m_I[15] = 58.2162334100266;		/* Layer4\C_gas_1\U_gas_init {J} */
	m_I[16] = 238400.0;		/* LayerLast\CSteel\Q_init {J} */
	m_I[17] = 498256.0;		/* LayerLast\CWater4\Q_init {J} */
	m_I[18] = 2.29008559702441e-4;		/* LayerLast\C_gas_1\m_gas_init {kg} */
	m_I[19] = 58.2162334100266;		/* LayerLast\C_gas_1\U_gas_init {J} */


	/* set the states */
	m_s[0] = m_I[0];		/* Layer1\CSteel\state {J} */
	m_s[1] = m_I[1];		/* Layer1\CWater4\state {J} */
	m_s[2] = m_I[2];		/* Layer1\C_gas_1\m_gas {kg} */
	m_s[3] = m_I[3];		/* Layer1\C_gas_1\U_gas {J} */
	m_s[4] = m_I[4];		/* Layer2\CSteel\state {J} */
	m_s[5] = m_I[5];		/* Layer2\CWater4\state {J} */
	m_s[6] = m_I[6];		/* Layer2\C_gas_1\m_gas {kg} */
	m_s[7] = m_I[7];		/* Layer2\C_gas_1\U_gas {J} */
	m_s[8] = m_I[8];		/* Layer3\CSteel\state {J} */
	m_s[9] = m_I[9];		/* Layer3\CWater4\state {J} */
	m_s[10] = m_I[10];		/* Layer3\C_gas_1\m_gas {kg} */
	m_s[11] = m_I[11];		/* Layer3\C_gas_1\U_gas {J} */
	m_s[12] = m_I[12];		/* Layer4\CSteel\state {J} */
	m_s[13] = m_I[13];		/* Layer4\CWater4\state {J} */
	m_s[14] = m_I[14];		/* Layer4\C_gas_1\m_gas {kg} */
	m_s[15] = m_I[15];		/* Layer4\C_gas_1\U_gas {J} */
	m_s[16] = m_I[16];		/* LayerLast\CSteel\state {J} */
	m_s[17] = m_I[17];		/* LayerLast\CWater4\state {J} */
	m_s[18] = m_I[18];		/* LayerLast\C_gas_1\m_gas {kg} */
	m_s[19] = m_I[19];		/* LayerLast\C_gas_1\U_gas {J} */


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
	m_M[16].mat = &m_V[164];		/* LayerLast\C_gas_1\pIn.e */
	m_M[16].rows = 2;
	m_M[16].columns = 1;
	m_M[17].mat = &m_V[166];		/* LayerLast\C_gas_1\pOut.e */
	m_M[17].rows = 2;
	m_M[17].columns = 1;
	m_M[18].mat = &m_V[184];		/* LayerLast\R_gas\pIn.f */
	m_M[18].rows = 2;
	m_M[18].columns = 1;
	m_M[19].mat = &m_V[186];		/* LayerLast\R_gas\pOut.f */
	m_M[19].rows = 2;
	m_M[19].columns = 1;
	m_M[20].mat = &m_V[199];		/* Se\p.e */
	m_M[20].rows = 2;
	m_M[20].columns = 1;
	m_M[21].mat = &m_V[202];		/* Sf\p.f */
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
		m_I[0] = m_P[20] * m_P[7];

		/* Layer1\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[21] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer1\CWater4\Q_init = Layer1\CWater4\C * TInit; */
		m_I[1] = m_P[21] * m_P[7];

		/* Layer1\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[22] = m_P[13] / m_P[4];

		/* Layer1\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[21] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer1\C_gas_1\m_gas_init = Layer1\C_gas_1\rho_init * Layer1\C_gas_1\v_gas; */
		m_I[2] = m_V[21] * m_P[22];

		/* Layer1\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[19] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer1\C_gas_1\U_gas_init = Layer1\C_gas_1\u_init * Layer1\C_gas_1\m_gas_init; */
		m_I[3] = m_V[19] * m_I[2];

		/* Layer1\RSteel\R = RSteel / nLayer; */
		m_V[32] = m_P[8] / m_P[4];

		/* Layer1\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[23] = m_P[18] / m_P[4];

		/* Layer2\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[24] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer2\CSteel\Q_init = Layer2\CSteel\C * TInit; */
		m_I[4] = m_P[24] * m_P[7];

		/* Layer2\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[25] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer2\CWater4\Q_init = Layer2\CWater4\C * TInit; */
		m_I[5] = m_P[25] * m_P[7];

		/* Layer2\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[26] = m_P[13] / m_P[4];

		/* Layer2\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[60] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer2\C_gas_1\m_gas_init = Layer2\C_gas_1\rho_init * Layer2\C_gas_1\v_gas; */
		m_I[6] = m_V[60] * m_P[26];

		/* Layer2\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[58] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer2\C_gas_1\U_gas_init = Layer2\C_gas_1\u_init * Layer2\C_gas_1\m_gas_init; */
		m_I[7] = m_V[58] * m_I[6];

		/* Layer2\RSteel\R = RSteel / nLayer; */
		m_V[71] = m_P[8] / m_P[4];

		/* Layer2\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[27] = m_P[18] / m_P[4];

		/* Layer3\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[28] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer3\CSteel\Q_init = Layer3\CSteel\C * TInit; */
		m_I[8] = m_P[28] * m_P[7];

		/* Layer3\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[29] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer3\CWater4\Q_init = Layer3\CWater4\C * TInit; */
		m_I[9] = m_P[29] * m_P[7];

		/* Layer3\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[30] = m_P[13] / m_P[4];

		/* Layer3\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[99] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer3\C_gas_1\m_gas_init = Layer3\C_gas_1\rho_init * Layer3\C_gas_1\v_gas; */
		m_I[10] = m_V[99] * m_P[30];

		/* Layer3\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[97] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer3\C_gas_1\U_gas_init = Layer3\C_gas_1\u_init * Layer3\C_gas_1\m_gas_init; */
		m_I[11] = m_V[97] * m_I[10];

		/* Layer3\RSteel\R = RSteel / nLayer; */
		m_V[110] = m_P[8] / m_P[4];

		/* Layer3\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[31] = m_P[18] / m_P[4];

		/* Layer4\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[32] = (m_P[6] * m_P[3]) / m_P[4];

		/* Layer4\CSteel\Q_init = Layer4\CSteel\C * TInit; */
		m_I[12] = m_P[32] * m_P[7];

		/* Layer4\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[33] = (m_P[5] * m_P[2]) / m_P[4];

		/* Layer4\CWater4\Q_init = Layer4\CWater4\C * TInit; */
		m_I[13] = m_P[33] * m_P[7];

		/* Layer4\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[34] = m_P[13] / m_P[4];

		/* Layer4\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[138] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* Layer4\C_gas_1\m_gas_init = Layer4\C_gas_1\rho_init * Layer4\C_gas_1\v_gas; */
		m_I[14] = m_V[138] * m_P[34];

		/* Layer4\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[136] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* Layer4\C_gas_1\U_gas_init = Layer4\C_gas_1\u_init * Layer4\C_gas_1\m_gas_init; */
		m_I[15] = m_V[136] * m_I[14];

		/* Layer4\RSteel\R = RSteel / nLayer; */
		m_V[149] = m_P[8] / m_P[4];

		/* Layer4\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[35] = m_P[18] / m_P[4];

		/* LayerLast\CSteel\C = (cpSteel * mSteel) / nLayer; */
		m_P[36] = (m_P[6] * m_P[3]) / m_P[4];

		/* LayerLast\CSteel\Q_init = LayerLast\CSteel\C * TInit; */
		m_I[16] = m_P[36] * m_P[7];

		/* LayerLast\CWater4\C = (cpWater * mWater) / nLayer; */
		m_P[37] = (m_P[5] * m_P[2]) / m_P[4];

		/* LayerLast\CWater4\Q_init = LayerLast\CWater4\C * TInit; */
		m_I[17] = m_P[37] * m_P[7];

		/* LayerLast\C_gas_1\v_gas = heater_volume / nLayer; */
		m_P[38] = m_P[13] / m_P[4];

		/* LayerLast\C_gas_1\rho_init = (M * p_init) / (R * TInit); */
		m_V[177] = (m_P[14] * m_P[11]) / (m_C[0] * m_P[7]);

		/* LayerLast\C_gas_1\m_gas_init = LayerLast\C_gas_1\rho_init * LayerLast\C_gas_1\v_gas; */
		m_I[18] = m_V[177] * m_P[38];

		/* LayerLast\C_gas_1\u_init = (cp_gas - R / M) * TInit; */
		m_V[175] = (m_P[15] - m_C[0] / m_P[14]) * m_P[7];

		/* LayerLast\C_gas_1\U_gas_init = LayerLast\C_gas_1\u_init * LayerLast\C_gas_1\m_gas_init; */
		m_I[19] = m_V[175] * m_I[18];

		/* LayerLast\RSteel\R = RSteel / nLayer; */
		m_V[183] = m_P[8] / m_P[4];

		/* LayerLast\R_gas\flowConductanceLayer = flowConductance / nLayer; */
		m_P[39] = m_P[18] / m_P[4];

}

/* This function calculates the static equations of the model.
 * These equations are only dependent from parameters and constants
 */
void Heater::CalculateStatic (void)
{
	/* Se\p.e = [p_init; 0]; */
	m_M[20].mat[0] = m_P[11];
	m_M[20].mat[1] = 0.0;

	/* [LayerLast\R_gas\pressureOut; LayerLast\R_gas\hOut] = Se\p.e; */
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
	/* if (time > timeMax) */
	if (m_time > m_P[1])
	{
		/* stopsimulation */
		XXStopSimulation ( "End of measurement", 0);

	}

	/* Layer1\CSteel\p.T = Layer1\CSteel\state / Layer1\CSteel\C; */
	m_V[6] = m_s[0] / m_P[20];

	/* Layer1\CWater4\p.T = Layer1\CWater4\state / Layer1\CWater4\C; */
	m_V[7] = m_s[1] / m_P[21];

	/* Layer1\C_gas_1\u = Layer1\C_gas_1\U_gas / Layer1\C_gas_1\m_gas; */
	m_V[18] = m_s[3] / m_s[2];

	/* Layer1\C_gas_1\rho = Layer1\C_gas_1\m_gas / Layer1\C_gas_1\v_gas; */
	m_V[20] = m_s[2] / m_P[22];

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
	m_V[45] = m_s[4] / m_P[24];

	/* Layer2\CWater4\p.T = Layer2\CWater4\state / Layer2\CWater4\C; */
	m_V[46] = m_s[5] / m_P[25];

	/* Layer2\C_gas_1\u = Layer2\C_gas_1\U_gas / Layer2\C_gas_1\m_gas; */
	m_V[57] = m_s[7] / m_s[6];

	/* Layer2\C_gas_1\rho = Layer2\C_gas_1\m_gas / Layer2\C_gas_1\v_gas; */
	m_V[59] = m_s[6] / m_P[26];

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
	m_V[84] = m_s[8] / m_P[28];

	/* Layer3\CWater4\p.T = Layer3\CWater4\state / Layer3\CWater4\C; */
	m_V[85] = m_s[9] / m_P[29];

	/* Layer3\C_gas_1\u = Layer3\C_gas_1\U_gas / Layer3\C_gas_1\m_gas; */
	m_V[96] = m_s[11] / m_s[10];

	/* Layer3\C_gas_1\rho = Layer3\C_gas_1\m_gas / Layer3\C_gas_1\v_gas; */
	m_V[98] = m_s[10] / m_P[30];

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
	m_V[123] = m_s[12] / m_P[32];

	/* Layer4\CWater4\p.T = Layer4\CWater4\state / Layer4\CWater4\C; */
	m_V[124] = m_s[13] / m_P[33];

	/* Layer4\C_gas_1\u = Layer4\C_gas_1\U_gas / Layer4\C_gas_1\m_gas; */
	m_V[135] = m_s[15] / m_s[14];

	/* Layer4\C_gas_1\rho = Layer4\C_gas_1\m_gas / Layer4\C_gas_1\v_gas; */
	m_V[137] = m_s[14] / m_P[34];

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

	/* LayerLast\CSteel\p.T = LayerLast\CSteel\state / LayerLast\CSteel\C; */
	m_V[162] = m_s[16] / m_P[36];

	/* LayerLast\CWater4\p.T = LayerLast\CWater4\state / LayerLast\CWater4\C; */
	m_V[163] = m_s[17] / m_P[37];

	/* LayerLast\C_gas_1\u = LayerLast\C_gas_1\U_gas / LayerLast\C_gas_1\m_gas; */
	m_V[174] = m_s[19] / m_s[18];

	/* LayerLast\C_gas_1\rho = LayerLast\C_gas_1\m_gas / LayerLast\C_gas_1\v_gas; */
	m_V[176] = m_s[18] / m_P[38];

	/* LayerLast\C_gas_1\T = LayerLast\C_gas_1\u / (cp_gas - R / M); */
	m_V[168] = m_V[174] / (m_P[15] - m_C[0] / m_P[14]);

	/* LayerLast\C_gas_1\p = (((LayerLast\C_gas_1\rho * R) * LayerLast\C_gas_1\T) / M); */
	m_V[169] = (((m_V[176] * m_C[0]) * m_V[168]) / m_P[14]);

	/* LayerLast\C_gas_1\h = LayerLast\C_gas_1\u + LayerLast\C_gas_1\p / LayerLast\C_gas_1\rho; */
	m_V[178] = m_V[174] + m_V[169] / m_V[176];

	/* LayerLast\C_gas_1\pIn.e = [LayerLast\C_gas_1\p; LayerLast\C_gas_1\h]; */
	m_M[16].mat[0] = m_V[169];
	m_M[16].mat[1] = m_V[178];

	/* LayerLast\C_gas_1\pOut.e = [LayerLast\C_gas_1\p; LayerLast\C_gas_1\h]; */
	m_M[17].mat[0] = m_V[169];
	m_M[17].mat[1] = m_V[178];

	/* GY\dm_water = dm_water; */
	m_V[4] = m_V[210];

	/* Sf\P_NG = P_natural_gas; */
	m_V[204] = m_V[211];

	/* Retour\effort = Tin; */
	m_V[198] = m_V[212];

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

	/* [LayerLast\R_gas\pressureIn; LayerLast\R_gas\hIn] = LayerLast\C_gas_1\pOut.e; */
	m_V[190] = m_M[17].mat[0];
	m_V[193] = m_M[17].mat[1];

	/* Sf\dm = Sf\P_NG / (cp_gas * (Tburner - TInit)); */
	m_V[206] = m_V[204] / (m_P[15] * (m_P[16] - m_P[7]));

	/* Sf\dH = (Sf\dm * Tburner) * cp_gas; */
	m_V[205] = (m_V[206] * m_P[16]) * m_P[15];

	/* Sf\p.f = [Sf\dm; Sf\dH]; */
	m_M[21].mat[0] = m_V[206];
	m_M[21].mat[1] = m_V[205];

	/* Sf1\r = GY\dm_water * cpWater; */
	m_V[208] = m_V[4] * m_P[5];

	/* GY\p2.dQ = GY\r * Retour\effort; */
	m_V[3] = m_V[5] * m_V[198];

	/* GY\p1.dQ = GY\r * Retour\effort; */
	m_V[2] = m_V[5] * m_V[198];

	/* Layer1\OneJunction4\p2.T = Layer1\CWater4\p.T - Layer1\CSteel\p.T; */
	m_V[27] = m_V[7] - m_V[6];

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

	/* Layer2\OneJunction4\p2.T = Layer2\CWater4\p.T - Layer2\CSteel\p.T; */
	m_V[66] = m_V[46] - m_V[45];

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

	/* Layer3\OneJunction4\p2.T = Layer3\CWater4\p.T - Layer3\CSteel\p.T; */
	m_V[105] = m_V[85] - m_V[84];

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

	/* Layer4\OneJunction4\p2.T = Layer4\CWater4\p.T - Layer4\CSteel\p.T; */
	m_V[144] = m_V[124] - m_V[123];

	/* [Layer4\R_gas\pressureOut; Layer4\R_gas\hOut] = LayerLast\C_gas_1\pIn.e; */
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

	/* LayerLast\OneJunction4\p2.T = LayerLast\CWater4\p.T - LayerLast\CSteel\p.T; */
	m_V[180] = m_V[163] - m_V[162];

	/* [Layer1\C_gas_1\dmOut; Layer1\C_gas_1\dHOut] = Layer1\R_gas\pIn.f; */
	m_V[16] = m_M[2].mat[0];
	m_V[17] = m_M[2].mat[1];

	/* Layer1\OneJunction1\p2.T = Layer1\C_gas_1\T - Layer1\CSteel\p.T; */
	m_V[26] = m_V[12] - m_V[6];

	/* [Layer2\C_gas_1\dmOut; Layer2\C_gas_1\dHOut] = Layer2\R_gas\pIn.f; */
	m_V[55] = m_M[6].mat[0];
	m_V[56] = m_M[6].mat[1];

	/* Layer2\OneJunction1\p2.T = Layer2\C_gas_1\T - Layer2\CSteel\p.T; */
	m_V[65] = m_V[51] - m_V[45];

	/* [Layer3\C_gas_1\dmOut; Layer3\C_gas_1\dHOut] = Layer3\R_gas\pIn.f; */
	m_V[94] = m_M[10].mat[0];
	m_V[95] = m_M[10].mat[1];

	/* Layer3\OneJunction1\p2.T = Layer3\C_gas_1\T - Layer3\CSteel\p.T; */
	m_V[104] = m_V[90] - m_V[84];

	/* [Layer4\C_gas_1\dmOut; Layer4\C_gas_1\dHOut] = Layer4\R_gas\pIn.f; */
	m_V[133] = m_M[14].mat[0];
	m_V[134] = m_M[14].mat[1];

	/* Layer4\OneJunction1\p2.T = Layer4\C_gas_1\T - Layer4\CSteel\p.T; */
	m_V[143] = m_V[129] - m_V[123];

	/* LayerLast\OneJunction1\p2.T = LayerLast\C_gas_1\T - LayerLast\CSteel\p.T; */
	m_V[179] = m_V[168] - m_V[162];

	/* if LayerLast\R_gas\pressureIn > LayerLast\R_gas\pressureOut */
	if (m_V[190] > m_V[191])
	{
		/* LayerLast\R_gas\h = LayerLast\R_gas\hIn; */
		m_V[192] = m_V[193];
	}
	else
	{
		/* LayerLast\R_gas\h = LayerLast\R_gas\hOut; */
		m_V[192] = m_V[194];
	}

	/* LayerLast\R_gas\dm = LayerLast\R_gas\flowConductanceLayer * (LayerLast\R_gas\pressureIn - LayerLast\R_gas\pressureOut); */
	m_V[188] = m_P[39] * (m_V[190] - m_V[191]);

	/* LayerLast\R_gas\dH = LayerLast\R_gas\dm * LayerLast\R_gas\h; */
	m_V[189] = m_V[188] * m_V[192];

	/* LayerLast\R_gas\pIn.f = [LayerLast\R_gas\dm; LayerLast\R_gas\dH]; */
	m_M[18].mat[0] = m_V[188];
	m_M[18].mat[1] = m_V[189];

	/* LayerLast\R_gas\pOut.f = [LayerLast\R_gas\dm; LayerLast\R_gas\dH]; */
	m_M[19].mat[0] = m_V[188];
	m_M[19].mat[1] = m_V[189];

	/* Sf1\p.f = Sf1\r * Layer1\CWater4\p.T; */
	m_V[207] = m_V[208] * m_V[7];

	/* [Layer1\C_gas_1\dmIn; Layer1\C_gas_1\dHIn] = Sf\p.f; */
	m_V[14] = m_M[21].mat[0];
	m_V[15] = m_M[21].mat[1];

	/* Layer1\C_gas_1\m_gas_dot = Layer1\C_gas_1\dmIn - Layer1\C_gas_1\dmOut; */
	m_R[2] = m_V[14] - m_V[16];

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

	/* [Layer2\C_gas_1\dmIn; Layer2\C_gas_1\dHIn] = Layer1\R_gas\pOut.f; */
	m_V[53] = m_M[3].mat[0];
	m_V[54] = m_M[3].mat[1];

	/* Layer2\C_gas_1\m_gas_dot = Layer2\C_gas_1\dmIn - Layer2\C_gas_1\dmOut; */
	m_R[6] = m_V[53] - m_V[55];

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

	/* [Layer3\C_gas_1\dmIn; Layer3\C_gas_1\dHIn] = Layer2\R_gas\pOut.f; */
	m_V[92] = m_M[7].mat[0];
	m_V[93] = m_M[7].mat[1];

	/* Layer3\C_gas_1\m_gas_dot = Layer3\C_gas_1\dmIn - Layer3\C_gas_1\dmOut; */
	m_R[10] = m_V[92] - m_V[94];

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

	/* [Layer4\C_gas_1\dmIn; Layer4\C_gas_1\dHIn] = Layer3\R_gas\pOut.f; */
	m_V[131] = m_M[11].mat[0];
	m_V[132] = m_M[11].mat[1];

	/* Layer4\C_gas_1\m_gas_dot = Layer4\C_gas_1\dmIn - Layer4\C_gas_1\dmOut; */
	m_R[14] = m_V[131] - m_V[133];

	/* Layer4\GY1\p2.dQ = Layer4\GY1\r * LayerLast\CWater4\p.T; */
	m_V[141] = m_V[142] * m_V[163];

	/* Layer4\GY1\p1.dQ = Layer4\GY1\r * LayerLast\CWater4\p.T; */
	m_V[140] = m_V[142] * m_V[163];

	/* Layer4\R\p.f = Layer4\OneJunction1\p2.T / RHX; */
	m_V[145] = m_V[143] / m_P[19];

	/* if LayerLast\CWater4\p.T > Layer4\CWater4\p.T */
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

	/* Layer4\R1\flow = (LayerLast\CWater4\p.T - Layer4\CWater4\p.T) * Layer4\R1\c; */
	m_V[147] = (m_V[163] - m_V[124]) * m_V[146];

	/* [LayerLast\C_gas_1\dmIn; LayerLast\C_gas_1\dHIn] = Layer4\R_gas\pOut.f; */
	m_V[170] = m_M[15].mat[0];
	m_V[171] = m_M[15].mat[1];

	/* [LayerLast\C_gas_1\dmOut; LayerLast\C_gas_1\dHOut] = LayerLast\R_gas\pIn.f; */
	m_V[172] = m_M[18].mat[0];
	m_V[173] = m_M[18].mat[1];

	/* LayerLast\C_gas_1\m_gas_dot = LayerLast\C_gas_1\dmIn - LayerLast\C_gas_1\dmOut; */
	m_R[18] = m_V[170] - m_V[172];

	/* LayerLast\R\p.f = LayerLast\OneJunction1\p2.T / RHX; */
	m_V[181] = m_V[179] / m_P[19];

	/* Layer1\ZeroJunction14\p1.dQ = Layer1\R1\flow + Layer1\GY1\p1.dQ; */
	m_V[44] = m_V[30] + m_V[23];

	/* Layer2\ZeroJunction14\p1.dQ = Layer2\R1\flow + Layer2\GY1\p1.dQ; */
	m_V[83] = m_V[69] + m_V[62];

	/* Layer3\ZeroJunction14\p1.dQ = Layer3\R1\flow + Layer3\GY1\p1.dQ; */
	m_V[122] = m_V[108] + m_V[101];

	/* Layer4\ZeroJunction14\p1.dQ = Layer4\R1\flow + Layer4\GY1\p1.dQ; */
	m_V[161] = m_V[147] + m_V[140];

	/* PlusMinus\output = Sf\p.f[2] - LayerLast\R_gas\pOut.f[2]; */
	m_V[195] = m_M[21].mat[1] - m_M[19].mat[1];

	/* Layer1\C_gas_1\U_gas_dot = (Layer1\C_gas_1\dHIn - Layer1\C_gas_1\dHOut) - Layer1\R\p.f; */
	m_R[3] = (m_V[15] - m_V[17]) - m_V[28];

	/* Layer2\C_gas_1\U_gas_dot = (Layer2\C_gas_1\dHIn - Layer2\C_gas_1\dHOut) - Layer2\R\p.f; */
	m_R[7] = (m_V[54] - m_V[56]) - m_V[67];

	/* Layer3\C_gas_1\U_gas_dot = (Layer3\C_gas_1\dHIn - Layer3\C_gas_1\dHOut) - Layer3\R\p.f; */
	m_R[11] = (m_V[93] - m_V[95]) - m_V[106];

	/* Layer4\C_gas_1\U_gas_dot = (Layer4\C_gas_1\dHIn - Layer4\C_gas_1\dHOut) - Layer4\R\p.f; */
	m_R[15] = (m_V[132] - m_V[134]) - m_V[145];

	/* LayerLast\C_gas_1\U_gas_dot = (LayerLast\C_gas_1\dHIn - LayerLast\C_gas_1\dHOut) - LayerLast\R\p.f; */
	m_R[19] = (m_V[171] - m_V[173]) - m_V[181];

	/* Layer1\RSteel\p.dQ = Layer1\OneJunction4\p2.T / Layer1\RSteel\R; */
	m_V[31] = m_V[27] / m_V[32];

	/* Layer2\RSteel\p.dQ = Layer2\OneJunction4\p2.T / Layer2\RSteel\R; */
	m_V[70] = m_V[66] / m_V[71];

	/* Layer3\RSteel\p.dQ = Layer3\OneJunction4\p2.T / Layer3\RSteel\R; */
	m_V[109] = m_V[105] / m_V[110];

	/* Layer4\RSteel\p.dQ = Layer4\OneJunction4\p2.T / Layer4\RSteel\R; */
	m_V[148] = m_V[144] / m_V[149];

	/* LayerLast\RSteel\p.dQ = LayerLast\OneJunction4\p2.T / LayerLast\RSteel\R; */
	m_V[182] = m_V[180] / m_V[183];

	/* Layer1\CSteel\p.dQ = Layer1\RSteel\p.dQ + Layer1\R\p.f; */
	m_R[0] = m_V[31] + m_V[28];

	/* Layer1\CWater4\p.dQ = (Layer1\GY1\p2.dQ + Layer1\R1\flow) - (Sf1\p.f + Layer1\RSteel\p.dQ); */
	m_R[1] = (m_V[24] + m_V[30]) - (m_V[207] + m_V[31]);

	/* Layer2\CSteel\p.dQ = Layer2\RSteel\p.dQ + Layer2\R\p.f; */
	m_R[4] = m_V[70] + m_V[67];

	/* Layer2\CWater4\p.dQ = (Layer2\GY1\p2.dQ + Layer2\R1\flow) - (Layer1\ZeroJunction14\p1.dQ + Layer2\RSteel\p.dQ); */
	m_R[5] = (m_V[63] + m_V[69]) - (m_V[44] + m_V[70]);

	/* Layer3\CSteel\p.dQ = Layer3\RSteel\p.dQ + Layer3\R\p.f; */
	m_R[8] = m_V[109] + m_V[106];

	/* Layer3\CWater4\p.dQ = (Layer3\GY1\p2.dQ + Layer3\R1\flow) - (Layer2\ZeroJunction14\p1.dQ + Layer3\RSteel\p.dQ); */
	m_R[9] = (m_V[102] + m_V[108]) - (m_V[83] + m_V[109]);

	/* Layer4\CSteel\p.dQ = Layer4\RSteel\p.dQ + Layer4\R\p.f; */
	m_R[12] = m_V[148] + m_V[145];

	/* Layer4\CWater4\p.dQ = (Layer4\GY1\p2.dQ + Layer4\R1\flow) - (Layer3\ZeroJunction14\p1.dQ + Layer4\RSteel\p.dQ); */
	m_R[13] = (m_V[141] + m_V[147]) - (m_V[122] + m_V[148]);

	/* LayerLast\CSteel\p.dQ = LayerLast\RSteel\p.dQ + LayerLast\R\p.f; */
	m_R[16] = m_V[182] + m_V[181];

	/* LayerLast\CWater4\p.dQ = GY\p2.dQ - (Layer4\ZeroJunction14\p1.dQ + LayerLast\RSteel\p.dQ); */
	m_R[17] = m_V[3] - (m_V[161] + m_V[182]);

}

/* This function calculates the output equations of the model.
 * These equations are not needed for calculation of the rates
 * and are kept separate to make the dynamic set of equations smaller.
 * These dynamic equations are called often more than one time for each
 * integration step that is taken. This makes model computation much faster.
 */
void Heater::CalculateOutput (void)
{
	/* enthalpy_in\enthalpyFlow = Sf\p.f[2]; */
	m_V[0] = m_M[21].mat[1];

	/* Tout = Layer1\CWater4\p.T; */
	m_V[209] = m_V[7];

	/* PlusMinus\plus1 = Sf\p.f[2]; */
	m_V[196] = m_M[21].mat[1];

	/* enthalpy_out\enthalpyFlow = LayerLast\R_gas\pOut.f[2]; */
	m_V[1] = m_M[19].mat[1];

	/* PlusMinus\minus1 = LayerLast\R_gas\pOut.f[2]; */
	m_V[197] = m_M[19].mat[1];

	/* Se\powerOut = LayerLast\R_gas\pOut.f[2]; */
	m_V[201] = m_M[19].mat[1];

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
