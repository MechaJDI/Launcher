#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN    80

int main(int argc, char *argv[])
{
  // Function prototypes
  
  // Local variables
  FILE *fid;
  char cmdLine[MAX_LINE_LEN];
  
  // CreateProcess parameters
  LPSECURITY_ATTRIBUTES processSA = NULL; // Default
  LPSECURITY_ATTRIBUTES threadSA = NULL; // Default
  BOOL shareRights = TRUE; // Default
  DWORD creationMask = CREATE_NEW_CONSOLE; // Window per process
  LPVOID environment = NULL; // Default
  LPTSTR curDir = NULL; // Default
  STARTUPINFO startInfo; // Result
  PROCESS_INFORMATION procInfo; // Result
  
  /*
  // 1. Read the command line parameters
 // argc = number of words per line
  if(argc != 2) {
          fprintf(stderr, "Usage: launch <launch_set_filename>\n");
          exit(0);
  }
  */
  
  printf("Enter a command filename > ");
  char string[MAX_LINE_LEN];
  scanf("%s", string);
  
  // 2. Open a file that contains a set of commands, entered at parameter line or as first argument
  // If file not found, close program
  if((fid = fopen(string, "r")) == NULL)
  {
         printf("File not found...");
         return 1;
  }       
  
  // 3. For every command in the launch file:
  while(fgets(cmdLine, MAX_LINE_LEN, fid) != NULL) {
                       // a. Read a command from the file
                       if(cmdLine[strlen(cmdLine)-1] == '\n')
                                                     cmdLine[strlen(cmdLine)-1] = '\0';      // Remove NEWLINE
                                                     
                       // b. Create a new process to execute the command
                       ZeroMemory(&startInfo, sizeof(startInfo));
                       startInfo.cb = sizeof(startInfo);
                       if(!CreateProcess(
                                         NULL, // File name of executable
                                         cmdLine, // Command line
                                         processSA, // Process inherited security
                                         threadSA, // Thread inherited security
                                         shareRights, // Rights propagation
                                         creationMask, // Various creation flags
                                         environment, // Environment variables
                                         curDir, // Child's current directory
                                         &startInfo,
                                         &procInfo
                                         )
                       )
                       {
                                         fprintf(stderr, "CreateProcess failed on error %d\n",
                                         GetLastError());
                                         ExitProcess(0);
                       }
  }
                       
  // 4. Terminate after all commands have finished
  return 0;     
        
        
  
}
