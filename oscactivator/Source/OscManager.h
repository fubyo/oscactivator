#pragma once
#include "../oscpack/osc/OscOutboundPacketStream.h"
#include "../oscpack/ip/UdpSocket.h"
#include "../oscpack/osc/OscReceivedElements.h"
#include "../oscpack/osc/OscPacketListener.h"
#include "Pool.h"

#include "../JuceLibraryCode/JuceHeader.h"

#include "../jucedOSC/jucetice_OpenSoundController.h"

#include <vector>
using namespace std;


struct ReceiverRegistration
{
	String address;
	int parameterIndex;
	int port;
	double *pValue;
};

class InputsPanelComponent;
class OutputsPanelComponent;

/*
class SocketThread: public Thread, public osc::OscPacketListener
{
public:
	SocketThread(Array<ReceiverRegistration, CriticalSection>* Receivers, int Port);
	~SocketThread();

	int getPort();

	void run();
	void Break();

private:
	Array<ReceiverRegistration, CriticalSection>* receivers;
	int port;
	ScopedPointer<UdpListeningReceiveSocket> s;

	InputsPanelComponent* ipc;
	OutputsPanelComponent* opc;

protected:
	virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);
};
*/

class OSCListener : public OpenSoundControllerListener
{
	Array<ReceiverRegistration, CriticalSection>* receivers;

public:
	OSCListener(Array<ReceiverRegistration, CriticalSection>* Receivers);
    ~OSCListener ();

    bool handleOSCMessage (OpenSoundController* controller, OpenSoundMessage *message);
};

class OpenSoundSocketThread : public OpenSoundController
{
	Array<ReceiverRegistration, CriticalSection>* receivers;
	
	OutputsPanelComponent* opc;
	ScopedPointer<OSCListener> oscProcessor;

public:
	InputsPanelComponent* ipc;

	OpenSoundSocketThread(Array<ReceiverRegistration, CriticalSection>* Receivers);
	~OpenSoundSocketThread();
};

class OscManager : public Thread
{
public:
    //==============================================================================
	OscManager ();
    ~OscManager();

	void registerReceiver(String Address, int ParameterIndex, int Port, double* pValue);
	void unregisterReceiver(double *pValue);

	void run();
	void stop();

	//==============================================================================
    juce_UseDebuggingNewOperator
    juce_DeclareSingleton (OscManager, false)

private:

	Array<ReceiverRegistration, CriticalSection> receivers;
	//Array<SocketThread*, CriticalSection> sockets;
	OwnedArray<OpenSoundSocketThread> opensoundsockets;

	CriticalSection cs;
};