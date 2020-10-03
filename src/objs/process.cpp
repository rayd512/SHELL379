#include "process.h"

using namespace std;

/** Constructor method for the process
 *
 * @param id the PID 
 * @param command the comnmand issued by user
 */
Process::Process(pid_t id, std::string command) {
	this->pid = id;
	this->command = command;
}

/** Getter method for time
 *
 * @return the cpu time of the process
 */
int Process::get_time() {
	return this->time;
}

/** Getter method for status
 *
 * @return the status of the process
 */
char Process::get_status() {
	return this->status;
}

/** Getter method for command
 *
 * @return the command the process is running
 */
std::string Process::get_command() {
	return this->command;
}

/** Setter method for status
 *
 * @param status the status of the process
 */
void Process::set_status(char status) {
	this->status = status;
}

/** Setter method for time
 *
 * @param time the cput time of the process
 */
void Process::set_time(int time) {
	this->time = time;
}