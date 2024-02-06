/*
 * acs758.c
 *
 *  Created on: Jan 19, 2024
 *      Author: mateu
 */

#include "acs758.h"
#include "stdint.h"
#include "adc.h"


void ACS7XX_Init_Default(ACS7XX *AcsStateHandler)
{

	AcsStateHandler->_sensitivity = ACS7XX_SENSITIVITY_DEFAULT;
	AcsStateHandler->_voltage = BOARD_VOLTAGE_DEFAULT;
    AcsStateHandler->_resolution = (double) BOARD_ADC_DEPTH;
    AcsStateHandler->_factor_value = (double) ACS7XX_FACTOR_VALUE;
    AcsStateHandler->_lastCurrent = 0.0;



//    AcsStateHandler->_lastMillis = 0;
//    AcsStateHandler->_AHCounter = 0.0;
//    AcsStateHandler->_CoulombCounter = 0.0;
//    AcsStateHandler->_adc_offset = (int) BOARD_MEASURED_OFFSET;
//	  AcsStateHandler->_voltage_offset = 0.0;
//    AcsStateHandler->_bidir = ACS7XX_BIDIR_DEFAULT;
//	  AcsStateHandler->_pintoread = ACS7XX_PIN_DEFAULT;
//    AcsStateHandler->_movavgexp_alpha = 2.0 / (EXP_MOVAVG_N + 1.0);
//    AcsStateHandler->_movavgexp_loop = 0;
//    AcsStateHandler->_movavgexp_val = 0.0;
}


void ACS7XX_Calibrate(ACS7XX *AcsStateHandler)
{
	uint32_t offset_sum = 0;
	uint16_t n_samples = 1000;  // Number of samples for calibration

	   // Assuming you have ADC_HandleTypeDef hadc1; declared and initialized

	for (uint16_t i = 0; i < n_samples; i++)
	{
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  offset_sum += HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
	}

	// Calculate average ADC reading for offset
	 AcsStateHandler->_offset = (float) offset_sum / n_samples;
}

void ACS7XX_InstantCurrent(ACS7XX *AcsStateHandler, double *current)
{

    // Assuming you have ADC_HandleTypeDef &hadc1; declared and initialized
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint32_t readvalue = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    float readvolt = (((float) readvalue - AcsStateHandler -> _offset) * (AcsStateHandler -> _factor_value) * (2)) / AcsStateHandler -> _resolution;
    float readcur = (readvolt) / AcsStateHandler -> _sensitivity;

    // If current is less than 0.7 A, set it to 0
    if (readcur < 0.7)
    {
        readcur = 0.0;
    }

    *current = readcur;
    AcsStateHandler->_lastCurrent = readcur;
    AcsStateHandler->_lreadvolt = readvolt;
    AcsStateHandler->_lreadvalue = readvalue;
}

void ACS7XX_ResetCounters(ACS7XX *AcsStateHandler)
{

    AcsStateHandler->_lastCurrent = 0.0;


//	 AcsStateHandler->_lastAmperehour = 0.0;
//    AcsStateHandler->_AHCounter = 0.0;
//    AcsStateHandler->_lastCoulomb = 0.0;
//    AcsStateHandler->_CoulombCounter = 0.0;
//    AcsStateHandler->_adc_offset = 0;
//    AcsStateHandler->_voltage_offset = 0.0;
//    AcsStateHandler->_movavgexp_val = 0;
//    AcsStateHandler->_movavgexp_loop = 0;
}

//void ACS7XX_AmpereHourCount(ACS7XX *AcsStateHandler, double *mamperehc) {
//    uint32_t Current_mAh = HAL_GetTick();
//    double timeframehour = (double)(Current_mAh - AcsStateHandler->_lastMillis) / 3600000.0;
//
//    double readcurrent;
//    ACS7XX_InstantCurrent(AcsStateHandler, &readcurrent);
//    *mamperehc = readcurrent * timeframehour;
//
//    AcsStateHandler->_lastMillis = Current_mAh;
//}


//
//void ACS7XX_updateCounters(ACS7XX *AcsStateHandler) {
//    double amperehcTemp;
//    ACS7XX_ampereHourCount(AcsStateHandler, &amperehcTemp);
//    AcsStateHandler->_lastAmperehour = amperehcTemp;
//    AcsStateHandler->_AHCounter += amperehcTemp;
//
//    AcsStateHandler->_lastCoulomb = amperehcTemp * 3.6;
//    AcsStateHandler->_CoulombCounter += AcsStateHandler->_lastCoulomb;
//}
//

//
//void ACS7XX_updateMillis(ACS7XX *AcsStateHandler) {
//	AcsStateHandler->_lastMillis = HAL_GetTick();
//}
//
//void ACS7XX_getAHCount(ACS7XX *AcsStateHandler, double *ahcount) {
//    *ahcount = AcsStateHandler->_AHCounter;
//}
//
//void ACS7XX_getCoulombCount(ACS7XX *AcsStateHandler, double *ccount) {
//    *ccount = AcsStateHandler->_CoulombCounter;
//}
//
//void ACS7XX_movingAvgExp(ACS7XX *AcsStateHandler, double current) {
//    //init moving average exponetial with simple average
//
//    if (AcsStateHandler->_movavgexp_loop < EXP_MOVAVG_LOOP) {
//    	AcsStateHandler->_movavgexp_val += current;
//        if (AcsStateHandler->_movavgexp_loop == (EXP_MOVAVG_LOOP - 1)) AcsStateHandler->_movavgexp_val = AcsStateHandler->_movavgexp_val / (double) EXP_MOVAVG_LOOP;
//        AcsStateHandler->_movavgexp_loop++;
//    }
//    else {
//        double movavgexp = AcsStateHandler->_movavgexp_val + AcsStateHandler->_movavgexp_alpha * (current - AcsStateHandler->_movavgexp_val);
//        AcsStateHandler->_movavgexp_val = movavgexp;
//    }
//}
//
//double ACS7XX_getMovingAvgExp(ACS7XX *AcsStateHandler) {
//    return AcsStateHandler->_movavgexp_val;
//}
//
//void ACS7XX_resetMovingAvgExp(ACS7XX *AcsStateHandler) {
//	AcsStateHandler->_movavgexp_val = 0;
//	AcsStateHandler->_movavgexp_loop = 0;
//}
//
//void ACS7XX_instantCurrent_NoiseReduction(ACS7XX *AcsStateHandler, double *current, double noiseThreshold)
//{
//    // Zwykłe odczytywanie wartości prądu
//    ACS7XX_instantCurrent(AcsStateHandler, current);
//
//    // Zerowanie pomiaru prądu, jeśli spada poniżej progu szumów
//    if (*current < noiseThreshold){
//        *current = 0;
//    }
//}
