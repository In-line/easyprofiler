#if defined _easyprofiler_included
	#endinput
#endif
#define _easyprofiler_included

#pragma reqlib easyprofiler
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib easyprofiler
#endif

/**
 * Pushes current time in the profiler virtual stack
 *
 * @noreturn
 */
native ep_start();


/**
 * Pops a time from the profiler virtual stack, calculates return value and
 * prints log message accroding to fmt if it was set.
 *
 * @param count         Divisor for time (iterations count)
 * @param fmt           C style format, where "%f" stands for time
 *
 * @return              Elapsed time for `count` operations +-correction value
 */
native Float:ep_end(count = 1, fmt[] = "");


/**
 * Pauses execution
 *
 * @param time         Time in seconds
 *
 * @return             Return value of linux select(...)
 */
native ep_sleep(Float:time);


/**
 * Sets global correction value
 *
 * @param time         Correction value
 *
 * @noreturn
 */
native ep_set_correction(Float:time);


/**
 * Pops a time from the profiler virtual stack, sets correction, calculates return value,
 * prints log message according to fmt if it was set and correction >0.0.
 *
 * @param count         Divisor for time (iterations count)
 * @param fmt           C style format, where "%f" stands for time
 *
 * @return              Correction value
 */
native ep_end_and_set_correction(count = 1, fmt[] = "");


/**
 * Dummy call that returns immediately
 *
 * @noreturn
 */
native ep_dummy_call();


/**
 * Automatically calibrate easyprofiler.
 *
 * @param n         Number of iterations
 *
 * @noreturn
 */
stock ep_calibrate(n = 50000)
{
	ep_start();
	for(new i = 0; i < n; ++i)
	{
		ep_start();
		ep_end();
	}
	ep_end_and_set_correction(n, "Correction is set to %.17f");
}
