#include "IMouseReceiver.h"

IMouseReceiver* IMouseReceiver::currentReceiver = nullptr;

void IMouseReceiver::SetCurrentReceiver(IMouseReceiver& receiver) {
	if (currentReceiver) {
		currentReceiver->DisableReceive();
	}
	receiver.EnableReceive();
	currentReceiver = &receiver;
}
