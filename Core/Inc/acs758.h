/*
 * acs758.h
 *
 *  Created on: Jan 19, 2024
 *      Author: mateu
 */



#ifndef INC_ACS758_H_
#define INC_ACS758_H_





// Default values - default is (.....) ACS758
#define ACS7XX_BIDIR_DEFAULT 1 //Is the sensor bidirectional ?
#define ACS7XX_PIN_DEFAULT	0 //Pin used  for measurements
#define ACS7XX_SENSITIVITY_DEFAULT  0.04 //Sensitivity of the sensor in V/A (divide per 1000 the datasheet value)
#define ACS7XX_FACTOR_VALUE 3.3 // adjust the unit read. For instance, a sensitivity in V/A and a 1000 factor provides a mA reading. 1 => A, 1000 => mA
// Default STM32F411CUE6 value
#define BOARD_MEASURED_OFFSET 100 //ADC may shift its measurement. For instance a shitfted value of 1 out of 1024 steps represents 0.05A for ACS712. In perfect world, BOARD_MEASURED_OFFSET should be 0
#define BOARD_VOLTAGE_DEFAULT 5.0 //Power supply voltage
#define BOARD_ADC_DEPTH 4095 // 10bits: 1024.0, 12bits: 4096.0, 14bits: 16384.0
// Moving Exponential Average init values
#define EXP_MOVAVG_N 10	//history length impact on moving average impact - keep in mind the moving average will be impacted by the measurement frequency too
#define EXP_MOVAVG_LOOP 1 //number of measurements before starting mobile Average - starting with a simple average - 1 allows a quick start. Value must be 1 minimum


typedef struct
{
    float _offset;
    double _lastCurrent;
    double _voltage;
    double _sensitivity;
    double _resolution;
    float _lreadvolt;
    float _lreadvalue;
    double _factor_value;


//    double _lastAmperehour;
//    double _lastCoulomb;
//    double _AHCounter;
//    double _CoulombCounter;
//    float _lreadvolt;
//    float _lreadvalue;
//    int _bidir;
//    int _pintoread;
//
//    int _adc_offset;
//    double _movavgexp_val;
//    double _movavgexp_alpha;
//    int _movavgexp_loop;
} ACS7XX;


void ACS7XX_Calibrate(ACS7XX *AcsStateHandler);
void ACS7XX_Init_Default(ACS7XX *AcsStateHandler);
void ACS7XX_InstantCurrent(ACS7XX* AcsStateHandler, double *current);	    //calculates in mA
void ACS7XX_ResetCounters(ACS7XX* AcsStateHandler);						// reset all counters







//void ACS7XX_ampereHourCount(ACS7XX* AcsStateHandler, double *mamperehc);   // mAh
//void ACS7XX_updateMillis(ACS7XX* AcsStateHandler);							// when starting a new cycle, we need to init Lastmillis
//void ACS7XX_updateCounters(ACS7XX* AcsStateHandler);
//void ACS7XX_getAHCount(ACS7XX* AcsStateHandler, double *mahcount);
//void ACS7XX_getCoulombCount(ACS7XX* sAcsStateHandlerelf, double *ccount);
//double ACS7XX_getMovingAvgExp(ACS7XX* AcsStateHandler);
//void ACS7XX_resetMovingAvgExp(ACS7XX* AcsStateHandler);
//void ACS7XX_movingAvgExp(ACS7XX* AcsStateHandler, double current);
//void ACS7XX_instantCurrent_NoiseReduction(ACS7XX *AcsStateHandler, double *current, double noiseThreshold);


#endif /* INC_ACS758_H_ */


