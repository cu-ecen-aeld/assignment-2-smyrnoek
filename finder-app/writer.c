#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // For open()
#include <unistd.h>   // For close() and write()
#include <syslog.h>
#include <string.h>   // For strlen()
int main(int argc, char* argv[])
{
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
    if(argc != 3){
      syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d", argc - 1);	
printf("Invladig number of arugments.\n");	
closelog();
      return 1;
    }

    // Get the arguments
    char *writefile = argv[1]; // Full path to the file
    char *writestr = argv[2]; // Text to write to the file

    // Open the file for writing (create if it doesn't exist, truncate if it does)
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
	syslog(LOG_ERR, "Error opening file: %s", writefile);
        perror("Error opening file");
	closelog();
        return 1; // Exit with error
    }

    // Write the string to the file
    ssize_t bytes_written = write(fd, writestr, strlen(writestr));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Error writing to file: %s", writefile);
	perror("Error writing to file");
        close(fd); // Close the file before exiting
        closelog();
	return 1; // Exit with error
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1; // Exit with error
    }

 // Correct syslog message according to the assignment
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
    printf("Writing '%s' to '%s'\n", writestr, writefile); // Print message to terminal

closelog();
    return 0; // Exit successfully
} 



