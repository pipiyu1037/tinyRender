#pragma once

class IMouseReceiver
{
public:
	virtual void EnableReceive() = 0;
	virtual void DisableReceive() = 0;
	static void SetCurrentReceiver(IMouseReceiver& receiver);
	static IMouseReceiver* currentReceiver;
};

