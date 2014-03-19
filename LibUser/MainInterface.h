#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H


#define WINDOW_TITLE "Virtual Fly-Through"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// MODULE NAME: MainInterface                                                 //
//                                                                            //
// DESCRIPTION: Simulate virtual fly-through.                                 //
//                                                                            //
// REMARKS:     The simulation is event-oriented:                             //
//              1. Synchronous (system-triggered) events:                     //
//                 a. Processing the menu command at every cycle.             //
//                 b. Processing the scene when the menu is hidden.           //
//              2. Asynchronous (user-triggered) events:                      //
//                 a. Changing the size of the window.                        //
//                 b. Moving or turning (using the keyboard).                 //
//                 c. Showing or hiding the menu (using the mouse).           //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


void CreateSimulation();
void DestroySimulation();
void AdjustSimulation(int iWindowId);


void OnIdle();
void OnDisplay();
void OnReshape(int iWidth,int iHeight);
void OnSpecial(int iKey,int iX,int iY);
void OnKeyboard(unsigned char iKey,int iX,int iY);
void OnMouse(int iButton,int iState,int iX,int iY);


#endif
