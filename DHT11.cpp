#include "DHT11.h"
#include <wiringPi.h>

using namespace std;

DHT11::DHT11(unsigned int DHT_PIN)
{
	DHTPin = DHT_PIN;
	wiringPiSetup();
}

void DHT11::ReadData(unsigned long & temperture, unsigned long & humidity)
{
	pinMode(DHTPin, OUTPUT);
	digitalWrite(DHTPin, LOW);
	delay(18);
	digitalWrite(DHTPin, HIGH);
	pinMode(DHTPin, INPUT);
	while (digitalRead(DHTPin) == HIGH) continue;
	while (digitalRead(DHTPin) == LOW) continue;
	while (digitalRead(DHTPin) == HIGH) continue;

	bitset<40> DHT_Data;
	for (size_t i = 39; i > 0; --i)
	{
		while (digitalRead(DHTPin) == LOW)continue;
		int t = 0;
		while (digitalRead(DHTPin) == HIGH)
		{
			++t;
			delayMicroseconds(1);
			if (t > 200) break;
		}
		DHT_Data.set(i, t > 40);
	}
	temperture = bitset_range<39, 32>(DHT_Data).to_ulong() - 7;
	humidity = bitset_range<23, 16>(DHT_Data).to_ulong() - 7;
}

DHT11::~DHT11()
{
}
