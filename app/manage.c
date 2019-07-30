#include <stdlib.h>
#include <string.h>
#include "common.h"

#define IDLE    0
#define FATAL   -1
#define TESTING 1

// Terminal Board index
#define DI_TB  1
#define DO_TB  2
#define AI_TB  3
#define HIO_TB 4

static int state = 0;
static int results[4][16] = {{1,}, {1,}, {1,}, {1,}};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
int test_DI_tb(int* result)
{
	static int state_DI_test = 0;
	static int channel_index = 0;
	static unsigned long long time_start = 0;
	static int value = 0;
	static int num = 0;
	int ret;
	ret = TEST_MORE_OPERATION;
	switch(state_DI_test)
	{
	case 0:
		channel_index = 0;
		num = 0;
		value = 0;
		memset(result, 0, 16);
		state_DI_test++;
	case 1:
		set_tb_digital_stimulation(DI_TB, channel_index + 1, value);
		time_start = get_time_ms();
		state_DI_test++;
		break;
	case 2:
		if ((get_time_ms() - time_start) >= STIMULATION_STABLE_TIME)
		{
			if (value != get_tb_digital_output(DI_TB, channel_index + 1))
			{
				result[channel_index] = -1;
			}
			else if (result[channel_index] == 0)
			{
				result[channel_index] = 1;
			}
			value = (value == 0) ? 1 : 0;
			if (++num > 2)
			{
				value = 0;
				num = 0;
				channel_index++;
			}
			if (channel_index > MAX_DI_CHANNEL)
			{
				state_DI_test = 0;
				ret = TEST_COMPLETE;
			}
			else
			{
				state_DI_test = 1;
			}
		}
		break;
	default:
		ret = TEST_FATAL;
		break;
	}
	return ret;
}

const int voltage_values[VOLTAGE_TEST_NUM] = { 0, 500, 1000, 2500, 0};

/*
 * The test for each channel includes 2-line and 4-line tests.
 * The total number of channel is MAX_AI_CHANNEL
 */
int test_AI_tb(int* result)
{
	static int state_AI_test = 0;
	static int channel_index = 0;
	static unsigned long long time_start = 0;
	static int value = 0;
	static int expect_voltage_value = 0;
	static int voltage_value_index = 0;
	int ret;
	int num;
	int voltage_A1;
	int voltage_A2;

	ret = TEST_MORE_OPERATION;
	switch(state_AI_test)
	{
	case 0:
		channel_index = 0;
		num = 0;
		value = 0;
		voltage_value_index = 0;
		memset(result, 0, 16);
		state_AI_test++;
	case 1:
		// 2-line mode
		expect_voltage_value = (value == 0) ? 0 :VOLTAGE_FOR_2LINE;
		set_tb_ai_2lines_stimulation(AI_TB, channel_index + 1, value);
		time_start = get_time_ms();
		state_AI_test = 2;
		break;
	case 2:
		if ((get_time_ms() - time_start) > STIMULATION_STABLE_TIME)
		{
			get_tb_ai_output(DI_TB, channel_index + 1, &voltage_A1, &voltage_A2);
			if ((abs(expect_voltage_value - voltage_A1) > MAX_AI_GAP)
				|| (abs(voltage_A2 - (voltage_A1 / 2)) > MAX_AI_GAP))
			{
				result[channel_index] = -1;
			}
			else if (result[channel_index] == 0)
			{
				result[channel_index] = 1;
			}
			value = (value == 0) ? 1 : 0;
			if (++num > 2)
			{
				value = 0;
				num = 0;
				state_AI_test = 3;
			}
			else
			{
				state_AI_test = 1;
			}
		}
		break;
	case 3:
		// 4-line mode
		// There're some voltage values in voltage_value to test.
		set_tb_ai_4lines_stimulation(AI_TB, channel_index + 1, voltage_values[voltage_value_index]);
		time_start = get_time_ms();
		state_AI_test = 4;
		break;
	case 4:
		if ((get_time_ms() - time_start) > STIMULATION_STABLE_TIME)
		{
			get_tb_ai_output(DI_TB, channel_index + 1, &voltage_A1, &voltage_A2);
			if ((abs(voltage_values[voltage_value_index] - voltage_A1) > MAX_AI_GAP)
				|| (abs(voltage_A2 - (voltage_A1 / 2)) > MAX_AI_GAP))
			{
				result[channel_index] = -1;
			}
			else if (result[channel_index] == 0)
			{
				result[channel_index] = 1;
			}
			if (++voltage_value_index > VOLTAGE_TEST_NUM)
			{
				if (++channel_index > MAX_AI_CHANNEL)
				{
					state_AI_test = 0;
					ret = TEST_COMPLETE;
				}
				else
				{
					// start next channel test.
					state_AI_test = 1;
				}
			}
			else
			{
				state_AI_test = 3;
			}
		}
		break;
	default:
		ret = TEST_FATAL;
		break;
	}
	return ret;
}
int test_DO_tb(int* result)
{
	return 0;
}
int test_HIO_tb(int* result)
{
	return 0;
}

int manage_entry()
{
	int module;
	int ret;
	int start_event;
	int (*pfn[4])(int *) = { test_DI_tb, test_DO_tb, test_AI_tb, test_HIO_tb};
	if (0 != hw_init())
	{
		state = FATAL;
	}
	else
	{
		state = IDLE;
	}
	while(1)
	{
		set_normal_run_flag();
		switch (state)
		{
		case FATAL:
			set_error_indication(ERROR_INIT);
			break;
		case IDLE:
			module = get_test_module_flag();
			if ((module < 1) || (module > 4))
			{
				set_error_indication(ERROR_MODULE);
			}
			else
			{
				set_error_indication(ERROR_NONE);
				// Set state and result for specified module.
				set_module_state(module, state);
				set_module_testing_result(module, results[module - 1]);

				// Detect start event.
				start_event = get_start_event();
				if (start_event)
				{
					state = TESTING;
				}
			}
			break;
		case TESTING:
			ret = pfn[module - 1](results[module - 1]);
			switch(ret)
			{
			case TEST_COMPLETE:
				state = IDLE;
				break;
			case TEST_MORE_OPERATION:
				set_module_state(module, state);
				set_module_testing_result(module, results[module - 1]);
				break;
			default:
				set_error_indication(ERROR_TEST_FATAL);
				break;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
#pragma GCC diagnostic pop
