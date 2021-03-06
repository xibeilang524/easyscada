/*
 *                         IndigoSCADA
 *
 *   This software and documentation are Copyright 2002 to 2009 Enscada 
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $HOME/LICENSE 
 *
 *   for full copyright notice and license terms. 
 *
 */

/*
*Header For:Modbus
*
*Purpose:
*/

#ifndef include_iec61850driver_h 
#define include_iec61850driver_h

#include "driver.h"
#include "iec61850driverConfiguration.h"
#include "iec61850driverInput.h"
#include "iec61850driverCommand.h"
#include "sptypes.h"
#include "smplstat.h"
#include "common.h"

#ifdef IEC61850DRIVER_EXPORTS
#define IEC61850DRIVERDRV __declspec(dllexport)
#else
#define IEC61850DRIVERDRV //__declspec(dllimport)
#endif

class Iec61850driver_Instance;

struct InstanceCfg // friend to anyone
{
	//IEC61850 TCP
	QString IEC61850ServerIPAddress;  // IEC61850 server IP address (slave)
	QString IEC61850ServerTCPPort;  // IEC61850 server TCP port
	
	unsigned SampleTime; // sampleing time 

	enum {
		TCP = 0
	};

	InstanceCfg() :
	SampleTime(1000),IEC61850ServerIPAddress(""),IEC61850ServerTCPPort("")
	{
	};

	InstanceCfg(const InstanceCfg &m) :
		SampleTime(m.SampleTime),IEC61850ServerIPAddress(m.IEC61850ServerIPAddress),
		IEC61850ServerTCPPort(m.IEC61850ServerTCPPort)
		{
		};
};


class IEC61850DRIVERDRV Iec61850driver : public Driver // all this is private to this one file
{
	Q_OBJECT
	public:
	typedef std::map<QString,Iec61850driver_Instance *, std::less<QString> > IDict;
	IDict Instances;
	enum
	{
		tListUnits = 1, tcreateNewUnit
	};


	Iec61850driver(QObject *parent,const QString &name);
	~Iec61850driver();
	//
	// user interface stuff
	// 
	void UnitConfigure(QWidget *parent, const QString &name, const QString &receipe="(default)"); // configure a unit
	void SetTypeList(QComboBox *pCombo, const QString &unitname); // set the type list for unit type
	void GetInputList(const QString &type, QStringList &,const QString &unit, const QString &name); // set the permitted input IDs
	QWidget * GetSpecificConfig(QWidget *, const QString &spname, const QString &sptype); //specific config for sample point of type
	void GetTagList(const QString &type, QStringList &,const QString &,const QString &); // returns the permitted tags for a given type for this unit
	void CreateNewUnit(QWidget *parent, const QString &, int); // create a new unit - quick configure
	void CommandDlg(QWidget *parent, const QString &name); // command dialog

	//
	// 
	static Iec61850driver *pDriver; // only one instance should be created

	int n_iec_items;
	QString iec_unit_name;
	//
	// Actual driver stuff
	//
	// these are slots - the declarations are virtual in Driver
	//  
	public slots:
	void Start(); // start everything under this driver's control
	void Stop(); // stop everything under this driver's control
	void Command(const QString &, BYTE, LPVOID, DWORD, DWORD); // process a command for a named unit 
	void QueryResponse (QObject *, const QString &, int, QObject*);
};
#endif

