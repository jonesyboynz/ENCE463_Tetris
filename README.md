ENCE4632016 - TETRIS UNDER FREERTOS.
By Simon Jones

Developed for the stellaris EKS-LM3S1968 Development board. Uses the TI stellaris libraries and the FREERTOS system libraries.
Developed under CCS (to save time), however the system could be built from linux if you can figure out how build the stellaris libraries (you may be able to extract them from the windows installer).

Ensure that the system has at least 0x1600 of stack and heap before running. System clock should also be configured to run at 50MHz.