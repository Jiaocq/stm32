#ifndef _COMMON_H_
#define _COMMON_H_

#define TEST_RESULT_FAILED -1
#define TEST_RESULT_RUNNING 0
#define TEST_RESULT_PASS    1

#define TEST_COMPLETE           0
#define TEST_MORE_OPERATION     1
#define TEST_FATAL              -1

#define VOLTAGE_TEST_NUM        5
#define MAX_DI_CHANNEL          15
#define MAX_AI_CHANNEL          7
#define MAX_DO_CHANNEL          15
#define MAX_HIO_CHANNEL         11
#define STIMULATION_STABLE_TIME 100
#define VOLTAGE_FOR_2LINE       1000  // in units of mV
#define VOLTAGE_FULL_SCALE      2500UL
#define MAX_AI_GAP              50 // VOLTAGE_FULL_SCALE/100   // in units of mV

#define ERROR_NONE       0
#define ERROR_INIT       1
#define ERROR_MODULE     2
#define ERROR_TEST_FATAL 3

/*
 * Hardware init
 *
 * return value:
 * 0: hardware initi successfully.
 * others: hardware init failed.
 */
int hw_init();

/**feed dog  */
void refersh_watchdog();

/*
 * Get current time in units of ms
 */
unsigned long long get_time_ms();

/*
 * Get test module indication.
 *
 * return value:
 * 0: no module being selected
 * 1: test DI module
 * 2: test DO module
 * 3: test AI module
 * 4: test HIO module
 * -1: failed to get indication or invalid indication.
 *
 */
int get_test_module_flag();

/*
 * get start event
 *
 * return value:
 * 1: start signal arrived
 * 0: no start signal
 */
int get_start_event(int module);

/*
 * set specified module state.
 * The LED of the module should blink by 1/s for IDLE or 5/s for TESTING.
 *
 * input parameters:
 *  module: 1,2,3,4 for DI/DO/AI/HIO respectively.
 *  state : 0,1 for IDLE and TESTING.
 */
void set_module_state(int module, int state, int *result);

/*
 * Set test result for specified module
 * input parameters:
 *  module: 1,2,3,4 for DI/DO/AI/HIO respectively.
 *  result: an int-type array with up to 16 items.
 *
 * The LEDs of the module should follow the definition below.
 *  -1: failed, blink quickly.
 *  0 : testing, turn off
 *  1 : pass, turn on.
 */
void set_module_testing_result(int module, int *result);

/*
 * Set normal running indication.
 */
void set_normal_run_flag();

/*
 * set error indication.
 * error_num: one of ERROR_INIT, ERROR_MODULE, ERROR_TEST_FATAL.
 */
void set_error_indication(int error_num);

/*
 * Set stimulation for terminal board
 *
 * parameters:
 * tb_type  DI~HIO (1~4)
 * channel  1~16 for DI/DO, 1~8 for AI, 1~12 for HIO
 * value    0,1 for DI/DO,
 */
void set_tb_digital_stimulation(int tb_type, int channel, int value);

/*
 * Get output from terminal board by specified channel
 *
 */
int get_tb_digital_output(int tb_type, int channel);

/*
 * Stimulation --> Terminal --> TerminalBoard --> DB50 --> Acquistion
 * Set AI tb stimulation with 2 lines mode.
 * parameters:
 * channel 1~8
 * value   0 disable, 1 enable
 */
void set_tb_ai_2lines_stimulation(int tb_type, int channel, int value);

/*
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel 1~8
 *  value   0~2500, in units of mV
 */
void set_tb_ai_4lines_stimulation(int tb_type, int channel, int value);

/*
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel    1~8
 *  value_A1   voltage at A1 point, in units of mV
 *  value_A2   voltage at A2 point, in units of mV
 */
int  get_tb_ai_output(int tb_type, int channel, int *value_A1, int *value_A2);

/*
 * Stimulation --> DB50 --> TerminalBoard --> Terminal --> Acquistion
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel 1~8
 *  value   0~2500, in units of mV
 */
void set_tb_ao_4lines_stimulation(int tb_type, int channel, int value);

/*
 * Set HIO-AO tb stimulation by 4 lines mode.
 * parameters:
 *  channel    1~8
 *  value_A1   voltage at A1 point, in units of mV
 *  value_A2   voltage at A2 point, in units of mV
 */
int set_tb_ao_stimulation(int tb_type, int channel, int value);

/*
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel    1~8
 *  value_A1   voltage at A1 point, in units of mV
 *  value_A2   voltage at A2 point, in units of mV
 */
int  get_tb_ao_output(int tb_type, int channel, int *value);

/*
 * Test DI terminal board
 *
 * parameters:
 *  result  An array of test result with up to 16 items (channels). Each item should be one of followings:
 *    TEST_RESULT_FAILED
 *    TEST_RESULT_RUNNING
 *    TEST_RESULT_PASS
 *
 * return value:
 * 0: complete
 * 1: more operation.
 */
int test_DI_tb(int *result);

/*
 * Test DO terminal board
 *
 * parameters:
 *  result  An array of test result with up to 16 items (channels). Each item should be one of followings:
 *    TEST_RESULT_FAILED
 *    TEST_RESULT_RUNNING
 *    TEST_RESULT_PASS
 *
 * return value:
 * 0: complete
 * 1: more operation.
 */
int test_DO_tb(int *result);

/*
 * Test AI terminal board
 *
 *  result  An array of test result with up to 16 items (channels). Each item should be one of followings:
 *    TEST_RESULT_FAILED
 *    TEST_RESULT_RUNNING
 *    TEST_RESULT_PASS
 * return value:
 * 0: complete
 * 1: more operation.
 */
int test_AI_tb(int *result);

/*
 * Test HIO terminal board
 *
 *  result  An array of test result with up to 16 items (channels). Each item should be one of followings:
 *    TEST_RESULT_FAILED
 *    TEST_RESULT_RUNNING
 *    TEST_RESULT_PASS
 * return value:
 * 0: complete
 * 1: more operation.
 */
int test_HIO_tb(int *result);

int manage_entry();
#endif
