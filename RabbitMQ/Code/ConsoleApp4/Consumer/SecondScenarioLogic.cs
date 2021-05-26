using Consumer.Observables;
using RabbitMQ.Client;
using System;

namespace Consumer
{
    class SecondScenarioLogic : IDisposable
    {
        IModel gpsChannel;
        IModel gyrosChannel;
        public SecondScenarioLogic(IConnection connection)
        {

            gpsChannel = connection.CreateModel();
            gyrosChannel = connection.CreateModel();
            GpsObservable gpsObservable = new GpsObservable(gpsChannel);
            GyroscopeObservable gyrosObservable = new GyroscopeObservable(gyrosChannel);

            SixthRule rule6 = new SixthRule(gpsObservable);
            SeventhRule rule7 = new SeventhRule(gyrosObservable);
        }

        public void Dispose()
        {
            gpsChannel.Dispose();
            gyrosChannel.Dispose();
        }
    }
}
