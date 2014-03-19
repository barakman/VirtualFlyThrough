#ifndef TRANSLATE_MNGR_H
#define TRANSLATE_MNGR_H


#include "..\GenericClasses\List.h"
#include "..\GraphicElements\Polyhedron.h"


enum AXIS
{
	X_AXIS = 0,
	Y_AXIS = 1,
	Z_AXIS = 2
};


enum DIRECTION
{
	NEGATIVE_DIRECTION = -1,
	POSITIVE_DIRECTION = +1
};


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CLASS NAME:  TranslateMngr                                                 //
//                                                                            //
// DESCRIPTION: Translate the polyhedrons in the scene.                       //
//                                                                            //
// REMARKS:     This manager maintains the following arrays:                  //
//              -The current motion of the user at each axis.                 //
//              -The current rotation of the user at each axis.               //
//              It processes the scene as follows:                            //
//              -Calculates a motion vector and a rotation matrix,            //
//               in a direction which is opposite to that of the user.        //
//              -Calls each polyhedron to translate itself respectively,      //
//               and then to project itself (regardless of the translation).  //
//                                                                            //
// AUTHOR:      Barakman (barakman@yahoo.com)                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


class TranslateMngr
{
public: //Must be invoked once during initialization
	TranslateMngr();
	virtual ~TranslateMngr();
	//--------------------------------------------------------------------------
public: //Can be invoked asynchronously at any cycle
	void SetMnThrst(double fMnThrst);
	void SetRnAngle(double fRnAngle);
	void SetMnDecrease(double fMnDecrease);
	void SetRnDecrease(double fRnDecrease);
	void Move(AXIS eAxis,DIRECTION eDirection);
	void Turn(AXIS eAxis,DIRECTION eDirection);
	//--------------------------------------------------------------------------
public: //Must be invoked synchronously at every cycle
	void Process(List<Polyhedron*>* pPolyhedronList);
	//--------------------------------------------------------------------------
private: //Internal operations
	void CalculateMnVector(double aMnVector[3]);
	void CalculateRnMatrix(double aRnMatrix[3][3]);
	//--------------------------------------------------------------------------
private: //Translation constants
	double m_fMnThrst;    //Motion thrust value
	double m_fRnAngle;    //Rotation angle value
	double m_fMnDecrease; //Motion decrease factor
	double m_fRnDecrease; //Rotation decrease factor
	//--------------------------------------------------------------------------
private: //Translation variables
	double m_aMnAtAxis[3]; //The current motion thrust at each axis
	double m_aRnAtAxis[3]; //The current rotation angle at each axis
	//--------------------------------------------------------------------------
};


#endif
