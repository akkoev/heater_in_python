/**********************************************************
 * This file is generated by the 20-sim C++ Code Generator
 *
 *  file:  Heater.h
 *  subm:  Heater
 *  model: heater
 *  expmt: heater
 *  date:  October 26, 2018
 *  time:  3:48:46 PM
 *  user:  Johannes Burger
 *  from:  Cooll Sustainable Energy Solutions BV, 20-sim 4.7 Professional Single
 *  build: 4.7.1.8902
 *
 **********************************************************/

/* This file describes the model functions
   that are supplied for computation.

   The model itself is the Heater.cpp file
*/
#ifndef Heater_H
#define Heater_H

/* 20-sim include files */
#include "common/xxfuncs.h"
#include "common/xxmatrix.h"
#include "common/xxmodel.h"
#include "common/xxinteg.h"


class Heater: virtual public Submodel20sim
{
	public:
		enum stateflags_Heater {initialrun, mainrun, finished};

		/**
		 * Heater constructor
		 */
		Heater(void);

		/**
		 * Heater destructor
		 */
		virtual ~Heater(void);


		


		/**
		 * Heater Initialization of the model and calculation of the values for the start time t
		 * @param u	This is the array with all input signals for this submodel
		 * @param y	This is the array with all output signals from this submodel
		 * @param t This is the start time for this run
		 */
		void Initialize (XXDouble *u, XXDouble *y, XXDouble t);

		/**
		 * Heater Calculate
		 * @param u	This is the array with all input signals for this submodel
		 * @param y	This is the array with all output signals from this submodel
		 */
		void Calculate (XXDouble *u, XXDouble *y /*, XXDouble t*/ );

		/**
		 * Heater Terminate
		 * @param u	This is the array with all input signals for this submodel
		 * @param y	This is the array with all output signals from this submodel
		 */
		void Terminate (XXDouble *u, XXDouble *y /*, XXDouble t*/ );


		/**
		 * SetFinishTime()
		 * @brief Overrrides the default finish time (from 20-sim) for this submodel
		 * @param time is the wanted finish time. Use 0.0 to change it to infinite.
		 * 
		 */
		bool SetFinishTime(XXDouble newtime);

		bool IsFinished(void);
		/**
		 * Reset()
		 * @brief Resets the submodel back to its initial state for a new run
		 */
		void Reset(XXDouble starttime);

		stateflags_Heater state;

	protected:
		/**
		 * CalculateDynamic()
		 * This function calculates the dynamic equations of the model.
		 * These equations are called from the integration method
		 * to calculate the new model rates (that are then integrated).
		 */
		void CalculateDynamic (void);

	private:
		/* internal submodel computation methods */

		/**
		 * CalculateInitial()
		 * This function calculates the initial equations of the model.
		 * These equations are calculated before anything else
		 */
		void CalculateInitial (void);

		/**
		 * CalculateStatic()
		 * This function calculates the static equations of the model.
		 * These equations are only dependent from parameters and constants
		 */
		void CalculateStatic (void);

		/**
		 * CalculateInput()
		 * This function calculates the input equations of the model.
		 * These equations are dynamic equations that must not change
		 * in calls from the integration method (like random and delay).
		 */
		void CalculateInput (void);

		/**
		 * CalculateOutput()
		 * This function calculates the output equations of the model.
		 * These equations are not needed for calculation of the rates
		 * and are kept separate to make the dynamic set of equations smaller.
		 * These dynamic equations are called often more than one time for each
		 * integration step that is taken. This makes model computation much faster.
		 */
		void CalculateOutput (void);

		/**
		 * CalculateFinal()
		 * This function calculates the final equations of the model.
		 * These equations are calculated after all the calculations
		 * are performed
		 */
		void CalculateFinal (void);

		/**
		 * CopyInputsToVariables
		 * This private function copies the input variables from the input vector
		 * @param u	This is the array with all input signals for this submodel
		 */
		void CopyInputsToVariables (XXDouble *u);

		/**
		 * CopyVariablesToOutputs
		 * This private function copies the output variables to the output vector
		 * @param y	This is the array with all output signals from this submodel
		 */
		void CopyVariablesToOutputs (XXDouble *y);


		XXBoolean XXStopSimulation (XXString message, XXInteger id);

		RungeKutta4 myintegmethod;	///< pointer to the integration method for this submodel
};

#endif	// Heater_H
