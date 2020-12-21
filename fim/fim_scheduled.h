/**
 * Proof of concept: Monitoring file using SHA1
 */

#ifndef _FIM_SCHEDULED_H
#define _FIM_SCHEDULED_H

#include <stdbool.h>

/**
 * Monitoring file passed as parameter.
 */
void fim_monitoring();

/**
 * Set the scan interval.
 */
bool fim_set_configuration(short interval);

/**
 * Set file to monitor
 */
bool fim_set_file_watched(const char *file);

#endif
