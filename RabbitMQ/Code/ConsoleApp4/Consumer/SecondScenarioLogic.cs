using Consumer.Observables;
using RabbitMQ.Client;
using System;

namespace Consumer
{
    class SecondScenarioLogic
    {
        static void Main(string[] args)
        {
            var factory = new ConnectionFactory() { HostName = "192.168.30.13", UserName = "atm", Password = "atm" };

            using (var connection = factory.CreateConnection())
            using (var gpsChannel = connection.CreateModel())
            using (var gyrosChannel = connection.CreateModel())
            {
                GpsObservable gpsObservable = new GpsObservable(gpsChannel);
                GyroscopeObservable gyrosObservable = new GyroscopeObservable(gyrosChannel);

                SixthRule rule6 = new SixthRule(gpsObservable);
                SeventhRule scenario2 = new SeventhRule(gyrosObservable);
                Console.ReadLine();
            }
        }
    }
}
